#include "t9602.h"

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
  Napi::Env env = info.Env();

    int length = info.Length();

    int address; 
    std::string path = "/dev";
    std::string i2cFilePath;
    std::string tempString;
    DIR *dir;
    
    if(length > 0)
    {
        if (!info[0].IsNumber()) {
            Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
            return;
        } else {
            address = info[0].As<Napi::Number>().Int32Value();
        }
    } else {
        address = 0x28;
    }


    struct dirent *ent;
    if ((dir = opendir ("/dev")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            tempString = ent->d_name;
            if(tempString.find("i2c") != std::string::npos) {
                i2cFilePath = std::string("/dev/") + tempString;
                break;
            }
        }
        closedir (dir);
    } else {
        Napi::TypeError::New(env, "Couldn't find /dev ????").ThrowAsJavaScriptException();
        return;
    }

    if(i2cFilePath.empty()) {
        Napi::TypeError::New(env, "Couldn't find I2C file, please check if you activated I2C and plugged your device correctly.").ThrowAsJavaScriptException();
        return;
    }

    int fd;

    if ((fd = open(i2cFilePath.c_str(), O_RDWR)) < 0 ) {
        Napi::TypeError::New(env, "Impossible to open I2C file.").ThrowAsJavaScriptException();
        return;
    }

    if (ioctl (fd, this->I2C_SLAVE, address) < 0) {
        Napi::TypeError::New(env, "Impossible to find I2C device.").ThrowAsJavaScriptException();
        return;
    }

    this->fd = fd;
}

Napi::Value T9602::getTemperature(const Napi::CallbackInfo& info) {
    __uint8_t data[4];
    if(read(fd,data,4) > 0) {
        float temperature = (float)((data[2] * 64) + (data[3] >> 2 )) / 16384.0 * 165.0 - 40.0;
        return Napi::Number::New(info.Env(), temperature);
    } else {
        Napi::Error::New(info.Env(), "Couldn't read temperature.").ThrowAsJavaScriptException();
        return Napi::Number::New(info.Env(), this->temperatureErrorValue);
    }
}

Napi::Value  T9602::getHumidity(const Napi::CallbackInfo& info) {
    __uint8_t data[2];
    if(read(fd,data,2) > 0) {
        float humidity = (float)(((data[0] & 0x3F ) << 8) + data[1]) / 16384.0 * 100.0;
        return Napi::Number::New(info.Env(), humidity);
    } else {
        Napi::Error::New(info.Env(), "Couldn't read humidity.").ThrowAsJavaScriptException();
        return Napi::Number::New(info.Env(), this->humidityErrorValue);
    }
}