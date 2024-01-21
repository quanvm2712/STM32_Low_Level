#include "stdint.h"
#include "stm32f1xx.h"

volatile uint32_t* reg = (uint32_t*)&RCC->APB2ENR;

void Enable_GPIOC_Clock(){
    RCC->APB2ENR |= (1UL << 4UL); //(RCC_APB2ENR_IOPCEN);
}

void GPIOC_Config(){
    Enable_GPIOC_Clock();
    GPIOC->CRH |= (0b0010UL << 20UL);
}

void GPIO_Set(){
    GPIOC->BSRR |= (1UL << 13UL);
}

void GPIO_Reset(){
    GPIOC->BSRR |= (1UL << 29UL);
}

void delay(uint32_t ms){
    for(int i=0; i< ms; i++);
}

int main(void){
    GPIOC_Config();

    while (1)
    {
        GPIO_Set();
        delay(1000000);
        GPIO_Reset();
        delay(1000000);
    }
    
}