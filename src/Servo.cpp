#include "Servocon.h"

Servocon::Servocon(HardwareSerial *Serial)
{
    this->Servo_Serial=Serial;
    this->ACTION_FLAG=false;
    this->FRAME_HEAD=0;
}

void Servocon::waitoend()
{
    while (!this->ACTION_FLAG)
    {
        
        if (this->Servo_Serial->available() > 0)
        {
            if (0x55 == this->Servo_Serial->read())
            {
                this->FRAME_HEAD++;
                if (this->FRAME_HEAD == 4)
                {
                    this->FRAME_HEAD = 0;
                    this->ACTION_FLAG = true;
                }
            }
        }
    }
}
void Servocon::Runactiongroup(int group,int time)
{
    this->ACTION_FLAG=false;
    this->Servo_Serial->write(0x55);
    this->Servo_Serial->write(0x55);
    this->Servo_Serial->write(0x05);
    this->Servo_Serial->write(0x06);
    this->Servo_Serial->write(group);
    this->Servo_Serial->write(time);
    this->Servo_Serial->write(time>>8);
    this->waitoend();
}