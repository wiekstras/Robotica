#ifndef CONTROLLER_INPUT_RECEIVER_SPEED_METER_H
#define CONTROLLER_INPUT_RECEIVER_SPEED_METER_H

/**
 * Controls the speed of the track motors.
 */
class Speed_Meter
{
public:
    /**
     * Prevent object from being cloned.
     * @param other
     */
    Speed_Meter(Speed_Meter &other) = delete;

    /**
     * Prevent object from being assigned.
     */
    void operator=(const Speed_Meter&) = delete;

    /**
     * Get instance.
     */
    static Speed_Meter* get_instance();

    /**
     * Sets the speed of the track motor.
     * @param analog_value Value that is read from the connected pins.
     */
    void set_speed(int analog_value);

    /**
     * Gets the current speed of the track motor.
     * @return speed of track motor
     */
    int get_speed();

private:
    /**
     * Represents the singleton instance of Speed_Meter.
     */
    static Speed_Meter* speed_meter;

    /**
     *
     */
    int speed;

    /**
     * Declare constructor private, preventing direct construction calls.
     */
    Speed_Meter(){};
};

#endif //CONTROLLER_INPUT_RECEIVER_SPEED_METER_H
