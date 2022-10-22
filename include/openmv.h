#pragma once
#include <Arduino.h>
#include "SoftwareSerial.h"

void Get_message(HardwareSerial *p,char task);
void Get_message(SoftwareSerial *p,char task);