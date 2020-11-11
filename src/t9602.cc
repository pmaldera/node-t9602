#include "t9602.h"

#define I2C_SLAVE 0x0703
#define T9602_ID 0x28

const float T9602::temperatureErrorValue = 9999.0;
const float T9602::humidityErrorValue = 9999.0;

Napi::Object T9602::Init(Napi::Env env, Napi::Object exports) {

  Napi::Function func =
      DefineClass(env,
                  "T9602",
                  {InstanceMethod("getTemperature", &T9602::getTemperature),
                   InstanceMethod("getHumidity", &T9602::getHumidity)});

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("T9602", func);
  return exports;
}

T9602::T9602(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<T9602>(info) {

    int address; // T9602 address
    std::string path = "/dev"; // i2c file folder
    std::string i2cFilesPattern = "i2c"; // i2c files search pattern
    std::string i2cFilePath; // i2c file path
    std::string tempString; // string used to search in dev folder
    DIR *dir;
    int fd;
    
    Napi::Env env = info.Env();
    int length = info.Length();
    
    // Getting device address or using default address.
    if(length > 0)
    {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Incorrect I2C device address.").ThrowAsJavaScriptException();
            return;
        } else {
            address = info[0].As<Napi::Number>().Int32Value();
        }
    } else {
        address = T9602_ID;
    }

    // Getting i2c file path (depending on Raspberry version names can be different).
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            tempString = ent->d_name;
            if(tempString.find(i2cFilesPattern) != std::string::npos) {
                i2cFilePath = std::string(path) + "/" + tempString;
                break;
            }
        }
        closedir (dir);
    } else {
        Napi::TypeError::New(env, "Couldn't find or open /dev.").ThrowAsJavaScriptException();
        return;
    }

    if(i2cFilePath.empty()) {
        Napi::TypeError::New(env, "Couldn't find I2C file, please check if you activated I2C and plugged your device correctly.").ThrowAsJavaScriptException();
        return;
    }

    // Opening i2c file
    if ((fd = open(i2cFilePath.c_str(), O_RDWR)) < 0 ) {
        Napi::TypeError::New(env, "Impossible to open I2C file.").ThrowAsJavaScriptException();
        return;
    }

    // Controling i2c device
    if (ioctl (fd, I2C_SLAVE, address) < 0) {
        Napi::TypeError::New(env, "Impossible to find I2C device.").ThrowAsJavaScriptException();
        return;
    }

    this->fd = fd;
}

Napi::Value T9602::getTemperature(const Napi::CallbackInfo& info) {
    // Temperature in C°
    __uint8_t data[4];
    if(read(fd,data,4) > 0) {
        float temperature = (float)((data[2] * 64) + (data[3] >> 2 )) / 16384.0 * 165.0 - 40.0;
        return Napi::Number::New(info.Env(), temperature);
    } else {
        Napi::Error::New(info.Env(), "Couldn't read temperature.").ThrowAsJavaScriptException();
        return Napi::Number::New(info.Env(), T9602::temperatureErrorValue);
    }
}

Napi::Value  T9602::getHumidity(const Napi::CallbackInfo& info) {
    // % of humidity
    __uint8_t data[2];
    if(read(fd,data,2) > 0) {
        float humidity = (float)(((data[0] & 0x3F ) << 8) + data[1]) / 16384.0 * 100.0;
        return Napi::Number::New(info.Env(), humidity);
    } else {
        Napi::Error::New(info.Env(), "Couldn't read humidity.").ThrowAsJavaScriptException();
        return Napi::Number::New(info.Env(), T9602::humidityErrorValue);
    }
}

T9602::~T9602() {
    close(this->fd);
}