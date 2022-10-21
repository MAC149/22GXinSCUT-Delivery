#include"step.h"

extern Motortot Mtot1;
extern int HT[2];

void setup()
{
    Serial.begin(9600);
    HT_Uart_Init();
    Mtot1.Motortot_Init();
    for(int i=0;i<2;i++)
    {
        pinMode(HT[2],INPUT);
    }
}

void loop()
{
    delay(2000);
    runtest();
    //MotorTestDemo();
    while(1);
    
}