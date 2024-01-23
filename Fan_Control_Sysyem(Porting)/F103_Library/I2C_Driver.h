#ifndef __I2C_DRIVER_H
#define __I2C_DRIVER_H

#include "stm32f1xx.h"
#include "gp_drive.h"



#define I2C_READ	1
#define I2C_WRITE	0

#define	I2C1_REMAP_DISABLE	0
#define	I2C1_REMAP_ENABLE		1


void I2C_init(uint8_t isRemapEnabled);
void I2C_write(uint8_t address, uint8_t *data, uint8_t dataSize);
void I2C_start(uint8_t address, uint8_t ReadWriteMode);
void I2C_data(uint8_t *data, uint8_t dataSize);
void I2C_stop(void);
void I2C_read(uint8_t address, uint8_t* data, uint8_t dataSize);
void I2C_read1(uint8_t address, uint8_t *data, uint8_t dataSize);
void I2C1_Enable_IO_Remap(uint8_t isEnabled);

#endif  //__I2C_DRIVER_H