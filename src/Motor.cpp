#include "Motor.h"

Motor::Motor(int Stp,int Dir)
{
  this->Motor_FRPin=Dir;
  this->Motor_StpPin=Stp;
}

void Motor::Motor_Init()
{
  pinMode(this->Motor_FRPin , OUTPUT);  digitalWrite(this->Motor_FRPin , LOW);  // initialize the Emm42_En_Pin as an output
  pinMode(this->Motor_StpPin, OUTPUT);  digitalWrite(this->Motor_StpPin, LOW);  // initialize the Emm42_Stp_Pin as an output
}

void Motor::Motor_Reset()
{
  digitalWrite(this->Motor_StpPin, LOW);
}

void Motor::Motor_round(int delayms,bool dir,int round)//dir 0顺时针
{
   int i = 0;
   digitalWrite(this->Motor_FRPin,dir);
  for(i=0;i<=6400*round;i++)
  {
    delayMicroseconds(delayms);
    digitalWrite(this->Motor_StpPin, !digitalRead(this->Motor_StpPin));
  }
}

void Motor::Motor_StpRun()
{
  digitalWrite(this->Motor_StpPin, !digitalRead(this->Motor_StpPin));
}

void Motor::Motor_SetDir(bool Dir)
{
  digitalWrite(this->Motor_FRPin,(int)Dir);
}