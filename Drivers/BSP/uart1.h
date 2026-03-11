//
// Created by 成培 on 2026/3/11.
//

#ifndef STM32_STD_TEMPLATE_UART1_H
#define STM32_STD_TEMPLATE_UART1_H

#include "stm32f10x.h"

#define UART1_RX_BUFFER_SIZE 128

void UART1_Init(uint32_t baudrate);

/* 发送 */
void UART1_SendByte(uint8_t data);
void UART1_SendBytes(uint8_t *buf,uint16_t len);
void UART1_SendString(char *str);

/* 接收 */
uint8_t UART1_Available(void);
uint8_t UART1_ReadByte(void);

#endif //STM32_STD_TEMPLATE_UART1_H