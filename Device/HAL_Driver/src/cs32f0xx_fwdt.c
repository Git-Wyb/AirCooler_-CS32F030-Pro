/**
  * @file    cs32f0xx_fwdt.c  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Free Watchdog Timer(FWDT) peripheral:           
  *           + Prescaler and Counter configuration
  *           + FWDT activation
  *           + Flag management
  *
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
    The driver using to FWDT peripheral with either window option enabled or disabled.         
    1. Window option is enabled:    
        a.Start the FWDT using fwdt_enable() function, when the FWDT is used
             in software mode (no need to enable the LRC, it will be enabled by hardware).                     
        b.FWDT_PDIV and FWDT_UVAL registers can be accessed by
             fwdt_write_access_enable_ctrl() function.
        c.Configure the FWDT prescaler using fwdt_prescaler_set() function.
        d.Configure the FWDT counter value using fwdt_reload_set() function.
             This value will be loaded in the FWDT counter each time the counter
             is reloaded, then the FWDT will start counting down from this value.
        e.Wait for the FWDT registers to be updated using fwdt_flag_status_get() function.
        f. Configure the FWDT refresh window using fwdt_window_value_set() function.

    2. Window option is disabled:    
        a. Enable write access to FWDT_PDIV and FWDT_UVAL registers using
             fwdt_write_access_enable_ctrl() function.
        b. Configure the FWDT prescaler using fwdt_prescaler_set() function.
        c. Configure the FWDT counter value using fwdt_reload_set() function.
             This value will be loaded in the FWDT counter each time the counter
             is reloaded, then the FWDT will start counting down from this value.
        d. Wait for the FWDT registers to be updated using fwdt_flag_status_get() function.
        e. reload the FWDT counter at regular intervals during normal operation 
             to prevent an MCU reset, using fwdt_reload_counter() function.
        f. Start the FWDT using fwdt_enable() function, when the FWDT is used
             in software mode (no need to enable the LRC, it will be enabled
             by hardware).
              
    @endverbatim
  *
  */


#include "cs32f0xx_fwdt.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup FWDT
  * @brief FWDT driver modules
  * @{
  */ 



/**
  * @}
  */


/**
  * @}
  */

