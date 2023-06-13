#include <Arduino.h>
#include "track_motor.h"
#include "motor_direction.h"
#include "speed_meter.h"
#include <SoftwareSerial.h>

const int rxPin = 5;
const int txPin = 4;
int joymove = 0;
SoftwareSerial xBee = SoftwareSerial(rxPin, txPin);

// Set the min and max values to decide the value range.
Motor_Direction* motor_direction = Motor_Direction::get_instance(6, 8, 6, 8);

int grip;
int height;
int speedpot;

int buttonarray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Create the motor objects.
Track_Motor track_motor_one(A1, A2);
Track_Motor track_motor_two(6, A3);
Track_Motor track_motor_three(7, 8);

// get one and only instance of Speed_meter object.
Speed_Meter* speed_meter = Speed_Meter::get_instance();

// Used to check if incoming data is received.
bool received_numbers = false;

/**
 * Arduino setup.
 */
void setup()
{
    xBee.begin(38400);
    Serial.begin(38400);
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    // Set connected track motor pins as output.
    pinMode(track_motor_one.get_pin_a(), OUTPUT);
    pinMode(track_motor_one.get_pin_b(), OUTPUT);
    pinMode(track_motor_two.get_pin_a(), OUTPUT);
    pinMode(track_motor_two.get_pin_b(), OUTPUT);
    pinMode(track_motor_three.get_pin_a(), OUTPUT);
    pinMode(track_motor_three.get_pin_b(), OUTPUT);
}

/**
 * Continuous check for incoming controller values to control track motors.
 */
void loop()
{
    joymove = 0;
    while (xBee.available())
    {
        int incomingInt;
        incomingInt = xBee.read();
        Serial.print("Something is coming! Value: ");
        Serial.println(incomingInt);
        switch (incomingInt)
        {
            case 16 ... 31: //0001 XXXX, JOYSTICK X VALUE
                motor_direction->set_y(incomingInt - 16);
                joymove = 1;
                Serial.print("X: ");
                Serial.println(motor_direction->x());
                break;

            case 32 ... 47://0010 XXXX, JOYSTICK Y VALUE
                motor_direction->set_x(incomingInt - 32);
                joymove = 1;
                Serial.print("Y: ");
                Serial.println(motor_direction->y());
                break;

            case 48 ... 63:// 0011 XXXX, GRIPPER OPEN VALUE
                grip = incomingInt - 48;
                Serial.print("Grip:");
                Serial.println(grip);
                break;

            case 64 ... 79://0100 XXXX, GRIPPER HEIGHT VALUE
                height = incomingInt - 64;
                Serial.print("Height:");
                Serial.println(height);
                break;

            case 80 ... 95://0101 XXXX, SPEEDPOT VALUE
                speedpot = incomingInt - 80;
                Serial.print("Speed:");
                Serial.println(speedpot);
                break;

            case 96 ... 111: //0110 1/2/3/4, BUTTONS 1-4 VALUES
                for (int i = 0; i < 4; i++)
                {
                    buttonarray[i] = (incomingInt - 96) >> i % 4 &
                                     1; //afbouwen van de waardes die we versturen. Bits shiften x4 om de waardes weer er uit te halen.
                    Serial.print("Button:");
                    Serial.print(i);
                    Serial.print("  Value:");
                    Serial.println(buttonarray[i]);
                }
                break;

            case 112 ... 127: //0111 5/6/7/8, BUTTONS 5-8 VALUES
                for (int i = 4; i < 8; i++)
                {
                    buttonarray[i] = (incomingInt - 112) >> i % 4 &
                                     1; //afbouwen van de waardes die we versturen. Bits shiften x4 om de waardes weer er uit te halen.
                    Serial.print("Button:");
                    Serial.print(i);
                    Serial.print("  Value:");
                    Serial.println(buttonarray[i]);
                }
                break;

            case 128 ... 143: // 1000 9/10/11/12, BUTTONS 9-12 VALUES
                for (int i = 8; i < 12; i++)
                {
                    buttonarray[i] = (incomingInt - 128) >> i % 4 &
                                     1; //afbouwen van de waardes die we versturen. Bits shiften x4 om de waardes weer er uit te halen.
                    Serial.print("Button:");
                    Serial.print(i);
                    Serial.print("  Value:");
                    Serial.println(buttonarray[i]);
                }
                break;

            case 144 ... 159: //1001 13/13/13/13, BUTTON 13 VALUE (X4)
                for (int i = 12; i < 16; i++)
                {
                    buttonarray[i] = (incomingInt - 144) >> i % 4 &
                                     1; //afbouwen van de waardes die we versturen. Bits shiften x4 om de waardes weer er uit te halen.
                    Serial.print("Button:");
                    Serial.print(i);
                    Serial.print("  Value:");
                    Serial.println(buttonarray[i]);
                }
                break;
            default: //do nothing
                break;
        }
    }

    int x = motor_direction->x();
    int y = motor_direction->y();
    int min_x = motor_direction->get_min_x();
    int max_x = motor_direction->get_max_x();
    int min_y = motor_direction->get_min_y();
    int max_y = motor_direction->get_max_y();

    speed_meter->set_speed(speedpot);

    // Joystick is moving forward, turn on motor 1 clockwise and motor 3 clockwise. Keep motor 2 off.
    if ((x > min_x && x < max_x) && (y >= max_y))
    {
        //motor_direction->move(track_motor_one, track_motor_two, track_motor_three, 255, 0);
        // Move robot forward.
        motor_direction->forward(track_motor_one, track_motor_two, track_motor_three, 255);
    }

    // Joystick is moving backward, turn on motor 1 counterclockwise and motor 3 counterclockwise. Keep motor 2 off.
    if ((x > min_x && x < max_x) && (y <= min_y))
    {
        //motor_direction->move(track_motor_one, track_motor_two, track_motor_three, 255, 1);
        motor_direction->backward(track_motor_one, track_motor_two, track_motor_three, 255);
    }

    // Joystick is moving right, turn on all motors clockwise but spin motor 1 0.66 times the speed.
    if ((x >= max_x) && (y > min_y && y < max_y))
    {
        //motor_direction->move(track_motor_one, track_motor_two, track_motor_three, 255, 2);
        motor_direction->right(track_motor_one, track_motor_two, track_motor_three, 255);
    }

    // Joystick is moving left, turn on all motors counterclockwise but spin motor 3 0.66 times the speed.
    if ((x < min_x) && ((y > min_y && y < max_y)))
    {
        //motor_direction->move(track_motor_one, track_motor_two, track_motor_three, 255, 3);
        motor_direction->left(track_motor_one, track_motor_two, track_motor_three, 255);
    }

    // Joystick is not moving, turn all motors off.
    if ((y >= min_y && y <= max_y) && (x >= min_x && x <= max_x))
    {
        // Serial.println("Joystick is not moving.");
        motor_direction->not_moving(track_motor_one, track_motor_two, track_motor_three);
    }

    // Rotate robot clockwise.
    if (buttonarray[0] == 1)
    {
        //motor_direction->move(track_motor_one, track_motor_two, track_motor_three, 255, 4);
        motor_direction->rotate(track_motor_one, track_motor_two, track_motor_three, 255, 0);
    }

    if (buttonarray[1] == 1)
    {
        motor_direction->not_moving(track_motor_one, track_motor_two, track_motor_three);
    }

    // Rotate robot counterclockwise.
    if (buttonarray[10] == 1)
    {
        //motor_direction->move(track_motor_one, track_motor_two, track_motor_three, 255, 5);
        motor_direction->rotate(track_motor_one, track_motor_two, track_motor_three, 255, 1);
    }
}