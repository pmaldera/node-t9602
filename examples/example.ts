import {T9602} from '../lib/';

var sensor:T9602 = new T9602();
console.log(sensor.getHumidity());
console.log(sensor.getTemperature());
