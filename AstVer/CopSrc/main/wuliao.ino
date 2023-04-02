#define PAD_ONE 45              //物料盘1
#define PAD_TWO 105             //物料盘2
#define PAD_THREE 165           //物料盘3
#define PAW_OPEN 94           //机械爪张开
#define PAW_CLOSE 54            //机械爪合拢
#define LIFT_GROUND 13800       //升降电机下降放置物料到地上
#define LIFT_PILE 7600          //升降电机下降放置物料进行码垛
#define LIFT_PAD 2550           //升降电机下降放置物料到物料盘
#define LIFT_CLAMP 2400         //升降电机下降夹取物料
#define LIFT_SECOND 11000       //升降电机下降夹取原料区下层物料
#define ROT_PAD 2800            //旋转电机转向物料盘

extern int k;  //上方限位器，A2
extern int h;  //下方限位器，A1
//红色-120 蓝色--60 绿色--180
//新45,105,165
int currentPAD=0;
void Pad_Smth(int target)
{
  if(currentPAD==target)
  {
    return;
  }
  else if(currentPAD>target)
  {
    for(int i=currentPAD;i>=target;i-=5)
  {
    myservo_1.write(i);     
    delay(50);
  }
  }
  else
  {
    for(int i=currentPAD;i<=target;i+=5)
    {
      myservo_1.write(i);     
      delay(50);
    }
  }
  currentPAD=target;
}
/**************************************************************/
/*                         物料区                             */
//左移，前进，夹取上层左边物料
void wuliao_left_shang() 
{
   catch1();                      //机械爪抓取步骤一   
   // left(1800,x);               //左移  
   // forward(1550,x);            //前进
   left_forward();
   catch2();                      //机械爪抓取步骤二  
   // backward(1550,x);           //后退
   // right(1800,x);              //右移回到物料架正中间     
   backward_right();                          
   catch3();                      //机械爪抓取步骤三  
}

  
//前进，夹取上层中间物料
void wuliao_middle_shang()  
{
   catch1();                      //机械爪抓取步骤一   
   // forward(1550,x);            //前进   
   forward_L2R2();                //前进至右二或左二灰度灯灭
   catch2();                      //机械爪抓取步骤二  
   // backward(1550,x);           //后退回到物料架正中间 
   backward_middle();      
   catch3();                      //机械爪抓取步骤三  
}

  
//右移，前进，夹取上层右边物料
void wuliao_right_shang()  
{
   catch1();                       //机械爪抓取步骤一 
   // right(1800,x);               //右移
   // forward(1550,x);             //前进
   right_forward();
   catch2();                       //机械爪抓取步骤二  
   // backward(1550,x);            //后退                    
   // left(1800,x);                //左移回到物料架正中间 
   backward_left();
   catch3();                      //机械爪抓取步骤三
}


//左移，前进，夹取下层左边物料
void wuliao_left_down()           
{
   catch11();                     //机械爪抓取步骤一（下）
   // left(1800,x);               //左移
   left_L3();
   forward(1550,x);            //前进
   //left_forward();
   catch22();                     //机械爪抓取步骤二（下）
   right(2600,150);               //右移回到正中间             
   track22();                      //巡线前进至前方灰度检测到黑线
}

  
//前进，夹取下层中间物料
void wuliao_middle_down()  
{
   catch11();                      //机械爪抓取步骤一（下）
   forward(1550,x);             //前进
  //  forward_L2R2();                 //前进至右二或左二灰度灯灭
   catch22();                      //机械爪抓取步骤二（下）      
   track22();                       //巡线前进至前方灰度检测到黑线 
}

  
//右移，前进，夹取下层右边物料
void wuliao_right_down()   
{
   catch11();                      //机械爪抓取步骤一（下）
   //  right(1950,x);              //右移
   right_R3();
    forward(1550,x);            //前进
   //  right_forward();
   catch22();                      //机械爪抓取步骤二（下） 
   left(2600,150);                 //左移回到正中间             
   track22();                       //巡线前进至前方灰度检测到黑线
}

       
/**********************************************************/
/*                        粗加工区                        */
void cu_left()                                 //放物料
{
   Pad_Smth(PAD_ONE);      //物料盘旋转至45度位置
   catch1();                      //机械爪抓取步骤一
   // left(2300,x);               //左移    
   // forward(1400,x);            //前进
   left_forward();
   catch4();                      //从物料盘中夹起物料放到地上
   // backward(1400,150);         //后退,右移回到正中间
   backward_right();                       
}

void cu_left2()                               //夹物料
{
   Pad_Smth(PAD_ONE);      //物料盘旋转至45度位置
   catch1();                      //机械爪抓取步骤一
   // left(2300,x);               //左移    
   // forward(1400,x);            //前进
   left_forward();
   catch5();                      //从地上夹起物料放到物料盘中
   // backward(1400,150);         //后退,右移回到正中间
   backward_right();                                    
}

 void cu_middle()
{
   Pad_Smth(PAD_TWO);      //物料盘旋转至105度位置
   catch1();                      //机械爪抓取步骤一
   forward_L2R2();                //前进至右二或左二灰度灯灭, 
   catch4();                      //从物料盘中夹起物料放到地上
   backward_middle();             //后退回到正中间                    
}

void cu_middle2()
{
   Pad_Smth(PAD_TWO);      //物料盘旋转至105度位置
   catch1();                      //机械爪抓取步骤一
   forward_L2R2();                //前进至右二或左二灰度灯灭
   catch5();                      //从地上夹起物料放到物料盘中
   backward_middle();             //后退回到正中间         
}

  void cu_right()
{
   Pad_Smth(PAD_THREE);   //物料盘旋转至165度位置
   catch1();                     //机械爪抓取步骤一
   //  right(2300,x);            //右移  
   //  forward(1400,x);          //前进
   right_forward();
   catch4();                      //从物料盘中夹起物料放到地上
   // backward(1400,150);         //后退,左移回到正中间
   backward_left();              
}

void cu_right2()
{
   Pad_Smth(PAD_THREE);     //物料盘旋转至165度位置
   catch1();                       //机械爪抓取步骤一
   // right(2300,x);               //右移    
   // forward(1400,x);             //前进
   right_forward();
   catch5();                       //从地上夹起物料放到物料盘中
   // backward(1400,150);          //后退,左移回到正中间
   backward_left();  
 }

 /**************************************************************/
 /*                    半加工区                                */
 void ban_left()
 {
   Pad_Smth(PAD_ONE);       //物料盘旋转至45度位置
   catch1();                       //机械爪抓取步骤一
   // left(2300,x);                //左移
   left_L3();                      //左移至左三灰度灯灭    
   catch4();                       //从物料盘中夹起物料放到地上
   right(2300,150);                //右移回到正中间             
 }

void ban_middle()
{
   Pad_Smth(PAD_TWO);       //物料盘旋转至105度位置
   catch1();                       //机械爪抓取步骤一
   catch4();                       //从物料盘中夹起物料放到地上
 }

 void ban_right()
 {
   Pad_Smth(PAD_THREE);      //物料盘旋转至165度位置
   catch1();                        //机械爪抓取步骤一
   //  right(2300,x);               //右移
   right_R3();                      //右移至右三灰度灯灭
   catch4();                        //从物料盘中夹起物料放到地上
   left(2300,150);                  //左移回到正中间             
 }

void ban_left2()
{
   Pad_Smth(PAD_ONE);       //物料盘旋转至45度位置
   catch1();                       //机械爪抓取步骤一
   // left(2300,x);                //左移
   left_L3();                      //左移至左三灰度灯灭 
   catch6();                       //从物料盘中夹起物料码垛   
   right(2300,150);                  //右移回到正中间             
}

void ban_middle2()
{
   Pad_Smth(PAD_TWO);       //物料盘旋转至105度位置
   catch1();                       //机械爪抓取步骤一
   catch6();                       //从物料盘中夹起物料码垛   
}
 
void ban_right2()
{
   Pad_Smth(PAD_THREE);      //物料盘旋转至165度位置
   catch1();                        //机械爪抓取步骤一
   //  right(2300,x);               //右移
   right_R3();                      //右移至右三灰度灯灭
   catch6();                        //从物料盘中夹起物料放到地上
   left(2300,150);                  //左移回到正中间                   
}
