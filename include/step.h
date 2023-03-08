#pragma once
#include"QRScanner.h"
#include"openmv.h"
#include "track.h"
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
void runtest();
void MotorTestDemo();
void step1();