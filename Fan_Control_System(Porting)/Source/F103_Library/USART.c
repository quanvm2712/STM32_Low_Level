#include "USART.h"

/**
 * @brief 
 * 
 * @param USARTx 
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

void USART_EnablePeripheral(USART_TypeDef* USARTx){
    USARTx->CR1 |= (1UL << 13UL);
}

void USART_ConfigStopBits(USART_TypeDef* USARTx, uint8_t NumberOfStopBits){
    USARTx->CR2 &= ~(0b11 << 12UL); //Reset all bits
    USARTx->CR2 |= (NumberOfStopBits << 12UL);
}

void USART_ConfigWordLength(USART_TypeDef* USARTx, _Bool WordLength){
    USARTx->CR1 &= ~(1UL << 12UL); //Reset bit
    USARTx->CR1 |= (WordLength << 12UL);
}

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

void USART_TransmitterEnable(USART_TypeDef* USARTx){
    USARTx->CR1 |= (1UL << 3UL);
}

void USART_TransmitterDisable(USART_TypeDef* USARTx){
    USARTx->CR1 &= ~(1UL << 3UL);
}

void USART_TransmitData(USART_TypeDef* USARTx, uint8_t* Data, uint16_t DataSize){
    USART_TransmitterEnable(USARTx);

    for(int count=0; count < DataSize; count++){
        USARTx->DR = Data[count];
        while (!(USARTx->SR & (1UL << 7UL))){};  //Wait until TXE is set
    }

    while (!(USARTx->SR & (1UL << 7UL))){};  //Wait until TC is set
    USARTx->SR &= ~(1UL << 7UL); //Clear TC bits
}

void USART_IOInit(USART_TypeDef* USARTx){
    if(USARTx == USART1){
        GPIO_Init(GPIO_A, 9, AFIO_OUTPUT);
        GPIO_Init(GPIO_A, 10, GPIO_INPUT);
    }
}

void USART_Init(USART_TypeDef* USARTx, _Bool WordLength, uint8_t NumberOfStopBits, uint8_t DesiredBaudrate){
    USART_EnableClock(USARTx);
    USART_EnablePeripheral(USARTx);
    USART_IOInit(USARTx);

    USART_ConfigWordLength(USARTx, WordLength);
    USART_ConfigStopBits(USARTx, NumberOfStopBits);
    USART_ConfigBaudrate(USARTx, DesiredBaudrate);
}