//
// Created by ruben on 6/5/23.
// In this file the trackmotor
//

#ifndef CONTROLLER_INPUT_RECEIVER_TRACK_MOTOR_H
#define CONTROLLER_INPUT_RECEIVER_TRACK_MOTOR_H


class Track_Motor
{
public:
    /**
     * Creates a new track motor object.
     * @param pin_a First connected pin value.
     * @param pin_b Second connected pin value.
     */
    Track_Motor(const unsigned int pin_a, const unsigned int pin_b);

    /**
     * Spins the motor in a given direction.
     * @param speed Motor speed.
     * @param direction 0 for clockwise, 1 for counterclockwise.
     */
    void spin_motor(unsigned int speed, unsigned int direction);
private:
    /**
     * First connected pin value.
     */
    unsigned int pin_a;

    /**
     * Second connected pin value.
     */
    unsigned int pin_b;
};


#endif //CONTROLLER_INPUT_RECEIVER_TRACK_MOTOR_H
