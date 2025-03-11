/******************************************************************************
 * *
 * Module: SysTick Timer
 *
 * File Name: systick.h
 *
 * Description: Header file for the ARM Cortex M4 SysTick Timer driver
 *
 * Author: Malik Anas
 *
 *******************************************************************************/


/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include "systick.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"


/*******************************************************************************
 *                           Variable Initializations                          *
 *******************************************************************************/

static volatile void (*g_SysTickCallBackPtr)(void);


/*******************************************************************************
 *                            Function Definitions                             *
 *******************************************************************************/

/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - Interrupt time in milliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the SysTick timer with the specified time in milliseconds
*              using interrupts. This function is used to setup the timer to
*              generate periodic interrupts every specified time in milliseconds.
**********************************************************************/

void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    CLEAR_REG(SYSTICK_CTRL_REG);
    uint32 RELOAD_VALUE = (a_TimeInMilliSeconds / ((1.0 / F_SYSTICK) * 1000)) - 1;
    SYSTICK_RELOAD_REG = RELOAD_VALUE;
    CLEAR_REG(SYSTICK_CURRENT_REG);

    SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_INTEN_BIT);
    SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_CLK_BIT);
    SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_ENABLE_BIT);
}

/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): a_TimeInMilliSeconds - Interrupt time in milliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the SysTick timer with the specified time in milliseconds
*              using polling or busy-wait technique. The function should exit when
*              the time is elapsed and stops the timer at the end.
**********************************************************************/

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    CLEAR_REG(SYSTICK_CTRL_REG);
    uint32 RELOAD_VALUE = (a_TimeInMilliSeconds / ((1.0 / F_SYSTICK) * 1000)) - 1;
    SYSTICK_RELOAD_REG = RELOAD_VALUE;
    CLEAR_REG(SYSTICK_CURRENT_REG);

    SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_CLK_BIT);
    SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_ENABLE_BIT);

    while(BIT_IS_CLEAR(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_COUNT_BIT));
}

/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: Asynchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Handler for SysTick interrupt use to call the call-back function.
**********************************************************************/

void SysTick_Handler(void)
{
    (* g_SysTickCallBackPtr)();
}

/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): Ptr2Func - Pointer to Function
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Handler for SysTick interrupt use to call the call-back function.
**********************************************************************/

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    g_SysTickCallBackPtr = Ptr2Func;
}

/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stop the SysTick timer
**********************************************************************/

void SysTick_Stop(void)
{
    CLEAR_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_ENABLE_BIT);
}

/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Start/Resume the SysTick timer
**********************************************************************/

void SysTick_Start(void)
{
    SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_ENABLE_BIT);
}

/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  : Function to De-initialize the SysTick Timer.
**********************************************************************/

void SysTick_DeInit(void)
{
    CLEAR_REG(SYSTICK_CTRL_REG);
}

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
