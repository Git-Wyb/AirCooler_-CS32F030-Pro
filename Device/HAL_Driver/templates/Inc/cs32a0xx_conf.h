/**
  * @file    cs32a0xx_conf.h 
  * @brief   Library configuration file.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CS32A0XX_CONF_H__
#define __CS32A0XX_CONF_H__

#include "RTE_Components.h"             /* Component selection */

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the HAL driver 
  */
#ifdef RTE_DEVICE_HAL_ADC
#define HAL_ADC_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_CRC
#define HAL_CRC_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_DMA
#define HAL_DMA_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_FLASH
#define HAL_FLASH_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_GPIO
#define HAL_GPIO_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_I2C
#define HAL_I2C_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_PMU
#define HAL_PMU_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_RCU
#define HAL_RCU_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_RTC
#define HAL_RTC_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_SPI
#define HAL_SPI_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_TIM
#define HAL_TIM_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_USART
#define HAL_USART_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_WWDT
#define HAL_WWDT_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_DEBUG
#define HAL_DEBUG_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_EXTI
#define HAL_EXTI_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_SYSCFG
#define HAL_SYSCFG_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_FRAMEWORK
#define HAL_FRAMEWORK_MODULE_ENABLED
#endif
#ifdef RTE_DEVICE_HAL_ADC2
#define HAL_ADC2_MODULE_ENABLED
#endif

/* ########################### System Configuration ######################### */
/**
  * @brief This is the HAL system configuration section
  */     
#define  VDD_VALUE                    3300U  /*!< Value of VDD in mv */           
#define  TICK_INT_PRIORITY            ((uint32_t)(1U<<__NVIC_PRIO_BITS) - 1U) /*!< tick interrupt priority (lowest by default)             */
                                                                              /*  Warning: Must be set to higher priority for HAL_Delay()  */
                                                                              /*  and HAL_GetTick() usage under interrupt context          */
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              1U
#define  INSTRUCTION_CACHE_ENABLE     0U
#define  DATA_CACHE_ENABLE            0U
#define  USE_SPI_CRC                  1U

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/*#define USE_FULL_ASSERT    1*/

/* Includes ------------------------------------------------------------------*/
/**
  * @brief Include module's header file 
  */

#ifdef HAL_RCU_MODULE_ENABLED
    #include "cs32f0xx_rcu.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
    #include "cs32f0xx_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
    #include "cs32f0xx_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
    #include "cs32f0xx_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
    #include "cs32f0xx_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
    #include "cs32f0xx_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
    #include "cs32f0xx_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_FWDT_MODULE_ENABLED
    #include "cs32f0xx_fwdt.h"
#endif /* HAL_FWDT_MODULE_ENABLED */

#ifdef HAL_PMU_MODULE_ENABLED
    #include "cs32f0xx_pmu.h"
#endif /* HAL_PMU_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
    #include "cs32f0xx_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
    #include "cs32f0xx_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
    #include "cs32f0xx_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
    #include "cs32f0xx_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_WWDT_MODULE_ENABLED
    #include "cs32f0xx_wwdt.h"
#endif /* HAL_WWDT_MODULE_ENABLED */

#ifdef HAL_DEBUG_MODULE_ENABLED
    #include "cs32f0xx_debug.h"
#endif /* HAL_DEBUG_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
    #include "cs32f0xx_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_SYSCFG_MODULE_ENABLED
    #include "cs32f0xx_syscfg.h"
#endif /* HAL_SYSCFG_MODULE_ENABLED */

#ifdef HAL_FRAMEWORK_MODULE_ENABLED
    #include "cs32f0xx_misc.h"
#endif /* HAL_FRAMEWORK_MODULE_ENABLED */

#ifdef HAL_ADC2_MODULE_ENABLED
    #include "cs32a0xx_adc2.h"
#endif /* HAL_ADC2_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed. 
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((char *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
    void assert_failed(char* file, uint32_t line);
#else
    #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */    
    
#ifdef __cplusplus
}
#endif

#endif /* __CS32A0XX_CONF_H__ */

