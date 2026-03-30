/**
  * @file    RCU/RCU_HRC/cs32f0xx_int.c 
  * @brief  Main Interrupt Service Routines. It provides template for
  *            all exceptions handler and  peripherals interrupt service routine.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */
  
  
#include "cs32f0xx_int.h"

/** @addtogroup CS32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup RCU_HRCExample
  * @{
  */


/**
  * @fn void NMI_Handler(void)
  * @brief  This function handles NMI exception.
  * @param  None
  * @return None
  */
void NMI_Handler(void)
{
    /* This interrupt is generated when HXT clock fails */
    if (__RCU_INTR_STATUS_GET(HXT_FAIL) != RESET)
    {   
        /* Enable HXT */
        __RCU_FUNC_ENABLE(HXT_CLK);

        /* Enable HXT Ready and PLL Ready interrupts */
        __RCU_INTR_ENABLE(RCU_INTR_HXT_STAB | RCU_INTR_PLL_STAB);

        /* Clear Clock Security System interrupt  bit */
        __RCU_INTR_FLAG_CLEAR(RCU_INTR_FLAG_CLR_HXT_FAIL);

    }
}

/**
  * @fn void HardFault_Handler(void)
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @return None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @fn void SVC_Handler(void)
  * @brief  This function handles SVCall exception.
  * @param  None
  * @return None
  */
void SVC_Handler(void)
{
}

/**
  * @fn void PendSV_Handler(void)
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @return None
  */
void PendSV_Handler(void)
{
}

/**
  * @fn void SysTick_Handler(void)
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @return None
  */
void SysTick_Handler(void)
{
    timing_delay_decrement();
}


/**
  * @}
  */ 

/**
  * @}
  */ 

