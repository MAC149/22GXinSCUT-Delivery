#pragma once
#include <Arduino.h>

void QR_Init(HardwareSerial *p);
String QR_Getstring(HardwareSerial *p);