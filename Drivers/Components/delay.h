#ifndef STM32_STD_TEMPLATE_DELAY_H
#define STM32_STD_TEMPLATE_DELAY_H

#include "stm32f10x.h"

void Delay_Init(void);
void Delay_ms(uint32_t ms);
uint32_t millis(void);

#endif //STM32_STD_TEMPLATE_DELAY_H