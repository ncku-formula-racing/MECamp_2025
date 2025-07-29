// Driving_school
/***********************************************************
 * Copyright 2025(c) NCKU Formula Racing. All right reserved.
 ***********************************************************/

/*
 * This is a Driving School lab.
 * We will use the color sensor of Adafruit "TCS34725"
 * You need to use a color sensor to detect the RGB values of
 * specific color (espacially RED), and then perform different
 * actions based on the rules.
 *
 * You may encounter three detection points
 * The first one you need to do parallel parking
 * The second one you need to accrelerate
 * The third one you need to stop
 * 
 * Here's the example code. Good luck.
 */


#include "ESP32Setting.h"
#define Red 0
#define White 1
int black = 500;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X);

struct ColorRange {
  int R, G, B;
  int error;  // acceptable error range
};




//ColorRange RED = { ?, ?, ?, 20 };  // R/G/B average value & error
//ColorRange YELLOW = { ?, ?, ?, 20 };
//ColorRange GREEN = { ?, ?, ?, 20 };
//ColorRange BLUE = { ?, ?, ?, 20 };
//ColorRange BLACK = {?,?, ?, 10};


void setup() {
  Serial.begin(9600);
  setPin();
}

void loop() {

  float R, G, B;
  // Use the sensor to detect RGB values
  tcs.getRGB(&R, &G, &B);
  Serial.print("R: "); Serial.print(R);
  Serial.print(" G: "); Serial.print(G);
  Serial.print(" B: "); Serial.println(B);
}

