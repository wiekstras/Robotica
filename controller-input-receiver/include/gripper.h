//
// Created by Giel on 14-6-2023.
//

#ifndef ROBOTCODE_GRIPPER_H
#define ROBOTCODE_GRIPPER_H
class Gripper{
public:
    void move_up(int limiterarray);
    void move_down();
    void close();
    void open();
};

#endif //ROBOTCODE_GRIPPER_H
