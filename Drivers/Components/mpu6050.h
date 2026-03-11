#ifndef STM32_STD_TEMPLATE_MPU6050_H
#define STM32_STD_TEMPLATE_MPU6050_H

#include "stm32f10x.h"

#define MPU6050_ADDR 0x68

/* 寄存器地址 */
#define MPU6050_RA_SMPLRT_DIV     0x19
#define MPU6050_RA_CONFIG         0x1A
#define MPU6050_RA_GYRO_CONFIG    0x1B
#define MPU6050_RA_ACCEL_CONFIG   0x1C

#define MPU6050_RA_ACCEL_XOUT_H   0x3B
#define MPU6050_RA_PWR_MGMT_1     0x6B
#define MPU6050_RA_WHO_AM_I       0x75


typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t gx;
    int16_t gy;
    int16_t gz;

    int16_t temp;

}MPU6050_Data_t;


/* 初始化 */
uint8_t MPU6050_Init(void);

/* 读取ID */
uint8_t MPU6050_ReadID(void);

/* 读取原始数据 */
void MPU6050_ReadRaw(MPU6050_Data_t *data);

/* 单独读取 */
void MPU6050_ReadAccel(int16_t *ax,int16_t *ay,int16_t *az);
void MPU6050_ReadGyro(int16_t *gx,int16_t *gy,int16_t *gz);

#endif //STM32_STD_TEMPLATE_MPU6050_H