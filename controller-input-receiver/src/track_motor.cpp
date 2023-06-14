//
// Created by ruben on 6/6/23.
//

#include <Arduino.h>
#include "track_motor.h"

Track_Motor::Track_Motor(const  int pin_a, const  int pin_b)
{
    this->pin_a = pin_a;
    this->pin_b = pin_b;
}

void Track_Motor::spin_motor( int speed,  int direction)
{
    if (direction == 0) // clockwise.
    {
        analogWrite(pin_a, 0);
        analogWrite(pin_b, speed);
    }

    if (direction == 1) // counterclockwise.
    {
        analogWrite(pin_a, speed);
        analogWrite(pin_b, 0);
    }
}
