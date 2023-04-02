/*********************************************************************
 *  函数名称：uart_Init
 *  函数功能：8路灰度串口初始化
 *  形    参：无
 *  输    出：无
 *  备    注：无
 ********************************************************************/
//extern float z;
// void uart_Init2()
// {
//   Serial2.begin(9600);
//
// }
//
/*********************************************************************
 *  函数名称：Read_Data
 *  函数功能：读取数据
 *  形    参：*Data: 读取到的数据
 *  输    出：无
 *  备    注：无
 ********************************************************************/
void Read_Data2(unsigned int *Data) {
  unsigned char y = 0;
  unsigned char USART_RX_STA[3] = { 0 };  //数据缓存区
  unsigned char Num = 0;                  //数组计数
  unsigned int Receive_data = 0;          //数据缓存区

  Serial2.write(0x57);
  ///////////////////////////数字量数值///////////////////////////////

  for (y = 0; y <= 5; y++) {
    delay(1);
    if (Serial2.available() > 0) {
      USART_RX_STA[Num++] = Serial2.read();  //依次读取接收到的数据
      if (Num == 1) {
        Num = 0;
        *Data = USART_RX_STA[0];
        break;
      }
    }
  }
}

void track3() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data2(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0x00) {
    Read_Data2(Temp);
    switch (Temp[0]) {                    //8765 4321
      case 0xFE: zuoxuan(SSTEPS, HTSPEED); break;   //1111 1110
      case 0xFD: zuoxuan(SSTEPS, HTSPEED); break;   //1111 1101
      case 0xFB: zuoxuan(SSTEPS, HTSPEED); break;   //1111 1011
      case 0xF3: zuoxuan(SSTEPS, HTSPEED); break;   //1111 0011
      case 0xF7: backward(CSTEPS, HTSPEED); break;  //1111 0111

      case 0xE7: backward(CSTEPS, HTSPEED); break;  //1110 0111   //正中间的位置

      case 0xEF: backward(CSTEPS, HTSPEED); break;  //1110 1111
      case 0xDF: youxuan(SSTEPS, HTSPEED); break;   //1101 1111
      case 0xBF: youxuan(SSTEPS, HTSPEED); break;   //1011 1111
      case 0xCF: youxuan(SSTEPS, HTSPEED); break;   //1100 1111
      case 0x7F: youxuan(SSTEPS, HTSPEED); break;   //0111 1111
      case 0x00:; break;
      default: backward(CSTEPS, HTSPEED); break;
    }
  }
}

void track4() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data2(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0x00) {
    Read_Data2(Temp);
    switch (Temp[0]) {                   //8765 4321
      case 0xFE: left(SSTEPS, HTSPEED); break;     //1111 1110
      case 0xFD: left(SSTEPS, HTSPEED); break;     //1111 1101
      case 0xFB: left(SSTEPS, HTSPEED); break;     //1111 1011
      case 0xF3: left(SSTEPS, HTSPEED); break;     //1111 0011
      case 0xF7: forward(CSTEPS, HTSPEED); break;  //1111 0111

      case 0xE7: forward(CSTEPS, HTSPEED); break;  //1110 0111   //正中间的位置

      case 0xEF: forward(CSTEPS, HTSPEED); break;  //1110 1111
      case 0xDF: right(SSTEPS, HTSPEED); break;    //1101 1111
      case 0xBF: right(SSTEPS, HTSPEED); break;    //1011 1111
      case 0xCF: right(SSTEPS, HTSPEED); break;    //1100 1111
      case 0x7F: right(SSTEPS, HTSPEED); break;    //0111 1111
      case 0x00:; break;
      default: forward(CSTEPS, HTSPEED); break;
    }
  }
}


void track33() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data2(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0x00) {
    Read_Data2(Temp);
    switch (Temp[0]) {                    //8765 4321
      case 0xFE: zuoxuan(SSTEPS, HTSPEED); break;   //1111 1110
      case 0xFD: zuoxuan(SSTEPS, HTSPEED); break;   //1111 1101
      case 0xFB: zuoxuan(SSTEPS, HTSPEED); break;   //1111 1011
      case 0xF3: zuoxuan(SSTEPS, HTSPEED); break;   //1111 0011
      case 0xF7: backward(CSTEPS, HTSPEED); break;  //1111 0111

      case 0xE7: backward(CSTEPS, HTSPEED); break;  //1110 0111   //正中间的位置

      case 0xEF: backward(CSTEPS, HTSPEED); break;  //1110 1111
      case 0xDF: youxuan(SSTEPS, HTSPEED); break;   //1101 1111
      case 0xBF: youxuan(SSTEPS, HTSPEED); break;   //1011 1111
      case 0xCF: youxuan(SSTEPS, HTSPEED); break;   //1100 1111
      case 0x7F: youxuan(SSTEPS, HTSPEED); break;   //0111 1111
      case 0x00:; break;
      default: backward(CSTEPS, HTSPEED); break;
    }
  }
}

void trackL() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data2(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0xE7 && Temp[0] != 0xF7 && Temp[0] != 0xEF) {
    switch(HT_Status())
    {
      case 'R':youxuan(SSTEPS,HTSPEED);break;
      case 'L':zuoxuan(SSTEPS,HTSPEED);break;
      case 'O':left(SSTEPS,HTSPEED);break;
      case 'F':forward(SSTEPS,HTSPEED);break;
      case 'B':backward(SSTEPS,HTSPEED);break;
      default:break;
    }
    Read_Data2(Temp);
  }
}

void trackR() {
  unsigned int Temp[2] = { 0 };  //数据缓存区
  Read_Data2(Temp);
  //  Serial.println(Temp[0]);
  while (Temp[0] != 0xE7 && Temp[0] != 0xF7 && Temp[0] != 0xEF) {
    switch(HT_Status())
    {
      case 'R':youxuan(SSTEPS,HTSPEED);break;
      case 'L':zuoxuan(SSTEPS,HTSPEED);break;
      case 'O':right(SSTEPS,HTSPEED);break;
      case 'F':forward(SSTEPS,HTSPEED);break;
      case 'B':backward(SSTEPS,HTSPEED);break;
      default:break;
    }
    Read_Data2(Temp);
  }
}
