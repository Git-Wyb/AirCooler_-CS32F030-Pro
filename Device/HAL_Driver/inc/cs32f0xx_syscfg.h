/**
  * @file    cs32f0xx_syscfg.h
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_SYSCFG_H__
#define __CS32F0XX_SYSCFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */

/** @defgroup SYSCFG_Exported_Constants
  * @{
  */

/** 
  * @brief SYSCFG EXTI Port Sources definition
  */ 
#define SYSCFG_EXTI_PORT_PA				((uint8_t)0x00)		//!< External interrupt port source from GPIO A 
#define SYSCFG_EXTI_PORT_PB       		((uint8_t)0x01) 	//!< External interrupt port source from GPIO B
#define SYSCFG_EXTI_PORT_PC       		((uint8_t)0x02) 	//!< External interrupt port source from GPIO C
#define SYSCFG_EXTI_PORT_PF       		((uint8_t)0x05) 	//!< External interrupt port source from GPIO F

#define SYSCFG_EXTI_PORT_CHECK(port) 	(((port) == SYSCFG_EXTI_PORT_PA) || ((port) == SYSCFG_EXTI_PORT_PB) || \
                                     	((port) == SYSCFG_EXTI_PORT_PC) ||  ((port) == SYSCFG_EXTI_PORT_PF))

/**  
  * @brief SYSCFG EXTI pin Sources definition
  */ 
#define SYSCFG_EXTI_PIN_0				((uint8_t)0x00) 	//!< External interrupt from pin 0
#define SYSCFG_EXTI_PIN_1            	((uint8_t)0x01) 	//!< External interrupt from pin 1
#define SYSCFG_EXTI_PIN_2            	((uint8_t)0x02) 	//!< External interrupt from pin 2
#define SYSCFG_EXTI_PIN_3            	((uint8_t)0x03) 	//!< External interrupt from pin 3
#define SYSCFG_EXTI_PIN_4            	((uint8_t)0x04) 	//!< External interrupt from pin 4
#define SYSCFG_EXTI_PIN_5            	((uint8_t)0x05) 	//!< External interrupt from pin 5
#define SYSCFG_EXTI_PIN_6            	((uint8_t)0x06) 	//!< External interrupt from pin 6
#define SYSCFG_EXTI_PIN_7            	((uint8_t)0x07) 	//!< External interrupt from pin 7
#define SYSCFG_EXTI_PIN_8            	((uint8_t)0x08) 	//!< External interrupt from pin 8
#define SYSCFG_EXTI_PIN_9            	((uint8_t)0x09) 	//!< External interrupt from pin 9
#define SYSCFG_EXTI_PIN_10           	((uint8_t)0x0A) 	//!< External interrupt from pin 10
#define SYSCFG_EXTI_PIN_11           	((uint8_t)0x0B) 	//!< External interrupt from pin 11
#define SYSCFG_EXTI_PIN_12           	((uint8_t)0x0C) 	//!< External interrupt from pin 12
#define SYSCFG_EXTI_PIN_13           	((uint8_t)0x0D) 	//!< External interrupt from pin 13
#define SYSCFG_EXTI_PIN_14           	((uint8_t)0x0E) 	//!< External interrupt from pin 14
#define SYSCFG_EXTI_PIN_15           	((uint8_t)0x0F) 	//!< External interrupt from pin 15

#define SYSCFG_EXTI_PIN_CHECK(pin)		(((pin) == SYSCFG_EXTI_PIN_0) || ((pin) == SYSCFG_EXTI_PIN_1)  || \
                                       	((pin) == SYSCFG_EXTI_PIN_2)  ||  ((pin) == SYSCFG_EXTI_PIN_3)  || \
                                       	((pin) == SYSCFG_EXTI_PIN_4)  ||  ((pin) == SYSCFG_EXTI_PIN_5)  || \
                                       	((pin) == SYSCFG_EXTI_PIN_6)  ||  ((pin) == SYSCFG_EXTI_PIN_7)  || \
                                       	((pin) == SYSCFG_EXTI_PIN_8)  ||  ((pin) == SYSCFG_EXTI_PIN_9)  || \
                                       	((pin) == SYSCFG_EXTI_PIN_10) ||  ((pin) == SYSCFG_EXTI_PIN_11) || \
                                       	((pin) == SYSCFG_EXTI_PIN_12) ||  ((pin) == SYSCFG_EXTI_PIN_13) || \
                                       	((pin) == SYSCFG_EXTI_PIN_14) ||  ((pin) == SYSCFG_EXTI_PIN_15))

/** 
  * @brief SYSCFG VTH Port Sources definition
  */ 
#define SYSCFG_VTH_PORT_PA				((uint8_t)0x00) 	//!< GPIO PORTA for VTH config 
#define SYSCFG_VTH_PORT_PB       		((uint8_t)0x01) 	//!< GPIO PORTB for VTH config 

#define SYSCFG_VTH_PORT_CHECK(port) 	(((port) == SYSCFG_VTH_PORT_PA) || ((port) == SYSCFG_VTH_PORT_PB))

/**  
  * @brief SYSCFG VTH pin Sources definition
  */ 
#define SYSCFG_VTH_PIN_6            	((uint8_t)0x06) 	//!< GPIO PIN6 for VTH config 
#define SYSCFG_VTH_PIN_7            	((uint8_t)0x07) 	//!< GPIO PIN7 for VTH config 
#define SYSCFG_VTH_PIN_8            	((uint8_t)0x08) 	//!< GPIO PIN8 for VTH config 
#define SYSCFG_VTH_PIN_9            	((uint8_t)0x09) 	//!< GPIO PIN9 for VTH config 
#define SYSCFG_VTH_PIN_10           	((uint8_t)0x0A) 	//!< GPIO PIN10 for VTH config 

#define SYSCFG_VTH_PIN_CHECK(pin) 		(((pin) == SYSCFG_VTH_PIN_6)  ||  ((pin) == SYSCFG_VTH_PIN_7)  || \
                                       	((pin) == SYSCFG_VTH_PIN_8)  ||  ((pin) == SYSCFG_VTH_PIN_9)   || \
                                       	((pin) == SYSCFG_VTH_PIN_10))
/**  
  * @brief SYSCFG VTH pin Sources definition
  */ 
#define SYSCFG_GPIO_VTH_1V8				((uint32_t)0x01)	//!< Threshold voltage is 1.8V or 1.2V
#define SYSCFG_GPIO_VTH_VDD				((uint32_t)0x00)	//!< Threshold voltage is VDD

#define SYSCFG_GPIO_VTH_CHECK(volt) 	(((volt) == SYSCFG_GPIO_VTH_1V8) || ((volt) == SYSCFG_GPIO_VTH_VDD))

/** 
  * @brief SYSCFG Memory Remap definition
  */ 
#define SYSCFG_MEM_REMAP_FLASH			((uint8_t)0x00)		//!< Remap main flash memory 
#define SYSCFG_MEM_REMAP_SYS_MEMORY		((uint8_t)0x01)		//!< Remap system flash memory 
#define SYSCFG_MEM_REMAP_SRAM			((uint8_t)0x03)		//!< Remap embedded SRAM 

#define SYSCFG_MEM_REMAP_CHECK(flag) 	(((flag) == SYSCFG_MEM_REMAP_FLASH) || ((flag) == SYSCFG_MEM_REMAP_SYS_MEMORY) || \
                                      	((flag) == SYSCFG_MEM_REMAP_SRAM))
/** 
  * @brief SYSCFG Lock Config
  */ 
#define SYSCFG_TIM_BREAK_LVD            SYSCFG_ERRLOCK_LVD_TIMBRK_LOCK			//!< Connects the LVD event to TIM1 break enable, not available for CS32F030 devices 
#define SYSCFG_TIM_BREAK_SRAM_PARITY    SYSCFG_ERRLOCK_SRAM_PRTY_TIMBRK_LOCK	//!< Connects the SRAM_PARITY error signal to TIM1 break enable
#define SYSCFG_TIM_BREAK_LOCKUP         SYSCFG_ERRLOCK_LOCKUP_TIMBRK_LOCK     	//!< Connects Lockup output of CortexM0 to TIM1 break enable

/** 
  * @brief SYSCFG DMA remap config definition
  */ 
#define SYSCFG_DMA_REMAP_TIM17       	SYSCFG_RMAPCFG_TIM17_DMA_CHRMAP     	//!< Remap TIM17 DMA requests from channel 1 to channel 2 
#define SYSCFG_DMA_REMAP_TIM16       	SYSCFG_RMAPCFG_TIM16_DMA_CHRMAP     	//!< Remap TIM16 DMA requests from channel 3 to channel 4
#define SYSCFG_DMA_REMAP_USART1RX    	SYSCFG_RMAPCFG_USART1RX_DMA_CHRMAP  	//!< Remap USART1 Rx DMA requests from channel 3 to channel 5
#define SYSCFG_DMA_REMAP_USART1TX    	SYSCFG_RMAPCFG_USART1TX_DMA_CHRMAP  	//!< Remap USART1 Tx DMA requests from channel 2 to channel 4
#define SYSCFG_DMA_REMAP_ADC1        	SYSCFG_RMAPCFG_ADC_DMA_CHRMAP       	//!< Remap ADC1 DMA requests from channel 1 to channel 2                          

/** 
  * @brief SYSCFG I2C FM+ config definition
  */ 
#define SYSCFG_I2CFastModePlus_PB6		SYSCFG_RMAPCFG_I2C_FMPEN_PB6			//!< PB6 I2C Fast Mode Plus (FM+)
#define SYSCFG_I2CFastModePlus_PB7		SYSCFG_RMAPCFG_I2C_FMPEN_PB7			//!< PB7 I2C Fast Mode Plus (FM+)
#define SYSCFG_I2CFastModePlus_PB8		SYSCFG_RMAPCFG_I2C_FMPEN_PB8			//!< PB8 I2C Fast Mode Plus (FM+)
#define SYSCFG_I2CFastModePlus_PB9		SYSCFG_RMAPCFG_I2C_FMPEN_PB9			//!< PB9 I2C Fast Mode Plus (FM+)
#define SYSCFG_I2CFastModePlus_PA9		SYSCFG_RMAPCFG_I2C_FMPEN_PA9			//!< Fast Mode Plus on PA9
#define SYSCFG_I2CFastModePlus_PA10		SYSCFG_RMAPCFG_I2C_FMPEN_PA10			//!< Fast Mode Plus on PA10

/**  
  * @brief SYSCFG SRAM PE(parity error) flag definition
  */
#define SYSCFG_FLAG_PE             		SYSCFG_ERRLOCK_SRAM_PRTY_ERR			//!< SRAM parity error flag

/**
  * @}
  */ 

/**
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @note   MEM_REMAP and ERRLOCK are not affected by APB reset.
  * @param  None
  * @return None
  */
#define __SYSCFG_DEF_INIT()					syscfg_def_init()	


/**
  * @brief  Connect the selected parameter to the TIM1 break.
  * @note   The selected configuration is locked and can be unlocked by system reset
  * @param  VALUE: selects the configuration to be connected to TIM1 break. It can be 
  *          @arg SYSCFG_TIM_BREAK_LVD (Connects the LVD event to TIM1 break enable)
  *          @arg SYSCFG_TIM_BREAK_SRAM_PARITY(Connects the SRAM_PARITY error signal to TIM1 break enable)
  *          @arg SYSCFG_TIM_BREAK_LOCKUP(Connects Lockup output of CortexM0 to TIM1 break enable)
  * @return None
  */
#define __SYSCFG_TIME_BREAK_SET(VALUE)		(SYSCFG->ERRLOCK |= VALUE)

/**
  * @brief  Enables the specified function of SYSCFG.
  * @param  FUNC: specifies the function to enable. 
  *			It can be any combination of the following values:  
  *          @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *          @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *          @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *          @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *          @arg SYSCFG_I2CFastModePlus_PA9: Configure fast mode plus driving capability for PA9 
  *          @arg SYSCFG_I2CFastModePlus_PA10: Configure fast mode plus driving capability for PA10
  *          @arg SYSCFG_DMA_REMAP_TIM17: Remap TIM17 DMA from channel 1 to channel 2
  *          @arg SYSCFG_DMA_REMAP_TIM16: Remap TIM16 DMA from channel 3 to channel 4
  *          @arg SYSCFG_DMA_REMAP_USART1RX: Remap USART1 Rx DMA from channel 3 to channel 5
  *          @arg SYSCFG_DMA_REMAP_USART1TX: Remap USART1 Tx DMA from channel 2 to channel 4
  *          @arg SYSCFG_DMA_REMAP_ADC1: Remap ADC1 DMA requests from channel 1 to channel 2
  * @return None
  */
#define __SYSCFG_FUNC_ENABLE(FUNC)			(SYSCFG->RMAPCFG |= FUNC)

/**
  * @brief  Disables the specified function of SYSCFG.
  * @param  FUNC: specifies the function to disable. 
  *			It can be any combination of the following values:  
  *          @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *          @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *          @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *          @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *          @arg SYSCFG_I2CFastModePlus_PA9: Configure fast mode plus driving capability for PA9 
  *          @arg SYSCFG_I2CFastModePlus_PA10: Configure fast mode plus driving capability for PA10
  *          @arg SYSCFG_DMA_REMAP_TIM17: Remap TIM17 DMA from channel 1 to channel 2
  *          @arg SYSCFG_DMA_REMAP_TIM16: Remap TIM16 DMA from channel 3 to channel 4
  *          @arg SYSCFG_DMA_REMAP_USART1RX: Remap USART1 Rx DMA from channel 3 to channel 5
  *          @arg SYSCFG_DMA_REMAP_USART1TX: Remap USART1 Tx DMA from channel 2 to channel 4
  *          @arg SYSCFG_DMA_REMAP_ADC1: Remap ADC1 DMA requests from channel 1 to channel 2
  * @return None
  */
#define __SYSCFG_FUNC_DISABLE(FUNC)			(SYSCFG->RMAPCFG &= ~(FUNC))

/**
  * @brief   Checks whether the specified SYSCFG flag is set or not.
  * @param   FLAG: specifies the SYSCFG flag to check. It can be
  *          @arg SYSCFG_FLAG_PE(SRAM parity error flag)
  * @return  state SET or RESET.
  */
#define __SYSCFG_FLAG_STATUS_GET(FLAG)		((SYSCFG->ERRLOCK & (FLAG)) ? SET : RESET)

/**
  * @brief  Clears the selected SYSCFG flag.
  * @param  FLAG: selects the flag to be cleared, it can be 
  *          @arg SYSCFG_FLAG_PE(SRAM parity error flag)
  * @return None
  */
#define __SYSCFG_FLAG_CLEAR(FLAG)	(SYSCFG->ERRLOCK |= FLAG)

/**
  * @fn void syscfg_def_init(void)
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @note   MEM_REMAP and ERRLOCK are not affected by APB reset.
  * @param  None
  * @return None
  */
void syscfg_def_init(void);

/**
  * @fn void syscfg_memory_remap_set(uint32_t value)
  * @brief  Set the memory mapping at address 0x00000000.
  * @param  value: selects the memory remapping, it can be:
  *          @arg SYSCFG_MEM_REMAP_FLASH(Main Flash memory mapped at 0x00000000)
  *          @arg SYSCFG_MEM_REMAP_SYS_MEMORY(System Flash memory mapped at 0x00000000)
  *          @arg SYSCFG_MEM_REMAP_SRAM(Embedded SRAM mapped at 0x00000000)
  * @return None
  */
void syscfg_memory_remap_set(uint32_t value);

/**
  * @fn void syscfg_exti_line_config(uint8_t port, uint8_t pin)
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  port: selects the GPIO port to be used as source for EXTI lines. It can be one of following values:
  *                 @arg SYSCFG_EXTI_PORT_PA
  *                 @arg SYSCFG_EXTI_PORT_PB
  *                 @arg SYSCFG_EXTI_PORT_PC
  *                 @arg SYSCFG_EXTI_PORT_PF
  * @param  pin: specifies the EXTI line to be configured. 
  *              It can be a value between SYSCFG_EXTI_PIN_0 ~ SYSCFG_EXTI_PIN_15
  * @return None
  */
void syscfg_exti_line_config(uint8_t port, uint8_t pin);

/**
  * @fn void syscfg_gpio_vth_config(uint8_t port, uint8_t pin, uint8_t volt)
  * @brief	Configures the GPIO threshold voltage.
  * @note	This is only available for CS32F03X-RA devices.
  * @param	port: specifies the GPIO port to configure. 				   
  * @param	pin: specifies the GPIO pin to configure.
  * @param	volt: specifies the threshold voltage to configure. 
  * 		It can be one of the following values:
  * 		 @arg SYSCFG_GPIO_VTH_1V8 (Set threshold voltage is 1.8V or 1.2V)
  * 		 @arg SYSCFG_GPIO_VTH_VDD (Set threshold voltage is VDD) 
  * @return None
  */
void syscfg_gpio_vth_config(uint8_t port, uint8_t pin, uint8_t volt);

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

