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
        static const float temperatureErrorValue;
        static const float humidityErrorValue;
        T9602(const Napi::CallbackInfo& info);
        ~T9602();

    private:
        Napi::Value getTemperature(const Napi::CallbackInfo& info);
        Napi::Value getHumidity(const Napi::CallbackInfo& info);
        
        int address;
        int fd;
};

#endif