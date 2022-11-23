#include"step.h"
#define SPEED 200
Motortot Mtot1(52,50,48,46,44,42,40,38,36,34,32,30);//AEn,Astp,Adir,Bstp,BEn,Bdir,CEn,Cstp,Cdir,DEn,Dstp,Ddir
Motor MotRot(53,51,49);
Motor MotLift(47,45,43);
Servo Servo_Pad;
Servo Servo_Paw;
int LeftHT[5]={31,29,27,25,23};//L2 L1 M R1 R2
int RightHT[5]={41,39,37,35,33};

String QRCode="";
extern SoftwareSerial qrcode;
enum Dirc{F=1,B,L,R};



U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 3, /* reset=*/ U8X8_PIN_NONE);




void MotorTestDemo()
{
  /* Mtot1.Motortot_ForwardR(200,2);
  delay(2000);
  Mtot1.Motortot_BackwardR(200,2);
  delay(2000);
  Mtot1.Motortot_LeftR(200,2);
  delay(2000);
  Mtot1.Motortot_RightR(200,2);
  delay(2000);
  Mtot1.Motortot_RotLeft(200);
  Mtot1.Motortot_Reset();
  delay(2000);
  Mtot1.Motortot_RotRight(200);
  Mtot1.Motortot_Reset();
  delay(2000);  */
  MotRot.Motor_En(1);
  MotLift.Motor_En(1);
  LiftReset();
  RotReset();
  //MotRot.Motor_round(SPEED,1,0);
  // MotLift.Motor_round(SPEED,1,0);
}

/* void runtest()
{   
  Mtot1.Motortot_ForwardTime(SPEED,3200);//向前一步
  delay(100);
  Mtot1.Motortot_LeftTime(SPEED,6400);//向左到第二格
  delay(100);
  FindMid_Left(200);//左巡线
  delay(100);
  NGoline(2,SPEED);//前走2线
  //QRcode
  NGoline(3,SPEED);//前走三线
  //openmv
  Mtot1.Motortot_RightTime(SPEED,3200);
  FindMid_Right(SPEED);
  //servo
  Mtot1.Motortot_RotLeft(SPEED);
  FindMid_Right(SPEED);
  NGoline(3,SPEED);
  //servo
  NGoline(2,SPEED);
  Mtot1.Motortot_RotLeft(SPEED);
  FindMid_Right(SPEED);
  NGoline(2,SPEED);
  //servo
  Mtot1.Motortot_RotLeft(SPEED);
  NGoline(5,SPEED);
  Mtot1.Motortot_RotLeft(SPEED);
  Find_RightEdge(SPEED);
  
    
    
    
} */



void step1()
{
  Mtot1.Motortot_ForLeftTime(SPEED, 12000);
  Mtot1.Motortot_BackwardTime(SPEED, 1300);
  mpuadjust(0);
  Find_Mid();

  while (QRCode == "")                 //扫码
  {
    QRCode = QR_Getstring(&qrcode);
  }
  u8g2.setFont(u8g2_font_inr16_mf);
  u8g2.drawStr(0, 32, &QRCode[0]);
  u8g2.sendBuffer();



  //2、前往原料区（上层） step02();
  Mtot1.Motortot_ForLeftTime(SPEED, 8000);
  Mtot1.Motortot_BackwardTime(SPEED, 1500);
  Follow();
  Mtot1.Motortot_ForwardTime(SPEED, 400);
  Follow();
  Mtot1.Motortot_ForwardTime(SPEED, 400);
  Follow();
  Mtot1.Motortot_ForwardTime(SPEED, 1500); //前进半格
  Mtot1.Motortot_RotRight(SPEED); //4100转过九十度
  Follow();
  delay(2000);//扫描物料颜色
  //Get_message('S');
  Mtot1.Motortot_ForwardTime(SPEED, 200);
  Follow(); //循线到物料架中间
/*   wuliao_left_shang();//左移，前进，夹取上层左边物料
  wuliao_middle_shang();//前进，夹取中间左边物料
  wuliao_right_shang();//右移，前进，夹取上层右边物料 */
  while (1);
}