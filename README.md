# CarDisplay
This project implements a Car Display unit that shows the car battery level and status, the car interior temperature and humidity.

## Details
The project main element is an Arduino Nano clone controller board. The board contains:
* ATmega328P microcontroller,
* external supply possibility,
* voltage regulator IC,
* ISP for flashing.

The car battery voltage is measured with the microcontroller built-in ADC module which is a 10-bit SAR converter.
* The voltage is measured with a voltage divider (33k/10k) filtered with a 10uF capacitor.
* The ADC has 5V reference voltage. 
* 21.5V maximum voltage can be measured with this configuration. The car battery has tipically 12V..14.4V so the most accurate part of the ADC characteristic is used.

The temperature and humidity is measured with a DHT22 (AM2302) sensor.
* It has a wide operating range -40°C..+80°C.
* It has a correct accuracy: +-2% relative humidity; +-0.5°C temperature.
* It is supplied with 5V.

The display unit is a 2x16 character size, HD44780 based, blue backlight LCD module.
* It is used in 4-bit data mode.
* It is supplied with 5V.
* The contrast is configurable with a 10k potentio meter.
* The backlight LED current is limited with 330 resistor that results ~15mA current.

## Usage
The unit has to be connected to the direct battery of the car.
The correct battery status can be measured if the ignition key is set to the first ACC position. In this case the measured battery is the same as on the accumulator poles.
If the ignition key is set to the ON position, the measured voltage will be less due to the voltage load of the swiched-on components of the car.

The unit displays a message for 3 seconds after switching on:
```
------------------
|   CarDisplay   |
|      v1.0      |
------------------
```
After the welcome message first the following information will be displayed:
* car battery voltage level in V dimension with one decimal precision,
* car battery voltage status with an informated icon,
* interior temperature in °C dimension with one decimal precision,
* interior humidity in % dimension without decimal precision.
For example:
```
------------------
| 12.6V    24.2C |
| |||||      62% |
------------------
```
The used voltage levels are the following:

Voltage | Status
------- | ------
above 14.7V | overcharge
13.7V - 14.7V | charge (generator mode)
12.6V - 13.7V | 100% capacity
12.4V - 12.6V | 75%-100% capacity
12.2V - 12.4V | 50%-75% capacity
12.0V - 12.2V | 25%-50% capacity
11.8V - 12.0V | 0%-25% capacity
below 11.8V | 0% capacity (battery is dead)

## Additional Information

### Built with
Program | Version
------- | -------
avr-gcc | 4.9.2
avrdude | 6.3
eagle | 7.5.0

### Version
1.0 - Initial version with full functionality

### Author
Gabor Simon | *M.Sc. Electrical Engineer* | *Budapest University of Technology and Economics (BUTE)*

### License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
