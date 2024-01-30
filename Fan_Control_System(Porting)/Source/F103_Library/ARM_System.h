#ifndef __ARM_SYSTEM_H
#define __ARM_SYSTEM_H

#include "stm32f1xx.h"

void ARM_ClockInit(void);
void ARM_SystickInit(void);
uint32_t ARM_GetTick(void);
void ARM_SystemInit(void);

#endif  //__ARM_SYSTEM_H