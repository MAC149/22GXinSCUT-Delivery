#include"step.h"
#define SPEED 100
Motortot Mtot1(4,3,2,10,9,8,7,6,5,13,12,11);//AEn,Astp,Adir,Bstp,BEn,Bdir,CEn,Cstp,Cdir,DEn,Dstp,Ddir
bool Break_Flag = 0;
bool LinePassBreak=0;
String QRCode="";
int line=0,check=0;
enum Dirc{F=1,B,L,R};
int HT[2]={A2,A3};
u8 count=0;

void uart_Init()
 {
   Serial3.begin(9600);  
 }
 
unsigned int Temp[2] = { 0 };
unsigned int Temp1[2] = { 0 };

void Read_Data(unsigned int *Data)         
{ 
  unsigned char y = 0;
  unsigned char USART_RX_STA[3] = { 0 };       //数据缓存区
  unsigned char Num = 0;              //数组计数
  unsigned int Receive_data = 0;       //数据缓存区
  
  Serial3.write(0x57);
 ///////////////////////////数字量数值///////////////////////////////  
 
  for(y=0;y <= 5;y++)
  {
    delay(1);
    if(Serial3.available() > 0)
    {
      USART_RX_STA[Num++] = Serial3.read(); //依次读取接收到的数据
      if(Num == 1)
      {
        Num = 0;
        *Data = USART_RX_STA[0];
        break;
      }
    } 
  }
} 

void Follow()
{
    Read_Data(Temp1);
    switch(Temp1[0])
    {                                     
        case 0xF7:     Mtot1.Motortot_SetDirRotLeft(); delay(30);Mtot1.Motortot_SteprunRAW(10,30); break;      //1111 0111
        case 0xE7:     Mtot1.Motortot_SetDirForward();delay(30); Mtot1.Motortot_SteprunRAW(10,10); break;      //1110 0111   //正中间的位置
        case 0xEF:     Mtot1.Motortot_SetDirRotRight(); delay(30);Mtot1.Motortot_SteprunRAW(10,30);break;       //1110 1111
        case 0x00:    break;
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
    Read_Data(Temp);
  }
  while(Temp[0]!=0xF7 && Temp[0]!=0xE7 && Temp[0]!=0xEF); 
}

void FindMid_Right(int delayms)
{
  Mtot1.Motortot_SetDirRight();
  do
  {
    Read_Data(Temp);
    Mtot1.Motortot_Steprun(delayms);
  }
  while(Temp[0]!=0xF7);  
}

bool NOnLineCheck()
{
  Read_Data(Temp);
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


void runtest()
{   
    Mtot1.Motortot_ForwardR(SPEED,1);
    delay(100);
    Mtot1.Motortot_LeftR(SPEED,2);
    delay(100);
    FindMid_Left(200);
    delay(100);
    Mtot1.Motortot_LeftR(SPEED,1);
    NGoline(2,SPEED);
    NGoline(3,SPEED);
    Mtot1.Motortot_RightR(SPEED,1);
    FindMid_Right(SPEED);

    
    
    
}
