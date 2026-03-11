#include "mpu6050.h"
#include "i2c1.h"

static uint8_t buffer[14];


/* 读取ID */
uint8_t MPU6050_ReadID(void)
{
    return I2C1_ReadByte(MPU6050_ADDR, MPU6050_RA_WHO_AM_I);
}


/* 初始化 */
uint8_t MPU6050_Init(void)
{
    uint8_t id;

    /* 唤醒 */
    I2C1_WriteByte(MPU6050_ADDR, MPU6050_RA_PWR_MGMT_1, 0x00);

    /* 采样率 = 1kHz/(1+7) = 125Hz */
    I2C1_WriteByte(MPU6050_ADDR, MPU6050_RA_SMPLRT_DIV, 7);

    /* DLPF 42Hz */
    I2C1_WriteByte(MPU6050_ADDR, MPU6050_RA_CONFIG, 0x03);

    /* 陀螺仪 ±2000°/s */
    I2C1_WriteByte(MPU6050_ADDR, MPU6050_RA_GYRO_CONFIG, 0x18);

    /* 加速度 ±2g */
    I2C1_WriteByte(MPU6050_ADDR, MPU6050_RA_ACCEL_CONFIG, 0x00);

    id = MPU6050_ReadID();

    if(id == 0x68 || id == 0x70)
        return 0;

    return 1;
}


/* 读取14字节原始数据 */
void MPU6050_ReadRaw(MPU6050_Data_t *data)
{
    I2C1_ReadBytes(MPU6050_ADDR, MPU6050_RA_ACCEL_XOUT_H, buffer, 14);

    data->ax = (buffer[0] << 8) | buffer[1];
    data->ay = (buffer[2] << 8) | buffer[3];
    data->az = (buffer[4] << 8) | buffer[5];

    data->temp = (buffer[6] << 8) | buffer[7];

    data->gx = (buffer[8] << 8) | buffer[9];
    data->gy = (buffer[10] << 8) | buffer[11];
    data->gz = (buffer[12] << 8) | buffer[13];
}


/* 读取加速度 */
void MPU6050_ReadAccel(int16_t *ax,int16_t *ay,int16_t *az)
{
    uint8_t buf[6];

    I2C1_ReadBytes(MPU6050_ADDR, MPU6050_RA_ACCEL_XOUT_H, buf, 6);

    *ax = (buf[0] << 8) | buf[1];
    *ay = (buf[2] << 8) | buf[3];
    *az = (buf[4] << 8) | buf[5];
}


/* 读取陀螺仪 */
void MPU6050_ReadGyro(int16_t *gx,int16_t *gy,int16_t *gz)
{
    uint8_t buf[6];

    I2C1_ReadBytes(MPU6050_ADDR, MPU6050_RA_ACCEL_XOUT_H + 8, buf, 6);

    *gx = (buf[0] << 8) | buf[1];
    *gy = (buf[2] << 8) | buf[3];
    *gz = (buf[4] << 8) | buf[5];
}