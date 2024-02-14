#ifndef __ADC_H
#define __ADC_H

#include "stm32f1xx.h"
#include "Delay.h"
#include "ARM_System.h"

/*ADC power on or off*/
#define ADC_POWER_ON                    1
#define ADC_POWER_OFF                   0   

/**ADC prescaler */
#define ADC_DIV_2                       0
#define ADC_DIV_4                       1
#define ADC_DIV_6                       2
#define ADC_DIV_8                       3

/**Conversion mode */
#define ADC_MODE_SINGLE                 0
#define ADC_MODE_CONTINUOUS             1

/**Scan mode */
#define ADC_SCANMODE_DISABLE            0
#define ADC_SCANMODE_ENABLE             1

/**Data alignment */
#define ADC_ALIGN_RIGHT                 0
#define ADC_ALIGN_LEFT                  1

/**Sample time */
#define ADC_SAMPLETIME_1ANDHALF         0
#define ADC_SAMPLETIME_7ANDHALF         1
#define ADC_SAMPLETIME_13ANDHALF        2
#define ADC_SAMPLETIME_28ANDHALF        3
#define ADC_SAMPLETIME_41ANDHALF        4
#define ADC_SAMPLETIME_55ANDHALF        5
#define ADC_SAMPLETIME_71ANDHALF        6
#define ADC_SAMPLETIME_239ANDHALF       7

/**ADC channel */
#define ADC_CHANNEL_0                   0
#define ADC_CHANNEL_1                   1
#define ADC_CHANNEL_2                   2
#define ADC_CHANNEL_3                   3
#define ADC_CHANNEL_4                   4
#define ADC_CHANNEL_5                   5
#define ADC_CHANNEL_6                   6
#define ADC_CHANNEL_7                   7
#define ADC_CHANNEL_8                   8
#define ADC_CHANNEL_9                   9

/**Number of conversion */
#define ADC_CONVERSION_1_TIME           0
#define ADC_CONVERSION_2_TIME           1
#define ADC_CONVERSION_3_TIME           2
#define ADC_CONVERSION_4_TIME           3
#define ADC_CONVERSION_5_TIME           4
#define ADC_CONVERSION_6_TIME           5
#define ADC_CONVERSION_7_TIME           6
#define ADC_CONVERSION_8_TIME           7
#define ADC_CONVERSION_9_TIME           8
#define ADC_CONVERSION_10_TIME          9
#define ADC_CONVERSION_11_TIME          10
#define ADC_CONVERSION_12_TIME          11
#define ADC_CONVERSION_13_TIME          12
#define ADC_CONVERSION_14_TIME          13
#define ADC_CONVERSION_15_TIME          14
#define ADC_CONVERSION_16_TIME          15

void ADC_PowerOn(ADC_TypeDef* ADCx);
void ADC_SetPrescaler(uint8_t ADCPrescaler);
void ADC_SetConversionMode(ADC_TypeDef* ADCx, _Bool ConversionMode);
void ADC_SetScanMode(ADC_TypeDef* ADCx, _Bool ScanMode);
void ADC_EnableDiscontinuousMode(ADC_TypeDef* ADCx, _Bool isEnabled);
void ADC_Calibrate(ADC_TypeDef* ADCx);
void ADC_SetDataAlignment(ADC_TypeDef* ADCx, _Bool Alignment);
void ADC_SetSampleTime(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t SampleTime);
void ADC_SetNumberOfConversion(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t NumberOfConversion);
void ADC_Init(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t SampleTime, uint8_t Prescaler, uint8_t NumberOfConversion);
void ADC_StartConversion(ADC_TypeDef* ADCx, uint16_t* ConvertedData);


#endif