// UltraSound Lab
/***********************************************************
 * Copyright (C) 2025 NCKU Formula Racing. All right reserved.
 ***********************************************************/

/*
 * This is a UltraSound lab.
 * You need to implement obstacle avoidance using an ultrasonic sensor
 * 
 * Finish the code！ 
 * And try to make your car faster
 * Here's the example code. Good luck.
 */

#include "ESP32Setting.h"
int black = 500;
void go_straight(); //循跡
void avoid_obs();   //避障

/********** You can modify Here *********/
// 循跡速度及轉彎時速度
// 勿超過255
int baseSpeed = 150;
int avoidspeed = 200;

// PID 參數
// 0 ~ 1
float Kp = 0.4;
float Ki = 0.0;
float Kd = 0.1;

//障礙物距離
int obs = 30;
/********** You can modify Here *********/

// PID setting
float error = 0;
float previousError = 0;
float integral = 0;
float derivative = 0;

//初始車道
int lane = 3;   



int pre_dis ;
void setup() {
  Serial.begin(9600);
  setPin();
  pre_dis = ultraDis();
}

// 在 ? 中填入avoid_obs()、 go_straight() 或 ESP32Setting.h 中的函數
void loop() {
  int dis = 0.5*pre_dis + 0.5*ultraDis();
  pre_dis = dis;

  if( dis < obs ){
    ?;
  }
  else{
    ?;
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


void avoid_obs(){

  stopMotor();
  delay(500);

  // 判斷要向左還是向右
  int r;  // 向右:1, 向左:0
  if( lane == 1 ){
    r = 0;
  }
  else if( lane == 5 ){
    r = 1;
  }
  else{
    r = random(0,1);
  }

  if( r == 0 ){     //向右轉
    turnRight2(avoidspeed);
    delay(500);
    while(analogRead(RPin) < black){
      turnRight2(baseSpeed);
      delay(100);
    }

    stopMotor();
    delay(1000);
    lane++;
  }

  else if( r == 1  ) { //向左轉
    turnLeft2(avoidspeed);
    delay(500);
    while(analogRead(LPin) < black ){
      turnLeft2(baseSpeed);
      delay(100);
    }

    stopMotor();
    delay(1000);
    lane--;
  }
}


