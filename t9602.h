#ifndef T9602_H
#define T9602_H
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <napi.h>

class T9602 : public Napi::ObjectWrap<T9602> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        T9602(const Napi::CallbackInfo& info);

    private:
        Napi::Value getTemperature(const Napi::CallbackInfo& info);
        Napi::Value getHumidity(const Napi::CallbackInfo& info);
        
        int address;
        int fd;
        const int temperatureErrorValue = 9999;
        const int humidityErrorValue = 9999;
        const int I2C_SLAVE = 0x0703;
};

#endif