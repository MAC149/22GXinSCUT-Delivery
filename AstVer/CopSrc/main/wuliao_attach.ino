extern int k;  //上方限位器，A2
extern int h;  //下方限位器，A1
/********************************电机*******************************/
/******************************升降/旋转****************************/
void lift_reset()           //升降电机上升至限位器灯亮
{
   k = digitalRead(A2);     
   while(k)
  {
    //Serial.println(k); 
    lift_up(5,10);
    k = digitalRead(A2);
  }
}

void rotation_reset()      //旋转电机右旋回中
{
   h = digitalRead(A1);
   while(h)               
 {
   //Serial.println(h); 
   rotation_right(5,100);
   h = digitalRead(A1);
 }  
}

/******************************底盘****************************/
void left_forward()              //左移后，前进
{
  L3 = digitalRead(27);          //左移至左三灰度灯灭,暗是1，亮输出0 
  while(1)
  {
     L3 = digitalRead(27);
     if(L3) break;
     left(5,200);
  }
  R2 = digitalRead(39);         //前进至右二灰度灯灭,暗是1，亮输出0 
  while(1)
 {
     R2 = digitalRead(39);
     if(R2) break;
     forward(50,200);
 }
}

void forward_L2R2()            //前进至右二或左二灰度灯灭,暗是1，亮输出0  
{
  //左侧灰度传感器31(L5) 29(L4) 27(L3) 25(L2) 23(L1)    暗是1，亮输出0
  L2 = digitalRead(25);
  //右侧灰度传感器41(L2) 39(L1) 37(M) 35(R1)  33(R2)
  R2 = digitalRead(39);
 while(1)
 {
    L2 = digitalRead(25);
    R2 = digitalRead(39);
    if(R2||L2||(R2&&L2)) break;
    forward(50,200);
 }
}

void right_forward()               //右移后，前进
{
  R3 = digitalRead(37);            //右移至右三灰度灯灭
  while(1)
  {
     R3 = digitalRead(37);
     if(R3) break;
     right(5,200);
  }
  L2 = digitalRead(25);           //前进至左二灰度灯灭
  while(1)
 {
     L2 = digitalRead(25);
     if(L2) break;
     forward(50,200);
  }
}

void backward_left()
{
   track33();                       //后退至后方灰度检测到黑线
   left(2600,150);                  //左移回到正中间
   track22();                       //巡线前进至前方灰度检测到黑线
}

void backward_middle()
{
   track33();                       //后退至后方灰度检测到黑线
   track22();                       //巡线前进至前方灰度检测到黑线
}

void backward_right()
{
   track33();                        //后退至后方灰度检测到黑线
   right(2600,150);                  //左移回到正中间
   track22();                        //巡线前进至前方灰度检测到黑线
}

void left_L3()                     //左移至左三灰度灯灭
{
  L3 = digitalRead(27);
  while(1)
  {
     L3 = digitalRead(27);
     if(L3) break;
     left(5,200);
  }
}


void right_R3()                     //右移至右三灰度灯灭
{
  R3 = digitalRead(37);
  while(1)
  {
     R3 = digitalRead(37);
     if(R3) break;
     right(5,200);
  }
}
/************************爪子*************************************/
/*********************原料区上层*********************************/
void catch1()                     //机械爪抓取步骤一  
{
   myservo_2.write(PAW_OPEN);     //机械爪张开
   lift_reset();                  //升降电机上升至限位器灯亮
   rotation_reset();              //旋转电机右旋回中
}

void catch2()                      //机械爪抓取步骤二  
{
    myservo_2.write(PAW_CLOSE);    //机械爪合拢
    delay(500);
}

void catch3()                     //机械爪抓取步骤三  
{
   rotation_left(ROT_PAD,100);    //旋转电机左旋
   lift_down(LIFT_PAD,80);        //升降电机下降将物料放到物料盘
   myservo_2.write(PAW_OPEN);     //机械爪张开，放置物料  
   delay(250);   
   lift_reset();                  //升降电机上升至限位器灯亮
   rotation_reset();              //旋转电机右旋回中
     

}

/************************原料区下层************************************/
void catch11()                     //机械爪抓取步骤一（下）  
{
   myservo_2.write(PAW_OPEN);     //机械爪张开
   rotation_reset();                //旋转电机右旋回中  
   lift_reset();                    //升降电机上升至限位器灯亮
   lift_down(LIFT_SECOND,50);     //升降电机下降夹取第二层物料
}

void catch22()                      //机械爪抓取步骤二（下）   
{
   myservo_2.write(PAW_CLOSE);    //机械爪合拢 
   delay(500);
   // backward(1550,x);       
   track3();                      //后退至后方灰度检测到黑线
   rotation_reset();                //旋转电机右旋回中  
   lift_reset();                    //升降电机上升至限位器灯亮                 
   rotation_left(ROT_PAD,100);    //旋转电机左旋
   lift_down(LIFT_PAD,80);        //升降电机下降将物料放到物料盘
   myservo_2.write(PAW_OPEN);     //机械爪张开，放置物料
   delay(250);     
  lift_reset();                    //升降电机上升至限位器灯亮
   rotation_reset();                //旋转电机右旋回中  
     

}

/********************从物料盘中夹起物料放到地上********************/
void catch4()
{
   rotation_left(ROT_PAD,100);    //旋转电机左旋到物料盘
   lift_down(LIFT_CLAMP,80);      //升降电机下降，夹取物料盘的物料
   myservo_2.write(PAW_CLOSE);    //机械爪合拢，夹取物料 
   delay(500);    
   lift_reset();                  //升降电机上升至限位器灯亮 
   rotation_reset();              //旋转电机右旋回中
   lift_down(LIFT_GROUND,50);     //升降电机下降，将物料放到地面
  for(int i=PAW_CLOSE;i<=PAW_OPEN;i+=5)
  {
       myservo_2.write(i);     //机械爪张开
    delay(50);
  }   
   lift_reset();                  //升降电机上升至限位器灯亮
     

}
/********************从地上夹起物料放到物料盘中********************/
void catch5()
{
  myservo_2.write(PAW_OPEN);     //机械爪张开
  lift_down(LIFT_GROUND,50);     //升降电机下降夹取地面的物料
   myservo_2.write(PAW_CLOSE);    //机械爪合拢，夹取物料 
   delay(500);
   lift_reset();                  //升降电机上升至限位器灯亮              
   rotation_left(ROT_PAD,100);    //旋转电机左旋到物料盘
   lift_down(LIFT_PAD,80);        //升降电机下降将物料放到物料盘
   myservo_2.write(PAW_OPEN);     //机械爪张开，放置物料   
   lift_reset();                  //升降电机上升至限位器灯亮
   rotation_reset();              //旋转电机右旋回中
  

}
/********************从物料盘中夹起物料码垛**********************/
void catch6()
{
   rotation_left(ROT_PAD,100);    //旋转电机左旋到物料盘
   lift_down(LIFT_CLAMP,80);      //升降电机下降，夹取物料盘的物料
   myservo_2.write(PAW_CLOSE);    //机械爪合拢，夹取物料 
   delay(500);    
   lift_reset();                  //升降电机上升至限位器灯亮 
   rotation_reset();              //旋转电机右旋回中
   lift_down(LIFT_PILE,50);     //升降电机下降，将物料放到地面
   for(int i=PAW_CLOSE;i<=PAW_OPEN;i+=5)
  {
       myservo_2.write(i);     //机械爪张开
    delay(50);
  }   
   lift_reset();                  //升降电机上升至限位器灯亮
     

}