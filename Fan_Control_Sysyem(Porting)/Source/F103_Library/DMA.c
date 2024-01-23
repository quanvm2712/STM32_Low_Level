#include "DMA.h"

void DMA_EnableClock(DMA_TypeDef* DMA_Instance){
	if(DMA_Instance == DMA1){
		RCC->AHBENR |= (1 << 0);
	}
	else{
		RCC->AHBENR |= (1 << 1);
	}
}

void DMA_SetPeripheralAddress(DMA_Channel_TypeDef* DMA_Channel, uint32_t PeripheralAddress){
	DMA_Channel->CPAR = PeripheralAddress;
}

void DMA_SetMemoryAddress(DMA_Channel_TypeDef* DMA_Channel, uint32_t MemoryAddress){
	DMA_Channel->CMAR = MemoryAddress;	
}

void DMA_SetNumberOfData(DMA_Channel_TypeDef* DMA_Channel, uint16_t NumberOfData){
	//Only write when DMA channel is disabled
	if(!(DMA_Channel->CCR & (1 << 0))){
		DMA_Channel->CNDTR = NumberOfData;
	}
}

void DMA_SetChannelPriority(DMA_Channel_TypeDef* DMA_Channel, uint8_t Priority){
	DMA_Channel->CCR &= ~(0b11 << 12); //Reset bits
	DMA_Channel->CCR |= (Priority << 12);
}

void DMA_SetDirection(DMA_Channel_TypeDef* DMA_Channel, uint8_t Direction){
	DMA_Channel->CCR &= ~(1 << 4);  //Reset bit
	DMA_Channel->CCR |= (Direction << 4);
}

void DMA_SetCircularMode(DMA_Channel_TypeDef* DMA_Channel, _Bool isEnabled){
	DMA_Channel->CCR &= ~(1 << 5);	//Reset bit
	DMA_Channel->CCR |= (isEnabled << 5);
}

void DMA_SetIncrementedMode(DMA_Channel_TypeDef* DMA_Channel, _Bool source, _Bool isEnabled){
	if(source == DMA_SOURCE_MEMORY){
		DMA_Channel->CCR &= ~(1 << 7);  //Reset bit
		DMA_Channel->CCR |= (isEnabled << 7);
	}
	else{
		DMA_Channel->CCR &= ~(1 << 6);  //Reset bit
		DMA_Channel->CCR |= (isEnabled << 6);		
	}
}

void DMA_SetMemorySize(DMA_Channel_TypeDef* DMA_Channel, uint8_t MemSize){
	DMA_Channel->CCR &= ~(0b11 << 10);  //Reset bits
	DMA_Channel->CCR |= (MemSize << 10);
}

void DMA_SetPeripheralSize(DMA_Channel_TypeDef* DMA_Channel, uint8_t PeripheralSize){
	DMA_Channel->CCR &= ~(0b11 << 8);  //Reset bits
	DMA_Channel->CCR |= (PeripheralSize << 8);
}

void DMA_Init(DMA_TypeDef* DMAx, DMA_Channel_TypeDef* DMA_Channel, uint8_t Direction, uint8_t Priority, _Bool CircularMode){
	DMA_EnableClock(DMAx);
	
	DMA_SetChannelPriority(DMA1_Channel3, Priority);
	DMA_SetDirection(DMA1_Channel3, Direction);
	
	DMA_SetIncrementedMode(DMA1_Channel3, DMA_SOURCE_MEMORY, DMA_INCREMENTED_ENABLE);
	DMA_SetIncrementedMode(DMA1_Channel3, DMA_SOURCE_PERIPHERAL, DMA_INCREMENTED_DISABLE);

	DMA_SetCircularMode(DMA1_Channel3, CircularMode);		
}


void DMA_SetTransactionInfo(DMA_Channel_TypeDef* DMA_Channel, uint32_t memoryAddress, uint32_t peripheralAddress, uint16_t size){
	DMA_SetMemoryAddress(DMA_Channel, memoryAddress);
	DMA_SetPeripheralAddress(DMA_Channel, peripheralAddress);
	DMA_SetNumberOfData(DMA_Channel, size);

	DMA_Enable(DMA_Channel);	
}

void DMA_Enable(DMA_Channel_TypeDef* DMA_Channel){
	DMA_Channel->CCR |= (1 << 0);
}

