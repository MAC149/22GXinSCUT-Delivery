#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
//#include <MPU6050_tockn.h>
#include <U8g2lib.h>
#include <Servo.h>
#include <SPI.h>
//#include <LobotServoController.h>
//  LobotServoController myse;  
Servo myservo_1;
Servo myservo_2;
//  MPU6050 mpu6050(Wire);
//  

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 3, /* reset=*/ U8X8_PIN_NONE);


//////电机接口定义///////
#define A_En 52   //使能   A左前 B右前 C右后 D左后
#define A_Stp 50  //脉冲
#define A_Dir 48  //方向
#define B_En 46
#define B_Stp 44
#define B_Dir 42
#define C_En 34
#define C_Stp 32
#define C_Dir 30
#define D_En 40
#define D_Stp 38
#define D_Dir 36
//
#define lift_En  47     //上方电机，升降
#define lift_Stp 45
#define lift_Dir 43
#define rotation_En  53   //下方电机，旋转
#define rotation_Stp 51
#define rotation_Dir 49

float z;//陀螺仪

////左右两侧灰度///
//左侧灰度传感器31(L2) 29(L1) 27(M) 25(R1) 23(R2)
#define left_L2 31   
#define left_L1 29
#define left_M 27
#define left_R1 25
#define left_R2 23
int L1 = digitalRead(31);
int L2 = digitalRead(29);
int L3 = digitalRead(27);
int L4 = digitalRead(25);
int L5 = digitalRead(23);
//右侧灰度传感器41(L2) 39(L1) 37(M) 35(R1)  33(R2)
#define right_L2 41  
#define right_L1 39
#define right_M 37
#define right_R1 35
#define right_R2 33
int R1 = digitalRead(41);
int R2 = digitalRead(39);
int R3 = digitalRead(37);
int R4 = digitalRead(35);
int R5 = digitalRead(33);

//限位器
#define up_xianweiqi A2
#define down_xianweiqi A1
int k = digitalRead(A2);//上方限位器
int h = digitalRead(A1);//上方限位器



int x= 80; //速度
String QRcode="";
int tt=0;
SoftwareSerial mySerial(11, 10); // RX, TX



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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // 设置波特率
  Serial1.begin(9600); // 与OpenMV通信,UART2:对应引脚RX(17)---P4(TX),TX(16)---P5(RX)

  mySerial.begin(9600);

    uart_Init();//8路灰度串口初始化
   
    motor(); //引脚端口初始化
    
//左右两侧灰度
pinMode(left_L2,INPUT);   //左侧灰度传感器31(L2) 29(L1) 27(M) 25(R1) 23(R2)
pinMode(left_L1,INPUT); 
pinMode(left_M,INPUT); 
pinMode(left_R1,INPUT);
pinMode(left_R2,INPUT);  
pinMode(right_L2,INPUT);   //右侧灰度传感器41(L2) 39(L1) 37(M) 35(R1)  33(R2)
pinMode(right_L1,INPUT); 
pinMode(right_M,INPUT); 
pinMode(right_R1,INPUT);
pinMode(right_R2,INPUT);  
  //oled初始化
 u8g2.begin();
  u8g2.clearBuffer(); //清除模组的缓存
  //陀螺仪初始化
//  Serial.begin(9600);//初始化串口，设置波特率为9600
  Wire.begin();//初始化IIC总线
//  mpu6050.begin();//初始化MPU6050
//  mpu6050.calcGyroOffsets(true);//开启角速度偏移计算

  pinMode(up_xianweiqi,INPUT);//上方限位器，A2
  pinMode(down_xianweiqi,INPUT);//下方限位器，A1

  myservo_1.attach(A0); //物料盘
  myservo_2.attach(A3); //机械爪
}


void loop() { 

  // put your main code here, to run repeatedly:
 //1、离开出发区,前往扫码 step01(); 
   zuoqian(12000,100);
   backward(1200,x);
   track2();

   while(QRcode=="")                    //扫码,获取颜色顺序
   {
     QRcode=QR_Getstring();
   }
   u8g2.setFont(u8g2_font_osr18_tf);
   u8g2.drawStr(10,44,&QRcode[0]);
   u8g2.sendBuffer();
 
//2、前往原料区（上层） step02();
 zuoqian(8000,100);
 backward(1500,x);
  track2();
 forward(800,x);
  track2();  
 forward(800,x);
  track2(); 
 forward(1500,x);//前进半格
 Get_message('S'); //扫描物料颜色，openmv
 youxuan(4000,100);//4100转过九十度
   track2(); 
 
 //扫描物料颜色
 
  forward(800,x);
    track2(); //循线到物料架中间
    OG_Action(1);
//    
//myservo_1.write(45);delay(100);
//  wuliao_left_shang();//左移，前进，夹取上层左边物料
//   myservo_1.write(105);delay(100);
//  wuliao_middle_shang();//前进，夹取中间左边物料
// myservo_1.write(165);
//  wuliao_right_shang();//右移，前进，夹取上层右边物料
// 

//3、前往粗加工区
 track3();
 backward(800,x);
  track3();
  backward(800,x);
  track3();
  backward(1500,x);
  zuoxuan(4000,100);
  track2();
  
//放物料
//cu_left();
//cu_middle();
//cu_right();
//cu_left2();
//cu_middle2();
//cu_right2();

RM_Action(1);

//4、前往半成品区
  track3();
  backward(800,x);
  track3();
  backward(800,x);
  track3();
   backward(1500,x);
   zuoxuan(4000,100);
  track2();
   forward(800,x);
    track2();
    track4();
//ban_left();
//ban_middle();
//ban_right();
SM_Action(1);


//5、返回原料区
backward(1500,x);
youxuan(4100,100);
track2();
forward(800,x);
track2();
forward(800,x);
youxuan(4100,100);
backward(700,x);
// left(7800,150);
//zuoqian(8000,x);
//zuoqian(8000,x);
//zuoqian(2000,x);
//backward(1400,x);
track2();
 forward(800,x);
    track6();
     forward(800,x);
    track6();
 forward(800,x);
    track6();
     forward(800,x);
    track2();
//夹取物料
OG_Action(2);
// myservo_1.write(45);delay(100);
//  wuliao_left_down();//左移，前进，夹取上层左边物料
//   myservo_1.write(105);delay(100);
//  wuliao_middle_down();//前进，夹取中间左边物料
// myservo_1.write(165);
//  wuliao_right_down();//右移，前进，夹取上层右边物料



//6、前往粗加工区
  track3();
 backward(800,x);
  track3();
  backward(800,x);
  track3();
  backward(1500,x);
  zuoxuan(4000,100);
  track2();

//放物料
//cu_left();
//cu_middle();
//cu_right();
//cu_left2();
//cu_middle2();
//cu_right2();
 RM_Action(2);

//7、前往半成品区
  track3();
  backward(800,x);
  track3();
  backward(800,x);
  track3();
   backward(1500,x);
   zuoxuan(4000,100);
  track2();
   forward(800,x);
    track2();
    track4();
//ban_left2();
//ban_middle2();
//ban_right2();
SM_Action(2);

//8、前往返回区
backward(1500,x);
youxuan(4000,100);
track3();
backward(800,x);
track3();
backward(800,x);
track3();

backward(2600,x);
left(6520,x);

while(1);

}
