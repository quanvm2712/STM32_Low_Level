#include "Timer.h"
#include "gpio.h"

TIM_TypeDef* Timer_global;  //Variable to store selected Timer

/*-------------------------------------------------------Timer General API------------------------------------------------------*/
/**
 * @brief Enables the clock for the APB bus containing the selected timer.
 * @param Timer: Pointer to the TIM_TypeDef structure representing the timer.
 */
void TIM_EnableTimerClock(TIM_TypeDef* Timer){
	if (Timer == TIM1) RCC->APB2ENR |= (1 << 11);
	else if (Timer == TIM2) RCC->APB1ENR |= (1 << 0);
	else if (Timer == TIM3) RCC->APB1ENR |= (1 << 1);
	else if (Timer == TIM4) RCC->APB1ENR |= (1 << 2);
}



/**
@brief	Set slave mode for selected Timer 
@Param	Timer:	Selected timer instance
					@arg:	TIM1
								TIM2
								TIM3
								TIM4
				SlaveMode: Slave configuration for selected timer instance
					@arg:	SLAVE_DISABLED			
								SLAVE_EncoderMode_1	
								SLAVE_EncoderMode_2	
								SLAVE_EncoderMode_3	
								SLAVE_ResetMode			
								SLAVE_GatedMode			
								SLAVE_TriggerMode		
*/
void TIM_SetSlaveMode(TIM_TypeDef* Timer, uint8_t SlaveMode){
	Timer->SMCR &= ~((0b111) << 0);
	Timer->SMCR |= (SlaveMode << 0);
}



/**
	@brief	Select polarity for selected channel
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
	@brief	Set Input/Output mode for selected channel
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
 * @brief Enables the counter for the specified timer and waits until the counter overflows.
 * @param Timer: Pointer to the TIM_TypeDef structure representing the timer.
 */
void TIM_EnableCounter(TIM_TypeDef* Timer){
	Timer->CR1 |= (1 << 0); //enable counter
	//while (!(Timer->SR & (1<<0))); //wait until counter is overflow
}


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




/*----------------------------------------------------------------PWM Module------------------------------------------------------------*/
/**
	*@brief Init PWM module of STM32
	*@param Timer: Pointer to the TIM_TypeDef structure representing the timer.
					channel: Target PWM output channel
	*/
void TIM_PWM_Init(TIM_TypeDef* Timer, uint16_t channel, uint16_t prescaler, uint16_t arrValue, uint16_t CCRxValue){
	Timer_global = Timer;
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
	//TIM_ChannelConfig(channel);
	//TIM_SetSlaveMode(Timer, SLAVE_EncoderMode_3);
}



/**
	*@brief	Set PWM mode 1 on selected TIM channel
	*@Param	channel:	Selected PWM Channel
	*				This parameter can have these following values
	*					@arg: TIM_Channel_1
	*					@arg: TIM_Channel_2
	*					@arg: TIM_Channel_3
	*					@arg: TIM_Channel_4

	*/
void TIM_ChannelMode_1(uint8_t channel){
	//PWM Mode 1 for selected channel
	if (channel == TIM_Channel_1) Timer_global->CCMR1 |= (1 << 5) | (1 << 6);
	else if (channel == TIM_Channel_2) Timer_global->CCMR1 |= (1 << 13) | (1 << 14);
	else if (channel == TIM_Channel_3) Timer_global->CCMR2 |= (1 << 5) | (1 << 6);
	else if (channel == TIM_Channel_4) Timer_global->CCMR2 |= (1 << 13) | (1 << 14);
}



/**
	*	@brief	Enable Capture/Compare Output on selected PWM channel
	*	@Param	channel:	Selected PWM Channel
	*				This parameter can have these following values
	*					@arg: TIM_Channel_1
	*					@arg: TIM_Channel_2
	*					@arg: TIM_Channel_3
	*					@arg: TIM_Channel_4
	*/
void TIM_EnableCCOutput(TIM_TypeDef* Timer,uint8_t channel){
	if(channel == TIM_Channel_1) Timer->CCER |= (1 << 0);
	else if (channel == TIM_Channel_2) Timer->CCER |= (1 << 4);
	else if (channel == TIM_Channel_3) Timer->CCER |= (1 << 8);
	else if (channel == TIM_Channel_4) Timer->CCER |= (1 << 12);
}


/**
	*	@brief	General PWM configuration for selected channel 
	*	@Param	channel:	Selected PWM Channel
	*				This parameter can have these following values
	*					@arg: TIM_Channel_1
	*					@arg: TIM_Channel_2
	*					@arg: TIM_Channel_3
	*					@arg: TIM_Channel_4
	*/
void TIM_ChannelConfig(uint8_t channel){
	//PWM Mode 1 for selected channel
	TIM_ChannelMode_1(channel);
	
	//Enable capture/compare output
	//TIM_EnableCCOutput(channel);
}


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
	*	@brief	Enable Update Generation for TIM 
	*/
void PWM_EnableUpdateGeneration(){
	Timer_global->EGR |= (1 << 0);
}





void TIM_PWM_Start(TIM_TypeDef* Timer, uint8_t Channel){
	PWM_EnableUpdateGeneration();
	TIM_EnableCCOutput(Timer, Channel);
	TIM_EnableCounter(Timer);
}


void TIM_SetPrescaler(TIM_TypeDef* Timer,uint16_t prescalerValue){
	Timer->PSC = prescalerValue - 1;
}




void TIM_SetARRReg(TIM_TypeDef* Timer, uint16_t ARRValue){
	Timer->ARR = ARRValue;
}



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






/*-------------------------------------------------Encoder Module-------------------------------------------*/
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

void TIM_EncoderStart(TIM_TypeDef* Timer){
	TIM_EnableCaptureInput(Timer, TIM_Channel_1);
	TIM_EnableCaptureInput(Timer, TIM_Channel_2);
	TIM_EnableCounter(Timer);
}

