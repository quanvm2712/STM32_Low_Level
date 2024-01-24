#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f1xx.h"
#include "stdbool.h"

//GPIO Port 
#define AFIOEN		        0
#define	GPIO_A		        2
#define	GPIO_B		        3
#define	GPIO_C		        4
#define	GPIO_D		        5
#define	GPIO_E		        6


//IO mode
#define	GPIO_OUTPUT		    0
#define GPIO_INPUT		    1
#define AFIO_OUTPUT		    2

//PULL UP/DOWN
#define	GPIO_PIN_PULLDOWN	0
#define GPIO_PIN_PULLUP	    1



void GPIO_EnableClock(uint8_t GPIO_Port);

//User function
void GPIO_Init(uint8_t GPIO_Port, uint8_t GPIO_Pin, uint8_t mode);
void GPIO_Set(uint8_t GPIO_Port, uint8_t GPIO_Pin);
void GPIO_Reset(uint8_t GPIO_Port, uint8_t GPIO_Pin);
void GPIO_Toggle(uint8_t GPIO_Port, uint8_t GPIO_Pin);
void GPIO_PullUpDown(uint8_t GPIO_Port,uint8_t GPIO_Pin, bool pullMode);
uint8_t GPIO_ReadPin(uint8_t GPIO_Port, uint8_t GPIO_Pin);

#endif //__GPIO_H