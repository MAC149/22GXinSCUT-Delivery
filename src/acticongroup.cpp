#include"actiongroup.h"
extern Motortot Mtot1;
extern Motor MotRot,MotLift;
void LiftReset()
{
  MotLift.Motor_SetDir(0);
  while(digitalRead(A2))
  {
    MotLift.Motor_StpRunTime(5,100);
  }
}

void RotReset()
{
  MotRot.Motor_SetDir(0);
  while(digitalRead(A1))
  {
    MotRot.Motor_StpRunTime(5,300);
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
      MotRot.Motor_StpRunTime(5,300);
    }
    if(digitalRead(A2))
    {
      MotLift.Motor_StpRunTime(5,100);
    }
  }
}



/* void wuliao_left_shang()
{

  myservo_1.write(60);    //物料盘旋转至60度位置
  myservo_2.write(80);     //机械爪张开
  RotReset();     //旋转电机右旋回中
  left(1800, x);           //左移
  forward(1500, x);        //前进
  myservo_2.write(42);     //机械爪合拢
  delay(1000);
  backward(1500, x);       //后退
  right(1800, x);          //右移回到物料架正中间
  rotation_left(ROTSTP, 300); //旋转电机左旋
  lift_down(2000, 200);     //升降电机下降
  myservo_2.write(80);      //机械爪张开，放置物料
  lift_up(100, 100);
  LiftReset();            //升降电机上升至限位器灯亮
  RotReset();             //旋转电机右旋回中
  myservo_1.write(120);
}


//前进，夹取上层中间物料
void wuliao_middle_shang()
{
  myservo_1.write(120);    //物料盘旋转至120度位置
  myservo_2.write(80);     //机械爪张开
  LimitReset();           //升降电机上升至限位器灯亮
  //旋转电机右旋回中
  forward(1500, x);        //前进
  myservo_2.write(42);     //机械爪合拢
  delay(1000);
  backward(1500, x);       //后退回到物料架正中间
  rotation_left(ROTSTP, 300); //旋转电机左旋
  lift_down(2000, 200);     //升降电机下降
  myservo_2.write(80);      //机械爪张开，放置物料
  LiftReset();            //升降电机上升至限位器灯亮
  RotReset();             //旋转电机右旋回中
  myservo_1.write(120);
}


//右移，前进，夹取上层右边物料
void wuliao_right_shang()
{
  myservo_1.write(180);    //物料盘旋转至180度位置
  myservo_2.write(80);     //机械爪张开
  LimitReset();     //升降电机上升至限位器灯亮
  //旋转电机右旋回中

  right(1800, x);          //右移
  forward(1500, x);        //前进
  myservo_2.write(42);     //机械爪合拢
  delay(1000);
  backward(1500, x);       //后退
  left(1800, x);           //左移回到物料架正中间
  rotation_left(ROTSTP, 300); //旋转电机左旋
  lift_down(2000, 200);     //升降电机下降
  myservo_2.write(80);      //机械爪张开，放置物料
  LiftReset();            //升降电机上升至限位器灯亮
  RotReset();             //旋转电机右旋回中
}


//左移，前进，夹取下层左边物料
void wuliao_left_down()
{
  myservo_1.write(60);    //物料盘旋转至60度位置
  myservo_2.write(80);     //机械爪张开

  LimitReset();     //升降电机上升至限位器灯亮
  //旋转电机右旋回中
  lift_down(11500, 200);    //升降电机下降
  left(1800, x);           //左移
  forward(1500, x);        //前进
  myservo_2.write(42);     //机械爪合拢
  delay(1000);
  backward(1500, x);       //后退
  right(1800, x);          //右移回到物料架正中间
  LiftReset();      //升降电机上升至限位器灯亮
  rotation_left(ROTSTP, 300); //旋转电机左旋
  lift_down(2000, 200);     //升降电机下降
  myservo_2.write(80);      //机械爪张开，放置物料

  LiftReset();      //升降电机上升至限位器灯亮

  RotReset();      //旋转电机右旋回中

}


//前进，夹取下层中间物料
void wuliao_middle_down()
{
  myservo_1.write(120);    //物料盘旋转至120度位置
  myservo_2.write(80);     //机械爪张开

  LimitReset();     //升降电机上升至限位器灯亮
  //旋转电机右旋回中
  lift_down(11500, 200);    //升降电机下降
  forward(1500, x);        //前进
  myservo_2.write(42);     //机械爪合拢
  delay(1000);
  backward(1500, x);       //后退回到物料架正中间

  LiftReset();      //升降电机上升至限位器灯亮
  rotation_left(ROTSTP, 300); //旋转电机左旋
  lift_down(2000, 200);     //升降电机下降
  myservo_2.write(80);      //机械爪张开，放置物料
  k = digitalRead(A2);      //升降电机上升至限位器灯亮
  LiftReset();
  RotReset();        //旋转电机右旋回中
  //物料盘旋转至180度位置
}


//右移，前进，夹取下层右边物料
void wuliao_right_down()
{
  myservo_1.write(180);    //物料盘旋转至180度位置
  myservo_2.write(80);     //机械爪张开

  LimitReset();    //升降电机上升至限位器灯亮
  //旋转电机右旋回中

  lift_down(11500, 200);    //升降电机下降

  right(1800, x);          //右移
  forward(1500, x);        //前进
  myservo_2.write(42);     //机械爪合拢
  delay(1000);
  backward(1500, x);       //后退
  left(1800, x);           //左移回到物料架正中间

  LiftReset();      //升降电机上升至限位器灯亮

  rotation_left(ROTSTP, 300); //旋转电机左旋
  lift_down(2000, 200);     //升降电机下降
  myservo_2.write(80);      //机械爪张开，放置物料

  LiftReset();      //升降电机上升至限位器灯亮

  RotReset();      //旋转电机右旋回中
} */