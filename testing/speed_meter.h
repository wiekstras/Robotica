//
// Created by ruben on 6/8/23.
//

#ifndef TESTING_SPEED_METER_H
#define TESTING_SPEED_METER_H


/**
 * Controls the speed of the track motors.
 */
class Speed_Meter
{
public:
    /**
     * Get instance.
     */
    static Speed_Meter* get_instance();

    /**
     * Sets the speed of the track motor.
     * @param analog_value Value that is read from the connected pins.
     */
    static void set_speed(unsigned int analog_value);

    /**
     * Gets the current speed of the track motor.
     * @return speed of track motor
     */
    static unsigned int get_speed();

private:
    /**
     * Represents the singleton instance of Speed_Meter.
     */
    static Speed_Meter* speed_meter;

    /**
     * Declare constructor private, preventing direct construction calls.
     */
    Speed_Meter(){};
};

Speed_Meter* Speed_Meter::speed_meter = nullptr;
#endif //TESTING_SPEED_METER_H
