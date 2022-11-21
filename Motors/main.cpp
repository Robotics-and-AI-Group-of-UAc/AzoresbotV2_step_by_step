#include <Arduino.h>
#include "Motor.h"


// Motors instance
Motor motor_right(16, 17, 18);
Motor motor_left(25, 26, 27);

// Line sensor
const int left   = 34;
const int center = 35;
const int right  = 32;

void setup()
{
    pinMode(left, INPUT);
    pinMode(center, INPUT);
    pinMode(right, INPUT);
}

void loop()
{
    if (digitalRead(left) == 0 && digitalRead(right) == 0 && digitalRead(center) == 1) {
        motor_right.avancar(150);
        motor_left.avancar(150);
    } else if (digitalRead(left) == 1) {
        motor_right.avancar(170);
        motor_left.avancar(40);
    } else if (digitalRead(right) == 1) {
        motor_right.avancar(40);
        motor_left.avancar(170);
    }
}
