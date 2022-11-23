#pragma once
#include<Arduino.h>

// Basic demo for accelerometer readings from Adafruit MPU6050

#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define INTERRUPT_PIN 2

void mpu_Init();
double mpu6050();