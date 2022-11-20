#pragma once
#include<Arduino.h>
#include"Motor.h"
//dir0逆时针
class Motortot
{
public:
    Motortot(int AEn,int Astp,int Adir,int Bstp,int BEn,int Bdir,int CEn,int Cstp,int Cdir,int DEn,int Dstp,int Ddir);
    //int Motortot_ST;
    Motor* MotorFL;
    Motor* MotorFR;
    Motor* MotorBL;
    Motor* MotorBR;
    //int Motortot_ADC;
    void Motortot_Init();
    void Motortot_ForwardTime(int delayms,int time);
    void Motortot_BackwardTime(int delayms,int time);
    void Motortot_LeftTime(int delayms,int time);
    void Motortot_RightTime(int delayms,int time);
    void Motortot_RotLeft(int delayms);
    void Motortot_RotRight(int delayms);
    void Motortot_ForLeftTime(int delayms,int time);
    void Motortot_ForRightTime(int delayms,int time);
    void Motortot_En(bool status);
    void Motortot_Reset();
    void Motortot_SetDir(bool FL,bool FR,bool BL,bool BR);
    void Motortot_SetDirForward();
    void Motortot_SetDirBackward();
    void Motortot_SetDirLeft();
    void Motortot_SetDirRight();
    void Motortot_SetDirForLeft();
    void Motortot_SetDirForRight();
    void Motortot_Steprun(int delayms);
    void Motortot_SteprunRAW(int delayms,int time);
    void Motortot_ForLeftSteprun(int delayms);
    void Motortot_ForRightSteprun(int delayms);
    void Motortot_SetDirRotLeft();
    void Motortot_SetDirRotRight();
    void PIDcontrolDemo(int target);
};