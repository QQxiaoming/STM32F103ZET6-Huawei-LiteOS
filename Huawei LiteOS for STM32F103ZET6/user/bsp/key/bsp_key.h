#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include <stm32f10x.h>

/* 类型定义 ------------------------------------------------------------------*/
typedef enum
{
  KEY_UP   = 0,
  KEY_DOWN = 1,
}KEYState_TypeDef;
#define IS_KEY_STATE(STATE)           ((STATE) == KEY_UP) || ((STATE) == KEY_DOWN))

/* 宏定义 --------------------------------------------------------------------*/
#define KEY1_RCC_CLOCKCMD             RCC_APB2PeriphClockCmd
#define KEY1_RCC_CLOCKGPIO            RCC_APB2Periph_GPIOA
#define KEY1_GPIO_PIN                 GPIO_Pin_0
#define KEY1_GPIO                     GPIOA
#define KEY1_INPUT_LEVEL              GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN)
#define KEY1_DOWN_LEVEL               1  /* 定义按键KEY1按下时是高电平为1，或者是低电平为0，具体值由原理图决定*/
#define KEY1_RCC_CLOCKAFIO            RCC_APB2Periph_AFIO
#define KEY1_GPIO_PORTSOURCE          GPIO_PortSourceGPIOA
#define KEY1_GPIO_PINSOURCE           GPIO_PinSource0
#define KEY1_EXITLINE                 EXTI_Line0
#define KEY1_IRQCHANNEL               EXTI0_IRQn
#define KEY1_IRQHANDLER               EXTI0_IRQHandler

#define KEY2_RCC_CLOCKCMD             RCC_APB2PeriphClockCmd
#define KEY2_RCC_CLOCKGPIO            RCC_APB2Periph_GPIOC
#define KEY2_GPIO_PIN                 GPIO_Pin_13
#define KEY2_GPIO                     GPIOC
#define KEY2_INPUT_LEVEL              GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_PIN)
#define KEY2_DOWN_LEVEL               0  /* 定义按键KEY2按下时是高电平为1，或者是低电平为0，具体值由原理图决定*/
#define KEY2_RCC_CLOCKAFIO            RCC_APB2Periph_AFIO
#define KEY2_GPIO_PORTSOURCE          GPIO_PortSourceGPIOC
#define KEY2_GPIO_PINSOURCE           GPIO_PinSource13
#define KEY2_EXITLINE                 EXTI_Line13
#define KEY2_IRQCHANNEL               EXTI15_10_IRQn
#define KEY2_IRQHANDLER               EXTI15_10_IRQHandler


#define IRQ_DISABLE                   __set_PRIMASK(1)		/* 关闭总中断 */  
#define IRQ_ENABLE                    __set_PRIMASK(0)		/* 开放总中断 */ 

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void KEY_GPIO_Init(void);
KEYState_TypeDef KEY1_StateRead(void);
KEYState_TypeDef KEY2_StateRead(void);

void KEY1_EXIT_Config(void);
void KEY2_EXIT_Config(void);

void KEY1_IRQHANDLER(void);
void KEY2_IRQHANDLER(void);
#endif  // __BSP_KEY_H__

/************************END OF FILE*******************************************/
