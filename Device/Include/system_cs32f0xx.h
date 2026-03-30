/**
  * @file    system_cs32f0xx.h
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Header File.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */
  
  
#ifndef __SYSTEM_CS32F0XX_H__
#define __SYSTEM_CS32F0XX_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup cs32f0xx_system
  * @{
  */  
  
extern uint32_t SystemCoreClock;     //!<  System Clock Frequency (Core Clock) 


/**
  * @fn void SystemInit (void)
  * @brief  Setup the microcontroller system. Initialize the Embedded Flash Interface,
  *        the PLL and update the SystemCoreClock variable.     
  * @param  None
  * @return None
  */
extern void SystemInit(void);

/**
  * @fn void SystemCoreClockUpdate (void)
  * @brief  Update SystemCoreClock according to Clock Register Values
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @param  None
  * @return None
  */
extern void SystemCoreClockUpdate(void);


#ifdef __cplusplus
}
#endif

#endif 

/**
  * @}
  */
  
/**
  * @}
  */  
