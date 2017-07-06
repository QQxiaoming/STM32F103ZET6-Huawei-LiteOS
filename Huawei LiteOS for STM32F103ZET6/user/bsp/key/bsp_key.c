/* 包含头文件 ----------------------------------------------------------------*/
#include "bsp/key/bsp_key.h"
#include "bsp/led/bsp_led.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 板载按键IO引脚初始化.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：使用宏定义方法代替具体引脚号，方便程序移植，只要简单修改bsp_key.h
  *           文件相关宏定义就可以方便修改引脚。
  */
void KEY_GPIO_Init(void)
{
  /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能(开启)KEY1引脚对应IO端口时钟 */  
  KEY1_RCC_CLOCKCMD(KEY1_RCC_CLOCKGPIO, ENABLE);
  
 	/* 使能(开启)KEY2引脚对应IO端口时钟 */  
  KEY2_RCC_CLOCKCMD(KEY2_RCC_CLOCKGPIO, ENABLE);

  /* 设定KEY1对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;  
  /* 设定KEY1对应引脚IO最大操作速度 ：GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* 设定KEY1对应引脚IO为浮空输入模式 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  /* 初始化KEY1对应引脚IO */
  GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);
 
  /* 设定KEY2对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;  
  /* 初始化KEY2对应引脚IO */
  GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);
}

/**
  * 函数功能: 简单粗暴的延时函数
  * 输入参数: time；延时时间设置
  * 返 回 值: 无
  * 说    明：按键在按下与弹开过程存在抖动，一般需要软件消抖，软件消抖最简单方法
  *           就是加延时。
  */
void KEY_ScanDelay(void)
{  
  uint32_t i,j;
  for(i=0;i<100;++i)
    for(j=0;j<1000;++j){ }
}

/**
  * 函数功能: 读取按键KEY1的状态
  * 输入参数：无
  * 返 回 值: KEY_DOWN：按键被按下；
  *           KEY_UP  ：按键没被按下
  * 说    明：无。
  */
KEYState_TypeDef KEY1_StateRead(void)
{
  /* 读取此时按键值并判断是否是被按下状态，如果是被按下状态进入函数内 */
  if(GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN)==KEY1_DOWN_LEVEL)
  {
    /* 延时一小段时间，消除抖动 */
    KEY_ScanDelay();
    /* 延时时间后再来判断按键状态，如果还是按下状态说明按键确实被按下 */
    if(GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN)==KEY1_DOWN_LEVEL)
    {
      /* 等待按键弹开才退出按键扫描函数 */
      while(GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN)==KEY1_DOWN_LEVEL);
       /* 按键扫描完毕，确定按键被按下，返回按键被按下状态 */
      return KEY_DOWN;
    }
  }
  /* 按键没被按下，返回没被按下状态 */
  return KEY_UP;
}

/**
  * 函数功能: 读取按键KEY2的状态
  * 输入参数：无
  * 返 回 值: KEY_DOWN：按键被按下；
  *           KEY_UP  ：按键没被按下
  * 说    明：无。
  */
KEYState_TypeDef KEY2_StateRead(void)
{
  /* 读取此时按键值并判断是否是被按下状态，如果是被按下状态进入函数内 */
  if(GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_PIN)==KEY2_DOWN_LEVEL)
  {
    /* 延时一小段时间，消除抖动 */
    KEY_ScanDelay();
    /* 延时时间后再来判断按键状态，如果还是按下状态说明按键确实被按下 */
    if(GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_PIN)==KEY2_DOWN_LEVEL)
    {
      /* 等待按键弹开才退出按键扫描函数 */
      while(GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_PIN)==KEY2_DOWN_LEVEL);
       /* 按键扫描完毕，确定按键被按下，返回按键被按下状态 */
      return KEY_DOWN;
    }
  }
  /* 按键没被按下，返回没被按下状态 */
  return KEY_UP;
}

/**
  * 函数功能: 配置KEY1作为中断引脚并使能中断
  * 输入参数：无
  * 返 回 值: 无
  * 说    明：我们配置KEY1为上升沿中断，查看开发板原理图可知在KEY1在没被按下时PA0为
  *           低电平(下拉电阻作用结果)，所以当我们按下按键时就有一个从低电平变为高
  *           电平过程，stm32f103芯片可以把这过程检测出来，当我们配置相关资源后就可
  *           以让stm32把检测到这电平变化消息告诉给我们，从而我们知道了我们的动作
  *           效果，进而进一步处理任务。
  */
void KEY1_EXIT_Config(void)
{
  /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* 定义外部中断线初始化结构体变量 */
  EXTI_InitTypeDef EXTI_InitStructure;
  /* 定义嵌套向量中断控制器初始化结构体变量 */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 为启用IO引脚中断功能需要使能复用功能时钟 */
  KEY1_RCC_CLOCKCMD(KEY1_RCC_CLOCKGPIO | KEY1_RCC_CLOCKAFIO,ENABLE);
  
  /* 设定KEY1对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;  
  /* 设定KEY1对应引脚IO最大操作速度 ：GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* 设定KEY1对应引脚IO为浮空输入模式 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  /* 初始化KEY1对应引脚IO */
  GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);

  /* 选择PA0作为中断输入源 */
  GPIO_EXTILineConfig(KEY1_GPIO_PORTSOURCE,KEY1_GPIO_PINSOURCE);
  
  /* KEY1对应的断线 */
  EXTI_InitStructure.EXTI_Line=KEY1_EXITLINE;
  /* 外部中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  /* 下降沿触发方式 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* 使能中断 */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  /* 根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器 */
  EXTI_Init(&EXTI_InitStructure);
  
  /* 选择中断优先级配置组为4个抢占式优先级和4个子优先级，可以参考misc.h文件了解相关设置 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 使能KEY1所在的外部中断通道 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_IRQCHANNEL;
  /* 设置抢占式优先级为2 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; 
  /* 设置子优先级为3 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
  /* 使能外部中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  /* 初始化配置嵌套向量中断控制器 */
  NVIC_Init(&NVIC_InitStructure); 
}

/**
  * 函数功能: 配置KEY2作为中断引脚并使能中断
  * 输入参数：无
  * 返 回 值: 无
  * 说    明：我们配置KEY2为下降沿中断，查看开发板原理图可知在KEY2在没被按下时PC0为
  *           高电平(上拉电阻作用结果)，所以当我们按下按键时就有一个从高电平变为低
  *           电平过程，stm32f103芯片可以把这过程检测出来，当我们配置相关资源后就可
  *           以让stm32把检测到这电平变化消息告诉给我们，从而我们知道了我们的动作
  *           效果，进而进一步处理任务。
  */
void KEY2_EXIT_Config(void)
{
  /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* 定义外部中断线初始化结构体变量 */
  EXTI_InitTypeDef EXTI_InitStructure;
  /* 定义嵌套向量中断控制器初始化结构体变量 */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 为启用IO引脚中断功能需要使能复用功能时钟 */
  KEY2_RCC_CLOCKCMD(KEY2_RCC_CLOCKGPIO | KEY2_RCC_CLOCKAFIO,ENABLE);
  
  /* 设定KEY2对应引脚IO编号 */
  GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;  
  /* 设定KEY2对应引脚IO最大操作速度 ：GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* 设定KEY2对应引脚IO为浮空输入模式 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  /* 初始化KEY2对应引脚IO */
  GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);

  /* 选择KEY2作为中断输入源 */
  GPIO_EXTILineConfig(KEY2_GPIO_PORTSOURCE,KEY2_GPIO_PINSOURCE);
  
  /* KEY2对应的中断线 */
  EXTI_InitStructure.EXTI_Line=KEY2_EXITLINE;
  /* 外部中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  /* 下降沿触发方式 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* 使能中断 */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  /* 根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器 */
  EXTI_Init(&EXTI_InitStructure);
  
  /* 选择中断优先级配置组为4个抢占式优先级和4个子优先级，可以参考misc.h文件了解相关设置 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 使能KEY2所在的外部中断通道 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_IRQCHANNEL;
  /* 设置抢占式优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 
  /* 设置子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  /* 使能外部中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  /* 初始化配置嵌套向量中断控制器 */
  NVIC_Init(&NVIC_InitStructure); 
}


///**
//  * 函数功能: KEY1中断服务函数
//  * 输入参数：无
//  * 返 回 值: 无
//  * 说    明：在stm32f103检测到下降沿信号后会自动进入对应的中断服务函数，我们可以在
//  *           服务函数内实现一些处理。
//  */
//void KEY1_IRQHANDLER(void)
//{
//  /* 确保是否产生了EXTI Line中断 */
//	if(EXTI_GetITStatus(KEY1_EXITLINE) != RESET)
//	{
//		/* LED1灯翻转	*/	
//		LED1_TOGGLE;
//    /* 清除中断标志位	*/
//		EXTI_ClearITPendingBit(KEY1_EXITLINE);     
//	}
//}

///**
//  * 函数功能: KEY2中断服务函数
//  * 输入参数：无
//  * 返 回 值: 无
//  * 说    明：在stm32f103检测到下降沿信号后会自动进入对应的中断服务函数，我们可以在
//  *           服务函数内实现一些处理。
//  */
//void KEY2_IRQHANDLER(void)
//{
//  /* 确保是否产生了EXTI Line中断 */
//	if(EXTI_GetITStatus(KEY2_EXITLINE) != RESET)
//	{
//    /* LED2灯翻转	*/	
//    LED2_TOGGLE;
//    /* 清除中断标志位	*/
//		EXTI_ClearITPendingBit(KEY2_EXITLINE);     
//	}
//}
/************************END OF FILE*******************************************/
