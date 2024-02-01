/**
 * @file USART.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief USART Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "USART.h"

/**
 * @brief Enable clock for selected USART instance
 * 
 * @param USARTx UASRT instance
 *  @arg  USART1
 *  @arg  USART2
 *  @arg  USART3
 */
void USART_EnableClock(USART_TypeDef* USARTx){
    if(USARTx == USART1){
        RCC->APB2ENR |= (1UL << 14);
    }
    else if(USARTx == USART2){
        RCC->APB1ENR |= (1UL << 17);
    }
    else if(USARTx == USART3){
        RCC->APB1ENR |= (1UL << 18);
    }
}

/**
 * @brief Enable USART functionality
 * 
 * @param USARTx USART instance
 *  @arg USART1
 *  @arg USART2
 *  @arg USART3
 */
void USART_EnablePeripheral(USART_TypeDef* USARTx){
    USARTx->CR1 |= (1UL << 13UL);
}

/**
 * @brief Set number of stop bits for selected USART instance
 * 
 * @param USARTx USART instance
 * @param NumberOfStopBits Number of stop bits for USART communication
 *  @arg USART_1_STOP_BIT
 *  @arg USART_HALF_STOP_BITS
 *  @arg USART_2_STOP_BITS
 *  @arg USART_1ANDHALF_STOP_BIT
 */
void USART_ConfigStopBits(USART_TypeDef* USARTx, uint8_t NumberOfStopBits){
    USARTx->CR2 &= ~(0b11 << 12UL); //Reset all bits
    USARTx->CR2 |= (NumberOfStopBits << 12UL);
}

/**
 * @brief Configure word length for USART
 * 
 * @param USARTx USART instance
 * @param WordLength USART word length
 *  @arg UASRT_8_DATA_BITS
 *  @arg UASRT_9_DATA_BITS
 */
void USART_ConfigWordLength(USART_TypeDef* USARTx, _Bool WordLength){
    USARTx->CR1 &= ~(1UL << 12UL); //Reset bit
    USARTx->CR1 |= (WordLength << 12UL);
}

/**
 * @brief Configure baudrate for USART
 * 
 * @param USARTx USART instance
 * @param DesiredBaudrate User's desired baudrate
 *  @arg USART_BAUDRATE_9600
 *  @arg USART_BAUDRATE_19200
 *  @arg USART_BAUDRATE_57600
 *  @arg USART_BAUDRATE_115200
 */
void USART_ConfigBaudrate(USART_TypeDef* USARTx, uint8_t DesiredBaudrate){
    if(USARTx == USART1){  //APB2, 72MHz clock
        switch (DesiredBaudrate)
        {
            case USART_BAUDRATE_9600:
                USARTx->BRR = 0x1D4C;    //USARTDIV = 468.75
                break;
            case USART_BAUDRATE_19200:
                USARTx->BRR = 0xEA6;    //USARTDIV = 234.375
                break;
            case USART_BAUDRATE_57600:
                USARTx->BRR = 0x4E2;    //USARTDIV = 78.125
                break;
            case USART_BAUDRATE_115200:
                USARTx->BRR = 0x271;    //USARTDIV = 39.0625
                break;
            
            default:
                break;
        }
    }

    else if(USARTx == USART2 || USARTx == USART3){  //APB1, 36MHz clock
        switch (DesiredBaudrate)
        {
            case USART_BAUDRATE_9600:
                USARTx->BRR = 0xEA6;    //USARTDIV = 234.375
                break;
            case USART_BAUDRATE_19200:
                USARTx->BRR = 0x753;    //USARTDIV = 117.1875
                break;
            case USART_BAUDRATE_57600:
                USARTx->BRR = 0x271;    //USARTDIV = 39.0625
                break;
            case USART_BAUDRATE_115200:
                USARTx->BRR = 0x138;    //USARTDIV = 19.5
                break;
            
            default:
                break;
        }
    }
}

/**
 * @brief Enable USART Transmit functionality
 * 
 * @param USARTx USART instance
 */
void USART_TransmitterEnable(USART_TypeDef* USARTx){
    USARTx->CR1 |= (1UL << 3UL);
}

/**
 * @brief Disable USART transmit functionality
 * 
 * @param USARTx USART intance
 */
void USART_TransmitterDisable(USART_TypeDef* USARTx){
    USARTx->CR1 &= ~(1UL << 3UL);
}

/**
 * @brief Configure IO Pin for USART functionality
 * 
 * @param USARTx USART instance
 */
void USART_IOInit(USART_TypeDef* USARTx){
    if(USARTx == USART1){
        GPIO_Init(GPIO_A, 9, AFIO_OUTPUT);
        GPIO_Init(GPIO_A, 10, GPIO_INPUT);
    }
}

/**
 * @brief Enable UASRT receive functionality
 * 
 * @param USARTx USART instance
 */
void USART_ReceiverEnable(USART_TypeDef* USARTx){
    USARTx->CR1 |= (1UL << 2UL);
}

/**
 * @brief Initialize selected USART 
 * 
 * @param USARTx USART instance
 * @param WordLength USART word length
 * @param NumberOfStopBits USART number of stop bits
 * @param DesiredBaudrate User desired baudrate
 */
void USART_Init(USART_TypeDef* USARTx, _Bool WordLength, uint8_t NumberOfStopBits, uint8_t DesiredBaudrate){
    USART_EnableClock(USARTx);
    USART_EnablePeripheral(USARTx);
    USART_IOInit(USARTx);

    USART_ConfigWordLength(USARTx, WordLength);
    USART_ConfigStopBits(USARTx, NumberOfStopBits);
    USART_ConfigBaudrate(USARTx, DesiredBaudrate);

    USART_ReceiverEnable(USARTx);
    USART_TransmitterEnable(USARTx);
}

/**
 * @brief Transmit data using USART
 * 
 * @param USARTx UASRT instance
 * @param Data Data to be transmitted
 * @param DataSize Number of bytes to be transmitted
 */
void USART_TransmitData(USART_TypeDef* USARTx, uint8_t* Data, uint16_t DataSize){
    USART_TransmitterEnable(USARTx);

    for(int count=0; count < DataSize; count++){
        USARTx->DR = Data[count];
        while (!(USARTx->SR & (1UL << 7UL))){};  //Wait until TXE is set
    }

    while (!(USARTx->SR & (1UL << 7UL))){};  //Wait until TC is set
    USARTx->SR &= ~(1UL << 7UL); //Clear TC bits
}

/**
 * @brief Receive data using USART
 * 
 * @param USARTx USART instance
 * @param ReceivedData Buffer to store received data
 * @param DataSize Number of bytes to be received
 */
void USART_ReceiveData(USART_TypeDef* USARTx, uint8_t* ReceivedData, uint8_t DataSize){
    static volatile uint8_t UARTDataCount = 0;
    static uint8_t trick_count = 1;

    //Since UARTDataCount cannot be initialize to 0, a walkaround is to init the variable to 0 
    //when this function is first called during program execution
    if(trick_count == 1){
        UARTDataCount = 0;
        trick_count ++;
    }

    USART_ReceiverEnable(USARTx);
    if(USARTx->SR & (1UL << 5UL)){  //Check if RDR contains data
        ReceivedData[UARTDataCount] = USARTx->DR;  //Read if RDR contains data
        UARTDataCount ++;
    }

    if(UARTDataCount >= (DataSize)){
        UARTDataCount = 0;  //Reset buffer index if exceed desired data size
    }
}

/**
 * @brief Receive data through UASRT using DMA
 * 
 * @param USARTx USART instance
 * @param ReceivedBuffer Buffer to store  received data
 * @param DataSize Number of bytes to be received
 */
void USART_ReceiveData_DMA(USART_TypeDef* USARTx, uint8_t* ReceivedBuffer, uint8_t DataSize){
    uint8_t Timeout = 50;
    uint32_t lastTicks;

    DMA_SetTransactionInfo(DMA1_Channel5, (uint32_t)ReceivedBuffer, (uint32_t)&USARTx->DR, DataSize);
    //USART_ReceiverEnable(USARTx);

    if(USARTx->SR & (1UL << 5UL)){    //Check if RXNE is set
        USARTx->CR3 |= (1UL << 6UL);  //Enable USART DMA receiver

        //Wait until RX buffer is empty
        uint8_t status;
        lastTicks = ARM_GetTick();
        do{
            status = USARTx->SR & (1UL << 5UL);
        }while(status && ((ARM_GetTick() - lastTicks) < Timeout));

        DMA1->IFCR |= (1UL << 16UL); //Clear TCIF flag
        USARTx->CR3 &= ~(1UL << 6UL); //Disable USART DMA channel
    }
}