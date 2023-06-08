//
// Created by ruben on 6/8/23.
//

#include "speed_meter.h"

Speed_Meter* Speed_Meter::get_instance()
{
    if (speed_meter == nullptr)
    {
        Speed_Meter* instance;
        speed_meter = instance;
        return speed_meter;
    }
    else return speed_meter;
}