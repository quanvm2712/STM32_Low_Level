#include "stdint.h"
#include "stm32f1xx.h"

uint32_t ms_count = 0;

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

void systick_handler(){
    ms_count++;

}

void ClockInit(void){
    FLASH->ACR |= (0b010 << 0); //Flash latency

    RCC->CR |= (1 << 16); //Enable HSE clock source
    while (!(RCC->CR & (1 << 17)));
 
    /*PLL Config*/
    RCC->CFGR |= (1UL << 16UL);  //HSE as clock source for PLL
    RCC->CFGR |= (0b111UL << 18UL); //PLL MULTIPLY BY 9
    RCC->CFGR |= (RCC_CFGR_PPRE1_DIV2);  //APB1 prescaler

    RCC->CR |= (1UL << 24UL);  //Enable PLL
    while(!(RCC->CR & (RCC_CR_PLLRDY_Msk))); //Wait for PLL to be ready
    
    RCC->CFGR |= (0b10UL << 0UL); //PLL as system clock
    while(!(RCC->CFGR & (0b10UL << 2UL)));  //Wait for status

}

int main(void){
    ClockInit();
    
    GPIOC_Config();

    SysTick_Config(72000);  //Generate 1ms time base for SysTick
    __enable_irq();

    GPIOC_Config();


    while (1){
        if(ms_count >= 1000){
            GPIOC_Toggle();
            ms_count = 0;
        }
    }
    
}