//dir:转动方向  stp：步距角1.8   en:使能输出信号
//直径80mm  周长251.2            250步1dm
//电机初始化
void motor()
{
   pinMode(A_En,OUTPUT);
  pinMode(A_Stp,OUTPUT);
  pinMode(A_Dir,OUTPUT);
  pinMode(B_En,OUTPUT);
  pinMode(B_Stp,OUTPUT);
  pinMode(B_Dir,OUTPUT);
  pinMode(C_En,OUTPUT);
  pinMode(C_Stp,OUTPUT);
  pinMode(C_Dir,OUTPUT);
  pinMode(D_En,OUTPUT);
  pinMode(D_Stp,OUTPUT);
  pinMode(D_Dir,OUTPUT); 
  pinMode(lift_En,OUTPUT);
  pinMode(lift_Stp,OUTPUT);
  pinMode(lift_Dir,OUTPUT);
  pinMode(rotation_En,OUTPUT);
  pinMode(rotation_Stp,OUTPUT);
  pinMode(rotation_Dir,OUTPUT);
  digitalWrite(A_En,HIGH);
  digitalWrite(B_En,HIGH);
  digitalWrite(C_En,HIGH);
  digitalWrite(D_En,HIGH);
  digitalWrite(lift_En,HIGH);
  digitalWrite(rotation_En,HIGH);
  }
void forward(int steps,int times)   //直行
{
  digitalWrite(A_Dir, LOW);                         //左前  
  digitalWrite(B_Dir, HIGH);                         //右前  
  digitalWrite(C_Dir, HIGH);                         //右后  
  digitalWrite(D_Dir, LOW);                         //左后  
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
void backward(int steps,int times)   //向后走
{
  digitalWrite(A_Dir, HIGH);                         //左前
  digitalWrite(B_Dir, LOW);                         //右前
  digitalWrite(C_Dir, LOW);                         //右后
  digitalWrite(D_Dir, HIGH);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}

void left(int steps,int times)   //向左
{
  digitalWrite(A_Dir, HIGH);                         //左前
  digitalWrite(B_Dir, HIGH);                         //右前
  digitalWrite(C_Dir, LOW);                         //右后
  digitalWrite(D_Dir, LOW);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
void right(int steps,int times)   //向右
{
  digitalWrite(A_Dir, LOW);                         //左前
  digitalWrite(B_Dir, LOW);                         //右前
  digitalWrite(C_Dir, HIGH);                         //右后
  digitalWrite(D_Dir, HIGH);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
void zuoxuan(int steps,int times)      //左旋转
{
  digitalWrite(A_Dir, HIGH);                         //左前
  digitalWrite(B_Dir, HIGH);                         //右前
  digitalWrite(C_Dir, HIGH);                         //右后
  digitalWrite(D_Dir, HIGH);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
void youxuan(int steps,int times)      //右旋转
{
  digitalWrite(A_Dir, LOW);                         //左前
  digitalWrite(B_Dir, LOW);                         //右前
  digitalWrite(C_Dir, LOW);                         //右后
  digitalWrite(D_Dir, LOW);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}




//下方电机
void rotation_left(int steps,int times)                                        //左旋转
{
  digitalWrite(rotation_Dir, HIGH);                         
  for(int x=0;x<steps;x++)
  {   
    digitalWrite(rotation_Stp, HIGH);                        
    delayMicroseconds(times);
    digitalWrite(rotation_Stp, LOW);                        
    delayMicroseconds(times);
  }
}
void rotation_right(int steps,int times)                                        //右旋转
{
  digitalWrite(rotation_Dir, LOW);                         
  for(int x=0;x<steps;x++)
  {   
    digitalWrite(rotation_Stp, HIGH);                        
    delayMicroseconds(times);
    digitalWrite(rotation_Stp, LOW);                        
    delayMicroseconds(times);
  }
}

//上方电机
void lift_up(int steps,int times)                                        //上升
{
  digitalWrite(lift_Dir, LOW);                         
  for(int x=0;x<steps;x++)
  {   
    digitalWrite(lift_Stp, HIGH);                        
    delayMicroseconds(times);
    digitalWrite(lift_Stp, LOW);                        
    delayMicroseconds(times);
  }
}
void lift_down(long steps,int times)                                        //下降
{
  digitalWrite(lift_Dir, HIGH);                         
  for(int x=0;x<steps;x++)
  {   
    digitalWrite(lift_Stp, HIGH);                        
    delayMicroseconds(times);
    digitalWrite(lift_Stp, LOW);                        
    delayMicroseconds(times);
  }
}

void youqian(long steps,int times)   //向右前
{
  digitalWrite(A_En, LOW);                         //左前
  digitalWrite(B_Dir, HIGH);                         //右前
  digitalWrite(C_En, LOW);                         //右后
  digitalWrite(D_Dir, LOW);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
void zuohou(int steps,int times)   //向左后
{
  digitalWrite(A_En, LOW);                         //左前
  digitalWrite(B_Dir, LOW);                         //右前
  digitalWrite(C_En, LOW);                         //右后
  digitalWrite(D_Dir, LOW);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}

void zuoqian(int steps,int times)   //向左前
{
  //digitalWrite(A_En, LOW);                         //左前
  digitalWrite(B_Dir, HIGH);                         //右前
  //digitalWrite(C_En, LOW);                         //右后
  digitalWrite(D_Dir, LOW);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
void youhou(int steps,int times)   //向右后
{
  digitalWrite(A_Dir, LOW);                         //左前
  digitalWrite(B_En, LOW);                         //右前
  digitalWrite(C_Dir, LOW);                         //右后
  digitalWrite(D_En, LOW);                         //左后
  for(int x=0;x<steps;x++)
  {
    digitalWrite(A_Stp, HIGH);                         //A 
    digitalWrite(B_Stp, HIGH);                         //B
    digitalWrite(C_Stp, HIGH);                         //C
    digitalWrite(D_Stp, HIGH);                        //D
    delayMicroseconds(times);
    digitalWrite(A_Stp, LOW);                         //A 
    digitalWrite(B_Stp, LOW);                         //B
    digitalWrite(C_Stp, LOW);                         //C
    digitalWrite(D_Stp, LOW);                        //D
    delayMicroseconds(times);
  }
}
