const addon = require('../build/Release/t9602-rpi');

export interface T9602 {
    getTemperature() : number;
    getHumidity() : number;
}

export var T9602 : {
    new(addres?: number) : T9602;
} = addon.T9602;