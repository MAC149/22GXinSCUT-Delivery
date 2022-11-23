#include"track.h"
#define SPEED 200
enum Dir{N=0,S=180,W=-90,E=90};
unsigned int Temp[2] = { 0 };
unsigned int Temp1[2] = { 0 };
extern Motortot Mtot1;
extern Motor MotRot,MotLift;
bool Break_Flag = 0;
bool LinePassBreak=0;
int line=0,check=0;
u8 count=0;

void mpuadjust(double angle)
{
  double temp;
  if(angle == 180 || angle == -180)
  {
    while(1)
    {
      temp = (mpu6050() + mpu6050()+ mpu6050()) / 3.0;
      if((temp > -180 + 0.5)&&(temp < 0)){
        Mtot1.Motortot_RotRightTime(200, 16);
        //u8g2.drawStr(0,40,ecvt()
      }
      else if((temp < 180 - 0.5)&&(temp >= 0)){
        Mtot1.Motortot_RotLeftTime(200, 16);;
      }
      else
        break;
    }
  }
  else{
    while(1){
    temp = (mpu6050() + mpu6050()+ mpu6050()) / 3.0;
    if(temp > angle+ 0.5){
      Mtot1.Motortot_RotLeftTime(200, 16);
      //u8g2.drawStr(0,40,ecvt()
    }
    else if(temp < angle- 0.5){
       Mtot1.Motortot_RotRightTime(200, 16);;
    }
    else
      break;
    }
  } 
}

void FindMid_Left(int delayms)
{
  Mtot1.Motortot_SetDirLeft();
  do
  {
    Read_Data(&Serial3,Temp);
    Mtot1.Motortot_Steprun(delayms);
  }
  while(Temp[0]!=0xF7);  
}

void FindMid_Right(int delayms)
{
  Mtot1.Motortot_SetDirRight();
  do
  {
    Read_Data(&Serial3,Temp);
    Mtot1.Motortot_Steprun(delayms);
  }
  while(Temp[0]!=0xF7);  
}

void Find_RightEdge(int delayms)
{
  Mtot1.Motortot_SetDirRight();
  do
  {
    Read_Data(&Serial3,Temp);
    Mtot1.Motortot_Steprun(delayms);
  }
  while(Temp[0]!=0x7F);  
}





void Find_Mid()
{
  Read_Data(&Serial3,Temp);
  if(Temp[0]==0xF7)
  {
    return;
  }
  else if(Temp[0]>0xE7)
  {
    Find_LeftEdge(SPEED);
  }
  else if(Temp[0]<0xE7)
  {
    FindMid_Right(SPEED);
  }
}


void Follow()
{
    Read_Data(&Serial3,Temp1);
    switch(Temp1[0])
    {                                     
        case 0xEF:     Mtot1.Motortot_SetDirRotLeft(); delay(30);Mtot1.Motortot_SteprunRAW(10,30); break;      //1110 1111 
        case 0xE7:     Mtot1.Motortot_SetDirForward();delay(30); Mtot1.Motortot_SteprunRAW(10,10); break;      //1110 0111   //正中间的位置
        case 0xF7:     break;       //1111 0111
        case 0x00:     break;
        default :         Mtot1.Motortot_SetDirForward();delay(30); Mtot1.Motortot_SteprunRAW(10,10); break;  
    }
}

bool FROnLineCheck()
{
  Read_Data(&Serial3,Temp);
  for(u8 i=0x01;i<0x80;i<<1)
  {
    if((Temp[0]&i)==0x01)
    {
      count++;
    }
  }
  if(count>=4)
  {
    count=0;
    return 1;
  }
  else
  {
    count=0;
    return 0;
  }
}

bool FROnLineCheckSim()
{
    Read_Data(&Serial3,Temp);
    if(Temp[0]==0x00)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void FRLine_Plus(int delayms)
{
  bool LinePassBreak=0;
    do
    {
        if(!(check%=100))
        {
            if (!(FROnLineCheckSim()))
            {
                LinePassBreak=1;
            }
        }
        Mtot1.Motortot_Steprun(delayms);
        check++;
    }while (!LinePassBreak);
  LinePassBreak=0;
line++;
}
  
void FRGoline(int Dir,u8 Lineobj,int delayms)
{
    Break_Flag=0;
    check=0;
    line=0;
    //Mtot1.Motortot_Reset();
    do
    {
        if(!(check%=200))
        {
            if (FROnLineCheck())
            {
                FRLine_Plus(delayms);
                if(line==Lineobj)
                {
                    Break_Flag=1;
                }
            }
            else
            {
              mpuadjust(Dir);
              Find_Mid();
            }
        }
        Mtot1.Motortot_Steprun(delayms);
        check++;
    } while (!Break_Flag);
    Break_Flag=0;
    line=0;
    check=0;
}
