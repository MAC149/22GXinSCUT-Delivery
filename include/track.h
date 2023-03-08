#pragma once
#include"Uart.h"
#include"Motortot.h"
//#include"MPU6050.h"
void mpuadjust(double angle);
void Follow();
void FindMid_Left(int delayms);
void FindMid_Right(int delayms);
void Find_RightEdge(int delayms);
void Find_LeftEdge(int delayms);
void Find_Mid();
void FRGoline(u8 Lineobj,int delayms);
void BRGoline(u8 Lineobj,int delayms);
