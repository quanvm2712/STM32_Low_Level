/**
 * @file GPIO.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief GPIO Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-01-24
 * 
 */

#include "GPIO.h"

/**
 * @brief Enable clock for selected GPIO port
 * 
 * @param GPIO_Port GPIO port
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 */
void GPIO_EnableClock(uint8_t GPIO_Port){
		RCC->APB2ENR |= (1<<GPIO_Port);
}

/**
 * @brief Configure a GPIO pin
 * 
 * @param GPIO_Port Target GPIO port
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 * @param GPIO_Pin Target GPIO pin
 * @param mode GPIO pin's mode
 * 	@arg GPIO_OUTPUT
 * 	@arg GPIO_INPUT
 * 	@arg AFIO_OUTPUT
 */
void GPIO_Init(uint8_t GPIO_Port, uint8_t GPIO_Pin, uint8_t mode){
	GPIO_EnableClock(GPIO_Port);  
	
	RCC->APB2ENR |= (1 << 0); //ENABLE AFIO clock
	AFIO->MAPR |= (1 << 25);//JTAG-DP Disabled and SW-DP Enabled 010 
	
	
	switch(GPIO_Port){
		case GPIO_A:
			// Case 1: GPIO_Pin is less than 8
			if(GPIO_Pin < 8){	
				uint8_t config_bit = (GPIO_Pin * 4);
				
	      		if(mode == GPIO_INPUT){
					GPIOA->CRL &= ~((0b1111) << config_bit);
					GPIOA->CRL |= ((0b1000) << config_bit);

				}
				else if (mode == GPIO_OUTPUT){
					//10mhz output mode, push-pull
					GPIOA->CRL &= ~((0b1111) << config_bit);
					GPIOA->CRL |= ((0b0001) << config_bit);					
				}
				else if (mode == AFIO_OUTPUT){
					GPIOA->CRL &= ~((0b1111) << config_bit);
					GPIOA->CRL |= ((0b1010) << config_bit);					
				}
				else if(mode == AFIO_OPEN_DRAIN){
					GPIOA->CRL &= ~((0b1111) << config_bit);
					GPIOA->CRL |= ((0b1110) << config_bit);						
				}
			}
			
			// Case 2: GPIO_Pin is 8 or bigger
			else if ((GPIO_Pin >= 8) & (GPIO_Pin < 16)){
				uint8_t config_bit = 4 * (GPIO_Pin - 8);
				
	     		if(mode == GPIO_INPUT){
					GPIOA->CRH &= ~((0b1111) << config_bit);
					GPIOA->CRH |= ((0b1000) << config_bit);

				}
				else if (mode == GPIO_OUTPUT){
					//10mhz output mode, push-pull
					GPIOA->CRH &= ~((0b1111) << config_bit);
					GPIOA->CRH |= ((0b0001) << config_bit);					
				}
				else if (mode == AFIO_OUTPUT){
					GPIOA->CRH &= ~((0b1111) << config_bit);
					GPIOA->CRH |= ((0b1010) << config_bit);					
				}
				else if (mode == AFIO_OPEN_DRAIN){
					GPIOA->CRH &= ~((0b1111) << config_bit);
					GPIOA->CRH |= ((0b1110) << config_bit);					
				}
			}
			break;
			
			

		case GPIO_B:
			// Case 1: GPIO_Pin is less than 8
			if(GPIO_Pin < 8){	
				uint8_t config_bit = (GPIO_Pin * 4);
				
	      		if(mode == GPIO_INPUT){
					GPIOB->CRL &= ~((0b1111) << config_bit);
					GPIOB->CRL |= ((0b1000) << config_bit);

				}
				else if (mode == GPIO_OUTPUT){
					//10mhz output mode, push-pull
					GPIOB->CRL &= ~((0b1111) << config_bit);
					GPIOB->CRL |= ((0b0001) << config_bit);					
				}
				else if (mode == AFIO_OUTPUT){
					GPIOB->CRL &= ~((0b1111) << config_bit);
					GPIOB->CRL |= ((0b1010) << config_bit);					
				}
				else if (mode == AFIO_OPEN_DRAIN){
					GPIOB->CRL &= ~((0b1111) << config_bit);
					GPIOB->CRL |= ((0b1110) << config_bit);					
				}
			}
			
			// Case 2: GPIO_Pin is 8 or bigger
			else if ((GPIO_Pin >= 8) & (GPIO_Pin < 16)){
				uint8_t config_bit = 4 * (GPIO_Pin - 8);
				
	      		if(mode == GPIO_INPUT){
					GPIOB->CRH &= ~((0b1111) << config_bit);
					GPIOB->CRH |= ((0b1000) << config_bit);

				}
				else if (mode == GPIO_OUTPUT){
					//10mhz output mode, push-pull
					GPIOB->CRH &= ~((0b1111) << config_bit);
					GPIOB->CRH |= ((0b0001) << config_bit);					
				}
				else if (mode == AFIO_OUTPUT){
					GPIOB->CRH &= ~((0b1111) << config_bit);
					GPIOB->CRH |= ((0b1010) << config_bit);					
				}
				else if (mode == AFIO_OPEN_DRAIN){
					GPIOB->CRH &= ~((0b1111) << config_bit);
					GPIOB->CRH |= ((0b1110) << config_bit);					
				}
			}
			break;	
			
			
		case GPIO_C:
			// Case 1: GPIO_Pin is less than 8
			if(GPIO_Pin < 8){	
				uint8_t config_bit = (GPIO_Pin * 4);
				
	      		if(mode == GPIO_INPUT){
					GPIOC->CRL &= ~((0b1111) << config_bit);
					GPIOC->CRL |= ((0b1000) << config_bit);

				}
				else if (mode == GPIO_OUTPUT){
					//10mhz output mode, push-pull
					GPIOC->CRL &= ~((0b1111) << config_bit);
					GPIOC->CRL |= ((0b0001) << config_bit);					
				}
				else if (mode == AFIO_OUTPUT){
					GPIOC->CRL &= ~((0b1111) << config_bit);
					GPIOC->CRL |= ((0b1010) << config_bit);					
				}
				else if (mode == AFIO_OPEN_DRAIN){
					GPIOC->CRL &= ~((0b1111) << config_bit);
					GPIOC->CRL |= ((0b1110) << config_bit);					
				}
			}
			
			// Case 2: GPIO_Pin is 8 or bigger
			else if ((GPIO_Pin >= 8) & (GPIO_Pin < 16)){
				uint8_t config_bit = 4 * (GPIO_Pin - 8);
				
	      		if(mode == GPIO_INPUT){
					GPIOC->CRH &= ~((0b1111) << config_bit);
					GPIOC->CRH |= ((0b1000) << config_bit);

				}
				else if (mode == GPIO_OUTPUT){
					//10mhz output mode, push-pull
					GPIOC->CRH &= ~((0b1111) << config_bit);
					GPIOC->CRH |= ((0b0001) << config_bit);					
				}
				else if (mode == AFIO_OUTPUT){
					GPIOC->CRH &= ~((0b1111) << config_bit);
					GPIOC->CRH |= ((0b1010) << config_bit);					
				}
				else if (mode == AFIO_OPEN_DRAIN){
					GPIOC->CRH &= ~((0b1111) << config_bit);
					GPIOC->CRH |= ((0b1110) << config_bit);					
				}
			}
			break;
	}
}

/**
 * @brief Set selected GPIO pin to high state.
 * 
 * @param GPIO_Port Target GPIO port.
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 * @param GPIO_Pin Target GPIO pin.
 */
void GPIO_Set(uint8_t GPIO_Port, uint8_t GPIO_Pin){
	switch (GPIO_Port){
		case GPIO_A: 
			GPIOA->BSRR |= (1 << GPIO_Pin);
			break;
		
		case GPIO_B:
			GPIOB->BSRR |= (1 << GPIO_Pin);
			break;
		
		case GPIO_C:
			GPIOC->BSRR |= (1 << GPIO_Pin);
			break;		

		case GPIO_D:
			GPIOD->BSRR |= (1 << GPIO_Pin);
			break;
		
	}
}

/**
 * @brief Set selected GPIO pin to low state.
 * 
 * @param GPIO_Port Target GPIO port.
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 * @param GPIO_Pin Target GPIO pin.
 */
void GPIO_Reset(uint8_t GPIO_Port, uint8_t GPIO_Pin){
	switch (GPIO_Port){
		case GPIO_A: 
			GPIOA->BSRR |= (1 << (GPIO_Pin + 16));
			break;
		
		case GPIO_B:
			GPIOB->BSRR |= (1 << (GPIO_Pin + 16));
			break;
		
		case GPIO_C:
			GPIOC->BSRR |= (1 << (GPIO_Pin + 16));
			break;		

		case GPIO_D:
			GPIOD->BSRR |= (1 << (GPIO_Pin + 16));
			break;
		
	}
}

/**
 * @brief Toggle the state of selected GPIO pin
 * 
 * @param GPIO_Port Target GPIO port.
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 * @param GPIO_Pin Target GPIO pin.
 */
void GPIO_Toggle(uint8_t GPIO_Port, uint8_t GPIO_Pin){
    switch (GPIO_Port){
			case GPIO_A:
				{
						uint32_t value = GPIOA->IDR & (1 << GPIO_Pin); //read gpio input data reg
						if (value == 0){
							GPIOA->BSRR |= (1 << GPIO_Pin); //set pin when its state is low
						}
						else if (value != 0){
							GPIOA->BSRR |= (1 << (GPIO_Pin + 16)); 	//reset pin when its state is high
						}
						
				}
				break; // End the case
				
			case GPIO_B:
				{
						uint32_t value = GPIOB->IDR & (1 << GPIO_Pin); //read gpio input data reg
						if (value == 0){
							GPIOB->BSRR |= (1 << GPIO_Pin); //set pin when its state is low
						}
						else if (value != 0){
							GPIOB->BSRR |= (1 << (GPIO_Pin + 16)); 	//reset pin when its state is high
						}
						
				}
				break; // End the case			
				
			case GPIO_C:
				{
						uint32_t value = GPIOC->IDR & (1 << GPIO_Pin); //read gpio input data reg
						if (value == 0){
							GPIOC->BSRR |= (1 << GPIO_Pin); //set pin when its state is low
						}
						else if (value != 0){
							GPIOC->BSRR |= (1 << (GPIO_Pin + 16)); 	//reset pin when its state is high
						}
						
				}
				break; // End the case	
        
    }
}

/**
 * @brief Pull selected GPIO pin up or down
 * 
 * @param GPIO_Port Target GPIO port.
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 * @param GPIO_Pin Target GPIO pin.
 * @param pullMode Pull up or down
 * 	@arg GPIO_PIN_PULLDOWN
 * 	@arg GPIO_PIN_PULLUP
 */
void GPIO_PullUpDown(uint8_t GPIO_Port,uint8_t GPIO_Pin, bool pullMode){
		switch(GPIO_Port){
			case GPIO_A:
				if (pullMode == GPIO_PIN_PULLDOWN)	GPIOA->ODR &= ~(1 << GPIO_Pin);
				else if (pullMode == GPIO_PIN_PULLUP) GPIOA->ODR |= (1 << GPIO_Pin);			
				break;
			
			case GPIO_B:
				if (pullMode == GPIO_PIN_PULLDOWN)	GPIOB->ODR &= ~(1 << GPIO_Pin);
				else if (pullMode == GPIO_PIN_PULLUP) GPIOB->ODR |= (1 << GPIO_Pin);			
				break;			

			case GPIO_C:
				if (pullMode == GPIO_PIN_PULLDOWN)	GPIOC->ODR &= ~(1 << GPIO_Pin);
				else if (pullMode == GPIO_PIN_PULLUP) GPIOC->ODR |= (1 << GPIO_Pin);			
				break;				
		}
}

/**
 * @brief Read state of a GPIO pin
 * 
 * @param GPIO_Port Target GPIO port.
 * 	@arg GPIO_A
 * 	@arg GPIO_B
 * 	@arg GPIO_C
 * @param GPIO_Pin Target GPIO pin.
 * @return uint8_t State of selected GPIO pin
 */
uint8_t GPIO_ReadPin(uint8_t GPIO_Port, uint8_t GPIO_Pin){
		switch(GPIO_Port){
			case GPIO_A:
				return GPIOA->IDR & (1 << GPIO_Pin);
				break;
			
			case GPIO_B:
				return GPIOB->IDR & (1 << GPIO_Pin);			
				break;			

			case GPIO_C:
				return GPIOC->IDR & (1 << GPIO_Pin);		
				break;				
		}	
		
		return 0;
}