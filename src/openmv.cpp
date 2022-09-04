#include<openmv.h>

/************ openmv-uart1 *************/
// 发送  CM+XX   XX = QR|扫描二维码 、 WL|获取物料放置位置
// 接收  QR_XXXXXX  WL_XXXXXX   (X = 1、2、3)
// 对应 QR|任务码  WL|物料位置           
String WL1_pose;    // 上层物料放置位置
String WL2_pose;    // 下层物料放置位置
String QR1_code;    // 上层物料任务码
String QR2_code;    // 上层物料任务码

char uart_recv[64];     // 串口缓存数据


void Uart_send_openmv(char CMD)  
{
  //Serial1.listen();
  switch(CMD){
    case '1':
    Serial1.print("CM+QR");  // 识别二维码
    Serial.println("Send to openmv:CM+QR");
    break;

    case '2':
    Serial1.print("CM+WL");  // 识别物料位置
    Serial.println("Send to openmv:CM+WL");
    break;
    
    default :
    Serial.println("Wrong cmd to send.");
    break;
  }
  }


void Uart_recv_openmv()   // QR1/QR2   CT1/CT2
{
  if(Serial1.available()>0)
  {
   int i=0;
   while(Serial1.available()>0)
  {
    uart_recv[i]=Serial1.read();
    i++;
    delay(2);   // 延时3ms
   }
   
   if(uart_recv[0]=='Q'&&uart_recv[1]=='R')     // 获取二维码
   {
    QR1_code = String(uart_recv[3])+String(uart_recv[4])+String(uart_recv[5]);
    QR2_code = String(uart_recv[6])+String(uart_recv[7])+String(uart_recv[8]);
    
    Serial.println("Got QR_CODE:"+QR1_code+QR2_code);
      
    }


    if(uart_recv[0]=='W'&&uart_recv[1]=='L')     // 获取物料放置位置
    {
      WL1_pose = String(uart_recv[3])+String(uart_recv[4])+String(uart_recv[5]);
      WL2_pose = String(uart_recv[6])+String(uart_recv[7])+String(uart_recv[8]);
    
    Serial.println("Got WL:"+WL1_pose+WL2_pose);
      }

     // 输出接收到的数据
     Serial.println(uart_recv);
       } 
  }


void Get_message(char task)   // Q-二维码 P-物料位置 S-抓取顺序
{
  switch(task)
  {
    case 'Q':
    Uart_send_openmv('1');  // 发送扫描二维码的指令  √
    while(QR1_code=="" && QR2_code=="")
        Uart_recv_openmv();

    Serial.println("********** QRcode recved. ************");
    break;

    case 'P':
    Uart_send_openmv('2');  // 发送扫描物料的指令  √
    while(WL1_pose=="" || WL2_pose=="")
      Uart_recv_openmv();
      
    Serial.println("********** WLpose recved. ************");
    break;

    default : 
    break;
  }
  }