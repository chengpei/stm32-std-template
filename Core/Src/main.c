#include "main.h"
#include <stdio.h>
#include "delay.h"
#include "i2c1.h"
#include "imu.h"
#include "mpu6050.h"
#include "stm32f10x.h"
#include "uart1.h"

MPU6050_Data_t mpu6050_data;
IMU_Data_t imu_data;

int main(void)
{
  /* 1. 开启GPIOC时钟 */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* 2. 配置PC13为推挽输出 */
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

  I2C1_Init();
  UART1_Init(115200);
  MPU6050_Init();
  Delay_Init();
  IMU_Init();

  /* 3. 主循环 */
  while (1)
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_13); // LED ON
    Delay_ms(1000);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);   // LED OFF
    Delay_ms(1000);

    IMU_Update(&imu_data);
    printf("AX:%d AY:%d AZ:%d GX:%d GY:%d GZ:%d\r\n",
           (int)(imu_data.ax * 1000),
           (int)(imu_data.ay * 1000),
           (int)(imu_data.az * 1000),
           (int)(imu_data.gx * 100),
           (int)(imu_data.gy * 100),
           (int)(imu_data.gz * 100));
  }
}
