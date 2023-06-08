//
// Created by ruben on 6/5/23.
//

#ifndef CONTROLLER_INPUT_RECEIVER_MOTOR_DIRECTION_H
#define CONTROLLER_INPUT_RECEIVER_MOTOR_DIRECTION_H

#include "track_motor.h"

/**
 * Motor direction control class.
 */
class Motor_Direction
{
public:
    /**
     * Set the min and max value range of the read analog values.
     * @param yValueMin min-y value
     * @param y_value_max max-y value
     * @param x_value_min min-x value
     * @param x_value_max max-x value
     */
    Motor_Direction (int yValueMin, int yValueMax, int xValueMin, int xValueMax);

    /**
     * Sets the incoming x and y controller values.
     * @param incomingX received analog x value.
     * @param incomingY received analog y value.
     */
    void set_incoming_values(int incomingX, int incomingY);

    /**
     * Gets the analog y value.
     * @return analog y value.
     */
    int y();

    /**
     * Gets the analog x value.
     * @return analog x value.
     */
    int x();

    /**
     * Gets the min and max y value.
     * @return a pointer to an array holding the min and max y value.
     */
    int* min_max_y() const;

    /**
     * Gets the min and max x value.
     * @return a pointer to an array holding the min and max x value.
     */
    int* min_max_x() const;

    /**
     * Move robot forward.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void forward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed);

    /**
     * Move robot backward.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void backward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed);

    /**
     * Move robot right.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void right(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed);

    /**
     * Move robot left.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void left(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed);

private:
    // Declare min, max, and incoming values to decide the direction of the joystick based on analog values.
    int y_value_min, y_value_max, x_value_min, x_value_max, incoming_x{}, incoming_y{};
};


#endif //CONTROLLER_INPUT_RECEIVER_MOTOR_DIRECTION_H
