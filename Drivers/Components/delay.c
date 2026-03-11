#include "delay.h"

static volatile uint32_t sysTickMs = 0;

/* SysTick中断 */
void SysTick_Handler(void)
{
    sysTickMs++;
}

/* 初始化 1ms SysTick */
void Delay_Init(void)
{
    SysTick_Config(SystemCoreClock / 1000);
}

/* 毫秒延时 */
void Delay_ms(uint32_t ms)
{
    uint32_t start = sysTickMs;

    while((sysTickMs - start) < ms);
}

/* 获取毫秒时间 */
uint32_t millis(void)
{
    return sysTickMs;
}