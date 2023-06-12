//
// Created by ruben on 6/5/23.
//

#ifndef CONTROLLER_INPUT_RECEIVER_TRACK_MOTOR_H
#define CONTROLLER_INPUT_RECEIVER_TRACK_MOTOR_H

#include <stdint.h>

/**
 * Controls the direction of the track motor.
 */
class Track_Motor
{
public:
    /**
     * Creates a new track motor object.
     * @param pin_a First connected pin value.
     * @param pin_b Second connected pin value.
     */
    Track_Motor(const  int pin_a, const  int pin_b);

    /**
     * Spins the motor in a given direction.
     * @param speed Motor speed.
     * @param direction 0 for clockwise, 1 for counterclockwise.
     */
    void spin_motor( int speed,  int direction);

    /**
     * Return connected pin a.
     * @return connected motor pin a.
     */
    inline  int get_pin_a() const { return pin_a; };

    /**
     * Return connected pin b.
     * @return connected motor pin b.
     */
    inline  int get_pin_b() const { return pin_b; };
private:
    /**
     * First connected pin value.
     */
     int pin_a;

    /**
     * Second connected pin value.
     */
     int pin_b;
};

#endif //CONTROLLER_INPUT_RECEIVER_TRACK_MOTOR_H
