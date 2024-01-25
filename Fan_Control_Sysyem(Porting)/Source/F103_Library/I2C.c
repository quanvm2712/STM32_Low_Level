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


void I2C_Enable(I2C_TypeDef* I2Cx){
    I2Cx->CR1 |= (1UL << 0UL);
}

I2C_Status I2C_GenerateStartCondition(I2C_TypeDef* I2Cx){
    I2C_Status status = I2C_OK;
    uint32_t Timeout = UINT32_MAX;
    uint32_t TimeoutCount = 0;

    I2C_Enable(I2Cx);

    I2Cx->CR1 |= (1UL << 8UL);  //Generate start condition
    uint8_t StartConditionStatus;

    do{ 
        StartConditionStatus = (I2Cx->SR1 & (1UL << 0UL));
        TimeoutCount++;
    }while((!StartConditionStatus) && (TimeoutCount<=Timeout)); //Wait until SB is set or until Timeout is reached

    if(!StartConditionStatus){
        status = I2C_ERROR;  //Set error flag to error if SB bit is not set
        return status;
    }

    return status;
}


/**
 * @brief 
 * 
 * @param I2Cx 
 * @param ClockFrequency 
 */
void I2C_SetClockFrequency(I2C_TypeDef* I2Cx, uint8_t ClockFrequency){
    if(ClockFrequency >= 2 && ClockFrequency <= 50){
        I2Cx->CR2 &= ~(0b111111 << 0UL);  //Reset all FREQ bits
        I2Cx->CR2 |= (ClockFrequency << 0UL);  
    }
     
}

/**
 * @brief 
 * 
 * @param I2Cx 
 * @param MasterMode 
 */
void I2C_MasterModeSelect(I2C_TypeDef* I2Cx, _Bool MasterMode){
    I2Cx->CCR &= ~(1UL << 15UL);
    I2Cx->CCR |= MasterMode << 15UL;
}


/**
 * @brief 
 * 
 * @param I2Cx 
 */
void I2C_SetCCRValue(I2C_TypeDef* I2Cx, uint16_t CCRValue){
    I2Cx->CCR &= ~(0b111111111111 < 0UL);  //Reset all CCR bits
    I2Cx->CCR |= (CCRValue << 0UL);
}


/**
 * @brief 
 * 
 * @param I2Cx 
 * @param TRISEValue 
 */
void I2C_SetTRISEValue(I2C_TypeDef* I2Cx, uint8_t TRISEValue){
    I2Cx->TRISE = TRISEValue;
}


/**
 * @brief Configure I2C clock for standard mode(100kHz)
 * 
 * @param I2Cx 
 */
void I2C_ClockConfig(I2C_TypeDef* I2Cx){
    I2C_MasterModeSelect(I2Cx, I2C_MASTERMODE_SM);  //I2C SM mode
    I2C_SetClockFrequency(I2Cx, 8); //8MHz input clock frequency
    I2C_SetCCRValue(I2Cx, 40); //Set CCR bits to generate 100kHz frequency for CLK line
    I2C_SetTRISEValue(I2Cx, 9);  //CLK maximum rise time is 1ms
}

/**
 * @brief 
 * 
 * @param I2Cx 
 * @param isEnabled 
 */
void I2C_ConfigureEnableAcknowledge(I2C_TypeDef* I2Cx, _Bool isEnabled){
    I2Cx->CR1 &= ~(1UL << 10UL); //Reset ACK bit
    I2Cx->CR1 |= (isEnabled << 10UL); 
}


/**
 * @brief 
 * 
 * @param I2Cx 
 * @param isRemapEnabled 
 * @param I2C_SpeedMode 
 */
void I2C_Init(I2C_TypeDef* I2Cx, _Bool isRemapEnabled, uint8_t I2C_SpeedMode){
    I2C_EnableClock(I2Cx); 

    I2C_IOConfig(I2Cx, isRemapEnabled);
    I2C_ClockConfig(I2Cx);
    I2C_ConfigureEnableAcknowledge(I2Cx, I2C_ACKNOWLEDGE_ENABLE);

    I2C_Enable(I2Cx);
}

I2C_Status I2C_TransmitSlaveAddress(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddress){
    I2C_Status status = I2C_OK;
    uint32_t Timeout = UINT32_MAX;
    uint32_t TimeoutCount = 0;

    I2C_GenerateStartCondition(I2Cx);

    uint16_t dummy = I2Cx->SR1;  //Dummy read for SR1 register
    I2Cx->DR = (I2CSlaveAddress << 1UL);  //Write address of slave device to I2C bus

    /**Check if ADDR flag is set*/
    uint8_t ADDRStatus;
    do{
        ADDRStatus = (I2Cx->SR1 & (1UL << 1UL)); //Get status of ADDR bit
        TimeoutCount++;
    }while(!ADDRStatus && (TimeoutCount <= Timeout));   //Wait until ADDR bit is set or until timeout is reached

    if(!ADDRStatus){
        status = I2C_ERROR;  //Set I2C status flag to ERROR if ADDR bit is not set
        return status;
    }

    //Dummy read to SR1 and SR2 to clear ADDR
    dummy = I2Cx->SR1;  
    dummy = I2Cx->SR2;

    /**Check if ADDR flag is reset*/
    TimeoutCount = 0;
    do{
        ADDRStatus = (I2Cx->SR1 & (1UL << 1UL)); //Get status of ADDR bit
        TimeoutCount++;
    }while(ADDRStatus && (TimeoutCount <= Timeout));   //Wait until ADDR bit is reset or until timeout is reached

    if(ADDRStatus){
        status = I2C_ERROR; //Set I2C status flag to ERROR if ADDR bit is set
        return status;
    }    

    return status;
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
I2C_Status I2C_TransmitData(I2C_TypeDef* I2Cx, uint8_t SlaveAddress, uint8_t* data, uint16_t DataSize){
    I2C_Status status = I2C_OK;
    uint32_t Timeout= UINT32_MAX;
    uint32_t TimeoutCount = 0;

    status = I2C_TransmitSlaveAddress(I2Cx, SlaveAddress);
    if(status != I2C_OK){
        return status;
    }

    
}
