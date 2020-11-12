var T9602 = require('../lib').T9602;
var sensor = new T9602();
console.log('Temperature : ' + sensor.getTemperature() + ' °C');
console.log('Humidity : ' + sensor.getHumidity() + ' %');