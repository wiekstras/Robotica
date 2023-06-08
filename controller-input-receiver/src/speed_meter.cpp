#include <Arduino.h>
#include "speed_meter.h"

Speed_Meter* Speed_Meter::get_instance()
{
    if (speed_meter == nullptr)
    {
        speed_meter = new Speed_Meter;
    }

    return speed_meter;
}

void Speed_Meter::set_speed(unsigned int analogValue)
{
    speed = map(analogValue, 0, 1023, 0, 255);
}

unsigned int Speed_Meter::get_speed()
{
    return speed;
}
