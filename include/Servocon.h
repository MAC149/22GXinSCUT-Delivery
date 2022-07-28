#pragma once
#include <HardwareSerial.h>
class Servocon
{
public:
    HardwareSerial *Servo_Serial;
    void Runactiongroup(int group,int time);
    Servocon(HardwareSerial *Serial);
    bool ACTION_FLAG;
    int FRAME_HEAD;
    void waitoend();
};