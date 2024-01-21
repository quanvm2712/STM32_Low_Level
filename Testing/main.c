#include "stdint.h"
#include "stm32f10x.h"

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

void GPIOC_Toggle(){
    GPIOC->ODR ^= (1 << 13);
}
void delay(uint32_t ms){
    for(int i=0; i< ms; i++);
}

void systick_handler(){
    GPIOC_Toggle();
}

void Clock_Init(void){
    RCC->CR |= (RCC_CR_HSEON); //Enable HSE clock source
    while (!(RCC->CR & (RCC_CR_HSERDY)));

    RCC->CFGR |= (RCC_CFGR_SW_HSE);
    while (!(RCC->CFGR & RCC_CFGR_SWS_HSE));
    
}

int main(void){
    SystemInit();

    SysTick_Config(100000);
    __enable_irq();

    GPIOC_Config();

    while (1)
    {
    }
    
}