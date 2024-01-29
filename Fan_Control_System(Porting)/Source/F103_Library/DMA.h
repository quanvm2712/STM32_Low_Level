#ifndef	__DMA_H
#define __DMA_H

#include "stm32f1xx.h"

/*DMA priority level*/
#define DMA_PRIORITY_LOW					0
#define DMA_PRIORITY_MEDIUM				1
#define DMA_PRIORITY_HIGH					2
#define DMA_PRIORITY_VERYHIGH			3

/*DMA Direction*/
#define DMA_PeripheralToMemory		0
#define DMA_MemoryToPeripheral		1

/*DMA circular mode*/
#define DMA_CIRCULARMODE_DISABLE	0
#define DMA_CIRCULARMODE_ENABLE		1

/*DMA Memory Source*/
#define	DMA_SOURCE_PERIPHERAL			0	
#define	DMA_SOURCE_MEMORY					1

/*DMA incremented mode*/
#define DMA_INCREMENTED_DISABLE		0
#define DMA_INCREMENTED_ENABLE		1

/*DMA Size*/
#define	DMA_8_BITS								0
#define	DMA_16_BITS								1
#define	DMA_32_BITS								2

void DMA_EnableClock(DMA_TypeDef* DMA_Instance);

void DMA_SetPeripheralAddress(DMA_Channel_TypeDef* DMA_Channel, uint32_t PeripheralAddress);
void DMA_SetMemoryAddress(DMA_Channel_TypeDef* DMA_Channel, uint32_t MemoryAddress);
void DMA_SetNumberOfData(DMA_Channel_TypeDef* DMA_Channel, uint16_t NumberOfData);
void DMA_SetChannelPriority(DMA_Channel_TypeDef* DMA_Channel, uint8_t Priority);
void DMA_SetDirection(DMA_Channel_TypeDef* DMA_Channel, uint8_t Direction);
void DMA_SetCircularMode(DMA_Channel_TypeDef* DMA_Channel, _Bool isEnabled);
void DMA_SetIncrementedMode(DMA_Channel_TypeDef* DMA_Channel, _Bool source, _Bool isEnabled);
void DMA_SetMemorySize(DMA_Channel_TypeDef* DMA_Channel, uint8_t MemSize);
void DMA_SetPeripheralSize(DMA_Channel_TypeDef* DMA_Channel, uint8_t PeripheralSize);
void DMA_Enable(DMA_Channel_TypeDef* DMA_Channel);

void DMA_Init(DMA_TypeDef* DMAx, DMA_Channel_TypeDef* DMA_Channel, uint8_t Direction, uint8_t Priority, _Bool CircularMode);
void DMA_SetTransactionInfo(DMA_Channel_TypeDef* DMA_Channel, uint32_t memoryAddress, uint32_t peripheralAddress, uint16_t size);


#endif	//_DMA_H