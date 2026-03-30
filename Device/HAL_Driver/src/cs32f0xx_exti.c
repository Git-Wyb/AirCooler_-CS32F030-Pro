/**
  * @file    cs32f0xx_exti.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the EXTI peripheral:Initialization and Configuration; 
  *          Interrupts and flags management.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
    1. In order to use an I/O pin as an external interrupt source, follow steps below:         
      a.Configure the I/O in input mode using gpio_init().
      b. Select the input source pin for the EXTI line using syscfg_exti_line_config().        
      c. Select the mode(interrupt, event) and configure the trigger selection 
        (Rising, falling or both) using exti_init(). For the internal interrupt,
        the trigger selection is not needed( the active edge is always the rising one).
      d. Configure NVIC IRQ channel mapped to the EXTI line using nvic_init().
      e. Optionally, you can generate a software     interrupt using the function exti_sw_interrupt_trigger().
      f. SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
      registers using rcu_apb2_periph_clock_enable_ctrl(RCU_APB2_PERI_SYSCFG, ENABLE);
    @endverbatim
  *
  */

#include "cs32f0xx_exti.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup EXTI
  * @{
  */


/**
  * @fn void exti_def_init(void)
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @return None
  */
void exti_def_init(void)
{
    EXTI->INTEN = 0x0FF40000;
    EXTI->EVTEN = 0x00000000;
  
    EXTI->RTEN = 0x00000000;
    EXTI->FTEN = 0x00000000;
    EXTI->PDF = 0x00000000;
}


/**
  * @}
  */

/**
  * @}
  */

