#include "los_bsp_led.h"

/******************************************************************************
    here include some special hearder file you need
******************************************************************************/
#include "bsp/led/bsp_led.h"


/*****************************************************************************
 Function    : LOS_EvbLedInit
 Description : Init LED device
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbLedInit(void)
{
    //add you code here.
    LED_GPIO_Init();
    return ;
}

/*************************************************************************************************
 *  Function    £ºLOS_EvbLedControl
 *  Discription : Led control function
 *  Input       : (1) index Led's index                                                                  *
 *                (2) cmd   Led on or off  
 *  Output      : None
 *  Return      : None                                                                                *
 *                                                                                 *
**************************************************************************************************/
void LOS_EvbLedControl(int index, int cmd)
{
    switch (index)
    {
        case LOS_LED1:
        {
            if (cmd == LOS_LED_ON)
            {
                //add you code here.
                LED1_ON;        /*led1 on */
            }
            else
            {
                //add you code here.
                LED1_OFF;        /*led1 off */
            }
            break;
        }
        case LOS_LED2:
        {
            if (cmd == LOS_LED_ON)
            {
                //add you code here.
                LED2_ON;        /*led2 on */
            }
            else
            {
                //add you code here.
                LED1_OFF;        /*led2 off */
            }
            break;
        }
        case LOS_LED3:
        {
            if (cmd == LOS_LED_ON)
            {
                //add you code here.
                LED3_ON;        /*led3 on */
            }
            else
            {
                //add you code here.
                LED3_OFF;        /*led3 off */
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}


