#ifndef __AHT20_H
#define __AHT20_H

#define AHT20_I2C_ADDRESS 0x38

#include "I2C.h"
#include "Delay.h"

typedef enum{
    AHT20_OK = 0,
    AHT20_ERROR = 1
}AHT20_Status;

void AHT20_Init(I2C_TypeDef* I2Cx);
AHT20_Status AHT20_GetSensorData(I2C_TypeDef* I2Cx, uint8_t* RX_Buffer);
AHT20_Status AHT20_SendTriggerMeasurementCommand(I2C_TypeDef* I2Cx);


#endif  //__AHT2_20