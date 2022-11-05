#pragma once
#include<Arduino.h>
#include"Motor.h"
//dir0逆时针
class Motortot
{
public:
    Motortot(int AEn,int Astp,int Adir,int Bstp,int BEn,int Bdir,int CEn,int Cstp,int Cdir,int DEn,int Dstp,int Ddir);
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
    void Motortot_ForwardRPair(int delayms,int round);
    void Motortot_BackwardRPair(int delayms,int round);
    void Motortot_LeftRPair(int delayms,int round);
    void Motortot_RightRPair(int delayms,int round);
    void Motortot_RotLeftPair(int delayms);
    void Motortot_RotRightPair(int delayms);
    void Motortot_ForLeftRPair(int delayms,int round);
    void Motortot_ForRightRPair(int delayms,int round);
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
    void Motortot_SteprunPair(int delayms);
    void Motortot_SteprunPairRAW(int delayms,int time);
    void Motortot_ForLeftSteprunPair(int delayms);
    void Motortot_ForRightSteprunPair(int delayms);
    void Motortot_SetDirRotLeft();
    void Motortot_SetDirRotRight();
    void PIDcontrolDemo(int target,int loc);
};