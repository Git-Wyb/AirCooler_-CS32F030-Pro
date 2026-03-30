/**
  * @file    cs32f0xx_wwdt.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Window Watchdog Timer(WWDT) peripheral:
  *           + Prescaler, Refresh window and Counter configuration
  *           + WWDT activation
  *           + Interrupts and flags management

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
        1. Enable WWDT clock using rcu_apb1_periph_clock_enable_ctrl(RCU_APB1_PERI_WWDT, ENABLE) 
            function.
              
        2. Configure the WWDT prescaler using wwdt_prescaler_set() function.
                             
        3. Configure the WWDT refresh window using wwdt_window_value_set() function.
              
        4. Set the WWDT counter value and start it using wwdt_enable() function.
            When the WWDT is enabled the counter value should be configured to 
            a value greater than 0x40 to prevent generating an immediate reset.
              
        5. Optionally you can enable the Early wakeup interrupt which is 
            generated when the counter reach 0x40.
            Once enabled this interrupt cannot be disabled except by a system reset.
                   
        6. Then the application program must refresh the WWDT counter at regular
            intervals during normal operation to prevent an MCU reset, using
            wwdt_counter_set() function. This operation must occur only when
            the counter value is lower than the refresh window value, 
            programmed using wwdt_window_value_set().
  
     @endverbatim
  *
  */  

#include "cs32f0xx_wwdt.h"
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup WWDT
  * @brief WWDT driver modules
  * @{
  */
  

/**
  *@fn void wwdt_prescaler_set(uint32_t wwdt_prescaler)
  * @brief  Sets the WWDT Prescaler.
  * @param  wwdt_prescaler: specifies the WWDT prescaler. This parameter can be one of the following values:
  *         @arg WWDT_PRESCALER_1 (WWDT counter clock = (PCLK1/4096)/1)
  *         @arg WWDT_PRESCALER_2 (WWDT counter clock = (PCLK1/4096)/2)
  *         @arg WWDT_PRESCALER_4 (WWDT counter clock = (PCLK1/4096)/4)
  *         @arg WWDT_PRESCALER_8 (WWDT counter clock = (PCLK1/4096)/8)
  * @return None
  */
void wwdt_prescaler_set(uint32_t wwdt_prescaler)
{ 
    ASSERT(WWDT_PRESCALER_CHECK(wwdt_prescaler));
    
    MODIFY_REG(WWDT->CTR2, (uint32_t)WWDT_CTR2_PDIV, wwdt_prescaler);
}

/**
  *@fn void wwdt_window_value_set(uint8_t window_value)
  * @brief  Sets the WWDT window value.
  * @param  window_value: specifies the window value to be compared to the downcounter. This parameter value must be
  *         lower than 0x80.
  * @return None.
  */
void wwdt_window_value_set(uint8_t window_value)
{
    ASSERT(WWDT_WINDOW_VALUE_CHECK(window_value));

    MODIFY_REG(WWDT->CTR2, (uint32_t)WWDT_CTR2_WVAL, (uint32_t)(window_value & WWDT_BIT_MASK));
}


/**
  * @}
  */

/**
  * @}
  */
