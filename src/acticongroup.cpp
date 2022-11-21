#include"actiongroup.h"
#define SPEED 200
#define PAW_CLOSE 42
#define PAW_OPEN 80
#define PAD_ONE 60
#define PAD_TWO 120
#define PAD_THREE 180
#define ROTSTP 3300

extern Motortot Mtot1;
extern Motor MotRot,MotLift;
extern Servo Servo_Pad,Servo_Paw;
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

void Place_P1()
{
  Servo_Pad.write(PAD_THREE);    //物料盘旋转至180度位置
  Servo_Paw.write(PAW_OPEN);     //机械爪张开
  LimitReset();
  Mtot1.Motortot_ForwardTime(SPEED, 1500);        //前进
  MotRot.Motor_RunAllSet(RotL,300, ROTSTP); //旋转电机左旋
  MotLift.Motor_RunAllSet(DOWN,SPEED, 2000);     //升降电机下降
  Servo_Paw.write(PAW_CLOSE); 
  MotLift.Motor_RunAllSet(UP,SPEED, 250);     //升降电机下降
  RotReset();     
  MotLift.Motor_RunAllSet(DOWN,SPEED, 9800);
  Servo_Paw.write(PAW_OPEN);
  Mtot1.Motortot_BackwardTime(SPEED, 1500);       //后退
  LimitReset();
}

void Place_P1_Blue()//L
{
  Mtot1.Motortot_LeftTime(SPEED,1800);
  Place_P1();
  Mtot1.Motortot_RightTime(SPEED, 1800); 
}
void Place_P1_Red()//M
{
  Place_P1();
}
void Place_P1_Green()//R
{
  Mtot1.Motortot_RightTime(SPEED, 1800);          //右移
  Place_P1();
  Mtot1.Motortot_LeftTime(SPEED, 1800);
}

