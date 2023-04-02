#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define INTERRUPT_PIN 2
MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t fifoBuffer[64]; // FIFO storage buffer
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
Quaternion q; 
VectorFloat gravity;  
float ypr[3];  
volatile bool mpuInterrupt = false;
void dmpDataReady() {
    mpuInterrupt = true;
}
void mpuinit()
{
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);
    devStatus = mpu.dmpInitialize();
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1888); // 1688 factory default for my test chip
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
}

double mpu6050(){
  if (!dmpReady) return;
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { 
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
  } 
  return ypr[0] * 180/M_PI;
}

void mputest()
{
  while(1)
  {
    mpu6050();
  }
}
void adjust_angle(double jz){
  double i[5];
  if(jz == 180.0){
    i[0] = -jz;
  }
  else{
    i[0] = jz;
  }
  if(jz == -180.0){
    i[1] = -jz;
  }
  else{
    i[1] = jz;
  }
  if(jz == 180 || jz == -180){
    while(1){
      i[2] = (mpu6050() + mpu6050()+ mpu6050()) / 3.0;
      if((i[2] > i[0] + 0.5)&&(i[2] < 0)){
        zuoxuan(50, 50);
      }
      else if((i[2] < i[1] - 0.5)&&(i[2] >= 0)){
        youxuan(50, 50);
      }
      else
        break;
    }
  }
  else{
    while(1){
    i[2] = (mpu6050() + mpu6050()+ mpu6050()) / 3.0;
    if(i[2] > i[0] + 0.5){
      zuoxuan(50, 50);
      //u8g2.drawStr(0,40,ecvt()
    }
    else if(i[2]< i[1] - 0.5){
      youxuan(50, 50);
    }
    else
      break;
    }
  } 
}


