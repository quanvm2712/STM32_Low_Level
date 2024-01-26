#include "stdint.h"
#include "Delay.h"
#include "GPIO.h"
#include "SPI.h"
#include "MAX7219.h"
#include "IWDG.h"
#include "Timer.h"
#include "I2C.h"

#define LED_PIN         	13
#define ENCODER_PPR     	30  	//Encoder resolution
#define AHT20_I2C_ADDRESS	0x38	//AHT20 I2C slave address

/*Motor variable*/
int counterVal;
uint16_t position = 0;
uint16_t old_position = 0;
uint16_t encoderPPS = 0;
uint16_t currentFanRPM = 0;
uint16_t ms_count = 0;
uint8_t rx_data = 60;

/*I2C variable*/
uint8_t RX_Data[6];

void TIM1_UP_Handler(){
	if(TIM1->SR & 0x1){  //Check if interrupt flag is set
		ms_count += 1;
		
		/*Calculate RPM every 200ms*/
		if(ms_count >= 200){
			position = counterVal / 4;  //Get current position of encoder
			if (position >= old_position){
				encoderPPS = (position - old_position) * 5;  
			}
			currentFanRPM = (encoderPPS * 60) / ENCODER_PPR;
			old_position = position;
            ms_count = 0;
		}
		TIM1->SR &= ~1;  //Reset interrupt flag
	}
}

void TIM1_Config(){
	TIM_EnableTimerClock(TIM1);
	
	//Set prescaler and ARR value (Timer 1 generate interrupt every 1ms)
	TIM1->PSC = 72-1;
	TIM1->ARR = 1000 - 1;
	
	//Enable update interrupt
	TIM1->DIER |= (1 << 0);
	
	NVIC_EnableIRQ(TIM1_UP_IRQn);
	NVIC_SetPriority(TIM1_UP_IRQn, 2);
	
	TIM1->CR1 |= (1 << 0);  //Enable timer 1
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

void ToggleLED(){
    GPIO_Toggle(GPIO_C, LED_PIN);
}

uint16_t GetCounterValue(){
	return TIM4->CNT;
}

void Set_DutyCycle(uint8_t DutyCycle){
	TIM_SetCCRxReg(TIM3,DutyCycle, TIM_Channel_3);
}


int main(void){
    ClockInit();
    TIM1_Config();

    IWDG_Init(IWDG_DIV_64, 3125);

    GPIO_Init(GPIO_C, LED_PIN, GPIO_OUTPUT);  //Config IO for blinking LED

    SPI_Init(SPI1, SPI_Master); //Init SPI1
    MAX7219_Clean();
    MAX7219_Init(15, DIGIT_0_TO_7, DECODE_MODE_DISABLE);

	//Init Timer 3 channel 3 IO for PWM functionality
	TIM_PWM_Init(TIM3, TIM_Channel_3, 72, 100, 50);
	TIM_PWM_Start(TIM3, TIM_Channel_3);
	
	//Encoder Mode Init and run
	TIM_Encoder_Init(TIM4, SLAVE_EncoderMode_3);
	TIM_EncoderStart(TIM4);

	/**I2C Init */
	I2C_Init(I2C1, I2C1_REMAPPING_ENABLE, I2C_MASTERMODE_SM);


    while (1){
        counterVal = GetCounterValue(); //Get current counter value from Timer 4	
        Set_DutyCycle(rx_data);

        MAX7219_PrintInt(currentFanRPM, 4, DIGIT_POSITION_7);
        ToggleLED();

		uint8_t data[3] = {0xBE, 0x08, 0x00};
		//I2C_Status status =  I2C_TransmitData(I2C1, AHT20_I2C_ADDRESS, data, 3);

		I2C_Status status = I2C_ReadData(I2C1, 0x38, RX_Data, 6);

        IWDG_Reset(); 
		delay_ms(100);
    }
    
}