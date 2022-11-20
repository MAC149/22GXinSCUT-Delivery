#pragma once
#include"Uart.h"
#include"Motortot.h"
void Follow();
void FindMid_Left(int delayms);
void FindMid_Right(int delayms);
void Find_RightEdge(int delayms);
void Find_LeftEdge(int delayms);
bool NOnLineCheck();
void NLine_Plus(int delayms);
void NGoline(u8 Lineobj,int delayms);
