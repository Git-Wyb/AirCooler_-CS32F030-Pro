/**
  * @file    cs32f0xx_fwdt.h
  * @brief   This file contains all the functions prototypes for the FWDT 
  *          firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_FWDT_H__
#define __CS32F0XX_FWDT_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup FWDT
  * @{
  */

/** @defgroup FWDT_Exported_Constants
  * @{
  */


/**  
  *@brief FWDT write access
  */
#define FWDT_WRITE_ACCESS_ENABLE    ((uint16_t)0x5555)  //!< FWDT write access enable
#define FWDT_WRITE_ACCESS_DISABLE   ((uint16_t)0x0000)  //!< FWDT write access disable

/**
  *@brief FWDT CCODE register bit mask 
  */
#define CCODE_CCODE_RELOAD          ((uint16_t)0xAAAA)  //!< reload counter
#define CCODE_CCODE_ENABLE          ((uint16_t)0xCCCC)  //!< FWDT enable

/**  
  *@brief FWDT prescaler selection
  */
#define FWDT_PRESCALER_4            ((uint8_t)0x00)     //!<FWDT prescaler divider 4
#define FWDT_PRESCALER_8            ((uint8_t)0x01)     //!<FWDT prescaler divider 8
#define FWDT_PRESCALER_16           ((uint8_t)0x02)     //!<FWDT prescaler divider 16
#define FWDT_PRESCALER_32           ((uint8_t)0x03)     //!<FWDT prescaler divider 32
#define FWDT_PRESCALER_64           ((uint8_t)0x04)     //!<FWDT prescaler divider 64
#define FWDT_PRESCALER_128          ((uint8_t)0x05)     //!<FWDT prescaler divider 128
#define FWDT_PRESCALER_256          ((uint8_t)0x06)     //!<FWDT prescaler divider 256

/** 
  *@ brief FWDT STS register flag 
  */
#define FWDT_FLAG_DRF               FWDT_STS_DRF        //!< Prescaler value update flag
#define FWDT_FLAG_UVRF              FWDT_STS_UVRF       //!< Reload value update flag
#define FWDT_FLAG_WRF               FWDT_STS_WRF        //!< Window value update flag

/**
  * @}
  */ 

/**
  * @brief  Enables write access to FWDT_PDIV and FWDT_UVAL registers.
  * @param  None.
  * @return None.
  */
#define __FWDT_WRITE_ACCESS_ENABLE()    (FWDT->CCODE = FWDT_WRITE_ACCESS_ENABLE)

/**
  * @brief  Disables write access to FWDT_PDIV and FWDT_UVAL registers.
  * @param  None.
  * @return None.
  */
#define __FWDT_WRITE_ACCESS_DISABLE()   (FWDT->CCODE = FWDT_WRITE_ACCESS_DISABLE)

/**
  * @brief  Sets FWDT Prescaler value.
  * @param  VALUE: specifies the FWDT Prescaler value. This parameter can be one of the following values:
  *         @arg FWDT_PRESCALER_4(FWDT prescaler set to 4)
  *         @arg FWDT_PRESCALER_8(FWDT prescaler set to 8)
  *         @arg FWDT_PRESCALER_16(FWDT prescaler set to 16)
  *         @arg FWDT_PRESCALER_32(FWDT prescaler set to 32)
  *         @arg FWDT_PRESCALER_64(FWDT prescaler set to 64)
  *         @arg FWDT_PRESCALER_128(FWDT prescaler set to 128)
  *         @arg FWDT_PRESCALER_256(FWDT prescaler set to 256)
  * @return None.
  */
#define __FWDT_PRESCALER_SET(VALUE)     (FWDT->PDIV = VALUE)

/**
  * @brief  Sets FWDT Reload value.
  * @param  VALUE: specifies the FWDT Reload value. This parameter must be a number between 0 and 0x0FFF.
  * @return None.
  */
#define __FWDT_RELOAD_VALUE_SET(VALUE)  (FWDT->UVAL = VALUE)

/**
  * @brief  Reloads FWDT counter with value defined in the reload register
  * @param  None.
  * @return None.
  */
#define __FWDT_RELOAD_COUNTER()         (FWDT->CCODE = CCODE_CCODE_RELOAD)

/**
  * @brief  Sets the FWDT window value.
  * @param  VALUE: specifies the window value to be compared to the downcounter.  This parameter must be a number between 
  *         0 and 0x0FFF.
  * @return None.
  */
#define __FWDT_WINDOW_VALUE_SET(VALUE)  (FWDT->WINVAL = VALUE)

/**
  * @brief  Enables FWDT (write access to FWDT_PDIV and FWDT_UVAL registers disabled).
  * @param  None.
  * @return None.
  */
#define __FWDT_ENABLE()                 (FWDT->CCODE = CCODE_CCODE_ENABLE)

/**
  * @brief  Checks whether the specified FWDT flag is set or not.
  * @param  FLAG: specifies the flag to check. It can be one of the following values:           
  *         DRF(prescaler value update flag)
  *         UVRF(reload value update flag)
  *         WRF(window value update flag)
  * @return bit status (SET or RESET).
  */
#define __FWDT_FLAG_STATUS_GET(FLAG)    ((FWDT->STS & (FWDT_FLAG_##FLAG)) ? SET : RESET)


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
  
