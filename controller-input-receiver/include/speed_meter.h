//
// Created by ruben on 6/5/23.
// This class is used to handle the speed of the track motors.
//


#ifndef CONTROLLER_INPUT_RECEIVER_SPEED_METER_H
#define CONTROLLER_INPUT_RECEIVER_SPEED_METER_H


class Speed_Meter
{
public:
    /**
     * Sets the speed of the track motor.
     * @param analog_value Value that is read from the connected pins.
     */
    static void set_speed(unsigned int analog_value);

    /**
     * Gets the current speed of the track motor.
     * @return
     */
    static unsigned int get_speed();
};

/**
 * Speed of the track motor.
 */
static unsigned int speed;


#endif //CONTROLLER_INPUT_RECEIVER_SPEED_METER_H
