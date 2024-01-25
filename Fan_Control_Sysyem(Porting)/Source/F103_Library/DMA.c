/**
 * @file DMA.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief DMA Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-01-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "DMA.h"

/**
 * @brief Enable clock for DMA peripheral (Since STM32 only have 1 DMA controller, DMA1 should be selected)
 * 
 * @param DMA_Instance Target DMA channel
 * 	@arg DMA1
 */
void DMA_EnableClock(DMA_TypeDef* DMA_Instance){
	if(DMA_Instance == DMA1){
		RCC->AHBENR |= (1 << 0);
	}
	else{
		RCC->AHBENR |= (1 << 1);
	}
}

/**
 * @brief Load address of peripheral's register for data transferring
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param PeripheralAddress Address of peripheral register
 */
void DMA_SetPeripheralAddress(DMA_Channel_TypeDef* DMA_Channel, uint32_t PeripheralAddress){
	DMA_Channel->CPAR = PeripheralAddress;
}

/**
 * @brief Load address of memory region used for data transferring
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param MemoryAddress Address of memory region used for data transferring
 */
void DMA_SetMemoryAddress(DMA_Channel_TypeDef* DMA_Channel, uint32_t MemoryAddress){
	DMA_Channel->CMAR = MemoryAddress;	
}

/**
 * @brief Set number of data (in bytes) that will be transferred
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param NumberOfData Number of bytes which will be transferred
 */
void DMA_SetNumberOfData(DMA_Channel_TypeDef* DMA_Channel, uint16_t NumberOfData){
	//Only write when DMA channel is disabled
	if(!(DMA_Channel->CCR & (1 << 0))){
		DMA_Channel->CNDTR = NumberOfData;
	}
}

/**
 * @brief Set DMA channel priority
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param Priority DMA Channel priority
 * 	@arg DMA_PRIORITY_LOW
 * 	@arg DMA_PRIORITY_MEDIUM
 * 	@arg DMA_PRIORITY_HIGH
 * 	@arg DMA_PRIORITY_VERY HIGH
 */
void DMA_SetChannelPriority(DMA_Channel_TypeDef* DMA_Channel, uint8_t Priority){
	DMA_Channel->CCR &= ~(0b11 << 12); //Reset bits
	DMA_Channel->CCR |= (Priority << 12);
}

/**
 * @brief Configure direction of DMA channel (MEMORY-PERIPHERAL or PERIPHERAL-MEMORY)
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param Direction Data transferring direction
 * 	@arg DMA_PeripheralToMemory
 * 	@arg DMA_MemoryToPeripheral
 */
void DMA_SetDirection(DMA_Channel_TypeDef* DMA_Channel, uint8_t Direction){
	DMA_Channel->CCR &= ~(1 << 4);  //Reset bit
	DMA_Channel->CCR |= (Direction << 4);
}

/**
 * @brief Enable or disable DMA Circular Mode 
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param isEnabled Circular mode on or off
 * 	@arg DMA_CIRCULARMODE_DISABLE
 * 	@arg DMA_CIRCULARMODE_ENABLE
 */
void DMA_SetCircularMode(DMA_Channel_TypeDef* DMA_Channel, _Bool isEnabled){
	DMA_Channel->CCR &= ~(1 << 5);	//Reset bit
	DMA_Channel->CCR |= (isEnabled << 5);
}

/**
 * @brief Configure Incremented mode for memory or peripheral
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param source Target to be configured
 * 	@arg DMA_SOURCE_PERIPHERAL
 * 	@arg DMA_SOURCE_MEMORY
 * @param isEnabled Enable or disable
 * 	@arg DMA_INCREMENTED_DISABLE
 * 	@arg DMA_INCREMENTED_ENABLE
 */
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

/**
 * @brief Configure size of memory address
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param MemSize Size of memory address
 */
void DMA_SetMemorySize(DMA_Channel_TypeDef* DMA_Channel, uint8_t MemSize){
	DMA_Channel->CCR &= ~(0b11 << 10);  //Reset bits
	DMA_Channel->CCR |= (MemSize << 10);
}

/**
 * @brief Configure size of peripheral's register
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param PeripheralSize Size of peripheral register
 */
void DMA_SetPeripheralSize(DMA_Channel_TypeDef* DMA_Channel, uint8_t PeripheralSize){
	DMA_Channel->CCR &= ~(0b11 << 8);  //Reset bits
	DMA_Channel->CCR |= (PeripheralSize << 8);
}

/**
 * @brief Initialize DMA for data transferring (By default incremented mode is enabled on memory address and disabled on peripheral register)
 * 
 * @param DMAx DMA_Instance
 * 	@arg DMA1
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param Direction Data transferring direction
 * 	@arg DMA_PeripheralToMemory
 * 	@arg DMA_MemoryToPeripheral
 * @param Priority DMA Channel priority
 * 	@arg DMA_PRIORITY_LOW
 * 	@arg DMA_PRIORITY_MEDIUM
 * 	@arg DMA_PRIORITY_HIGH
 * 	@arg DMA_PRIORITY_VERY HIGH
 * @param CircularMode Circular mode on or off
 * 	@arg DMA_CIRCULARMODE_DISABLE
 * 	@arg DMA_CIRCULARMODE_ENABLE
 */
void DMA_Init(DMA_TypeDef* DMAx, DMA_Channel_TypeDef* DMA_Channel, uint8_t Direction, uint8_t Priority, _Bool CircularMode){
	DMA_EnableClock(DMAx);
	
	DMA_SetChannelPriority(DMA1_Channel3, Priority);
	DMA_SetDirection(DMA1_Channel3, Direction);
	
	DMA_SetIncrementedMode(DMA1_Channel3, DMA_SOURCE_MEMORY, DMA_INCREMENTED_ENABLE);
	DMA_SetIncrementedMode(DMA1_Channel3, DMA_SOURCE_PERIPHERAL, DMA_INCREMENTED_DISABLE);

	DMA_SetCircularMode(DMA1_Channel3, CircularMode);		
}

/**
 * @brief Configure information about source, destination and size of data to be transferred
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 * @param memoryAddress Address of memory region used for data transferring
 * @param peripheralAddress Address of peripheral register 
 * @param size Number of bytes which will be transferred
 */
void DMA_SetTransactionInfo(DMA_Channel_TypeDef* DMA_Channel, uint32_t memoryAddress, uint32_t peripheralAddress, uint16_t size){
	DMA_SetMemoryAddress(DMA_Channel, memoryAddress);
	DMA_SetPeripheralAddress(DMA_Channel, peripheralAddress);
	DMA_SetNumberOfData(DMA_Channel, size);

	DMA_Enable(DMA_Channel);	
}

/**
 * @brief Enable selected DMA channel
 * 
 * @param DMA_Channel DMA channel which includes the peripheral
 * 	@arg DMA1_Channel1
 * 	@arg DMA1_Channel2
 * 	@arg DMA1_Channel3
 * 	@arg DMA1_Channel4
 * 	@arg DMA1_Channel5
 * 	@arg DMA1_Channel6
 * 	@arg DMA1_Channel7
 */
void DMA_Enable(DMA_Channel_TypeDef* DMA_Channel){
	DMA_Channel->CCR |= (1 << 0);
}

