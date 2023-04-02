////MPU6050 mpu6050(Wire);
//
//long timer = 0;
///*
//void setup() {
//  Serial.begin(9600);
//  Wire.begin();
//  mpu6050.begin();
//  mpu6050.calcGyroOffsets(true);
//}
//*/
//extern  float z;
//void gyro() {
//  mpu6050.update();
//
//  if(millis() - timer > 10){
//    
//    Serial.println("=======================================================");
///*    Serial.print("temp : ");Serial.println(mpu6050.getTemp());   //温度数据
//    Serial.print("accX : ");Serial.print(mpu6050.getAccX());     //角加速度
//    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
//    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
//  
//    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());  //角速度
//    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
//    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
//  
//    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());  //通过角加速度计算的偏移角度
//    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
//  
//    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX()); //通过角速度计算的偏移角度
//    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
//    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
// */   
// //   Serial.print("angleX : ");Serial.print(mpu6050.getAngleX()); //角度
// //   Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
//    Serial.print("angleZ : ");z = mpu6050.getAngleZ();
//    
//    //Serial.println(mpu6050.getAngleZ());
//    Serial.println(z);
//    timer = millis();
//    
//    
//  }
//   
//}
