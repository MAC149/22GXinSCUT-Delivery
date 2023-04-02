/*********************************************************************
 *  函数名称：uart_Init
 *  函数功能：8路灰度串口初始化
 *  形    参：无
 *  输    出：无
 *  备    注：无
 ********************************************************************/
extern float z;
 void uart_Init()
 {
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
///////////////////////////数字量数值/////////////////////////////// 


/*********************************************************************
 *  函数名称：track_zhixian1()
 *  函数功能：直线循迹
 *  形    参：无
 *  输    出：无
 *  备    注：串口
 *  前
 ********************************************************************/

void track2()
{
int x=80;
  unsigned int Temp[2] = { 0 };       //数据缓存区   
  Read_Data(Temp);
//  Serial.println(Temp[0]);
while(Temp[0]!=0x00){
  Read_Data(Temp);
  switch(Temp[0])
  {                                         //8765 4321
    case 0xFE:     zuoxuan(25,x); break;    //1111 1110
    case 0xFD:     zuoxuan(25,x); break;   //1111 1101
    case 0xFB:      zuoxuan(25,x); break;   //1111 1011
    case 0xF3:     zuoxuan(25,x); break;      //1111 0011
    case 0xF7:     forward(25,x); break;      //1111 0111
    
    case 0xE7:     forward(25,x); break;      //1110 0111   //正中间的位置
   
    case 0xEF:     forward(25,x);break;       //1110 1111
    case 0xDF:     youxuan(25,x);break;    //1101 1111
    case 0xBF:     youxuan(25,x);break;    //1011 1111
    case 0xCF:     youxuan(25,x);break;       //1100 1111
    case 0x7F:     youxuan(25,x);break;    //0111 1111
    case 0x00:        ;   break;
    default :forward(25,x);break;
  }
  /*
  for(int i=0;i<10;i++){
    if(z>5)
    { zuoxuan(10,x);}
    else if(z<-5)
    {youxuan(10,x);}}
    */
}

}
void track6()
{
int x=80;
  unsigned int Temp[2] = { 0 };       //数据缓存区   
  Read_Data(Temp);
//  Serial.println(Temp[0]);
while(Temp[0]!=0x00){
  Read_Data(Temp);
  switch(Temp[0])
  {                                         //8765 4321
    case 0xFE:     zuoxuan(25,x); break;    //1111 1110
    case 0xFD:     zuoxuan(25,x); break;   //1111 1101
    case 0xFB:      zuoxuan(25,x); break;   //1111 1011
    case 0xF3:     zuoxuan(25,x); break;      //1111 0011
    case 0xF7:     zuoxuan(25,x); break;      //1111 0111
    
    case 0xE7:     forward(25,x); break;      //1110 0111   //正中间的位置
   
    case 0xEF:     youxuan(25,x);break;       //1110 1111
    case 0xDF:     youxuan(25,x);break;    //1101 1111
    case 0xBF:     youxuan(25,x);break;    //1011 1111
    case 0xCF:     youxuan(25,x);break;       //1100 1111
    case 0x7F:     youxuan(25,x);break;    //0111 1111
    case 0x00:        ;   break;
    default :forward(25,x);break;
  }
 
}

}

void track22()
{
int x=80;
  unsigned int Temp[2] = { 0 };       //数据缓存区   
  Read_Data(Temp);
//  Serial.println(Temp[0]);
while(Temp[0]!=0x00){
  Read_Data(Temp);
  switch(Temp[0])
  {                                         //8765 4321
    case 0xFE:     zuoxuan(25,x); break;    //1111 1110
    case 0xFD:     zuoxuan(25,x); break;   //1111 1101
    case 0xFB:      zuoxuan(25,x); break;   //1111 1011
    case 0xF3:     zuoxuan(25,x); break;      //1111 0011
    case 0xF7:     forward(25,x); break;      //1111 0111
    
    case 0xE7:     forward(25,x); break;      //1110 0111   //正中间的位置
   
    case 0xEF:     forward(25,x);break;       //1110 1111
    case 0xDF:     youxuan(25,x);break;    //1101 1111
    case 0xBF:     youxuan(25,x);break;    //1011 1111
    case 0xCF:     youxuan(25,x);break;       //1100 1111
    case 0x7F:     youxuan(25,x);break;    //0111 1111
    case 0x00:        ;   break;
    default :forward(25,x);break;
  }
 
}

}
