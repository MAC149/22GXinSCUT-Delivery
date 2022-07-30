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
    void Motortot_ForwardR(int delayms,int round);
    void Motortot_BackwardR(int delayms,int round);
    void Motortot_LeftR(int delayms,int round);
    void Motortot_RightR(int delayms,int round);
    void Motortot_RotLeft(int delayms);
    void Motortot_RotRight(int delayms);
    void Motortot_ForLeftR(int delayms,int round);
    void Motortot_ForRightR(int delayms,int round);
    void Motortot_En(bool stats);
    void Motortot_Reset();
    void Motortot_SetDir(bool FL,bool FR,bool BL,bool BR);
    void Motortot_SetDirForward();
    void Motortot_SetDirBackward();
    void Motortot_SetDirLeft();
    void Motortot_SetDirRight();
    void Motortot_SetDirForLeft();
    void Motortot_SetDirForRight();
    void Motortot_Steprun(int delayms);
};