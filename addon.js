var T9602 = require('bindings')('t9602-rpi').T9602;
var obj = new T9602();
console.log(obj.getTemperature());
console.log(obj.getHumidity());