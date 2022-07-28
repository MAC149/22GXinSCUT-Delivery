#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

void QR_Init(int RXP,int TXP);
String QR_Getstring(SoftwareSerial mySerial);