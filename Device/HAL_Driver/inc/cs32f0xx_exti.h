/**
  * @file    cs32f0xx_exti.h
  * @brief   This file contains all the functions prototypes for the EXTI firmware library
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_EXTI_H__
#define __CS32F0XX_EXTI_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/** @defgroup EXTI_Exported_Constants
  * @{
  */

/** 
  * @brief EXTI_Lines
  */  
#define EXTI_LINE_0       				((uint32_t)0x00000001)  //!< External interrupt line 0  
#define EXTI_LINE_1       				((uint32_t)0x00000002)  //!< External interrupt line 1  
#define EXTI_LINE_2       				((uint32_t)0x00000004)  //!< External interrupt line 2  
#define EXTI_LINE_3       				((uint32_t)0x00000008)  //!< External interrupt line 3  
#define EXTI_LINE_4       				((uint32_t)0x00000010)  //!< External interrupt line 4 
#define EXTI_LINE_5       				((uint32_t)0x00000020)  //!< External interrupt line 5  
#define EXTI_LINE_6       				((uint32_t)0x00000040)  //!< External interrupt line 6 
#define EXTI_LINE_7       				((uint32_t)0x00000080)  //!< External interrupt line 7  
#define EXTI_LINE_8       				((uint32_t)0x00000100)  //!< External interrupt line 8  
#define EXTI_LINE_9       				((uint32_t)0x00000200)  //!< External interrupt line 9  
#define EXTI_LINE_10      				((uint32_t)0x00000400)  //!< External interrupt line 10
#define EXTI_LINE_11      				((uint32_t)0x00000800)  //!< External interrupt line 11 
#define EXTI_LINE_12      				((uint32_t)0x00001000)  //!< External interrupt line 12 
#define EXTI_LINE_13      				((uint32_t)0x00002000)  //!< External interrupt line 13 
#define EXTI_LINE_14      				((uint32_t)0x00004000)  //!< External interrupt line 14 
#define EXTI_LINE_15      				((uint32_t)0x00008000)  //!< External interrupt line 15
#define EXTI_LINE_16      				((uint32_t)0x00010000)  //!< External interrupt line 16, connected to the LVD                                               
#define EXTI_LINE_17      				((uint32_t)0x00020000)  //!< Internal interrupt line 17, connected to the RTC Alarm event                                                                                                             
#define EXTI_LINE_19      				((uint32_t)0x00080000)  //!< Internal interrupt line 19, connected to the RTC Tamper event                                      
#define EXTI_LINE_23     				((uint32_t)0x00800000)  //!< Internal interrupt line 23, connected to the I2C1 wakeup event                                                    
#define EXTI_LINE_25      				((uint32_t)0x02000000)  //!< Internal interrupt line 25, connected to the USART1 wakeup event
                                                     
/** 
  * @brief EXTI edge definition  
  */
#define EXTI_EDGE_RISING				((uint8_t)0x08)			//!< External interrupt trigger (rising signal)
#define EXTI_EDGE_FALLING				((uint8_t)0x0C)		   	//!< External interrupt trigger (falling signal)


/**
  * @}
  */

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @return None
  */
#define __EXTI_DEF_INIT()				exti_def_init()

/**
  * @brief  Enables the interrupt of specified EXTI lines.
  * @param  LINE: specifies the EXTI lines to enable.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define	__EXTI_INTR_ENABLE(LINE)		(EXTI->INTEN |= LINE)

/**
  * @brief  Enables the interrupt of specified EXTI lines.
  * @param  LINE: specifies the EXTI lines to disbale.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define	__EXTI_INTR_DISABLE(LINE)		(EXTI->INTEN &= ~(LINE))

/**
  * @brief  Enables the event of specified EXTI lines.
  * @param  LINE: specifies the EXTI lines to enable.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define	__EXTI_EVENT_ENABLE(LINE)		(EXTI->EVTEN |= LINE)

/**
  * @brief  Enables the event of specified EXTI lines.
  * @param  LINE: specifies the EXTI lines to disbale.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define	__EXTI_EVENT_DISABLE(LINE)		(EXTI->EVTEN &= ~(LINE))

/**
  * @brief  Enables the edge detected of specified EXTI lines.
  * @param  EDGE: specifies the edge to enable.
  *			It can be one of the following values:
  *			 @arg EXTI_EDGE_RISING: Rising edge
  *			 @arg EXTI_EDGE_FALLING: Falling edge  
  * @param  LINE: specifies the EXTI lines to enable.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define	__EXTI_EDGE_ENABLE(EDGE, LINE)	(*(__IO uint32_t *)((uint32_t)EXTI_BASE + EDGE) |= LINE)

/**
  * @brief  Enables the interrupt of specified EXTI lines.
  * @param  EDGE: specifies the edge to enable.
  *			It can be one of the following values:
  *			 @arg EXTI_EDGE_RISING: Rising edge
  *			 @arg EXTI_EDGE_FALLING: Falling edge    
  * @param  LINE: specifies the EXTI lines to disbale.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define	__EXTI_EDGE_DISABLE(EDGE, LINE)	(*(__IO uint32_t *)((uint32_t)EXTI_BASE + EDGE) &= ~(LINE))

/**
  * @brief  Generates a Software interrupt on selected EXTI lines.
  * @param  LINE: specifies the EXTI line on which the software interrupt will be generated.
  *         It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define __EXTI_SW_INTR_TRIGGER(LINE)	(EXTI->SWTIEN |= LINE)

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  FLAG: specifies the EXTI line pending interrupt flag to check.
  *			It can be one of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return SET or RESET
  */
#define __EXTI_FLAG_STATUS_GET(FLAG)	((EXTI->PDF & (FLAG)) ? SET : RESET)

/**
  * @brief  Clears the EXTI's line flags.
  * @param  FLAG: specifies the EXTI lines flags to clear.
  *			It can be any combination of EXTI_LINE_x where x can be (0~17,19,23,25).
  * @return None
  */
#define __EXTI_FLAG_CLEAR(FLAG)			(EXTI->PDF = FLAG)

/**
  * @fn void exti_def_init(void)
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @return None
  */
void exti_def_init(void);


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

