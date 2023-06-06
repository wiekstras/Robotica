#include <Arduino.h>
#include "track_motor.h"
#include "motor_direction.h"
#include "speed_meter.h"

/**
 * define connected pins for track motors.
 */
const unsigned int IN1A = 10;
const unsigned int IN1B = 11;
const unsigned int IN2A = 8;
const unsigned int IN2B = 9;
const unsigned int IN3A = 6;
const unsigned int IN3B = 7;

/**
 * Set the min and max values to decide the value range.
 */
Motor_Direction motor_direction(464, 494, 507, 537);

/**
 * Create the motor objects.
 */
Track_Motor track_motor_one(IN1A, IN1B);
Track_Motor track_motor_two(IN2A, IN2B);
Track_Motor track_motor_three(IN3A, IN3B);

/**
 * Used to check if incoming data is received.
 */
bool received_numbers = false;

void setup()
{
    /**
     * Set connected track motor pins as output.
     */
    pinMode(IN1A, OUTPUT);
    pinMode(IN1B, OUTPUT);
    pinMode(IN2A, OUTPUT);
    pinMode(IN2B, OUTPUT);
    pinMode(IN3A, OUTPUT);
    pinMode(IN3B, OUTPUT);
}

void loop()
{
    /**
     * TODO: need to decide when robot runs with or without controller.
     * The code below uses incoming data from the controller to determine track motor control.
     * Also the analog values are used to determine the speed of the track motors. this will be the value of the
     * potentiometer.
     */
    if (Serial.available()) {
        String incoming_data = Serial.readStringUntil('\n');
        int index = incoming_data.indexOf(',');

        if (index != -1) {
            String number1_str = incoming_data.substring(0, index);
            String number2_str = incoming_data.substring(index + 1);

            motor_direction.set_incoming_values(number1_str.toInt(), number2_str.toInt());

            received_numbers = true;

            int y = motor_direction.y();
            int x = motor_direction.x();
            int* y_range = motor_direction.min_max_y();
            int* x_range = motor_direction.min_max_x();

            // Joystick is moving forward, turn on motor 1 clockwise and motor 3 clockwise. Keep motor 2 off.
            if ((x > x_range[0] && x < x_range[1]) && (y >= y_range[1]))
            {
                Speed_Meter::set_speed(y);
                motor_direction.forward(track_motor_one, track_motor_two, track_motor_three, Speed_Meter::get_speed());
            }

            // Joystick is moving backward, turn on motor 1 counterclockwise and motor 3 counterclockwise. Keep motor 2 off.
            if ((x > x_range[0] && x < x_range[1]) && (y <= y_range[0]))
            {
                Speed_Meter::set_speed(y);
                motor_direction.backward(track_motor_one, track_motor_two, track_motor_three, Speed_Meter::get_speed());
            }

            // Joystick is moving right, turn on all motors clockwise but spin motor 1 half the speed.
            if ((x >= x_range[1]) && (y > y_range[0] && y < y_range[1]))
            {
                Speed_Meter::set_speed(x);
                motor_direction.right(track_motor_one, track_motor_two, track_motor_three, Speed_Meter::get_speed());
            }

            // Joystick is moving left, turn on all motors counter clockwise but spin motor 3 half the speed.
            if ((x < x_range[0]) && ((y > y_range[0] && y < y_range[1])))
            {
                Speed_Meter::set_speed(x);
                motor_direction.left(track_motor_one, track_motor_two, track_motor_three, Speed_Meter::get_speed());
            }

            motor_direction.set_incoming_values(0, 0);
            received_numbers = false;
        }
    }
    else
    {
        Serial.println("Please connect controller");
    }
}