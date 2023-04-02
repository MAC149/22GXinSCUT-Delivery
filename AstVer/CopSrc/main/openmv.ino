
String WL1_pose;    // 上层物料放置位置
String WL2_pose;    // 下层物料放置位置
//1--红 2--绿 3--蓝
//半成品,粗加工固定顺序--蓝红绿312
char uart_recv[64]="a";     // 串口缓存数据

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
     u8g2.drawStr(10,60,&uart_recv[0]);
     u8g2.sendBuffer();
    break;

   //停止扫描
    case 'E':
    Uart_send_openmv('2'); 
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
        case 1:Pad_Switch(QRcode[i]);wuliao_left_shang();break;
        case 2:Pad_Switch(QRcode[i]);wuliao_middle_shang();break;
        case 3:Pad_Switch(QRcode[i]);wuliao_right_shang();break;
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
        case 1:Pad_Switch(QRcode[i]);wuliao_left_down();break;
        case 2:Pad_Switch(QRcode[i]);wuliao_middle_down();break;
        case 3:Pad_Switch(QRcode[i]);wuliao_right_down();break;
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
        case '1':cu_left();break;
        case '2':cu_middle();break;
        case '3':cu_right();break;
        default:break;
      }
    }
    for(int i=0;i<3;i++)
    {
      switch(QRcode[i])
      {
        case '1':cu_left2();break;
        case '2':cu_middle2();break;
        case '3':cu_right2();break;
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
        case '1':cu_left();break;
        case '2':cu_middle();break;
        case '3':cu_right();break;
        default:break;
      }
    }
    for(int i=4;i<7;i++)
    {
      switch(QRcode[i])
      {
        case '1':cu_left2();break;
        case '2':cu_middle2();break;
        case '3':cu_right2();break;
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
        case '1':ban_left();break;
        case '2':ban_middle();break;
        case '3':ban_right();break;
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
        case '1':ban_left2();break;
        case '2':ban_middle2();break;
        case '3':ban_right2();break;
        default:break;
      }
    }
  }
}
