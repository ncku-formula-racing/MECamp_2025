#include "ESP32Setting.h"

void setPin(){
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(LR1, OUTPUT);
    pinMode(LR2, OUTPUT);
    pinMode(LR_PWM, OUTPUT);
    pinMode(RR1, OUTPUT);
    pinMode(RR2, OUTPUT);
    pinMode(RR_PWM, OUTPUT);
    pinMode(LF1, OUTPUT);
    pinMode(LF2, OUTPUT);
    pinMode(LF_PWM, OUTPUT);
    pinMode(RF1, OUTPUT);
    pinMode(RF2, OUTPUT);
    pinMode(RF_PWM, OUTPUT);
}


void LF(String dir, int speed){
    if (dir == "+"){
        digitalWrite(LF1, HIGH);
        digitalWrite(LF2, LOW);
        analogWrite(LF_PWM, speed);
    }
    else if (dir == "-"){
        digitalWrite(LF1, LOW);
        digitalWrite(LF2, HIGH);
        analogWrite(LF_PWM, speed);
    }
    else{
        digitalWrite(LF1, LOW);
        digitalWrite(LF2, LOW);
    }
}

void RF(String dir, int speed){
    if (dir == "+"){
        digitalWrite(RF1, HIGH);
        digitalWrite(RF2, LOW);
        analogWrite(RF_PWM, speed);
        //analogWrite(RF_PWM, motorspeed*0.6);
    }
    else if (dir == "-"){
        digitalWrite(RF1, LOW);
        digitalWrite(RF2, HIGH);
        analogWrite(RF_PWM, speed);
        //analogWrite(RF_PWM, motorspeed*0.6);
    }
    else{
        digitalWrite(RF1, LOW);
        digitalWrite(RF2, LOW);
    }
}

void LR(String dir, int speed){
    if (dir == "+"){
        digitalWrite(LR1, HIGH);
        digitalWrite(LR2, LOW);
        analogWrite(LR_PWM, speed);
    }
    else if (dir == "-"){
        digitalWrite(LR1, LOW);
        digitalWrite(LR2, HIGH);
        analogWrite(LR_PWM, speed);
    }
    else{
        digitalWrite(LR1, LOW);
        digitalWrite(LR2, LOW);
    }
}

void RR(String dir, int speed){
    if (dir == "+"){
        digitalWrite(RR1, HIGH);
        digitalWrite(RR2, LOW);
        analogWrite(RR_PWM, speed);
    }
    else if (dir == "-"){
        digitalWrite(RR1, LOW);
        digitalWrite(RR2, HIGH);
        analogWrite(RR_PWM, speed);
    }
    else{
        digitalWrite(RR1, LOW);
        digitalWrite(RR2, LOW);
    }
}

void forward(int speed){
  LR("+", speed);
  RR("+", speed);
  LF("+", speed);
  RF("+", speed);
}


void backward(int speed){
  LR("-", speed);
  RR("-", speed);
  LF("-", speed);
  RF("-", speed);
}

void turnLeft1(int speed){
  LR("+", speed);
  RR("-", speed);
  LF("-", speed);
  RF("+", speed);
}

void turnRight1(int speed){
  LR("-", speed);
  RR("+", speed);
  LF("+", speed);
  RF("-", speed);
}


void turnLeft2(int speed){
  LR("+", speed);
  RR("", 0);
  LF("", 0);
  RF("+", speed);
}

void turnRight2(int speed){
  LR("", 0);
  RR("+", speed);
  LF("+", speed);
  RF("", 0);
}

void turnLeft3(String dir, int speed){
  LR("", 0);
  RR(dir, speed);
  LF("", 0);
  RF(dir, speed);
}

void turnRight3(String dir, int speed){
  LR(dir, speed);
  RR("", 0);
  LF(dir, speed);
  RF("", 0);
}

void cycleLeft(int speed){
  LR("-", speed);
  RR("+", speed);
  LF("-", speed);
  RF("+", speed);
}


void cycleRight(int speed){
  LR("+", speed);
  RR("-", speed);
  LF("+", speed);
  RF("-", speed);
}

void stopMotor() {
  analogWrite(LR_PWM, 0);
  analogWrite(RR_PWM, 0);
  analogWrite(LF_PWM, 0);
  analogWrite(RF_PWM, 0);
}


int ultraDis(){
    long duration, distance;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration = pulseIn(ECHO, HIGH);

    distance = duration * 0.034 / 2;

    delay(50);

    return distance;
}