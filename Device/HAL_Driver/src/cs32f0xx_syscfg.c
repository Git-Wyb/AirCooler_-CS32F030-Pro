/**
  * @file    cs32f0xx_syscfg.c  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the SYSCFG peripheral:
  *             Remapping the memory mapped at 0x00000000;  
  *             Remapping the DMA channels;
  *             Enabling I2C fast mode plus driving capability for I2C pins;   
  *             Configuring the EXTI lines connection to the GPIO port;
  *             Configuring the ERRLOCK features (SYSCFG error and timer break lock).
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#include "cs32f0xx_syscfg.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup SYSCFG 
  * @{
  */ 


/**
  * @fn void syscfg_def_init(void)
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @note   MEM_REMAP and ERRLOCK are not affected by APB reset.
  * @param  None
  * @return None
  */
void syscfg_def_init(void)
{
    /* Set SYSCFG_CFGR1 register to reset value without affecting MEM_RMAP bit */
    SYSCFG->RMAPCFG &= SYSCFG_RMAPCFG_MEM_RMAP;
    SYSCFG->EXTISRC[0] = 0;
    SYSCFG->EXTISRC[1] = 0;
    SYSCFG->EXTISRC[2] = 0;
    SYSCFG->EXTISRC[3] = 0;
	
    /*  clear SRAM parity error flag */
    SYSCFG->ERRLOCK |= SYSCFG_ERRLOCK_SRAM_PRTY_ERR;
}

/**
  * @fn void syscfg_memory_remap_set(uint32_t value)
  * @brief  Set the memory mapping at address 0x00000000.
  * @param  value: selects the memory remapping, it can be:
  *          @arg SYSCFG_MEM_REMAP_FLASH(Main Flash memory mapped at 0x00000000)
  *          @arg SYSCFG_MEM_REMAP_SYS_MEMORY(System Flash memory mapped at 0x00000000)
  *          @arg SYSCFG_MEM_REMAP_SRAM(Embedded SRAM mapped at 0x00000000)
  * @return None
  */
void syscfg_memory_remap_set(uint32_t value)
{
    ASSERT(SYSCFG_MEM_REMAP_CHECK(value));

    /* Set the memory remap value */
	MODIFY_REG(SYSCFG->RMAPCFG, SYSCFG_RMAPCFG_MEM_RMAP, value);
}

/**
  * @fn void syscfg_exti_line_config(uint8_t port, uint8_t pin)
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  port: selects the GPIO port to be used as source for EXTI lines. It can be one of following values:
  *                 @arg SYSCFG_EXTI_PORT_PA
  *                 @arg SYSCFG_EXTI_PORT_PB
  *                 @arg SYSCFG_EXTI_PORT_PC
  *                 @arg SYSCFG_EXTI_PORT_PF
  * @param  pin: specifies the EXTI line to be configured. 
  *              It can be a value between SYSCFG_EXTI_PIN_0 ~ SYSCFG_EXTI_PIN_15.
  * @return None
  */
void syscfg_exti_line_config(uint8_t port, uint8_t pin)
{
	uint8_t idx = 0x00;
	uint8_t shift = 0x00;

    ASSERT(SYSCFG_EXTI_PORT_CHECK(port));
    ASSERT(SYSCFG_EXTI_PIN_CHECK(pin));

	idx = pin >> 2;
	shift = (pin & 0x03) * 4;
	
	MODIFY_REG(SYSCFG->EXTISRC[idx], (uint32_t)0x0F << shift, (uint32_t)port << shift);	
}

/**
  * @fn void syscfg_gpio_vth_config(uint8_t port, uint8_t pin, uint8_t volt)
  * @brief  Configures the GPIO threshold voltage.
  * @note   This is only available for CS32F03X-RA devices.
  * @param  port: specifies the GPIO port to configure.                    
  * @param  pin: specifies the GPIO pin to configure.
  * @param  volt: specifies the threshold voltage to configure. 
  *			It can be one of the following values:
  *          @arg SYSCFG_GPIO_VTH_1V8 (Set threshold voltage is 1.8V or 1.2V)
  *          @arg SYSCFG_GPIO_VTH_VDD (Set threshold voltage is VDD) 
  * @return None
  */
void syscfg_gpio_vth_config(uint8_t port, uint8_t pin, uint8_t volt)
{
    ASSERT(SYSCFG_VTH_PORT_CHECK(port));
    ASSERT(SYSCFG_VTH_PIN_CHECK(pin));	
	ASSERT(SYSCFG_GPIO_VTH_CHECK(volt));

	MODIFY_REG(SYSCFG->GPIO_VTH[port], (uint32_t)0x03 << (pin * 2), (uint32_t)volt << (pin * 2));
}


/**
  * @}
  */ 

/**
  * @}
  */ 

