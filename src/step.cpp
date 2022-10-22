#include"step.h"
#define SPEED 100
Motortot Mtot1(52,50,48,46,44,42,40,38,36,34,32,30);//AEn,Astp,Adir,Bstp,BEn,Bdir,CEn,Cstp,Cdir,DEn,Dstp,Ddir
Motor MotRot(53,51,49);
Motor MotLift(47,45,43);
int LeftHT[5]={31,29,27,25,23};//L2 L1 M R1 R2
int RightHT[5]={41,39,37,35,33};
bool Break_Flag = 0;
bool LinePassBreak=0;
String QRCode="";
int line=0,check=0;
enum Dirc{F=1,B,L,R};
u8 count=0;

unsigned int Temp[2] = { 0 };
unsigned int Temp1[2] = { 0 };

void Follow()
{
    Read_Data(&Serial3,Temp1);
    switch(Temp1[0])
    {                                     
        case 0xF7:     Mtot1.Motortot_SetDirRotLeft(); delay(30);Mtot1.Motortot_SteprunRAW(10,30); break;      //1111 0111
        case 0xE7:     Mtot1.Motortot_SetDirForward();delay(30); Mtot1.Motortot_SteprunRAW(10,10); break;      //1110 0111   //正中间的位置
        case 0xEF:     break;       //1110 1111
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

void MotorTestDemo()
{
    /*
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
    delay(2000);*/
    MotRot.Motor_En(1);
    MotLift.Motor_En(1);
    MotRot.Motor_round(SPEED,1,1);
    //MotRot.Motor_round(SPEED,1,0);
    MotLift.Motor_round(SPEED,1,1);
    //MotLift.Motor_round(SPEED,1,0);
;    
}


void runtest()
{   
  Mtot1.Motortot_ForwardR(SPEED,1);//向前一步
  delay(100);
  Mtot1.Motortot_LeftR(SPEED,2);//向左到第二格
  delay(100);
  FindMid_Left(200);//左巡线
  delay(100);
  NGoline(2,SPEED);//前走2线
  //QRcode
  NGoline(3,SPEED);//前走三线
  //openmv
  Mtot1.Motortot_RightR(SPEED,1);
  FindMid_Right(SPEED);
  //servo
  Mtot1.Motortot_RotLeft(SPEED);
  FindMid_Right(SPEED);
  NGoline(3,SPEED);
  //servo
  NGoline(2,SPEED);
  Mtot1.Motortot_RotLeft(SPEED);
  FindMid_Right(SPEED);
  NGoline(2,SPEED);
  //servo
  Mtot1.Motortot_RotLeft(SPEED);
  NGoline(5,SPEED);
  Mtot1.Motortot_RotLeft(SPEED);
  Find_RightEdge(SPEED);
  
    
    
    
}
