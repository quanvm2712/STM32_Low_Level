#include "ADC.h"

void ADC_EnableClock(ADC_TypeDef* ADCx){
    if(ADCx == ADC1){
        RCC->APB2ENR |= (1UL << 9UL);
    }
    else if(ADCx==ADC2){
        RCC->APB2ENR |= (1UL << 10UL);
    }
}

void ADC_PowerOn(ADC_TypeDef* ADCx){
    ADCx->CR2 |= (1UL << 0UL); 
}

void ADC_SetPrescaler(uint8_t ADCPrescaler){
    RCC->CFGR &= ~(0b11 << 14UL);
    RCC->CFGR |= ADCPrescaler << 14UL;
}

void ADC_SetConversionMode(ADC_TypeDef* ADCx, _Bool ConversionMode){
    ADCx->CR2 &= ~(1UL << 1UL);
    ADCx->CR2 |= (ConversionMode << 1UL);
}

void ADC_SetScanMode(ADC_TypeDef* ADCx, _Bool ScanMode){
    ADCx->CR1 &= ~(1UL << 8UL);
    ADCx->CR1 |= (ScanMode << 8UL);
}

void ADC_EnableDiscontinuousMode(ADC_TypeDef* ADCx, _Bool isEnabled){
    ADCx->CR1 &= ~(1UL << 11UL);
    ADCx->CR1 |= (isEnabled << 11UL);
}

void ADC_Calibrate(ADC_TypeDef* ADCx){
    //Only calibrate after ADC is on
    uint8_t Timeout = 50; //50ms Timeout
    uint32_t lastTicks;

    if(ADCx->CR2 & (1UL << 0UL)){
        delay_us(10); //Ensure ADC is on for at least 2 clock cycle
        ADCx->CR2 |= (1UL << 2UL); //Enable calibration
        lastTicks = ARM_GetTick();
        while(ADCx->CR2 & (1UL << 2UL)  &&  ((ARM_GetTick() - lastTicks) < Timeout)){}; //Wait until ADC calib is complete 
    }
}

void ADC_SetDataAlignment(ADC_TypeDef* ADCx, _Bool Alignment){
    ADCx->CR2 &= ~(1UL << 11UL);
    ADCx->CR2 |= (Alignment << 11UL);
}

void ADC_SetSampleTime(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t SampleTime){
    switch (ADC_Channel)
    {
    case ADC_CHANNEL_0:
        ADCx->SMPR2 &= ~(0b111UL << 0UL);
        ADCx->SMPR2 |= (SampleTime << 0UL);
        break;

    case ADC_CHANNEL_1:
        ADCx->SMPR2 &= ~(0b111UL << 3UL);
        ADCx->SMPR2 |= (SampleTime << 3UL);
        break;
    case ADC_CHANNEL_2:
        ADCx->SMPR2 &= ~(0b111UL << 6UL);
        ADCx->SMPR2 |= (SampleTime << 6UL);
        break;

    case ADC_CHANNEL_3:
        ADCx->SMPR2 &= ~(0b111UL << 9UL);
        ADCx->SMPR2 |= (SampleTime << 9UL);
        break;
    case ADC_CHANNEL_4:
        ADCx->SMPR2 &= ~(0b111UL << 12UL);
        ADCx->SMPR2 |= (SampleTime << 12UL);
        break;
    case ADC_CHANNEL_5:
        ADCx->SMPR2 &= ~(0b111UL << 15UL);
        ADCx->SMPR2 |= (SampleTime << 15UL);
        break;
    case ADC_CHANNEL_6:
        ADCx->SMPR2 &= ~(0b111UL << 18UL);
        ADCx->SMPR2 |= (SampleTime << 18UL);
        break;
    case ADC_CHANNEL_7:
        ADCx->SMPR2 &= ~(0b111UL << 21UL);
        ADCx->SMPR2 |= (SampleTime << 21UL);
        break;
    case ADC_CHANNEL_8:
        ADCx->SMPR2 &= ~(0b111UL << 24UL);
        ADCx->SMPR2 |= (SampleTime << 24UL);
        break;
    case ADC_CHANNEL_9:
        ADCx->SMPR2 &= ~(0b111UL << 27UL);
        ADCx->SMPR2 |= (SampleTime << 27UL);
        break;
    default:
        break;
    }
}

void ADC_SetNumberOfConversion(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t NumberOfConversion){
    //Config number of conversion time
    ADCx->SQR1 &= ~(0b1111 << 20UL);
    ADCx->SQR1 |= (NumberOfConversion << 20UL);


    switch (NumberOfConversion)
    {
        case ADC_CONVERSION_1_TIME:
            ADCx->SQR3 &= ~(0b11111 << 0UL);
            ADCx->SQR3 |= (ADC_Channel << 0UL);
            break;

        case ADC_CONVERSION_2_TIME:
            ADCx->SQR3 &= ~(0b11111 << 5UL);
            ADCx->SQR3 |= (ADC_Channel << 5UL);
            break;

        case ADC_CONVERSION_3_TIME:
            ADCx->SQR3 &= ~(0b11111 << 10UL);
            ADCx->SQR3 |= (ADC_Channel << 10UL);
            break;

        case ADC_CONVERSION_4_TIME:
            ADCx->SQR3 &= ~(0b11111 << 16UL);
            ADCx->SQR3 |= (ADC_Channel << 16UL);
            break;

        case ADC_CONVERSION_5_TIME:
            ADCx->SQR3 &= ~(0b11111 << 20UL);
            ADCx->SQR3 |= (ADC_Channel << 20UL);
            break;

        case ADC_CONVERSION_6_TIME:
            ADCx->SQR3 &= ~(0b11111 << 25UL);
            ADCx->SQR3 |= (ADC_Channel << 25UL);
            break;

        case ADC_CONVERSION_7_TIME:
            ADCx->SQR2 &= ~(0b11111 << 0UL);
            ADCx->SQR2 |= (ADC_Channel << 0UL);
            break;

        case ADC_CONVERSION_8_TIME:
            ADCx->SQR2 &= ~(0b11111 << 5UL);
            ADCx->SQR2 |= (ADC_Channel << 5UL);
            break;

        case ADC_CONVERSION_9_TIME:
            ADCx->SQR2 &= ~(0b11111 << 10UL);
            ADCx->SQR2 |= (ADC_Channel << 10UL);
            break;

        case ADC_CONVERSION_10_TIME:
            ADCx->SQR2 &= ~(0b11111 << 15UL);
            ADCx->SQR2 |= (ADC_Channel << 15UL);
            break;

        case ADC_CONVERSION_11_TIME:
            ADCx->SQR2 &= ~(0b11111 << 20UL);
            ADCx->SQR2 |= (ADC_Channel << 20UL);
            break;

        case ADC_CONVERSION_12_TIME:
            ADCx->SQR2 &= ~(0b11111 << 25UL);
            ADCx->SQR2 |= (ADC_Channel << 25UL);
            break;

        case ADC_CONVERSION_13_TIME:
            ADCx->SQR1 &= ~(0b11111 << 0UL);
            ADCx->SQR1 |= (ADC_Channel << 0UL);
            break;

        case ADC_CONVERSION_14_TIME:
            ADCx->SQR1 &= ~(0b11111 << 5UL);
            ADCx->SQR1 |= (ADC_Channel << 5UL);
            break;

        case ADC_CONVERSION_15_TIME:
            ADCx->SQR1 &= ~(0b11111 << 10UL);
            ADCx->SQR1 |= (ADC_Channel << 10UL);
            break;

        case ADC_CONVERSION_16_TIME:
            ADCx->SQR1 &= ~(0b11111 << 15UL);
            ADCx->SQR1 |= (ADC_Channel << 15UL);
            break;
        default:
            break;
    }
}

void ADC_Init(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t SampleTime, uint8_t Prescaler, uint8_t NumberOfConversion){
    ADC_EnableClock(ADCx);

    ADC_SetPrescaler(Prescaler);
    ADC_SetNumberOfConversion(ADCx, ADC_Channel, NumberOfConversion);
    ADC_SetSampleTime(ADCx, ADC_Channel, SampleTime);
    ADC_SetScanMode(ADCx, ADC_SCANMODE_ENABLE);
    ADC_SetDataAlignment(ADCx, ADC_ALIGN_RIGHT);
    ADC_SetConversionMode(ADCx, ADC_MODE_CONTINUOUS);

    ADC_PowerOn(ADCx);
    ADC_Calibrate(ADCx);
}

void ADC_StartConversion(ADC_TypeDef* ADCx, uint16_t* ConvertedData){
    ADC_PowerOn(ADCx);
    uint8_t Timeout = 100; //Set 100ms timeout
    uint32_t lastTicks = ARM_GetTick();

    while((ADCx->SR & (1UL << 1UL))  &&  ((ARM_GetTick() - lastTicks) < Timeout)){};  //Wait until EOC flag is set
    *ConvertedData = ADCx->DR;  //Get converted data
}