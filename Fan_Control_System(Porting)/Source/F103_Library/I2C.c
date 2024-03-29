/**
 * @file I2C.c
 * @author Vo Minh Quan (quanvm198@gmail.com)
 * @brief I2C Hardware Abstraction Layer for STM32F103C8T6.
 * @version 0.1
 * @date 2024-01-25
 * 
 */

#include "I2C.h"

/**
 * @brief Enable clock for selected I2C instance
 * 
 * @param I2Cx I2C instance
 */
void I2C_EnableClock(I2C_TypeDef* I2Cx){
    if(I2Cx == I2C1){
        RCC->APB1ENR |= (1UL << 21UL);
    }
    else if(I2Cx == I2C2){
        RCC->APB1ENR |= (1UL << 22UL);
    }
}

/**
 * @brief Configure IO pins for selected I2C instance
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param isRemapEnabled Enable IO remapping (I2C1 only)
 *  @arg I2C1_REMAPPING_DISABLE
 *  @arg I2C1_REMAPPING_ENABLE
 */
void I2C_IOConfig(I2C_TypeDef* I2Cx, _Bool isRemapEnabled){
    if(I2Cx == I2C1){
        if(!isRemapEnabled){
            RCC->APB2ENR |= (1UL << 0UL); //Enable clock for AFIO register
            AFIO->MAPR &= ~(1UL << 1UL); //Disable IO remapping for I2C1
            GPIO_Init(GPIO_B, 6, AFIO_OPEN_DRAIN); 
            GPIO_Init(GPIO_B, 7, AFIO_OPEN_DRAIN);
        }
        else if(isRemapEnabled){
            RCC->APB2ENR |= (1UL << 0UL); //Enable clock for AFIO register
            AFIO->MAPR |= (1UL << 1UL); //Enable IO remapping for I2C1
            GPIO_Init(GPIO_B, 8, AFIO_OPEN_DRAIN);
            GPIO_Init(GPIO_B, 9, AFIO_OPEN_DRAIN);            
        }
    }

    else if(I2Cx == I2C2){
        GPIO_Init(GPIO_B, 10, AFIO_OPEN_DRAIN);
        GPIO_Init(GPIO_B, 11, AFIO_OPEN_DRAIN);        
    }
}

/**
 * @brief Enable selected I2C instance
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 */
void I2C_Enable(I2C_TypeDef* I2Cx){
    I2Cx->CR1 |= (1UL << 0UL);
}

/**
 * @brief Generate start signal for I2C data transmission
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @return I2C_Status Status of the operation
 */
I2C_Status I2C_GenerateStartCondition(I2C_TypeDef* I2Cx, uint8_t Timeout){
    I2C_Status status = I2C_OK;
    uint32_t lastTicks;

    I2C_Enable(I2Cx);

    I2Cx->CR1 |= (1UL << 8UL);  //Generate start condition
    uint8_t StartConditionStatus;

    lastTicks = ARM_GetTick();
    do{ 
        StartConditionStatus = (I2Cx->SR1 & (1UL << 0UL));
    }while((!StartConditionStatus) && ((ARM_GetTick() - lastTicks) < Timeout)); //Wait until SB is set or until Timeout is reached

    if(!StartConditionStatus){
        status = I2C_ERROR;  //Set error flag to error if SB bit is not set
        return status;
    }

    return status;
}

/**
 * @brief Generate stop signal for ending data transmission
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 */
void I2C_GenerateStopCondition(I2C_TypeDef* I2Cx){
    I2Cx->CR1 |= (1UL << 9UL);
}

/**
 * @brief Configure I2C input clock frequency.
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param ClockFrequency I2C input clock frequency (2 <= ClockFrequency <= 50) 
 */
void I2C_SetClockFrequency(I2C_TypeDef* I2Cx, uint8_t ClockFrequency){
    if(ClockFrequency >= 2 && ClockFrequency <= 50){
        I2Cx->CR2 &= ~(0b111111 << 0UL);  //Reset all FREQ bits
        I2Cx->CR2 |= (ClockFrequency << 0UL);  
    }
}

/**
 * @brief Configure I2C standard or fast mode
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param MasterMode I2C standard or fast mode
 *  @arg I2C_MASTERMODE_SM
 *  @arg I2C_MASTERMODE_FM
 */
void I2C_MasterModeSelect(I2C_TypeDef* I2Cx, _Bool MasterMode){
    I2Cx->CCR &= ~(1UL << 15UL);
    I2Cx->CCR |= MasterMode << 15UL;
}


/**
 * @brief Set CCR value of selected I2C instance
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param CCRValue Value to write to CCR bits
 */
void I2C_SetCCRValue(I2C_TypeDef* I2Cx, uint16_t CCRValue){
    I2Cx->CCR &= ~(0b111111111111 < 0UL);  //Reset all CCR bits
    I2Cx->CCR |= (CCRValue << 0UL);
}


/**
 * @brief Set TRISE value of selected I2C instance
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param TRISEValue Value to write to TRISE register
 */
void I2C_SetTRISEValue(I2C_TypeDef* I2Cx, uint8_t TRISEValue){
    I2Cx->TRISE = TRISEValue;
}


/**
 * @brief Configure I2C clock for standard mode(100kHz)
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 */
void I2C_ClockConfig(I2C_TypeDef* I2Cx){
    I2C_MasterModeSelect(I2Cx, I2C_MASTERMODE_SM);  //I2C SM mode
    I2C_SetClockFrequency(I2Cx, 8); //8MHz input clock frequency
    I2C_SetCCRValue(I2Cx, 40); //Set CCR bits to generate 100kHz frequency for CLK line
    I2C_SetTRISEValue(I2Cx, 9);  //CLK maximum rise time is 1ms
}

/**
 * @brief Generate ACK signal when receiving data
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param isEnabled Enable or disable.
 *  @arg I2C_ACKNOWLEDGE_DISABLE
 *  @arg I2C_ACKNOWLEDGE_ENABLE
 */
void I2C_EnableAcknowledge(I2C_TypeDef* I2Cx, _Bool isEnabled){
    I2Cx->CR1 &= ~(1UL << 10UL); //Reset ACK bit
    I2Cx->CR1 |= (isEnabled << 10UL); 
}


/**
 * @brief Initialize selected I2C instance.
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param isRemapEnabled Enable IO remapping (I2C1 only)
 *  @arg I2C1_REMAPPING_DISABLE
 *  @arg I2C1_REMAPPING_ENABLE
 * @param MasterMode I2C standard or fast mode
 *  @arg I2C_MASTERMODE_SM
 *  @arg I2C_MASTERMODE_FM 
 */
void I2C_Init(I2C_TypeDef* I2Cx, _Bool isRemapEnabled, uint8_t I2C_MasterMode){
    I2C_EnableClock(I2Cx); 

    I2C_IOConfig(I2Cx, isRemapEnabled);
    I2C_MasterModeSelect(I2Cx, I2C_MASTERMODE_SM); //Set standard mode
    I2C_ClockConfig(I2Cx);

    I2C_Enable(I2Cx);
    
}

/**
 * @brief Slave address transmission
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param I2CSlaveAddress Address of I2C slave device
 * @param I2C_Operation Read or write operation
 *  @arg I2C_READ
 *  @arg I2C_WRITE
 * 
 * @return I2C_Status 
 */
I2C_Status I2C_TransmitSlaveAddress(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddress, _Bool I2C_Operation, uint8_t Timeout){
    I2C_Status status = I2C_OK;
    uint32_t lastTicks = 0;

    if(I2C_GenerateStartCondition(I2Cx, 50) != I2C_OK){
        return I2C_ERROR;
    }

    uint16_t dummy = I2Cx->SR1;  //Dummy read for SR1 register
    I2Cx->DR = (I2CSlaveAddress << 1UL) | I2C_Operation;  //Write address of slave device to I2C bus

    /**Check if ADDR flag is set*/
    uint8_t ADDRStatus;
    lastTicks = ARM_GetTick();
    do{
        ADDRStatus = (I2Cx->SR1 & (1UL << 1UL)); //Get status of ADDR bit
    }while(!ADDRStatus && ((ARM_GetTick() - lastTicks) < Timeout));   //Wait until ADDR bit is set or until timeout is reached

    if(!ADDRStatus){
        status = I2C_ERROR;  //Set I2C status flag to ERROR if ADDR bit is not set
        return status;
    }

    //Dummy read to SR1 and SR2 to clear ADDR
    dummy = I2Cx->SR1;  
    dummy = I2Cx->SR2;

    /**Check if ADDR flag is reset*/
    lastTicks = ARM_GetTick();
    do{
        ADDRStatus = (I2Cx->SR1 & (1UL << 1UL)); //Get status of ADDR bit
    }while(ADDRStatus && ((ARM_GetTick() - lastTicks) < Timeout));   //Wait until ADDR bit is reset or until timeout is reached

    if(ADDRStatus){
        status = I2C_ERROR; //Set I2C status flag to ERROR if ADDR bit is set
        return status;
    }    

    return status;
}

/**
 * @brief Transmit data to selected I2C slave
 * 
 * @param I2Cx I2C instance
 *  @arg I2C1
 *  @arg I2C2
 * @param SlaveAddress Address of I2C slave device
 * @param data Data to be transmitted
 * @param DataSize Number of bytes to be transmitted
 * 
 * @return I2C_Status 
 */
I2C_Status I2C_TransmitData(I2C_TypeDef* I2Cx, uint8_t SlaveAddress, uint8_t* data, uint16_t DataSize, uint8_t Timeout){
    I2C_Status status = I2C_OK;
    uint32_t lastTicks;

    status = I2C_TransmitSlaveAddress(I2Cx, SlaveAddress, I2C_WRITE, 50);
    if(status != I2C_OK){
        return status;
    }


    uint8_t TXE_Status;
    //Write data to transmit buffer
    for(int dataCount=0; dataCount < DataSize; dataCount++){
        //Wait until TxE is set (indicate transmit buffer is empty)
        lastTicks = ARM_GetTick();
        do{
            TXE_Status = (I2Cx->SR1 & (1UL << 7UL));  //Read TXE flag
        }while((!TXE_Status) && ((ARM_GetTick() - lastTicks) < Timeout)); //Wait until TXE flag is set or Timeout is reached
        if(!TXE_Status) return I2C_ERROR;

        I2Cx->DR = data[dataCount]; //Write data to DR
    }

    //Wait until TxE is set (indicate transmit buffer is empty)
    lastTicks = ARM_GetTick();
    do{
        TXE_Status = (I2Cx->SR1 & (1UL << 7UL));  //Read TXE flag
    }while((!TXE_Status) && ((ARM_GetTick() - lastTicks) < Timeout)); //Wait until TXE flag is set or Timeout is reached
    if(!TXE_Status) return I2C_ERROR;

    I2C_GenerateStopCondition(I2Cx);
    return I2C_OK;
}


/**
 * @brief 
 * 
 * @param I2Cx 
 * @param SlaveAddress 
 * @param data 
 * @param DataSize 
 * @return I2C_Status 
 */
I2C_Status I2C_ReadData(I2C_TypeDef* I2Cx, uint8_t SlaveAddress, uint8_t* RX_Data, uint16_t DataSize, uint8_t Timeout){
    I2C_Status status = I2C_OK;
    uint32_t lastTicks;

    //I2C_EnableAcknowledge(I2Cx, I2C_ACKNOWLEDGE_ENABLE);
    
    //Transmit slave address with READ operation
    status = I2C_TransmitSlaveAddress(I2Cx, SlaveAddress, I2C_READ, 50);
    if(status != I2C_OK){
        return status;
    }    

    //Read I2C data
    if(DataSize == 1){
        I2C_GenerateStopCondition(I2Cx);

        //Wait for RXNE to set
        uint16_t RXNE_Status;
        lastTicks = ARM_GetTick();
        do{
            RXNE_Status = (I2Cx->SR1 & (1UL << 6UL));  //Get status of RXNE bit
        }while(!RXNE_Status && ((ARM_GetTick() - lastTicks) < Timeout));  //Wait until RXNE flag is set or timeout is reached
        if(!RXNE_Status) return I2C_ERROR;  //Return error if RXNE flag is not set within timeout

        *RX_Data = I2Cx->DR; //Read received data and clear RxNE
    }

    else if(DataSize == 2){
        I2C_EnableAcknowledge(I2Cx, I2C_ACKNOWLEDGE_DISABLE); //Acknowledge disable after ADDR is reset

        //Wait until BTF bit is set
        uint16_t BTF_Status;
        lastTicks = ARM_GetTick();
        do{
            BTF_Status = (I2Cx->SR1 & (1UL << 2UL)); //Get status of BTF bit
        }while(!BTF_Status && ((ARM_GetTick() - lastTicks) < Timeout)); //Wait until BTF flag is set or timeout is reached
        if(!BTF_Status) return I2C_ERROR;

        //Generate stop condition
        I2C_GenerateStopCondition(I2Cx);
    }

    else if(DataSize > 2){
        I2C_EnableAcknowledge(I2Cx, I2C_ACKNOWLEDGE_ENABLE);
        for(int dataCount = 0; dataCount < DataSize; dataCount++){
            //When dataCount does not reach the last 3 bytes
            if(dataCount < (DataSize - 3)){
                /*Wait for RXNE to set*/
                uint16_t RXNE_Status;
                lastTicks = ARM_GetTick();
                do{
                    RXNE_Status = (I2Cx->SR1 & (1UL << 6UL));  //Get status of RXNE bit
                }while(!RXNE_Status && ((ARM_GetTick() - lastTicks) < Timeout));  //Wait until RXNE flag is set or timeout is reached
                if(!RXNE_Status) return I2C_ERROR;  //Return error if RXNE flag is not set within timeout       

                /*Get data from DR register */
                RX_Data[dataCount] = I2Cx->DR;
            }

            //When dataCount is within the last 3 bytes
            else{
                /*Wait until BTF bit is set*/
                uint16_t BTF_Status;
                lastTicks = ARM_GetTick();
                do{
                    BTF_Status = (I2Cx->SR1 & (1UL << 2UL)); //Get status of BTF bit
                }while(!BTF_Status && ((ARM_GetTick() - lastTicks) < Timeout)); //Wait until BTF flag is set or timeout is reached
                if(!BTF_Status) return I2C_ERROR; 


                /*Disable ACK and read data N-2*/
                I2C_EnableAcknowledge(I2Cx, I2C_ACKNOWLEDGE_DISABLE);
                RX_Data[dataCount++] = I2Cx->DR;

                /*Generate stop condition and read data N-1 */
                I2C_GenerateStopCondition(I2Cx);
                RX_Data[dataCount++] = I2Cx->DR;

                /**Wait until RxNE is set and read data N*/
                //Wait for RXNE to set
                uint16_t RXNE_Status;
                lastTicks = ARM_GetTick();
                do{
                    RXNE_Status = (I2Cx->SR1 & (1UL << 6UL));  //Get status of RXNE bit
                }while(!RXNE_Status && ((ARM_GetTick() - lastTicks) < Timeout));  //Wait until RXNE flag is set or timeout is reached
                if(!RXNE_Status) return I2C_ERROR;  //Return error if RXNE flag is not set within timeout  
 
                RX_Data[dataCount] = I2Cx->DR;
            }
        }
    }

    return I2C_OK;
}