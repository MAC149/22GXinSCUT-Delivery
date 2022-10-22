#include"step.h"

extern Motortot Mtot1;
extern Motor MotRot,MotLift;
extern int LeftHT[5],RightHT[5];
SoftwareSerial qrcode(10,11);
void setup()
{
    Serial.begin(9600);
    Serial_Init(&qrcode);
    Mtot1.Motortot_Init();
    MotRot.Motor_Init();
    MotLift.Motor_Init();
    for(int i=0;i<5;i++)
    {
        pinMode(LeftHT[i],INPUT);
        pinMode(RightHT[i],INPUT);
    }
}

void loop()
{
    delay(2000);
    //runtest();
    MotorTestDemo();
    while(1);
    
}