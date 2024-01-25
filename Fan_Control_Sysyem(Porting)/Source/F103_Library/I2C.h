#ifndef __I2C_H
#define __I2C_H

#include "stm32f1xx.h"
#include "GPIO.h"

//I2C IO remapping
#define I2C1_REMAPPING_DISABLE      0
#define I2C1_REMAPPING_ENABLE       1

//I2C master mode
#define I2C_MASTERMODE_SM           0
#define I2C_MASTERMODE_FM           1

//I2C acknowledge enable
#define I2C_ACKNOWLEDGE_DISABLE     0
#define I2C_ACKNOWLEDGE_ENABLE      1

//I2C Operation
#define I2C_WRITE                   0
#define I2C_READ                    1


typedef enum{
    I2C_OK = 0x00U,
    I2C_ERROR = 0x01U,
    I2C_TIMEOUT = 0x02
}I2C_Status;


void I2C_EnableClock(I2C_TypeDef* I2Cx);
void I2C_IOConfig(I2C_TypeDef* I2Cx, _Bool isRemapEnabled);
void I2C_Enable(I2C_TypeDef* I2Cx);
void I2C_SetClockFrequency(I2C_TypeDef* I2Cx, uint8_t ClockFrequency);
void I2C_MasterModeSelect(I2C_TypeDef* I2Cx, _Bool MasterMode);
void I2C_SetCCRValue(I2C_TypeDef* I2Cx, uint16_t CCRValue);
void I2C_SetTRISEValue(I2C_TypeDef* I2Cx, uint8_t TRISEValue);
void I2C_ClockConfig(I2C_TypeDef* I2Cx);

void I2C_Init(I2C_TypeDef* I2Cx, _Bool isRemapEnabled, uint8_t I2C_MasterMode);
I2C_Status I2C_GenerateStartCondition(I2C_TypeDef* I2Cx);
I2C_Status I2C_TransmitSlaveAddress(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddress, _Bool I2C_Operation);
I2C_Status I2C_TransmitData(I2C_TypeDef* I2Cx, uint8_t SlaveAddress, uint8_t* data, uint16_t DataSize);

#endif  //__I2C_H