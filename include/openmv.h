#pragma once
#include <Arduino.h>

void Uart_send_openmv(char CMD) ;

void Uart_recv_openmv();

void Get_message(char task);