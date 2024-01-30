#include "ARM_System.h"

uint32_t ticks = 0;

void ARM_ClockInit(void){
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

void systick_handler(void){
    ticks++;
}

void ARM_SystickInit(void){
    SysTick->CTRL |= (1UL << 2UL); //AHB clock as Systick source clock
    SysTick->LOAD = 72000; //Generate interrupt every 72000 clock cycle (every 1ms)

    SysTick->CTRL |= (1UL << 1UL); //Enable interrupt generation when counter reach 0
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_SetPriority(SysTick_IRQn, 0);

    SysTick->CTRL |= (1UL << 0UL); //Enable counter
}

void ARM_SystemInit(void){
    ARM_ClockInit();
    ARM_SystickInit();
}

uint32_t ARM_GetTick(void){
    return ticks;
}