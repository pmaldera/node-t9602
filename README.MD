# node-t9602

A node module for reading temperature and humidity using T9602 sensor on Raspberry Pi.

## Preliminary warning

This module has only been **tested on Raspbery Pi 4 Model B 4 GiB running on Raspberry PI OS**. <br/>
I'm not aware of all the products differences and **I'm not planning on testing this module on other products myself**. <br/>

**Don't hesitate to tell me about your attempts on other products.** <br/>

|  Model   |   Supported   |  
|----------|:-------------:|
| Raspberry Pi A | ❓ |
| Raspberry Pi B | ❓ |
| Raspberry Pi A+ | ❓ |
| Raspberry Pi B+ | ❓ |
| Raspberry Pi 2 B+ | ❓ |
| Raspberry Pi Zero Zero | ❓ |
| Raspberry Pi Zero W/WH | ❓ |
| Raspberry Pi 3 B | ❓ |
| Raspberry Pi 3 A+ | ❓ |
| Raspberry Pi 3 B+ | ❓ |
| Raspberry Pi 4 B 1GiB | ❓ |
| Raspberry Pi 4 B 2GiB | ❓ |
| Raspberry Pi 4 B 4GiB | ✔ |
| Raspberry Pi 4 B 8GiB | ❓ |
| Raspberry Pi 4 B 400 | ❓ |

<br/>

## Connections on Raspberry Pi 4 Model B

Here is how I connected my t9602 sensor on my Rpi 4 B following the sensor pin design :

- V+ (red cable) on 3.3V
- Ground (green cable) to any Ground Pin
- SDA (white cable) on SDA1 (GPIO2)
- SCL (black cable) on SCL1 (GPIO3)

Refer to [the official Raspberry Pi 4 Model B datasheet](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0_preliminary.pdf) if necessary.


## Installation & Usage

- Don't forget to enable I2C with `sudo raspi-config` and reboot.
- `npm install node-t9602`
- Check examples folder if needed.