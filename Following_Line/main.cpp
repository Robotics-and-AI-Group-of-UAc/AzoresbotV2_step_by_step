#include <Arduino.h>
#include "ESP32MotorControl.h"

#define LEFT 34
#define CENTER 35
#define RIGHT 32

ESP32MotorControl MotorControl = ESP32MotorControl();

void setup()
{
  MotorControl.attachMotors(17, 18, 26, 27);
  Serial.begin(115200);
  pinMode(LEFT, INPUT);
  pinMode(CENTER, INPUT);
  pinMode(RIGHT, INPUT);  
}

void loop(){

      if (digitalRead(LEFT) == 0 && digitalRead(RIGHT) == 0 && digitalRead(CENTER) == 1)
      {
        MotorControl.motorForward(0, 50);
        MotorControl.motorForward(1, 50);
      }
      else if (digitalRead(LEFT) == 1)
      {
        MotorControl.motorForward(1, 55);
        MotorControl.motorReverse(0, 20);
      }
      else if (digitalRead(RIGHT) == 1)
      {
        MotorControl.motorReverse(1, 20);
        MotorControl.motorForward(0, 55);
      }
      else
      {
        MotorControl.motorForward(0, 50);
        MotorControl.motorForward(1, 50);
      }
}
