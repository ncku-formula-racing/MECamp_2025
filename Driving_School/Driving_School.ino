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



/********** You can modify Here *********/
// PID 參數
// 0 ~ 1
float Kp = 0.4;
float Ki = 0;
float Kd = 0.1;

// 循跡速度
// 勿超過 255
int baseSpeed = 130;

// 馬達轉速
int moveSpeed = 135;
int turnspeed = 150;




/********** You should modify Here *********/
ColorRange RED = { ?, ?, ?, 20 };  // R/G/B average value & error
//ColorRange YELLOW = { ?, ?, ?, 20 };
//ColorRange GREEN = { ?, ?, ?, 20 };
//ColorRange BLUE = { ?, ?, ?, 20 };
//ColorRange BLACK = {?,?, ?, 10};




// PID setting
float error = 0;
float previousError = 0;
float integral = 0;
float derivative = 0;

int red_count = 0;



// 回傳顏色
int detectColor(float R, float G, float B);
// Just follow the roads
void go_straight();
// parking and back to the roads
void parking(); 

void setup() {
  Serial.begin(9600);
  setPin();
}

void loop() {

  float R, G, B;
  // Use the sensor to detect RGB values
  tcs.getRGB(&R, &G, &B);
  /*
  Serial.print("R: "); Serial.print(R);
  Serial.print(" G: "); Serial.print(G);
  Serial.print(" B: "); Serial.println(B);
  Serial.println(detectColor(R,G,B));
*/



// YOU should finish the code
// 請從 ESP32Setting.h 中的函數，以及 go_straight()、parking() 找適合的函數填入 ? 中
  if (detectColor(R, G, B) == Red) {
    switch (red_count) {
      case 0: // parking
        ?;
        red_count++;
        break;
      case 1:  // acceleration
        ?;
        delay(1000);
        red_count++;
        break;
      case 2: // Stop
        ?;
        delay(1000);
        red_count++;
        break;
      default:
        break;
    }
  } 
  else {
    if (red_count > 2) {
      stopMotor();
    } 
    else {
      ?;
    }
  }
}







// If you can understand, you can modify the indexes inside
void go_straight() {
  int leftSensor = analogRead(LPin);
  int rightSensor = analogRead(RPin);
  error = rightSensor - leftSensor;

  // PID 計算
  integral += error;
  derivative = error - previousError;
  previousError = error;

  float correction = Kp * error + Ki * integral + Kd * derivative;

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // 控制四輪同步差速前進
  LR("+", leftSpeed);
  RR("+", rightSpeed);
  LF("+", leftSpeed);
  RF("+", rightSpeed);
}


void parking() {
  stopMotor();
  delay(1000);

  turnRight2(turnspeed);
  delay(100);
  while (analogRead(LPin) < black) {
    turnRight2(turnspeed);
    delay(50);
  }
  turnRight2(turnspeed);
  delay(100);
  stopMotor();
  delay(1000);


  while (analogRead(RPin) < black) {
    turnLeft2(moveSpeed);
    delay(50);
  }
  turnLeft2(moveSpeed);
  delay(100);
  stopMotor();
  delay(1000);
  integral = 0;
  derivative = 0;
}

int detectColor(float R, float G, float B) {
  if (abs(R - RED.R) <= RED.error && abs(G - RED.G) <= RED.error && abs(B - RED.B) <= RED.error)
    return Red;
  /*
  if (abs(R - YELLOW.R) <= YELLOW.error && abs(G - YELLOW.G) <= YELLOW.error && abs(B - YELLOW.B) <= YELLOW.error)
    return "Yellow";

  if (abs(R - GREEN.R) <= GREEN.error && abs(G - GREEN.G) <= GREEN.error && abs(B - GREEN.B) <= GREEN.error)
    return "Green";

  if (abs(R - BLUE.R) <= BLUE.error && abs(G - BLUE.G) <= BLUE.error && abs(B - BLUE.B) <= BLUE.error)
    return "Blue";

  if (abs(R - BLACK.R) <= BLACK.error &&
      abs(G - BLACK.G) <= BLACK.error &&
      abs(B - BLACK.B) <= BLACK.error)
    return "Black";
  */

  return White;
}
