#include "stdint.h"
#include "Delay.h"
#include "GPIO.h"
#include "SPI.h"
#include "MAX7219.h"
#include "IWDG.h"

#define LED_PIN     13

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

void ToggleLED(){
    GPIO_Toggle(GPIO_C, LED_PIN);
}

int main(void){
    ClockInit();

    IWDG_Init(IWDG_DIV_64, 3125);

    GPIO_Init(GPIO_C, LED_PIN, GPIO_OUTPUT);  //Config IO for blinking LED

    SPI_Init(SPI1, SPI_Master); //Init SPI1
    MAX7219_Clean();
    MAX7219_Init(15, DIGIT_0_TO_7, DECODE_MODE_DISABLE);


    while (1){
        MAX7219_PrintInt(2024, 4, DIGIT_POSITION_7);
        ToggleLED();
        delay_ms(100);

        IWDG_Reset(); 
    }
    
}