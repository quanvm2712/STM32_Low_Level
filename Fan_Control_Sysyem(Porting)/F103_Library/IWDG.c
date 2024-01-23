#include "IWDG.h"

void IWDG_SetPrescaler(uint8_t PrescalerValue){
	/*Write Key to enable modifying PR value*/
	IWDG->KR  = 0x5555;	
	
	while(IWDG->SR & (1 << 0));	//Wait until PVU flag is reset
	//IWDG->PR &= ~(0b111 << 0); //Reset PR register
	IWDG->PR |= (PrescalerValue << 0);
}

void IWDG_SetReloadValue(uint16_t ReloadValue){
	/*Write Key to enable modifying PR value*/
	IWDG->KR  = 0x5555;	

	IWDG->RLR = ReloadValue;  //Set RLR register's value
}

void IWDG_Start(void){
	IWDG->KR  = 0xCCCC;	
}

void IWDG_Reset(void){
	IWDG->KR  = 0xAAAA;	
}

void IWDG_Init(uint8_t PrescalerValue, uint16_t ReloadValue){
	IWDG_Start();
	
	IWDG_SetPrescaler(PrescalerValue);
	IWDG_SetReloadValue(ReloadValue);
	
	IWDG_Reset();
}