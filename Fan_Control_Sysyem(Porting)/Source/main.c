#include "stdint.h"
#include "Delay.h"
#include "GPIO.h"

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

    SysTick_Config(72000000);  //Generate 1s time base for SysTick
    __enable_irq();

    GPIO_Init(GPIO_C, 13, GPIO_OUTPUT);



    while (1){
        GPIO_Toggle(GPIO_C, 13);
        delay_ms(100);
    }
    
}