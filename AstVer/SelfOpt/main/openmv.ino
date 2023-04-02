
String WL1_pose;    // 上层物料放置位置
String WL2_pose;    // 下层物料放置位置
//1--红 2--绿 3--蓝
//半成品,粗加工固定顺序--蓝红绿312
char uart_recv[64]="a";     // 串口缓存数据

String QR_Getstring()
{
  unsigned long starttime;
  String str = "";
  unsigned char Wakecmd[9] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x02, 0x01, 0xAB, 0xCD};
  mySerial.write(Wakecmd, 9);
  //等待回收信号结束
  while (mySerial.read() != 0x31);
  //delay(500);
  starttime = millis();
  while (true)
  {
    //扫码模块扫出来是会加换行符的
    str = mySerial.readStringUntil('/r');
    if ((str.length() >= 1) || (millis() - starttime > 5000))
      break;
  }
  return str;
}

void Uart_send_openmv(char CMD)  
{
  //Serial1.listen();
  switch(CMD){
    case '1':
    Serial1.print("ST");  
    Serial.println("Send to openmv:CM+ST");
    break;

    case '2':
    Serial1.print("ED"); 
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

//扫描获取物料颜色，结果保存在 WL1_pose 和 WL2_pose  ,WL1 ：上层 ， WL2 ： 下层
void Get_message(char task)   // Q-二维码 P-物料位置 S-抓取顺序
{
  switch(task)
  {
    //开始扫描
    case 'S':
    Uart_send_openmv('1'); 
    while(WL1_pose=="" || WL2_pose=="")
        Uart_recv_openmv();

    Serial.println("********** WLpose recved. ************");
    Serial.println(WL1_pose);
    Serial.println(WL2_pose);
    u8g2.drawStr(10,52,&uart_recv[0]);
    u8g2.sendBuffer();
    break;

   //停止扫描
    case 'E':
    Uart_send_openmv('2'); 
    break;
    case 'T':
      WL1_pose="321";
      WL2_pose="123";
      break;
    default : 
    break;
  }
  }

int Pad_Switch(char target)
{
  switch(target)
  {
    case '2':myservo_1.write(105);break;
    case '3':myservo_1.write(165);break;
    case '1':myservo_1.write(45);break;
    
  }
}


int Action_Order(int Phase,char target)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      if(WL1_pose[i]==target)
      {
        Serial.println(i+1);
        return i+1;
      }
    }
  }
  else
  {
    for(int i=0;i<3;i++)
    {
      if(WL2_pose[i]==target)
      {
        return i+1;
      }
    }
  }
  return -1;
}

void OG_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(Action_Order(Phase,QRcode[i]))
      {
        case 1:Pad_Switch(QRcode[i]);OG_Pick_Up_Left();break;
        case 2:Pad_Switch(QRcode[i]);OG_Pick_Up_Mid();break;
        case 3:Pad_Switch(QRcode[i]);OG_Pick_Up_Right();break;
        default:break;
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=4;i<7;i++)
    {
      switch(Action_Order(Phase,QRcode[i]))
      {
        case 1:Pad_Switch(QRcode[i]);OG_Pick_Down_Left();break;
        case 2:Pad_Switch(QRcode[i]);OG_Pick_Down_Mid();break;
        case 3:Pad_Switch(QRcode[i]);OG_Pick_Down_Right();break;
        default:break;
      }
    }
  }
}

void RM_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(QRcode[i])
      {
        case '1':RM_Place_Left();break;
        case '2':RM_Place_Mid();break;
        case '3':RM_Place_Right();break;
        default:break;
      }
    }
    for(int i=0;i<3;i++)
    {
      switch(QRcode[i])
      {
        case '1':RM_Pick_Left();break;
        case '2':RM_Pick_Mid();break;
        case '3':RM_Pick_Right();break;
        default:break;
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=4;i<7;i++)
    {
      switch(QRcode[i])
      {
        case '1':RM_Place_Left();break;
        case '2':RM_Place_Mid();break;
        case '3':RM_Place_Right();break;
        default:break;
      }
    }
    for(int i=4;i<7;i++)
    {
      switch(QRcode[i])
      {
        case '1':RM_Pick_Left();break;
        case '2':RM_Pick_Mid();break;
        case '3':RM_Pick_Right();break;
        default:break;
      }
    }
  }
}

void SM_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(QRcode[i])
      {
        case '1':SM_Place_Ground_Left();break;
        case '2':SM_Place_Ground_Mid();break;
        case '3':SM_Place_Ground_Right();break;
        default:break;
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=4;i<7;i++)
    {
      switch(QRcode[i])
      {
        case '1':SM_Place_Stack_Left();break;
        case '2':SM_Place_Stack_Mid();break;
        case '3':SM_Place_Stack_Right();break;
        default:break;
      }
    }
  }
}
