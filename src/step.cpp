#include"step.h"
#include<MsTimer2.h>
Motortot Mtot1(4,3,2,10,9,8,13,12,11,7,6,5);//AEn,Astp,Adir,Bstp,BEn,Bdir,CEn,Cstp,Cdir,DEn,Dstp,Ddir
bool Break_Flag = 0;
bool LinePassBreak=0;
bool AdjustBreak=0;
int HT[8]={31,33,35,37,39,41,43,45};
String QRCode="";
int line=0,check=0;
enum Dirc{F=1,B,L,R};

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

int CheckResSim(Dirc checkdir)
{
    switch(checkdir)
    {
        case L:return (digitalRead(HT[2]));break;
        case R:return (digitalRead(HT[4]));break;
        case F:return (digitalRead(HT[0]));break;
        case B:return (digitalRead(HT[6]));break;
    }
}

int CheckResSim2(Dirc checkdir)
{
    switch(checkdir)
    {
        case L:return (digitalRead(HT[3]));break;
        case R:return (digitalRead(HT[5]));break;
        case F:return (digitalRead(HT[1]));break;
        case B:return (digitalRead(HT[7]));break;
    }
}

void Stright_Fix(Dirc godir,Dirc checkdir,int delayms)
{
    check=0;
    switch(godir)
    {
        case B:break;
        case R:
         do
            {
                if(!(check%=150))
                {
                    if ((CheckResSim2(godir)&&CheckResSim(godir)))
                    {
                        AdjustBreak=1;
                    }
                    else if(CheckResSim2(godir)&&(!CheckResSim(godir)))
                    {
                    Mtot1.Motortot_SetDirRotLeft();
                    }
                    else if(CheckResSim(godir)&&(!CheckResSim2(godir)))
                    {
                        Mtot1.Motortot_SetDirRotRight();
                    }
                }
            Mtot1.Motortot_Steprun(delayms);
            check++;
        } while(!AdjustBreak);break;
        case L:
        case F:
             do
            {
                if(!(check%=150))
                {
                    if ((CheckResSim2(godir)&&CheckResSim(godir)))
                    {
                        AdjustBreak=1;
                    }
                    else if(CheckResSim2(godir)&&(!CheckResSim(godir)))
                    {
                    Mtot1.Motortot_SetDirRotLeft();
                    }
                    else if(CheckResSim(godir)&&(!CheckResSim2(godir)))
                    {
                        Mtot1.Motortot_SetDirRotRight();
                    }
                }
            Mtot1.Motortot_Steprun(delayms);
            check++;
        } while(!AdjustBreak);break;
    }
    switch (godir)
    {
    case F:Mtot1.Motortot_SetDirForward();break;
    case B:Mtot1.Motortot_SetDirBackward();break;
    case L:Mtot1.Motortot_SetDirLeft();break;
    case R:Mtot1.Motortot_SetDirRight();break;
    }
    AdjustBreak=0;
    check=0;
}


void Line_Plus(Dirc godir,Dirc checkdir,int delayms)
{
    LinePassBreak=0;
    do
    {
         if(!(check%=100))
        {
            if (!(CheckResSim(checkdir)))
            {
                LinePassBreak=1;
            }
        }
        Mtot1.Motortot_Steprun(delayms);
        check++;
    } while(!LinePassBreak);
    LinePassBreak=0;
    line++;
}


void Goline(u8 Lineobj,Dirc godir,Dirc checkdir,int delayms)
{
    Break_Flag=0;
    check=0;
    line=0;
    //Mtot1.Motortot_Reset();
    switch (godir)
    {
    case F:Mtot1.Motortot_SetDirForward();break;
    case B:Mtot1.Motortot_SetDirBackward();break;
    case L:Mtot1.Motortot_SetDirLeft();break;
    case R:Mtot1.Motortot_SetDirRight();break;
    }
    delay(100);
    do
    {
        if(!(check%=200))
        {
            /*if((CheckResSim2(godir)||CheckResSim(godir)))
            {
                Stright_Fix(godir,checkdir,500);
            }*/
            if (CheckResSim(checkdir))
            {
                Line_Plus(godir,checkdir,delayms);
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
    check=0;
}

void runtest()
{   
    Mtot1.Motortot_ForwardR(100,1);
    delay(100);
    Mtot1.Motortot_LeftR(100,1);    
    Goline(1,L,L,100);
    Goline(2,F,F,100);
    /*do
    {
        QRCode=QR_Getstring(&Serial);
    }while(QRCode=="");*/
    delay(1000);//起点-扫码
    Goline(4,F,R,100);
    Goline(1,R,R,100);
    delay(1000);//扫码-原料区
    Mtot1.Motortot_RotLeft(100);
    Goline(3,F,R,100);
    Goline(1,R,R,100);
    delay(1000);//原料-粗加工区
    Goline(2,F,F,100);
    delay(100);
    Mtot1.Motortot_RotLeft(100);
    Goline(3,F,L,100);
    Goline(1,R,L,100);
    delay(1000);//粗加工-精加工
    Goline(1,L,R,100);
    delay(100);
    Mtot1.Motortot_RotLeft(100);
    Mtot1.Motortot_RotLeft(100);
    Goline(5,R,R,100);
    Goline(3,F,L,100);
    //Goline(1,R,R,100);
    delay(1000);//精加工-原料二轮
    Mtot1.Motortot_RotLeft(100);
    Goline(3,F,R,100);
    Goline(1,R,R,100);
    delay(1000);//原料-粗加工
    Goline(2,F,F,100);
    delay(100);
    Mtot1.Motortot_RotLeft(100);
    Goline(3,F,L,100);
    Goline(1,R,L,100);
    delay(1000);//粗加工-精加工
    Mtot1.Motortot_ForwardR(100,4);
}

void runtest1()
{
    
}