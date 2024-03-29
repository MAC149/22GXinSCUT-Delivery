#include "Motor.h"

Motor::Motor(int En,int Stp,int Dir)
{
  this->Motor_DirPin=Dir;
  this->Motor_EnPin=En;
  this->Motor_StpPin=Stp;
}

void Motor::Motor_Init()
{
  pinMode(this->Motor_DirPin , OUTPUT);  digitalWrite(this->Motor_DirPin , LOW);  // initialize the Emm42_En_Pin as an output
  pinMode(this->Motor_StpPin, OUTPUT);  digitalWrite(this->Motor_StpPin, LOW);  // initialize the Emm42_Stp_Pin as an output
  pinMode(this->Motor_EnPin, OUTPUT);  digitalWrite(this->Motor_EnPin, LOW);  // initialize the Emm42_Dir_Pin as an output
}

void Motor::Motor_Reset()
{
  digitalWrite(this->Motor_StpPin, LOW);
}

void Motor::Motor_En(bool Status)
{
  digitalWrite(this->Motor_EnPin, (int)Status);
}

void Motor::Motor_round(int delayms,int round,bool dir)//dir 0顺时针
{
  u8 i = 0;
  digitalWrite(this->Motor_DirPin,(int)dir);
  for(i=0;i<=3200*round;i++)
  {
    delayMicroseconds(delayms);
    this->Motor_StpRun();
  }
}

void Motor::Motor_StpRun()
{
  digitalWrite(this->Motor_StpPin, 1);
  digitalWrite(this->Motor_StpPin, 0);
}

void Motor::Motor_SetDir(bool Dir)
{
  digitalWrite(this->Motor_DirPin,(int)Dir);
  digitalWrite(this->Motor_EnPin,1);
}

void Motor::Motor_StpRunTime(int delayms,int time)
{
  for(int i=0;i<time;i++)
  {
    digitalWrite(this->Motor_StpPin, 1);
    digitalWrite(this->Motor_StpPin, 0);
    delayMicroseconds(delayms);
  }
}

void Motor::Motor_RunAllSet(bool dir,int delayms,int time)
{
  this->Motor_SetDir(dir);
  for(int i=0;i<time;i++)
  {
    digitalWrite(this->Motor_StpPin, 1);
    digitalWrite(this->Motor_StpPin, 0);
    delayMicroseconds(delayms);
  }
}