#include "delay.h"

void TIM2_Config(void){
	//enable timer2 clock
	RCC->APB1ENR |= (1 << 0);
	
	TIM2->ARR = 0xFFFF - 1;  //auto-reload register
	TIM2->PSC = 72 - 1;  //prescaler
	
	
	//enable counter
	TIM2->CR1 |= (1<<0);
	
	while(!(TIM2->SR & (1<<0))); //wait for counter to overflow
	
}


void delay_us(uint16_t time_us){
	TIM2_Config();
	TIM2->CNT = 0; //reset counter value
	while (TIM2->CNT < time_us);  //wait until counter value exceed time_us
}

void delay_ms(uint16_t time_ms){
	for (uint16_t i=0; i < time_ms; i++){
		delay_us(1000);
	}
}
