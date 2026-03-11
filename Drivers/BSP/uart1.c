#include "uart1.h"

static uint8_t rxBuffer[UART1_RX_BUFFER_SIZE];
static volatile uint16_t rxWriteIndex = 0;
static volatile uint16_t rxReadIndex  = 0;


/* 初始化 */
void UART1_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 时钟 */
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA |
        RCC_APB2Periph_USART1 |
        RCC_APB2Periph_AFIO,
        ENABLE
    );

    /* TX PA9 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    /* RX PA10 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    /* USART */
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(USART1,&USART_InitStructure);

    /* RX中断 */
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    /* NVIC */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1,ENABLE);
}


/* 发送一个字节 */
void UART1_SendByte(uint8_t data)
{
    USART_SendData(USART1,data);

    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}


/* 发送多个字节 */
void UART1_SendBytes(uint8_t *buf,uint16_t len)
{
    uint16_t i;

    for(i=0;i<len;i++)
    {
        UART1_SendByte(buf[i]);
    }
}


/* 发送字符串 */
void UART1_SendString(char *str)
{
    while(*str)
    {
        UART1_SendByte(*str++);
    }
}


/* 是否有数据 */
uint8_t UART1_Available(void)
{
    return (rxWriteIndex != rxReadIndex);
}


/* 读取一个字节 */
uint8_t UART1_ReadByte(void)
{
    uint8_t data = 0;

    if(rxReadIndex != rxWriteIndex)
    {
        data = rxBuffer[rxReadIndex];

        rxReadIndex++;

        if(rxReadIndex >= UART1_RX_BUFFER_SIZE)
            rxReadIndex = 0;
    }

    return data;
}


/* USART1 中断 */
void USART1_IRQHandler(void)
{
    uint8_t data;

    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART1);

        rxBuffer[rxWriteIndex] = data;

        rxWriteIndex++;

        if(rxWriteIndex >= UART1_RX_BUFFER_SIZE)
            rxWriteIndex = 0;
    }
}


/* printf 重定向串口1 */
int _write(int fd, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        USART_SendData(USART1, ptr[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }

    return len;
}