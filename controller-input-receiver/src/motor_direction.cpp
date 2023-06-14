//
// Created by ruben on 6/6/23.
//

#include <HardwareSerial.h>
#include "motor_direction.h"

Motor_Direction* Motor_Direction::motor_direction = nullptr;

Motor_Direction* Motor_Direction::get_instance(int yValueMin, int yValueMax, int xValueMin, int xValueMax)
{
    if (motor_direction == nullptr)
    {
        motor_direction = new Motor_Direction(yValueMin, yValueMax, xValueMin, xValueMax);
    }

    return motor_direction;
}

void Motor_Direction::set_x(int incomingX)
{
    incoming_x = incomingX;
}

void Motor_Direction::set_y(int incomingY)
{
    incoming_y = incomingY;
}

void Motor_Direction::forward(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed)
{
    motor_one.spin_motor(speed, 0);
    motor_two.spin_motor(speed, 0);
    motor_three.spin_motor(0, 0);
}

void Motor_Direction::backward(Track_Motor &motor_one, Track_Motor &motor_two, Track_Motor &motor_three, int speed)
{
    motor_one.spin_motor(speed, 1);
    motor_two.spin_motor(speed, 1);
    motor_three.spin_motor(0, 1);
}

void Motor_Direction::left(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed)
{
    motor_one.spin_motor(speed * 0.66, 1);
    motor_two.spin_motor(speed, 1);
    motor_three.spin_motor(speed, 1);
}

void Motor_Direction::right(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed)
{
    motor_one.spin_motor(speed, 0);
    motor_two.spin_motor(speed * 0.66, 0);
    motor_three.spin_motor(speed, 0);
}

void Motor_Direction::rotate(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three, int speed, int direction)
{
    int other_direction;
    if (direction == 0)
    {
        other_direction = 1;
    }
    else
    {
        other_direction = 0;
    }
    motor_one.spin_motor(speed, direction);
    motor_two.spin_motor(speed, direction);
    motor_three.spin_motor(speed, other_direction);
}

void Motor_Direction::not_moving(Track_Motor& motor_one, Track_Motor& motor_two, Track_Motor& motor_three)
{
    motor_one.spin_motor(0, 0);
    motor_two.spin_motor(0, 0);
    motor_three.spin_motor(0, 0);
}

int Motor_Direction::y()
{
    return incoming_y;
}

int Motor_Direction::x()
{
    return incoming_x;
}

int Motor_Direction::get_min_y() const
{
    return y_value_min;
}

int Motor_Direction::get_max_y() const
{
    return y_value_max;
}

int Motor_Direction::get_min_x() const
{
    return x_value_min;
}

int Motor_Direction::get_max_x() const
{
    return x_value_max;
}
