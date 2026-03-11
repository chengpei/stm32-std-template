#ifndef STM32_STD_TEMPLATE_I2C1_H
#define STM32_STD_TEMPLATE_I2C1_H

#include "stm32f10x.h"

/* I2C1 初始化 */
void I2C1_Init(void);

/* 单字节写 */
uint8_t I2C1_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);

/* 单字节读 */
uint8_t I2C1_ReadByte(uint8_t devAddr, uint8_t regAddr);

/* 多字节读 */
uint8_t I2C1_ReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t *buf, uint8_t len);

/* 多字节写 */
uint8_t I2C1_WriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t *buf, uint8_t len);

#endif //STM32_STD_TEMPLATE_I2C1_H