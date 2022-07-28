#include"Motortot.h"
#include"Servo.h"
#include"QRScanner.h"

Motortot Mtot1(2,A0,4,8,5,9,6,10,7,11);
void setup()
{
    Serial.begin(9600);
    Mtot1.Motortot_Init();
}

void loop()
{
    
    Mtot1.Motortot_Forward(200,2);
    delay(2000);
    Mtot1.Motortot_Backward(200,2);
    delay(2000);
    Mtot1.Motortot_Left(200,2);
    delay(2000);
    Mtot1.Motortot_Right(200,2);
    delay(2000);
    Mtot1.Motortot_RotLeft(200);
    Mtot1.Motortot_Reset();
    delay(2000);
    Mtot1.Motortot_RotRight(200);
    Mtot1.Motortot_Reset();
    delay(2000);
}