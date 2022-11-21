#pragma once
#include <Arduino.h>

class Motor
{
public:
  int Motor_EnPin;
  int Motor_StpPin;
  int Motor_DirPin;
  void Motor_Init();
  Motor(int En,int Sto,int Dir);
  void Motor_round(int delayms,int round,bool Dir);
  void Motor_Reset();
  void Motor_StpRun();
  void Motor_SetDir(bool Dir);
  void Motor_En(bool Status);
  void Motor_StpRunTime(int delayms,int time);
  void Motor_RunAllSet(bool dir,int delayms,int time);
};