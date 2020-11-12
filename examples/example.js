"use strict";
exports.__esModule = true;
var lib_1 = require("../lib/");
var sensor = new lib_1.T9602();
console.log(sensor.getHumidity());
console.log(sensor.getTemperature());
