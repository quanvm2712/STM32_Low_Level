#include "stdint.h"

#define RCC_BASE    (0x40021000U)
#define GPIOC_BASE  (0x40011000U)

#define RCC_CR      (*((volatile uint32_t*)(RCC_BASE + 0x00U)))
#define RCC_APB2ENR (*((volatile uint32_t*)(RCC_BASE + 0x18U)))

#define GPIOC_CRH   (*((volatile uint32_t*)(GPIOC_BASE + 0x4U)))
#define GPIOC_BSRR  (*((volatile uint32_t*)(GPIOC_BASE + 0x10U)))

void GPIOC_Config(void){
    //Enable clock for GPIOC peripheral
    RCC_APB2ENR |= (1 << 4);

    //Config OUTPUT Mode for GPIOC Pin 13
    GPIOC_CRH |= (0b0010 << 20);
}

void GPIO_Set(void){
    GPIOC_BSRR |= (1 << 13);
}

void GPIO_Reset(void){
    GPIOC_BSRR |= (1 << 29);
}


void delay(uint32_t ms){
    for(int i=0; i<ms; i++);
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