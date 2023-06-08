//
// Created by ruben on 6/6/23.
//

#include "motor_direction.h"

Motor_Direction::Motor_Direction(int yValueMin, int yValueMax, int xValueMin, int xValueMax)
{
    y_value_min = yValueMin;
    y_value_max = yValueMax;
    x_value_min = xValueMin;
    x_value_max = xValueMax;
}

void Motor_Direction::set_incoming_values(int incomingX, int incomingY)
{
    incoming_x = incomingX;
    incoming_y = incomingY;
}

void Motor_Direction::forward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed)
{
    motor_one.spin_motor(speed, 0);
    motor_two.spin_motor(speed, 0);
    motor_three.spin_motor(0, 0);
}

void Motor_Direction::backward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed)
{
    motor_one.spin_motor(speed, 1);
    motor_two.spin_motor(speed, 1);
    motor_three.spin_motor(0, 0);
}

void Motor_Direction::right(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed)
{
    motor_one.spin_motor(speed * 0.66, 0);
    motor_two.spin_motor(speed, 0);
    motor_three.spin_motor(speed, 0);
}

void Motor_Direction::left(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, unsigned int speed)
{
    motor_one.spin_motor(speed, 1);
    motor_two.spin_motor(speed, 1);
    motor_three.spin_motor(speed * 0.66, 1);
}

int Motor_Direction::y()
{
    return incoming_y;
}

int Motor_Direction::x()
{
    return incoming_x;
}

int *Motor_Direction::min_max_y() const
{
    int* arr = new int[2];
    arr[0] = y_value_min;
    arr[1] = y_value_max;
    return arr;
}

int *Motor_Direction::min_max_x() const
{
    int* arr = new int[2];
    arr[0] = x_value_min;
    arr[1] = x_value_max;
    return arr;
}