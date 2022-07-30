#include"step.h"
#include<MsTimer2.h>
const int INTERVAL = 100;
Motortot Mtot1(2,A0,4,8,5,9,6,10,7,11);
bool Break_Flag = 0;
bool LinePassBreak=0;
u8 LineStats=0;
int HT[8]={31,33,35,37,39,41,43,45};
String QRCode="";
int line=0,check=0;
enum Dirc{F=1,B,L,R,LR};

void MotorTestDemo()
{
    Mtot1.Motortot_ForwardR(200,2);
    delay(2000);
    Mtot1.Motortot_BackwardR(200,2);
    delay(2000);
    Mtot1.Motortot_LeftR(200,2);
    delay(2000);
    Mtot1.Motortot_RightR(200,2);
    delay(2000);
    Mtot1.Motortot_RotLeft(200);
    Mtot1.Motortot_Reset();
    delay(2000);
    Mtot1.Motortot_RotRight(200);
    Mtot1.Motortot_Reset();
    delay(2000);
}


int CheckRes(Dirc checkdir)
{
    switch(checkdir)
    {
        case L:return (digitalRead(HT[2]||digitalRead(HT[3])));break;
        case R:return (digitalRead(HT[4]||digitalRead(HT[5])));break;
        case F:return (digitalRead(HT[0]||digitalRead(HT[1])));break;
        case B:return (digitalRead(HT[6]||digitalRead(HT[7])));break;
        case LR:return (digitalRead(HT[2]||digitalRead(HT[3])||digitalRead(HT[4]||digitalRead(HT[5]))));break;
    }
}

void TimerCheck(Dirc checkdir)
{
    switch (LineStats)
    {
    case 0:if(CheckRes(checkdir)){LineStats=1;}break;
    case 1:if(!CheckRes(checkdir)){LineStats=2;}break;
    }
}


void Stright_Adjust()
{

}

void Line_Plus(Dirc checkdir,int delayms)
{
    LinePassBreak=0;
    do
    {
         if(!(check%=20))
        {
            if (!CheckRes(checkdir))
            {
                    LinePassBreak=1;
            }
        }
        Mtot1.Motortot_Steprun(delayms);
    } while(!LinePassBreak);
    LinePassBreak=0;
    line++;
}


void Goline(u8 Lineobj,Dirc godir,Dirc checkdir,int delayms)
{
    Break_Flag=0;
    line=0;
    switch (godir)
    {
    case F:Mtot1.Motortot_SetDirForward();break;
    case B:Mtot1.Motortot_SetDirBackward();break;
    case L:Mtot1.Motortot_SetDirLeft();break;
    case R:Mtot1.Motortot_SetDirRight();break;
    }
    do
    {
        if(!(check%=20))
        {
            if (CheckRes(checkdir))
            {
                Line_Plus(checkdir,delayms);
                if(line==Lineobj)
                {
                    Break_Flag=1;
                }
            }
        }
        Mtot1.Motortot_Steprun(delayms);
        check++;
    } while (!Break_Flag);
    Break_Flag=0;
    line=0;
}

void runtest()
{   
    Mtot1.Motortot_ForwardR(100,1);
    Mtot1.Motortot_LeftR(100,1);    
    Goline(1,L,L,100);
    Goline(2,F,F,100);
    /*do
    {
        QRCode=QR_Getstring(&Serial);
    }while(QRCode=="");*/
    delay(2000);//起点-扫码
    Goline(2,F,LR,100);
    Goline(1,R,R,100);
    delay(2000);//扫码-原料区
    Mtot1.Motortot_RotLeft(100);
    Goline(2,F,R,100);
    delay(2000);//原料-粗加工区
    Goline(2,F,F,100);
    Mtot1.Motortot_RotLeft(100);
    Goline(2,F,F,100);
    delay(2000);//粗加工-精加工
    Mtot1.Motortot_RotLeft(100);
    Mtot1.Motortot_RotLeft(100);
    Goline(5,R,L,100);
    Goline(2,F,R,100);
    delay(2000);//精加工-原料二轮
    Mtot1.Motortot_RotLeft(100);
    Goline(2,F,R,100);
    delay(2000);//原料-粗加工
    Goline(2,F,F,100);
    Mtot1.Motortot_RotLeft(100);
    Goline(2,F,F,100);
    delay(2000);//粗加工-精加工
    Mtot1.Motortot_ForwardR(100,2);

}

void stp1()
{
    
}