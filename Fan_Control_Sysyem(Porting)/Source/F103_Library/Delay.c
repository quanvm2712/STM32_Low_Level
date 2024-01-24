/**
 * @file Delay.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief Implementing function for generating precise delay
 * @version 0.1
 * @date 2024-01-24
 * 
 */

#include "Delay.h"

/**
 * @brief Configure Timer2 for generating presise delay.
 * Configure the timer so that its counter will increase every 1us
 * 
 */
void TIM2_Config(void){
	RCC->APB1ENR |= (1 << 0); //Enable timer2 clock
	
	TIM2->ARR = 0xFFFF - 1;  //Load value auto-reload register
	TIM2->PSC = 72 - 1;  //Load value to prescaler register
	
	TIM2->CR1 |= (1<<0); //enable counter
	
	while(!(TIM2->SR & (1<<0))); //wait for counter to overflow
	
}

/**
 * @brief Generate delay in us
 * 
 * @param time_us Desired time (in us) for the processor to be delayed
 */
void delay_us(uint16_t time_us){
	TIM2_Config();
	TIM2->CNT = 0; //Reset counter value.
	while (TIM2->CNT < time_us);  //Wait until counter value exceed time_us
}

/**
 * @brief Generate delay in ms
 * 
 * @param time_ms Desired time (in us) for the processor to be delayed
 */
void delay_ms(uint16_t time_ms){
	for (uint16_t i=0; i < time_ms; i++){
		delay_us(1000);  //Generate 1000us for each 1ms
	}
}
