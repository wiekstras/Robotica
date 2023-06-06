//
// Created by ruben on 6/6/23.
//

#include "track_motor.h"

Track_Motor::Track_Motor(const unsigned int pin_a, const unsigned int pin_b)
{
    this->pin_a = pin_a;
    this->pin_b = pin_b;
}

void Track_Motor::spin_motor(unsigned int speed, unsigned int direction)
{
    if (direction == 0) // Clockwise.
    {
        this->pin_a = speed;
        this->pin_b = 0;
    } else if (direction == 1) // Counterclockwise.
    {
        this->pin_a = 0;
        this->pin_b = speed;
    }
}
