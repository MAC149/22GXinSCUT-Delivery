#pragma once
#include<Arduino.h>
#include"Motor.h"
//dir0逆时针
class Motortot
{
public:
    Motortot(int ST,int ADCPin,int Astp,int Adir,int Bstp,int Bdir,int Cstp,int Cdir,int Dstp,int Ddir);
    int Motortot_ST;
    Motor* MotorFL;
    Motor* MotorFR;
    Motor* MotorBL;
    Motor* MotorBR;
    int Motortot_ADC;
    void Motortot_Init();
    void Motortot_Forward(int delayms,int round);
    void Motortot_Backward(int delayms,int round);
    void Motortot_Left(int delayms,int round);
    void Motortot_Right(int delayms,int round);
    void Motortot_RotLeft(int delayms);
    void Motortot_RotRight(int delayms);
    void Motortot_ForLeft(int delayms,int round);
    void Motortot_ForRight(int delayms,int round);
    void Motortot_En(bool stats);
    void Motortot_Reset();
    void Motortot_SetDir(bool FL,bool FR,bool BL,bool BR);
};