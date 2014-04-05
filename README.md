# PHPUnit-NeoPixel-Indicator

Author: Dan Ruscoe (dan@ruscoe.org).

A PHP and Arduino system to display PHPUnit test statuses as a light color using an Adafruit NeoPixel.

Only tested on Linux, but should run on Windows and OS X as long as all requirements are met.

[YouTube demo video](http://youtu.be/0OtbiL9Lrsg)

![PHPUnit-NeoPixel-Indicator in action](http://img.ruscoe.org/arduino/phpunit-neopixel-indicator.png)

## Requirements

### Hardware
* [Arduino](http://www.arduino.cc/) or Arduino-compatible development board.
  * Tested on Arduino Uno.
* One [Adafruit NeoPixel](http://www.adafruit.com/products/1260)
  * Multiple NeoPixels may be used with a minor code change.
* Jumper cables or other means of connecting the NeoPixel to the Arduino board.

### Software
* [Arduino IDE](http://arduino.cc/en/Main/Software)
* [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
* PHP 5.3 or greater.
* [PHP Serial](https://github.com/Xowap/PHP-Serial) (Installed via Composer)
* [PHPUnit](http://phpunit.de/)

## Circuit Construction

[These alligator clip cables](http://www.adafruit.com/products/1592) work well with regular male/male jumper cables for Arduino prototyping.

With the Arduino board **powered off**:
* Connect the board's 5V pin to the NeoPixel's VCC (+) pad.
* Connect the board's GND pin to the NeoPixel's GND (-) pad.
* Connect pin 8 of the board to the NeoPixel's data-in pad.

## Installation

Clone this repo locally.
```bash
git clone git@github.com:ruscoe/PHPUnit-NeoPixel-Indicator.git PHPUnit-NeoPixel-Indicator
```

### Arduino

Copy the Arduino sketch from the `PHPUnit-NeoPixel-Indicator/arduino` directory into your Arduino sketchbook directory.

Open or restart the Arduino IDE and open the UnitTestNeoPixelIndicator sketch from the File / Sketchbook menu.

Connect your Arduino board circuit (see [Circuit Construction](#circuit-construction)) to your PC's USB port and take note of the serial port in use under the Tools / Serial Port menu. You'll need that later.

Upload the sketch to your Arduino board via the File / Upload menu.

If everything went well, the NeoPixel will be glowing green.

### PHP

In the `PHPUnit-NeoPixel-Indicator/php` directory:

Get dependencies using Composer:
```bash
curl -sS https://getcomposer.org/installer | php
```
```bash
php composer.phar install
```

Open PHPUnitIndicatorListener.php and alter the SERIAL_PORT constant to match the serial port your Arduino board is connected to. See the Tools / Serial Port menu in the Arduino IDE.

#### Note for Linux Users

Your user most likely won't have permission to write to serial ports. You can either run unit tests as root / sudo (not ideal) or check which group has permission to write to the serial port you want to use and add your user to that group.

Substitute your serial port to get groups with permission to write to it.
```bash
ls -l /dev/ttyUSB0
```
Substitute groupName and userName to add your user to that group.
```bash
usermod -a -G groupName userName
```

#### Example Tests

You should now be able to run both example unit tests and see the NeoPixel change color to reflect the results.

```bash
phpunit tests/ExampleSuccessTest.php
```
The NeoPixel should turn yellow then green.

```bash
phpunit tests/ExampleFailureTest.php
```
The NeoPixel should turn yellow then red.

Copy `phpunit.xml` into other PHPUnit test directories to use this listener with your projects. Make sure the path to PHPUnitIndicatorListener.php remains correct.
