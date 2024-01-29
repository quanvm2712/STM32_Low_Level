#include "DHT11.h"


void DHT11_SendStartSignal(DHT11_Instance DHT11){
	GPIO_Init(DHT11.GPIO_Port, DHT11.GPIO_Pin, GPIO_OUTPUT);
	
	GPIO_Reset(DHT11.GPIO_Port, DHT11.GPIO_Pin);
	delay_ms(18);
	
	GPIO_Set(DHT11.GPIO_Port, DHT11.GPIO_Pin);
	delay_us(20);
	
	
	/*Process signal from DHT11*/
	GPIO_Init(DHT11.GPIO_Port, DHT11.GPIO_Pin, GPIO_INPUT);
	//Wait until DHT11's start signal end
	uint8_t pin_state;
	do{
		pin_state = GPIO_ReadPin(DHT11.GPIO_Port, DHT11.GPIO_Pin);
	}while(!pin_state);
	
	
	//Wait for DHT11 preparation to send data
	do{
		pin_state = GPIO_ReadPin(DHT11.GPIO_Port, DHT11.GPIO_Pin);
	}while(pin_state);		
}


void DHT11_GetSignal(DHT11_Instance DHT11, uint8_t* data){
	DHT11_SendStartSignal(DHT11);
	
	for(int i=0; i<5; i++){
		uint8_t data_byte = 0;
		for(int j=0; j<8; j++){
			while(!(GPIO_ReadPin(DHT11.GPIO_Port, DHT11.GPIO_Pin)));  //Wait for next bit start signal to end
			delay_us(30);
			data_byte <<= 1;
			if(GPIO_ReadPin(DHT11.GPIO_Port, DHT11.GPIO_Pin))  data_byte |= 1;
			delay_us(45);
		}
		data[i] = data_byte;
 	}
}


void DHT11_GetValue(DHT11_Instance DHT11, uint8_t* value){
	uint8_t DHT11_Signal[5];
	DHT11_GetSignal(DHT11, DHT11_Signal);
	
	uint16_t checksum = 0;
	for(int i=0; i<4; i++){
		checksum += DHT11_Signal[i];
	}
	
	if((checksum & 0xFF) == DHT11_Signal[4]){
		value[0] = DHT11_Signal[0];  //Humidity
		value[1] = DHT11_Signal[2];	 //Temperature
	}
}