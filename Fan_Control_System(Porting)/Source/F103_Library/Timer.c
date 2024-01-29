/**
 * @file Timer.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief Timer Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-01-24
 * 
 */

#include "Timer.h"

/**
* @brief Enables the clock for the APB bus containing the selected timer.
* @param Timer Pointer to the TIM_TypeDef structure representing the timer.
*		@arg TIM1
*		@arg TIM2
*		@arg TIM3
*		@arg TIM4
*/
void TIM_EnableTimerClock(TIM_TypeDef* Timer){
	if (Timer == TIM1) RCC->APB2ENR |= (1 << 11);
	else if (Timer == TIM2) RCC->APB1ENR |= (1 << 0);
	else if (Timer == TIM3) RCC->APB1ENR |= (1 << 1);
	else if (Timer == TIM4) RCC->APB1ENR |= (1 << 2);
}



/**
* @brief Set slave mode for selected Timer 
* @param Timer	Selected timer instance
*	 @arg TIM1
*	 @arg TIM2
*	 @arg TIM3
*	 @arg TIM4
*@param	 SlaveMode Slave configuration for selected timer instance
*	 @arg SLAVE_DISABLED		
*	 @arg SLAVE_EncoderMode_1	
*	 @arg SLAVE_EncoderMode_2	
*	 @arg SLAVE_EncoderMode_3	
*	 @arg SLAVE_ResetMode			
*	 @arg SLAVE_GatedMode			
*	 @arg SLAVE_TriggerMoe	
*/
void TIM_SetSlaveMode(TIM_TypeDef* Timer, uint8_t SlaveMode){
	Timer->SMCR &= ~((0b111) << 0);
	Timer->SMCR |= (SlaveMode << 0);
}



/**
 * @brief Select polarity for selected channel
 * @param Timer	Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param Channel Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 * @param Edge Edge of timer output channel at idle state
 * 		@arg TIM_EDGE_RISING
 * 		@arg TIM_EDGE_FALLING
 */
void TIM_SetPolarity(TIM_TypeDef* Timer, uint8_t Channel, uint8_t Edge){
	switch(Channel){
		case TIM_Channel_1:
			Timer->CCER &= ~(1 << 1);
			Timer->CCER |= (Edge << 1);
			break;
		
		case TIM_Channel_2:
			Timer->CCER &= ~(1 << 5);
			Timer->CCER |= (Edge << 5);
			break;

		case TIM_Channel_3:
			Timer->CCER &= ~(1 << 9);
			Timer->CCER |= (Edge << 9);
			break;
		
		case TIM_Channel_4:
			Timer->CCER &= ~(1 << 13);
			Timer->CCER |= (Edge << 13);
			break;
	}
}




/**
 * @brief Set Input/Output mode for selected channel
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param Channel Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 * @param ChannelDir Direction of the selected channel
 * 		@arg TIM_Channel_OUTPUT
 * 		@arg TIM_Channel_INPUT
 */
void TIM_SetChannelDirection(TIM_TypeDef* Timer, uint8_t Channel, uint8_t ChannelDir){
	switch(Channel){
		case TIM_Channel_1:
			Timer->CCMR1 &= ~(0b11 << 0);
			Timer->CCMR1 |= (ChannelDir << 0);
			break;
		case TIM_Channel_2:
			Timer->CCMR1 &= ~(0b11 << 8);
			Timer->CCMR1 |= (ChannelDir << 8);
			break;	
		case TIM_Channel_3:
			Timer->CCMR2 &= ~(0b11 << 0);
			Timer->CCMR2 |= (ChannelDir << 0);
			break;	
		case TIM_Channel_4:
			Timer->CCMR2 &= ~(0b11 << 8);
			Timer->CCMR2 |= (ChannelDir << 8);
			break;			
	}
}


/**
 * @brief Configure input filter for input capture
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param InputFilter 4-bit value input filter for selected timer channel
 * @param Channel Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 */
void TIM_SetInputCaptureFilter(TIM_TypeDef* Timer, uint8_t InputFilter, uint8_t Channel){
	switch(Channel){
		case TIM_Channel_1:
			Timer->CCMR1 &= ~(0b1111 << 4);
			Timer->CCMR1 |= (InputFilter << 4);
			break;
		case TIM_Channel_2:
			Timer->CCMR1 &= ~(0b1111 << 12);
			Timer->CCMR1 |= (InputFilter << 12);
			break;
		case TIM_Channel_3:
			Timer->CCMR2 &= ~(0b1111 << 4);
			Timer->CCMR2 |= (InputFilter << 4);
			break;
		case TIM_Channel_4:
			Timer->CCMR2 &= ~(0b1111 << 12);
			Timer->CCMR2 |= (InputFilter << 12);
			break;		
	}
}

/**
 * @brief Enables the counter for the specified timer
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 */
void TIM_EnableCounter(TIM_TypeDef* Timer){
	Timer->CR1 |= (1 << 0); //enable counter
}

/**
 * @brief Enable capturing input signal on selected timer channel
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param Channel: Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 */
void TIM_EnableCaptureInput(TIM_TypeDef* Timer, uint8_t Channel){
	switch(Channel){
		case TIM_Channel_1:
			Timer->CCER |= (1 << 0);
			break;
		case TIM_Channel_2:
			Timer->CCER |= (1 << 4);
			break;	
		case TIM_Channel_3:
			Timer->CCER |= (1 << 8);
		case TIM_Channel_4:
			Timer->CCER |= (1 << 12);
			break;			
	}
}

/**
 * @brief Configure IO pins for PWM functionality
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param channel: Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 */
void TIM_PWM_IO_Config(TIM_TypeDef* Timer, uint8_t channel){
	if(Timer == TIM1){
		switch (channel)
		{
			case TIM_Channel_1:
				GPIO_Init(GPIO_A, 8, AFIO_OUTPUT);
				break;
			case TIM_Channel_2:
				GPIO_Init(GPIO_A, 9, AFIO_OUTPUT);
				break;
			case TIM_Channel_3:
				GPIO_Init(GPIO_A, 10, AFIO_OUTPUT);
				break;
			case TIM_Channel_4:
				GPIO_Init(GPIO_A, 11, AFIO_OUTPUT);
				break;
			default:
				break;
		}
	}
	else if(Timer == TIM2){
		switch (channel)
		{
			case TIM_Channel_1:
				GPIO_Init(GPIO_A, 0, AFIO_OUTPUT);
				break;
			case TIM_Channel_2:
				GPIO_Init(GPIO_A, 1, AFIO_OUTPUT);
				break;
			case TIM_Channel_3:
				GPIO_Init(GPIO_A, 2, AFIO_OUTPUT);
				break;
			case TIM_Channel_4:
				GPIO_Init(GPIO_A, 3, AFIO_OUTPUT);
				break;		
			default:
				break;
		}
	}
	else if(Timer == TIM3){
		switch (channel)
		{
			case TIM_Channel_1:
				GPIO_Init(GPIO_A, 6, AFIO_OUTPUT);
				break;
			case TIM_Channel_2:
				GPIO_Init(GPIO_A, 7, AFIO_OUTPUT);
				break;
			case TIM_Channel_3:
				GPIO_Init(GPIO_B, 0, AFIO_OUTPUT);
				break;
			case TIM_Channel_4:
				GPIO_Init(GPIO_B, 1, AFIO_OUTPUT);
				break;		
			default:
				break;
		}
	}
	else if(Timer == TIM4){
		switch (channel)
		{
			case TIM_Channel_1:
				GPIO_Init(GPIO_B, 6, AFIO_OUTPUT);
				break;
			case TIM_Channel_2:
				GPIO_Init(GPIO_B, 7, AFIO_OUTPUT);
				break;
			case TIM_Channel_3:
				GPIO_Init(GPIO_B, 8, AFIO_OUTPUT);
				break;
			case TIM_Channel_4:
				GPIO_Init(GPIO_B, 9, AFIO_OUTPUT);
				break;		
			default:
				break;
		}
	}
}

/**
 * @brief Initialize PWM functionality on selected timer channel
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param channel: Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 * @param prescaler Timer prescaler
 * @param arrValue Value for ARR register (for setting PWM frequency)
 * @param CCRxValue Value for CCRx register (for setting PWM duty cycle)
 */
void TIM_PWM_Init(TIM_TypeDef* Timer, uint8_t channel, uint16_t prescaler, uint16_t arrValue, uint16_t CCRxValue){
	TIM_EnableTimerClock(Timer);
	//GPIO_EnableClock(GPIO_A);
	
	switch(channel){
		case TIM_Channel_1:
			Timer->PSC = prescaler - 1;
			Timer->ARR = arrValue - 1;
			Timer->CCR1 = CCRxValue;
			break;
		
		case TIM_Channel_2:
			Timer->PSC = prescaler - 1;
			Timer->ARR = arrValue - 1;
			Timer->CCR2 = CCRxValue;	
			break;
		
		case TIM_Channel_3:
			Timer->PSC = prescaler - 1;
			Timer->ARR = arrValue - 1;
			Timer->CCR3 = CCRxValue;	
			break;

		case TIM_Channel_4:
			Timer->PSC = prescaler - 1;
			Timer->ARR = arrValue - 1;
			Timer->CCR4 = CCRxValue;	
			break;
	}

	TIM_SetChannelDirection(Timer, channel, TIM_Channel_OUTPUT);
	TIM_SetSlaveMode(Timer, SLAVE_DISABLED);
	TIM_SetPolarity(Timer, channel, TIM_EDGE_RISING);  //Output compare active high
	TIM_PWM_Mode(Timer, channel, PWM_Mode_1);
	TIM_PWM_IO_Config(Timer, channel);

}

/**
 * @brief Enable Capture/Compare functionality on selected timer channel
 * @param Timer Timer instance
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param channel Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 */
void TIM_EnableCCOutput(TIM_TypeDef* Timer,uint8_t channel){
	if(channel == TIM_Channel_1) Timer->CCER |= (1 << 0);
	else if (channel == TIM_Channel_2) Timer->CCER |= (1 << 4);
	else if (channel == TIM_Channel_3) Timer->CCER |= (1 << 8);
	else if (channel == TIM_Channel_4) Timer->CCER |= (1 << 12);
}

/**
 * @brief Configure PWM mode for timer channel.
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param channel Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 * @param PWM_Mode PWM mode when timer channel is configured as output compare mode (Refer to Manual for more)
 * 		@arg PWM_Mode_1
 * 		@arg PWM_Mode_2
 */
void TIM_PWM_Mode(TIM_TypeDef* Timer, uint8_t channel, uint8_t PWM_Mode){
	switch(channel){
		case TIM_Channel_1:
			Timer->CCMR1 &= ~(0b111 << 4);
			Timer->CCMR1 |= (PWM_Mode << 4);
			break;
		case TIM_Channel_2:
			Timer->CCMR1 &= ~(0b111 << 12);
			Timer->CCMR1 |= (PWM_Mode << 12);
			break;
		case TIM_Channel_3:
			Timer->CCMR2 &= ~(0b111 << 4);
			Timer->CCMR2 |= (PWM_Mode << 4);
			break;
		case TIM_Channel_4:
			Timer->CCMR2 &= ~(0b111 << 12);
			Timer->CCMR2 |= (PWM_Mode << 12);
			break;
	}
}


/**
 * @brief Reinitialize timer counter and generate an update event
 * @param Timer	Timer instance
 */
void TIM_EnableUpdateGeneration(TIM_TypeDef* Timer){
	Timer->EGR |= (1 << 0);
}




/**
 * @brief Start generating PWM signal on selected timer channel
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param Channel Timer channel
 * 		@arg TIM_Channel_1
 * 		@arg TIM_Channel_2
 * 		@arg TIM_Channel_3
 * 		@arg TIM_Channel_4
 */
void TIM_PWM_Start(TIM_TypeDef* Timer, uint8_t Channel){
	TIM_EnableUpdateGeneration(Timer);
	TIM_EnableCCOutput(Timer, Channel);
	TIM_EnableCounter(Timer);
}

/**
 * @brief Set prescaler for selected timer channel
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param prescalerValue Prescaler value for timer source clock
 */
void TIM_SetPrescaler(TIM_TypeDef* Timer,uint16_t prescalerValue){
	Timer->PSC = prescalerValue - 1;
}


/**
 * @brief Set value for ARR register (for setting PWM frequency).
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param ARRValue 16 bit value to load into ARR register 
 */
void TIM_SetARRReg(TIM_TypeDef* Timer, uint16_t ARRValue){
	Timer->ARR = ARRValue;
}

/**
 * @brief Set CCR value for selected timer (for setting PWM duty cycle).
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param CCRxValue  16-bit value to load into CCRx register.
 * @param channel Timer channel.
 */
void TIM_SetCCRxReg(TIM_TypeDef* Timer, uint16_t CCRxValue, uint16_t channel){
	switch(channel){
		case TIM_Channel_1:
			Timer->CCR1 = CCRxValue;
			break;
		
		case TIM_Channel_2:
			Timer->CCR2 = CCRxValue;
			break;

		case TIM_Channel_3:
			Timer->CCR3 = CCRxValue;
			break;

		case TIM_Channel_4:
			Timer->CCR4 = CCRxValue;
			break;		
	}
}


/**
 * @brief Initialize Encoder Mode on selected timer channel.
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 * @param Mode Configure encoder mode.
 * 		@arg SLAVE_EncoderMode_1
 * 		@arg SLAVE_EncoderMode_2
 * 		@arg SLAVE_EncoderMode_3
 */
void TIM_Encoder_Init(TIM_TypeDef* Timer, uint8_t Mode){
	TIM_EnableTimerClock(Timer);  //Enable clock for selected Timer instance
	
	TIM_SetSlaveMode(Timer, Mode);  //Counter is counting on both channels
	
	//Set caputre edge for each channel
	TIM_SetPolarity(Timer, TIM_Channel_1, TIM_EDGE_RISING);
	TIM_SetPolarity(Timer, TIM_Channel_2, TIM_EDGE_RISING);
	
	//Set input dir for each channel and map to corresponding T1x
	TIM_SetChannelDirection(Timer, TIM_Channel_1, TIM_Channel_INPUT);
	TIM_SetChannelDirection(Timer, TIM_Channel_2, TIM_Channel_INPUT);
}

/**
 * @brief Start encoder functionality on selected timer (On channel 1 and 2 by default)
 * @param Timer Timer instance.
 * 		@arg TIM1
 * 		@arg TIM2
 * 		@arg TIM3
 * 		@arg TIM4
 */
void TIM_EncoderStart(TIM_TypeDef* Timer){
	TIM_EnableCaptureInput(Timer, TIM_Channel_1);
	TIM_EnableCaptureInput(Timer, TIM_Channel_2);
	TIM_EnableCounter(Timer);
}

