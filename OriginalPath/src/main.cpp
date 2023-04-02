#include"step.h"
extern Motortot Mtot1;
extern Motor MotRot,MotLift;
extern int LeftHT[5],RightHT[5];
extern Servo Servo_Pad,Servo_Paw;
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;
SoftwareSerial qrcode(11,10);
void setup()
{
    Serial.begin(9600);
    Serial_Init(&qrcode);
    Serial1.begin(9600);    //openmv
    Serial2.begin(9600);    //front HT
    Serial3.begin(9600);    //back HT
    Mtot1.Motortot_Init();
    MotRot.Motor_Init();
    MotLift.Motor_Init();
    MotRot.Motor_En(1);
    MotLift.Motor_En(1);
    for(int i=0;i<5;i++)
    {
        pinMode(LeftHT[i],INPUT);
        pinMode(RightHT[i],INPUT);
    }
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
    Servo_Pad.attach(A0);
    Servo_Paw.attach(A3);
    //mpu_Init();
}

void loop()
{
    delay(50);
    step1();
    //mpuadjust(180);
    //runtest();
    //MotorTestDemo();
    //Place_P1_Red();
    while(1);
    
}