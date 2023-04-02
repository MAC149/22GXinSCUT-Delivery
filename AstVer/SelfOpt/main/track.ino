#define HTSPEED 120
#define CSTEPS 50
#define SSTEPS 4
/*********************************************************************
 *  函数名称：uart_Init
 *  函数功能：8路灰度串口初始化
 *  形    参：无
 *  输    出：无
 *  备    注：无
 ********************************************************************/
extern float z;
unsigned int HTData[2]={0};
void uart_Init() {
  Serial3.begin(9600);
  Serial2.begin(9600);
}

/*********************************************************************
 *  函数名称：Read_Data
 *  函数功能：读取数据
 *  形    参：*Data: 读取到的数据
 *  输    出：无
 *  备    注：无
 ********************************************************************/
void Read_Data(unsigned int *Data) {
  unsigned char y = 0;
  unsigned char USART_RX_STA[3] = { 0 };  //数据缓存区
  unsigned char Num = 0;                  //数组计数
  unsigned int Receive_data = 0;          //数据缓存区

  Serial3.write(0x57);
  ///////////////////////////数字量数值///////////////////////////////

  for (y = 0; y <= 5; y++) {
    delay(1);
    if (Serial3.available() > 0) {
      USART_RX_STA[Num++] = Serial3.read();  //依次读取接收到的数据
      if (Num == 1) {
        Num = 0;
        *Data = USART_RX_STA[0];
        break;
      }
    }
  }
}
///////////////////////////数字量数值///////////////////////////////


/*********************************************************************
 *  函数名称：track_zhixian1()
 *  函数功能：直线循迹
 *  形    参：无
 *  输    出：无
 *  备    注：串口
 *  前
 ********************************************************************/

void track1() {

  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data(Temp);
  //  Serial.println(Temp[0]);
  //while(1){
  //if(Temp[0]!=0xFF)
  //forward(50,300);
  //else
  //motor_stop();}
  while (Temp[0] != 0xF7 && Temp[0] != 0xE7 && Temp[0] != 0xEF) {
    Read_Data(Temp);
    switch (Temp[0]) {                //8765 4321
      case 0xF7: delay(1000); break;  //1111 0111
      case 0xE7: delay(1000); break;  //1110 0111   //正中间的位置
      case 0xEF: delay(1000); break;  //1110 1111
      default: left(50, 100); break;
    }
  }
  delay(5);
}



void track2() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0x00) {
    Read_Data(Temp);
    switch (Temp[0]) {                   //8765 4321
      case 0xFE: zuoxuan(SSTEPS, HTSPEED); break;  //1111 1110
      case 0xFD: zuoxuan(SSTEPS, HTSPEED); break;  //1111 1101
      case 0xFB: zuoxuan(SSTEPS, HTSPEED); break;  //1111 1011
      case 0xF3: zuoxuan(SSTEPS, HTSPEED); break;  //1111 0011
      case 0xF7: forward(CSTEPS, HTSPEED); break;  //1111 0111

      case 0xE7: forward(CSTEPS, HTSPEED); break;  //1110 0111   //正中间的位置

      case 0xEF: forward(CSTEPS, HTSPEED); break;  //1110 1111
      case 0xDF: youxuan(SSTEPS, HTSPEED); break;  //1101 1111
      case 0xBF: youxuan(SSTEPS, HTSPEED); break;  //1011 1111
      case 0xCF: youxuan(SSTEPS, HTSPEED); break;  //1100 1111
      case 0x7F: youxuan(SSTEPS, HTSPEED); break;  //0111 1111
      case 0x00:; break;
      default: forward(CSTEPS, HTSPEED); break;
    }
    /*
  for(int i=0;i<10;i++){
    if(z>5)
    { zuoxuan(10,HTSPEED);}
    else if(z<-5)
    {youxuan(10,HTSPEED);}}
    */
  }
}

void trackbw() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0x00) {
    Read_Data(Temp);
    backward(8, HTSPEED);
  }
}

void track22() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0x00) {
    Read_Data(Temp);
    switch (Temp[0]) {                   //8765 4321
      case 0xFE: zuoxuan(SSTEPS, HTSPEED); break;  //1111 1110
      case 0xFD: zuoxuan(SSTEPS, HTSPEED); break;  //1111 1101
      case 0xFB: zuoxuan(SSTEPS, HTSPEED); break;  //1111 1011
      case 0xF3: zuoxuan(SSTEPS, HTSPEED); break;  //1111 0011
      case 0xF7: forward(CSTEPS, HTSPEED); break;  //1111 0111

      case 0xE7: forward(CSTEPS, HTSPEED); break;  //1110 0111   //正中间的位置

      case 0xEF: forward(CSTEPS, HTSPEED); break;  //1110 1111
      case 0xDF: youxuan(SSTEPS, HTSPEED); break;  //1101 1111
      case 0xBF: youxuan(SSTEPS, HTSPEED); break;  //1011 1111
      case 0xCF: youxuan(SSTEPS, HTSPEED); break;  //1100 1111
      case 0x7F: youxuan(SSTEPS, HTSPEED); break;  //0111 1111
      case 0x00:; break;
      default: forward(CSTEPS, HTSPEED); break;
    }
  }
}

void track6()
{
  unsigned int Temp[2] = { 0 };       //数据缓存区   
  Read_Data(Temp);
//  Serial.println(Temp[0]);
while(Temp[0]!=0x00){
  Read_Data(Temp);
  switch(Temp[0])
  {                                         //20765 4321
    case 0xFE:     zuoxuan(SSTEPS,HTSPEED); break;    //1111 1110
    case 0xFD:     zuoxuan(SSTEPS,HTSPEED); break;   //1111 1101
    case 0xFB:      zuoxuan(SSTEPS,HTSPEED); break;   //1111 1011
    case 0xF3:     zuoxuan(SSTEPS,HTSPEED); break;      //1111 0011
    case 0xF7:     zuoxuan(SSTEPS,HTSPEED); break;      //1111 0111
    
    case 0xE7:     forward(CSTEPS,HTSPEED); break;      //1110 0111   //正中间的位置
   
    case 0xEF:     youxuan(SSTEPS,HTSPEED);break;       //1110 1111
    case 0xDF:     youxuan(SSTEPS,HTSPEED);break;    //1101 1111
    case 0xBF:     youxuan(SSTEPS,HTSPEED);break;    //1011 1111
    case 0xCF:     youxuan(SSTEPS,HTSPEED);break;       //1100 1111
    case 0x7F:     youxuan(SSTEPS,HTSPEED);break;    //0111 1111
    case 0x00:        ;   break;
    default :forward(CSTEPS,HTSPEED);break;
  }
 
}

}



char HT_Status()
{
  if(digitalRead(left_L2)&&digitalRead(left_R2))
  {
    return 'O';
  }
  if(digitalRead(left_L1)&&digitalRead(right_L1))
  {
    return 'L';
  }
  if(digitalRead(left_L2)&&digitalRead(right_L2))
  {
    return 'L';
  }
  if(digitalRead(left_R1)&&digitalRead(right_R1))
  {
    return 'R';
  }
  if(digitalRead(left_R2)&&digitalRead(right_R2))
  {
    return 'R';
  }
  return 'O';
}

void HT_Right_Track(char dir)
{
  while(!digitalRead(right_L2)||!digitalRead(right_R2))
  {
    switch(HT_Status())
    {
      case 'R':youxuan(SSTEPS,HTSPEED);break;
      case 'L':zuoxuan(SSTEPS,HTSPEED);break;
      case 'O':switch(dir){case 'L':left(SSTEPS,HTSPEED);break;case 'R':right(SSTEPS,HTSPEED);break;}break;
      case 'F':forward(SSTEPS,HTSPEED);break;
      case 'B':backward(SSTEPS,HTSPEED);break;
      default:break;
    }
  }
}

void HT_Left_Track(char dir)
{
  while((!digitalRead(left_L2))||(!digitalRead(right_R2)))
  {
    switch(HT_Status())
    {
      case 'R':youxuan(SSTEPS,HTSPEED);break;
      case 'L':zuoxuan(SSTEPS,HTSPEED);break;
      case 'O':switch(dir){case 'L':left(SSTEPS,HTSPEED);break;case 'R':right(SSTEPS,HTSPEED);break;};break;
      case 'F':forward(SSTEPS,HTSPEED);break;
      case 'B':backward(SSTEPS,HTSPEED);break;
      default:break;    
    }
  }
}