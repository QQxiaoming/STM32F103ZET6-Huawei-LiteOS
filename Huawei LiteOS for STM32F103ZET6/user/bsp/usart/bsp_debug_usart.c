/* 包含头文件 ----------------------------------------------------------------*/
#include "bsp/usart/bsp_debug_usart.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 板载调试串口参数配置.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_led.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void DEBUG_USART_Init(void)
{
  /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* 定义USART初始化结构体变量 */
	USART_InitTypeDef USART_InitStructure;
  /* 使能USART时钟 */
  DEBUG_USARTx_ClockCmd(DEBUG_USARTx_CLK,ENABLE);
  /* 使能USART功能GPIO时钟 */
  DEBUG_USARTx_GPIO_ClockCmd(DEBUG_USARTx_TX_CLK | DEBUG_USARTx_RX_CLK | RCC_APB2Periph_AFIO,ENABLE);
  
	/* 调试USART功能GPIO初始化 */
	/* 设定USART发送对应IO编号 */
	GPIO_InitStructure.GPIO_Pin =  DEBUG_USARTx_TX_PIN;
  /* 设定USART发送对应IO模式：复用推挽输出 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  /* 设定USART发送对应IO最大操作速度 ：GPIO_Speed_50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* 初始化USART发送对应IO */
	GPIO_Init(DEBUG_USARTx_TX_PORT, &GPIO_InitStructure);    
  
	/* 设定USART接收对应IO编号 */
	GPIO_InitStructure.GPIO_Pin = DEBUG_USARTx_RX_PIN;
  /* 设定USART发送对应IO模式：浮空输入 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  /* 其他没有重新赋值的成员使用与串口发送相同配置 */
  /* 初始化USART接收对应IO */
	GPIO_Init(DEBUG_USARTx_RX_PORT, &GPIO_InitStructure);	
			
	/* USART工作环境配置 */
  /* USART波特率:115200 */
	USART_InitStructure.USART_BaudRate = DEBUG_USARTx_BAUDRATE;
  /* USART字长(有效位)：8位 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  /* USART停止位：1位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* USART校验位：无 */
	USART_InitStructure.USART_Parity = USART_Parity_No ;
  /* USART硬件数据流控制(硬件信号控制传输停止)：无 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART工作模式使能：允许接收和发送 */
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* 初始化USART */
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
  /* 使能USART */
	USART_Cmd(DEBUG_USARTx, ENABLE);
	
}

///**
//  * 函数功能: 重定向c库函数printf到USARTx
//  * 输入参数: 无
//  * 返 回 值: 无
//  * 说    明：无
//  */
//int fputc(int ch, FILE *f)
//{
//  /* 发送一个字节数据到调试串口 */
//  USART_SendData(DEBUG_USARTx, (uint8_t) ch);

//  /* 等待串口数据发送完毕 */
//  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		

//  return (ch);
//}

/**
  * 函数功能: 重定向c库函数getchar,scanf到USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE *f)
{
  /* 等待串口输入数据 */
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(DEBUG_USARTx);
}

/************************END OF FILE*****************************************/
