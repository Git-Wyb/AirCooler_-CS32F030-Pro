/**
  * @file    cs32f0xx_misc.c
  * @brief   This file provides all the miscellaneous firmware functions. 
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
      It provide functions allowing to configure the NVIC interrupts (IRQ).
      The Cortex-M0 exceptions are managed by CMSIS functions.
      1. Enable and Configure the priority of the selected IRQ Channels,
         The priority can be 0.1.2.3.                
    @endverbatim
  *
  */

#include "cs32f0xx_misc.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup MISC 
  * @{
  */


/**
  * @fn void nvic_init(nvic_config_t* ptr_config)
  * @brief  Initializes the NVIC peripheral according to the specified parameters in the ptr_config.
  * @param  ptr_config: pointer to a nvic_config_t structure that contains the configuration information for the specified
  *         NVIC peripheral.
  * @return None.
  */
void nvic_init(nvic_config_t* ptr_config)
{
    ASSERT(FUNCTIONAL_STATE_CHECK(ptr_config->enable_flag));
    ASSERT(NVIC_PRIORITY_CHECK(ptr_config->priority));  
    
    if (ptr_config->enable_flag != DISABLE)
    {
        MODIFY_REG(NVIC->IP[ptr_config->IRQn >> 0x02], ((uint32_t)0xFF) << ((ptr_config->IRQn & 0x03) * 8), \
                   (((uint32_t)ptr_config->priority << 6) & 0xFF) << ((ptr_config->IRQn & 0x03) * 8));
    
        /* Enable the Selected IRQ Channels */
        NVIC->ISER[0] = (uint32_t)0x01 << (ptr_config->IRQn & (uint8_t)0x1F);
    }
    else
    {
        /* Disable the Selected IRQ Channels */
        NVIC->ICER[0] = (uint32_t)0x01 << (ptr_config->IRQn & (uint8_t)0x1F);
    }
}

/**
  * @fn void systick_clock_config(uint32_t select)
  * @brief  Configures the SysTick clock source.
  * @param  select: specifies the SysTick clock source. It can be one of following values: 
  *         @arg SYSTICK_CLKSEL_HCLK_DIV8
  *         @arg SYSTICK_CLKSEL_HCLK
  * @return None.
  */
void systick_clock_config(uint32_t select)
{
    ASSERT(SYSTICK_CLKSEL_CHECK(select)); 
    
    MODIFY_REG(SysTick->CTRL, SYSTICK_CLKSEL_HCLK, select);
}


/**
  * @}
  */

/**
  * @}
  */

