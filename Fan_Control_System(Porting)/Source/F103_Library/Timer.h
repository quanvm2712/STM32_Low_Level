#ifndef __Timer_H
#define __Timer_H

#include "stm32f1xx.h"
#include "GPIO.h"

#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */
#define   	__I     volatile const       /*!< Defines 'read only' permissions */
	
#define	TIM_Channel_1	        1UL
#define	TIM_Channel_2	        2UL
#define	TIM_Channel_3	        3UL      
#define	TIM_Channel_4	        4UL



/*----------------Timer General Function-----------------*/
//Timer Slave Mode Define
#define	SLAVE_DISABLED			0UL
#define SLAVE_EncoderMode_1	    1UL
#define SLAVE_EncoderMode_2	    2UL
#define SLAVE_EncoderMode_3	    3UL
#define SLAVE_ResetMode			4UL
#define	SLAVE_GatedMode			5UL
#define	SLAVE_TriggerMode		6UL

//Timer Channel Define
#define	TIM_Channel_1	        1UL
#define	TIM_Channel_2	        2UL
#define	TIM_Channel_3	        3UL
#define	TIM_Channel_4	        4UL

//Timer Channel Polarity Define
#define TIM_EDGE_RISING	        0UL
#define TIM_EDGE_FALING	        1UL

//Timer Channel Direction
#define	TIM_Channel_OUTPUT	    0UL
#define	TIM_Channel_INPUT	    1UL



void TIM_ChannelConfig(uint8_t channel);
void TIM_EnableTimerClock(TIM_TypeDef* Timer);
void TIM_SetSlaveMode(TIM_TypeDef* Timer, uint8_t SlaveMode);
void TIM_SetPolarity(TIM_TypeDef* Timer, uint8_t Channel, uint8_t Edge);
void TIM_SetChannelDirection(TIM_TypeDef* Timer, uint8_t Channel, uint8_t ChannelDir);
void TIM_EnableCounter(TIM_TypeDef* Timer);
void TIM_SetPrescaler( TIM_TypeDef* Timer,uint16_t prescalerValue);
void TIM_SetARRReg(TIM_TypeDef* Timer, uint16_t ARRValue);
void TIM_SetCCRxReg(TIM_TypeDef* Timer, uint16_t CCRxValue, uint16_t channel);

void PWM_EnableUpdateGeneration();
void TIM_EnableCCOutput(TIM_TypeDef* Timer,uint8_t channel);




/*-----------------PWM User Function---------------------*/
#define	PWM_Mode_1	0b110
#define PWM_Mode_2	0b111

void TIM_PWM_Init(TIM_TypeDef* Timer, uint8_t channel, uint16_t prescaler, uint16_t arrValue, uint16_t CCRxValue);
void TIM_PWM_Start(TIM_TypeDef* Timer, uint8_t Channel);
void TIM_PWM_Mode(TIM_TypeDef* Timer, uint8_t channel, uint8_t PWM_Mode);


/*-----------------Encoder Mode User Function---------------------*/
void TIM_Encoder_Init(TIM_TypeDef* Timer, uint8_t Mode);
void TIM_EncoderStart(TIM_TypeDef* Timer);

#endif //__Timer_H