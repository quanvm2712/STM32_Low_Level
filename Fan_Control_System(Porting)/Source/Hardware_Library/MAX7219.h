#ifndef	__MAX7219_H
#define	__MAX7219_H

#include "stm32f1xx.h"
#include "string.h"
#include "GPIO.h"
#include "SPI.h"

#define CS_Set()		                GPIO_Reset(GPIO_A, 4)
#define CS_Reset()	                    GPIO_Set(GPIO_A, 4)

#define DIGIT_0_ONLY		            0
#define DIGIT_0_TO_1		            1
#define DIGIT_0_TO_2		            2
#define DIGIT_0_TO_3		            3
#define DIGIT_0_TO_4		            4
#define DIGIT_0_TO_5		            5
#define DIGIT_0_TO_6		            6
#define DIGIT_0_TO_7		            7

/*Decode mode*/
#define	DECODE_MODE_DISABLE				0x00
#define DECODE_MODE_DIGIT_0				0x01
#define DECODE_MODE_DIGIT_0_TO_3	    0x0F		
#define DECODE_MODE_DIGIT_0_TO_7	    0xFF

/*Digit position*/
#define	DIGIT_POSITION_0		        0
#define	DIGIT_POSITION_1		        1
#define	DIGIT_POSITION_2		        2
#define	DIGIT_POSITION_3		        3
#define	DIGIT_POSITION_4		        4
#define	DIGIT_POSITION_5		        5
#define	DIGIT_POSITION_6		        6
#define	DIGIT_POSITION_7		        7

void MAX7219_SendData(uint8_t address, uint8_t data);
void MAX7219_PowerOn(void);

void MAX7219_SetIntensity(uint8_t Intensity);
void MAX7219_SetScanLimit(uint8_t ScanLimit);
void MAX7219_Clean(void);
void MAX7219_SetDecodeMode(uint8_t DecodeMode);
void MAX7219_Init(uint8_t Intensity, uint8_t ScanLimit, uint8_t DecodeMode);
void MAX7219_PrintString(char* StringToPrint, uint8_t StartPosition);
void MAX7219_PrintInt(uint32_t IntToPrint, uint8_t NumOfDigits, uint8_t StartPosition);
#endif	//__MAX7219_H