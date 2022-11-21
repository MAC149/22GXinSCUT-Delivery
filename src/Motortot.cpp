#include"Motortot.h"

void Motortot::Motortot_Init()
{
    this->MotorFL->Motor_Init();
    this->MotorFR->Motor_Init();
    this->MotorBL->Motor_Init();
    this->MotorBR->Motor_Init();
}

Motortot::Motortot(int AEn,int Astp,int Adir,int BEn,int Bstp,int Bdir,int CEn,int Cstp,int Cdir,int DEn,int Dstp,int Ddir)
{
    this->MotorFL = new Motor(AEn,Astp, Adir);
    this->MotorFR = new Motor(BEn,Bstp, Bdir);
    this->MotorBL = new Motor(CEn,Cstp, Cdir);
    this->MotorBR = new Motor(DEn,Dstp, Ddir);
}

void Motortot::Motortot_Reset()
{
    MotorFL->Motor_Reset();
    MotorBL->Motor_Reset();
    MotorFR->Motor_Reset();
    MotorBR->Motor_Reset();
}

 void Motortot::Motortot_En(bool status)
 {
    digitalWrite(this->MotorFR->Motor_EnPin,(int)status);
    digitalWrite(this->MotorFL->Motor_EnPin,(int)status);
    digitalWrite(this->MotorBR->Motor_EnPin,(int)status);
    digitalWrite(this->MotorBL->Motor_EnPin,(int)status);
 }

void Motortot::Motortot_SetDir(bool FL,bool FR,bool BL,bool BR)
{
    this->MotorFL->Motor_SetDir(FL);
    this->MotorFR->Motor_SetDir(FR);
    this->MotorBL->Motor_SetDir(BL);
    this->MotorBR->Motor_SetDir(BR);
}  

void Motortot::Motortot_ForwardTime(int delayms,int time)
{
    this->Motortot_SetDir(0,1,0,1);
    this->Motortot_En(1);
    for(int i=0;i<time;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_BackwardTime(int delayms,int time)
{
    this->Motortot_SetDir(1,0,1,0);
    this->Motortot_En(1);
    for(int i=0;i<time;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_LeftTime(int delayms,int time)
{
    this->Motortot_SetDir(1,1,0,0);
    this->Motortot_En(1);
    for(int i=0;i<time;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_RightTime(int delayms,int time)
{
    this->Motortot_SetDir(0,0,1,1);
    this->Motortot_En(1);
    for(int i=0;i<time;i++)
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
    for(int i=0;i<=4000;i++)
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
    for(int i=0;i<=4000;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_RotLeftTime(int delayms,int time)
{
    this->Motortot_SetDir(1,1,1,1);
    this->Motortot_En(1);
    for(int i=0;i<=time;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_RotRightTime(int delayms,int time)
{
    this->Motortot_SetDir(0,0,0,0);
    this->Motortot_En(1);
    for(int i=0;i<=time;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}


void Motortot::Motortot_ForLeftTime(int delayms,int time)
    {
        this->Motortot_SetDir(0,1,0,1);
        this->Motortot_En(1);
        for(int i=0;i<time;i++)
        {
            MotorFL->Motor_StpRun();
            //MotorFR->Motor_StpRun();
            //MotorBL->Motor_StpRun();
            MotorBR->Motor_StpRun();
            delayMicroseconds(delayms);
        }
    }
    
void Motortot::Motortot_ForRightTime(int delayms,int time)
    {
        this->Motortot_SetDir(0,1,0,1);
        this->Motortot_En(1);
        for(int i=0;i<time;i++)
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

void Motortot::Motortot_SetDirRotLeft()
{
    this->Motortot_SetDir(1,1,1,1);
    this->Motortot_En(1);
}

void Motortot::Motortot_SetDirRotRight()
{
    this->Motortot_SetDir(0,0,0,0);
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

void Motortot::Motortot_SteprunRAW(int delayms,int time)
{
    for(int i=0;i<time;i++)
    {
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(delayms);
    }
}

void Motortot::Motortot_ForLeftSteprun(int delayms)
{
    MotorFL->Motor_StpRun();
    MotorBR->Motor_StpRun();
    delayMicroseconds(delayms);
}

void  Motortot::Motortot_ForRightSteprun(int delayms)
{
    MotorFR->Motor_StpRun();
    MotorBL->Motor_StpRun();
    delayMicroseconds(delayms);
}

void Motortot::PIDcontrolDemo(int target)//位置量->速度量
{
    int i=0,sum=0,res=0,reslast=0;
    int base=1000;
    float Kp,Ki,Kd;
    Kp=1;
    Ki=1;
    Kd=1;
    this->Motortot_SetDir(0,1,0,1);
    this->Motortot_En(1);
    for(i=0;i<3200*target;i++)
    {
        sum+=3200*target-i;
        reslast=res;
        res=(3200*target-i)*Kp;
        res+=Kd*(base/reslast);
        res+=Ki*(sum);
        
        
        MotorFL->Motor_StpRun();
        MotorFR->Motor_StpRun();
        MotorBL->Motor_StpRun();
        MotorBR->Motor_StpRun();
        delayMicroseconds(base/res);
    }
}
