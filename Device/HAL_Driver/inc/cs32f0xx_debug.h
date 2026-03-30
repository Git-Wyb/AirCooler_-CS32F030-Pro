/**
  * @file   cs32f0xx_debug.h 
  * @brief  This file contains all the functions prototypes for the DEBUG firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_DEBUG_H__
#define __CS32F0XX_DEBUG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup DEBUG
  * @{
  */ 

/** @defgroup DEBUG_Exported_Constants
  * @{
  */

/** 
  * @brief Debug support mode for low power configuration register 
  */
#define DEBUG_MODE_DSM                          DBG_LPWCFG_DSM_DBGEN                //!< Stop mode debug support 
#define DEBUG_MODE_PWD                          DBG_LPWCFG_PWD_DBGEN                //!< Standby mode debug support 

/** 
  * @brief Debug support mode for APB1 peripherals configuration register 
  */
#define DEBUG_TIM2_PAUSE                        DBG_APB1CFG_TIM2_DBG_PAUSE          //!< TIM2 counter paused when system is in debug mode    
#define DEBUG_TIM3_PAUSE                        DBG_APB1CFG_TIM3_DBG_PAUSE          //!< TIM3 counter paused when system is in debug mode    
#define DEBUG_TIM6_PAUSE                        DBG_APB1CFG_TIM6_DBG_PAUSE          //!< TIM6 counter paused when system is in debug mode    
#define DEBUG_TIM7_PAUSE                        DBG_APB1CFG_TIM7_DBG_PAUSE          //!< TIM7 counter paused when system is in debug mode    
#define DEBUG_TIM14_PAUSE                       DBG_APB1CFG_TIM14_DBG_PAUSE         //!< TIM14 counter paused when system is in debug mode   
#define DEBUG_RTC_PAUSE                         DBG_APB1CFG_RTC_DBG_PAUSE           //!< RTC paused when system is in debug mode             
#define DEBUG_WWDT_PAUSE                        DBG_APB1CFG_WWDT_DBG_PAUSE          //!< Window watchdog paused when system is in debug mode 
#define DEBUG_FWDT_PAUSE                        DBG_APB1CFG_FWDT_DBG_PAUSE          //!< Free watchdog paused when system is in debug mode   
#define DEBUG_I2C1_SMBUS_PAUSE                  DBG_APB1CFG_I2C1_SMBUS_DBG_PAUSE    //!< I2C1 SMBUS paused when system is in debug mode      
#define DEBUG_CAN1_PAUSE                        DBG_APB1CFG_CAN_DBG_PAUSE           //!< CAN1 paused when system is in debug mode            

/** 
  * @brief Debug support mode for APB2 peripherals configuration register 
  */
#define DEBUG_TIM1_PAUSE                        DBG_APB2CFG_TIM1_DBG_PAUSE          //!< TIM1 counter paused when system is in debug mode  
#define DEBUG_TIM15_PAUSE                       DBG_APB2CFG_TIM15_DBG_PAUSE         //!< TIM15 counter paused when system is in debug mode 
#define DEBUG_TIM16_PAUSE                       DBG_APB2CFG_TIM16_DBG_PAUSE         //!< TIM16 counter paused when system is in debug mode 
#define DEBUG_TIM17_PAUSE                       DBG_APB2CFG_TIM17_DBG_PAUSE         //!< TIM17 counter paused when system is in debug mode 

/**
  * @brief The DEBUG function registers.
  */
#define DEBUG_ENABLE_REG_TIM2_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG TIM2 pause enable reg
#define DEBUG_ENABLE_REG_TIM3_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG TIM3 pause enable reg
#define DEBUG_ENABLE_REG_TIM6_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG TIM6 pause enable reg
#define DEBUG_ENABLE_REG_TIM7_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG TIM7 pause enable reg
#define DEBUG_ENABLE_REG_TIM14_PAUSE            (DBGMCU->APB1CFG)                   //!< DEBUG TIM14 pause enable reg
#define DEBUG_ENABLE_REG_RTC_PAUSE              (DBGMCU->APB1CFG)                   //!< DEBUG RTC pause enable reg
#define DEBUG_ENABLE_REG_WWDT_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG WWDT pause enable reg
#define DEBUG_ENABLE_REG_FWDT_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG FWDT pause enable reg
#define DEBUG_ENABLE_REG_I2C1_SMBUS_PAUSE       (DBGMCU->APB1CFG)                   //!< DEBUG I2C1 pause enable reg
#define DEBUG_ENABLE_REG_CAN1_PAUSE             (DBGMCU->APB1CFG)                   //!< DEBUG CAN1 pause enable reg
#define DEBUG_ENABLE_REG_TIM1_PAUSE             (DBGMCU->APB2CFG)                   //!< DEBUG TIM1 pause enable reg
#define DEBUG_ENABLE_REG_TIM15_PAUSE            (DBGMCU->APB2CFG)                   //!< DEBUG TIM15 pause enable reg
#define DEBUG_ENABLE_REG_TIM16_PAUSE            (DBGMCU->APB2CFG)                   //!< DEBUG TIM16 pause enable reg
#define DEBUG_ENABLE_REG_TIM17_PAUSE            (DBGMCU->APB2CFG)                   //!< DEBUG TIM17 pause enable reg

/**
  * @brief The DEBUG function enable bits.
  */ 
#define DEBUG_ENABLE_BIT_TIM2_PAUSE             (DEBUG_TIM2_PAUSE)                  //!< DEBUG TIM2 pause enable bits
#define DEBUG_ENABLE_BIT_TIM3_PAUSE             (DEBUG_TIM3_PAUSE)                  //!< DEBUG TIM3 pause enable bits
#define DEBUG_ENABLE_BIT_TIM6_PAUSE             (DEBUG_TIM6_PAUSE)                  //!< DEBUG TIM6 pause enable bits
#define DEBUG_ENABLE_BIT_TIM7_PAUSE             (DEBUG_TIM7_PAUSE)                  //!< DEBUG TIM7 pause enable bits
#define DEBUG_ENABLE_BIT_TIM14_PAUSE            (DEBUG_TIM14_PAUSE)                 //!< DEBUG TIM14 pause enable bits
#define DEBUG_ENABLE_BIT_RTC_PAUSE              (DEBUG_RTC_PAUSE)                   //!< DEBUG RTC pause enable bits
#define DEBUG_ENABLE_BIT_WWDT_PAUSE             (DEBUG_WWDT_PAUSE)                  //!< DEBUG WWDT pause enable bits
#define DEBUG_ENABLE_BIT_FWDT_PAUSE             (DEBUG_FWDT_PAUSE)                  //!< DEBUG FWDT pause enable bits
#define DEBUG_ENABLE_BIT_I2C1_SMBUS_PAUSE       (DEBUG_I2C1_SMBUS_PAUSE)            //!< DEBUG I2C1 pause enable bits
#define DEBUG_ENABLE_BIT_CAN1_PAUSE             (DEBUG_CAN1_PAUSE)                  //!< DEBUG CAN1 pause enable bits
#define DEBUG_ENABLE_BIT_TIM1_PAUSE             (DEBUG_TIM1_PAUSE)                  //!< DEBUG TIM1 pause enable bits
#define DEBUG_ENABLE_BIT_TIM15_PAUSE            (DEBUG_TIM15_PAUSE)                 //!< DEBUG TIM15 pause enable bits
#define DEBUG_ENABLE_BIT_TIM16_PAUSE            (DEBUG_TIM16_PAUSE)                 //!< DEBUG TIM16 pause enable bits
#define DEBUG_ENABLE_BIT_TIM17_PAUSE            (DEBUG_TIM17_PAUSE)                 //!< DEBUG TIM17 pause enable bits

/**
  * @}
  */ 
  
/**
  * @brief  Returns the device revision identifier(REVID).
  * @param  None.
  * @return Device revision identifier
  */
#define __DEBUG_REVISION_ID_GET()           (DBGMCU->ID >> 16)

/**
  * @brief  Returns the device identifier(DEVID).
  * @param  None.
  * @return Device identifier
  */
#define __DEBUG_DEVICE_ID_GET()             (DBGMCU->ID & 0x00000FFF)

/**
  * @brief  Enables low power mode behavior when the MCU is in Debug mode.
  * @param  MODE: It can be any combination of the following values:
  *          @arg DEBUG_MODE_DSM(stop mode debug support)
  *          @arg DEBUG_MODE_PWD(Standby mode debug support)
  * @return None
  */
#define __DEBUG_LOW_POWR_MODE_ENABLE(MODE)  (DBGMCU->LPWCFG |= MODE)

/**
  * @brief  Disables low power mode behavior when the MCU is in Debug mode.
  * @param  MODE: It can be any combination of the following values:
  *          @arg DEBUG_MODE_DSM(stop mode debug support)
  *          @arg DEBUG_MODE_PWD(Standby mode debug support)
  * @return None
  */
#define __DEBUG_LOW_POWR_MODE_DISABLE(MODE) (DBGMCU->LPWCFG &= ~(MODE))

/**
  * @brief  Enables the specified peripheral pause in debug mode. 
  * @param  PERI: specifies the DEBUG function.
  *         It can be one of the following values:
  *          @arg TIM2_PAUSE(TIM2 counter paused when system is in debug mode)
  *          @arg TIM3_PAUSE(TIM3 counter paused when system is in debug mode)
  *          @arg TIM6_PAUSE(TIM6 counter paused when system is in debug mode)
  *          @arg TIM7_PAUSE(TIM7 counter paused when system is in debug mode)
  *          @arg TIM14_PAUSE(TIM14 counter paused when system is in debug mode)
  *          @arg RTC_PAUSE(RTC counter paused when system is in debug mode)
  *          @arg WWDT_PAUSE( Debug WWDT stopped when system is in debug mode)
  *          @arg FWDT_PAUSE(Debug FWDT stopped when system is in debug mode)
  *          @arg I2C1_SMBUS_PAUSE(I2C1 SMBUS timeout mode stopped when system is in debug mode)
  *          @arg CAN1_PAUSE(Debug CAN stopped when system is in debug mode)
  *          @arg TIM1_PAUSE(TIM2 counter paused when system is in debug mode)
  *          @arg TIM15_PAUSE(TIM15 counter paused when system is in debug mode)
  *          @arg TIM16_PAUSE(TIM16 counter paused when system is in debug mode)
  *          @arg TIM17_PAUSE(TIM17 counter paused when system is in debug mode)
  * @return None
  */
#define __DEBUG_PERI_PAUSE_ENABLE(PERI)     ((DEBUG_ENABLE_REG_##PERI) |= (DEBUG_ENABLE_BIT_##PERI))

/**
  * @brief  Disables the specified peripheral pause in debug mode. 
  * @param  PERI: specifies the DEBUG function.
  *         It can be one of the following values:
  *          @arg TIM2_PAUSE(TIM2 counter paused when system is in debug mode)
  *          @arg TIM3_PAUSE(TIM3 counter paused when system is in debug mode)
  *          @arg TIM6_PAUSE(TIM6 counter paused when system is in debug mode)
  *          @arg TIM7_PAUSE(TIM7 counter paused when system is in debug mode)
  *          @arg TIM14_PAUSE(TIM14 counter paused when system is in debug mode)
  *          @arg RTC_PAUSE(RTC counter paused when system is in debug mode)
  *          @arg WWDT_PAUSE( Debug WWDT stopped when system is in debug mode)
  *          @arg FWDT_PAUSE(Debug FWDT stopped when system is in debug mode)
  *          @arg I2C1_SMBUS_PAUSE(I2C1 SMBUS timeout mode stopped when system is in debug mode)
  *          @arg CAN1_PAUSE(Debug CAN stopped when system is in debug mode)
  *          @arg TIM1_PAUSE(TIM2 counter paused when system is in debug mode)
  *          @arg TIM15_PAUSE(TIM15 counter paused when system is in debug mode)
  *          @arg TIM16_PAUSE(TIM16 counter paused when system is in debug mode)
  *          @arg TIM17_PAUSE(TIM17 counter paused when system is in debug mode)
  * @return None
  */
#define __DEBUG_PERI_PAUSE_DISABLE(PERI)    ((DEBUG_ENABLE_REG_##PERI) &= ~(DEBUG_ENABLE_BIT_##PERI))

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

