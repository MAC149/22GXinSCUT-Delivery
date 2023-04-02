#define PAD_ONE 45
#define PAD_TWO 105
#define PAD_THREE 165
#define PAW_OPEN 116
#define PAW_CLOSE 66
#define LIFT_DOWN_GROUND 13100  
#define LIFT_DOWN_PAD 2550
#define LIFT_DOWN_STACK 7400
#define ROT_PAD 2800
#define OG_MOVE_FRONT 1500
#define OG_MOVE_SIDE 2400
#define OG_DOWN_DOWN 11000
#define RM_MOVE_SIDE 2300
#define RM_MOVE_FRONT 1400
#define RM_BAK_ADJ 25
#define RM_SIDE_ADJ 25
#define SM_MOVE_SIDE 2300
#define SIDE_SPEED 200
extern int k;  //上方限位器，A2
extern int h;  //下方限位器，A1
//红色-120 蓝色--60 绿色--180
//新45,105,165
int ReturnCount=0;
void Lift_Reset()
{
  while(digitalRead(A2))
  {
    lift_up(5, 10);
  }
}

void Rot_Reset()
{
  while (digitalRead(A1)) {
    //Serial.println(h);
    rotation_right(5, 100);
  }
}

void LiftRot_Reset()
{
  while(digitalRead(A1) || digitalRead(A2))
  {
    if(digitalRead(A1))
    {
      rotation_right(5, 100);
    }
    if(digitalRead(A2))
    {
      lift_up(5, 10);
    }
  }
}

void HT_ToLeft()
{
  while (!digitalRead(left_M)) {
    left(10, SIDE_SPEED);
    ReturnCount++;
  }
}

void HT_LeftReturn()
{
  left(10*ReturnCount, 200);
  ReturnCount=0;
}

void HT_RightReturn()
{
 right(10*ReturnCount, 200);
 ReturnCount=0;
}

void HT_ToRight()
{
  while (!digitalRead(right_M)) {
    right(10, SIDE_SPEED);
    ReturnCount++;
  }
}

/**************************************************************/
/*                         物料区                             */
//左移，前进，夹取上层左边物料

void OG_Pick_Up()
{
  myservo_2.write(PAW_OPEN);
  LiftRot_Reset();
  // adjust_angle(90);  //MPU
  forward(OG_MOVE_FRONT,SPEED);         //前进
  myservo_2.write(PAW_CLOSE);  //机械爪合拢
  delay(500);
  //backward(OG_MOVE_FRONT,SPEED);        //后退
  track33();                       //后退至后方灰度检测到黑线
  track22();                       //巡线前进至前方灰度检测到黑线
  //trackbw();
  rotation_left(ROT_PAD, 100);   //旋转电机左旋
  lift_down(LIFT_DOWN_PAD, 80);        //升降电机下降
  myservo_2.write(PAW_OPEN);  //机械爪张开，放置物料
  delay(250);
  Lift_Reset();
  Rot_Reset();
}

void OG_Pick_Up_Left()
{
  // while (!digitalRead(left_M)) {
  //   left(10, 200);
  // }
  // while (!digitalRead(right_L1)) {
  //   R2 = digitalRead(39);
  //   forward(50, 200);
  // }
  //left(OG_MOVE_SIDE,SPEED); 
  HT_ToLeft();
  //HT_Left_Track('L');
  OG_Pick_Up();
  HT_RightReturn();
  //right(OG_MOVE_SIDE,SPEED);           //右移回到物料架正中
  // track3();
  // right(2600, 150);  //右移回到正中间
  // track2();
}

void OG_Pick_Up_Mid()
{
  OG_Pick_Up();
  // track3();
  // track2();
}

void OG_Pick_Up_Right()
{
  // while (!digitalRead(L3)) {
  //   left(10, 200);
  // }
  // while (!digitalRead(R2)) {
  //   R2 = digitalRead(39);
  //   forward(50, 200);
  // }
  //right(OG_MOVE_SIDE,SPEED);           //右移
  HT_ToRight();
  OG_Pick_Up();
  HT_LeftReturn();
  //left(OG_MOVE_SIDE,SPEED);
  // track3();
  // right(2600, 150);  //右移回到正中间
  // track2();
}

void OG_Pick_Down()
{
  myservo_2.write(PAW_OPEN);
  LiftRot_Reset();
  //adjust_angle(90);  //MPU
  lift_down(OG_DOWN_DOWN, 50);
  forward(OG_MOVE_FRONT,SPEED);         //前进
  myservo_2.write(PAW_CLOSE);  //机械爪合拢
  delay(500);
  backward(OG_MOVE_FRONT,SPEED);        //后退
  //trackbw();
  Lift_Reset();
  rotation_left(ROT_PAD, 100);   //旋转电机左旋
  lift_down(LIFT_DOWN_PAD, 80);        //升降电机下降
  myservo_2.write(PAW_OPEN);  //机械爪张开，放置物料
  delay(250);
  LiftRot_Reset();
}

void OG_Pick_Down_Left()
{
  // while (!digitalRead(L3)) {
  //   left(10, 200);
  // }
  // while (!digitalRead(R2)) {
  //   R2 = digitalRead(39);
  //   forward(50, 200);
  // }
  left(OG_MOVE_SIDE,HTSPEED); 
  //HT_ToLeft();
  OG_Pick_Down();
  //HT_RightReturn();
  right(OG_MOVE_SIDE,HTSPEED);           //右移回到物料架正中
  // track3();
  // right(2600, 150);  //右移回到正中间
  // track2();
}

void OG_Pick_Down_Mid()
{
  OG_Pick_Down();
  // track3();
  // track2();
}

void OG_Pick_Down_Right()
{
  // while (!digitalRead(L3)) {
  //   left(10, 200);
  // }
  // while (!digitalRead(R2)) {
  //   R2 = digitalRead(39);
  //   forward(50, 200);
  // }
  right(OG_MOVE_SIDE,HTSPEED);           //右移
  //HT_ToRight();
  OG_Pick_Down();
  //HT_LeftReturn();
  left(OG_MOVE_SIDE,HTSPEED);
  // track3();
  // right(2600, 150);  //右移回到正中间
  // track2();
}


/**********************************************************/
/*                        粗加工区                        */
void RM_Place()
{
  // adjust_angle(0);
  LiftRot_Reset();
  //forward(RM_MOVE_FRONT,SPEED); 
  myservo_2.write(PAW_OPEN);  //机械爪张开
  rotation_left(ROT_PAD, 100);      //旋转电机左旋
  lift_down(LIFT_DOWN_PAD, 80);  //升降电机下降，原来数据2300,80
  myservo_2.write(PAW_CLOSE);    //机械爪合拢，夹取物料
  delay(250);
  Lift_Reset();
  Rot_Reset();
  lift_down(LIFT_DOWN_GROUND, 50);  //升降电机下降，原来数据13000
  myservo_2.write(PAW_OPEN);
  delay(500);
  Lift_Reset();
  //backward(RM_MOVE_FRONT,150);        //后退
  // track33();
  //trackbw();
  // track22();
}

void RM_Pick()
{
  // adjust_angle(0);
  LiftRot_Reset();
  //forward(RM_MOVE_FRONT,SPEED); 
  myservo_2.write(PAW_OPEN);
  lift_down(13100, 50);        //升降电机下降 13000
  myservo_2.write(PAW_CLOSE);  //机械爪合拢
  delay(500);
  Lift_Reset();
  rotation_left(ROT_PAD, 100);      //旋转电机左旋
  lift_down(LIFT_DOWN_PAD, 80);  //升降电机下降,2300
  myservo_2.write(PAW_OPEN);
  delay(250);
  Lift_Reset();
  Rot_Reset();
  //backward(RM_MOVE_FRONT,150);        //后退
  //trackbw();
}

void RM_Place_Left()
{
  myservo_1.write(PAD_ONE);
  //left(RM_MOVE_SIDE,SIDE_SPEED);
  //HT_ToLeft();
  //backward(RM_BAK_ADJ,SPEED);
  //right(RM_SIDE_ADJ,SIDE_SPEED);
  HT_Left_Track('L');
  RM_Place();
  HT_Right_Track('R');
  trackR();
  //HT_RightReturn();
  
}

void RM_Pick_Left()
{
  myservo_1.write(PAD_ONE);
  //left(RM_MOVE_SIDE,SIDE_SPEED);
  //HT_ToLeft();
  HT_Left_Track('L');
  RM_Pick();
  HT_Right_Track('R');
  trackR();
  //HT_RightReturn();
  //right(RM_MOVE_SIDE,SIDE_SPEED);
}

void RM_Place_Mid()
{
  myservo_1.write(PAD_TWO);
  RM_Place();
}

void RM_Pick_Mid()
{
  myservo_1.write(PAD_TWO);
  RM_Pick();
}

void RM_Place_Right()
{
  myservo_1.write(PAD_THREE);
  //right(RM_MOVE_SIDE,SIDE_SPEED);
  //HT_ToRight();
  HT_Right_Track('R');
  RM_Place();
  HT_Left_Track('L');
  trackL();
  //HT_LeftReturn();
  //left(RM_MOVE_SIDE,SIDE_SPEED);
}

void RM_Pick_Right()
{
  myservo_1.write(PAD_THREE);
  //right(RM_MOVE_SIDE,SIDE_SPEED);
  //HT_ToRight();
  HT_Right_Track('R');
  RM_Pick();
  HT_Left_Track('L');
  trackL();
  //HT_LeftReturn();
  //left(RM_MOVE_SIDE,SIDE_SPEED);
}

/**************************************************************/
/*                    半加工区                                */
void SM_Place_Ground()
{
  // adjust_angle(-90);
  LiftRot_Reset();
  myservo_2.write(PAW_OPEN);  //机械爪张开
  rotation_left(ROT_PAD, 100);      //旋转电机左旋
  lift_down(LIFT_DOWN_PAD, 80);  //升降电机下降，原来数据2300,80
  myservo_2.write(PAW_CLOSE);    //机械爪合拢，夹取物料
  delay(250);
  Lift_Reset();
  Rot_Reset();
  lift_down(LIFT_DOWN_GROUND, 50);  //升降电机下降，原来数据13000
  myservo_2.write(PAW_OPEN);
  delay(500);
  Lift_Reset();
}

void SM_Place_Ground_Left()
{
  myservo_1.write(PAD_ONE);
  left(SM_MOVE_SIDE,SIDE_SPEED);
  SM_Place_Ground();
  right(SM_MOVE_SIDE,SIDE_SPEED);
}

void SM_Place_Ground_Mid()
{
  myservo_1.write(PAD_TWO);
  SM_Place_Ground();
}

void SM_Place_Ground_Right()
{
  myservo_1.write(PAD_THREE);
  right(SM_MOVE_SIDE,SIDE_SPEED);
  SM_Place_Ground();
  left(SM_MOVE_SIDE,SIDE_SPEED);
}

void SM_Place_Stack()
{
  myservo_2.write(PAW_OPEN);  //机械爪张开
  rotation_left(ROT_PAD, 100);      //旋转电机左旋
  lift_down(LIFT_DOWN_PAD, 80);  //升降电机下降，原来数据2300,80
  myservo_2.write(PAW_CLOSE);    //机械爪合拢，夹取物料
  delay(250);
  Lift_Reset();
  Rot_Reset();
  lift_down(LIFT_DOWN_STACK, 50);  //升降电机下降，原来数据13000
  myservo_2.write(PAW_OPEN);
  delay(500);
  Lift_Reset();
}

void SM_Place_Stack_Left()
{
  myservo_1.write(PAD_ONE);
  left(SM_MOVE_SIDE,SIDE_SPEED);
  SM_Place_Stack();
  right(SM_MOVE_SIDE,SIDE_SPEED);
}

void SM_Place_Stack_Mid()
{
  myservo_1.write(PAD_TWO);
  SM_Place_Stack();
}

void SM_Place_Stack_Right()
{
  myservo_1.write(PAD_THREE);
  right(SM_MOVE_SIDE,SIDE_SPEED);
  SM_Place_Stack();
  left(SM_MOVE_SIDE,SIDE_SPEED);
}