#pragma once
#include <Arduino.h>
#include "SoftwareSerial.h"

void Serial_Init(HardwareSerial *p);
void Serial_Init(SoftwareSerial *p);
void Read_Data(HardwareSerial *p,unsigned int *Data);
void Read_Data(SoftwareSerial *p,unsigned int *Data);