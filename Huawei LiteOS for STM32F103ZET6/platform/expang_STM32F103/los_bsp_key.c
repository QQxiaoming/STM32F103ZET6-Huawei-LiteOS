#include "los_bsp_key.h"

/******************************************************************************
    here include some special hearder file you need
******************************************************************************/
#include "los_hwi.h"
#include "bsp/key/bsp_key.h"
#include "bsp/led/bsp_led.h"

/*****************************************************************************
 Function    : LOS_EvbKeyInit
 Description : Init GIOP Key 
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbKeyInit(void)
{
    //add you code here.
    KEY_GPIO_Init();
	KEY1_EXIT_Config();
	LOS_HwiCreate(6, 0, 0, KEY1_IRQHANDLER, NULL);	
    return ;
}

/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    unsigned int KeyVal = 0xFFFFFFFF;
    
    //add you code here.
    if(GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN) == KEY1_DOWN_LEVEL)
	{
		KeyVal = 0;
	}
	
    return KeyVal;
}

/*****************************************************************************
 Function    : EXTIxxx_IRQHandler
 Description : EXT xxx IRQ Handler detail,change the function name 
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void KEY1_IRQHANDLER(void)
{
  /* 确保是否产生了EXTI Line中断 */
	if(EXTI_GetITStatus(KEY1_EXITLINE) != RESET)
	{
	/* LED1灯翻转	*/	
		LED1_TOGGLE;
    /* 清除中断标志位	*/
		EXTI_ClearITPendingBit(KEY1_EXITLINE);     
	}
}
