/**
 * @file AHT20.c
 * @author Vo Minh Quan
 * @brief STM32F1x library for AHT20 sensor
 * @version 0.1
 * @date 2024-01-26
 * 
 */

#include "AHT20.h"

AHT20_Status AHT20_SendInitializeCommand(I2C_TypeDef* I2Cx){
    uint8_t AHT20_InitCommand[3] = {0xBE, 0x08, 0x00};
    I2C_Status I2CStatus = I2C_TransmitData(I2Cx, AHT20_I2C_ADDRESS, AHT20_InitCommand, 3);    

    if(I2CStatus != I2C_OK) return AHT20_ERROR;
    return AHT20_OK;
}

AHT20_Status AHT20_SendTriggerMeasurementCommand(I2C_TypeDef* I2Cx){
    uint8_t AHT20_TriggerMeasurementCommand[3] = {0xAC, 0x33, 0x00};
    I2C_Status I2CStatus = I2C_TransmitData(I2Cx, AHT20_I2C_ADDRESS, AHT20_TriggerMeasurementCommand, 3);

    if(I2CStatus != I2C_OK) return AHT20_ERROR;

    return AHT20_OK;
}

void AHT20_Init(I2C_TypeDef* I2Cx){
    delay_ms(40);

    AHT20_Reset(I2Cx);
    
    uint8_t InitCommand[3] = {0xBE, 0x08, 0x00};
    I2C_TransmitData(I2Cx, AHT20_I2C_ADDRESS, InitCommand, 3);
}

void AHT20_Reset(I2C_TypeDef* I2Cx){
    uint8_t AHT20_ResetCommand = 0b10111010;
    I2C_TransmitData(I2Cx, AHT20_I2C_ADDRESS, &AHT20_ResetCommand, 1);
}

AHT20_Status AHT20_GetSensorSignal(I2C_TypeDef* I2Cx, uint8_t* RX_Buffer){
    AHT20_Status status = I2C_OK;
    AHT20_SendTriggerMeasurementCommand(I2Cx);
    delay_ms(80);  //Wait for 80ms to wait for the measurement to be completed

    do{
        status = I2C_ReadData(I2Cx, AHT20_I2C_ADDRESS, RX_Buffer, 6);
    }while((RX_Buffer[0] & (1UL << 7UL)));  //Wait until AHT20 is not busy


    return status;
}

AHT20_Status AHT20_GetSensorData(I2C_TypeDef* I2Cx, uint8_t* Temperature, uint8_t* Humidity){
   uint8_t SensorSignal[6]; 

   AHT20_GetSensorSignal(I2Cx, SensorSignal);
   //if(status != AHT20_OK) return AHT20_ERROR;

   int rawTemperature = SensorSignal[5] | (SensorSignal[4] << 8) | ((SensorSignal[3] & 0xF) << 16);
   int rawHumidity = ((SensorSignal[1] << 16) | (SensorSignal[2] << 8) | SensorSignal[3]) >> 4;

   *Temperature = ((rawTemperature *200)/1048576) - 50;
   *Humidity = (rawHumidity * 100) / 1048576;
   return AHT20_OK;
}