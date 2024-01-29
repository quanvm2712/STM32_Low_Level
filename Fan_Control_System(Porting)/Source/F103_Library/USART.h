#ifndef __USART_H
#define __USART_H

#include "stm32f1xx.h"
#include "GPIO.h"

/*Number of stop bits */
#define USART_1_STOP_BIT            0
#define USART_HALF_STOP_BITS        1
#define USART_2_STOP_BITS           2
#define USART_1ANDHALF_STOP_BIT     3

/*Word length */
#define UASRT_8_DATA_BITS           0
#define UASRT_9_DATA_BITS           1


/*USART Baudrate */
#define USART_BAUDRATE_9600         0
#define USART_BAUDRATE_19200        1
#define USART_BAUDRATE_57600        2
#define USART_BAUDRATE_115200       3


void USART_Init(USART_TypeDef* USARTx, _Bool WordLength, uint8_t NumberOfStopBits, uint8_t DesiredBaudrate);
void USART_TransmitData(USART_TypeDef* USARTx, uint8_t* Data, uint16_t DataSize);

#endif //__USART_H