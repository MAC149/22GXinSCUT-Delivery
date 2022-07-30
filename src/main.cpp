#include"step.h"

extern Motortot Mtot1;
extern int HT[8];

void setup()
{
    Serial.begin(9600);
    Mtot1.Motortot_Init();
    for(int i=0;i<8;i++)
    {
        pinMode(HT[i],INPUT);
    }
}

void loop()
{
    delay(2000);
    runtest();
    while(1);
    
}