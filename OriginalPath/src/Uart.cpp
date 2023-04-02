#include "Uart.h"
/* void Serial_Init(HardwareSerial *p)
{
  p->begin(9600);
} */

void Serial_Init(SoftwareSerial *p)
{
  p->begin(9600);
}

void Read_Data(SoftwareSerial *p,unsigned int *Data)         
{ 
  unsigned char y = 0;
  unsigned char USART_RX_STA[3] = { 0 };       //数据缓存区
  unsigned char Num = 0;              //数组计数
  unsigned int Receive_data = 0;       //数据缓存区
  
  p->write(0x57);
 ///////////////////////////数字量数值///////////////////////////////  
 
  for(y=0;y <= 5;y++)
  {
    delay(1);
    if(p->available() > 0)
    {
      USART_RX_STA[Num++] = p->read(); //依次读取接收到的数据
      if(Num == 1)
      {
        Num = 0;
        *Data = USART_RX_STA[0];
        break;
      }
    } 
  }
} 

void Read_Data(HardwareSerial *p,unsigned int *Data)         
{ 
  unsigned char y = 0;
  unsigned char USART_RX_STA[3] = { 0 };       //数据缓存区
  unsigned char Num = 0;              //数组计数
  unsigned int Receive_data = 0;       //数据缓存区
  
  p->write(0x57);
 ///////////////////////////数字量数值///////////////////////////////  
 
  for(y=0;y <= 5;y++)
  {
    delay(1);
    if(p->available() > 0)
    {
      USART_RX_STA[Num++] = p->read(); //依次读取接收到的数据
      if(Num == 1)
      {
        Num = 0;
        *Data = USART_RX_STA[0];
        break;
      }
    } 
  }
} 

