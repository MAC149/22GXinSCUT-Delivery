#include<openmv.h>

String WL1_pose;    // 上层物料放置位置
String WL2_pose;    // 下层物料放置位置

char uart_recv[64]="a";     // 串口缓存数据

void Uart_send_openmv(HardwareSerial *p,char CMD)  
{
  //Serial1.listen();
  switch(CMD){
    case '1':
    p->write("ST");  
    Serial.println("Send to openmv:START");
    break;

    case '2':
    p->write("ED"); 
    Serial.println("Send to openmv:END");
    break;
    
    default :
    Serial.println("Wrong cmd to send.");
    break;
  }
  }

void Uart_send_openmv(SoftwareSerial *p,char CMD)  
{
  //Serial1.listen();
  switch(CMD){
    case '1':
    p->write("ST");  
    Serial.println("Send to openmv:START");
    break;

    case '2':
    p->write("ED"); 
    Serial.println("Send to openmv:END");
    break;
    
    default :
    Serial.println("Wrong cmd to send.");
    break;
  }
  }



void Uart_recv_openmv(HardwareSerial *p) 
{
  if(p->available()>0)
  {
   int i=0;
   while(p->available()>0)
  {
    uart_recv[i]=p->read();
    if(uart_recv[i]=='b'){break;}
    i++;
    delay(2);   // 延时3ms
   }

    if(uart_recv[0]=='W')     // 获取物料放置位置
    {
      WL1_pose = String(uart_recv[1])+String(uart_recv[2])+String(uart_recv[3]);
      WL2_pose = String(uart_recv[4])+String(uart_recv[5])+String(uart_recv[6]);
    
    Serial.println("Got WL:"+WL1_pose+WL2_pose);
      }

     // 输出接收到的数据
     Serial.println(uart_recv);
       } 
  }

void Uart_recv_openmv(SoftwareSerial *p) 
{
  if(p->available()>0)
  {
   int i=0;
   while(p->available()>0)
  {
    uart_recv[i]=p->read();
    i++;
    delay(2);   // 延时3ms
   }

if(uart_recv[0]=='W')     // 获取物料放置位置
    {
      WL1_pose = String(uart_recv[1])+String(uart_recv[2])+String(uart_recv[3]);
      WL2_pose = String(uart_recv[4])+String(uart_recv[5])+String(uart_recv[6]);
    
    Serial.println("Got WL:"+WL1_pose+WL2_pose);
      }

     // 输出接收到的数据
     Serial.println(uart_recv);
       } 
  }



void Get_message(HardwareSerial *p,char task)   // Q-二维码 P-物料位置 S-抓取顺序
{
  switch(task)
  {
    case 'S':
    Uart_send_openmv(p,'1'); 
    while(WL1_pose=="" || WL2_pose=="")
        Uart_recv_openmv(p);

    Serial.println("********** WLpose recved. ************");
    break;

    case 'E':
    Uart_send_openmv(p,'2'); 
    break;

    default : 
    break;
  }
  }
  
void Get_message(SoftwareSerial *p,char task)   // Q-二维码 P-物料位置 S-抓取顺序
{
  switch(task)
  {
    case 'S':
    Uart_send_openmv(p,'1'); 
    while(WL1_pose=="" || WL2_pose=="")
        Uart_recv_openmv(p);

    Serial.println("********** WLpose recved. ************");
    break;

    case 'E':
    Uart_send_openmv(p,'2'); 
    break;

    default : 
    break;
  }
}

