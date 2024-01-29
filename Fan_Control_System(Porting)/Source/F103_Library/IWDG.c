/**
 * @file IWDG.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief IWDG Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-01-24
 * 
 */

#include "IWDG.h"

/**
 * @brief Set prescaler for IWDG source clock (LSI)
 * 
 * @param PrescalerValue Desired prescaler value
 */
void IWDG_SetPrescaler(uint8_t PrescalerValue){
	/*Write Key to enable modifying PR value*/
	IWDG->KR  = 0x5555;	
	
	while(IWDG->SR & (1 << 0));	//Wait until PVU flag is reset
	//IWDG->PR &= ~(0b111 << 0); //Reset PR register
	IWDG->PR |= (PrescalerValue << 0);
}

/**
 * @brief Set reload value for IWDG
 * 
 * @param ReloadValue Desired reload value
 */
void IWDG_SetReloadValue(uint16_t ReloadValue){
	/*Write Key to enable modifying PR value*/
	IWDG->KR  = 0x5555;	

	IWDG->RLR = ReloadValue;  //Set RLR register's value
}

/**
 * @brief Start the IWDG
 * 
 */
void IWDG_Start(void){
	IWDG->KR  = 0xCCCC;	
}

/**
 * @brief Reset the IWDG
 * 
 */
void IWDG_Reset(void){
	IWDG->KR  = 0xAAAA;	
}

/**
 * @brief Initialize IWDG
 * 
 * @param PrescalerValue Desired prescaler value
 * @param ReloadValue Desired reload value
 */
void IWDG_Init(uint8_t PrescalerValue, uint16_t ReloadValue){
	IWDG_Start(); 
	
	IWDG_SetPrescaler(PrescalerValue);
	IWDG_SetReloadValue(ReloadValue);
	
	IWDG_Reset();  //Reset to load reload value to specified register
}