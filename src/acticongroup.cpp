#include"actiongroup.h"
#define SPEED 300
#define PAW_CLOSE 42
#define PAW_OPEN 76
#define PAD_ONE 60          //RED
#define PAD_TWO 120       //GREEN
#define PAD_THREE 175   //BLUE
#define ROTSTP 2850


extern Motortot Mtot1;
extern Motor MotRot,MotLift;
extern Servo Servo_Pad,Servo_Paw;
extern String WL1_pose,WL2_pose,QRCode;
enum Lift{UP=0,DOWN};
enum RotDir{RotR=0,RotL};

void LiftReset()
{
  MotLift.Motor_SetDir(0);
  while(digitalRead(A2))
  {
    MotLift.Motor_StpRunTime(100,5);
  }
}

void RotReset()
{
  MotRot.Motor_SetDir(0);
  while(digitalRead(A1))
  {
    MotRot.Motor_StpRunTime(300,5);
  }
}

void LimitReset()
{
  MotLift.Motor_SetDir(0);
  MotRot.Motor_SetDir(0);
  while(digitalRead(A1)||digitalRead(A2))
  {
    if(digitalRead(A1))
    {
      MotRot.Motor_StpRunTime(300,5);
    }
    if(digitalRead(A2))
    {
      MotLift.Motor_StpRunTime(100,5);
    }
  }
}

void Pick_Upper()
{
  Servo_Paw.write(PAW_OPEN);     //机械爪张开
  LimitReset(); 
  Mtot1.Motortot_ForwardTime(SPEED, 1500);        //前进
  Servo_Paw.write(PAW_CLOSE);     //机械爪合拢
  delay(1000);
  Mtot1.Motortot_BackwardTime(SPEED, 1500);       //后退
  MotRot.Motor_RunAllSet(RotL,300, ROTSTP);  //旋转电机左旋
  MotLift.Motor_RunAllSet(DOWN,SPEED,200);    //升降电机下降
  Servo_Paw.write(PAW_OPEN);      //机械爪张开，放置物料
  LiftReset();            //升降电机上升至限位器灯亮
  RotReset();             //旋转电机右旋回中
}

void Pick_Lower()
{
  Servo_Paw.write(PAW_OPEN);     //机械爪张开
  LimitReset();     //升降电机上升至限位器灯亮
  //旋转电机右旋回中
  MotLift.Motor_RunAllSet(DOWN,SPEED, 11500);    //升降电机下降
  Mtot1.Motortot_ForwardTime(SPEED, 1500);        //前进
  Servo_Paw.write(PAW_CLOSE);     //机械爪合拢
  delay(1000);
  Mtot1.Motortot_BackwardTime(SPEED, 1500);       //后退回到物料架正中间
  LiftReset();      //升降电机上升至限位器灯亮
  MotRot.Motor_RunAllSet(RotL,300, ROTSTP);  //旋转电机左旋
  MotLift.Motor_RunAllSet(DOWN,SPEED, 2000);     //升降电机下降
  Servo_Paw.write(PAW_OPEN);      //机械爪张开，放置物料
  LiftReset();  //升降电机上升至限位器灯亮
  RotReset();        //旋转电机右旋回中
}

void Pick_UpLeft()
{
  Servo_Pad.write(PAD_ONE);    //物料盘旋转至60度位置
  Mtot1.Motortot_LeftTime(SPEED,1800);
  Pick_Upper();
  Mtot1.Motortot_RightTime(SPEED, 1800);          //右移回到物料架正中间
}

void Pick_UpMid()
{
  Servo_Pad.write(PAD_TWO);    //物料盘旋转至120度位置
  Pick_Upper();
}

void Pick_UpRight()
{
  Servo_Pad.write(PAD_THREE);    //物料盘旋转至180度位置
  Mtot1.Motortot_RightTime(SPEED, 1800);          //右移
  Pick_Upper();
  Mtot1.Motortot_LeftTime(SPEED, 1800);           //左移回到物料架正中间
}

void Pick_DownLeft()
{
  Servo_Pad.write(PAD_ONE);    //物料盘旋转至60度位置
  Mtot1.Motortot_LeftTime(SPEED, 1800);           //左移
  Pick_Lower();
  Mtot1.Motortot_RightTime(SPEED, 1800);          //右移回到物料架正中间
}

void Pick_DownMid()
{
  Servo_Pad.write(PAD_TWO);    //物料盘旋转至120度位置
  Pick_Lower();
}

void Pick_DownRight()
{
  Servo_Pad.write(PAD_THREE);    //物料盘旋转至180度位置
  Mtot1.Motortot_RightTime(SPEED, 1800);          //右移
  Pick_Lower();
  Mtot1.Motortot_LeftTime(SPEED, 1800);           //左移回到物料架正中间
}

void Pad_Switch(char target)
{
  switch(target)
  {
    case '1':Servo_Pad.write(PAD_ONE);break;
    case '2':Servo_Pad.write(PAD_TWO);break;
    case '3':Servo_Pad.write(PAD_THREE);break;
    default:break;
  }
}

void Place_P1()
{
  //Servo_Pad.write(PAD_THREE);    //物料盘旋转至180度位置
  Servo_Paw.write(PAW_OPEN);     //机械爪张开
  LimitReset();
  Mtot1.Motortot_ForwardTime(SPEED, 1500);        //前进
  MotRot.Motor_RunAllSet(RotL,300, ROTSTP); //旋转电机左旋
  delay(1000);//----------
  MotLift.Motor_RunAllSet(DOWN,SPEED, 2000);     //升降电机下降
  Servo_Paw.write(PAW_CLOSE); 
  MotLift.Motor_RunAllSet(UP,SPEED, 250);     //升降电机下降
  RotReset();     
  MotLift.Motor_RunAllSet(DOWN,SPEED, 9800);
  Servo_Paw.write(PAW_OPEN);
  delay(1000);//----------------
  Mtot1.Motortot_BackwardTime(SPEED, 1500);       //后退
  LimitReset();
}

void Place_P2()
{
  Servo_Paw.write(PAW_OPEN);     //机械爪张开
  LimitReset();
  Mtot1.Motortot_ForwardTime(SPEED, 1500);        //前进
  MotRot.Motor_RunAllSet(RotL,300, ROTSTP); //旋转电机左旋
  delay(1000);//----------
  MotLift.Motor_RunAllSet(DOWN,SPEED, 2000);     //升降电机下降
  Servo_Paw.write(PAW_CLOSE); 
  MotLift.Motor_RunAllSet(UP,SPEED, 250);     //升降电机下降
  RotReset();     
  MotLift.Motor_RunAllSet(DOWN,SPEED, 4900);
  Servo_Paw.write(PAW_OPEN);
  delay(1000);//----------------
  Mtot1.Motortot_BackwardTime(SPEED, 1500);       //后退
  LimitReset();
}

void Place_P1_Blue()//L
{
  Servo_Pad.write(PAD_THREE);
  Mtot1.Motortot_LeftTime(SPEED,1800);
  Place_P1();
  Mtot1.Motortot_RightTime(SPEED, 1800); 
}
void Place_P1_Red()//M
{
  Servo_Pad.write(PAD_ONE);
  Place_P1();
}
void Place_P1_Green()//R
{
  Servo_Pad.write(PAD_TWO);
  Mtot1.Motortot_RightTime(SPEED, 1800);          //右移
  Place_P1();
  Mtot1.Motortot_LeftTime(SPEED, 1800);
}

void Place_P2_Blue()
{
  Servo_Pad.write(PAD_THREE);
  Mtot1.Motortot_LeftTime(SPEED,1800);
  Place_P2();
  Mtot1.Motortot_RightTime(SPEED, 1800); 
}

void Place_P2_Red()
{
  Servo_Pad.write(PAD_ONE);
  Place_P2();
}

void Place_P2_Green()
{
  Servo_Pad.write(PAD_TWO);
  Mtot1.Motortot_RightTime(SPEED,1800);
  Place_P2();
  Mtot1.Motortot_LeftTime(SPEED, 1800); 
}

int Action_Order(int Phase,char target)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      if(WL1_pose[i]==target)
      {
        return i+1;
      }
    }
  }
  else
  {
    for(int i=0;i<3;i++)
    {
      if(WL2_pose[i]==target)
      {
        return i+1;
      }
    }
  }
  return -1;
}

void OG_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(Action_Order(Phase,QRCode[i]))
      {
        case 1:Pad_Switch(QRCode[i]);Pick_UpLeft();break;
        case 2:Pad_Switch(QRCode[i]);Pick_UpMid();break;
        case 3:Pad_Switch(QRCode[i]);Pick_UpRight();break;
        default:break;
      }
    }
  }
  else
  {
    for(int i=4;i<7;i++)
    {
      switch(Action_Order(Phase,QRCode[i]))
      {
        case 1:Pad_Switch(QRCode[i]);Pick_DownLeft();break;
        case 2:Pad_Switch(QRCode[i]);Pick_DownMid();break;
        case 3:Pad_Switch(QRCode[i]);Pick_DownRight();break;
        default:break;
      }
    }
  }
}

void RM_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(QRCode[i])
      {
        case 3:Place_P1_Blue();break;
        case 2:Place_P1_Red();break;
        case 1:Place_P1_Green();break;
        default:break;
      }
    }
    for(int i=0;i<3;i++)
    {
      switch(QRCode[i])
      {
        case 3:Pad_Switch(QRCode[i]);Pick_DownLeft();break;
        case 2:Pad_Switch(QRCode[i]);Pick_DownMid();break;
        case 1:Pad_Switch(QRCode[i]);Pick_DownRight();break;
        default:break;
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=3;i<6;i++)
    {
     switch(QRCode[i])
      {
        case 3:Place_P1_Blue();break;
        case 2:Place_P1_Red();break;
        case 1:Place_P1_Green();break;
        default:break;
      }
    }
    for(int i=3;i<6;i++)
    {
      switch(QRCode[i])
      {
        case 3:Pad_Switch(QRCode[i]);Pick_DownLeft();break;
        case 2:Pad_Switch(QRCode[i]);Pick_DownMid();break;
        case 1:Pad_Switch(QRCode[i]);Pick_DownRight();break;
        default:break;
      }
    }
  }
}

void SM_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(QRCode[i])
      {
        case 3:Place_P1_Blue();break;
        case 2:Place_P1_Red();break;
        case 1:Place_P1_Green();break;
        default:break;
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=3;i<6;i++)
    {
      switch(QRCode[i])
      {
         case 3:Place_P2_Blue();break;
         case 2:Place_P2_Red();break;
         case 1:Place_P2_Green();break;
        default:break;
      }
    }
  }
}
