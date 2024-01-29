#ifndef	__SPI_H
#define	__SPI_H

#include "stm32f1xx.h"
#include "gpio.h"
#include "delay.h"

/*SPI Mode*/
#define SPI_Slave					0
#define SPI_Master				1

/*Data capture edge*/
#define SPI_ClockPhase_1st	0
#define SPI_ClockPhase_2nd	1

/*Clock idle polarity*/
#define SPI_Polarity_LOW		0
#define SPI_Polarity_HIGH		1

/*Master or slave mode*/
#define SPI_SlaveMode				0
#define SPI_MasterMode			1

/*Frame format*/
#define SPI_MSBFirst				0
#define SPI_LSBFirst				1

void SPI_EnableClock(SPI_TypeDef* SPIx);

void SPI_Init(SPI_TypeDef* SPIx, uint8_t SPI_Mode);
void SPI_IO_Init(SPI_TypeDef* SPIx);
void SPI_SetTransmitOnlyMode(void);
void SPI_SetClockPolarity(SPI_TypeDef* SPIx, uint8_t ClockPolarity);
void SPI_SetMasterSlave(SPI_TypeDef* SPIx, uint8_t Mode);
void SPI_SoftwareSlaveSelect_Enable(SPI_TypeDef* SPIx);
void SPI_SetFrameFormat(SPI_TypeDef* SPIx, uint8_t Format);

void SPI_Transmit(SPI_TypeDef* SPIx, uint8_t* data, uint8_t dataSize);
void SPI_Transmit_DMA(SPI_TypeDef* SPIx, uint8_t* data, uint8_t dataSize);
	
#define	SPI	((SPI1_Typedef*)SPI_BASE_1)
#endif	//__SPI_H
