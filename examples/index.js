var T9602 = require('../lib');
var sensor = new T9602();
console.log(sensor.getTemperature());
console.log(sensor.getHumidity());