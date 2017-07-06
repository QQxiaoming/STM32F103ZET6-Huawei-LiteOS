/* 包含头文件 ----------------------------------------------------------------*/
#include "bsp/led/bsp_led.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 板载LED灯IO引脚初始化.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_led.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void LED_GPIO_Init(void)
{
   /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能(开启)LED1引脚对应IO端口时钟 */  
  RCC_APB2PeriphClockCmd(LED1_RCC_CLOCKGPIO|LED2_RCC_CLOCKGPIO |LED3_RCC_CLOCKGPIO , ENABLE);
  
  /* 设定LED1对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;  
  /* 设定LED1对应引脚IO最大操作速度 ：GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* 设定LED1对应引脚IO为输出模式 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  /* 初始化LED1对应引脚IO */
  GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
 
  /* 设定LED2对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;  
  /* 初始化LED2对应引脚IO */
  GPIO_Init(LED2_GPIO, &GPIO_InitStructure);

  /* 设定LED3对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;  
  /* 初始化LED3对应引脚IO */
  GPIO_Init(LED3_GPIO, &GPIO_InitStructure);
  
  /* 设置引脚输出为低电平，此时LED1灭 */
  GPIO_ResetBits(LED1_GPIO,LED1_GPIO_PIN);  
  /* 设置引脚输出为低电平，此时LED2灭 */
  GPIO_ResetBits(LED2_GPIO,LED2_GPIO_PIN);  
  /* 设置引脚输出为低电平，此时LED3灭 */
  GPIO_ResetBits(LED3_GPIO,LED3_GPIO_PIN);
}

/**
  * 函数功能: 设置板载LED灯的状态
  * 输入参数: LEDx:其中x可甚至为(1,2,3)用来选择对应的LED灯
  * 输入参数：state:设置LED灯的输出状态。
  *             可选值：LED_OFF：LED灯灭；
  *             可选值：LED_ON： LED灯亮。
  * 返 回 值: 无
  * 说    明：该函数使用类似标准库函数的编程方法，方便理解标准库函数编程思想。
  */
void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state)
{
  /* 检查输入参数是否合法 */
  assert_param(IS_LED_TYPEDEF(LEDx));
  assert_param(IS_LED_STATE(state));
  
  /* 判断设置的LED灯状态，如果设置为LED灯灭 */
  if(state==LED_OFF)
  {
    if(LEDx & LED1)            
      GPIO_ResetBits(LED1_GPIO,LED1_GPIO_PIN);/* 设置引脚输出为低电平，此时LED1灭 */
    if(LEDx & LED2)
      GPIO_ResetBits(LED2_GPIO,LED2_GPIO_PIN);/* 设置引脚输出为低电平，此时LED2灭 */
    if(LEDx & LED3)
      GPIO_ResetBits(LED3_GPIO,LED3_GPIO_PIN);/* 设置引脚输出为低电平，此时LED3灭 */    
  }
  else  /* state=LED_ON ：否则，设置LED灯为亮 */
  {
    if(LEDx & LED1)
      GPIO_SetBits(LED1_GPIO,LED1_GPIO_PIN);/* 设置引脚输出为高电平，此时LED1亮 */
    if(LEDx & LED2)
      GPIO_SetBits(LED2_GPIO,LED2_GPIO_PIN);/* 设置引脚输出为高电平，此时LED2亮 */
    if(LEDx & LED3)
      GPIO_SetBits(LED3_GPIO,LED3_GPIO_PIN);/* 设置引脚输出为高电平，此时LED3亮 */ 
  }
}

/*************************END OF FILE********************************************/
