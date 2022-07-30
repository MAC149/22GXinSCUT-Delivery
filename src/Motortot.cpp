#include"Motortot.h"

void Motortot::Motortot_Init()
{
    this->MotorFL->Motor_Init();
    this->MotorFR->Motor_Init();
    this->MotorBL->Motor_Init();
    this->MotorBR->Motor_Init();
    pinMode(this->Motortot_ADC, INPUT);
    pinMode(this->Motortot_ST, OUTPUT);
}

Motortot::Motortot(int ST,int ADCPin,int Astp,int Adir,int Bstp,int Bdir,int Cstp,int Cdir,int Dstp,int Ddir)
{
    this->Motortot_ST=ST;
    this->Motortot_ADC=ADCPin;
    this->MotorFL = new Motor(Astp, Adir);
    this->MotorFR = new Motor(Bstp, Bdir);
    this->MotorBL = new Motor(Cstp, Cdir);
    this->MotorBR = new Motor(Dstp, Ddir);
}

void Motortot::Motortot_Reset()
{
    MotorFL->Motor_Reset();
    MotorBL->Motor_Reset();
    MotorFR->Motor_Reset();
    MotorBR->Motor_Reset();
}

 void Motortot::Motortot_En(bool stats)
 {
    digitalWrite(this->Motortot_ST,(int)stats);
 }

void Motortot::Motortot_SetDir(bool FL,bool FR,bool BL,bool BR)
{
    this->MotorFL->Motor_SetDir(FL);
    this->MotorFR->Motor_SetDir(FR);
    this->MotorBL->Motor_SetDir(BL);
    this->MotorBR->Motor_SetDir(BR);
}  

void Motortot::Motortot_ForwardR(int delayms,int round)
{
    this->Motortot_SetDir(0,1,0,1);
    this->Motortot_En(1);
    for(int i=0;i<6400*round;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_BackwardR(int delayms,int round)
{
    this->Motortot_SetDir(1,0,1,0);
    this->Motortot_En(1);
    for(int i=0;i<6400*round;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_LeftR(int delayms,int round)
{
    this->Motortot_SetDir(1,1,0,0);
    this->Motortot_En(1);
    for(int i=0;i<6400*round;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_RightR(int delayms,int round)
{
    this->Motortot_SetDir(0,0,1,1);
    this->Motortot_En(1);
    for(int i=0;i<6400*round;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_RotLeft(int delayms)
{
    this->Motortot_SetDir(1,1,1,1);
    this->Motortot_En(1);
    for(int i=0;i<=8000;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_RotRight(int delayms)
{
    this->Motortot_SetDir(0,0,0,0);
    this->Motortot_En(1);
    for(int i=0;i<=8000;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

    void Motortot::Motortot_ForLeftR(int delayms,int round)
    {
        this->Motortot_SetDir(0,1,0,1);
        this->Motortot_En(1);
        for(int i=0;i<6400*round;i++)
        {
            MotorFL->Motor_StpRun();
            //MotorFR->Motor_StpRun();
            //MotorBL->Motor_StpRun();
            MotorBR->Motor_StpRun();
            delayMicroseconds(delayms);
        }
    }
    
    void Motortot::Motortot_ForRightR(int delayms,int round)
    {
        this->Motortot_SetDir(0,1,0,1);
        this->Motortot_En(1);
        for(int i=0;i<6400*round;i++)
        {
            //MotorFL->Motor_StpRun();
            MotorFR->Motor_StpRun();
            MotorBL->Motor_StpRun();
            //MotorBR->Motor_StpRun();
            delayMicroseconds(delayms);
        }
    }
        
    void Motortot::Motortot_SetDirForward()
    {
        this->Motortot_SetDir(0,1,0,1);
        this->Motortot_En(1);
    }
    
    void Motortot::Motortot_SetDirBackward()
    {
        this->Motortot_SetDir(1,0,1,0);
        this->Motortot_En(1);
    }
    
    void Motortot::Motortot_SetDirLeft()
    {
        this->Motortot_SetDir(1,1,0,0);
        this->Motortot_En(1);
    }
    
    void Motortot::Motortot_SetDirRight()
    {
        this->Motortot_SetDir(0,0,1,1);
        this->Motortot_En(1);
    }
    
    void Motortot::Motortot_SetDirForLeft()
    {
        this->Motortot_SetDir(0,1,0,1);
        this->Motortot_En(1);
    }
    
    void Motortot::Motortot_SetDirForRight()
    {
         this->Motortot_SetDir(0,1,0,1);
         this->Motortot_En(1);
    }
    
    void Motortot::Motortot_Steprun(int delayms)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }