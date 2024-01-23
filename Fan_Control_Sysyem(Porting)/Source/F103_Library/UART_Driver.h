#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

#include "stm32f1xx.h"  
#include "gp_drive.h" 

void UART_init();
void USART2_ReceiveString(char *buffer, int length);
char USART2_ReceiveChar(void);
void USART2_SendChar(char ch);
void UART_SendString(char str[]);

#endif  //__UART_DRIVER_H