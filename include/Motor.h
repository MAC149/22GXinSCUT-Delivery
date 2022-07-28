#pragma once
#include <Arduino.h>

class Motor
{
public:
  int Motor_StpPin;
  int Motor_FRPin;
  void Motor_Init();
  Motor(int Stp,int Dir);
  void Motor_round(int delayms,bool Dir,int round);
  void Motor_StpRun();
  void Motor_Reset();
  void Motor_SetDir(bool Dir);
};
