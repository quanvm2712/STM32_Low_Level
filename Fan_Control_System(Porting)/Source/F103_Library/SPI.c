/**
 * @file SPI.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief SPI Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-01-25
 * 
 */
#include "SPI.h"
#include "DMA.h"

/**
 * @brief Enable clock for selected SPI instance
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 */
void SPI_EnableClock(SPI_TypeDef* SPIx){
	if (SPIx == SPI1)	{
		RCC->APB2ENR |= (1 << 12);
	}
	else if (SPIx == SPI2){
		RCC->APB1ENR |= (1 << 14);
	}
}

/**
 * @brief Configure SPI clock line's edge to be used for data sampling
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 * @param ClockPhase Edge used for data sampling
 * 	@arg SPI_ClockPhase_1st
 * 	@arg SPI_ClockPhase_2nd
 */
void SPI_SetClockPhase(SPI_TypeDef* SPIx,uint8_t ClockPhase){
	SPIx->CR1 &= ~(0b1 << 0);
	SPIx->CR1 |= (ClockPhase << 0);
}

/**
 * @brief Configure SPI clock's logic level at idle state
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 * @param ClockPolarity Logic level at idle state
 * 	@arg SPI_Polarity_LOW
 * 	@arg SPI_Polarity_HIGH
 */
void SPI_SetClockPolarity(SPI_TypeDef* SPIx, uint8_t ClockPolarity){
	SPIx->CR1 &= ~(0b1 << 1);
	SPIx->CR1 |= (ClockPolarity << 1);
}

/**
 * @brief Configure selected SPI as slave or master
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 * @param Mode Master or slave mode
 * 	@arg SPI_SlaveMode
 * 	@arg SPI_MasterMode
 */
void SPI_SetMasterSlave(SPI_TypeDef* SPIx, uint8_t Mode){
	SPIx->CR1 &= ~(0b1 << 2);
	SPIx->CR1 |= (Mode << 2);
}

/**
 * @brief Configure selected SPI instance with 9Mb/s baudrate
 * 
 * @param SPIx SPI Instance
 * 	@arg SPI1
 * 	@arg SPI2
 */
void SPI_SetSourceClock(SPI_TypeDef* SPIx){
	//9Mb/s	Baudrate
	if(SPIx == SPI1){
		SPIx->CR1 |= (0b010 << 3);
	}
	else if(SPIx == SPI2){
		SPIx->CR1 |= (0b001 << 3);
	}
}

/**
 * @brief Enable selected SPI instance
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 */
void SPI_Enable(SPI_TypeDef* SPIx){
	SPIx->CR1 |= (1 << 6);
}

/**
 * @brief Disable selected SPI instance
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 */
void SPI_Disable(SPI_TypeDef* SPIx){
	while(!(SPIx->SR & (1 << 1))); //Wait for TXE to set
	while(SPIx->SR & (1 << 7)); //Wait until communication to be completed
	
	SPIx->CR1 &= ~(1 << 6);
}

/**
 * @brief Enable software slave select for target SPI instance
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 */
void SPI_SoftwareSlaveSelect_Enable(SPI_TypeDef* SPIx){
	SPIx->CR1 &= ~(0b1 << 9);
	SPIx->CR1 |= (1 << 9); 
	SPIx->CR1 |= (1 << 8);
}

/**
 * @brief Configure data format for SPI data transfer
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 * @param Format MSBFirst or LSBFirst
 * 	@arg SPI_MSBFirst
 * 	@arg SPI_LSBFirst
 */
void SPI_SetFrameFormat(SPI_TypeDef* SPIx, uint8_t Format){
	SPIx->CR1 &= ~(0b1 << 7);
	SPIx->CR1 |= (Format << 7);
}


/**
 * @brief Inititalize selected SPI instance. By default, SPI is configured to be low polarity, 
 * 		  1st-clock phase capture, 9Mb/s baudrate, MSBFirst and software slave select is enabled.
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 * @param SPI_Mode SPI as slave or master
 * 	@arg SPI_SlaveMode
 * 	@arg SPI_MasterMode 
 */
void SPI_Init(SPI_TypeDef* SPIx, uint8_t SPI_Mode){
	SPI_EnableClock(SPIx);
	
	SPI_SetClockPolarity(SPIx, SPI_Polarity_HIGH);		//Clock is low at idle state
	SPI_SetClockPhase(SPIx, SPI_ClockPhase_1st);		//Capture data at 1st clock transition
	SPI_SetMasterSlave(SPIx, SPI_Mode);					//SPI as slave or master
	SPI_SetSourceClock(SPIx);							//9Mb/s baudrate
	SPI_SoftwareSlaveSelect_Enable(SPIx);
	SPI_SetFrameFormat(SPIx, SPI_MSBFirst);
	
	SPI_IO_Init(SPIx);
}

/**
 * @brief Configure selected SPI instance to be used in Transmit only mode.
 * 
 */
void SPI_SetTransmitOnlyMode(void){
	SPI1->CR1 |= (1 << 15);	 	//1-line bidirectional
	SPI1->CR1 |= (1 << 14);		//Output enable
}

/**
 * @brief Configure IO pins for SPI functionality
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 */
void SPI_IO_Init(SPI_TypeDef* SPIx){
	//Init CS IO
	if(SPIx == SPI1){
		GPIO_Init(GPIO_A, 4, GPIO_OUTPUT);
		GPIO_PullUpDown(GPIO_A, 4, GPIO_PIN_PULLUP);
		
		//Init SPI1 IO
		GPIO_Init(GPIO_A, 5, AFIO_OUTPUT);  //CLK
		GPIO_Init(GPIO_A, 6, AFIO_OUTPUT);  
		GPIO_Init(GPIO_A, 7, AFIO_OUTPUT);	//MOSI	
	}
	else if(SPIx==SPI2){
		GPIO_Init(GPIO_B, 12, GPIO_OUTPUT);
		GPIO_PullUpDown(GPIO_B, 12, GPIO_PIN_PULLUP);	

		//Init SPI1 IO
		GPIO_Init(GPIO_B, 13, AFIO_OUTPUT);  //CLK
		GPIO_Init(GPIO_B, 14, AFIO_OUTPUT);	//MOSI
		GPIO_Init(GPIO_B, 15, AFIO_OUTPUT);	//MOSI		
	}
}

/**
 * @brief Transmit data through SPI.
 * 
 * @param SPIx SPI instance
 * 	@arg SPI1
 * 	@arg SPI2
 * @param data Data to be transmitted
 * @param dataSize size of data (in bytes) to be transmitted
 */
void SPI_Transmit(SPI_TypeDef* SPIx, uint8_t* data, uint8_t dataSize){
	SPI_Enable(SPIx);
	uint8_t count = 0;
	while (count < dataSize){
		while(!((SPIx->SR) & (1 << 1)));  //Wait until TX buffer is empty
		SPIx->DR = data[count];
		count++;
	}
	
	while (!((SPIx->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPIx->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	

	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI1->DR;
	temp = SPI1->SR;	

	SPI_Disable(SPIx); //Disable SPI	
}

/**
 * @brief Transmit data through SPI using DMA
 * 
 * @param SPIx SPI instance.
 * 	@arg SPI1
 * 	@arg SPI2
 * @param data Data to be transmitted.
 * @param dataSize Size of data (in bytes) to be transmitted.
 */
void SPI_Transmit_DMA(SPI_TypeDef* SPIx, uint8_t* data, uint8_t dataSize){
	DMA_SetTransactionInfo(DMA1_Channel3, (uint32_t)data, (uint32_t)&SPIx->DR, dataSize);

	SPIx->CR2 |= (1 << 1);  //Enable TX buffer DMA (Send request to DMA channel)
	while(!(DMA1->ISR & (1 << 9))); //Wait for Transfer complete flag to set
	SPI_Enable(SPIx);
	
	SPIx->CR2 &= ~(1 << 1); //Release request
	SPI_Disable(SPIx);
}