/**
  * @file    cs32f0xx_rcu.h
  * @brief   This file contains all the functions prototypes for the RCU 
  *          firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_RCU_H__
#define __CS32F0XX_RCU_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup RCU
  * @{
  */
  
/** @defgroup RCU_Exported_Constants
  * @{
  */
  

/** 
  * @struct rcu_clock_t
  * @brief  RCU clock structures definition  
  */ 
typedef struct
{
    uint32_t system_clk_freq;   //!< System clock frequency
    uint32_t hclk_freq;         //!< HCLK frequency
    uint32_t pclk_freq;         //!< PCLK frequency
    uint32_t i2c1_clk_freq;     //!< I2C1 clock frequency
    uint32_t usart1_clk_freq;   //!< Usart1 clock frequency
}rcu_clock_t;
                                    
/** 
  * @brief RCU AHB peripherals enable definition
  */
#define RCU_AHB_PERI_GPIOA                  RCU_AHBEN_PAEN          //!< RCU GPIOA clock enable 
#define RCU_AHB_PERI_GPIOB                  RCU_AHBEN_PBEN          //!< RCU GPIOB clock enable 
#define RCU_AHB_PERI_GPIOC                  RCU_AHBEN_PCEN          //!< RCU GPIOC clock enable 
#define RCU_AHB_PERI_GPIOF                  RCU_AHBEN_PFEN          //!< RCU GPIOF clock enable 
#define RCU_AHB_PERI_CRC                    RCU_AHBEN_CRCEN         //!< RCU CRC clock enable 
#define RCU_AHB_PERI_FMC                    RCU_AHBEN_FMCEN         //!< RCU FMC clock enable 
#define RCU_AHB_PERI_SRAM                   RCU_AHBEN_RMCEN         //!< RCU SRAM clock enable 
#define RCU_AHB_PERI_DMA                    RCU_AHBEN_DMAEN         //!< RCU DMA clock enable  

/** 
  * @brief RCU APB1 peripherals enable definition
  */
#define RCU_APB1_PERI_TIM2                  RCU_APB1EN_TIM2EN       //!< RCU APB1 peripheral TIM2 clock enable, only available for CS32F031 devices, excluded CS32F031-RA version.
#define RCU_APB1_PERI_TIM3                  RCU_APB1EN_TIM3EN       //!< RCU APB1 peripheral TIM3 clock enable
#define RCU_APB1_PERI_TIM6                  RCU_APB1EN_TIM6EN       //!< RCU APB1 peripheral TIM6 clock enable, not available for CS32F036 devices.
#define RCU_APB1_PERI_TIM14                 RCU_APB1EN_TIM14EN      //!< RCU APB1 peripheral TIM14 clock enable
#define RCU_APB1_PERI_WWDT                  RCU_APB1EN_WWDTEN       //!< RCU APB1 peripheral WWDT clock enable
#define RCU_APB1_PERI_SPI2                  RCU_APB1EN_SPI2EN       //!< RCU APB1 peripheral SPI2 clock enable
#define RCU_APB1_PERI_USART2                RCU_APB1EN_USART2EN     //!< RCU APB1 peripheral USART2 clock enable
#define RCU_APB1_PERI_I2C1                  RCU_APB1EN_I2C1EN       //!< RCU APB1 peripheral I2C1 clock enable
#define RCU_APB1_PERI_I2C2                  RCU_APB1EN_I2C2EN       //!< RCU APB1 peripheral I2C2 clock enable
#define RCU_APB1_PERI_PMU                   RCU_APB1EN_PMUEN        //!< RCU APB1 peripheral PMU clock enable 

/** 
  * @brief RCU APB2 peripherals enable definition
  */
#define RCU_APB2_PERI_SYSCFG                RCU_APB2EN_SYSCFGEN     //!< RCU APB2 peripheral system clock enable
#define RCU_APB2_PERI_USART6                RCU_APB2EN_USART6EN     //!< RCU APB2 peripheral USART6 clock enable
#define RCU_APB2_PERI_USART7                RCU_APB2EN_USART7EN     //!< RCU APB2 peripheral USART7 clock enable
#define RCU_APB2_PERI_USART8                RCU_APB2EN_USART8EN     //!< RCU APB2 peripheral USART8 clock enable
#define RCU_APB2_PERI_ADC                   RCU_APB2EN_ADCEN        //!< RCU APB2 peripheral ADC clock enable
#define RCU_APB2_PERI_TIM1                  RCU_APB2EN_TIM1EN       //!< RCU APB2 peripheral TIM1 clock enable
#define RCU_APB2_PERI_SPI1                  RCU_APB2EN_SPI1EN       //!< RCU APB2 peripheral SPI1 clock enable
#define RCU_APB2_PERI_USART1                RCU_APB2EN_USART1EN     //!< RCU APB2 peripheral USART1 clock enable
#define RCU_APB2_PERI_TIM15                 RCU_APB2EN_TIM15EN      //!< RCU APB2 peripheral TIM15 clock enable, not available for CS32F036 devices.
#define RCU_APB2_PERI_TIM16                 RCU_APB2EN_TIM16EN      //!< RCU APB2 peripheral TIM16 clock enable
#define RCU_APB2_PERI_TIM17                 RCU_APB2EN_TIM17EN      //!< RCU APB2 peripheral TIM17 clock enable
#define RCU_APB2_PERI_DBG                   RCU_APB2EN_DBGEN        //!< RCU APB2 peripheral DBG clock enable 

/**
  * @brief RCU peripheral reset register definition
  */
#define RCU_PERI_RST_REG_GPIOA              RCU->AHBRST             //!< GPIOA reset
#define RCU_PERI_RST_REG_GPIOB              RCU->AHBRST             //!< GPIOB reset
#define RCU_PERI_RST_REG_GPIOC              RCU->AHBRST             //!< GPIOC reset
#define RCU_PERI_RST_REG_GPIOF              RCU->AHBRST             //!< GPIOF reset
                                                                    
#define RCU_PERI_RST_REG_TIM2               RCU->APB1RST            //!< Timer 2 reset, only available for CS32F031 devices, excluded RA version.
#define RCU_PERI_RST_REG_TIM3               RCU->APB1RST            //!< Timer 3 reset
#define RCU_PERI_RST_REG_TIM6               RCU->APB1RST            //!< Timer 6 reset, not available for CS32F036 devices.
#define RCU_PERI_RST_REG_TIM14              RCU->APB1RST            //!< Timer 14 reset
#define RCU_PERI_RST_REG_WWDT               RCU->APB1RST            //!< Window watchdog
#define RCU_PERI_RST_REG_SPI2               RCU->APB1RST            //!< SPI2 reset
#define RCU_PERI_RST_REG_USART2             RCU->APB1RST            //!< USART 2 reset
#define RCU_PERI_RST_REG_I2C1               RCU->APB1RST            //!< I2C 1 reset
#define RCU_PERI_RST_REG_I2C2               RCU->APB1RST            //!< I2C 2 reset
#define RCU_PERI_RST_REG_PMU                RCU->APB1RST            //!< PMU reset
                                                                    
#define RCU_PERI_RST_REG_SYSCFG             RCU->APB2RST            //!< SYSCFG reset
#define RCU_PERI_RST_REG_USART6             RCU->APB2RST            //!< ADC reset
#define RCU_PERI_RST_REG_USART7             RCU->APB2RST            //!< USART8 reset
#define RCU_PERI_RST_REG_USART8             RCU->APB2RST            //!< USART7 reset
#define RCU_PERI_RST_REG_ADC                RCU->APB2RST            //!< USART6 reset
#define RCU_PERI_RST_REG_TIM1               RCU->APB2RST            //!< TIM1 reset
#define RCU_PERI_RST_REG_SPI1               RCU->APB2RST            //!< SPI1 reset
#define RCU_PERI_RST_REG_USART1             RCU->APB2RST            //!< USART1 reset
#define RCU_PERI_RST_REG_TIM15              RCU->APB2RST            //!< TIM15 reset, not available for CS32F036 devices.
#define RCU_PERI_RST_REG_TIM16              RCU->APB2RST            //!< TIM16 reset
#define RCU_PERI_RST_REG_TIM17              RCU->APB2RST            //!< TIM17 reset
#define RCU_PERI_RST_REG_DBG                RCU->APB2RST            //!< DBGMCU reset

/**
  * @brief RCU peripheral reset bit definition
  */
#define RCU_PERI_RST_BIT_GPIOA              RCU_AHBRST_PARST        //!< GPIOA reset
#define RCU_PERI_RST_BIT_GPIOB              RCU_AHBRST_PBRST        //!< GPIOB reset
#define RCU_PERI_RST_BIT_GPIOC              RCU_AHBRST_PCRST        //!< GPIOC reset
#define RCU_PERI_RST_BIT_GPIOF              RCU_AHBRST_PFRST        //!< GPIOF reset
                            
#define RCU_PERI_RST_BIT_TIM2               RCU_APB1RST_TIM2RST     //!< Timer 2 reset, only available for CS32F031 devices, excluded RA version.
#define RCU_PERI_RST_BIT_TIM3               RCU_APB1RST_TIM3RST     //!< Timer 3 reset
#define RCU_PERI_RST_BIT_TIM6               RCU_APB1RST_TIM6RST     //!< Timer 6 reset, not available for CS32F036 devices.
#define RCU_PERI_RST_BIT_TIM14              RCU_APB1RST_TIM14RST    //!< Timer 14 reset
#define RCU_PERI_RST_BIT_WWDT               RCU_APB1RST_WWDTRST     //!< Window Watchdog reset
#define RCU_PERI_RST_BIT_SPI2               RCU_APB1RST_SPI2RST     //!< SPI2 reset
#define RCU_PERI_RST_BIT_USART2             RCU_APB1RST_USART2RST   //!< USART 2 reset
#define RCU_PERI_RST_BIT_I2C1               RCU_APB1RST_I2C1RST     //!< I2C 1 reset
#define RCU_PERI_RST_BIT_I2C2               RCU_APB1RST_I2C2RST     //!< I2C 2 reset
#define RCU_PERI_RST_BIT_PMU                RCU_APB1RST_PMURST      //!< PMU reset
        
#define RCU_PERI_RST_BIT_SYSCFG             RCU_APB2RST_SYSCFGRST   //!< SYSCFG reset
#define RCU_PERI_RST_BIT_ADC                RCU_APB2RST_ADCRST      //!< ADC reset
#define RCU_PERI_RST_BIT_USART8             RCU_APB2RST_USART8RST   //!< USART8 reset
#define RCU_PERI_RST_BIT_USART7             RCU_APB2RST_USART7RST   //!< USART7 reset
#define RCU_PERI_RST_BIT_USART6             RCU_APB2RST_USART6RST   //!< USART6 reset
#define RCU_PERI_RST_BIT_TIM1               RCU_APB2RST_TIM1RST     //!< TIM1 reset
#define RCU_PERI_RST_BIT_SPI1               RCU_APB2RST_SPI1RST     //!< SPI1 reset
#define RCU_PERI_RST_BIT_USART1             RCU_APB2RST_USART1RST   //!< USART1 reset
#define RCU_PERI_RST_BIT_TIM15              RCU_APB2RST_TIM15RST    //!< TIM15 reset, not available for CS32F036 devices.
#define RCU_PERI_RST_BIT_TIM16              RCU_APB2RST_TIM16RST    //!< TIM16 reset
#define RCU_PERI_RST_BIT_TIM17              RCU_APB2RST_TIM17RST    //!< TIM17 reset
#define RCU_PERI_RST_BIT_DBG                RCU_APB2RST_DBGRST      //!< DBGMCU reset

/** 
  * @brief PLL clock definition  
  */
#define RCU_PLL_CFG_HRC_DIV2                ((uint32_t)0x00000000)  //!< RCU PLL clock source selection is HRC
#define RCU_PLL_CFG_HXT_DIV1                ((uint32_t)0x00010000)  //!< RCU PLL clock source selection is HXT/1
#define RCU_PLL_CFG_HXT_DIV2                ((uint32_t)0x00010001)  //!< RCU PLL clock source selection is HXT/2
#define RCU_PLL_CFG_HXT_DIV3                ((uint32_t)0x00010002)  //!< RCU PLL clock source selection is HXT/3
#define RCU_PLL_CFG_HXT_DIV4                ((uint32_t)0x00010003)  //!< RCU PLL clock source selection is HXT/4
#define RCU_PLL_CFG_HXT_DIV5                ((uint32_t)0x00010004)  //!< RCU PLL clock source selection is HXT/5
#define RCU_PLL_CFG_HXT_DIV6                ((uint32_t)0x00010005)  //!< RCU PLL clock source selection is HXT/6
#define RCU_PLL_CFG_HXT_DIV7                ((uint32_t)0x00010006)  //!< RCU PLL clock source selection is HXT/7
#define RCU_PLL_CFG_HXT_DIV8                ((uint32_t)0x00010007)  //!< RCU PLL clock source selection is HXT/8
#define RCU_PLL_CFG_HXT_DIV9                ((uint32_t)0x00010008)  //!< RCU PLL clock source selection is HXT/9
#define RCU_PLL_CFG_HXT_DIV10               ((uint32_t)0x00010009)  //!< RCU PLL clock source selection is HXT/10
#define RCU_PLL_CFG_HXT_DIV11               ((uint32_t)0x0001000A)  //!< RCU PLL clock source selection is HXT/11
#define RCU_PLL_CFG_HXT_DIV12               ((uint32_t)0x0001000B)  //!< RCU PLL clock source selection is HXT/12
#define RCU_PLL_CFG_HXT_DIV13               ((uint32_t)0x0001000C)  //!< RCU PLL clock source selection is HXT/13
#define RCU_PLL_CFG_HXT_DIV14               ((uint32_t)0x0001000D)  //!< RCU PLL clock source selection is HXT/14
#define RCU_PLL_CFG_HXT_DIV15               ((uint32_t)0x0001000E)  //!< RCU PLL clock source selection is HXT/15
#define RCU_PLL_CFG_HXT_DIV16               ((uint32_t)0x0001000F)  //!< RCU PLL clock source selection is HXT/16

#define RCU_PLL_CFG_CHECK(clk)              (((clk) == RCU_PLL_CFG_HXT_DIV1)  || ((clk) == RCU_PLL_CFG_HXT_DIV2)  || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV3)  || ((clk) == RCU_PLL_CFG_HXT_DIV4)  || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV5)  || ((clk) == RCU_PLL_CFG_HXT_DIV6)  || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV7)  || ((clk) == RCU_PLL_CFG_HXT_DIV8)  || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV9)  || ((clk) == RCU_PLL_CFG_HXT_DIV10) || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV11) || ((clk) == RCU_PLL_CFG_HXT_DIV12) || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV13) || ((clk) == RCU_PLL_CFG_HXT_DIV14) || \
                                             ((clk) == RCU_PLL_CFG_HXT_DIV15) || ((clk) == RCU_PLL_CFG_HXT_DIV16) || \
                                             ((clk) == RCU_PLL_CFG_HRC_DIV2))

/**
  * @brief RCU PLL multiplication factor definition
  */
#define RCU_PLL_MULTI_2                     ((uint32_t)0x00000000)  //!< RCU PLL clock multiplication factor is 2
#define RCU_PLL_MULTI_3                     ((uint32_t)0x00040000)  //!< RCU PLL clock multiplication factor is 3
#define RCU_PLL_MULTI_4                     ((uint32_t)0x00080000)  //!< RCU PLL clock multiplication factor is 4
#define RCU_PLL_MULTI_5                     ((uint32_t)0x000C0000)  //!< RCU PLL clock multiplication factor is 5
#define RCU_PLL_MULTI_6                     ((uint32_t)0x00100000)  //!< RCU PLL clock multiplication factor is 6
#define RCU_PLL_MULTI_7                     ((uint32_t)0x00140000)  //!< RCU PLL clock multiplication factor is 7
#define RCU_PLL_MULTI_8                     ((uint32_t)0x00180000)  //!< RCU PLL clock multiplication factor is 8
#define RCU_PLL_MULTI_9                     ((uint32_t)0x001C0000)  //!< RCU PLL clock multiplication factor is 9
#define RCU_PLL_MULTI_10                    ((uint32_t)0x00200000)  //!< RCU PLL clock multiplication factor is 10
#define RCU_PLL_MULTI_11                    ((uint32_t)0x00240000)  //!< RCU PLL clock multiplication factor is 11
#define RCU_PLL_MULTI_12                    ((uint32_t)0x00280000)  //!< RCU PLL clock multiplication factor is 12
#define RCU_PLL_MULTI_13                    ((uint32_t)0x002C0000)  //!< RCU PLL clock multiplication factor is 13
#define RCU_PLL_MULTI_14                    ((uint32_t)0x00300000)  //!< RCU PLL clock multiplication factor is 14
#define RCU_PLL_MULTI_15                    ((uint32_t)0x00340000)  //!< RCU PLL clock multiplication factor is 15
#define RCU_PLL_MULTI_16                    ((uint32_t)0x00380000)  //!< RCU PLL clock multiplication factor is 16

#define RCU_PLL_MULTI_CHECK(value)          (((value) == RCU_PLL_MULTI_2)   || ((value) == RCU_PLL_MULTI_3)  || \
                                             ((value) == RCU_PLL_MULTI_4)   || ((value) == RCU_PLL_MULTI_5)  || \
                                             ((value) == RCU_PLL_MULTI_6)   || ((value) == RCU_PLL_MULTI_7)  || \
                                             ((value) == RCU_PLL_MULTI_8)   || ((value) == RCU_PLL_MULTI_9)  || \
                                             ((value) == RCU_PLL_MULTI_10)  || ((value) == RCU_PLL_MULTI_11) || \
                                             ((value) == RCU_PLL_MULTI_12)  || ((value) == RCU_PLL_MULTI_13) || \
                                             ((value) == RCU_PLL_MULTI_14)  || ((value) == RCU_PLL_MULTI_15) || \
                                             ((value) == RCU_PLL_MULTI_16))

/** 
  * @brief RCU HXT drive definition
  */
#define RCU_HXT_DRIVE_LEVEL_0               ((uint32_t)0x00000000)  //!< RCU HXT oscillator high drive capability
#define RCU_HXT_DRIVE_LEVEL_1               RCU_CTR_HXTDRV_0        //!< RCU HXT oscillator medium drive capability
#define RCU_HXT_DRIVE_LEVEL_2               RCU_CTR_HXTDRV_1        //!< RCU HXT oscillator medium low drive capability
#define RCU_HXT_DRIVE_LEVEL_3               RCU_CTR_HXTDRV          //!< RCU HXT oscillator low drive capability       

#define RCU_HXT_DRIVE_CHECK(value)          (((value) == RCU_HXT_DRIVE_LEVEL_0) || ((value) == RCU_HXT_DRIVE_LEVEL_1) || \
                                             ((value) == RCU_HXT_DRIVE_LEVEL_2) || ((value) == RCU_HXT_DRIVE_LEVEL_3))

/** 
  * @brief RCU LXT drive definition
  */
#define RCU_LXT_DRIVE_LEVEL_0               ((uint32_t)0x00000000)  //!< RCU LXT oscillator low drive capability
#define RCU_LXT_DRIVE_LEVEL_1               ((uint32_t)0x00000008)  //!< RCU LXT oscillator medium low drive capability
#define RCU_LXT_DRIVE_LEVEL_2               ((uint32_t)0x00000010)  //!< RCU LXT oscillator medium drive capability
#define RCU_LXT_DRIVE_LEVEL_3               ((uint32_t)0x00000018)  //!< RCU LXT oscillator medium high drive capability
#define RCU_LXT_DRIVE_LEVEL_4               ((uint32_t)0x00000030)  //!< RCU LXT oscillator sub-high drive capability
#define RCU_LXT_DRIVE_LEVEL_5               ((uint32_t)0x00000038)  //!< RCU LXT oscillator high drive capability

#define RCU_LXT_DRIVE_CHECK(value)          (((value) == RCU_LXT_DRIVE_LEVEL_0) || ((value) == RCU_LXT_DRIVE_LEVEL_1) || \
                                             ((value) == RCU_LXT_DRIVE_LEVEL_2) || ((value) == RCU_LXT_DRIVE_LEVEL_3) || \
                                             ((value) == RCU_LXT_DRIVE_LEVEL_4) || ((value) == RCU_LXT_DRIVE_LEVEL_5))
                                    
/** 
  * @brief RCU RTC clock definition
  */
#define RCU_RTCCLK_SEL_LXT                  ((uint32_t)0x00000100)  //!< RCU LXT oscillator clock used as RTC clock
#define RCU_RTCCLK_SEL_LRC                  ((uint32_t)0x00000200)  //!< RCU LRT oscillator clock used as RTC clock
#define RCU_RTCCLK_SEL_HXT_DIV32            ((uint32_t)0x00000300)  //!< RCU HXT oscillator clock used as RTC clock

#define RCU_RTCCLK_SEL_CHECK(value)         (((value) == RCU_RTCCLK_SEL_LXT) || ((value) == RCU_RTCCLK_SEL_LRC) || \
                                             ((value) == RCU_RTCCLK_SEL_HXT_DIV32)) 
 
/** 
  * @brief RCU CLKOUT select definition
  */
#define RCU_CLKOUT_SEL_NO_CLK               ((uint8_t)0x00)         //!< RCU CLKOUT select no clock source
#define RCU_CLKOUT_SEL_HRC14                ((uint8_t)0x01)         //!< RCU CLKOUT select HRC14 as clock source
#define RCU_CLKOUT_SEL_LRC                  ((uint8_t)0x02)         //!< RCU CLKOUT select LRC as clock source
#define RCU_CLKOUT_SEL_LXT                  ((uint8_t)0x03)         //!< RCU CLKOUT select LXT as clock source
#define RCU_CLKOUT_SEL_SYSCLK               ((uint8_t)0x04)         //!< RCU CLKOUT select SYSCLK as clock source
#define RCU_CLKOUT_SEL_HRC                  ((uint8_t)0x05)         //!< RCU CLKOUT select HRC as clock source
#define RCU_CLKOUT_SEL_HXT                  ((uint8_t)0x06)         //!< RCU CLKOUT select HXT as clock source
#define RCU_CLKOUT_SEL_PLL_DIV2             ((uint8_t)0x07)         //!< RCU CLKOUT select PLL divided by 2 as clock source
#define RCU_CLKOUT_SEL_PLL                  ((uint8_t)0x87)         //!< RCU CLKOUT select PLL as clock source
                                               
#define RCU_CLKOUT_SEL_CHECK(value)         (((value) == RCU_CLKOUT_SEL_NO_CLK) || ((value) == RCU_CLKOUT_SEL_HRC14) || \
                                             ((value) == RCU_CLKOUT_SEL_LRC)    || ((value) == RCU_CLKOUT_SEL_LXT)   || \
                                             ((value) == RCU_CLKOUT_SEL_SYSCLK) || ((value) == RCU_CLKOUT_SEL_HRC)   || \
                                             ((value) == RCU_CLKOUT_SEL_HXT)    || ((value) == RCU_CLKOUT_SEL_PLL)   || \
                                             ((value) == RCU_CLKOUT_SEL_PLL_DIV2))                            
                                                
/** 
  * @brief RCU CLKOUT prescaler definition
  */                                                
#define RCU_CLKOUT_PDIV_1                   ((uint32_t)0x00000000)  //!< RCU CLKOUT is divided by 1
#define RCU_CLKOUT_PDIV_2                   ((uint32_t)0x10000000)  //!< RCU CLKOUT is divided by 2
#define RCU_CLKOUT_PDIV_4                   ((uint32_t)0x20000000)  //!< RCU CLKOUT is divided by 4
#define RCU_CLKOUT_PDIV_8                   ((uint32_t)0x30000000)  //!< RCU CLKOUT is divided by 8
#define RCU_CLKOUT_PDIV_16                  ((uint32_t)0x40000000)  //!< RCU CLKOUT is divided by 16
#define RCU_CLKOUT_PDIV_32                  ((uint32_t)0x50000000)  //!< RCU CLKOUT is divided by 32
#define RCU_CLKOUT_PDIV_64                  ((uint32_t)0x60000000)  //!< RCU CLKOUT is divided by 64
#define RCU_CLKOUT_PDIV_128                 ((uint32_t)0x70000000)  //!< RCU CLKOUT is divided by 128

#define RCU_CLKOUT_PDIV_CHECK(value)        (((value) == RCU_CLKOUT_PDIV_1)  ||((value) == RCU_CLKOUT_PDIV_2)      || \
                                             ((value) == RCU_CLKOUT_PDIV_4)  || ((value) == RCU_CLKOUT_PDIV_8)     || \
                                             ((value) == RCU_CLKOUT_PDIV_16) || ((value) == RCU_CLKOUT_PDIV_32)    || \
                                             ((value) == RCU_CLKOUT_PDIV_64) ||  ((value) == RCU_CLKOUT_PDIV_128)) 

/** 
  * @brief RCU SYSCLK source select definition
  */
#define RCU_SYSCLK_SEL_HRC                  ((uint32_t)0x00000000)  //!< RCU config system clock sources is HRC
#define RCU_SYSCLK_SEL_HXT                  RCU_CFG_SYSSW_0         //!< RCU config system clock sources is HXT
#define RCU_SYSCLK_SEL_PLL                  RCU_CFG_SYSSW_1         //!< RCU config system clock sources is PLL 

#define RCU_SYSCLK_SEL_CHECK(value)         (((value) == RCU_SYSCLK_SEL_HRC)   || ((value) == RCU_SYSCLK_SEL_HXT) || \
                                             ((value) == RCU_SYSCLK_SEL_PLL)) 

/** 
  * @brief RCU SYSCLK source definition
  */
#define RCU_SYSCLK_SRC_HRC                  ((uint32_t)0x00000000)  //!< RCU config system clock sources is HRC
#define RCU_SYSCLK_SRC_HXT                  RCU_CFG_SYSSS_0         //!< RCU config system clock sources is HXT
#define RCU_SYSCLK_SRC_PLL                  RCU_CFG_SYSSS_1         //!< RCU config system clock sources is PLL
                                              

/** 
  * @brief RCU HCLK source definition
  */
#define RCU_HCLK_CFG_SYSCLK_DIV1            ((uint32_t)0x00000000)  //!< SYSCLK not divided 
#define RCU_HCLK_CFG_SYSCLK_DIV2            ((uint32_t)0x00000080)  //!< SYSCLK divided by 2
#define RCU_HCLK_CFG_SYSCLK_DIV4            ((uint32_t)0x00000090)  //!< SYSCLK divided by 4
#define RCU_HCLK_CFG_SYSCLK_DIV8            ((uint32_t)0x000000A0)  //!< SYSCLK divided by 8
#define RCU_HCLK_CFG_SYSCLK_DIV16           ((uint32_t)0x000000B0)  //!< SYSCLK divided by 16
#define RCU_HCLK_CFG_SYSCLK_DIV64           ((uint32_t)0x000000C0)  //!< SYSCLK divided by 64
#define RCU_HCLK_CFG_SYSCLK_DIV128          ((uint32_t)0x000000D0)  //!< SYSCLK divided by 128
#define RCU_HCLK_CFG_SYSCLK_DIV256          ((uint32_t)0x000000E0)  //!< SYSCLK divided by 256
#define RCU_HCLK_CFG_SYSCLK_DIV512          ((uint32_t)0x000000F0)  //!< SYSCLK divided by 512

#define RCU_HCLK_CFG_CHECK(value)           (((value) == RCU_HCLK_CFG_SYSCLK_DIV1)   || ((value) == RCU_HCLK_CFG_SYSCLK_DIV2)   || \
                                             ((value) == RCU_HCLK_CFG_SYSCLK_DIV4)   || ((value) == RCU_HCLK_CFG_SYSCLK_DIV8)   || \
                                             ((value) == RCU_HCLK_CFG_SYSCLK_DIV16)  || ((value) == RCU_HCLK_CFG_SYSCLK_DIV64)  || \
                                             ((value) == RCU_HCLK_CFG_SYSCLK_DIV128) || ((value) == RCU_HCLK_CFG_SYSCLK_DIV256) || \
                                             ((value) == RCU_HCLK_CFG_SYSCLK_DIV512))

/** 
  * @brief RCU PCLK source definition
  */
#define RCU_PCLK_CFG_HCLK_DIV1              ((uint32_t)0x00000000)  //!< HCLK not divied 
#define RCU_PCLK_CFG_HCLK_DIV2              ((uint32_t)0x00000400)  //!< HCLK divided by 2
#define RCU_PCLK_CFG_HCLK_DIV4              ((uint32_t)0x00000500)  //!< HCLK divided by 4
#define RCU_PCLK_CFG_HCLK_DIV8              ((uint32_t)0x00000600)  //!< HCLK divided by 8
#define RCU_PCLK_CFG_HCLK_DIV16             ((uint32_t)0x00000700)  //!< HCLK divided by 16

#define RCU_PCLK_CFG_CHECK(pclk)            (((pclk) == RCU_PCLK_CFG_HCLK_DIV1) || ((pclk) == RCU_PCLK_CFG_HCLK_DIV2) || \
                                             ((pclk) == RCU_PCLK_CFG_HCLK_DIV4) || ((pclk) == RCU_PCLK_CFG_HCLK_DIV8) || \
                                             ((pclk) == RCU_PCLK_CFG_HCLK_DIV16))
                                             
/** 
  * @brief RCU USART clock source definition
  */
#define RCU_USART1CLK_CFG_PCLK              ((uint32_t)0x00000000)  //!< RCU USART1 select PCLK as clock source 
#define RCU_USART1CLK_CFG_SYSCLK            ((uint32_t)0x00000001)  //!< RCU USART1 select SYSCLK as clock source
#define RCU_USART1CLK_CFG_LXT               ((uint32_t)0x00000002)  //!< RCU USART1 select LXT as clock source
#define RCU_USART1CLK_CFG_HRC               ((uint32_t)0x00000003)  //!< RCU USART1 select HRC as clock source

#define RCU_USARTxCLK_CFG_CHECK(value)      (((value) == RCU_USART1CLK_CFG_PCLK) || ((value) == RCU_USART1CLK_CFG_SYSCLK) || \
                                             ((value) == RCU_USART1CLK_CFG_LXT)  || ((value) == RCU_USART1CLK_CFG_HRC))

/** 
  * @brief RCU I2C1 clock source definition
  */
#define RCU_I2C1CLK_CFG_HRC                 ((uint32_t)0x00000000)  //!< RCU I2C1 clock source is HRC 
#define RCU_I2C1CLK_CFG_SYSCLK              RCU_CFG3_I2C1SEL        //!< RCU I2C1 clock source is SYSCLK 

#define RCU_I2C1CLK_CFG_CHECK(value)        (((value) == RCU_I2C1CLK_CFG_HRC) || ((value) == RCU_I2C1CLK_CFG_SYSCLK))

#define RCU_HRC_CALI_VALUE_CHECK(value)     ((value) <= 0x1F)

#define RCU_HRC14_CALI_VALUE_CHECK(value)   ((value) <= 0x1F)
 
/**
  * @brief RCU function register definition
  */
#define RCU_ENABLE_REG_PLL_CLK              RCU->CTR                //!< PLL clock
#define RCU_ENABLE_REG_HXT_CLK              RCU->CTR                //!< HXT clock
#define RCU_ENABLE_REG_HXT_BYPASS           RCU->CTR                //!< HXT bypass
#define RCU_ENABLE_REG_HXT_MONITOR          RCU->CTR                //!< HXT monitor
#define RCU_ENABLE_REG_HRC_CLK              RCU->CTR                //!< HRC clock
#define RCU_ENABLE_REG_LXT_CLK              RCU->VBDC               //!< LXT clock
#define RCU_ENABLE_REG_LXT_BYPASS           RCU->VBDC               //!< LXT bypass
#define RCU_ENABLE_REG_RTC_CLK              RCU->VBDC               //!< RTCCLK
#define RCU_ENABLE_REG_LRC_CLK              RCU->STS                //!< LRC CLK          
#define RCU_ENABLE_REG_HRC14_CLK            RCU->CTR2               //!< HRC14 CLK        
#define RCU_ENABLE_REG_ADC_DISABLE_HRC14    RCU->CTR2               //!< Disable ADC request HRC14 opening
#define RCU_ENABLE_REG_VBAT_RESET           RCU->VBDC               //!< VBAT RESET (not available for CS32F03X-RA device)        
#define RCU_ENABLE_REG_RTC_RESET            RCU->VBDC               //!< RTC RESET (only available for CS32F03X-RA device)       

/**
  * @brief RCU function bit definition
  */
#define RCU_ENABLE_BIT_PLL_CLK              RCU_CTR_PLLEN           //!< PLL clock
#define RCU_ENABLE_BIT_HXT_CLK              RCU_CTR_HXTEN           //!< HXT clock
#define RCU_ENABLE_BIT_HXT_BYPASS           RCU_CTR_HXTBPS          //!< HXT bypass
#define RCU_ENABLE_BIT_HXT_MONITOR          RCU_CTR_HXTME           //!< HXT monitor
#define RCU_ENABLE_BIT_HRC_CLK              RCU_CTR_HRCEN           //!< HRC clock
#define RCU_ENABLE_BIT_LXT_CLK              RCU_VBDC_LXTEN          //!< LXT clock
#define RCU_ENABLE_BIT_LXT_BYPASS           RCU_VBDC_LXTBYP         //!< LXT bypass
#define RCU_ENABLE_BIT_RTC_CLK              RCU_VBDC_RTCCLKEN       //!< RTCCLK
#define RCU_ENABLE_BIT_LRC_CLK              RCU_STS_LRCEN           //!< LRC CLK          
#define RCU_ENABLE_BIT_HRC14_CLK            RCU_CTR2_HRC14EN        //!< HRC14 CLK        
#define RCU_ENABLE_BIT_ADC_DISABLE_HRC14    RCU_CTR2_ADCDISHRC14    //!< Disable ADC request HRC14 opening 
#define RCU_ENABLE_BIT_VBAT_RESET           RCU_VBDC_VBTRST         //!< VBAT RESET (not available for CS32F03X-RA device)       
#define RCU_ENABLE_BIT_RTC_RESET            RCU_VBDC_VBTRST         //!< RTC RESET (only available for CS32F03X-RA device)       

/** 
  * @brief RCU interrupt definition
  */
#define RCU_INTR_LRC_STAB                   RCU_INTR_LRCSTABIE      //!< RCU LRC stabilization interrupt
#define RCU_INTR_LXT_STAB                   RCU_INTR_LXTSTABIE      //!< RCU LXT stabilization interrupt
#define RCU_INTR_HRC_STAB                   RCU_INTR_HRCSTABIE      //!< RCU HRC stabilization interrupt
#define RCU_INTR_HXT_STAB                   RCU_INTR_HXTSTABIE      //!< RCU HXT stabilization interrupt
#define RCU_INTR_PLL_STAB                   RCU_INTR_PLLSTABIE      //!< RCU PLL stabilization interrupt
#define RCU_INTR_HRC14_STAB                 RCU_INTR_HRC14STABIE    //!< RCU HRC14 stabilization interrupt

/** 
  * @brief RCU interrupt flag definition
  */
#define RCU_INTR_FLAG_LRC_STAB              RCU_INTR_LRCSTABIF      //!< RCU LRC stabilization interrupt flag
#define RCU_INTR_FLAG_LXT_STAB              RCU_INTR_LXTSTABIF      //!< RCU LXT stabilization interrupt flag 
#define RCU_INTR_FLAG_HRC_STAB              RCU_INTR_HRCSTABIF      //!< RCU HRC stabilization interrupt flag 
#define RCU_INTR_FLAG_HXT_STAB              RCU_INTR_HXTSTABIF      //!< RCU HXT stabilization interrupt flag
#define RCU_INTR_FLAG_PLL_STAB              RCU_INTR_PLLSTABIF      //!< RCU PLL stabilization interrupt flag
#define RCU_INTR_FLAG_HRC14_STAB            RCU_INTR_HRC14STABIF    //!< RCU HRC14 stabilization interrupt flag
#define RCU_INTR_FLAG_HXT_FAIL              RCU_INTR_CKFAILIF       //!< RCU HXT clock fail interrupt flag

/** 
  * @brief RCU interrupt flag clear definition
  */
#define RCU_INTR_FLAG_CLR_LRC_STAB          RCU_INTR_LRCSTABIC      //!< RCU LRC stabilization interrupt flag clear 
#define RCU_INTR_FLAG_CLR_LXT_STAB          RCU_INTR_LXTSTABIC      //!< RCU LXT stabilization interrupt flag clear
#define RCU_INTR_FLAG_CLR_HRC_STAB          RCU_INTR_HRCSTABIC      //!< RCU HRC stabilization interrupt flag clear
#define RCU_INTR_FLAG_CLR_HXT_STAB          RCU_INTR_HXTSTABIC      //!< RCU HXT stabilization interrupt flag clear
#define RCU_INTR_FLAG_CLR_PLL_STAB          RCU_INTR_PLLSTABIC      //!< RCU PLL stabilization interrupt flag clear
#define RCU_INTR_FLAG_CLR_HRC14_STAB        RCU_INTR_HRC14STABIC    //!< RCU HRC14 stabilization interrupt flag clear
#define RCU_INTR_FLAG_CLR_HXT_FAIL          RCU_INTR_CKFAILIC       //!< RCU HXT clock fail interrupt flag clear

/** 
  * @brief RCU flag register definition
  */
#define RCU_FLAG_REG_HRC_STAB               RCU->CTR                //!< RCU HRC stabilization flag 
#define RCU_FLAG_REG_HXT_STAB               RCU->CTR                //!< RCU HXT stabilization flag 
#define RCU_FLAG_REG_PLL_STAB               RCU->CTR                //!< RCU PLL stabilization flag 
#define RCU_FLAG_REG_LXT_STAB               RCU->VBDC               //!< RCU LXT stabilization flag 
#define RCU_FLAG_REG_LRC_STAB               RCU->STS                //!< RCU LRC stabilization flag
#define RCU_FLAG_REG_HRC14_STAB             RCU->CTR2               //!< RCU HRC14 stabilization flag
#define RCU_FLAG_REG_REGERRRST              RCU->STS                //!< RCU register error reset flag
#define RCU_FLAG_REG_V15RST                 RCU->STS                //!< RCU 1.5V domain system reset flag 
#define RCU_FLAG_REG_OBURST                 RCU->STS                //!< RCU option byte update reset flag 
#define RCU_FLAG_REG_NRST                   RCU->STS                //!< RCU nRST pin reset flag 
#define RCU_FLAG_REG_PORRST                 RCU->STS                //!< RCU POR/PDR reset flag 
#define RCU_FLAG_REG_SWRST                  RCU->STS                //!< RCU software reset flag 
#define RCU_FLAG_REG_FWDTRST                RCU->STS                //!< RCU FWDT reset flag 
#define RCU_FLAG_REG_WWDTRST                RCU->STS                //!< RCU WWDT reset flag 
#define RCU_FLAG_REG_LPERST                 RCU->STS                //!< RCU low-power mode enter reset flag 

/** 
  * @brief RCU clock stabilization flag definition
  */
#define RCU_FLAG_BIT_HRC_STAB               RCU_CTR_HRCSTAB         //!< RCU HRC stabilization flag 
#define RCU_FLAG_BIT_HXT_STAB               RCU_CTR_HXTSTAB         //!< RCU HXT stabilization flag 
#define RCU_FLAG_BIT_PLL_STAB               RCU_CTR_PLLSTAB         //!< RCU PLL stabilization flag 
#define RCU_FLAG_BIT_LXT_STAB               RCU_VBDC_LXTSTAB        //!< RCU LXT stabilization flag 
#define RCU_FLAG_BIT_LRC_STAB               RCU_STS_LRCSTAB         //!< RCU LRC stabilization flag
#define RCU_FLAG_BIT_HRC14_STAB             RCU_CTR2_HRC14STAB      //!< RCU HRC14 stabilization flag
#define RCU_FLAG_BIT_REGERRRST              RCU_STS_REGERRRSTF      //!< RCU register error reset flag
#define RCU_FLAG_BIT_V15RST                 RCU_STS_V15RSTF         //!< RCU 1.5V domain system reset flag 
#define RCU_FLAG_BIT_OBURST                 RCU_STS_OBURSTF         //!< RCU option byte update reset flag 
#define RCU_FLAG_BIT_NRST                   RCU_STS_NRSTF           //!< RCU nRST pin reset flag 
#define RCU_FLAG_BIT_PORRST                 RCU_STS_PORRSTF         //!< RCU POR/PDR reset flag 
#define RCU_FLAG_BIT_SWRST                  RCU_STS_SWRSTF          //!< RCU software reset flag 
#define RCU_FLAG_BIT_FWDTRST                RCU_STS_FWDTRSTF        //!< RCU FWDT reset flag 
#define RCU_FLAG_BIT_WWDTRST                RCU_STS_WWDTRSTF        //!< RCU WWDT reset flag 
#define RCU_FLAG_BIT_LPERST                 RCU_STS_LPERSTF         //!< RCU low-power mode enter reset flag 

/**
  * @}
  */ 

/**
  * @brief  Resets the RCU clock configuration to the default reset state.
  * @note   The default reset state including HRC ON and used as system clock source HRC14, HXT and PLL OFF AHB, APB 
  *         prescaler is set to 1, CSS and CLKOUT is off.  All interrupts is disabled, but it doesn't modify the
  *         configuration of the peripheral clocks LRC, LXT and RTC clocks.
  * @param  None.
  * @return None.
  */
#define __RCU_DEF_INIT()                rcu_def_init()

/**
  * @brief  Enables the AHB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and the application 
  *         software has to enable this clock before using it.    
  * @param  PERI: specifies the AHB peripheral to gates its clock. It can be any combination of the following values:
  *         @arg RCU_AHB_PERI_GPIOA (GPIOA clock)
  *         @arg RCU_AHB_PERI_GPIOB (GPIOB clock)
  *         @arg RCU_AHB_PERI_GPIOC (GPIOC clock)
  *         @arg RCU_AHB_PERI_GPIOF (GPIOF clock)
  *         @arg RCU_AHB_PERI_CRC (CRC clock)
  *         @arg RCU_AHB_PERI_FMC (has effect only when the Flash memory is in power down mode)  
  *         @arg RCU_AHB_PERI_SRAM (SRAM clock)
  *         @arg RCU_AHB_PERI_DMA (DMA clock)
  * @return None.
  */
#define __RCU_AHB_CLK_ENABLE(PERI)      (RCU->AHBEN |= PERI)

/**
  * @brief  Disables the AHB peripheral clock.   
  * @param  PERI: specifies the AHB peripheral to gates its clock. It can be any combination of the following values:
  *         @arg RCU_AHB_PERI_GPIOA (GPIOA clock)
  *         @arg RCU_AHB_PERI_GPIOB (GPIOB clock)
  *         @arg RCU_AHB_PERI_GPIOC (GPIOC clock)
  *         @arg RCU_AHB_PERI_GPIOF (GPIOF clock)
  *         @arg RCU_AHB_PERI_CRC (CRC clock)
  *         @arg RCU_AHB_PERI_FMC (has effect only when the Flash memory is in power down mode)  
  *         @arg RCU_AHB_PERI_SRAM (SRAM clock)
  *         @arg RCU_AHB_PERI_DMA (DMA clock)
  * @return None.
  */
#define __RCU_AHB_CLK_DISABLE(PERI)     (RCU->AHBEN &= ~(PERI))
                                                                                                            
/**
  * @brief  Enables the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and the application 
  *         software has to enable this clock before using it.    
  * @param  PERI: specifies the APB1 peripheral to gates its clock. It can be any combination of the following values:
  *         @arg RCU_APB1_PERI_TIM2 (TIM2 clock, only available for CS32F031 devices, excluded CS32F031-RA version.)
  *         @arg RCU_APB1_PERI_TIM3 (TIM3 clock)
  *         @arg RCU_APB1_PERI_TIM6 (TIM6 clock)
  *         @arg RCU_APB1_PERI_TIM14 (TIM14 clock)
  *         @arg RCU_APB1_PERI_WWDT (WWDT clock)
  *         @arg RCU_APB1_PERI_SPI2 (SPI2 clock)
  *         @arg RCU_APB1_PERI_USART2 (USART2 clock)     
  *         @arg RCU_APB1_PERI_I2C1 (I2C1 clock)
  *         @arg RCU_APB1_PERI_I2C2 (I2C2 clock)  
  *         @arg RCU_APB1_PERI_PMU (PMU clock)  
  * @return None.
  */
#define __RCU_APB1_CLK_ENABLE(PERI)     (RCU->APB1EN |= PERI)

/**
  * @brief  Disables the APB1 peripheral clock.   
  * @param  PERI: specifies the APB1 peripheral to gates its clock. It can be any combination of the following values:
  *         @arg RCU_APB1_PERI_TIM2 (TIM2 clock, only available for CS32F031 devices, excluded CS32F031-RA version.)
  *         @arg RCU_APB1_PERI_TIM3 (TIM3 clock)
  *         @arg RCU_APB1_PERI_TIM6 (TIM6 clock)
  *         @arg RCU_APB1_PERI_TIM14 (TIM14 clock)
  *         @arg RCU_APB1_PERI_WWDT (WWDT clock)
  *         @arg RCU_APB1_PERI_SPI2 (SPI2 clock)
  *         @arg RCU_APB1_PERI_USART2 (USART2 clock)     
  *         @arg RCU_APB1_PERI_I2C1 (I2C1 clock)
  *         @arg RCU_APB1_PERI_I2C2 (I2C2 clock)  
  *         @arg RCU_APB1_PERI_PMU (PMU clock) 
  * @return None.
  */
#define __RCU_APB1_CLK_DISABLE(PERI)    (RCU->APB1EN &= ~(PERI))                                        
                                                                                                                          
/**
  * @brief  Enables the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and the application
  *         software has to enable this clock before using it.    
  * @param  PERI: specifies the APB2 peripheral to gates its clock. It can be any combination of the following values:
  *         @arg RCU_APB2_PERI_SYSCFG (SYSCFG clock)
  *         @arg RCU_APB2_PERI_USART6 (USART6 clock)
  *         @arg RCU_APB2_PERI_USART7 (USART7 clock)
  *         @arg RCU_APB2_PERI_USART8 (USART8 clock)
  *         @arg RCU_APB2_PERI_ADC (ADC clock)
  *         @arg RCU_APB2_PERI_TIM1 (TIM1 clock)
  *         @arg RCU_APB2_PERI_SPI1 (SPI1 clock)
  *         @arg RCU_APB2_PERI_USART1 (USART1 clock)  
  *         @arg RCU_APB2_PERI_TIM15 (TIM15 clock)
  *         @arg RCU_APB2_PERI_TIM16 (TIM16 clock)
  *         @arg RCU_APB2_PERI_TIM17 (TIM17 clock)
  *         @arg RCU_APB2_PERI_DBG (DBGMCU clock)
  * @return None.
  */
#define __RCU_APB2_CLK_ENABLE(PERI)     (RCU->APB2EN |= PERI)

/**
  * @brief  Disables the APB2 peripheral clock.  
  * @param  PERI: specifies the APB2 peripheral to gates its clock. It can be any combination of the following values:
  *         @arg RCU_APB2_PERI_SYSCFG (SYSCFG clock)
  *         @arg RCU_APB2_PERI_USART6 (USART6 clock)
  *         @arg RCU_APB2_PERI_USART7 (USART7 clock)
  *         @arg RCU_APB2_PERI_USART8 (USART8 clock)
  *         @arg RCU_APB2_PERI_ADC (ADC clock)
  *         @arg RCU_APB2_PERI_TIM1 (TIM1 clock)
  *         @arg RCU_APB2_PERI_SPI1 (SPI1 clock)
  *         @arg RCU_APB2_PERI_USART1 (USART1 clock)  
  *         @arg RCU_APB2_PERI_TIM15 (TIM15 clock)
  *         @arg RCU_APB2_PERI_TIM16 (TIM16 clock)
  *         @arg RCU_APB2_PERI_TIM17 (TIM17 clock)
  *         @arg RCU_APB2_PERI_DBG (DBGMCU clock)
  * @return None.
  */
#define __RCU_APB2_CLK_DISABLE(PERI)    (RCU->APB2EN &= ~(PERI))  

/**
  * @brief  Enables the specified peripheral reset.   
  * @param  PERI: specifies peripheral. It can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOF, TIM2(only available for CS32F031 devices, excluded CS32F031-RA version.),
  *			TIM3, TIM6, TIM14, WWDT, SPI2, USART2, 
  *         I2C1, I2C2, PMU, SYSCFG, USART6, USART7, 
  *			USART8, ADC, TIM1, SPI1, USART1, TIM15, TIM16, TIM17, DBG.
  * @return None.
  */
#define __RCU_PERI_RST_ENABLE(PERI)     ((RCU_PERI_RST_REG_##PERI) |= (RCU_PERI_RST_BIT_##PERI))

/**
  * @brief  Enables the specified peripheral reset.   
  * @param  PERI: specifies peripheral. It can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOF, TIM2(only available for CS32F031 devices, excluded CS32F031-RA version.), 
  *			TIM3, TIM6, TIM14, WWDT, SPI2, USART2, 
  *         I2C1, I2C2, PMU, SYSCFG, USART6, USART7, 
  *			USART8, ADC, TIM1, SPI1, USART1, TIM15, TIM16, TIM17, DBG.
  * @return None.
  */
#define __RCU_PERI_RST_DISABLE(PERI)    ((RCU_PERI_RST_REG_##PERI) &= ~(RCU_PERI_RST_BIT_##PERI))

/**
  * @brief  Returns the clock source by switched.
  * @param  None.
  * @return The clock source used as system clock. It can be one of the following values:
  *         @arg RCU_SYSCLK_SRC_HRC (HRC used as system clock).
  *         @arg RCU_SYSCLK_SRC_HXT (HXT used as system clock). 
  *         @arg RCU_SYSCLK_SRC_PLL (PLL used as system clock).
  * @return None.
  */                                            
#define __RCU_SYSCLK_SRC_GET()          (RCU->CFG & RCU_CFG_SYSSS)

/**
  * @brief  Enables the specified RCU function.           
  * @param  VALUE: specifies the RCU function, it can be one of the following values:
  *         @arg PLL_CLK (PLL clock)
  *         @arg HXT_CLK (HXT clock)
  *         @arg HXT_BYPASS (HXT bypass)     
  *         @arg HXT_MONITOR (HXT monitor)  
  *         @arg HRC_CLK (HRC clock)  
  *         @arg LXT_CLK (LXT clock)  
  *         @arg LXT_BYPASS (LRC bypass)
  *         @arg RTC_CLK (RTC clock)  
  *         @arg LRC_CLK (LRC clock)  
  *         @arg HRC14_CLK (HRC14 clock)  
  *         @arg ADC_DISABLE_HRC14 (disable ADC request HRC14 opening)  
  *         @arg VBAT_RESET (VBAT reset, not available for CS32F03X-RA device)
  *         @arg RTC_RESET (RTC reset, only available for CS32F03X-RA device)   
  * @return None.
  */
#define __RCU_FUNC_ENABLE(VALUE)        ((RCU_ENABLE_REG_##VALUE) |= (RCU_ENABLE_BIT_##VALUE)) 

/**
  * @brief  Disables the specified RCU function.           
  * @param  VALUE: specifies the RCU function, it can be one of the following values:
  *         @arg PLL_CLK (PLL clock)
  *         @arg HXT_CLK (HXT clock)
  *         @arg HXT_BYPASS (HXT bypass)     
  *         @arg HXT_MONITOR (HXT monitor)  
  *         @arg HRC_CLK (HRC clock)  
  *         @arg LXT_CLK (LXT clock)  
  *         @arg LXT_BYPASS (LRC bypass) 
  *         @arg RTC_CLK (RTC clock)    
  *         @arg LRC_CLK (LRC clock)  
  *         @arg HRC14_CLK (HRC14 clock)  
  *         @arg ADC_DISABLE_HRC14 (disable ADC request HRC14 opening)  
  *         @arg VBAT_RESET (VBAT reset, not available for CS32F03X-RA device)  
  *         @arg RTC_RESET (RTC reset, only available for CS32F03X-RA device)  
  * @return None.
  */
#define __RCU_FUNC_DISABLE(VALUE)       ((RCU_ENABLE_REG_##VALUE) &= ~(RCU_ENABLE_BIT_##VALUE)) 

/**
  * @brief  Enables the specified RCU interrupts.
  * @param  INT: specifies the RCU interrupt sources to be enabled. It can be any combination of the following values:
  *         @arg RCU_INTR_LRC_STAB (LRC stabilization interrupt)
  *         @arg RCU_INTR_LXT_STAB (LXT stabilization interrupt)
  *         @arg RCU_INTR_HRC_STAB (HRC stabilization interrupt)
  *         @arg RCU_INTR_HXT_STAB (HXT stabilization interrupt)
  *         @arg RCU_INTR_PLL_STAB (PLL stabilization interrupt)
  *         @arg RCU_INTR_HRC14_STAB (HRC14 stabilization interrupt)
  * @return None.
  */
#define __RCU_INTR_ENABLE(INT)          (RCU->INTR |= INT)

/**
  * @brief  Diasables the specified RCU interrupts.
  * @param  INT: specifies the RCU interrupt sources to be enabled. It can be any combination of the following values:
  *         @arg RCU_INTR_LRC_STAB (LRC stabilization interrupt)
  *         @arg RCU_INTR_LXT_STAB (LXT stabilization interrupt)
  *         @arg RCU_INTR_HRC_STAB (HRC stabilization interrupt)
  *         @arg RCU_INTR_HXT_STAB (HXT stabilization interrupt)
  *         @arg RCU_INTR_PLL_STAB (PLL stabilization interrupt)
  *         @arg RCU_INTR_HRC14_STAB (HRC14 stabilization interrupt)
  * @return None.
  */
#define __RCU_INTR_DISABLE(INT)         (RCU->INTR &= ~(INT))

/**
  * @brief  Checks whether the specified RCU interrupt has occurred or not.
  * @param  FLAG: specifies the RCU interrupt source to check. It can be one of the following values:
  *         @arg HXT_STAB (HXT oscillator clock interrupt) 
  *         @arg HRC_STAB (HRC oscillator clock interrupt)
  *         @arg PLL_STAB (PLL clock interrupt) 
  *         @arg LXT_STAB (LXT oscillator clock interrupt) 
  *         @arg LRC_STAB (LRC oscillator clock interrupt) 
  *         @arg HRC14_STAB (HRC14 stable interrupt)
  *         @arg HXT_FAIL (HXT Clock fail Interrupt)
  * @return The new state of flag (SET or RESET).
  */
#define __RCU_INTR_STATUS_GET(FLAG)     ((RCU->INTR & (RCU_INTR_FLAG_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the RCU's interrupt pending bits.
  * @param  FLAG: specifies the interrupt pending bit to clear. It can be any combination of the following values:
  *         @arg RCU_INTR_FLAG_CLR_HXT_STAB (HXT oscillator clock interrupt flag)
  *         @arg RCU_INTR_FLAG_CLR_HRC_STAB (HRC oscillator clock interrupt flag)
  *         @arg RCU_INTR_FLAG_CLR_PLL_STAB (PLL clock interrupt flag)
  *         @arg RCU_INTR_FLAG_CLR_LXT_STAB(LXT oscillator clock interrupt flag)  
  *         @arg RCU_INTR_FLAG_CLR_LRC_STAB (LRC oscillator clock interrupt flag)
  *         @arg RCU_INTR_FLAG_CLR_HRC14_STAB (HRC14 stable interrupt flag)
  *         @arg RCU_INTR_FLAG_CLR_HXT_FAIL (HXT clock fail interrupt flag)
  * @return None.
  */
#define __RCU_INTR_FLAG_CLEAR(FLAG)     (RCU->INTR = FLAG)  

/**
  * @brief  Checks whether the specified RCU stabilization flag is set or not.
  * @param  FLAG: specifies the reset flag to check, it can be one of the following values:
  *         @arg OBURST (Option Byte Update reset )
  *         @arg NRST (nRST Pin reset)
  *         @arg V15RST (the 1.5V domain reset)
  *         @arg PORRST (POR/PDR reset)
  *         @arg SWRST (Software reset)
  *         @arg FWDTRST (FWDT reset)
  *         @arg WWDTRST (WWDT reset)
  *         @arg LPERST (Low-power mode enter-reset)
  *         @arg REGERRRST (Register error reset)
  *         @arg HRC_STAB (HRC oscillator clock stabilization)
  *         @arg HXT_STAB (HXT oscillator clock stabilization)
  *         @arg PLL_STAB (PLL clock stabilization)
  *         @arg LXT_STAB (LXT oscillator clock stabilization)
  *         @arg LRC_STAB (LRC oscillator clock stabilization)
  *         @arg HRC14_STAB (HRC14 oscillator clock stabilization)
  * @return The new state of flag (SET or RESET).
  */
#define __RCU_FLAG_STATUS_GET(FLAG)     (((RCU_FLAG_REG_##FLAG) & (RCU_FLAG_BIT_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the RCU flags. The flags are: RCU_FLAG_BIT_OBURSTF, RCU_FLAG_BIT_NRST, RCU_FLAG_BIT_V15RSTF,
  *         RCU_FLAG_BIT_PORRST, RCU_FLAG_BIT_SWRST, RCU_FLAG_BIT_FWDTRST, RCU_FLAG_BIT_WWDTRST, RCU_FLAG_BIT_LPERST.
  * @param  None.
  * @return None.
  */
#define __RCU_FLAG_CLEAR()              (RCU->STS |= RCU_STS_CRSTF)

/**
  * @fn void rcu_def_init(void)
  * @brief  Resets the RCU clock configuration to the default reset state.
  * @note   The default reset state including HRC ON and used as system clock source HRC14, HXT and PLL OFF AHB, APB 
  *         prescaler is set to 1, CSS and CLKOUT is off.  All interrupts is disabled, but it doesn't modify the
  *         configuration of the peripheral clocks LRC, LXT and RTC clocks.
  * @param  None.
  * @return None.
  */ 
void rcu_def_init(void);

/**
  * @fn error_status_t rcu_hxt_stabilization_wait(void)
  * @brief  Waits for HXT stabilization. It waits on HSERDY flag to be set and return SUCCESS. The HXT is stopped by  
  *         hardware when entering STOP and STANDBY modes.
  * @param  None.
  * @return SUCCESS(oscillator is stable) or ERROR(oscillator not yet stable).
  */
error_status_t rcu_hxt_stabilization_wait(void);

/**
  * @fn void rcu_hrc_calibration_adjust(uint8_t value)
  * @brief  Adjusts the internal high speed RC (HRC) calibration value.
  * @param  value: specifies the HRC calibration trimming value (between 0 and 0x1F).
  * @return None.
  */
void rcu_hrc_calibration_adjust(uint8_t value);

/**
  * @fn void rcu_hrc14_calibration_adjust(uint8_t value)
  * @brief  Adjusts the Internal high speed RC14 for ADC (HRC14) calibration value.
  * @param  value: specifies the HRC14 calibration trimming value. This parameter must be a number between 0 and 0x1F.
  * @return None.
  */
void rcu_hrc14_calibration_adjust(uint8_t value);

/**
  * @fn void rcu_hxt_drive_config(uint32_t value)
  * @brief  Configures the external high speed crystal oscillator (LXT) drive capability.
  * @param  value: specifies the new state of the HXT drive capability. It can be one of the following values:
  *         @arg RCU_HXT_DRIVE_LEVEL_0(HXT oscillator low drive capability)
  *         @arg RCU_HXT_DRIVE_LEVEL_1(HXT oscillator medium low drive capability)
  *         @arg RCU_HXT_DRIVE_LEVEL_2(HXT oscillator medium high drive capability)
  *         @arg RCU_HXT_DRIVE_LEVEL_3(HXT oscillator high drive capability)
  * @return None.
  */
void rcu_hxt_drive_config(uint32_t value);

/**
  * @fn void rcu_lxt_drive_config(uint32_t value)
  * @brief  Configures the external low speed crystal oscillator (LXT) drive capability.
  * @param  value: specifies the new state of the LXT drive capability. It can be one of the following values:
  *         @arg RCU_LXT_DRIVE_LEVEL_0 (LXT oscillator low drive capability)
  *         @arg RCU_LXT_DRIVE_LEVEL_1 (LXT oscillator medium low drive capability)
  *         @arg RCU_LXT_DRIVE_LEVEL_2 (LXT oscillator medium high drive capability)
  *         @arg RCU_LXT_DRIVE_LEVEL_3 (LXT oscillator high drive capability)
  * @return None.
  */
void rcu_lxt_drive_config(uint32_t value);

/**
  * @fn void rcu_pll_config(uint32_t sel_value, uint32_t multiple)
  * @brief  Configures the PLL clock source and multiplication factor. It must be used only when the PLL is disabled.
  * @param  sel_value: specifies the PLL selected clock source. It can be one of the following values:
  *         @arg RCU_PLL_CFG_HRC (HRC oscillator clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT (HXT clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV2 (HXT/2 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV3 (HXT/3 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV4 (HXT/4 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV5 (HXT/5 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV6 (HXT/6 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV7 (HXT/7 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV8 (HXT/8 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV9 (HXT/9 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV10 (HXT/10 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV11 (HXT/11 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV12 (HXT/12 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV13 (HXT/13 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV14 (HXT/14 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV15 (HXT/15 clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV16 (HXT/16 clock selected as PLL clock source)
  * @param  multiple: specifies the PLL multiplication factor (between RCU_PLL_MULTI_2 ~ RCU_PLL_MULTI_16)  
  * @return None.
  */
void rcu_pll_config(uint32_t sel_value, uint32_t multiple);

/**
  * @fn void rcu_clkout_config(uint8_t sel_value, uint32_t prescaler)
  * @brief  Selects the clock source to output on CLKOUT pin (PA8). It should be configured in  multi-function mode.
  * @param  sel_value: specifies the clock source to output, it can be one of the following values:
  *         @arg RCU_CLKOUT_SEL_NO_CLK (No clock selected)
  *         @arg RCU_CLKOUT_SEL_HRC14 (HRC14 oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_LRC (LRC oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_LXT (LXT oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_SYSCLK (System clock selected)
  *         @arg RCU_CLKOUT_SEL_HRC (HRC oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_HXT (HXT oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_PLL_DIV2 (PLL clock divided by 2 selected)
  * @param  prescaler: specifies the prescaler on CLKOUT pin, it can be one of the following values:
  *         @arg RCU_CLKOUT_PDIV_1 (CLKOUT clock is divided by 1)
  *         @arg RCU_CLKOUT_PDIV_2 (CLKOUT clock is divided by 2)
  *         @arg RCU_CLKOUT_PDIV_4 (CLKOUT clock is divided by 4)
  *         @arg RCU_CLKOUT_PDIV_8 (CLKOUT clock is divided by 8)
  *         @arg RCU_CLKOUT_PDIV_16 (CLKOUT clock is divided by 16)
  *         @arg RCU_CLKOUT_PDIV_32 (CLKOUT clock is divided by 32)
  *         @arg RCU_CLKOUT_PDIV_64 (CLKOUT clock is divided by 64)
  *         @arg RCU_CLKOUT_PDIV_128 (CLKOUT clock is divided by 128)   
  * @return None.
  */
void rcu_clkout_config(uint8_t sel_value, uint32_t prescaler);

/**
  * @fn void rcu_sysclk_config(uint32_t value)
  * @brief Configures the system clock (SYSCLK).  
  * @param  value: specifies the clock source used as system clock. It can be one of the following values:
  *         @arg RCU_SYSCLK_SEL_HRC (HRC selected as system clock)
  *         @arg RCU_SYSCLK_SEL_HXT (HXT selected as system clock)
  *         @arg RCU_SYSCLK_SEL_PLL (PLL selected as system clock)
  * @return None.
  */
void rcu_sysclk_config(uint32_t value);

/**
  * @fn void rcu_hclk_config(uint32_t value)
  * @brief  Configures the AHB clock (HCLK).
  * @param  value: defines HCLK divider. It is derived from SYSCLK (the system clock). It can be one of the following 
  *         values:
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV1 (HCLK = SYSCLK)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV2 (HCLK = SYSCLK/2)   
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV4 (HCLK = SYSCLK/4)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV8 (HCLK = SYSCLK/8)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV16 (HCLK = SYSCLK/16)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV64 (HCLK = SYSCLK/64)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV128 (HCLK = SYSCLK/128)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV256 (HCLK = SYSCLK/256)
  *         @arg RCU_HCLK_CFG_SYSCLK_DIV512 (HCLK = SYSCLK/512)
  * @return None.
  */
void rcu_hclk_config(uint32_t value);

/**
  * @fn void rcu_pclk_config(uint32_t value)
  * @brief  Configures the APB clock (PCLK).
  * @param  value: defines the APB clock divider which is derived from HCLK (the AHB clock). It can be one of the 
  *         following values:
  *         @arg RCU_PCLK_CFG_HCLK_DIV1 (APB clock = HCLK) 
  *         @arg RCU_PCLK_CFG_HCLK_DIV2 (APB clock = HCLK/2)
  *         @arg RCU_PCLK_CFG_HCLK_DIV4 (APB clock = HCLK/4)
  *         @arg RCU_PCLK_CFG_HCLK_DIV8 (APB clock = HCLK/8)
  *         @arg RCU_PCLK_CFG_HCLK_DIV16 (APB clock = HCLK/16)
  * @return None.
  */
void rcu_pclk_config(uint32_t value);

/**
  * @fn void rcu_i2cclk_config(uint32_t value)
  * @brief  Configures the I2C1 clock (I2C1CLK).
  * @param  value: defines the I2C1 clock source which is derived from the HRC or system clock. It can be one of the 
  *         following values:
  *         @arg RCU_I2C1CLK_CFG_HRC (I2C1 clock = HRC)
  *         @arg RCU_I2C1CLK_CFG_SYSCLK (I2C1 clock = System Clock)
  * @return None.
  */
void rcu_i2cclk_config(uint32_t value);

/**
  * @fn void rcu_usartclk_config(uint32_t value)
  * @brief  Configures the USART1 clock (USART1CLK).
  * @param  value: defines the USART clock source which is derived from the HRC or system clock. It can be one of the
  *         following values:
  *         @arg RCU_USART1CLK_CFG_PCLK (USART1 clock =PCLK)
  *         @arg RCU_USART1CLK_CFG_SYSCLK (USART1 clock = System Clock)
  *         @arg RCU_USART1CLK_CFG_LXT (USART1 clock = LXT Clock)
  *         @arg RCU_USART1CLK_CFG_HRC (USART1 clock = HRC Clock) 
  * @return None.
  */
void rcu_usartclk_config(uint32_t value);

/**
  * @fn void rcu_rtcclk_config(uint32_t value)
  * @brief  Configures the RTC clock (RTCCLK).           
  * @param  value: specifies the RTC clock source, it can be one of the following values:
  *         @arg RCU_RTCCLK_SEL_LXT(LXT selected as RTC clock)
  *         @arg RCU_RTCCLK_SEL_LRC(LRC selected as RTC clock)
  *         @arg RCU_RTCCLK_SEL_HXT_DIV32(HXT divided by 32 selected as RTC clock)                                  
  * @return None.
  */
void rcu_rtcclk_config(uint32_t value);

/**
  * @fn void rcu_clk_freq_get(rcu_clock_t* ptr_clock)
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.             
  * @param  ptr_clock: pointer to a rcu_clock_t structure which will hold the clocks frequencies.  
  * @return None.
  */
void rcu_clk_freq_get(rcu_clock_t* ptr_clock);


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
