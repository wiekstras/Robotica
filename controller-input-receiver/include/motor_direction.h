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
     * Prevent object from being cloned.
     * @param Motor_Direction object.
     */
    Motor_Direction(Motor_Direction &other) = delete;

    /**
     * Prevent object from being assigned.
     */
    void operator=(const Motor_Direction&) = delete;

    /**
     * Get instance.
     */
    static Motor_Direction* get_instance(int yValueMin, int yValueMax, int xValueMin, int xValueMax);

    void set_x(int incomingX);

    void set_y(int incomingY);

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

    int get_min_y() const;
    int get_max_y() const;
    int get_min_x() const;
    int get_max_x() const;

    /**
     * Move robot forward.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void forward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed);

    /**
     * Move robot backward.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void backward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed);

    /**
     * Move robot right.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void right(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed);

    /**
     * Move robot left.
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void left(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed);

    /**
     * Turn motors off
     * @param motor_one First motor.
     * @param motor_two Second motor.
     * @param motor_three Third motor.
     */
    void not_moving(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three);

    void rotate(Track_Motor &motor_one, Track_Motor &motor_two, Track_Motor &motor_three, int speed, int direction);

private:
    /**
     * Set the min and max value range of the read analog values.
     * @param yValueMin min-y value
     * @param y_value_max max-y value
     * @param x_value_min min-x value
     * @param x_value_max max-x value
     */
    Motor_Direction (int yValueMin, int yValueMax, int xValueMin, int xValueMax)
    {
        y_value_min = yValueMin;
        y_value_max = yValueMax;
        x_value_min = xValueMin;
        x_value_max = xValueMax;
    };

    /**
    * Represents the singleton instance of Motor_Direction.
    */
    static Motor_Direction* motor_direction;

    // Declare min, max, and incoming values to decide the direction of the joystick based on analog values.
    int y_value_min, y_value_max, x_value_min, x_value_max, incoming_x = 0, incoming_y = 0;
};


#endif //CONTROLLER_INPUT_RECEIVER_MOTOR_DIRECTION_H
