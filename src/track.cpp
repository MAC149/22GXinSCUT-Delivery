#include"track.h"
#define SPEED 300
unsigned int Temp[2] = { 0 };
unsigned int Temp1[2] = { 0 };
extern Motortot Mtot1;
extern Motor MotRot,MotLift;
bool Break_Flag = 0;
bool LinePassBreak=0;
int line=0,check=0;

/* void mpuadjust(double angle)
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
        Mtot1.Motortot_RotLeftTime(200, 16);
      }
      else
        break;
    }
  }
  else{
    while(1){
    temp = (mpu6050() + mpu6050()+ mpu6050()) / 3.0;
    if(temp > angle+ 0.5){
      Mtot1.Motortot_RotRightTime(200, 8);
      //u8g2.drawStr(0,40,ecvt()
    }
    else if(temp < angle- 0.5){
       Mtot1.Motortot_RotLeftTime(200, 8);
    }
    else
      break;
    }
  } 
} */

void FindMid_Left(int delayms)
{
  Mtot1.Motortot_SetDirLeft();
  do
  {
    Mtot1.Motortot_SteprunRAW(delayms,50);
    Read_Data(&Serial3,Temp);
    Serial.println(Temp[0]);
  }
  while(Temp[0]!=0xF7);  
}

void FindMid_Right(int delayms)
{
  Mtot1.Motortot_SetDirRight();
  do
  {
    Mtot1.Motortot_SteprunRAW(delayms,50);
    Read_Data(&Serial3,Temp);
  }
  while(Temp[0]!=0xF7);  
}

void Find_RightEdge(int delayms)
{
  Mtot1.Motortot_SetDirRight();
  do
  {
    Mtot1.Motortot_SteprunRAW(delayms,50);
    Read_Data(&Serial3,Temp);
  }
  while(Temp[0]!=0x7F);  
}

void Find_LeftEdge(int delayms)
{
  Mtot1.Motortot_SetDirLeft();
  do
  {
    Mtot1.Motortot_SteprunRAW(delayms,50);
    Read_Data(&Serial3,Temp);
  }
  while(Temp[0]!=0xFE);  
}

void Find_Mid()
{
  Read_Data(&Serial3,Temp);
  if(Temp[0]==0xF7 || Temp[0]==0x00);
  else if(Temp[0]>0xE7)
  {
    FindMid_Left(SPEED);
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

/* void track2()
{
while(Temp[0]!=0x00){
  Read_Data(&Serial3,Temp);
  switch(Temp[0])
  {                                         //8765 4321
    case 0xFE:     Mtot1.Motortot_RotLeftTime(SPEED,50); break;    //1111 1110
    case 0xFD:     Mtot1.Motortot_RotLeftTime(SPEED,50); break;   //1111 1101
    case 0xFB:    Mtot1.Motortot_RotLeftTime(SPEED,50); break;   //1111 1011
    case 0xF3:     Mtot1.Motortot_RotLeftTime(SPEED,50); break;      //1111 0011
    case 0xF7:     Mtot1.Motortot_ForwardTime(SPEED,50); break;      //1111 0111
    
    case 0xE7:    Mtot1.Motortot_RotRightTime(SPEED,50);break;      //1110 0111   //正中间的位置
   
    case 0xEF:     Mtot1.Motortot_RotRightTime(SPEED,50);break;       //1110 1111
    case 0xDF:     Mtot1.Motortot_RotRightTime(SPEED,50);break;    //1101 1111
    case 0xBF:    Mtot1.Motortot_RotRightTime(SPEED,50);break;    //1011 1111
    case 0xCF:     Mtot1.Motortot_RotRightTime(SPEED,50);break;       //1100 1111
    case 0x7F:     Mtot1.Motortot_RotRightTime(SPEED,50);break;    //0111 1111
    case 0x00:      ; break;
    default :Mtot1.Motortot_ForwardTime(SPEED,50);break;
    }
  }
} */

bool OnLineCheck(HardwareSerial*p)
{
  int count=0;
  Read_Data(p,Temp);
  for(u8 i=0x01;i<=0x80;i<<1)
  {
    if((Temp[0]&i)==i)
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

bool OnLineCheckSim(HardwareSerial*p)
{
    Read_Data(p,Temp);
    if(Temp[0]==0x00)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Line_Plus(HardwareSerial*p,int delayms,int Linobj)
{
  LinePassBreak=0;
  if (Linobj!=line+1)
  {
    do
    {
        if(!(check%=100))
        {
            if (!(OnLineCheckSim(p)))
            {
                LinePassBreak=1;
            }
        }
        Mtot1.Motortot_SteprunRAW(delayms,5);
        check++;
    }while (!LinePassBreak);
  }
  LinePassBreak=0;
line++;
}

void FRGoline(u8 Lineobj,int delayms)
{
  Break_Flag=0;
  check=0;
  line=0;
  //Mtot1.Motortot_Reset();
  do
  {
    if(!(check%=3))
    {
      if (OnLineCheckSim(&Serial3))
      {
        Mtot1.Motortot_SetDirForward();
        Line_Plus(&Serial3,delayms,Lineobj);
        if(line==Lineobj)
        {
          Break_Flag=1;
        }
      }
      else 
      {
        //mpuadjust(Dir);
       }
    }
    Read_Data(&Serial3,Temp);
    switch(Temp[0])
    {                                         //8765 4321
      case 0xFE:    Mtot1.Motortot_RotLeftTime(SPEED,50); break;    //1111 1110
      case 0xFD:    Mtot1.Motortot_RotLeftTime(SPEED,50); break;   //1111 1101
      case 0xFB:    Mtot1.Motortot_RotLeftTime(SPEED,50); break;   //1111 1011
      case 0xF3:     Mtot1.Motortot_RotLeftTime(SPEED,50); break;      //1111 0011
      case 0xF7:     Mtot1.Motortot_ForwardTime(SPEED,50); break;      //1111 0111
      case 0xE7:    Mtot1.Motortot_RotRightTime(SPEED,50);break;      //1110 0111   //正中间的位置
      case 0xEF:     Mtot1.Motortot_RotRightTime(SPEED,50);break;       //1110 1111
      case 0xDF:     Mtot1.Motortot_RotRightTime(SPEED,50);break;    //1101 1111
      case 0xBF:    Mtot1.Motortot_RotRightTime(SPEED,50);break;    //1011 1111
      case 0xCF:     Mtot1.Motortot_RotRightTime(SPEED,50);break;       //1100 1111
      case 0x7F:     Mtot1.Motortot_RotRightTime(SPEED,50);break;    //0111 1111
      case 0x00:     break;
      default :Mtot1.Motortot_ForwardTime(SPEED,50);break;
      }
      check++;
  }while (!Break_Flag);
  Break_Flag=0;
  line=0;
  check=0;
}

void BRGoline(u8 Lineobj,int delayms)
{
  Break_Flag=0;
  check=0;
  line=0;
  //Mtot1.Motortot_Reset();
  do
  {
    if(!(check%=3))
    {
      if (OnLineCheckSim(&Serial2))
      {
        Mtot1.Motortot_SetDirBackward();
        Line_Plus(&Serial2,delayms,Lineobj);
        if(line==Lineobj)
        {
          Break_Flag=1;
        }
      }
      else 
      {
        //mpuadjust(Dir);
       }
    }
    Read_Data(&Serial3,Temp);
    switch(Temp[0])
    {                                         //8765 4321
      case 0xFE:    Mtot1.Motortot_RotRightTime(SPEED,50); break;    //1111 1110
      case 0xFD:    Mtot1.Motortot_RotRightTime(SPEED,50); break;   //1111 1101
      case 0xFB:    Mtot1.Motortot_RotRightTime(SPEED,50); break;   //1111 1011
      case 0xF3:     Mtot1.Motortot_RotRightTime(SPEED,50); break;      //1111 0011
      case 0xF7:     Mtot1.Motortot_BackwardTime(SPEED,50); break;      //1111 0111
      case 0xE7:    Mtot1.Motortot_RotLeftTime(SPEED,50);break;      //1110 0111   //正中间的位置
      case 0xEF:     Mtot1.Motortot_RotLeftTime(SPEED,50);break;       //1110 1111
      case 0xDF:     Mtot1.Motortot_RotLeftTime(SPEED,50);break;    //1101 1111
      case 0xBF:    Mtot1.Motortot_RotLeftTime(SPEED,50);break;    //1011 1111
      case 0xCF:     Mtot1.Motortot_RotLeftTime(SPEED,50);break;       //1100 1111
      case 0x7F:     Mtot1.Motortot_RotLeftTime(SPEED,50);break;    //0111 1111
      case 0x00:     break;
      default :Mtot1.Motortot_BackwardTime(SPEED,50);break;
      }
      check++;
  }while (!Break_Flag);
  Break_Flag=0;
  line=0;
  check=0;
}

