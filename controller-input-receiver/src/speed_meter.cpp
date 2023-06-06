//
// Created by ruben on 6/5/23.
//

#include <Arduino.h>
#include "speed_meter.h"

void Speed_Meter::set_speed(unsigned int analogValue)
{
    speed = map(analogValue, 0, 1023, 0, 255);
}

unsigned int Speed_Meter::get_speed()
{
    return speed;
}
