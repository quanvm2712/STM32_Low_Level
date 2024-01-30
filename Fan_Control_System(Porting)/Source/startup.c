#define SRAM_START  (0x20000000U)
#define SRAM_SIZE   (20U * 1024U)
#define SRAM_END    (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS  (SRAM_END)

#include <stdint.h>
#define ISR_VECTOR_SIZE_WORDS 59

/*ARM exception handler*/
void reset_handler(void);
void default_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void mem_manage_handler(void)__attribute__((weak, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));

/*STM32F103 interrupt handler*/
void WWDG_Handler(void)__attribute((weak, alias("default_handler")));
void PVD_Handler(void)__attribute((weak, alias("default_handler")));
void TAMPER_Handler(void)__attribute((weak, alias("default_handler")));
void RTC_Handler(void)__attribute((weak, alias("default_handler")));
void FLASH_Handler(void)__attribute((weak, alias("default_handler")));
void RCC_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI0_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI1_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI2_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI3_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI4_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel1_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel2_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel3_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel4_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel5_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel6_Handler(void)__attribute((weak, alias("default_handler")));
void DMA1_Channel7_Handler(void)__attribute((weak, alias("default_handler")));
void ADC1_2_Handler(void)__attribute((weak, alias("default_handler")));
void USB_HP_CAN_TX_Handler(void)__attribute((weak, alias("default_handler")));
void USB_LP_CAN_RX0_Handler(void)__attribute((weak, alias("default_handler")));
void CAN_RX1_Handler(void)__attribute((weak, alias("default_handler")));
void CAN_SCE_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI9_5_Handler(void)__attribute((weak, alias("default_handler")));
void TIM1_BRK_Handler(void)__attribute((weak, alias("default_handler")));
void TIM1_UP_Handler(void)__attribute((weak, alias("default_handler")));
void TIM1_TRG_COM_Handler(void)__attribute((weak, alias("default_handler")));
void TIM1_CC_Handler(void)__attribute((weak, alias("default_handler")));
void TIM2_Handler(void)__attribute((weak, alias("default_handler")));
void TIM3_Handler(void)__attribute((weak, alias("default_handler")));
void TIM4_Handler(void)__attribute((weak, alias("default_handler")));
void I2C1_EV_Handler(void)__attribute((weak, alias("default_handler")));
void I2C1_ER_Handler(void)__attribute((weak, alias("default_handler")));
void I2C2_EV_Handler(void)__attribute((weak, alias("default_handler")));
void I2C2_ER_Handler(void)__attribute((weak, alias("default_handler")));
void SPI1_Handler(void)__attribute((weak, alias("default_handler")));
void SPI2_Handler(void)__attribute((weak, alias("default_handler")));
void USART1_Handler(void)__attribute((weak, alias("default_handler")));
void USART2_Handler(void)__attribute((weak, alias("default_handler")));
void USART3_Handler(void)__attribute((weak, alias("default_handler")));
void EXTI15_10_Handler(void)__attribute((weak, alias("default_handler")));
void RTCAlarm_Handler(void)__attribute((weak, alias("default_handler")));
void USBWakeup_Handler(void)__attribute((weak, alias("default_handler")));


uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
    STACK_POINTER_INIT_ADDRESS,

    /*ARM exception handler*/
    (uint32_t)&reset_handler,
    (uint32_t)&nmi_handler,
    (uint32_t)&hard_fault_handler,
    (uint32_t)&mem_manage_handler,
    (uint32_t)&bus_fault_handler,
    (uint32_t)&usage_fault_handler,
    0,
    0,
    0,
    0,
    (uint32_t)&svcall_handler,
    (uint32_t)&debug_monitor_handler,
    0,
    (uint32_t)&pendsv_handler,
    (uint32_t)&systick_handler,

    /*STM32F103 interrupt handler*/
    (uint32_t)&WWDG_Handler,
    (uint32_t)&PVD_Handler,
    (uint32_t)&TAMPER_Handler,
    (uint32_t)&RTC_Handler,
    (uint32_t)&FLASH_Handler,
    (uint32_t)&RCC_Handler,
    (uint32_t)&EXTI0_Handler,
    (uint32_t)&EXTI1_Handler,
    (uint32_t)&EXTI2_Handler,
    (uint32_t)&EXTI3_Handler,
    (uint32_t)&EXTI4_Handler,
    (uint32_t)&DMA1_Channel1_Handler,
    (uint32_t)&DMA1_Channel2_Handler,
    (uint32_t)&DMA1_Channel3_Handler,
    (uint32_t)&DMA1_Channel4_Handler,
    (uint32_t)&DMA1_Channel5_Handler,
    (uint32_t)&DMA1_Channel6_Handler,
    (uint32_t)&DMA1_Channel7_Handler,
    (uint32_t)&ADC1_2_Handler,
    (uint32_t)&USB_HP_CAN_TX_Handler,
    (uint32_t)&USB_LP_CAN_RX0_Handler,
    (uint32_t)&CAN_RX1_Handler,
    (uint32_t)&CAN_SCE_Handler,
    (uint32_t)&EXTI9_5_Handler,
    (uint32_t)&TIM1_BRK_Handler,
    (uint32_t)&TIM1_UP_Handler,
    (uint32_t)&TIM1_TRG_COM_Handler,
    (uint32_t)&TIM1_CC_Handler,
    (uint32_t)&TIM2_Handler,
    (uint32_t)&TIM3_Handler,
    (uint32_t)&TIM4_Handler,
    (uint32_t)&I2C1_EV_Handler,
    (uint32_t)&I2C1_ER_Handler,
    (uint32_t)&I2C2_EV_Handler,
    (uint32_t)&I2C2_ER_Handler,
    (uint32_t)&SPI1_Handler,
    (uint32_t)&SPI2_Handler,
    (uint32_t)&USART1_Handler,
    (uint32_t)&USART2_Handler,
    (uint32_t)&USART3_Handler,
    (uint32_t)&EXTI15_10_Handler,
    (uint32_t)&RTCAlarm_Handler,
    (uint32_t)&USBWakeup_Handler,
};

void default_handler(void){
    while(1);
}

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main(void);

void reset_handler(void){
    //Copy data from flash to sram
    uint32_t data_size = (uint32_t) &_edata - (uint32_t) &_sdata;
    uint8_t* sram_data = (uint8_t*) &_sdata;
    uint8_t* flash_data = (uint8_t*) &_etext;

    for(int i=0; i<data_size; i++){
        sram_data[i] = flash_data[i];
    }

    //Write 0 to entire .bss region
    uint32_t bss_size = (uint32_t) &_ebss - (uint32_t)&_sbss;
    uint32_t* bss = (uint32_t*)&_ebss;

    for(int i=0; i<bss_size; i++){
        bss[i] = 0;
    }

    //Call main function
    main();
}