#include <Arduino.h>
#include "speed_meter.h"

// define static member variables.
Speed_Meter* Speed_Meter::speed_meter = nullptr;

Speed_Meter* Speed_Meter::get_instance()
{
    if (speed_meter == nullptr)
    {
        speed_meter = new Speed_Meter;
    }

    return speed_meter;
}

void Speed_Meter::set_speed(int analogValue)
{
    speed = map(analogValue, 0, 15, 0, 255);
}

int Speed_Meter::get_speed()
{
    return speed;
}
