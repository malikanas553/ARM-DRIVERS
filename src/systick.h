/*
 **
 * Module: SysTick Timer
 *
 * File Name: systick.h
 *
 * Description: Header file for the ARM Cortex M4 SysTick Timer driver
 *
 * Author: Malik Anas
 *
 *******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/

#define F_SYSTICK 16000000
#define SYSTICK_CTRL_REG_ENABLE_BIT 0
#define SYSTICK_CTRL_REG_INTEN_BIT 1
#define SYSTICK_CTRL_REG_CLK_BIT 2
#define SYSTICK_CTRL_REG_COUNT_BIT 16

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);



/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/

#endif /* SYSTICK_H_ */
