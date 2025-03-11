/*
 *
 * Module: NVIC
 *
 * File Name: nvic.c
 *
 * Description: Source file for the ARM Cortex M4 NVIC driver
 *
 * Author: Malik Anas
 *
 *******************************************************************************/

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/

#include "nvic.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*******************************************************************************
 *                            Function Definitions                             *
 *******************************************************************************/

/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if(IRQ_Num > 138)
    {
        return;
    }
    uint8 REG_NUM = IRQ_Num/32;
    uint8 BIT_POS = IRQ_Num%32;
    switch(REG_NUM)
    {
    case 0:
        SET_BIT(NVIC_EN0_REG,BIT_POS);
        break;
    case 1:
        SET_BIT(NVIC_EN1_REG,BIT_POS);
        break;
    case 2:
        SET_BIT(NVIC_EN2_REG,BIT_POS);
        break;
    case 3:
        SET_BIT(NVIC_EN3_REG,BIT_POS);
        break;
    case 4:
        SET_BIT(NVIC_EN4_REG,BIT_POS);
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if(IRQ_Num > 138)
    {
        return;
    }
    uint8 REG_NUM = IRQ_Num/32;
    uint8 BIT_POS = IRQ_Num%32;
    switch(REG_NUM)
    {
    case 0:
        SET_BIT(NVIC_DIS0_REG,BIT_POS);
        break;
    case 1:
        SET_BIT(NVIC_DIS1_REG,BIT_POS);
        break;
    case 2:
        SET_BIT(NVIC_DIS2_REG,BIT_POS);
        break;
    case 3:
        SET_BIT(NVIC_DIS3_REG,BIT_POS);
        break;
    case 4:
        SET_BIT(NVIC_DIS4_REG,BIT_POS);
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table, IRQ_Priority - IRQ Priority Level from 0 - 7
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to set the priority value for specific IRQ.
**********************************************************************/

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,
                         NVIC_IRQPriorityType IRQ_Priority)
{
    if(IRQ_Num > 138 || IRQ_Priority > 7)
    {
        return;
    }
    uint8 REG_NUM = IRQ_Num / 4;
    uint8 BIT_POS = IRQ_Num % 4;
    volatile uint32 * NVIC_PRI_BASE_ADDRESS = &(NVIC_PRI0_REG);
    switch(BIT_POS)
    {
    case 0:
        (*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) = ((*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) & INTA_PRI_BIT_MASK) | (IRQ_Priority << INTA_PRI_BIT_POS);
        break;
    case 1:
        (*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) = ((*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) & INTB_PRI_BIT_MASK) | (IRQ_Priority << INTB_PRI_BIT_POS);
        break;
    case 2:
        (*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) = ((*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) & INTC_PRI_BIT_MASK) | (IRQ_Priority << INTC_PRI_BIT_POS);
        break;
    case 3:
        (*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) = ((*(NVIC_PRI_BASE_ADDRESS + REG_NUM)) & INTD_PRI_BIT_MASK) | (IRQ_Priority << INTD_PRI_BIT_POS);
        break;
    }


}

/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from the NVIC_ExceptionType enum
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to enable specific ARM system or fault exceptions.
**********************************************************************/

void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
    case EXCEPTION_RESET_TYPE:
        break;
    case EXCEPTION_NMI_TYPE:
        break;
    case EXCEPTION_HARD_FAULT_TYPE:
        break;
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
        break;
    case EXCEPTION_SVC_TYPE:
        break;
    case EXCEPTION_DEBUG_MONITOR_TYPE:
        break;
    case EXCEPTION_PEND_SV_TYPE:
        break;
    case EXCEPTION_SYSTICK_TYPE:
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from the NVIC_ExceptionType enum
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to disable specific ARM system or fault exceptions.
**********************************************************************/


void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
    case EXCEPTION_RESET_TYPE:
        break;
    case EXCEPTION_NMI_TYPE:
        break;
    case EXCEPTION_HARD_FAULT_TYPE:
        break;
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(MEM_FAULT_ENABLE_MASK);
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(BUS_FAULT_ENABLE_MASK);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_SYSHNDCTRL &= ~(USAGE_FAULT_ENABLE_MASK);
        break;
    case EXCEPTION_SVC_TYPE:
        break;
    case EXCEPTION_DEBUG_MONITOR_TYPE:
        break;
    case EXCEPTION_PEND_SV_TYPE:
        break;
    case EXCEPTION_SYSTICK_TYPE:
        break;
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in):  Exception_Num - Number of the Exception from the NVIC_ExceptionType enum,
                    Exception_Priority - Exception Priority Level from 0 - 7
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:  Function to set the priority value for specific ARM system or fault exceptions.
**********************************************************************/

void NVIC_SetPriorityException(NVIC_ExceptionType
                               Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    switch(Exception_Num)
    {
    case EXCEPTION_RESET_TYPE:
        break;
    case EXCEPTION_NMI_TYPE:
        break;
    case EXCEPTION_HARD_FAULT_TYPE:
        break;
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG | MEM_FAULT_PRIORITY_MASK) & (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG | BUS_FAULT_PRIORITY_MASK) & (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG | USAGE_FAULT_PRIORITY_MASK) & (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_SVC_TYPE:
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG | SVC_PRIORITY_MASK) & (Exception_Priority << SVC_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_DEBUG_MONITOR_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG | DEBUG_MONITOR_PRIORITY_MASK) & (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_PEND_SV_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG | PENDSV_PRIORITY_MASK) & (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
        break;
    case EXCEPTION_SYSTICK_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG | SYSTICK_PRIORITY_MASK) & (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
        break;
    }
}

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
