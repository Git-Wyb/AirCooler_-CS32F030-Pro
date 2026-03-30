/**
  * @file    RCU/RCU_HRC/cs32f0xx_int.h 
  * @brief   This file contains the headers of the interrupt handlers.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */
  
  
#ifndef __CS32F0XX_INT_H__
#define __CS32F0XX_INT_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include "main.h"



/**
  * @fn void NMI_Handler(void)
  * @brief  This function handles NMI exception.
  * @param  None
  * @return None
  */
void NMI_Handler(void);

/**
  * @fn void HardFault_Handler(void)
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @return None
  */
void HardFault_Handler(void) __attribute__((noreturn));

/**
  * @fn void SVC_Handler(void)
  * @brief  This function handles SVCall exception.
  * @param  None
  * @return None
  */
void SVC_Handler(void);

/**
  * @fn void PendSV_Handler(void)
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @return None
  */
void PendSV_Handler(void);

/**
  * @fn void SysTick_Handler(void)
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @return None
  */
void SysTick_Handler(void);

/**
  * @fn void RCU_IRQHandler(void)
  * @brief  This function handles RCU interrupt request. 
  * @param  None
  * @return None
  */
void RCU_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif 

