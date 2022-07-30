#include"QRScanner.h"

void QR_Init(HardwareSerial *p)
{
  String qr_code = "";
  p->begin(9600);
}

String QR_Getstring(HardwareSerial *p)
{
  unsigned long starttime;
  String str = "";
  unsigned char Wakecmd[9] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x02, 0x01, 0xAB, 0xCD};
  p->write(Wakecmd, 9);
  //等待回收信号结束
  while (p->read() != 0x31);
  starttime = millis();
  while (true)
  {
    //扫码模块扫出来是会加换行符的
    str = p->readStringUntil('/r');
    if ((str.length() >= 1) || (millis() - starttime > 5000))
      break;
  }
  return str;
}