#include "Adafruit_WS2801.h"
#include "SPI.h"
//#include <ccspi.h>
#include <string.h>
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_ADXL345_U.h>

//Data PIN for NeoPixel
#define PIN 6
#define Z_AXIS 0
#define Y_AXIS 1
#define X_AXIS 2
#define LEDS 20

uint32_t ip;

/* Assign a unique ID to this sensor at the same time */
//Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


//led values
byte ledValues[3]; //  RGB
int ledSteps[3]; //inc- or decrement value per color

uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(LEDS, dataPin, clockPin);
void setup()
{
  //setup serial
  Serial.begin(115200);
  
  //accel.setRange(ADXL345_RANGE_8_G);

  //initial values for color values and increment steps
  ledValues[0] = 0;
  ledValues[1] = 0;
  ledValues[2] = 0;

  ledSteps[0] = 0;
  ledSteps[1] = 0;
  ledSteps[2] = 0;

  delay(1000);

  strip.begin();
  strip.show();

  //show that we are alive
  strip.setPixelColor(0, Color(127, 0, 0));
  strip.show();
  delay(500);

  strip.setPixelColor(0, Color(0, 127, 0));
  strip.show();
  delay(500);

  strip.setPixelColor(0, Color(0, 0, 127));
  strip.show();
  delay(500);

  strip.setPixelColor(0, Color(0, 63, 127));
  strip.show();
  delay(500);
  strip.setPixelColor(0, Color(0, 0, 0));
  strip.show();
  
}

void loop(void) 
{

  int treshold_min = 280;
  int treshold_max = 600;
  float multyplier = 255/float(treshold_max-treshold_min);
  int z_axis = analogRead(Z_AXIS);
  int y_axis = analogRead(Y_AXIS);
  int x_axis = analogRead(X_AXIS);
  //Serial.println("values");
  //Serial.println(z_axis);
  //Serial.println(y_axis);
  //Serial.println(x_axis);
  
  if(z_axis < treshold_min) {
    z_axis = treshold_min;
  } else if(z_axis > treshold_max) {
    z_axis = treshold_max;
  } 

  if(x_axis < treshold_min) {
    x_axis = treshold_min;
  } else if(x_axis > treshold_max) {
    x_axis = treshold_max;
  } 

  if(y_axis < treshold_min) {
    y_axis = treshold_min;
  } else if(y_axis > treshold_max) {
    y_axis = treshold_max;
  } 

  z_axis = z_axis - treshold_min;
  x_axis = x_axis - treshold_min;
  y_axis = y_axis - treshold_min;
  
  Serial.println("-------------");
  //Serial.println(z_axis);
  //Serial.println(y_axis);
  //Serial.println(x_axis);
  //Serial.println("* * *");
  //Serial.println(z_axis*multyplier);
  //Serial.println(y_axis*multyplier);
  //Serial.println(x_axis*multyplier);
  
  //strip.setPixelColor(0, Color((int) x_axis*multyplier,(int) y_axis*multyplier, (int) z_axis*multyplier));
  setColor((int) x_axis*multyplier,(int) y_axis*multyplier, (int) z_axis*multyplier);
  strip.show();
  delay(60);
}

uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = b;
  c <<= 8;
  c |= r;
  c <<= 8;
  c |= g;
  return c;
}

void setColor(int red, int green, int blue)
{
  int i;
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Color(green, blue, red));
  }
   strip.show();
}
