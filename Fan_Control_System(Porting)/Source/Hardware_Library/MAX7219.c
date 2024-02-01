/**
 * @file MAX7219.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief MAX7219-based display module driver for STM32F1xx microcontroller
 * @version 0.1
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "MAX7219.h"


uint8_t DigitCodes[10] = {
    0x7E, // Hex code for 0
    0x30, // Hex code for 1
    0x6D, // Hex code for 2
    0x79, // Hex code for 3
    0x33, // Hex code for 4
    0x5B, // Hex code for 5
    0x5F, // Hex code for 6
    0x70, // Hex code for 7
    0x7F, // Hex code for 8
    0x7B  // Hex code for 9
};


/**
 * @brief Send data to the module
 * 
 * @param address Address of the register to receive data
 * @param data Data to be transmitted to the selected register
 */
void MAX7219_SendData(uint8_t address, uint8_t data){
	CS_Set();
	SPI_Transmit(SPI1, &address, 1);
	SPI_Transmit(SPI1, &data, 1);
	CS_Reset();
}

/**
 * @brief Turn on the display module (The module is off after reset)
 * 
 */
void MAX7219_PowerOn(void){
	MAX7219_SendData(0x0C, 0x01);
}

/**
 * @brief Set intensity (brightness) for the module
 * 
 * @param Intensity Desired intensity (0 -> 15)
 */
void MAX7219_SetIntensity(uint8_t Intensity){
	if(Intensity < 16){
		MAX7219_SendData(0x0A, Intensity);
	}
}

/**
 * @brief Configure which digits to be displayed
 * 
 * @param ScanLimit Desired scan limit
 * 	@arg DIGIT_0_ONLY
 * 	@arg DIGIT_0_TO_1
 * 	@arg DIGIT_0_TO_2
 * 	@arg DIGIT_0_TO_3
 * 	@arg DIGIT_0_TO_4
 * 	@arg DIGIT_0_TO_5
 * 	@arg DIGIT_0_TO_6
 * 	@arg DIGIT_0_TO_7
 */
void MAX7219_SetScanLimit(uint8_t ScanLimit){
	MAX7219_SendData(0x0B, ScanLimit);
}

/**
 * @brief Clear all the registers' data
 * 
 */
void MAX7219_Clean(void){
	for(int count = 0; count <= 0xC; count++){
		MAX7219_SendData(count, 0);
	}
	MAX7219_SendData(0xF, 0);
}

/**
 * @brief Configure decode mode for the module
 * 
 * @param DecodeMode Desired decode mode
 * 	@arg DECODE_MODE_DISABLE
 * 	@arg DECODE_MODE_DIGIT_0
 * 	@arg DECODE_MODE_DIGIT_0_TO_3
 * 	@arg DECODE_MODE_DIGIT_0_TO_7
 */
void MAX7219_SetDecodeMode(uint8_t DecodeMode){
	MAX7219_SendData(0x9, DecodeMode);
}

/**
 * @brief Initialize MAX7219 display module 
 * 
 * @param Intensity Desired intensity
 * @param ScanLimit Desired scan limit
 * 	@arg DIGIT_0_ONLY
 * 	@arg DIGIT_0_TO_1
 * 	@arg DIGIT_0_TO_2
 * 	@arg DIGIT_0_TO_3
 * 	@arg DIGIT_0_TO_4
 * 	@arg DIGIT_0_TO_5
 * 	@arg DIGIT_0_TO_6
 * 	@arg DIGIT_0_TO_7
 * @param DecodeMode Desired decode mode
 * 	@arg DECODE_MODE_DISABLE
 * 	@arg DECODE_MODE_DIGIT_0
 * 	@arg DECODE_MODE_DIGIT_0_TO_3
 * 	@arg DECODE_MODE_DIGIT_0_TO_7
 */
void MAX7219_Init(uint8_t Intensity, uint8_t ScanLimit, uint8_t DecodeMode){
	MAX7219_PowerOn();
	MAX7219_Clean();
	
	MAX7219_SetIntensity(Intensity);
	MAX7219_SetScanLimit(ScanLimit);
	MAX7219_SetDecodeMode(DecodeMode);
}

/**
 * @brief Make all digits not to display
 * 
 */
void MAX7219_EmptyAllDigits(void){
	for(int i=1; i<=8; i++){
		MAX7219_SendData(i, 0);
	}
}

/**
 * @brief Print string
 * 
 * @param StringToPrint Desired string to be printed (e.g "2024")
 * @param StartPosition Position where the string start to be printed on the module
 * 	@arg DIGIT_POSITION_0
 * 	@arg DIGIT_POSITION_1
 * 	@arg DIGIT_POSITION_2
 * 	@arg DIGIT_POSITION_3
 * 	@arg DIGIT_POSITION_4
 * 	@arg DIGIT_POSITION_5
 * 	@arg DIGIT_POSITION_6
 * 	@arg DIGIT_POSITION_7	
 */
void MAX7219_PrintString(char* StringToPrint, uint8_t StartPosition){
	MAX7219_EmptyAllDigits();
	
	while(*StringToPrint){
		uint8_t digit = *(StringToPrint++) - '0';
		MAX7219_SendData(StartPosition + 1, DigitCodes[digit]);
		StartPosition--;
	}
}

/**
 * @brief Print string
 * 
 * @param StringToPrint Desired integer to be printed (e.g 2024)
 * @param StartPosition Position where the integer start to be printed on the module
 * 	@arg DIGIT_POSITION_0
 * 	@arg DIGIT_POSITION_1
 * 	@arg DIGIT_POSITION_2
 * 	@arg DIGIT_POSITION_3
 * 	@arg DIGIT_POSITION_4
 * 	@arg DIGIT_POSITION_5
 * 	@arg DIGIT_POSITION_6
 * 	@arg DIGIT_POSITION_7	
 */
void MAX7219_PrintInt(uint32_t IntToPrint, uint8_t NumOfDigits, uint8_t StartPosition){
	//MAX7219_EmptyAllDigits();

	uint8_t IntDigit[NumOfDigits];
	int8_t count = 0;
	
	//Store digits into array ()
	while(count < NumOfDigits){
		IntDigit[count++] = IntToPrint % 10;
		IntToPrint /= 10;
	}
	count = NumOfDigits - 1;
	
	while(count >= 0){
		MAX7219_SendData(StartPosition + 1, DigitCodes[IntDigit[count]]);
		count--;
		StartPosition--;
	}
	
}