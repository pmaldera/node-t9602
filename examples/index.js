var T9602 = require('../lib');
var sensor = new T9602();
console.log('Temperature : ' + sensor.getTemperature() + ' °C');
console.log('Humidity : ' + sensor.getHumidity() + ' %');