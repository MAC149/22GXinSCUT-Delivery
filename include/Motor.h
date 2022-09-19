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
class Motor
{
public:
  int Motor_EnPin;
  int Motor_StpPin;
  int Motor_DirPin;
  void Motor_Init();
  Motor(int En,int Sto,int Dir);
  void Motor_round(int delayms,int round,bool Dir);
  void Motor::Motor_Reset();
  void Motor::Motor_StpRun();
  void Motor::Motor_SetDir(bool Dir);
};