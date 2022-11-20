#include"track.h"
unsigned int Temp[2] = { 0 };
unsigned int Temp1[2] = { 0 };
extern Motortot Mtot1;
extern Motor MotRot,MotLift;
bool Break_Flag = 0;
bool LinePassBreak=0;
int line=0,check=0;
u8 count=0;
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


void FindMid_Left(int delayms)
{
  Mtot1.Motortot_SetDirLeft();
  do
  {
    for(int i=0;i<50;i++)
    {
    Mtot1.Motortot_Steprun(delayms);
    }
    Read_Data(&Serial3,Temp);
  }
  while(Temp[0]!=0xEF); 
}

void FindMid_Right(int delayms)
{
  Mtot1.Motortot_SetDirRight();
  do
  {
    Read_Data(&Serial3,Temp);
    Mtot1.Motortot_Steprun(delayms);
  }
  while(Temp[0]!=0xEF);  
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

void Find_LeftEdge(int delayms)
{
  Mtot1.Motortot_SetDirLeft();
  do
  {
    Read_Data(&Serial3,Temp);
    Mtot1.Motortot_Steprun(delayms);
  }
  while(Temp[0]!=0xFE);  
}

bool NOnLineCheck()
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

bool NOnLineCheckSim()
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

void NLine_Plus(int delayms)
{
  bool LinePassBreak=0;
    do
    {
        if(!(check%=100))
        {
            if (!(NOnLineCheck()))
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
  
void NGoline(u8 Lineobj,int delayms)
{
    Break_Flag=0;
    check=0;
    line=0;
    //Mtot1.Motortot_Reset();
    do
    {
        if(!(check%=200))
        {
            if (NOnLineCheck())
            {
                NLine_Plus(delayms);
                if(line==Lineobj)
                {
                    Break_Flag=1;
                }
            }
            else
            {
              Follow();
            }
        }
        Mtot1.Motortot_Steprun(delayms);
        check++;
    } while (!Break_Flag);
    Break_Flag=0;
    line=0;
    check=0;
}
