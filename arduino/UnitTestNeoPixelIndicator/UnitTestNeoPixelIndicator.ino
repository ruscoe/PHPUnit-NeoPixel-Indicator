#include <Adafruit_NeoPixel.h>

/*
 Unit Test Indicator Serial Listener
 
 Sets the color of an Adafruit NeoPixel based on
 unit test status codes from incoming serial data.
 
 The circuit:
 * Requires at least one Adafruit NeoPixel: http://www.adafruit.com/products/1260
 * Arduino GND pin connected to NeoPixel VCC (-) pad.
 * Arduino +5V pin connected to NeoPixel GND (+) pad.
 * Arduino pin 8 connected to NeoPixel data-in pad.
 * Additional NeoPixels may be connected in series
   to the data output pad of the initial NeoPixel.
 
 By Dan Ruscoe
 */

const int LED_PIN = 8;

const String TEST_STATUS_START = "START";
const String TEST_STATUS_SUCCESS = "SUCCESS";
const String TEST_STATUS_FAILURE = "FAILURE";

const int SERIAL_DELIMITER = (int) '|';

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t startColor = strip.Color(20, 15, 0);
uint32_t successColor = strip.Color(0, 20, 0);
uint32_t failureColor = strip.Color(20, 0, 0);

char serialBuffer[16];

String serialData = "";
int incomingByte = 0;

boolean reachedDelimiter = false;

void setup() {
  strip.begin();
  
  // Start in success state.
  setColor(successColor);

  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    // Read the incoming serial data.
    incomingByte = Serial.read();
    if (incomingByte == -1) {
      setColor(failureColor);
      break;
    }
    else if (incomingByte == SERIAL_DELIMITER) {
      reachedDelimiter = true;
      break;
    }
    else {
      serialData += (char) incomingByte;
    }
  }
  if (reachedDelimiter) {
    // Copy read serial data into char array.
    int stringLength = serialData.length();

    String testStatus = "";
    int i;
    for (i = 0; i < stringLength; i++) {
      testStatus += char(serialData[i]);
    }

    serialData = "";
    reachedDelimiter = false;

    if (testStatus == TEST_STATUS_START) {
      setColor(startColor);
    }
    else if (testStatus == TEST_STATUS_SUCCESS) {
      setColor(successColor);
    }
    else if (testStatus == TEST_STATUS_FAILURE) {
      setColor(failureColor);
    }
  }
}

void setColor(uint32_t color) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}
