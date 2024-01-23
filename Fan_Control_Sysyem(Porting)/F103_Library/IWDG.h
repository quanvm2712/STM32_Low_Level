#ifndef	__IWDG_H
#define	__IWDG_H

#include "stm32f1xx.h"

#define	IWDG_DIV_4		0b000
#define	IWDG_DIV_8		0b001
#define	IWDG_DIV_16		0b010
#define	IWDG_DIV_32		0b011
#define	IWDG_DIV_64		0b100
#define	IWDG_DIV_128	0b101
#define	IWDG_DIV_256	0b110

void IWDG_SetPrescaler(uint8_t PrescalerValue);
void IWDG_SetReloadValue(uint16_t ReloadValue);
void IWDG_Start(void);
void IWDG_Reset(void);
void IWDG_Init(uint8_t PrescalerValue, uint16_t ReloadValue);

#endif	//__IWDG_H