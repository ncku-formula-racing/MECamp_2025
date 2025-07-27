// line_tracking
/***********************************************************
 * Copyright (C) 2025 NCKU Formula Racing. All right reserved.
 ***********************************************************/

/*
 * This is a line tracking lab.
 *
 * The only thing you have to do is upload the code
 * And make the car move ！
 * 
 * You may also modify the index below to make the car faster and more stable
 * Here's the example code. Good luck.
 */
#include "ESP32Setting.h"


/********** You can modify Here *********/
// PID 參數
// 0 ~ 1
float Kp = 0.4;
float Ki = 0.0;
float Kd = 0.1;

// 速度
// 勿超過 255
int baseSpeed = 100;
/****************************************/


// PID setting
float error = 0;
float previousError = 0;
float integral = 0;
float derivative = 0;
// 循跡
void go_straight();



void setup() {
  Serial.begin(9600);
  setPin();
}

void loop() {
  go_straight();
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
