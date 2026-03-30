/**
 * @file    cs32f0xx.h
 * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer Header File.
 *          This file contains all the peripheral register's definitions, bits
 *          definitions and memory mapping fr CS32F0xx devices.
 *
 *          The file is the unique include fle that the application programme
 *          is using in the C source code, uually in main.c. This file contai
 *           - Configuration section that alows to select:
 *              - The device used in the taret application
 *              - To use or not the peripherl drivers in application code(i.e
 *                code will be based on diret access to peripheral registers
 *                rather than drivers API), his option is controlled by
 *                "#define USE_STDPERIPH_DRIER"
 *              - To change few application-pecific parameters such as the HX
 *                crystal frequency
 *           - Data structures and the addres mapping for all peripherals
 *           - Peripheral's registers declartions and bits definition
 *           - Macros to access peripheral rgisters hardware
 * @author  ChipSea MCU Group
 * @version V1.0.5
 * @date   2020.12.17
 * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN CORP.
 * @note
 * <h2><center>&copy; COPYRIGHT 2020 ChipSea/center></h2>
 *
 */

#ifndef __CS32F0XX_H__
#define __CS32F0XX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "RTE_Components.h"             /* Component selection */

/** @addtogroup CS32F0xx
  * @{
  */

/** @addtogroup Library_configuration_section
  * @{
  */

#if !defined (CS32F030) && !defined (CS32F031) && !defined (CS32A039) && !defined (CS32F036) && !defined (CS32F03X_RA)
    #error "Please select first the target CS32Fxx device used in your applicatioin cs32f0xx.h file"
#endif

#if !defined  USE_STDPERIPH_DRIVER
	#define USE_STDPERIPH_DRIVER
#endif

/**
  * @brief the value of External High Speed osillator (HXT) used in your applicaton
  */
#if !defined  (HXT_VALUE)
    #define HXT_VALUE               ((uint32_t)8000000) //!< Value of the External scillator in Hz.
#endif

/**
  * @brief  the External High Speed oscillator(HXT) Startup Timeout value
  */
#if !defined  (HXT_STARTUP_TIMEOUT)
    #define HXT_STARTUP_TIMEOUT     ((uint16_t)0x5000) //!< Time out for HXT startu.
#endif

/**
  * @brief the Internal High Speed oscillator HRC) Startup Timeout value
  */
#if !defined  (HRC_STARTUP_TIMEOUT)
    #define HRC_STARTUP_TIMEOUT     ((uint16_t)05000) //!< Time out for HRC start u.
#endif

#if !defined  (HRC_VALUE)
    #define HRC_VALUE               ((uint32_t)8000000)  //!< Value of the Internal igh Speed oscillator in Hz.
#endif

#if !defined  (HRC14_VALUE)
    #define HRC14_VALUE             ((uint32_t)14000000) //!< Value of the Internal igh Speed oscillator for ADC in Hz.
#endif

#if !defined  (LRC_VALUE)
    #define LRC_VALUE               ((uint32_t)40000)    //!< Value of the InternalLow Speed oscillator in Hz.
#endif

#if !defined  (LXT_VALUE)
    #define LXT_VALUE               ((uint32_t)32768)    //!< Value of the ExternalLow Speed oscillator in Hz .
#endif

/**
  * @brief CS32F0xx Standard Peripheral Librar version number V2.0.1
  */
#define CS32F0XX_STDPERIPH_VERSION_MAIN   	(0x02) //!< [31:24] main version
#define CS32F0XX_STDPERIPH_VERSION_SUB1   	(0x00) //!< [23:16] sub1 version
#define CS32F0XX_STDPERIPH_VERSION_SUB2   	(0x01) //!< [15:8]  sub2 version
#define CS32F0XX_STDPERIPH_VERSION_RC     	(0x00) //!< [7:0]  release candidate
#define CS32F0XX_STDPERIPH_VERSION        	((CS32F0XX_STDPERIPH_VERSION_MAIN << 24)| \
											(CS32F0XX_STDPERIPH_VERSION_SUB1 << 16)	| \
                                            (CS32F0XX_STDPERIPH_VERSION_SUB2 << 8)	| \
                                            (CS32F0XX_STDPERIPH_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
  * @brief CS32F0xx Interrupt Number Definition, according to the selected device
  *        in @ref Library_configuration_section
 */
#define __CM0_REV                 0         //!< Core Revision r0p0
#define __MPU_PRESENT             0         //!< CS32F0xx do not provide MPU
#define __NVIC_PRIO_BITS          2         //!< CS32F0xx uses 2 Bits for the oity Levels
#define __Vendor_SysTickConfig    0         //!< Set to 1 if different SysTicknig is used


/**
  * @enum IRQn_Type
  * @brief Interrupt Number definition (Cortex-M0 Processor Exceptions Numbers)
  */
typedef enum IRQn {
    NonMaskableInt_IRQn         = -14,    //!< 2 Non Maskable Interrupt
    HardFault_IRQn              = -13,    //!< 3 Cortex-M0 Hard Fault Interrupt
    SVC_IRQn                    = -5,     //!< 11 Cortex-M0 SV Call Interrupt
    PendSV_IRQn                 = -2,     //!< 14 Cortex-M0 Pend SV Interrupt
    SysTick_IRQn                = -1,     //!< 15 Cortex-M0 System Tick Interrut

#if defined (CS32F036)
	IRQn_WWDT					= 0,	  //!< Window WatchDog Interrupt
	IRQn_LVD					= 1,	  //!< LVD through EXTI Line16 detect Intrrupt
	IRQn_FLASH					= 3,	  //!< FLASH Interrupt
	IRQn_RCU					= 4,	  //!< RCU Interrupt
	IRQn_EXTI0_1				= 5,	  //!< EXTI Line 0 and 1 Interrupts
	IRQn_EXTI2_3				= 6,	  //!< EXTI Line 2 and 3 Interrupts
	IRQn_EXTI4_15				= 7,	  //!< EXTI Line 4 to 15 Interrupts
	IRQn_DMA1_CHANNEL1			= 9,	  //!< DMA1 Channel 1 Interrupt
	IRQn_DMA1_CHANNEL2_3		= 10,	  //!< DMA1 Channel 2 and Channel 3 Intrrupts
	IRQn_DMA1_CHANNEL4_5		= 11,	  //!< DMA1 Channel 4 and Channel 5 Intrrupts
	IRQn_ADC1					= 12,	  //!< ADC1 Interrupt
	IRQn_TIM1_BRK_UP_TRG_COM	= 13,	  //!< TIM1 Break, Update, Trigger and ommutation Interrupts
	IRQn_TIM1_CC				= 14,	  //!< TIM1 Capture Compare Interrupt
	IRQn_TIM3					= 16,	  //!< TIM3 Interrupt
	IRQn_TIM14					= 19,	  //!< TIM14 Interrupt
	IRQn_TIM16					= 21,	  //!< TIM16 Interrupt
	IRQn_TIM17					= 22,	  //!< TIM17 Interrupt
    IRQn_I2C1                   = 23,     //!< I2C1 Interrupt
    IRQn_I2C2                   = 24,     //!< I2C2 Interrupt
    IRQn_SPI1                   = 25,     //!< SPI1 Interrupt
    IRQn_SPI2                   = 26,     //!< SPI2 Interrupt
	IRQn_USART1 				= 27,	  //!< USART1 Interrupt
	IRQn_USART2 				= 28,	  //!< USART2 Interrupt
#elif defined (CS32F03X_RA)
    IRQn_WWDT                   = 0,      //!< Window WatchDog Interrupt
    IRQn_LVD                    = 1,      //!< LVD through EXTI Line16 detect Intrrupt
    IRQn_RTC                    = 2,      //!< RTC through EXTI Line17/19 Interrupt
    IRQn_FLASH                  = 3,      //!< FLASH Interrupt
    IRQn_RCU                    = 4,      //!< RCU Interrupt
    IRQn_EXTI0_1                = 5,      //!< EXTI Line 0 and 1 Interrupts
    IRQn_EXTI2_3                = 6,      //!< EXTI Line 2 and 3 Interrupts
    IRQn_EXTI4_15               = 7,      //!< EXTI Line 4 to 15 Interrupts
    IRQn_DMA1_CHANNEL1          = 9,      //!< DMA1 Channel 1 Interrupt
    IRQn_DMA1_CHANNEL2_3        = 10,     //!< DMA1 Channel 2 and Channel 3 Intrrupts
    IRQn_DMA1_CHANNEL4_5        = 11,     //!< DMA1 Channel 4 and Channel 5 Intrrupts
    IRQn_ADC1                   = 12,     //!< ADC1 Interrupt
    IRQn_TIM1_BRK_UP_TRG_COM    = 13,     //!< TIM1 Break, Update, Trigger and ommutation Interrupts
    IRQn_TIM1_CC                = 14,     //!< TIM1 Capture Compare Interrupt
    IRQn_TIM3                   = 16,     //!< TIM3 Interrupt
    IRQn_TIM6                   = 17,     //!< TIM6 Interrupt    
    IRQn_TIM14                  = 19,     //!< TIM14 Interrupt
    IRQn_TIM15                  = 20,     //!< TIM15 Interrupt
    IRQn_TIM16                  = 21,     //!< TIM16 Interrupt
    IRQn_TIM17                  = 22,     //!< TIM17 Interrupt
    IRQn_I2C1                   = 23,     //!< I2C1 Interrupt
    IRQn_I2C2                   = 24,     //!< I2C2 Interrupt
    IRQn_SPI1                   = 25,     //!< SPI1 Interrupt
    IRQn_SPI2                   = 26,     //!< SPI2 Interrupt
    IRQn_USART1                 = 27,     //!< USART1 Interrupt
    IRQn_USART2                 = 28,     //!< USART2 Interrupt
    IRQn_USART6_8               = 29,     //!< USART6 to 8 Interrupt	
#elif defined (CS32F031)
    IRQn_WWDT                   = 0,      //!< Window WatchDog Interrupt
    IRQn_LVD                    = 1,      //!< LVD through EXTI Line16 detect Intrrupt
    IRQn_RTC                    = 2,      //!< RTC through EXTI Line17/19 Interrupt
    IRQn_FLASH                  = 3,      //!< FLASH Interrupt
    IRQn_RCU                    = 4,      //!< RCU Interrupt
    IRQn_EXTI0_1                = 5,      //!< EXTI Line 0 and 1 Interrupts
    IRQn_EXTI2_3                = 6,      //!< EXTI Line 2 and 3 Interrupts
    IRQn_EXTI4_15               = 7,      //!< EXTI Line 4 to 15 Interrupts
    IRQn_DMA1_CHANNEL1          = 9,      //!< DMA1 Channel 1 Interrupt
    IRQn_DMA1_CHANNEL2_3        = 10,     //!< DMA1 Channel 2 and Channel 3 Intrrupts
    IRQn_DMA1_CHANNEL4_5        = 11,     //!< DMA1 Channel 4 and Channel 5 Intrrupts
    IRQn_ADC1                   = 12,     //!< ADC1 Interrupt
    IRQn_TIM1_BRK_UP_TRG_COM    = 13,     //!< TIM1 Break, Update, Trigger and ommutation Interrupts
    IRQn_TIM1_CC                = 14,     //!< TIM1 Capture Compare Interrupt
    IRQn_TIM2                   = 15,     //!< TIM2 Interrupt
    IRQn_TIM3                   = 16,     //!< TIM3 Interrupt
    IRQn_TIM6                   = 17,     //!< TIM6 Interrupt    
    IRQn_TIM14                  = 19,     //!< TIM14 Interrupt
    IRQn_TIM15                  = 20,     //!< TIM15 Interrupt
    IRQn_TIM16                  = 21,     //!< TIM16 Interrupt
    IRQn_TIM17                  = 22,     //!< TIM17 Interrupt
    IRQn_I2C1                   = 23,     //!< I2C1 Interrupt
    IRQn_I2C2                   = 24,     //!< I2C2 Interrupt
    IRQn_SPI1                   = 25,     //!< SPI1 Interrupt
    IRQn_SPI2                   = 26,     //!< SPI2 Interrupt
    IRQn_USART1                 = 27,     //!< USART1 Interrupt
    IRQn_USART2                 = 28,     //!< USART2 Interrupt
    IRQn_USART6_8               = 29,     //!< USART6 to 8 Interrupt
#elif defined (CS32F030)
    IRQn_WWDT                   = 0,      //!< Window WatchDog Interrupt
    IRQn_LVD                    = 1,      //!< LVD through EXTI Line detect Intrrupt    
    IRQn_RTC                    = 2,      //!< RTC through EXTI Line Interrupt
    IRQn_FLASH                  = 3,      //!< FLASH Interrupt
    IRQn_RCU                    = 4,      //!< RCU Interrupt
    IRQn_EXTI0_1                = 5,      //!< EXTI Line 0 and 1 Interrupts
    IRQn_EXTI2_3                = 6,      //!< EXTI Line 2 and 3 Interrupts
    IRQn_EXTI4_15               = 7,      //!< EXTI Line 4 to 15 Interrupts
    IRQn_DMA1_CHANNEL1          = 9,      //!< DMA1 Channel 1 Interrupt
    IRQn_DMA1_CHANNEL2_3        = 10,     //!< DMA1 Channel 2 and Channel 3 Intrrupts
    IRQn_DMA1_CHANNEL4_5        = 11,     //!< DMA1 Channel 4 and Channel 5 Intrrupts
    IRQn_ADC1                   = 12,     //!< ADC1 Interrupt
    IRQn_TIM1_BRK_UP_TRG_COM    = 13,     //!< TIM1 Break, Update, Trigger and ommutation Interrupts
    IRQn_TIM1_CC                = 14,     //!< TIM1 Capture Compare Interrupt
    IRQn_TIM3                   = 16,     //!< TIM3 Interrupt
    IRQn_TIM6                   = 17,     //!< TIM6 Interrupt
    IRQn_TIM14                  = 19,     //!< TIM14 Interrupt
    IRQn_TIM15                  = 20,     //!< TIM15 Interrupt
    IRQn_TIM16                  = 21,     //!< TIM16 Interrupt
    IRQn_TIM17                  = 22,     //!< TIM17 Interrupt
    IRQn_I2C1                   = 23,     //!< I2C1 Interrupt
    IRQn_I2C2                   = 24,     //!< I2C2 Interrupt
    IRQn_SPI1                   = 25,     //!< SPI1 Interrupt
    IRQn_SPI2                   = 26,     //!< SPI2 Interrupt
    IRQn_USART1                 = 27,     //!< USART1 Interrupt
    IRQn_USART2                 = 28,     //!< USART2 Interrupt
#elif defined (CS32A039)
    IRQn_WWDT                   = 0,      //!< Window WatchDog Interrupt
    IRQn_LVD                    = 1,      //!< LVD through EXTI Line detect Intrrupt
    IRQn_RTC                    = 2,      //!< RTC through EXTI Line Interrupt
    IRQn_FLASH                  = 3,      //!< FLASH Interrupt
    IRQn_RCU                    = 4,      //!< RCU Interrupt
    IRQn_EXTI0_1                = 5,      //!< EXTI Line 0 and 1 Interrupts
    IRQn_EXTI2_3                = 6,      //!< EXTI Line 2 and 3 Interrupts
    IRQn_EXTI4_15               = 7,      //!< EXTI Line 4 to 15 Interrupts
    IRQn_DMA1_CHANNEL1          = 9,      //!< DMA1 Channel 1 Interrupt
    IRQn_DMA1_CHANNEL2_3        = 10,     //!< DMA1 Channel 2 and Channel 3 Intrrupts
    IRQn_DMA1_CHANNEL4_5        = 11,     //!< DMA1 Channel 4 and Channel 5 Intrrupts
    IRQn_ADC1                   = 12,     //!< ADC1 Interrupt
    IRQn_TIM1_BRK_UP_TRG_COM    = 13,     //!< TIM1 Break, Update, Trigger and ommutation Interrupts
    IRQn_TIM1_CC                = 14,     //!< TIM1 Capture Compare Interrupt
    IRQn_TIM2                   = 15,     //!< TIM2 Interrupt
    IRQn_TIM3                   = 16,     //!< TIM3 Interrupt
    IRQn_TIM6                   = 17,     //!< TIM6 Interrupt
    IRQn_TIM14                  = 19,     //!< TIM14 Interrupt
    IRQn_TIM15                  = 20,     //!< TIM15 Interrupt
    IRQn_TIM16                  = 21,     //!< TIM16 Interrupt
    IRQn_TIM17                  = 22,     //!< TIM17 Interrupt
    IRQn_I2C1                   = 23,     //!< I2C1 Interrupt
    IRQn_I2C2                   = 24,     //!< I2C2 Interrupt
    IRQn_SPI1                   = 25,     //!< SPI1 Interrupt
    IRQn_USART1                 = 27,     //!< USART1 Interrupt
    IRQn_USART2                 = 28,     //!< USART2 Interrupt
    IRQn_USART6_8               = 29      //!< USART6 to 8 Interrupt
#endif
} IRQn_Type;

/**
  * @}
  */


#include "core_cm0.h"


/** @addtogroup Exported_types
  * @{
  */

/**
  * @enum error_status_t
  * @brief Error status definition
  */
typedef enum {
    ERROR   = 0,
    SUCCESS = !ERROR
} error_status_t;

/**
  * @enum bit_status_t
  * @brief bit flag set or status get definitoin
  */
typedef enum {
    RESET   = 0,
    SET     = !RESET
} bit_status_t;

/**
  * @enum enable_state_t
  * @brief enable or disable  definition
  */
typedef enum {
    DISABLE   = 0,
    ENABLE    = !DISABLE
} enable_state_t;

/**
  * @brief Check enable  definition
  */
#define FUNCTIONAL_STATE_CHECK(STATE)          (((STATE) == DISABLE) || ((STATE == ENABLE)))

/**
  * @brief Register modify macro
  */
#define MODIFY_REG(REG, CLEARMASK, SETMASK)	((REG) = ((REG) & (~(CLEARMASK))) | (SETMASK))	


/** @addtogroup Peripheral_registers_structues
  * @{
  */

/**
  * @struct adc_reg_t
  * @brief Analog to Digital Converter structure definition
  */
typedef struct {
    __IO    uint32_t STAT;         	//!< ADC status register
    __IO    uint32_t INTEN;        	//!< ADC Interrupt Enable register
    __IO    uint32_t CTR;          	//!< ADC general control register
    __IO    uint32_t CFG;          	//!< ADC Configuration register
    __IO    uint32_t CLK;          	//!< ADC clock source register
    __IO    uint32_t SMPLR;        	//!< ADC Sampling time register
            uint32_t RESERVED1;    	//!< Reserved
            uint32_t RESERVED2;    	//!< Reserved
    __IO    uint32_t WDTH;         	//!< ADC watchdog threshold register 
            uint32_t RESERVED3;    	//!< Reserved
    __IO    uint32_t CHANSEL;      	//!< ADC conversion channel sction register
            uint32_t RESERVED4[5]; 	//!< Reserved
    __IO    uint32_t OUTDAT;       	//!< ADC conversion output daregister
            uint32_t RESERVED5[177];//!< Reserved  
    __IO    uint32_t INNCHEN;		//!< ADC internal conversion channel enabl register    
} adc_reg_t;

/**
  * @struct crc_reg_t
  * @brief CRC calculation structure definitio
  */
typedef struct
{
    __IO    uint32_t DATA;        	//!< CRC Data register
    __IO    uint8_t  FREDATA;     	//!< CRC independent data register
            uint8_t  RESERVED0;   	//!< Reserved
            uint16_t RESERVED1;   	//!< Reserved
    __IO    uint32_t CTR;         	//!< CRC Control register
            uint32_t RESERVED2;   	//!< Reserved
    __IO    uint32_t INITCFG;     	//!< Initial CRC value registe
    __IO    uint32_t POL;         	//!< CRC polynomial register
} crc_reg_t;

/**
  * @struct debug_reg_t
  * @brief Debug register structure definition
  */
typedef struct
{
    __IO    uint32_t ID;          //!< MCU device ID code
    __IO    uint32_t LPWCFG;      //!< Debug MCU configuration register
    __IO    uint32_t APB1CFG;     //!< Debug MCU APB1 freeze register
    __IO    uint32_t APB2CFG;     //!< Debug MCU APB2 freeze register
} debug_reg_t;

/**
 * @struct dma_channel_reg_t
 * @brief DMA channel register structure defiition
 */
typedef struct
{
    __IO    uint32_t CHxCTR;        //!< DMA channel x controller register
    __IO    uint32_t CHxNUM;        //!< Transfer data number register of DMA cannel x
    __IO    uint32_t CHxPA;         //!< Peripheral address register of DMA chanel x
    __IO    uint32_t CHxMA;         //!< Memory address register of DMA channelx
} dma_channel_reg_t;

/**
  * @struct dma_reg_t
  * @brief DMA  register structure definition
  */
typedef struct {
    __IO    uint32_t STS;            //!< DMA interrupt status register
    __IO    uint32_t INTFC;          //!< DMA interrupt flag clear register
} dma_reg_t;

/**
  * @struct exti_reg_t
  * @brief External Interrupt/Event Controllerstructure definition
  */
typedef struct {
    __IO    uint32_t INTEN;          //!< Interrupt enable register
    __IO    uint32_t EVTEN;          //!< Event enable register
    __IO    uint32_t RTEN;           //!< Rising edge trigger enable register
    __IO    uint32_t FTEN;           //!< Falling edge trigger enable register
    __IO    uint32_t SWTIEN;         //!< Software trigger interrupt/event enabe register
    __IO    uint32_t PDF;            //!< Pending flag register
} exti_reg_t;

/**
  * @struct fmc_reg_t
  * @brief FMC (FLASH Memory Control )Register structure definition
  */
typedef struct {
    __IO    uint32_t WCR;          //!< FMC Wait control register
    __IO    uint32_t CCODE;        //!< FMC Control code register
    __IO    uint32_t OBCCODE;      //!< FMC Option Byte Control code register
    __IO    uint32_t STS;          //!< FMC status register
    __IO    uint32_t CTR;          //!< FMC Control register
    __IO    uint32_t ERSADR;       //!< Flash erase address register,
    __IO    uint32_t RESERVED;     //!< Reserved
    __IO    uint32_t OBSTS;        //!< Option byte status register
    __IO    uint32_t WPSTS;        //!< Write protection status register
    __IO    uint32_t CFG;          //!< Config register
    __IO    uint32_t CFGU;         //!< Config register    
} fmc_reg_t;

/**
  * @struct ob_reg_t
  * @brief Option Bytes Registers structure deinition
  */
typedef struct
{
    __IO uint16_t RPROT;          /*!< FLASH option byte Read protection,               Address offset: 0x00 */
    __IO uint16_t USER;           /*!< FLASH option byte user options,                  Address offset: 0x02 */
    __IO uint16_t DATA0;          /*!< User data byte 0 (stored in FLASH_OBSTS[23:16]), Address offset: 0x04 */
    __IO uint16_t DATA1;          /*!< User data byte 1 (stored in FLASH_OBSTS[31:24]), Address offset: 0x06 */
    __IO uint16_t WPROTOB0;       /*!< FLASH option byte write protection 0,            Address offset: 0x08 */
    __IO uint16_t WPROTOB1;       /*!< FLASH option byte write protection 1,            Address offset: 0x0A */
} ob_reg_t;

/**
  * @struct gpio_reg_t
  * @brief General Purpose IO Registers structre definition
  */
typedef struct {
    __IO    uint32_t PFR;          //!< GPIO port function register
    __IO    uint16_t PODENR;       //!< GPIO port output open-drain enable regiser
            uint16_t RESERVED0;    //!< Reserved
    __IO    uint32_t POSR;         //!< GPIO port output speed register
    __IO    uint32_t PUPDR;        //!< GPIO port pull-up/pull-down register
    __IO    uint16_t DI;           //!< GPIO port data input register
            uint16_t RESERVED1;    //!< Reseved
    __IO    uint16_t DO;           //!< GPIO port output data register
            uint16_t RESERVED2;    //!< Reserved
    __IO    uint32_t SCR;          //!< GPIO port set/clear register
    __IO    uint32_t LOCK;         //!< GPIO port lock register
    __IO    uint32_t MFSEL[2];     //!< GPIO multi-function selection register
    __IO    uint16_t CLRR;         //!< GPIO port clear register
            uint16_t RESERVED3;    //!< Reserved
} gpio_reg_t;

/**
  * @struct syscfg_reg_t
  * @brief SysTem Configuration Registers struture definition
  */
typedef struct {
    __IO    uint32_t RMAPCFG;           //!<SYSCFG remap configuration
            uint32_t RESERVED;          //!<Reserved
    __IO    uint32_t EXTISRC[4];        //!<SYSCFG external interrupt source seection register
    __IO    uint32_t ERRLOCK;           //!<SYSCFG error and timer break lock
    __IO	uint32_t GPIO_VTH[2];
} syscfg_reg_t;


/**
  * @struct i2c_reg_t
  * @brief Inter-integrated Circuit Interface egisters structure definition
  */
typedef struct
{
    __IO    uint32_t CTR1;      //!< I2C Control register 1
    __IO    uint32_t CTR2;      //!< I2C Control register 2
    __IO    uint32_t SADR1;     //!< I2C slave address 1 register
    __IO    uint32_t SADR2;     //!< I2C slave address 2 register
    __IO    uint32_t TMR;       //!< I2C Timing register
    __IO    uint32_t OVRT;      //!< I2C overtime register
    __IO    uint32_t STS;       //!< I2C status register
    __IO    uint32_t STSC;      //!< I2C status clear register
    __IO    uint32_t PECCODE;   //!< I2C received PEC code register
    __IO    uint32_t RXBUF;     //!< I2C Receive buffer register
    __IO    uint32_t TXBUF;     //!< I2C Transmit buffer register
} i2c_reg_t;

/**
  * @struct fwdt_reg_t* @brief FWDT(Free Watchdog Timer) Registersstructure definition
  */
typedef struct {
    __IO    uint32_t CCODE;   //!< FWDT Control code register
    __IO    uint32_t PDIV;    //!< FWDT Pre-divider register
    __IO    uint32_t UVAL;    //!< FWDT Update register
    __IO    uint32_t STS;     //!< FWDT Status register
    __IO    uint32_t WINVAL;  //!< FWDT Window value register
} fwdt_reg_t;

/**
  * @struct pmu_reg_t
  * @brief Power management unit (PMU) Registers structure definition
  */
typedef struct {
    __IO    uint32_t CTR;      //!< control register
    __IO    uint32_t CS;       //!< control/statu register
} pmu_reg_t;

/**
  * @struct rcu_reg_t* @brief Reset and Clock Control Registers sructure definition
  */
typedef struct {
    __IO    uint32_t CTR;       //!< clock control register
    __IO    uint32_t CFG;       //!< clock configuration register
    __IO    uint32_t INTR;      //!< clock interrupt register
    __IO    uint32_t APB2RST;   //!< APB2 peripheral reset register
    __IO    uint32_t APB1RST;   //!< APB1 peripheral reset register
    __IO    uint32_t AHBEN;     //!< AHB peripheral clock register
    __IO    uint32_t APB2EN;    //!< APB2 peripheral clock enable register
    __IO    uint32_t APB1EN;    //!< APB1 peripheral clock enable register
    __IO    uint32_t VBDC;      //!< VBAT domain control register
    __IO    uint32_t STS;       //!< status register
    __IO    uint32_t AHBRST;    //!< AHB  reset register
    __IO    uint32_t CFG2;      //!< clock configuration register 2
    __IO    uint32_t CFG3;      //!< clock configuration register 3
    __IO    uint32_t CTR2;      //!< clock control register 2
} rcu_reg_t;

/**
  * @struct rtc_reg_t
  * @brief Real-Time Clock Registers structuredefinition
  */
typedef struct {
    __IO    uint32_t TIME;        //!< RTC time register
    __IO    uint32_t DATE;        //!< RTC date register
    __IO    uint32_t CTR;         //!< RTC control register
    __IO    uint32_t STS;         //!< RTC status register
    __IO    uint32_t PDIV;        //!< RTC pre-divider register,
            uint32_t RESERVED1;   //!< Reserved
            uint32_t RESERVED2;   //!< Reserved
    __IO    uint32_t ACFG1;       //!< RTC alarm config1 register
            uint32_t RESERVED3;   //!< Reserved
    __IO    uint32_t CCODE;       //!< RTC control code registerr
    __IO    uint32_t SSEC;        //!< RTC sub second register
    __IO    uint32_t ADJ;         //!< RTC adjustment register
    __IO    uint32_t TR2;         //!< RTC Time recording2 register
    __IO    uint32_t TR1;         //!< RTC Time recording1 register
    __IO    uint32_t TR3;         //!< RTC Time recording3 register
    __IO    uint32_t RTC_1SCAL;   //!< RTC 1Hz clock calibration register
    __IO    uint32_t MF;          //!< RTC multiplex function register
    __IO    uint32_t ACFG2;       //!< RTC alarm config2 register
            uint32_t RESERVED4;   //!< Reserved
            uint32_t RESERVED5;   //!< Reserved
    __IO    uint32_t AO0;         //!< RTC always on registers 0
    __IO    uint32_t AO1;         //!< RTC always on registers 1
    __IO    uint32_t AO2;         //!< RTC always on registers 2
    __IO    uint32_t AO3;         //!< RTC always on registers 3
    __IO    uint32_t AO4;         //!< RTC always on registers 4
} rtc_reg_t;

/**
  * @struct spi_reg_t
  * @brief Serial Peripheral Interface Registes structure definition
  */
typedef struct {
    __IO    uint16_t CTR1;          //!< SPI Control register 1
            uint16_t RESERVED0;     //!< Reserved
    __IO    uint16_t CTR2;          //!< SPI Control register 2
            uint16_t RESERVED1;     //!< Reserved
    __IO    uint16_t STS;           //!< SPI Status register
            uint16_t RESERVED2;     //!< Reserved
    __IO    uint16_t DATA;          //!< SPI data register
            uint16_t RESERVED3;     //!< Reserved
    __IO    uint16_t CRCPOLYR;      //!< SPI CRC polynomial register
            uint16_t RESERVED4;     //!< Reserved
    __IO    uint16_t RCRC;          //!< SPI Rx CRC register
            uint16_t RESERVED5;     //!< Reserved
    __IO    uint16_t TCRC;          //!< SPI Tx CRC register
            uint16_t RESERVED6;     //!< Reserved
    __IO    uint16_t I2SCTR;        //!< I2S control register
            uint16_t RESERVED7;     //!< Reserved
    __IO    uint16_t I2SPDIV;       //!< I2S pre-divider register
            uint16_t RESERVED8;     //!< Reserved
} spi_reg_t;

/**
  * @struct tim_reg_t
  * @brief TIM Registers structure definition
  */
typedef struct {
    __IO    uint32_t CTR1;            //!< TIMx control register 1
    __IO    uint32_t CTR2;            //!< TIMx control register 2
    __IO    uint32_t SMCFG;           //!< TIMx slave mode configuration registr
    __IO    uint32_t DIEN;            //!< TIMx DMA and interrupt enable registr
    __IO    uint32_t STS;             //!< TIMx status register
    __IO    uint32_t SWEGR;           //!< TIMx software event generation regiser
    __IO    uint32_t CHxCFGR[2];      //!< TIMx channel 1~4 configuation register
    __IO    uint32_t CCCTR;           //!< TIMx channel capture compare controeister
    __IO    uint32_t CNT;             //!< TIMx counter register
    __IO    uint32_t PDIV;            //!< TIMx pre-divider register
    __IO    uint32_t UVAL;            //!< TIMx counter update register
    __IO    uint32_t UVALREP;         //!< TIMx counter update repetition regiser
    __IO    uint32_t CHxCCVAL[4];     //!< TIMx channel 1~4 capture compare value register
    __IO    uint32_t CHOPR;           //!< TIMx channel output protect register
    __IO    uint32_t DMAACR;          //!< TIMx DMA access configuration registr
    __IO    uint32_t DMAIR;           //!< TIMx DMA access interface register
    __IO    uint32_t REMAP;           //!< TIM14 remap register
} tim_reg_t;

/**
  * @struct usart_reg_t
  * @brief Universal Synchronous Asynchronous eceiver Transmitter registers strur definition
  */
typedef struct {
    __IO    uint32_t CTR1;          //!< USART Control register 1
    __IO    uint32_t CTR2;          //!< USART Control register 2
    __IO    uint32_t CTR3;          //!< USART Control register 3
    __IO    uint16_t BRT;           //!< USART Baud rate register
            uint16_t RESERVED1;     //!< Reserved
    __IO    uint16_t GTPDIV;        //!< Guard time and pre-divider register
            uint16_t RESERVED2;     //!< Reserved
    __IO    uint32_t ROT;           //!< Receiver timeout register
    __IO    uint16_t SWTR;          //!< Software Trigger register
            uint16_t RESERVED3;     //!< Reserved
    __IO    uint32_t STS;           //!< USART Interrupt and status register
    __IO    uint32_t IFCLR;         //!< USART Interrupt flag Clear register
    __IO    uint16_t RXBUF;         //!< Receive buffer register
            uint16_t RESERVED4;     //!< Reserved
    __IO    uint16_t TXBUF;         //!< Transmit buffer register
            uint16_t RESERVED5;     //!< Reserved
} usart_reg_t;


/**
  * @struct wwdt_reg_t
  * @brief WWDT(Window Watchdog Timer) registes  registers structure definition
  */
typedef struct {
    __IO    uint32_t CTR1;   //!< WWDT Control register 1
    __IO    uint32_t CTR2;   //!< WWDT Control register 2
    __IO    uint32_t STS;    //!< WWDT Status register
} wwdt_reg_t;


/**
  * @}
  */


/** @addtogroup Peripheral_memory_map
  * @{
  */
#define FLASH_BASE            ((uint32_t)0x08000000) //!< FLASH base address ih alias region
#define SRAM_BASE             ((uint32_t)0x20000000) //!< SRAM base address inealias region
#define PERIPH_BASE           ((uint32_t)0x40000000) //!< Peripheral base addr n the alias region
#define OB_BASE               ((uint32_t)0x1FFFF800) //!< FLASH Option Bytes b ddress

/**
  * @brief Peripheral memory map definition
  */
#define APB_PERIPH_BASE        PERIPH_BASE
#define AHB_PERIPH_BASE       (PERIPH_BASE      + 0x00020000)
#define AHB2_PERIPH_BASE      (PERIPH_BASE      + 0x08000000)


#define TIM2_BASE             (APB_PERIPH_BASE  + 0x00000000)
#define TIM3_BASE             (APB_PERIPH_BASE  + 0x00000400)
#define TIM6_BASE             (APB_PERIPH_BASE  + 0x00001000)
#define TIM14_BASE            (APB_PERIPH_BASE  + 0x00002000)
#define RTC_BASE              (APB_PERIPH_BASE  + 0x00002800)
#define WWDT_BASE             (APB_PERIPH_BASE  + 0x00002C00)
#define FWDT_BASE             (APB_PERIPH_BASE  + 0x00003000)
#define SPI2_BASE             (APB_PERIPH_BASE  + 0x00003800)
#define USART2_BASE           (APB_PERIPH_BASE  + 0x00004400)
#define I2C1_BASE             (APB_PERIPH_BASE  + 0x00005400)
#define I2C2_BASE             (APB_PERIPH_BASE  + 0x00005800)
#define PMU_BASE              (APB_PERIPH_BASE  + 0x00007000)
#define SYSCFG_BASE           (APB_PERIPH_BASE  + 0x00010000)

#define EXTI_BASE             (APB_PERIPH_BASE  + 0x00010400)
#define USART6_BASE           (APB_PERIPH_BASE  + 0x00011400)
#define USART7_BASE           (APB_PERIPH_BASE  + 0x00011800)
#define USART8_BASE           (APB_PERIPH_BASE  + 0x00011C00)
#define ADC1_BASE             (APB_PERIPH_BASE  + 0x00012400)
#define TIM1_BASE             (APB_PERIPH_BASE  + 0x00012C00)
#define SPI1_BASE             (APB_PERIPH_BASE  + 0x00013000)
#define USART1_BASE           (APB_PERIPH_BASE  + 0x00013800)
#define TIM15_BASE            (APB_PERIPH_BASE  + 0x00014000)
#define TIM16_BASE            (APB_PERIPH_BASE  + 0x00014400)
#define TIM17_BASE            (APB_PERIPH_BASE  + 0x00014800)
#define DBGMCU_BASE           (APB_PERIPH_BASE  + 0x00015800)

#define DMA1_BASE             (AHB_PERIPH_BASE  + 0x00000000)
#define DMA1_CHANNEL1_BASE    (DMA1_BASE        + 0x00000008)
#define DMA1_CHANNEL2_BASE    (DMA1_BASE        + 0x0000001C)
#define DMA1_CHANNEL3_BASE    (DMA1_BASE        + 0x00000030)
#define DMA1_CHANNEL4_BASE    (DMA1_BASE        + 0x00000044)
#define DMA1_CHANNEL5_BASE    (DMA1_BASE        + 0x00000058)

#define RCU_BASE              (AHB_PERIPH_BASE  + 0x00001000)
#define FLASH_REG_BASE        (AHB_PERIPH_BASE  + 0x00002000) //!< FLASH registrs base address
#define CRC_BASE              (AHB_PERIPH_BASE  + 0x00003000)

#define GPIOA_BASE            (AHB2_PERIPH_BASE + 0x00000000)
#define GPIOB_BASE            (AHB2_PERIPH_BASE + 0x00000400)
#define GPIOC_BASE            (AHB2_PERIPH_BASE + 0x00000800)
#define GPIOD_BASE            (AHB2_PERIPH_BASE + 0x00000C00)
#define GPIOE_BASE            (AHB2_PERIPH_BASE + 0x00001000)
#define GPIOF_BASE            (AHB2_PERIPH_BASE + 0x00001400)

/**
  * @}
  */



/** @addtogroup Peripheral_declaration
  * @{
  */
#define TIM2                ((tim_reg_t *)        TIM2_BASE)
#define TIM3                ((tim_reg_t *)        TIM3_BASE)
#define TIM6                ((tim_reg_t *)        TIM6_BASE)
#define TIM14               ((tim_reg_t *)        TIM14_BASE)
#define RTC                 ((rtc_reg_t *)        RTC_BASE)
#define WWDT                ((wwdt_reg_t *)       WWDT_BASE)
#define FWDT                ((fwdt_reg_t *)       FWDT_BASE)
#define SPI2                ((spi_reg_t *)        SPI2_BASE)
#define USART2              ((usart_reg_t *)      USART2_BASE)
#define I2C1                ((i2c_reg_t *)        I2C1_BASE)
#define I2C2                ((i2c_reg_t *)        I2C2_BASE)
#define PMU                 ((pmu_reg_t *)        PMU_BASE)
#define SYSCFG              ((syscfg_reg_t *)     SYSCFG_BASE)

#define EXTI                ((exti_reg_t *)       EXTI_BASE)
#define USART6              ((usart_reg_t *)      USART6_BASE)
#define USART7              ((usart_reg_t *)      USART7_BASE)
#define USART8              ((usart_reg_t *)      USART8_BASE)
#define ADC1                ((adc_reg_t *)        ADC1_BASE)
#define TIM1                ((tim_reg_t *)        TIM1_BASE)
#define SPI1                ((spi_reg_t *)        SPI1_BASE)
#define USART1              ((usart_reg_t *)      USART1_BASE)
#define TIM15               ((tim_reg_t *)        TIM15_BASE)
#define TIM16               ((tim_reg_t *)        TIM16_BASE)
#define TIM17               ((tim_reg_t *)        TIM17_BASE)
#define DBGMCU              ((debug_reg_t *)      DBGMCU_BASE)

#define DMA1                ((dma_reg_t *)         DMA1_BASE)
#define DMA1_CHANNEL1       ((dma_channel_reg_t *) DMA1_CHANNEL1_BASE)
#define DMA1_CHANNEL2       ((dma_channel_reg_t *) DMA1_CHANNEL2_BASE)
#define DMA1_CHANNEL3       ((dma_channel_reg_t *) DMA1_CHANNEL3_BASE)
#define DMA1_CHANNEL4       ((dma_channel_reg_t *) DMA1_CHANNEL4_BASE)
#define DMA1_CHANNEL5       ((dma_channel_reg_t *) DMA1_CHANNEL5_BASE)

#define FLASH               ((fmc_reg_t *)        FLASH_REG_BASE)
#define OB                  ((ob_reg_t *)         OB_BASE)
#define RCU                 ((rcu_reg_t *)        RCU_BASE)
#define CRC                 ((crc_reg_t *)        CRC_BASE)

#define GPIOA               ((gpio_reg_t *)       GPIOA_BASE)
#define GPIOB               ((gpio_reg_t *)       GPIOB_BASE)
#define GPIOC               ((gpio_reg_t *)       GPIOC_BASE)
#define GPIOD               ((gpio_reg_t *)       GPIOD_BASE)
#define GPIOE               ((gpio_reg_t *)       GPIOE_BASE)
#define GPIOF               ((gpio_reg_t *)       GPIOF_BASE)

/**
  * @}
  */




/** @addtogroup Peripheral_Registers_Bits_Deinition
  * @{
  */


/*---------------------------------------------------------------------------*/
/*             Analog to Digital Converter (DC)                              */
/*---------------------------------------------------------------------------*/

/**
  * @brief ADC_STAT register  Bits definition
  */
#define ADC_STAT_WDEVT                ((uint32_t)0x00000080)        //!< analogwatchdog event flag
#define ADC_STAT_DOVR                 ((uint32_t)0x00000010)        //!< ADC daa overrun flag
#define ADC_STAT_EOCG                 ((uint32_t)0x00000008)        //!< End ofconversion group flag
#define ADC_STAT_EOCH                 ((uint32_t)0x00000004)        //!< End ofchannel conversion flag
#define ADC_STAT_EOSP                 ((uint32_t)0x00000002)        //!< End ofsampling phase flag
#define ADC_STAT_EOI                  ((uint32_t)0x00000001)        //!< End ofADC initialization


/**
  * @brief ADC_INTEN register Bits definition
  */
#define ADC_INTEN_WDEVTIE             ((uint32_t)0x00000080)        //!< analogwatchdog event interrupt enable
#define ADC_INTEN_DOVRIE              ((uint32_t)0x00000010)        //!< ADC daa overrun interrupt enable
#define ADC_INTEN_EOGIE               ((uint32_t)0x00000008)        //!< End ofconversion group interrupt enable
#define ADC_INTEN_EOCIE               ((uint32_t)0x00000004)        //!< End ofchannel conversion interrupt enable
#define ADC_INTEN_EOSPIE              ((uint32_t)0x00000002)        //!< End ofsampling phase interrupt enable
#define ADC_INTEN_EOIIE               ((uint32_t)0x00000001)        //!< End ofADC initialization interrupt enable


/**
  * @brief ADC_CTR register Bits definition
  */
#define ADC_CTR_CALB                  ((uint32_t)0x80000000)        //!< ADC caibration control
#define ADC_CTR_ADSTOP                ((uint32_t)0x00000010)        //!< ADC stp conversion command
#define ADC_CTR_ADSTRT                ((uint32_t)0x00000004)        //!< ADC strt conversion command
#define ADC_CTR_ADCOFF                ((uint32_t)0x00000002)        //!< ADC poer off command
#define ADC_CTR_ADCON                 ((uint32_t)0x00000001)        //!< ADC poer on command

/**
  * @brief ADC_CFG register   Bits definition
  */
#define  ADC_CFG_WDGCHAN              ((uint32_t)0x7C000000)       //!< WDGCHAN4:0] bits (Analog watchdog monitor channel selection).
#define  ADC_CFG_WDGCHAN_0            ((uint32_t)0x04000000)       //!< Bit 0
#define  ADC_CFG_WDGCHAN_1            ((uint32_t)0x08000000)       //!< Bit 1
#define  ADC_CFG_WDGCHAN_2            ((uint32_t)0x10000000)       //!< Bit 2
#define  ADC_CFG_WDGCHAN_3            ((uint32_t)0x20000000)       //!< Bit 3
#define  ADC_CFG_WDGCHAN_4            ((uint32_t)0x40000000)       //!< Bit 4
#define  ADC_CFG_WDGEN                ((uint32_t)0x00800000)       //!< Analog atchdog enable
#define  ADC_CFG_WDGCHMODE            ((uint32_t)0x00400000)       //!< Analog atchdog channel monitor mode.
#define  ADC_CFG_DISCONT              ((uint32_t)0x00010000)       //!< Discontnuous conversion mode
#define  ADC_CFG_ATSTDBY              ((uint32_t)0x00008000)       //!< ADC aut standby mode
#define  ADC_CFG_PAUSE                ((uint32_t)0x00004000)       //!< converson pause mode
#define  ADC_CFG_GCONT                ((uint32_t)0x00002000)       //!< Group cnversion Single/continuous mode
#define  ADC_CFG_DOVRWRT              ((uint32_t)0x00001000)       //!< Converson data overrun overwriten mode
#define  ADC_CFG_TRGMODE              ((uint32_t)0x00000C00)       //!< TRGMODE1:0] bits (Coverstion Trigger mode selection).
#define  ADC_CFG_TRGMODE_0            ((uint32_t)0x00000400)       //!< Bit 0
#define  ADC_CFG_TRGMODE_1            ((uint32_t)0x00000800)       //!< Bit 1
#define  ADC_CFG_HTRGSEL              ((uint32_t)0x000001C0)       //!< HTRGSEL2:0] bits (Hardware trigger source selection).
#define  ADC_CFG_HTRGSEL_0            ((uint32_t)0x00000040)       //!< Bit 0
#define  ADC_CFG_HTRGSEL_1            ((uint32_t)0x00000080)       //!< Bit 1
#define  ADC_CFG_HTRGSEL_2            ((uint32_t)0x00000100)       //!< Bit 2
#define  ADC_CFG_DATALG               ((uint32_t)0x00000020)       //!< Converson data format alignment.
#define  ADC_CFG_DATRES               ((uint32_t)0x00000018)       //!< DATRES[:0] bits (Conversion data reselution).
#define  ADC_CFG_DATRES_0             ((uint32_t)0x00000008)       //!< Bit 0
#define  ADC_CFG_DATRES_1             ((uint32_t)0x00000010)       //!< Bit 1
#define  ADC_CFG_CGDIR                ((uint32_t)0x00000004)       //!< Coveraton group sequence direction
#define  ADC_CFG_DMAMODE              ((uint32_t)0x00000002)       //!< Direct memory access single/circle mode
#define  ADC_CFG_DMAEN                ((uint32_t)0x00000001)       //!< Direct memory access enable

/**
  * @brief ADC_CLK register Bits definition
  */
#define  ADC_CLK_CKSRC                ((uint32_t)0xC0000000)       //!< ADC clok source selection
#define  ADC_CLK_CKSRC_1              ((uint32_t)0x80000000)       //!< ADC cloked by PCLK div4.
#define  ADC_CLK_CKSRC_0              ((uint32_t)0x40000000)       //!< ADC cloked by PCLK div2 .

/**
  * @brief ADC_SMPLR register Bit definition
  */
#define  ADC_SMPLR_SMPLT              ((uint32_t)0x00000007)       //!< SMPLT[20] bits (Sampling time selection).
#define  ADC_SMPLR_SMPLT_0            ((uint32_t)0x00000001)       //!< Bit 0
#define  ADC_SMPLR_SMPLT_1            ((uint32_t)0x00000002)       //!< Bit 1
#define  ADC_SMPLR_SMPLT_2            ((uint32_t)0x00000004)       //!< Bit 2

/**
  * @brief ADC_WDTH register  Bit definition
  */
#define  ADC_WDTH_HITH                ((uint32_t)0x0FFF0000)       //!< Analog atchdog higher threshold.
#define  ADC_WDTH_LOTH                ((uint32_t)0x00000FFF)       //!< Analog atchdog lower threshold.

/**
  * @brief ADC_CHANSEL register Bit definition
  */
#define  ADC_CHANSEL_CHANSEL18        ((uint32_t)0x00040000)       //!< Channel18 selection.
#define  ADC_CHANSEL_CHANSEL17        ((uint32_t)0x00020000)       //!< Channel17 selection.
#define  ADC_CHANSEL_CHANSEL16        ((uint32_t)0x00010000)       //!< Channel16 selection.
#define  ADC_CHANSEL_CHANSEL15        ((uint32_t)0x00008000)       //!< Channel15 selection.
#define  ADC_CHANSEL_CHANSEL14        ((uint32_t)0x00004000)       //!< Channel14 selection.
#define  ADC_CHANSEL_CHANSEL13        ((uint32_t)0x00002000)       //!< Channel13 selection.
#define  ADC_CHANSEL_CHANSEL12        ((uint32_t)0x00001000)       //!< Channel12 selection.
#define  ADC_CHANSEL_CHANSEL11        ((uint32_t)0x00000800)       //!< Channel11 selection.
#define  ADC_CHANSEL_CHANSEL10        ((uint32_t)0x00000400)       //!< Channel10 selection.
#define  ADC_CHANSEL_CHANSEL9         ((uint32_t)0x00000200)       //!< Channel9 selection.
#define  ADC_CHANSEL_CHANSEL8         ((uint32_t)0x00000100)       //!< Channel8 selection.
#define  ADC_CHANSEL_CHANSEL7         ((uint32_t)0x00000080)       //!< Channel7 selection.
#define  ADC_CHANSEL_CHANSEL6         ((uint32_t)0x00000040)       //!< Channel6 selection.
#define  ADC_CHANSEL_CHANSEL5         ((uint32_t)0x00000020)       //!< Channel5 selection.
#define  ADC_CHANSEL_CHANSEL4         ((uint32_t)0x00000010)       //!< Channel4 selection.
#define  ADC_CHANSEL_CHANSEL3         ((uint32_t)0x00000008)       //!< Channel3 selection.
#define  ADC_CHANSEL_CHANSEL2         ((uint32_t)0x00000004)       //!< Channel2 selection.
#define  ADC_CHANSEL_CHANSEL1         ((uint32_t)0x00000002)       //!< Channel1 selection.
#define  ADC_CHANSEL_CHANSEL0         ((uint32_t)0x00000001)       //!< Channel0 selection.

/**
  * @brief ADC_OUTDAT register  Bit definition
  */
#define  ADC_OUTDAT_OUTDAT            ((uint32_t)0x0000FFFF)       //!< converson output data.

/**
  * @brief ADC_INNCHEN register  Bit definitio
  */
#define  ADC_INNCHEN_VBATMEN          ((uint32_t)0x01000000)       //!< VBAT moitor enable.
#define  ADC_INNCHEN_TSEN             ((uint32_t)0x00800000)       //!< Temperaure sensor enable
#define  ADC_INNCHEN_VREFINTEN        ((uint32_t)0x00400000)       //!< VREFINTenable


/*------------------------------------------ --------------------------------*/
/*               CRC calculation unit (CRC)                                  */
/*------------------------------------------ --------------------------------*/

/**
  * @brief CRC_DATA register  Bit definition
  */
#define  CRC_DATA_DATA                ((uint32_t)0xFFFFFFFF)       //!< Data reister bits */

/**
  * @brief CRC_FREDATA register Bit definition
  */
#define  CRC_FREDATA_FREDATA          ((uint8_t)0xFF)              //!< Free Daa register bits

/**
  * @brief CRC_CTR register Bit definition
  */
#define  CRC_CTR_RST                  ((uint32_t)0x00000001)       //!< RESET te CRC computation unit bit
#define  CRC_CTR_DINREVMOD            ((uint32_t)0x00000060)       //!< Input data Reverse mode selection
#define  CRC_CTR_DINREVMOD_0          ((uint32_t)0x00000020)       //!< Bit 0
#define  CRC_CTR_DINREVMOD_1          ((uint32_t)0x00000040)       //!< Bit 1
#define  CRC_CTR_DOREVEN              ((uint32_t)0x00000080)       //!< Output ata Reverse enable

/**
  * @brief CRC_INITCFG register Bit definition
  */
#define  CRC_INITCFG_INITCFG          ((uint32_t)0xFFFFFFFF)       //!< CRC iniial value configuration bits


/*--------------------------------------------------------------------------*/
/*                           Debug module                                   */
/*--------------------------------------------------------------------------*/

/**
  * @brief DBG_ID register Bit definition
  */
#define  DBG_ID_DEV_ID                ((uint32_t)0x00000FFF)       //!< Device dentifier

#define  DBG_ID_REV_ID                ((uint32_t)0xFFFF0000)       //!< REV_ID[5:0] bits (Revision Identifier)
#define  DBG_ID_REV_ID_0              ((uint32_t)0x00010000)       //!< Bit 0
#define  DBG_ID_REV_ID_1              ((uint32_t)0x00020000)       //!< Bit 1
#define  DBG_ID_REV_ID_2              ((uint32_t)0x00040000)       //!< Bit 2
#define  DBG_ID_REV_ID_3              ((uint32_t)0x00080000)       //!< Bit 3
#define  DBG_ID_REV_ID_4              ((uint32_t)0x00100000)       //!< Bit 4
#define  DBG_ID_REV_ID_5              ((uint32_t)0x00200000)       //!< Bit 5
#define  DBG_ID_REV_ID_6              ((uint32_t)0x00400000)       //!< Bit 6
#define  DBG_ID_REV_ID_7              ((uint32_t)0x00800000)       //!< Bit 7
#define  DBG_ID_REV_ID_8              ((uint32_t)0x01000000)       //!< Bit 8
#define  DBG_ID_REV_ID_9              ((uint32_t)0x02000000)       //!< Bit 9
#define  DBG_ID_REV_ID_10             ((uint32_t)0x04000000)       //!< Bit 10
#define  DBG_ID_REV_ID_11             ((uint32_t)0x08000000)       //!< Bit 11
#define  DBG_ID_REV_ID_12             ((uint32_t)0x10000000)       //!< Bit 12
#define  DBG_ID_REV_ID_13             ((uint32_t)0x20000000)       //!< Bit 13
#define  DBG_ID_REV_ID_14             ((uint32_t)0x40000000)       //!< Bit 14
#define  DBG_ID_REV_ID_15             ((uint32_t)0x80000000)       //!< Bit 15

/**
  * @brief DBG_LPWCFG register Bit definition
  */
#define  DBG_LPWCFG_DSM_DBGEN         ((uint32_t)0x00000002)       //!< Stop moe debug support
#define  DBG_LPWCFG_PWD_DBGEN         ((uint32_t)0x00000004)       //!< Standbymode debug support

/**
  * @brief DBG_APB1CFG register Bit definition
  */
#define  DBG_APB1CFG_TIM2_DBG_PAUSE          ((uint32_t)0x00000001)        //!<TIM2 counter paused when system is in debug mode
#define  DBG_APB1CFG_TIM3_DBG_PAUSE          ((uint32_t)0x00000002)        //!<TIM3 counter paused when system is in debug mode
#define  DBG_APB1CFG_TIM6_DBG_PAUSE          ((uint32_t)0x00000010)        //!<TIM6 counter paused when system is in debug mode
#define  DBG_APB1CFG_TIM14_DBG_PAUSE         ((uint32_t)0x00000100)        //!<TIM14 counter paused when system is in debug mode
#define  DBG_APB1CFG_RTC_DBG_PAUSE           ((uint32_t)0x00000400)        //!<RTC paused when system is in debug mode
#define  DBG_APB1CFG_WWDT_DBG_PAUSE          ((uint32_t)0x00000800)        //!<window watchdog paused when system is in debug mode
#define  DBG_APB1CFG_FWDT_DBG_PAUSE          ((uint32_t)0x00001000)        //!<Free watchdog paused when system is in debug mode
#define  DBG_APB1CFG_I2C1_SMBUS_DBG_PAUSE    ((uint32_t)0x00200000)        //!<SMBUS timeout counter  paused when system is in debug mod
#define  DBG_APB1CFG_CAN_DBG_PAUSE           ((uint32_t)0x02000000)        //!<CAN paused when system is in debug mode

/**
  * @brief DBG_APB2CFG register Bit definition
  */
#define  DBG_APB2CFG_TIM1_DBG_PAUSE          ((uint32_t)0x00000800)        //!<TIM1 counter paused when system is in debug mode
#define  DBG_APB2CFG_TIM15_DBG_PAUSE         ((uint32_t)0x00010000)        //!<TIM15   counter paused when system is in debug mode
#define  DBG_APB2CFG_TIM16_DBG_PAUSE         ((uint32_t)0x00020000)        //!<TIM16 counter paused when system is in debug mode
#define  DBG_APB2CFG_TIM17_DBG_PAUSE         ((uint32_t)0x00040000)        //!<TIM17 counter paused when system is in debug mode

/*--------------------------------------------------------------------------*/
/*              DMA Controller (DMA)                                        */
/*--------------------------------------------------------------------------*/

/**
  * @brief DMA_STS register Bit definition
  */
#define  DMA_STS_GIF1                        ((uint32_t)0x00000001)       	//!< lobal interrupt flag of Channel 1
#define  DMA_STS_CMPIF1                      ((uint32_t)0x00000002)       	//!< ransfer complete flag of Channel 1
#define  DMA_STS_HLFIF1                      ((uint32_t)0x00000004)       	//!< alf transfer flag of Channel 1
#define  DMA_STS_ERRIF1                      ((uint32_t)0x00000008)       	//!< ransfer error flag of Channel 1

#define  DMA_STS_GIF2                        ((uint32_t)0x00000010)       	//!< lobal interrupt flag of Channel 2
#define  DMA_STS_CMPIF2                      ((uint32_t)0x00000020)       	//!< ransfer complete flag of Channel 2
#define  DMA_STS_HLFIF2                      ((uint32_t)0x00000040)       	//!< alf transfer flag of Channel 2
#define  DMA_STS_ERRIF2                      ((uint32_t)0x00000080)       	//!< ransfer error flag of Channel 2

#define  DMA_STS_GIF3                        ((uint32_t)0x00000100)       	//!< lobal interrupt flag of Channel 3
#define  DMA_STS_CMPIF3                      ((uint32_t)0x00000200)       	//!< ransfer complete flag of Channel 3
#define  DMA_STS_HLFIF3                      ((uint32_t)0x00000400)       	//!< alf transfer flag of Channel 3
#define  DMA_STS_ERRIF3                      ((uint32_t)0x00000800)       	//!< ransfer error flag of Channel 3

#define  DMA_STS_GIF4                        ((uint32_t)0x00001000)       	//!< lobal interrupt flag of Channel 4
#define  DMA_STS_CMPIF4                      ((uint32_t)0x00002000)       	//!< ransfer complete flag of Channel 4
#define  DMA_STS_HLFIF4                      ((uint32_t)0x00004000)       	//!< alf transfer flag of Channel 4
#define  DMA_STS_ERRIF4                      ((uint32_t)0x00008000)       	//!< ransfer error flag of Channel 4

#define  DMA_STS_GIF5                        ((uint32_t)0x00010000)       	//!< lobal interrupt flag of Channel 5
#define  DMA_STS_CMPIF5                      ((uint32_t)0x00020000)       	//!< ransfer complete flag of Channel 5
#define  DMA_STS_HLFIF5                      ((uint32_t)0x00040000)       	//!< alf transfer flag of Channel 5
#define  DMA_STS_ERRIF5                      ((uint32_t)0x00080000)       	//!< ransfer error flag of Channel 5

/**
  * @brief DMA_INTFC register  Bit definition
  */
#define  DMA_INTFC_GIFC1                     ((uint32_t)0x00000001)        //!< Global interrupt flag clear of Channel 1
#define  DMA_INTFC_CMPIFC1                   ((uint32_t)0x00000002)        //!< Transfer complete flag clear of Channe 1
#define  DMA_INTFC_HLFIFC1                   ((uint32_t)0x00000004)        //!< Half transfer flag clear of Channel 1
#define  DMA_INTFC_ERRIFC1                   ((uint32_t)0x00000008)        //!< Transfer error flag clear of Channel 1

#define  DMA_INTFC_GIFC2                     ((uint32_t)0x00000010)        //!< Global interrupt flag clear of Channel 2
#define  DMA_INTFC_CMPIFC2                   ((uint32_t)0x00000020)        //!< Transfer complete flag clear of Channe 2
#define  DMA_INTFC_HLFIFC2                   ((uint32_t)0x00000040)        //!< Half transfer flag clear of Channel 2
#define  DMA_INTFC_ERRIFC2                   ((uint32_t)0x00000080)        //!< Transfer error flag clear of Channel 2

#define  DMA_INTFC_GIFC3                     ((uint32_t)0x00000100)        //!< Global interrupt flag clear of Channel 3
#define  DMA_INTFC_CMPIFC3                   ((uint32_t)0x00000200)        //!< Transfer complete flag clear of Channe 3
#define  DMA_INTFC_HLFIFC3                   ((uint32_t)0x00000400)        //!< Half transfer flag clear of Channel 3
#define  DMA_INTFC_ERRIFC3                   ((uint32_t)0x00000800)        //!< Transfer error flag clear of Channel 3

#define  DMA_INTFC_GIFC4                     ((uint32_t)0x00001000)        //!< Global interrupt flag clear of Channel 4
#define  DMA_INTFC_CMPIFC4                   ((uint32_t)0x00002000)        //!< Transfer complete flag clear of Channe 4
#define  DMA_INTFC_HLFIFC4                   ((uint32_t)0x00004000)        //!< Half transfer flag clear of Channel 4
#define  DMA_INTFC_ERRIFC4                   ((uint32_t)0x00008000)        //!< Transfer error flag clear of Channel 4

#define  DMA_INTFC_GIFC5                     ((uint32_t)0x00010000)        //!< Global interrupt flag clear of Channel 5
#define  DMA_INTFC_CMPIFC5                   ((uint32_t)0x00020000)        //!< Transfer complete flag clear of Channe 5
#define  DMA_INTFC_HLFIFC5                   ((uint32_t)0x00040000)        //!< Half transfer flag clear of Channel 5
#define  DMA_INTFC_ERRIFC5                   ((uint32_t)0x00080000)        //!< Transfer error flag clear of Channel 5

/**
  * @brief DMA_CHxCTR register Bit definition
  */
#define  DMA_CHxCTR_CEN                      ((uint32_t)0x00000001)        //!< Channel enable
#define  DMA_CHxCTR_CMPIE                    ((uint32_t)0x00000002)        //!< Enable bit for Transfer complete interrupt
#define  DMA_CHxCTR_HLFIE                    ((uint32_t)0x00000004)        //!< Enable bit for Half transfer interrupt
#define  DMA_CHxCTR_ERRIE                    ((uint32_t)0x00000008)        //!< Enable bit for Transfer error interrupt
#define  DMA_CHxCTR_DIR                      ((uint32_t)0x00000010)        //!< Direction of transfer
#define  DMA_CHxCTR_CIRM                     ((uint32_t)0x00000020)        //!< Circular mode
#define  DMA_CHxCTR_PAGM                     ((uint32_t)0x00000040)        //!< Peripheral address generation mode
#define  DMA_CHxCTR_MAGM                     ((uint32_t)0x00000080)        //!< Memory address generation mode

#define  DMA_CHxCTR_PWDH                     ((uint32_t)0x00000300)        //!< Peripheral width PWDH[1:0] bits
#define  DMA_CHxCTR_PWDH_0                   ((uint32_t)0x00000100)        //!< Bit 0
#define  DMA_CHxCTR_PWDH_1                   ((uint32_t)0x00000200)        //!< Bit 1

#define  DMA_CHxCTR_MWDH                     ((uint32_t)0x00000C00)        //!< Memory width MWDH[1:0] bits
#define  DMA_CHxCTR_MWDH_0                   ((uint32_t)0x00000400)        //!< Bit 0
#define  DMA_CHxCTR_MWDH_1                   ((uint32_t)0x00000800)        //!< Bit 1

#define  DMA_CHxCTR_PRIL                     ((uint32_t)0x00003000)        //!< Priority level of Channel PRIL[1:0]bits
#define  DMA_CHxCTR_PRIL_0                   ((uint32_t)0x00001000)        //!< Bit 0
#define  DMA_CHxCTR_PRIL_1                   ((uint32_t)0x00002000)        //!< Bit 1

#define  DMA_CHxCTR_M2MM                     ((uint32_t)0x00004000)        //!< Memory to memory mode

/**
  * @brief DMA_CHxNUM register Bit definition
  */
#define  DMA_CHxNUM_NUM                      ((uint32_t)0x0000FFFF)        //!< Number of data to Transfer

/**
  * @brief DMA_CHxPA register Bit definition
  */
#define  DMA_CHxPA_PADR                      ((uint32_t)0xFFFFFFFF)        //!< Peripheral Address

/**
  * @brief DMA_CHxMA register Bit definition
  */
#define  DMA_CHxMA_MADR                      ((uint32_t)0xFFFFFFFF)        //!< Memory Address


/*---------------------------------------------------------------------------*/
/*          External Interrupt/Event Controler (EXTI)                        */
/*---------------------------------------------------------------------------*/

/**
  * @brief EXTI_INTEN register Bit definition
  */
#define  EXTI_INTEN_INTEN0                    ((uint32_t)0x00000001)        //!< Interrupt enable for line0
#define  EXTI_INTEN_INTEN1                    ((uint32_t)0x00000002)        //!< Interrupt enable for line1
#define  EXTI_INTEN_INTEN2                    ((uint32_t)0x00000004)        //!< Interrupt enable for line2
#define  EXTI_INTEN_INTEN3                    ((uint32_t)0x00000008)        //!< Interrupt enable for line3
#define  EXTI_INTEN_INTEN4                    ((uint32_t)0x00000010)        //!< Interrupt enable for line4
#define  EXTI_INTEN_INTEN5                    ((uint32_t)0x00000020)        //!< Interrupt enable for line5
#define  EXTI_INTEN_INTEN6                    ((uint32_t)0x00000040)        //!< Interrupt enable for line6
#define  EXTI_INTEN_INTEN7                    ((uint32_t)0x00000080)        //!< Interrupt enable for line7
#define  EXTI_INTEN_INTEN8                    ((uint32_t)0x00000100)        //!< Interrupt enable for line8
#define  EXTI_INTEN_INTEN9                    ((uint32_t)0x00000200)        //!< Interrupt enable for line9
#define  EXTI_INTEN_INTEN10                   ((uint32_t)0x00000400)        //!< Interrupt enable for line10
#define  EXTI_INTEN_INTEN11                   ((uint32_t)0x00000800)        //!< Interrupt enable for line11
#define  EXTI_INTEN_INTEN12                   ((uint32_t)0x00001000)        //!< Interrupt enable for line12
#define  EXTI_INTEN_INTEN13                   ((uint32_t)0x00002000)        //!< Interrupt enable for line13
#define  EXTI_INTEN_INTEN14                   ((uint32_t)0x00004000)        //!< Interrupt enable for line14
#define  EXTI_INTEN_INTEN15                   ((uint32_t)0x00008000)        //!< Interrupt enable for line15
#define  EXTI_INTEN_INTEN16                   ((uint32_t)0x00010000)        //!< Interrupt enable for line16
#define  EXTI_INTEN_INTEN17                   ((uint32_t)0x00020000)        //!< Interrupt enable for line17
#define  EXTI_INTEN_INTEN18                   ((uint32_t)0x00040000)        //!< Interrupt enable for line18
#define  EXTI_INTEN_INTEN19                   ((uint32_t)0x00080000)        //!< Interrupt enable for line19
#define  EXTI_INTEN_INTEN20                   ((uint32_t)0x00100000)        //!< Interrupt enable for line20
#define  EXTI_INTEN_INTEN21                   ((uint32_t)0x00200000)        //!< Interrupt enable for line21
#define  EXTI_INTEN_INTEN22                   ((uint32_t)0x00400000)        //!< Interrupt enable for line22
#define  EXTI_INTEN_INTEN23                   ((uint32_t)0x00800000)        //!< Interrupt enable for line23
#define  EXTI_INTEN_INTEN24                   ((uint32_t)0x01000000)        //!< Interrupt enable for line24
#define  EXTI_INTEN_INTEN25                   ((uint32_t)0x02000000)        //!< Interrupt enable for line25
#define  EXTI_INTEN_INTEN26                   ((uint32_t)0x04000000)        //!< Interrupt enable for line26
#define  EXTI_INTEN_INTEN27                   ((uint32_t)0x08000000)        //!< Interrupt enable for line27
#define  EXTI_INTEN_INTEN28                   ((uint32_t)0x10000000)        //!< Interrupt enable for line28
#define  EXTI_INTEN_INTEN29                   ((uint32_t)0x20000000)        //!< Interrupt enable for line29
#define  EXTI_INTEN_INTEN30                   ((uint32_t)0x40000000)        //!< Interrupt enable for line30
#define  EXTI_INTEN_INTEN31                   ((uint32_t)0x80000000)        //!< Interrupt enable for line31

/**
  * @brief EXTI_EVTEN register Bit definition
  */
#define  EXTI_EVTEN_EVTEN0                    ((uint32_t)0x00000001)        //!< Event enable for line0
#define  EXTI_EVTEN_EVTEN1                    ((uint32_t)0x00000002)        //!< Event enable for line1
#define  EXTI_EVTEN_EVTEN2                    ((uint32_t)0x00000004)        //!< Event enable for line2
#define  EXTI_EVTEN_EVTEN3                    ((uint32_t)0x00000008)        //!< Event enable for line3
#define  EXTI_EVTEN_EVTEN4                    ((uint32_t)0x00000010)        //!< Event enable for line4
#define  EXTI_EVTEN_EVTEN5                    ((uint32_t)0x00000020)        //!< Event enable for line5
#define  EXTI_EVTEN_EVTEN6                    ((uint32_t)0x00000040)        //!< Event enable for line6
#define  EXTI_EVTEN_EVTEN7                    ((uint32_t)0x00000080)        //!< Event enable for line7
#define  EXTI_EVTEN_EVTEN8                    ((uint32_t)0x00000100)        //!< Event enable for line8
#define  EXTI_EVTEN_EVTEN9                    ((uint32_t)0x00000200)        //!< Event enable for line9
#define  EXTI_EVTEN_EVTEN10                   ((uint32_t)0x00000400)        //!< Event enable for line10
#define  EXTI_EVTEN_EVTEN11                   ((uint32_t)0x00000800)        //!< Event enable for line11
#define  EXTI_EVTEN_EVTEN12                   ((uint32_t)0x00001000)        //!< Event enable for line12
#define  EXTI_EVTEN_EVTEN13                   ((uint32_t)0x00002000)        //!< Event enable for line13
#define  EXTI_EVTEN_EVTEN14                   ((uint32_t)0x00004000)        //!< Event enable for line14
#define  EXTI_EVTEN_EVTEN15                   ((uint32_t)0x00008000)        //!< Event enable for line15
#define  EXTI_EVTEN_EVTEN16                   ((uint32_t)0x00010000)        //!< Event enable for line16
#define  EXTI_EVTEN_EVTEN17                   ((uint32_t)0x00020000)        //!< Event enable for line17
#define  EXTI_EVTEN_EVTEN18                   ((uint32_t)0x00040000)        //!< Event enable for line18
#define  EXTI_EVTEN_EVTEN19                   ((uint32_t)0x00080000)        //!< Event enable for line19
#define  EXTI_EVTEN_EVTEN20                   ((uint32_t)0x00100000)        //!< Event enable for line20
#define  EXTI_EVTEN_EVTEN21                   ((uint32_t)0x00200000)        //!< Event enable for line21
#define  EXTI_EVTEN_EVTEN22                   ((uint32_t)0x00400000)        //!< Event enable for line22
#define  EXTI_EVTEN_EVTEN23                   ((uint32_t)0x00800000)        //!< Event enable for line23
#define  EXTI_EVTEN_EVTEN24                   ((uint32_t)0x01000000)        //!< Event enable for line24
#define  EXTI_EVTEN_EVTEN25                   ((uint32_t)0x02000000)        //!< Event enable for line25
#define  EXTI_EVTEN_EVTEN26                   ((uint32_t)0x04000000)        //!< Event enable for line26
#define  EXTI_EVTEN_EVTEN27                   ((uint32_t)0x08000000)        //!< Event enable for line27
#define  EXTI_EVTEN_EVTEN28                   ((uint32_t)0x10000000)        //!< Event enable for line28
#define  EXTI_EVTEN_EVTEN29                   ((uint32_t)0x20000000)        //!< Event enable for line29
#define  EXTI_EVTEN_EVTEN30                   ((uint32_t)0x40000000)        //!< Event enable for line30
#define  EXTI_EVTEN_EVTEN31                   ((uint32_t)0x80000000)        //!< Event enable for line31

/**
  * @brief  EXTI_RTEN register Bit definition
  */
#define  EXTI_RTEN_RTEN0                      ((uint32_t)0x00000001)        //!< Rising edge trigger enable for line0
#define  EXTI_RTEN_RTEN1                      ((uint32_t)0x00000002)        //!< Rising edge trigger enable for line1
#define  EXTI_RTEN_RTEN2                      ((uint32_t)0x00000004)        //!< Rising edge trigger enable for line2
#define  EXTI_RTEN_RTEN3                      ((uint32_t)0x00000008)        //!< Rising edge trigger enable for line3
#define  EXTI_RTEN_RTEN4                      ((uint32_t)0x00000010)        //!< Rising edge trigger enable for line4
#define  EXTI_RTEN_RTEN5                      ((uint32_t)0x00000020)        //!< Rising edge trigger enable for line5
#define  EXTI_RTEN_RTEN6                      ((uint32_t)0x00000040)        //!< Rising edge trigger enable for line6
#define  EXTI_RTEN_RTEN7                      ((uint32_t)0x00000080)        //!< Rising edge trigger enable for line7
#define  EXTI_RTEN_RTEN8                      ((uint32_t)0x00000100)        //!< Rising edge trigger enable for line8
#define  EXTI_RTEN_RTEN9                      ((uint32_t)0x00000200)        //!< Rising edge trigger enable for line9
#define  EXTI_RTEN_RTEN10                     ((uint32_t)0x00000400)        //!< Rising edge trigger enable for line10
#define  EXTI_RTEN_RTEN11                     ((uint32_t)0x00000800)        //!< Rising edge trigger enable for line11
#define  EXTI_RTEN_RTEN12                     ((uint32_t)0x00001000)        //!< Rising edge trigger enable for line12
#define  EXTI_RTEN_RTEN13                     ((uint32_t)0x00002000)        //!< Rising edge trigger enable for line13
#define  EXTI_RTEN_RTEN14                     ((uint32_t)0x00004000)        //!< Rising edge trigger enable for line14
#define  EXTI_RTEN_RTEN15                     ((uint32_t)0x00008000)        //!< Rising edge trigger enable for line15
#define  EXTI_RTEN_RTEN16                     ((uint32_t)0x00010000)        //!< Rising edge trigger enable for line16
#define  EXTI_RTEN_RTEN17                     ((uint32_t)0x00020000)        //!< Rising edge trigger enable for line17
#define  EXTI_RTEN_RTEN19                     ((uint32_t)0x00080000)        //!< Rising edge trigger enable for line19
#define  EXTI_RTEN_RTEN20                     ((uint32_t)0x00100000)        //!< Rising edge trigger enable for line20
#define  EXTI_RTEN_RTEN21                     ((uint32_t)0x00200000)        //!< Rising edge trigger enable for line21
#define  EXTI_RTEN_RTEN22                     ((uint32_t)0x00400000)        //!< Rising edge trigger enable for line22
#define  EXTI_RTEN_RTEN31                     ((uint32_t)0x80000000)        //!< Rising edge trigger enable for line31

/**
  * @brief EXTI_FTEN register Bit definition
  */
#define  EXTI_FTEN_FTEN0                      ((uint32_t)0x00000001)        //!< Falling edge trigger enable for line0
#define  EXTI_FTEN_FTEN1                      ((uint32_t)0x00000002)        //!< Falling edge trigger enable for line1
#define  EXTI_FTEN_FTEN2                      ((uint32_t)0x00000004)        //!< Falling edge trigger enable for line2
#define  EXTI_FTEN_FTEN3                      ((uint32_t)0x00000008)        //!< Falling edge trigger enable for line3
#define  EXTI_FTEN_FTEN4                      ((uint32_t)0x00000010)        //!< Falling edge trigger enable for line4
#define  EXTI_FTEN_FTEN5                      ((uint32_t)0x00000020)        //!< Falling edge trigger enable for line5
#define  EXTI_FTEN_FTEN6                      ((uint32_t)0x00000040)        //!< Falling edge trigger enable for line6
#define  EXTI_FTEN_FTEN7                      ((uint32_t)0x00000080)        //!< Falling edge trigger enable for line7
#define  EXTI_FTEN_FTEN8                      ((uint32_t)0x00000100)        //!< Falling edge trigger enable for line8
#define  EXTI_FTEN_FTEN9                      ((uint32_t)0x00000200)        //!< Falling edge trigger enable for line9
#define  EXTI_FTEN_FTEN10                     ((uint32_t)0x00000400)        //!< Falling edge trigger enable for line10
#define  EXTI_FTEN_FTEN11                     ((uint32_t)0x00000800)        //!< Falling edge trigger enable for line11
#define  EXTI_FTEN_FTEN12                     ((uint32_t)0x00001000)        //!< Falling edge trigger enable for line12
#define  EXTI_FTEN_FTEN13                     ((uint32_t)0x00002000)        //!< Falling edge trigger enable for line13
#define  EXTI_FTEN_FTEN14                     ((uint32_t)0x00004000)        //!< Falling edge trigger enable for line14
#define  EXTI_FTEN_FTEN15                     ((uint32_t)0x00008000)        //!< Falling edge trigger enable for line15
#define  EXTI_FTEN_FTEN16                     ((uint32_t)0x00010000)        //!< Falling edge trigger enable for line16
#define  EXTI_FTEN_FTEN17                     ((uint32_t)0x00020000)        //!< Falling edge trigger enable for line17
#define  EXTI_FTEN_FTEN19                     ((uint32_t)0x00080000)        //!< Falling edge trigger enable for line19
#define  EXTI_FTEN_FTEN20                     ((uint32_t)0x00100000)        //!< Falling edge trigger enable for line20
#define  EXTI_FTEN_FTEN21                     ((uint32_t)0x00200000)        //!< Falling edge trigger enable for line21
#define  EXTI_FTEN_FTEN22                     ((uint32_t)0x00400000)        //!< Falling edge trigger enable for line22
#define  EXTI_FTEN_FTEN31                     ((uint32_t)0x80000000)        //!< Falling edge trigger enable for line31

/**
  * @brief EXTI_SWTIEN register Bit definition
  */
#define  EXTI_SWTIEN_SWTIEN0                  ((uint32_t)0x00000001)        //!< Software trigger interrupt/event for line0
#define  EXTI_SWTIEN_SWTIEN1                  ((uint32_t)0x00000002)        //!< Software trigger interrupt/event for line1
#define  EXTI_SWTIEN_SWTIEN2                  ((uint32_t)0x00000004)        //!< Software trigger interrupt/event for line2
#define  EXTI_SWTIEN_SWTIEN3                  ((uint32_t)0x00000008)        //!< Software trigger interrupt/event for line3
#define  EXTI_SWTIEN_SWTIEN4                  ((uint32_t)0x00000010)        //!< Software trigger interrupt/event for line4
#define  EXTI_SWTIEN_SWTIEN5                  ((uint32_t)0x00000020)        //!< Software trigger interrupt/event for line5
#define  EXTI_SWTIEN_SWTIEN6                  ((uint32_t)0x00000040)        //!< Software trigger interrupt/event for line6
#define  EXTI_SWTIEN_SWTIEN7                  ((uint32_t)0x00000080)        //!< Software trigger interrupt/event for line7
#define  EXTI_SWTIEN_SWTIEN8                  ((uint32_t)0x00000100)        //!< Software trigger interrupt/event for line8
#define  EXTI_SWTIEN_SWTIEN9                  ((uint32_t)0x00000200)        //!< Software trigger interrupt/event for line9
#define  EXTI_SWTIEN_SWTIEN10                 ((uint32_t)0x00000400)        //!< Software trigger interrupt/event for line10
#define  EXTI_SWTIEN_SWTIEN11                 ((uint32_t)0x00000800)        //!< Software trigger interrupt/event for line11
#define  EXTI_SWTIEN_SWTIEN12                 ((uint32_t)0x00001000)        //!< Software trigger interrupt/event for line12
#define  EXTI_SWTIEN_SWTIEN13                 ((uint32_t)0x00002000)        //!< Software trigger interrupt/event for line13
#define  EXTI_SWTIEN_SWTIEN14                 ((uint32_t)0x00004000)        //!< Software trigger interrupt/event for line14
#define  EXTI_SWTIEN_SWTIEN15                 ((uint32_t)0x00008000)        //!< Software trigger interrupt/event for line15
#define  EXTI_SWTIEN_SWTIEN16                 ((uint32_t)0x00010000)        //!< Software trigger interrupt/event for line16
#define  EXTI_SWTIEN_SWTIEN17                 ((uint32_t)0x00020000)        //!< Software trigger interrupt/event for line17
#define  EXTI_SWTIEN_SWTIEN19                 ((uint32_t)0x00080000)        //!< Software trigger interrupt/event for line19
#define  EXTI_SWTIEN_SWTIEN20                 ((uint32_t)0x00100000)        //!< Software trigger interrupt/event for line20
#define  EXTI_SWTIEN_SWTIEN21                 ((uint32_t)0x00200000)        //!< Software trigger interrupt/event for line21
#define  EXTI_SWTIEN_SWTIEN22                 ((uint32_t)0x00400000)        //!< Software trigger interrupt/event for line22
#define  EXTI_SWTIEN_SWTIEN31                 ((uint32_t)0x80000000)        //!< Software trigger interrupt/event for line31

/**
  * @brief EXTI_PDF register Bit definition
  */
#define  EXTI_PDF_PDF0                        ((uint32_t)0x00000001)        //!< Pending interrupt flag for line 0
#define  EXTI_PDF_PDF1                        ((uint32_t)0x00000002)        //!< Pending interrupt flag for line 1
#define  EXTI_PDF_PDF2                        ((uint32_t)0x00000004)        //!< Pending interrupt flag for line 2
#define  EXTI_PDF_PDF3                        ((uint32_t)0x00000008)        //!< Pending interrupt flag for line 3
#define  EXTI_PDF_PDF4                        ((uint32_t)0x00000010)        //!< Pending interrupt flag for line 4
#define  EXTI_PDF_PDF5                        ((uint32_t)0x00000020)        //!< Pending interrupt flag for line 5
#define  EXTI_PDF_PDF6                        ((uint32_t)0x00000040)        //!< Pending interrupt flag for line 6
#define  EXTI_PDF_PDF7                        ((uint32_t)0x00000080)        //!< Pending interrupt flag for line 7
#define  EXTI_PDF_PDF8                        ((uint32_t)0x00000100)        //!< Pending interrupt flag for line 8
#define  EXTI_PDF_PDF9                        ((uint32_t)0x00000200)        //!< Pending interrupt flag for line 9
#define  EXTI_PDF_PDF10                       ((uint32_t)0x00000400)        //!< Pending interrupt flag for line 10
#define  EXTI_PDF_PDF11                       ((uint32_t)0x00000800)        //!< Pending interrupt flag for line 11
#define  EXTI_PDF_PDF12                       ((uint32_t)0x00001000)        //!< Pending interrupt flag for line 12
#define  EXTI_PDF_PDF13                       ((uint32_t)0x00002000)        //!< Pending interrupt flag for line 13
#define  EXTI_PDF_PDF14                       ((uint32_t)0x00004000)        //!< Pending interrupt flag for line 14
#define  EXTI_PDF_PDF15                       ((uint32_t)0x00008000)        //!< Pending interrupt flag for line 15
#define  EXTI_PDF_PDF16                       ((uint32_t)0x00010000)        //!< Pending interrupt flag for line 16
#define  EXTI_PDF_PDF17                       ((uint32_t)0x00020000)        //!< Pending interrupt flag for line 17
#define  EXTI_PDF_PDF19                       ((uint32_t)0x00080000)        //!< Pending interrupt flag for line 19
#define  EXTI_PDF_PDF20                       ((uint32_t)0x00100000)        //!< Pending interrupt flag for line 20
#define  EXTI_PDF_PDF21                       ((uint32_t)0x00200000)        //!< Pending interrupt flag for line 21
#define  EXTI_PDF_PDF22                       ((uint32_t)0x00400000)        //!< Pending interrupt flag for line 22
#define  EXTI_PDF_PDF31                       ((uint32_t)0x80000000)        //!< Pending interrupt flag for line 31


/*---------------------------------------------------------------------------*/
/*   FMC(FLASH Memory Control) and Option Byes Registers                     */
/*---------------------------------------------------------------------------*/

/**
  * @brief FMC_WCR register Bit definition
  */
#define  FMC_WCR_WCNT                         ((uint32_t)0x00000001)        //!< NT bit (FMC wait conuter)
#define  FMC_WCR_WE                           ((uint32_t)0x00000010)        //!< MC wait enable
#define  FMC_WCR_WS                           ((uint32_t)0x00000020)        //!< MC wait status(read only)

/**
  * @brief FMC_CCODE register Bit definition
  */
#define  FMC_CCODE_CCODE                      ((uint32_t)0xFFFFFFFF)        //!< MC Control code

/**
  * @brief FMC_OBCCODE register Bit definition
  */
#define  FMC_OBCCODE_OBCCODE                  ((uint32_t)0xFFFFFFFF)        //!< FMC Option Byte Control code

/**
  * @brief FMC CCODE Bit definition
  */
#define FMC_CCODE_VALUE1                      ((uint32_t)0x45670123)        //!< Flash program erase key1
#define FMC_CCODE_VALUE2                      ((uint32_t)0xCDEF89AB)        //!< Flash program erase key2
#define FMC_OBCCODE_VALUE1                    ((uint32_t)0x45670123)        //!< Flash option key1
#define FMC_OBCCODE_VALUE2                    ((uint32_t)0xCDEF89AB)        //!< Flash option key2

/**
  * @brief FMC_STS register Bit definition
  */
#define  FMC_STS_BUSY                         ((uint32_t)0x00000001)        //!< Busy
#define  FMC_STS_PGERR                        ((uint32_t)0x00000004)        //!< Programming Error
#define  FMC_STS_WPERR                        ((uint32_t)0x00000010)        //!< Write Protection Error
#define  FMC_STS_ENDF                         ((uint32_t)0x00000020)        //!< End of operation

/**
  * @brief FMC_CTR register Bit definition
  */
#define  FMC_CTR_PG                           ((uint32_t)0x00000001)        //!< Main flash program
#define  FMC_CTR_PERS                         ((uint32_t)0x00000002)        //!< Flash page erase
#define  FMC_CTR_CHIPERS                      ((uint32_t)0x00000004)        //!< Mass flash CHIP ERASE
#define  FMC_CTR_OBPG                         ((uint32_t)0x00000010)        //!< Option byte program command
#define  FMC_CTR_OBERS                        ((uint32_t)0x00000020)        //!< Option bytes erase command
#define  FMC_CTR_START                        ((uint32_t)0x00000040)        //!< Start of erase
#define  FMC_CTR_LOCK                         ((uint32_t)0x00000080)        //!< Lock
#define  FMC_CTR_OBWEN                        ((uint32_t)0x00000200)        //!< Option byte erase/program enable
#define  FMC_CTR_ERRIE                        ((uint32_t)0x00000400)        //!< Error interrupt enable
#define  FMC_CTR_ENDIE                        ((uint32_t)0x00001000)        //!< End of operation interrupt enable
#define  FMC_CTR_OBUPDATE                     ((uint32_t)0x00002000)        //!< Update option byte

/**
  * @brief FMC_ERSADR register Bit definition
  */
#define  FMC_ERSADR_ERSADR                    ((uint32_t)0xFFFFFFFF)        // lash erase address

/**
  * @brief FMC_OBSTS register Bit definition
  */
#define  FMC_OBSTS_OBERR                      ((uint32_t)0x00000001)        //!< OBERR
#define  FMC_OBSTS_RPROT1                     ((uint32_t)0x00000002)        //!< Read protection Level bit 1
#define  FMC_OBSTS_RPROT2                     ((uint32_t)0x00000004)        //!< Read protection Level bit 2
#define  FMC_OBSTS_USER                       ((uint32_t)0x00003700)        //!< User Option Bytes
#define  FMC_OBSTS_FWDT_AO                    ((uint32_t)0x00000100)        //!< FWDT_ALWAYSON
#define  FMC_OBSTS_nRST_DSM                   ((uint32_t)0x00000200)        //!< nRST_DSM 
#define  FMC_OBSTS_nRST_PWD                   ((uint32_t)0x00000400)        //!< nRST_PWD
#define  FMC_OBSTS_nBOOT1                     ((uint32_t)0x00001000)        //!< nBOOT1
#define  FMC_OBSTS_VDDA_DET                   ((uint32_t)0x00002000)        //!< VDDA_DETECT
#define  FMC_OBSTS_RAM_PCHK                   ((uint32_t)0x00004000)        //!< RAM_PARITY_CHECK
#define  FMC_OBSTS_DATA0                      ((uint32_t)0x00FF0000)        //!< DATA0
#define  FMC_OBSTS_DATA1                      ((uint32_t)0xFF000000)        //!< DATA1

/**
  * @brief FMC_WPSTS register Bit definition
  */
#define  FMC_WPSTS_WPROT                      ((uint32_t)0xFFFFFFFF)        //!<  Write Protect

/**
  * @brief FMC_CFG register Bit definition
  */
#define  FMC_CFG_PGWORD              		  ((uint32_t)0x00000001)        //!<  Support word program

/**
  * @brief FMC_CFGU register Bit definition
  */
#define  FMC_CFGU_VBUF_EN              		  ((uint32_t)0x00000004)        //!<  0.8V VBUF enable/disable in deepsleep mode
#define  FMC_CFGU_FWUP_EN              		  ((uint32_t)0x00000001)        //!<  FLASH fast wake-up in deepsleep mode

/**
  * @brief OB_RPROT register Bit definition
  */
#define  OB_RPROT_RPROT                       ((uint32_t)0x000000FF)        //!<  Read protection option byte
#define  OB_RPROT_nRPROT                      ((uint32_t)0x0000FF00)        //!<  Read protection complemented option byte

/**
  * @brief OB_USER register Bit definition
  */
#define  OB_USER_USER                         ((uint32_t)0x00FF0000)        //!<  User option byte
#define  OB_USER_nUSER                        ((uint32_t)0xFF000000)        //!<  User complemented option byte

/**
  * @brief OB_WPROT0 register Bit definition
  */
#define  OB_WPROT0_WPROT0                     ((uint32_t)0x000000FF)        //!<  Flash memory write protection option bytes
#define  OB_WPROT0_nWPROT0                    ((uint32_t)0x0000FF00)        //!<  Flash memory write protection complemented option bytes

/**
  * @brief OB_WPROT1 register Bit definition
  */
#define  OB_WPROT1_WPROT1                     ((uint32_t)0x00FF0000)        //!<  Flash memory write protection option bytes
#define  OB_WPROT1_nWPROT1                    ((uint32_t)0xFF000000)        //!<  Flash memory write protection complemented option bytes

/**
  * @brief OB_WPROT2 register Bit definition
  */
#define  OB_WPROT2_WPROT2                     ((uint32_t)0x000000FF)        //!<  Flash memory write protection option bytes
#define  OB_WPROT2_nWPROT2                    ((uint32_t)0x0000FF00)        //!<  Flash memory write protection complemented option bytes

/**
  * @brief OB_WPROT3 register Bit definition
  */
#define  OB_WPROT3_WPROT3                     ((uint32_t)0x00FF0000)        //!<  Flash memory write protection option bytes
#define  OB_WPROT3_nWPROT3                    ((uint32_t)0xFF000000)        //!<  Flash memory write protection complemented option bytes

/*---------------------------------------------------------------------------*/
/*            General Purpose input/output (PIO)                             */
/*---------------------------------------------------------------------------*/

/**
  * @brief GPIO_PFR register Bit definition
  */
#define GPIO_PFR_FUNC0                        ((uint32_t)0x00000003)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC0_0                      ((uint32_t)0x00000001)  //!< bit
#define GPIO_PFR_FUNC0_1                      ((uint32_t)0x00000002)  //!< bit
#define GPIO_PFR_FUNC1                        ((uint32_t)0x0000000C)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC1_0                      ((uint32_t)0x00000004)  //!< bit
#define GPIO_PFR_FUNC1_1                      ((uint32_t)0x00000008)  //!< bit
#define GPIO_PFR_FUNC2                        ((uint32_t)0x00000030)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC2_0                      ((uint32_t)0x00000010)  //!< bit
#define GPIO_PFR_FUNC2_1                      ((uint32_t)0x00000020)  //!< bit
#define GPIO_PFR_FUNC3                        ((uint32_t)0x000000C0)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC3_0                      ((uint32_t)0x00000040)  //!< bit
#define GPIO_PFR_FUNC3_1                      ((uint32_t)0x00000080)  //!< bit
#define GPIO_PFR_FUNC4                        ((uint32_t)0x00000300)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC4_0                      ((uint32_t)0x00000100)  //!< bit
#define GPIO_PFR_FUNC4_1                      ((uint32_t)0x00000200)  //!< bit
#define GPIO_PFR_FUNC5                        ((uint32_t)0x00000C00)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC5_0                      ((uint32_t)0x00000400)  //!< bit
#define GPIO_PFR_FUNC5_1                      ((uint32_t)0x00000800)  //!< bit
#define GPIO_PFR_FUNC6                        ((uint32_t)0x00003000)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC6_0                      ((uint32_t)0x00001000)  //!< bit
#define GPIO_PFR_FUNC6_1                      ((uint32_t)0x00002000)  //!< bit
#define GPIO_PFR_FUNC7                        ((uint32_t)0x0000C000)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC7_0                      ((uint32_t)0x00004000)  //!< bit
#define GPIO_PFR_FUNC7_1                      ((uint32_t)0x00008000)  //!< bit
#define GPIO_PFR_FUNC8                        ((uint32_t)0x00030000)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC8_0                      ((uint32_t)0x00010000)  //!< bit
#define GPIO_PFR_FUNC8_1                      ((uint32_t)0x00020000)  //!< bit
#define GPIO_PFR_FUNC9                        ((uint32_t)0x000C0000)  //!< FUNC[1:0] Port function  bits
#define GPIO_PFR_FUNC9_0                      ((uint32_t)0x00040000)  //!< bit
#define GPIO_PFR_FUNC9_1                      ((uint32_t)0x00080000)  //!< bit
#define GPIO_PFR_FUNC10                       ((uint32_t)0x00300000)  //!< FUNC0[1:0] Port function  bits
#define GPIO_PFR_FUNC10_0                     ((uint32_t)0x00100000)  //!< bit
#define GPIO_PFR_FUNC10_1                     ((uint32_t)0x00200000)  //!< bit
#define GPIO_PFR_FUNC11                       ((uint32_t)0x00C00000)  //!< FUNC1[1:0] Port function  bits
#define GPIO_PFR_FUNC11_0                     ((uint32_t)0x00400000)  //!< bit
#define GPIO_PFR_FUNC11_1                     ((uint32_t)0x00800000)  //!< bit
#define GPIO_PFR_FUNC12                       ((uint32_t)0x03000000)  //!< FUNC2[1:0] Port function  bits
#define GPIO_PFR_FUNC12_0                     ((uint32_t)0x01000000)  //!< bit
#define GPIO_PFR_FUNC12_1                     ((uint32_t)0x02000000)  //!< bit
#define GPIO_PFR_FUNC13                       ((uint32_t)0x0C000000)  //!< FUNC3[1:0] Port function  bits
#define GPIO_PFR_FUNC13_0                     ((uint32_t)0x04000000)  //!< bit
#define GPIO_PFR_FUNC13_1                     ((uint32_t)0x08000000)  //!< bit
#define GPIO_PFR_FUNC14                       ((uint32_t)0x30000000)  //!< FUNC4[1:0] Port function  bits
#define GPIO_PFR_FUNC14_0                     ((uint32_t)0x10000000)  //!< bit
#define GPIO_PFR_FUNC14_1                     ((uint32_t)0x20000000)  //!< bit
#define GPIO_PFR_FUNC15                       ((uint32_t)0xC0000000)  //!< FUNC5[1:0] Port function  bits
#define GPIO_PFR_FUNC15_0                     ((uint32_t)0x40000000)  //!< bit
#define GPIO_PFR_FUNC15_1                     ((uint32_t)0x80000000)  //!< bit

/**
  * @brief GPIO_PODENR register Bit definition
  */
#define GPIO_PODENR_ODEN_0                    ((uint32_t)0x00000001)  //!< Portbit 0 output open-drain enable
#define GPIO_PODENR_ODEN_1                    ((uint32_t)0x00000002)  //!< Portbit 1 output open-drain enable
#define GPIO_PODENR_ODEN_2                    ((uint32_t)0x00000004)  //!< Portbit 2 output open-drain enable
#define GPIO_PODENR_ODEN_3                    ((uint32_t)0x00000008)  //!< Portbit 3 output open-drain enable
#define GPIO_PODENR_ODEN_4                    ((uint32_t)0x00000010)  //!< Portbit 4 output open-drain enable
#define GPIO_PODENR_ODEN_5                    ((uint32_t)0x00000020)  //!< Portbit 5 output open-drain enable
#define GPIO_PODENR_ODEN_6                    ((uint32_t)0x00000040)  //!< Portbit 6 output open-drain enable
#define GPIO_PODENR_ODEN_7                    ((uint32_t)0x00000080)  //!< Portbit 7 output open-drain enable
#define GPIO_PODENR_ODEN_8                    ((uint32_t)0x00000100)  //!< Portbit 8 output open-drain enable
#define GPIO_PODENR_ODEN_9                    ((uint32_t)0x00000200)  //!< Portbit 9 output open-drain enable
#define GPIO_PODENR_ODEN_10                   ((uint32_t)0x00000400)  //!< Portbit 10 output open-drain enable
#define GPIO_PODENR_ODEN_11                   ((uint32_t)0x00000800)  //!< Portbit 11 output open-drain enable
#define GPIO_PODENR_ODEN_12                   ((uint32_t)0x00001000)  //!< Portbit 12 output open-drain enable
#define GPIO_PODENR_ODEN_13                   ((uint32_t)0x00002000)  //!< Portbit 13 output open-drain enable
#define GPIO_PODENR_ODEN_14                   ((uint32_t)0x00004000)  //!< Portbit 14 output open-drain enable
#define GPIO_PODENR_ODEN_15                   ((uint32_t)0x00008000)  //!< Portbit 15 output open-drain enable

/**
  * @brief GPIO_POSR register Bit definition
  */
#define GPIO_POSR_OS0                         ((uint32_t)0x00000003)  //!< OS0[:0] (output speed)
#define GPIO_POSR_OS0_0                       ((uint32_t)0x00000001)  //!< bit
#define GPIO_POSR_OS0_1                       ((uint32_t)0x00000002)  //!< bit
#define GPIO_POSR_OS1                         ((uint32_t)0x0000000C)  //!<OS1[10] (output speed)
#define GPIO_POSR_OS1_0                       ((uint32_t)0x00000004)  //!< bit
#define GPIO_POSR_OS1_1                       ((uint32_t)0x00000008)  //!< bit
#define GPIO_POSR_OS2                         ((uint32_t)0x00000030)  //!< OS2[:0] (output speed)
#define GPIO_POSR_OS2_0                       ((uint32_t)0x00000010)  //!< bit
#define GPIO_POSR_OS2_1                       ((uint32_t)0x00000020)  //!< bit
#define GPIO_POSR_OS3                         ((uint32_t)0x000000C0)  //!< OS3[:0] (output speed)
#define GPIO_POSR_OS3_0                       ((uint32_t)0x00000040)  //!< bit
#define GPIO_POSR_OS3_1                       ((uint32_t)0x00000080)  //!< bit
#define GPIO_POSR_OS4                         ((uint32_t)0x00000300)  //!< OS4[:0] (output speed)
#define GPIO_POSR_OS4_0                       ((uint32_t)0x00000100)  //!< bit
#define GPIO_POSR_OS4_1                       ((uint32_t)0x00000200)  //!< bit
#define GPIO_POSR_OS5                         ((uint32_t)0x00000C00)  //!< OS5[:0] (output speed)
#define GPIO_POSR_OS5_0                       ((uint32_t)0x00000400)  //!< bit
#define GPIO_POSR_OS5_1                       ((uint32_t)0x00000800)  //!< bit
#define GPIO_POSR_OS6                         ((uint32_t)0x00003000)  //!< OS6[:0] (output speed)
#define GPIO_POSR_OS6_0                       ((uint32_t)0x00001000)  //!< bit
#define GPIO_POSR_OS6_1                       ((uint32_t)0x00002000)  //!< bit
#define GPIO_POSR_OS7                         ((uint32_t)0x0000C000)  //!< OS7[:0] (output speed)
#define GPIO_POSR_OS7_0                       ((uint32_t)0x00004000)  //!< bit
#define GPIO_POSR_OS7_1                       ((uint32_t)0x00008000)  //!< bit
#define GPIO_POSR_OS8                         ((uint32_t)0x00030000)  //!< OS8[:0] (output speed)
#define GPIO_POSR_OS8_0                       ((uint32_t)0x00010000)  //!< bit
#define GPIO_POSR_OS8_1                       ((uint32_t)0x00020000)  //!< bit
#define GPIO_POSR_OS9                         ((uint32_t)0x000C0000)  //!< OS9[:0] (output speed)
#define GPIO_POSR_OS9_0                       ((uint32_t)0x00040000)  //!< bit
#define GPIO_POSR_OS9_1                       ((uint32_t)0x00080000)  //!< bit
#define GPIO_POSR_OS10                        ((uint32_t)0x00300000)  //!< OS101:0] (output speed)
#define GPIO_POSR_OS10_0                      ((uint32_t)0x00100000)  //!< bit
#define GPIO_POSR_OS10_1                      ((uint32_t)0x00200000)  //!< bit
#define GPIO_POSR_OS11                        ((uint32_t)0x00C00000)  //!< OS111:0] (output speed)
#define GPIO_POSR_OS11_0                      ((uint32_t)0x00400000)  //!< bit
#define GPIO_POSR_OS11_1                      ((uint32_t)0x00800000)  //!< bit
#define GPIO_POSR_OS12                        ((uint32_t)0x03000000)  //!< OS121:0] (output speed)
#define GPIO_POSR_OS12_0                      ((uint32_t)0x01000000)  //!< bit
#define GPIO_POSR_OS12_1                      ((uint32_t)0x02000000)  //!< bit
#define GPIO_POSR_OS13                        ((uint32_t)0x0C000000)  //!< OS131:0] (output speed)
#define GPIO_POSR_OS13_0                      ((uint32_t)0x04000000)  //!< bit
#define GPIO_POSR_OS13_1                      ((uint32_t)0x08000000)  //!< bit
#define GPIO_POSR_OS14                        ((uint32_t)0x30000000)  //!< OS141:0] (output speed)
#define GPIO_POSR_OS14_0                      ((uint32_t)0x10000000)  //!< bit
#define GPIO_POSR_OS14_1                      ((uint32_t)0x20000000)  //!< bit
#define GPIO_POSR_OS15                        ((uint32_t)0xC0000000)  //!< OS151:0] (output speed)
#define GPIO_POSR_OS15_0                      ((uint32_t)0x40000000)  //!< bit
#define GPIO_POSR_OS15_1                      ((uint32_t)0x80000000)  //!< bit


/**
  * @brief GPIO_PUPDR register Bit definition
  */
#define GPIO_PUPDR_PUPD0                      ((uint32_t)0x00000003)  //!< PUPD0[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD0_0                    ((uint32_t)0x00000001)  //!< bit 0
#define GPIO_PUPDR_PUPD0_1                    ((uint32_t)0x00000002)  //!< bit 1
#define GPIO_PUPDR_PUPD1                      ((uint32_t)0x0000000C)  //!< PUPD1[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD1_0                    ((uint32_t)0x00000004)  //!< bit 0
#define GPIO_PUPDR_PUPD1_1                    ((uint32_t)0x00000008)  //!< bit 1
#define GPIO_PUPDR_PUPD2                      ((uint32_t)0x00000030)  //!< PUPD2[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD2_0                    ((uint32_t)0x00000010)  //!< bit 0
#define GPIO_PUPDR_PUPD2_1                    ((uint32_t)0x00000020)  //!< bit 1
#define GPIO_PUPDR_PUPD3                      ((uint32_t)0x000000C0)  //!< PUPD3[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD3_0                    ((uint32_t)0x00000040)  //!< bit 0
#define GPIO_PUPDR_PUPD3_1                    ((uint32_t)0x00000080)  //!< bit 1
#define GPIO_PUPDR_PUPD4                      ((uint32_t)0x00000300)  //!< PUPD4[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD4_0                    ((uint32_t)0x00000100)  //!< bit 0
#define GPIO_PUPDR_PUPD4_1                    ((uint32_t)0x00000200)  //!< bit 1
#define GPIO_PUPDR_PUPD5                      ((uint32_t)0x00000C00)  //!< PUPD5[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD5_0                    ((uint32_t)0x00000400)  //!< bit 0
#define GPIO_PUPDR_PUPD5_1                    ((uint32_t)0x00000800)  //!< bit 1
#define GPIO_PUPDR_PUPD6                      ((uint32_t)0x00003000)  //!< PUPD6[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD6_0                    ((uint32_t)0x00001000)  //!< bit 0
#define GPIO_PUPDR_PUPD6_1                    ((uint32_t)0x00002000)  //!< bit 1
#define GPIO_PUPDR_PUPD7                      ((uint32_t)0x0000C000)  //!< PUPD7[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD7_0                    ((uint32_t)0x00004000)  //!< bit 0
#define GPIO_PUPDR_PUPD7_1                    ((uint32_t)0x00008000)  //!< bit 1
#define GPIO_PUPDR_PUPD8                      ((uint32_t)0x00030000)  //!< PUPD8[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD8_0                    ((uint32_t)0x00010000)  //!< bit 0
#define GPIO_PUPDR_PUPD8_1                    ((uint32_t)0x00020000)  //!< bit 1
#define GPIO_PUPDR_PUPD9                      ((uint32_t)0x000C0000)  //!< PUPD9[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD9_0                    ((uint32_t)0x00040000)  //!< bit 0
#define GPIO_PUPDR_PUPD9_1                    ((uint32_t)0x00080000)  //!< bit 1
#define GPIO_PUPDR_PUPD10                     ((uint32_t)0x00300000)  //!< PUPD10[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD10_0                   ((uint32_t)0x00100000)  //!< bit 0
#define GPIO_PUPDR_PUPD10_1                   ((uint32_t)0x00200000)  //!< bit 1
#define GPIO_PUPDR_PUPD11                     ((uint32_t)0x00C00000)  //!< PUPD11[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD11_0                   ((uint32_t)0x00400000)  //!< bit 0
#define GPIO_PUPDR_PUPD11_1                   ((uint32_t)0x00800000)  //!< bit 1
#define GPIO_PUPDR_PUPD12                     ((uint32_t)0x03000000)  //!< PUPD12[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD12_0                   ((uint32_t)0x01000000)  //!< bit 0
#define GPIO_PUPDR_PUPD12_1                   ((uint32_t)0x02000000)  //!< bit 1
#define GPIO_PUPDR_PUPD13                     ((uint32_t)0x0C000000)  //!< PUPD13[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD13_0                   ((uint32_t)0x04000000)  //!< bit 0
#define GPIO_PUPDR_PUPD13_1                   ((uint32_t)0x08000000)  //!< bit 1
#define GPIO_PUPDR_PUPD14                     ((uint32_t)0x30000000)  //!< PUPD14[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD14_0                   ((uint32_t)0x10000000)  //!< bit 0
#define GPIO_PUPDR_PUPD14_1                   ((uint32_t)0x20000000)  //!< bit 1
#define GPIO_PUPDR_PUPD15                     ((uint32_t)0xC0000000)  //!< PUPD15[1:0]config (pull-up/pull-down )
#define GPIO_PUPDR_PUPD15_0                   ((uint32_t)0x40000000)  //!< bit 0
#define GPIO_PUPDR_PUPD15_1                   ((uint32_t)0x80000000)  //!< bit 1

/**
  * @brief GPIO_DI register Bit definition
  */
#define GPIO_DI_0                             ((uint32_t)0x00000001)  //!< Portx bit 0 data input
#define GPIO_DI_1                             ((uint32_t)0x00000002)  //!< Portx bit 1 data input
#define GPIO_DI_2                             ((uint32_t)0x00000004)  //!< Portx bit 2 data input
#define GPIO_DI_3                             ((uint32_t)0x00000008)  //!< Portx bit 3 data input
#define GPIO_DI_4                             ((uint32_t)0x00000010)  //!< Portx bit 4 data input
#define GPIO_DI_5                             ((uint32_t)0x00000020)  //!< Portx bit 5 data input
#define GPIO_DI_6                             ((uint32_t)0x00000040)  //!< Portx bit 6 data input
#define GPIO_DI_7                             ((uint32_t)0x00000080)  //!< Portx bit 7 data input
#define GPIO_DI_8                             ((uint32_t)0x00000100)  //!< Portx bit 8 data input
#define GPIO_DI_9                             ((uint32_t)0x00000200)  //!< Portx bit 9 data input
#define GPIO_DI_10                            ((uint32_t)0x00000400)  //!< Portx bit 10 data input
#define GPIO_DI_11                            ((uint32_t)0x00000800)  //!< Portx bit 11 data input
#define GPIO_DI_12                            ((uint32_t)0x00001000)  //!< Portx bit 12 data input
#define GPIO_DI_13                            ((uint32_t)0x00002000)  //!< Portx bit 13 data input
#define GPIO_DI_14                            ((uint32_t)0x00004000)  //!< Portx bit 14 data input
#define GPIO_DI_15                            ((uint32_t)0x00008000)  //!< Portx bit 15 data input

/**
  * @brief GPIO_DO register Bit definition
  */
#define GPIO_DO_0                             ((uint32_t)0x00000001)  //!< Portx bit 0 data output
#define GPIO_DO_1                             ((uint32_t)0x00000002)  //!< Portx bit 1 data output
#define GPIO_DO_2                             ((uint32_t)0x00000004)  //!< Portx bit 2 data output
#define GPIO_DO_3                             ((uint32_t)0x00000008)  //!< Portx bit 3 data output
#define GPIO_DO_4                             ((uint32_t)0x00000010)  //!< Portx bit 4 data output
#define GPIO_DO_5                             ((uint32_t)0x00000020)  //!< Portx bit 5 data output
#define GPIO_DO_6                             ((uint32_t)0x00000040)  //!< Portx bit 6 data output
#define GPIO_DO_7                             ((uint32_t)0x00000080)  //!< Portx bit 7 data output
#define GPIO_DO_8                             ((uint32_t)0x00000100)  //!< Portx bit 8 data output
#define GPIO_DO_9                             ((uint32_t)0x00000200)  //!< Portx bit 9 data output
#define GPIO_DO_10                            ((uint32_t)0x00000400)  //!< Portx bit 10 data output
#define GPIO_DO_11                            ((uint32_t)0x00000800)  //!< Portx bit 11 data output
#define GPIO_DO_12                            ((uint32_t)0x00001000)  //!< Portx bit 12 data output
#define GPIO_DO_13                            ((uint32_t)0x00002000)  //!< Portx bit 13 data output
#define GPIO_DO_14                            ((uint32_t)0x00004000)  //!< Portx bit 14 data output
#define GPIO_DO_15                            ((uint32_t)0x00008000)  //!< Portx bit 15 data output

/**
  * @brief GPIO_SCR register Bit definition
  */
#define GPIO_SCR_BS_0                         ((uint32_t)0x00000001)  //!< Portx bit 0 set
#define GPIO_SCR_BS_1                         ((uint32_t)0x00000002)  //!< Portx bit 1 set
#define GPIO_SCR_BS_2                         ((uint32_t)0x00000004)  //!< Portx bit 2 set
#define GPIO_SCR_BS_3                         ((uint32_t)0x00000008)  //!< Portx bit 3 set
#define GPIO_SCR_BS_4                         ((uint32_t)0x00000010)  //!< Portx bit 4 set
#define GPIO_SCR_BS_5                         ((uint32_t)0x00000020)  //!< Portx bit 5 set
#define GPIO_SCR_BS_6                         ((uint32_t)0x00000040)  //!< Portx bit 6 set
#define GPIO_SCR_BS_7                         ((uint32_t)0x00000080)  //!< Portx bit 7 set
#define GPIO_SCR_BS_8                         ((uint32_t)0x00000100)  //!< Portx bit 8 set
#define GPIO_SCR_BS_9                         ((uint32_t)0x00000200)  //!< Portx bit 9 set
#define GPIO_SCR_BS_10                        ((uint32_t)0x00000400)  //!< Portx bit 10 set
#define GPIO_SCR_BS_11                        ((uint32_t)0x00000800)  //!< Portx bit 11 set
#define GPIO_SCR_BS_12                        ((uint32_t)0x00001000)  //!< Portx bit 12 set
#define GPIO_SCR_BS_13                        ((uint32_t)0x00002000)  //!< Portx bit 13 set
#define GPIO_SCR_BS_14                        ((uint32_t)0x00004000)  //!< Portx bit 14 set
#define GPIO_SCR_BS_15                        ((uint32_t)0x00008000)  //!< Portx bit 15 set
#define GPIO_SCR_BC_0                         ((uint32_t)0x00010000)  //!< Portx bit 0 clear
#define GPIO_SCR_BC_1                         ((uint32_t)0x00020000)  //!< Portx bit 1 clear
#define GPIO_SCR_BC_2                         ((uint32_t)0x00040000)  //!< Portx bit 2 clear
#define GPIO_SCR_BC_3                         ((uint32_t)0x00080000)  //!< Portx bit 3 clear
#define GPIO_SCR_BC_4                         ((uint32_t)0x00100000)  //!< Portx bit 4 clear
#define GPIO_SCR_BC_5                         ((uint32_t)0x00200000)  //!< Portx bit 5 clear
#define GPIO_SCR_BC_6                         ((uint32_t)0x00400000)  //!< Portx bit 6 clear
#define GPIO_SCR_BC_7                         ((uint32_t)0x00800000)  //!< Portx bit 7 clear
#define GPIO_SCR_BC_8                         ((uint32_t)0x01000000)  //!< Portx bit 8 clear
#define GPIO_SCR_BC_9                         ((uint32_t)0x02000000)  //!< Portx bit 9 clear
#define GPIO_SCR_BC_10                        ((uint32_t)0x04000000)  //!< Portx bit 10 clear
#define GPIO_SCR_BC_11                        ((uint32_t)0x08000000)  //!< Portx bit 11 clear
#define GPIO_SCR_BC_12                        ((uint32_t)0x10000000)  //!< Portx bit 12 clear
#define GPIO_SCR_BC_13                        ((uint32_t)0x20000000)  //!< Portx bit 13 clear
#define GPIO_SCR_BC_14                        ((uint32_t)0x40000000)  //!< Portx bit 14 clear
#define GPIO_SCR_BC_15                        ((uint32_t)0x80000000)  //!< Portx bit 15 clear

/**
  * @brief GPIO_LOCK register Bit definition
  */
#define GPIO_LOCK_LOCK0                       ((uint32_t)0x00000001)  //!< Portx lock bit 0
#define GPIO_LOCK_LOCK1                       ((uint32_t)0x00000002)  //!< Portx lock bit 1
#define GPIO_LOCK_LOCK2                       ((uint32_t)0x00000004)  //!< Portx lock bit 2
#define GPIO_LOCK_LOCK3                       ((uint32_t)0x00000008)  //!< Portx lock bit 3
#define GPIO_LOCK_LOCK4                       ((uint32_t)0x00000010)  //!< Portx lock bit 4
#define GPIO_LOCK_LOCK5                       ((uint32_t)0x00000020)  //!< Portx lock bit 5
#define GPIO_LOCK_LOCK6                       ((uint32_t)0x00000040)  //!< Portx lock bit 6
#define GPIO_LOCK_LOCK7                       ((uint32_t)0x00000080)  //!< Portx lock bit 7
#define GPIO_LOCK_LOCK8                       ((uint32_t)0x00000100)  //!< Portx lock bit 8
#define GPIO_LOCK_LOCK9                       ((uint32_t)0x00000200)  //!< Portx lock bit 9
#define GPIO_LOCK_LOCK10                      ((uint32_t)0x00000400)  //!< Portx lock bit 10
#define GPIO_LOCK_LOCK11                      ((uint32_t)0x00000800)  //!< Portx lock bit 11
#define GPIO_LOCK_LOCK12                      ((uint32_t)0x00001000)  //!< Portx lock bit 12
#define GPIO_LOCK_LOCK13                      ((uint32_t)0x00002000)  //!< Portx lock bit 13
#define GPIO_LOCK_LOCK14                      ((uint32_t)0x00004000)  //!< Portx lock bit 14
#define GPIO_LOCK_LOCK15                      ((uint32_t)0x00008000)  //!< Portx lock bit 15
#define GPIO_LOCK_LOCKK                       ((uint32_t)0x00010000)  //!< Lock sequence key

/**
  * @brief GPIO_MFSELL register Bit definition
  */
#define GPIO_MFSELL_MFSELL0                   ((uint32_t)0x0000000F)  //!< Port xmulti-function selection 0
#define GPIO_MFSELL_MFSELL1                   ((uint32_t)0x000000F0)  //!< Port xmulti-function selection 1
#define GPIO_MFSELL_MFSELL2                   ((uint32_t)0x00000F00)  //!< Port xmulti-function selection 2
#define GPIO_MFSELL_MFSELL3                   ((uint32_t)0x0000F000)  //!< Port xmulti-function selection 3
#define GPIO_MFSELL_MFSELL4                   ((uint32_t)0x000F0000)  //!< Port xmulti-function selection 4
#define GPIO_MFSELL_MFSELL5                   ((uint32_t)0x00F00000)  //!< Port xmulti-function selection 5
#define GPIO_MFSELL_MFSELL6                   ((uint32_t)0x0F000000)  //!< Port xmulti-function selection 6
#define GPIO_MFSELL_MFSELL7                   ((uint32_t)0xF0000000)  //!< Port xmulti-function selection 7

/**
  * @brief GPIO_MFSELH register Bit definition
  */
#define GPIO_MFSELH_MFSELH0                   ((uint32_t)0x0000000F)  //!< Port xmulti-function selection 0
#define GPIO_MFSELH_MFSELH1                   ((uint32_t)0x000000F0)  //!< Port xmulti-function selection 1
#define GPIO_MFSELH_MFSELH2                   ((uint32_t)0x00000F00)  //!< Port xmulti-function selection 2
#define GPIO_MFSELH_MFSELH3                   ((uint32_t)0x0000F000)  //!< Port xmulti-function selection 3
#define GPIO_MFSELH_MFSELH4                   ((uint32_t)0x000F0000)  //!< Port xmulti-function selection 4
#define GPIO_MFSELH_MFSELH5                   ((uint32_t)0x00F00000)  //!< Port xmulti-function selection 5
#define GPIO_MFSELH_MFSELH6                   ((uint32_t)0x0F000000)  //!< Port xmulti-function selection 6
#define GPIO_MFSELH_MFSELH7                   ((uint32_t)0xF0000000)  //!< Port xmulti-function selection 7


/**
  * @brief GPIO_CLRR register Bit definition
  */
#define GPIO_CLRR_BCLR_0                      ((uint32_t)0x00000001)   //!< Port x bit clear 0
#define GPIO_CLRR_BCLR_1                      ((uint32_t)0x00000002)   //!< Port x bit clear 1
#define GPIO_CLRR_BCLR_2                      ((uint32_t)0x00000004)   //!< Port x bit clear 2
#define GPIO_CLRR_BCLR_3                      ((uint32_t)0x00000008)   //!< Port x bit clear 3
#define GPIO_CLRR_BCLR_4                      ((uint32_t)0x00000010)   //!< Port x bit clear 4
#define GPIO_CLRR_BCLR_5                      ((uint32_t)0x00000020)   //!< Port x bit clear 5
#define GPIO_CLRR_BCLR_6                      ((uint32_t)0x00000040)   //!< Port x bit clear 6
#define GPIO_CLRR_BCLR_7                      ((uint32_t)0x00000080)   //!< Port x bit clear 7
#define GPIO_CLRR_BCLR_8                      ((uint32_t)0x00000100)   //!< Port x bit clear 8
#define GPIO_CLRR_BCLR_9                      ((uint32_t)0x00000200)   //!< Port x bit clear 9
#define GPIO_CLRR_BCLR_10                     ((uint32_t)0x00000400)   //!< Port x bit clear 10
#define GPIO_CLRR_BCLR_11                     ((uint32_t)0x00000800)   //!< Port x bit clear 11
#define GPIO_CLRR_BCLR_12                     ((uint32_t)0x00001000)   //!< Port x bit clear 12
#define GPIO_CLRR_BCLR_13                     ((uint32_t)0x00002000)   //!< Port x bit clear 13
#define GPIO_CLRR_BCLR_14                     ((uint32_t)0x00004000)   //!< Port x bit clear 14
#define GPIO_CLRR_BCLR_15                     ((uint32_t)0x00008000)   //!< Port x bit clear 15

/*---------------------------------------------------------------------------*/
/*            Inter-integrated Circuit Interace (I2C)                        */
/*---------------------------------------------------------------------------*/

/**
  * @brief I2C_CTR1 register Bit definition
  */
#define  I2C_CTR1_I2CEN                       ((uint32_t)0x00000001)   //!< I2C enable
#define  I2C_CTR1_TXINTFIE                    ((uint32_t)0x00000002)   //!< Enable bit for TX interrupt
#define  I2C_CTR1_RXNEIE                      ((uint32_t)0x00000004)   //!< Enable bit for RX interrupt
#define  I2C_CTR1_ADRMIE                      ((uint32_t)0x00000008)   //!< Enable bit for Address match interrupt
#define  I2C_CTR1_NACKRIE                     ((uint32_t)0x00000010)   //!< Enable bit for Not acknowledge received interrupt
#define  I2C_CTR1_STOPDIE                     ((uint32_t)0x00000020)   //!< Enable bit for STOP detection interrupt
#define  I2C_CTR1_CMPIE                       ((uint32_t)0x00000040)   //!< Enable bit for Transfer complete interrupt
#define  I2C_CTR1_ERRDIE                      ((uint32_t)0x00000080)   //!< Enable bit for Error detection interrupt
#define  I2C_CTR1_DFCFG                       ((uint32_t)0x00000F00)   //!< Digital filter configuration
#define  I2C_CTR1_AFDIS                       ((uint32_t)0x00001000)   //!< Analog filter Disable
#define  I2C_CTR1_TXDMAREQEN                  ((uint32_t)0x00004000)   //!< Enable bit for Transmission DMA requests
#define  I2C_CTR1_RXDMAREQEN                  ((uint32_t)0x00008000)   //!< Enable bit for Reception DMA requests
#define  I2C_CTR1_SLVRC                       ((uint32_t)0x00010000)   //!< Slave response control
#define  I2C_CTR1_DISSTRETCH                  ((uint32_t)0x00020000)   //!< Disable clock stretching
#define  I2C_CTR1_WKUPEN                      ((uint32_t)0x00040000)   //!< Enable bit for Stop mode Wakeup
#define  I2C_CTR1_GCEN                        ((uint32_t)0x00080000)   //!< Enable bit for General call
#define  I2C_CTR1_SMBHAEN                     ((uint32_t)0x00100000)   //!< Enable bit for SMBus Host address
#define  I2C_CTR1_SMBDDAEN                    ((uint32_t)0x00200000)   //!< Enable bit for SMBus Device Default address
#define  I2C_CTR1_SMBAEN                      ((uint32_t)0x00400000)   //!< SMBus alter enable
#define  I2C_CTR1_PECMEN                      ((uint32_t)0x00800000)   //!< PEC mode enable

/**
  * @brief I2C_CTR2 register Bit definition
  */
#define  I2C_CTR2_MTADR                       ((uint32_t)0x000003FF)   //!< Master transfer address on I2C bus
#define  I2C_CTR2_TDIR                        ((uint32_t)0x00000400)   //!< Direction of Transfer (master mode)
#define  I2C_CTR2_ADRFMT                      ((uint32_t)0x00000800)   //!< Addressing format (master mode)
#define  I2C_CTR2_HEAD10AR                    ((uint32_t)0x00001000)   //!< 10-bit address header only read direction
#define  I2C_CTR2_STARTGEN                    ((uint32_t)0x00002000)   //!< Generate a Start on I2C bus
#define  I2C_CTR2_STOPGEN                     ((uint32_t)0x00004000)   //!< Generate a Stop on I2C bus(master mode)
#define  I2C_CTR2_NACKGEN                     ((uint32_t)0x00008000)   //!< Generate a NACK on I2C bus(slave mode)
#define  I2C_CTR2_BNUM                        ((uint32_t)0x00FF0000)   //!< Bytes number
#define  I2C_CTR2_RELOADM                     ((uint32_t)0x01000000)   //!< Bytes number reload mode
#define  I2C_CTR2_TENDSEL                     ((uint32_t)0x02000000)   //!< Tranfer end mode selection(master mode)
#define  I2C_CTR2_PECCTR                      ((uint32_t)0x04000000)   //!< PEC byte control

/**
  * @brief I2C_SADR1 register Bit definition
  */
#define  I2C_SADR1_SADR1                      ((uint32_t)0x000003FF)   //!< Slave Address 1
#define  I2C_SADR1_SADR1MODE                  ((uint32_t)0x00000400)   //!< Slave Address 1 10-bit mode
#define  I2C_SADR1_SADR1EN                    ((uint32_t)0x00008000)   //!< Slave Address 1 enable

/**
  * @brief I2C_SADR2 register Bit definition
  */
#define  I2C_SADR2_SADR2                      ((uint32_t)0x000000FE)   //!<Slave Address 2
#define  I2C_SADR2_SADR2MSK                   ((uint32_t)0x00000700)   //!<Slave Address 2 masks
#define  I2C_SADR2_SADR2EN                    ((uint32_t)0x00008000)   //!<Slave Address 2 enable

/**
  * @brief I2C_TMR register Bit definition
  */
#define  I2C_TMR_SCLLT                        ((uint32_t)0x000000FF)   //!< Master mode SCL low time
#define  I2C_TMR_SCLHT                        ((uint32_t)0x0000FF00)   //!< Master mode SCL high time
#define  I2C_TMR_SDAHT                        ((uint32_t)0x000F0000)   //!< SDA hold time
#define  I2C_TMR_SDAST                        ((uint32_t)0x00F00000)   //!< SDA setup time
#define  I2C_TMR_TPDIV                        ((uint32_t)0xF0000000)   //!< Timing pre-divider

/**
  * @brief I2C_OVRT register Bit definition
  */
#define  I2C_OVRT_TIMA                        ((uint32_t)0x00000FFF)   //!< Bus overtime A
#define  I2C_OVRT_IDLEDEN                     ((uint32_t)0x00001000)   //!< Idle clock overtime detection
#define  I2C_OVRT_TIMAEN                      ((uint32_t)0x00008000)   //!< timer A enable
#define  I2C_OVRT_TIMB                        ((uint32_t)0x0FFF0000)   //!< Bus overtime B
#define  I2C_OVRT_TIMBEN                      ((uint32_t)0x80000000)   //!< timer B enable

/**
  * @brief I2C_STS register Bit definition
  */
#define  I2C_STS_TXEF                         ((uint32_t)0x00000001)   //!< Data register empty flag in transmitting mode
#define  I2C_STS_TXINTF                       ((uint32_t)0x00000002)   //!< Transmit interrupt flag
#define  I2C_STS_RXNEF                        ((uint32_t)0x00000004)   //!< Data register not empty in receiving mode
#define  I2C_STS_ADRF                         ((uint32_t)0x00000008)   //!< Slave mode Address matched flag
#define  I2C_STS_NACKF                        ((uint32_t)0x00000010)   //!< NACK received flag
#define  I2C_STS_STOPF                        ((uint32_t)0x00000020)   //!< Stop detection flag
#define  I2C_STS_CMPF                         ((uint32_t)0x00000040)   //!< Master mode Transfer Complete flag
#define  I2C_STS_RLDF                         ((uint32_t)0x00000080)   //!< Reload flag
#define  I2C_STS_BUSERRF                      ((uint32_t)0x00000100)   //!< Bus error flag
#define  I2C_STS_ARBLOF                       ((uint32_t)0x00000200)   //!< Arbitration lost flag
#define  I2C_STS_OVRF                         ((uint32_t)0x00000400)   //!< Overtime or tLOW detection flag
#define  I2C_STS_PECERRF                      ((uint32_t)0x00000800)   //!< PEC Error flag
#define  I2C_STS_TIMEOUT                      ((uint32_t)0x00001000)   //!< Overtime or tLOW detection flag
#define  I2C_STS_SMBAF                        ((uint32_t)0x00002000)   //!< SMBus alert flag
#define  I2C_STS_BUSYF                        ((uint32_t)0x00008000)   //!< Bus busy flag
#define  I2C_STS_DIRF                         ((uint32_t)0x00010000)   //!< Slave Transfer direction flag
#define  I2C_STS_MSLVA                        ((uint32_t)0x00FE0000)   //!< Matched Slave Address

/**
  * @brief I2C_STSC register Bit definition
  */
#define  I2C_STSC_ADRFC                       ((uint32_t)0x00000008)   //!< Slave mode Address matched flag clear
#define  I2C_STSC_NACKFC                      ((uint32_t)0x00000010)   //!< NACK received flag clear
#define  I2C_STSC_STOPFC                      ((uint32_t)0x00000020)   //!< Stop detection flag clear
#define  I2C_STSC_BUSERRFC                    ((uint32_t)0x00000100)   //!< Bus error flag clear
#define  I2C_STSC_ARLOFC                      ((uint32_t)0x00000200)   //!< Arbittration Lost flag clear
#define  I2C_STSC_OVRFC                       ((uint32_t)0x00000400)   //!< Slave Overflow/Underflow flag clear
#define  I2C_STSC_PECERRFC                    ((uint32_t)0x00000800)   //!< PEC Error flag clear
#define  I2C_STSC_OVRTFC                      ((uint32_t)0x00001000)   //!< Overtime detection flag clear
#define  I2C_STSC_SMBAFC                      ((uint32_t)0x00002000)   //!< SMBus alert flag clear

/**
  * @brief I2C_PECCODE register Bit definition
  */
#define  I2C_PECCODE_PECCODE                  ((uint32_t)0x000000FF)   //!< Received PEC code

/**
  * @brief I2C_RXBUF register Bit definition
  */
#define  I2C_RXBUF_RXBUF                      ((uint32_t)0x000000FF)   //!< Receive buffer register

/**
  * @brief I2C_TXBUF register Bit definition
  */
#define  I2C_TXBUF_TXBUF                      ((uint32_t)0x000000FF)   //!< Transmit buffer register



/*--------------------------------------------------------------------------*/
/*             FWDT(Free Watchdog Timer)                                    */
/*--------------------------------------------------------------------------*/

/**
  * @brief FWDT_CCODE register Bit definition
  */
#define  FWDT_CCODE_CCODE                      ((uint16_t)0xFFFF)     //!< Control code (write only, read 0000h)

/**
  * @brief FWDT_PDIV register Bit definition
  */
#define  FWDT_PDIV_PDIV                        ((uint8_t)0x07)        //!< PDIV[2:0] (Pre-divider)
#define  FWDT_PDIV_PDIV_0                      ((uint8_t)0x01)        //!< Bit 0
#define  FWDT_PDIV_PDIV_1                      ((uint8_t)0x02)        //!< Bit 1
#define  FWDT_PDIV_PDIV_2                      ((uint8_t)0x04)        //!< Bit 2

/**
  * @brief FWDT_UVAL register Bit definition
  */
#define  FWDT_UVAL_RL                          ((uint16_t)0x0FFF)     //!< Watchdog counter update value

/**
  * @brief FWDT_STS register Bit definition
  */
#define  FWDT_STS_DRF                          ((uint8_t)0x01)        //!< FWDT divider refresh flag
#define  FWDT_STS_UVRF                         ((uint8_t)0x02)        //!< FWDT update value refresh flag
#define  FWDT_STS_WRF                          ((uint8_t)0x04)        //!< FWDT divider refresh flag

/**
  * @brief FWDT_WINVAL register Bit definition
  */
#define  FWDT_WINVAL_WIN                       ((uint16_t)0x0FFF)     //!< IWDT window value

/*--------------------------------------------------------------------------*/
/*        Power management unit (PMU)                                       */
/*--------------------------------------------------------------------------*/

/**
  * @brief PMU_CTR register Bit definition
  */
#define  PMU_CTR_LDOLM                         ((uint16_t)0x0001)     //!< LDO ow power Control
#define  PMU_CTR_DSMODE                        ((uint16_t)0x0002)     //!< Deepsleep Mode or Power down selection
#define  PMU_CTR_CLRWUPF                       ((uint16_t)0x0004)     //!< Clear wakup flag
#define  PMU_CTR_CLRPWDF                       ((uint16_t)0x0008)     //!< Clear power down flag
#define  PMU_CTR_LVDEN                         ((uint16_t)0x0010)     //!< low vlotage detector Enable

#define  PMU_CTR_LVDSEL                        ((uint16_t)0x00E0)     //!< LVDSEL[2:0] bits (low vlotage detector threshold Selection)
#define  PMU_CTR_LVDSEL_0                      ((uint16_t)0x0020)     //!< Bit 0
#define  PMU_CTR_LVDSEL_1                      ((uint16_t)0x0040)     //!< Bit 1
#define  PMU_CTR_LVDSEL_2                      ((uint16_t)0x0080)     //!< Bit 2

/* LVDSEL level configuration */
#define  PMU_CTR_LVDSEL_LEVEL0                 ((uint16_t)0x0000)     //!< LVDSEL level 0
#define  PMU_CTR_LVDSEL_LEVEL1                 ((uint16_t)0x0020)     //!< LVDSEL level 1
#define  PMU_CTR_LVDSEL_LEVEL2                 ((uint16_t)0x0040)     //!< LVDSEL level 2
#define  PMU_CTR_LVDSEL_LEVEL3                 ((uint16_t)0x0060)     //!< LVDSEL level 3
#define  PMU_CTR_LVDSEL_LEVEL4                 ((uint16_t)0x0080)     //!< LVDSEL level 4
#define  PMU_CTR_LVDSEL_LEVEL5                 ((uint16_t)0x00A0)     //!< LVDSEL level 5
#define  PMU_CTR_LVDSEL_LEVEL6                 ((uint16_t)0x00C0)     //!< LVDSEL level 6
#define  PMU_CTR_LVDSEL_LEVEL7                 ((uint16_t)0x00E0)     //!< LVDSEL level 7
#define  PMU_CTR_VBTWEN                        ((uint16_t)0x0100)     //!< VBAT domain write enable

/**
  * @brief PMU_CS register Bit definition
  */
#define  PMU_CS_WUPF                           ((uint16_t)0x0001)     //!< Wakeup Flag
#define  PMU_CS_PWDF                           ((uint16_t)0x0002)     //!< power down flag
#define  PMU_CS_LVDO                           ((uint16_t)0x0004)     //!< low vlotage detector Output

#define  PMU_CS_WUPEN1                         ((uint16_t)0x0100)     //!< Enable WKUP pin 1
#define  PMU_CS_WUPEN2                         ((uint16_t)0x0200)     //!< Enable WKUP pin 2
#define  PMU_CS_WUPEN3                         ((uint16_t)0x0400)     //!< Enable WKUP pin 3
#define  PMU_CS_WUPEN4                         ((uint16_t)0x0800)     //!< Enable WKUP pin 4
#define  PMU_CS_WUPEN5                         ((uint16_t)0x1000)     //!< Enable WKUP pin 5
#define  PMU_CS_WUPEN6                         ((uint16_t)0x2000)     //!< Enable WKUP pin 6
#define  PMU_CS_WUPEN7                         ((uint16_t)0x4000)     //!< Enable WKUP pin 7
#define  PMU_CS_WUPEN8                         ((uint16_t)0x8000)     //!< Enable WKUP pin 8

/*---------------------------------------------------------------------------*/
/*               Reset and Clock Control                                     */
/*---------------------------------------------------------------------------*/

/**
  * @brief RCU_CTR register Bit definition
  */
#define  RCU_CTR_HRCEN                         ((uint32_t)0x00000001) //!< HRC Enable
#define  RCU_CTR_HRCSTAB                       ((uint32_t)0x00000002) //!< HRC Stabilization flag
#define  RCU_CTR_HRCTRIM                       ((uint32_t)0x000000F8) //!< HRC Triming
#define  RCU_CTR_HRCCALIB                      ((uint32_t)0x0000FF00) //!< HRC Internal 8MHz RC calibration
#define  RCU_CTR_HXTEN                         ((uint32_t)0x00010000) //!< HXT Enable
#define  RCU_CTR_HXTSTAB                       ((uint32_t)0x00020000) //!< HXT Stabilization flag
#define  RCU_CTR_HXTBPS                        ((uint32_t)0x00040000) //!< HXT Bypass Enable
#define  RCU_CTR_HXTME                         ((uint32_t)0x00080000) //!< HXT Monitor Enable
#define  RCU_CTR_HXTDRV                        ((uint32_t)0x00600000) //!< HXT Drive capability Selection
#define  RCU_CTR_HXTDRV_0                      ((uint32_t)0x00200000) //!< Bit 0
#define  RCU_CTR_HXTDRV_1                      ((uint32_t)0x00400000) //!< Bit 1
#define  RCU_CTR_PLLEN                         ((uint32_t)0x01000000) //!< PLL Enable
#define  RCU_CTR_PLLSTAB                       ((uint32_t)0x02000000) //!< PLL Stabilization flag

/**
  * @brief RCU_CFG register Bit definition
  */
#define  RCU_CFG_SYSSW                         ((uint32_t)0x00000003) //!< SYSSW[1:0] bits System clock switch Control
#define  RCU_CFG_SYSSW_0                       ((uint32_t)0x00000001) //!< Bit 0
#define  RCU_CFG_SYSSW_1                       ((uint32_t)0x00000002) //!< Bit 1
/* SYSSW configuration */
#define  RCU_CFG_SYSSW_HRC                     ((uint32_t)0x00000000) //!< HRC selected as system clock
#define  RCU_CFG_SYSSW_HXT                     ((uint32_t)0x00000001) //!< HXT selected as system clock
#define  RCU_CFG_SYSSW_PLL                     ((uint32_t)0x00000002) //!< PLL selected as system clock

#define  RCU_CFG_SYSSS                         ((uint32_t)0x0000000C) //!< SYSSS[1:0] bits (System clock switch status)
#define  RCU_CFG_SYSSS_0                       ((uint32_t)0x00000004) //!< Bit 0
#define  RCU_CFG_SYSSS_1                       ((uint32_t)0x00000008) //!< Bit 1
/* SYSSS configuration */
#define  RCU_CFG_SYSSS_HRC                     ((uint32_t)0x00000000) //!< HRC oscillator used as system clock
#define  RCU_CFG_SYSSS_HXT                     ((uint32_t)0x00000004) //!< HXT oscillator used as system clock
#define  RCU_CFG_SYSSS_PLL                     ((uint32_t)0x00000008) //!< PLL used as system clock

#define  RCU_CFG_HCLKPDIV                      ((uint32_t)0x000000F0) //!< HCLKPDIV[3:0] bits (HCLK Pre-divider)
#define  RCU_CFG_HCLKPDIV_0                    ((uint32_t)0x00000010) //!< Bit 0
#define  RCU_CFG_HCLKPDIV_1                    ((uint32_t)0x00000020) //!< Bit 1
#define  RCU_CFG_HCLKPDIV_2                    ((uint32_t)0x00000040) //!< Bit 2
#define  RCU_CFG_HCLKPDIV_3                    ((uint32_t)0x00000080) //!< Bit 3
#define  RCU_CFG_PCLKPDIV                      ((uint32_t)0x00000700) //!< PCLKPDIV[2:0] bits (PCLK Pre-divider)
/* HCLKPDIV configuration */
#define  RCU_CFG_HCLKPDIV_DIV1                 ((uint32_t)0x00000000) //!< not divided
#define  RCU_CFG_HCLKPDIV_DIV2                 ((uint32_t)0x00000080) //!< divided by 2
#define  RCU_CFG_HCLKPDIV_DIV4                 ((uint32_t)0x00000090) //!< divided by 4
#define  RCU_CFG_HCLKPDIV_DIV8                 ((uint32_t)0x000000A0) //!< divided by 8
#define  RCU_CFG_HCLKPDIV_DIV16                ((uint32_t)0x000000B0) //!< divided by 16
#define  RCU_CFG_HCLKPDIV_DIV64                ((uint32_t)0x000000C0) //!< divided by 64
#define  RCU_CFG_HCLKPDIV_DIV128               ((uint32_t)0x000000D0) //!< divided by 128
#define  RCU_CFG_HCLKPDIV_DIV256               ((uint32_t)0x000000E0) //!< divided by 256
#define  RCU_CFG_HCLKPDIV_DIV512               ((uint32_t)0x000000F0) //!< divided by 512

#define  RCU_CFG_PCLKPDIV_0                    ((uint32_t)0x00000100) //!< Bit 0
#define  RCU_CFG_PCLKPDIV_1                    ((uint32_t)0x00000200) //!< Bit 1
#define  RCU_CFG_PCLKPDIV_2                    ((uint32_t)0x00000400) //!< Bit 2
/* PCLKPDIV configuration */
#define  RCU_CFG_PCLKPDIV_DIV1                 ((uint32_t)0x00000000) //!< HCLK not divided
#define  RCU_CFG_PCLKPDIV_DIV2                 ((uint32_t)0x00000400) //!< HCLK divided by 2
#define  RCU_CFG_PCLKPDIV_DIV4                 ((uint32_t)0x00000500) //!< HCLK divided by 4
#define  RCU_CFG_PCLKPDIV_DIV8                 ((uint32_t)0x00000600) //!< HCLK divided by 8
#define  RCU_CFG_PCLKPDIV_DIV16                ((uint32_t)0x00000700) //!< HCLK divided by 16

#define  RCU_CFG_ADCPDIV                       ((uint32_t)0x00004000) //!< ADC Clock Pre-divider

#define  RCU_CFG_PLLSEL                        ((uint32_t)0x00018000) //!< PLL source Selction
#define  RCU_CFG_PLLSEL_0                      ((uint32_t)0x00008000) //!< Bit 0
#define  RCU_CFG_PLLSEL_1                      ((uint32_t)0x00010000) //!< Bit 1

#define  RCU_CFG_PLLSEL_HRC_DIV2               ((uint32_t)0x00000000) //!< PLL source HRC
#define  RCU_CFG_PLLSEL_HXT_PREDIV             ((uint32_t)0x00010000) //!< PLL source HXT/PLLPDIV

#define  RCU_CFG_PLLHXTPDIV                    ((uint32_t)0x00020000) //!<PLL source HXT pre-divdier
#define  RCU_CFG_PLLMUF                        ((uint32_t)0x003C0000) //!< PLLMUF[3:0] bits (PLL multiplication factor) */
#define  RCU_CFG_PLLMUF_0                      ((uint32_t)0x00040000) //!< Bit 0
#define  RCU_CFG_PLLMUF_1                      ((uint32_t)0x00080000) //!< Bit 1
#define  RCU_CFG_PLLMUF_2                      ((uint32_t)0x00100000) //!< Bit 2
#define  RCU_CFG_PLLMUF_3                      ((uint32_t)0x00200000) //!< Bit 3

#define  RCU_CFG_PLLMUF2                       ((uint32_t)0x00000000) //!< PLL input clock*2
#define  RCU_CFG_PLLMUF3                       ((uint32_t)0x00040000) //!< PLL input clock*3
#define  RCU_CFG_PLLMUF4                       ((uint32_t)0x00080000) //!< PLL input clock*4
#define  RCU_CFG_PLLMUF5                       ((uint32_t)0x000C0000) //!< PLL input clock*5
#define  RCU_CFG_PLLMUF6                       ((uint32_t)0x00100000) //!< PLL input clock*6
#define  RCU_CFG_PLLMUF7                       ((uint32_t)0x00140000) //!< PLL input clock*7
#define  RCU_CFG_PLLMUF8                       ((uint32_t)0x00180000) //!< PLL input clock*8
#define  RCU_CFG_PLLMUF9                       ((uint32_t)0x001C0000) //!< PLL input clock*9
#define  RCU_CFG_PLLMUF10                      ((uint32_t)0x00200000) //!< PLL input clock10
#define  RCU_CFG_PLLMUF11                      ((uint32_t)0x00240000) //!< PLL input clock*11
#define  RCU_CFG_PLLMUF12                      ((uint32_t)0x00280000) //!< PLL input clock*12
#define  RCU_CFG_PLLMUF13                      ((uint32_t)0x002C0000) //!< PLL input clock*13
#define  RCU_CFG_PLLMUF14                      ((uint32_t)0x00300000) //!< PLL input clock*14
#define  RCU_CFG_PLLMUF15                      ((uint32_t)0x00340000) //!< PLL input clock*15
#define  RCU_CFG_PLLMUF16                      ((uint32_t)0x00380000) //!< PLL input clock*16

#define  RCU_CFG_CKOSEL                        ((uint32_t)0x0F000000) //!< CLKOUT[2:0] bits CLKOUT Source Selection
#define  RCU_CFG_CKOSEL_0                      ((uint32_t)0x01000000) //!< Bit 0
#define  RCU_CFG_CKOSEL_1                      ((uint32_t)0x02000000) //!< Bit 1
#define  RCU_CFG_CKOSEL_2                      ((uint32_t)0x04000000) //!< Bit 2
#define  RCU_CFG_CKOSEL_3                      ((uint32_t)0x08000000) //!< Bit 3
#define  RCU_CFG_CKOPDIV                       ((uint32_t)0x70000000) //!< CLKOUT prescaler
#define  RCU_CFG_CKOPDIV_0                     ((uint32_t)0x10000000) //!< Bit 0
#define  RCU_CFG_CKOPDIV_1                     ((uint32_t)0x20000000) //!< Bit 1
#define  RCU_CFG_CKOPDIV_2                     ((uint32_t)0x40000000) //!< Bit 2
#define  RCU_CFG_CKOPLLND                      ((uint32_t)0x80000000) //!< PLL clock not divided for CLKOUT

/**
  * @brief RCU_INTR register Bit definition
  */
#define  RCU_INTR_LRCSTABIF                    ((uint32_t)0x00000001) //!< LRC stabilization Interrupt Flag
#define  RCU_INTR_LXTSTABIF                    ((uint32_t)0x00000002) //!< LXT stabilization Interrupt Flag
#define  RCU_INTR_HRCSTABIF                    ((uint32_t)0x00000004) //!< HRC stabilization Interrupt Flag
#define  RCU_INTR_HXTSTABIF                    ((uint32_t)0x00000008) //!< HXT stabilization Interrupt Flag
#define  RCU_INTR_PLLSTABIF                    ((uint32_t)0x00000010) //!< PLL stabilization Interrupt Flag
#define  RCU_INTR_HRC14STABIF                  ((uint32_t)0x00000020) //!< HRC14 stabilization Interrupt Flag
#define  RCU_INTR_CKFAILIF                     ((uint32_t)0x00000080) //!< HXT Clock Fail Interrupt Flag

#define  RCU_INTR_LRCSTABIE                    ((uint32_t)0x00000100) //!< LRC stabilization Interrupt Enable
#define  RCU_INTR_LXTSTABIE                    ((uint32_t)0x00000200) //!< LXT stabilization Interrupt Enable
#define  RCU_INTR_HRCSTABIE                    ((uint32_t)0x00000400) //!< HRC stabilization Interrupt Enable
#define  RCU_INTR_HXTSTABIE                    ((uint32_t)0x00000800) //!< HXT stabilization Interrupt Enable
#define  RCU_INTR_PLLSTABIE                    ((uint32_t)0x00001000) //!< PLL stabilization Interrupt Enable
#define  RCU_INTR_HRC14STABIE                  ((uint32_t)0x00002000) //!< HRC14 stabilization Interrupt Enable

#define  RCU_INTR_LRCSTABIC                    ((uint32_t)0x00010000) //!< LRC stabilization Interrupt Clear
#define  RCU_INTR_LXTSTABIC                    ((uint32_t)0x00020000) //!< LXT stabilization Interrupt Clear
#define  RCU_INTR_HRCSTABIC                    ((uint32_t)0x00040000) //!< HRC stabilization Interrupt Clear
#define  RCU_INTR_HXTSTABIC                    ((uint32_t)0x00080000) //!< HXT stabilization Interrupt Clear
#define  RCU_INTR_PLLSTABIC                    ((uint32_t)0x00100000) //!< PLL stabilization Interrupt Clear
#define  RCU_INTR_HRC14STABIC                  ((uint32_t)0x00200000) //!< HRC14 stabilization Interrupt Clear
#define  RCU_INTR_CKFAILIC                     ((uint32_t)0x00800000) //!< HXT Clock Fail Interrupt Clear

/**
  * @brief RCU_APB2RST register Bit definition
  */
#define  RCU_APB2RST_SYSCFGRST                 ((uint32_t)0x00000001) //!< SYSCFG reset
#define  RCU_APB2RST_USART6RST                 ((uint32_t)0x00000020) //!< USART6 clock reset
#define  RCU_APB2RST_USART7RST                 ((uint32_t)0x00000040) //!< USART7 clock reset
#define  RCU_APB2RST_USART8RST                 ((uint32_t)0x00000080) //!< USART8 clock reset
#define  RCU_APB2RST_ADCRST                    ((uint32_t)0x00000200) //!< ADC clock reset
#define  RCU_APB2RST_TIM1RST                   ((uint32_t)0x00000800) //!< TIM1 clock reset
#define  RCU_APB2RST_SPI1RST                   ((uint32_t)0x00001000) //!< SPI1 clock reset
#define  RCU_APB2RST_USART1RST                 ((uint32_t)0x00004000) //!< USART1 clock reset
#define  RCU_APB2RST_TIM15RST                  ((uint32_t)0x00010000) //!< TIM15 clock reset
#define  RCU_APB2RST_TIM16RST                  ((uint32_t)0x00020000) //!< TIM16 clock reset
#define  RCU_APB2RST_TIM17RST                  ((uint32_t)0x00040000) //!< TIM17 clock reset
#define  RCU_APB2RST_DBGRST                    ((uint32_t)0x00400000) //!< DBGMCU clock reset

/**
  * @brief RCU_APB1RST register Bit definition
  */
#define  RCU_APB1RST_TIM2RST                   ((uint32_t)0x00000001) //!< Timer 2 clock reset
#define  RCU_APB1RST_TIM3RST                   ((uint32_t)0x00000002) //!< Timer 3 clock reset
#define  RCU_APB1RST_TIM6RST                   ((uint32_t)0x00000010) //!< Timer 6 clock reset
#define  RCU_APB1RST_TIM14RST                  ((uint32_t)0x00000100) //!< Timer 14 clock reset
#define  RCU_APB1RST_WWDTRST                   ((uint32_t)0x00000800) //!< Window Watchdog clock reset
#define  RCU_APB1RST_SPI2RST                   ((uint32_t)0x00004000) //!< SPI2 clock reset
#define  RCU_APB1RST_USART2RST                 ((uint32_t)0x00020000) //!< USART 2 clock reset
#define  RCU_APB1RST_I2C1RST                   ((uint32_t)0x00200000) //!< I2C 1 clock reset
#define  RCU_APB1RST_I2C2RST                   ((uint32_t)0x00400000) //!< I2C 2 clock reset
#define  RCU_APB1RST_PMURST                    ((uint32_t)0x10000000) //!< PMU clock reset

/**
  * @brief RCU_AHBEN register Bit definition
  */
#define  RCU_AHBEN_DMAEN                       ((uint32_t)0x00000001) //!< DMA clock enable
#define  RCU_AHBEN_RMCEN                       ((uint32_t)0x00000004) //!< SRAM interface clock enable
#define  RCU_AHBEN_FMCEN                       ((uint32_t)0x00000010) //!< FMC clock enable
#define  RCU_AHBEN_CRCEN                       ((uint32_t)0x00000040) //!< CRC clock enable
#define  RCU_AHBEN_PAEN                        ((uint32_t)0x00020000) //!< GPIOA clock enable
#define  RCU_AHBEN_PBEN                        ((uint32_t)0x00040000) //!< GPIOB clock enable
#define  RCU_AHBEN_PCEN                        ((uint32_t)0x00080000) //!< GPIOC clock enable
#define  RCU_AHBEN_PFEN                        ((uint32_t)0x00400000) //!< GPIOF clock enable

/**
  * @brief RCU_APB2EN register Bit definition
  */
#define  RCU_APB2EN_SYSCFGEN                   ((uint32_t)0x00000001) //!< SYSCFG clock enable
#define  RCU_APB2EN_USART6EN                   ((uint32_t)0x00000020) //!< USART6 clock enable
#define  RCU_APB2EN_USART7EN                   ((uint32_t)0x00000040) //!< USART7 clock enable
#define  RCU_APB2EN_USART8EN                   ((uint32_t)0x00000080) //!< USART8 clock enable
#define  RCU_APB2EN_ADCEN                      ((uint32_t)0x00000200) //!< ADC1 clock enable
#define  RCU_APB2EN_TIM1EN                     ((uint32_t)0x00000800) //!< TIM1 clock enable
#define  RCU_APB2EN_SPI1EN                     ((uint32_t)0x00001000) //!< SPI1 clock enable
#define  RCU_APB2EN_USART1EN                   ((uint32_t)0x00004000) //!< USART1 clock enable
#define  RCU_APB2EN_TIM15EN                    ((uint32_t)0x00010000) //!< TIM15 clock enable
#define  RCU_APB2EN_TIM16EN                    ((uint32_t)0x00020000) //!< TIM16 clock enable
#define  RCU_APB2EN_TIM17EN                    ((uint32_t)0x00040000) //!< TIM17 clock enable
#define  RCU_APB2EN_DBGEN                      ((uint32_t)0x00400000) //!< DBGMCU clock enable

/**
  * @brief RCU_APB1EN register Bit definition
  */
#define  RCU_APB1EN_TIM2EN                     ((uint32_t)0x00000001) //!< Timer 2 clock enable
#define  RCU_APB1EN_TIM3EN                     ((uint32_t)0x00000002) //!< Timer 3 clock enable
#define  RCU_APB1EN_TIM6EN                     ((uint32_t)0x00000010) //!< Timer 6 clock enable
#define  RCU_APB1EN_TIM14EN                    ((uint32_t)0x00000100) //!< Timer 14 clock enable
#define  RCU_APB1EN_WWDTEN                     ((uint32_t)0x00000800) //!< Window Watchdog clock enable
#define  RCU_APB1EN_SPI2EN                     ((uint32_t)0x00004000) //!< SPI2 clock enable
#define  RCU_APB1EN_USART2EN                   ((uint32_t)0x00020000) //!< USART2 clock enable
#define  RCU_APB1EN_I2C1EN                     ((uint32_t)0x00200000) //!< I2C1 clock enable
#define  RCU_APB1EN_I2C2EN                     ((uint32_t)0x00400000) //!< I2C2 clock enable
#define  RCU_APB1EN_PMUEN                      ((uint32_t)0x10000000) //!< PMU clock enable

/**
  * @brief RCU_VBDC register Bit definition
  */
#define  RCU_VBDC_LXTEN                        ((uint32_t)0x00000001) //!< LXT Enable
#define  RCU_VBDC_LXTSTAB                      ((uint32_t)0x00000002) //!< LXT Stabilization flag
#define  RCU_VBDC_LXTBYP                       ((uint32_t)0x00000004) //!< LXT Bypass

#define  RCU_VBDC_LXTDRV                       ((uint32_t)0x00000038) //!< LXTDRV[2:0] bits (LXT Osc. drive capability) */
#define  RCU_VBDC_LXTDRV_0                     ((uint32_t)0x00000008) //!< Bit 0
#define  RCU_VBDC_LXTDRV_1                     ((uint32_t)0x00000010) //!< Bit 1
#define  RCU_VBDC_LXTDRV_2                     ((uint32_t)0x00000020) //!< Bit 2

#define  RCU_VBDC_RTCSRC                       ((uint32_t)0x00000300) //!< RTCSRC[1:0] bits
#define  RCU_VBDC_RTCSRC_0                     ((uint32_t)0x00000100) //!< Bit 0
#define  RCU_VBDC_RTCSRC_1                     ((uint32_t)0x00000200) //!< Bit 1

#define  RCU_VBDC_RTCCLKEN                     ((uint32_t)0x00008000) //!< RTC clock enable
#define  RCU_VBDC_VBTRST                       ((uint32_t)0x00010000) //!< VBAT domain software reset

/**
  * @brief RCU_STS register Bit definition
  */
#define  RCU_STS_LRCEN                         ((uint32_t)0x00000001) //!< LRC enable
#define  RCU_STS_LRCSTAB                       ((uint32_t)0x00000002) //!< LRC Stabilization flag
#define  RCU_STS_REGERRRSTF                    ((uint32_t)0x00400000) //!< register error reset flag
#define  RCU_STS_V15RSTF                       ((uint32_t)0x00800000) //!< Reset flag from the 1.5V domain
#define  RCU_STS_CRSTF                         ((uint32_t)0x01000000) //!< Clear reset Flag
#define  RCU_STS_OBURSTF                       ((uint32_t)0x02000000) //!< Option byte Update reset flag
#define  RCU_STS_NRSTF                         ((uint32_t)0x04000000) //!< reset flag of pin nRST
#define  RCU_STS_PORRSTF                       ((uint32_t)0x08000000) //!< POR/PDR reset flag
#define  RCU_STS_SWRSTF                        ((uint32_t)0x10000000) //!< Software reset flag
#define  RCU_STS_FWDTRSTF                      ((uint32_t)0x20000000) //!< FWDT reset flag
#define  RCU_STS_WWDTRSTF                      ((uint32_t)0x40000000) //!< WWDT reset flag
#define  RCU_STS_LPERSTF                       ((uint32_t)0x80000000) //!< Low power enter reset flag

/**
  * @brief RCU_AHBRST register Bit definition
  */
#define  RCU_AHBRST_PARST                      ((uint32_t)0x00020000) //!< PORT A clock reset
#define  RCU_AHBRST_PBRST                      ((uint32_t)0x00040000) //!< PORT B clock reset
#define  RCU_AHBRST_PCRST                      ((uint32_t)0x00080000) //!< PORT C clock reset
#define  RCU_AHBRST_PFRST                      ((uint32_t)0x00040000) //!< PORT F clock reset


/**
  * @brief RCU_CFG2 register Bit definition
  */
#define  RCU_CFG2_PLLPDIV1                     ((uint32_t)0x0000000F) //!< PLLPDIV[3:0] bits
#define  RCU_CFG2_PLLPDIV1_0                   ((uint32_t)0x00000001) //!< Bit 0
#define  RCU_CFG2_PLLPDIV1_1                   ((uint32_t)0x00000002) //!< Bit 1
#define  RCU_CFG2_PLLPDIV1_2                   ((uint32_t)0x00000004) //!< Bit 2
#define  RCU_CFG2_PLLPDIV1_3                   ((uint32_t)0x00000008) //!< Bit 3

/**
  * @brief RCU_CFG3 register Bit definition
  */
#define  RCU_CFG3_USART1SEL                    ((uint32_t)0x00000003) //!< USART1SEL[1:0] bits
#define  RCU_CFG3_USART1SEL_0                  ((uint32_t)0x00000001) //!< Bit 0
#define  RCU_CFG3_USART1SEL_1                  ((uint32_t)0x00000002) //!< Bit 1
#define  RCU_CFG3_I2C1SEL                      ((uint32_t)0x00000010) //!< I2C1SEL bits

/**
  * @brief RCU_CTR2 register Bit definition
  */
#define  RCU_CTR2_HRC14EN                      ((uint32_t)0x00000001) //!< HRC14 enable
#define  RCU_CTR2_HRC14STAB                    ((uint32_t)0x00000002) //!< HRC14 Stabilization flag
#define  RCU_CTR2_ADCDISHRC14                  ((uint32_t)0x00000004) //!< ADC control HRC14 opening disable
#define  RCU_CTR2_HRC14TRIM                    ((uint32_t)0x000000F8) //!< HRC14 Triming
#define  RCU_CTR2_HRC14CALIB                   ((uint32_t)0x0000FF00) //!< HRC14 calibration

/*----------------------------------------------------------------------------*/
/*            Real-Time Clock (RTC)                                           */
/*----------------------------------------------------------------------------*/

/**
  * @brief RTC_TIME register Bit definition
  */
#define RTC_TIME_PM                            ((uint32_t)0x00400000) //!< AM/PM notation
#define RTC_TIME_HORTEN                        ((uint32_t)0x00300000) //!< HORTEN[1:0] (Hour tens (BCD))
#define RTC_TIME_HORTEN_0                      ((uint32_t)0x00100000) //!< bit 0
#define RTC_TIME_HORTEN_1                      ((uint32_t)0x00200000) //!< bit 1
#define RTC_TIME_HORUNT                        ((uint32_t)0x000F0000) //!<  HORUNT[3:0] (Hour units (BCD))
#define RTC_TIME_HORUNT_0                      ((uint32_t)0x00010000) //!<  bit 0
#define RTC_TIME_HORUNT_1                      ((uint32_t)0x00020000) //!<  bit 1
#define RTC_TIME_HORUNT_2                      ((uint32_t)0x00040000) //!< bit 2
#define RTC_TIME_HORUNT_3                      ((uint32_t)0x00080000) //!<  bit 3
#define RTC_TIME_MINTEN                        ((uint32_t)0x00007000) //!< MINTEN[2:0] (Minute tens (BCD))
#define RTC_TIME_MINTEN_0                      ((uint32_t)0x00001000) //!< bit 0
#define RTC_TIME_MINTEN_1                      ((uint32_t)0x00002000) //!< bit 1
#define RTC_TIME_MINTEN_2                      ((uint32_t)0x00004000) //!< bit 2
#define RTC_TIME_MINUNT                        ((uint32_t)0x00000F00) //!< MINUNT[3:0] (Minute units (BCD))
#define RTC_TIME_MINUNT_0                      ((uint32_t)0x00000100) //!< bit 0
#define RTC_TIME_MINUNT_1                      ((uint32_t)0x00000200) //!< bit 1
#define RTC_TIME_MINUNT_2                      ((uint32_t)0x00000400) //!< bit 2
#define RTC_TIME_MINUNT_3                      ((uint32_t)0x00000800) //!< bit 3
#define RTC_TIME_SECTEN                        ((uint32_t)0x00000070) //!< SECTEN[2:0] (Second tens (BCD))
#define RTC_TIME_SECTEN_0                      ((uint32_t)0x00000010) //!< bit 0
#define RTC_TIME_SECTEN_1                      ((uint32_t)0x00000020) //!< bit 1
#define RTC_TIME_SECTEN_2                      ((uint32_t)0x00000040) //!< bit 2
#define RTC_TIME_SECUNT                        ((uint32_t)0x0000000F) //!< SECUNT[3:0]
#define RTC_TIME_SECUNT_0                      ((uint32_t)0x00000001) //!< bit 0
#define RTC_TIME_SECUNT_1                      ((uint32_t)0x00000002) //!< bit 1
#define RTC_TIME_SECUNT_2                      ((uint32_t)0x00000004) //!< bit 2
#define RTC_TIME_SECUNT_3                      ((uint32_t)0x00000008) //!< bit 3

/**
  * @brief RTC_DATE register Bit definition
  */
#define RTC_DATE_YTEN                          ((uint32_t)0x00F00000) //!< YTEN[3:0] (Year tens (BCD))
#define RTC_DATE_YTEN_0                        ((uint32_t)0x00100000) //!< bit 0
#define RTC_DATE_YTEN_1                        ((uint32_t)0x00200000) //!< bit 1
#define RTC_DATE_YTEN_2                        ((uint32_t)0x00400000) //!< bit 2
#define RTC_DATE_YTEN_3                        ((uint32_t)0x00800000) //!< bit 3
#define RTC_DATE_YUNT                          ((uint32_t)0x000F0000) //!< YUNT[3:0] (Year units (BCD))
#define RTC_DATE_YUNT_0                        ((uint32_t)0x00010000) //!< bit  0
#define RTC_DATE_YUNT_1                        ((uint32_t)0x00020000) //!< bit  1
#define RTC_DATE_YUNT_2                        ((uint32_t)0x00040000) //!< bit   2
#define RTC_DATE_YUNT_3                        ((uint32_t)0x00080000) //!< bit  3
#define RTC_DATE_WUNT                          ((uint32_t)0x0000E000) //!< WUNT[2:0] (eek day units)
#define RTC_DATE_WUNT_0                        ((uint32_t)0x00002000) //!< bit 0
#define RTC_DATE_WUNT_1                        ((uint32_t)0x00004000) //!< bit 1
#define RTC_DATE_WUNT_2                        ((uint32_t)0x00008000) //!< bit 2
#define RTC_DATE_MTEN                          ((uint32_t)0x00001000) //!< MTEN (Month tens (BCD))
#define RTC_DATE_MUNT                          ((uint32_t)0x00000F00) //!< MUNT[3:0] (Month units (BCD))
#define RTC_DATE_MUNT_0                        ((uint32_t)0x00000100) //!< bit 0
#define RTC_DATE_MUNT_1                        ((uint32_t)0x00000200) //!< bit 1
#define RTC_DATE_MUNT_2                        ((uint32_t)0x00000400) //!< bit 2
#define RTC_DATE_MUNT_3                        ((uint32_t)0x00000800) //!< bit 3
#define RTC_DATE_DTEN                          ((uint32_t)0x00000030) //!< DTEN[1:0] (Date tens (BCD))
#define RTC_DATE_DTEN_0                        ((uint32_t)0x00000010) //!< bit 0
#define RTC_DATE_DTEN_1                        ((uint32_t)0x00000020) //!< bit 1
#define RTC_DATE_DUNT                          ((uint32_t)0x0000000F) //!< DUNT[3:0] (Date units (BCD))
#define RTC_DATE_DUNT_0                        ((uint32_t)0x00000001) //!< bit 0
#define RTC_DATE_DUNT_1                        ((uint32_t)0x00000002) //!< bit 1
#define RTC_DATE_DUNT_2                        ((uint32_t)0x00000004) //!< bit 2
#define RTC_DATE_DUNT_3                        ((uint32_t)0x00000008) //!< bit 3

/**
  * @brief RTC_CTR register Bit definition
  */
#define RTC_CTR_CALOE                          ((uint32_t)0x00800000) //!< Calibration output enable
#define RTC_CTR_OUTSRC                         ((uint32_t)0x00600000) //!< Output source
#define RTC_CTR_OUTSRC_0                       ((uint32_t)0x00200000) //!< bit 0
#define RTC_CTR_OUTSRC_1                       ((uint32_t)0x00400000) //!< bit 1
#define RTC_CTR_APOL                           ((uint32_t)0x00100000) //!< Alarm Output polarity
#define RTC_CTR_CALSRC                         ((uint32_t)0x00080000) //!< Calibration output source
#define RTC_CTR_SAVEF                          ((uint32_t)0x00040000) //!< saving time flag
#define RTC_CTR_DEC1H                          ((uint32_t)0x00020000) //!< decrease 1 hour
#define RTC_CTR_INC1H                          ((uint32_t)0x00010000) //!< increase 1 hour
#define RTC_CTR_TRIE                           ((uint32_t)0x00008000) //!< Time recording
#define RTC_CTR_ALRIE                          ((uint32_t)0x00001000) //!< Alarm interrupt enable
#define RTC_CTR_TRE                            ((uint32_t)0x00000800) //!< Time recording enable
#define RTC_CTR_ALRE                           ((uint32_t)0x00000100) //!< Alarm enable
#define RTC_CTR_FMT12                          ((uint32_t)0x00000040) //!< Hour format
#define RTC_CTR_DAR                            ((uint32_t)0x00000020) //!< Direct access register
#define RTC_CTR_OPCLKEN                        ((uint32_t)0x00000010) //!< External accurate clock detection enable
#define RTC_CTR_TRESEL                         ((uint32_t)0x00000008) //!< Time record event valid edge

/**
  * @brief RTC_STS register Bit definition
  */
#define RTC_STS_CALBSY                         ((uint32_t)0x00010000) //!< Calibration busy
#define RTC_STS_TAMP2F                         ((uint32_t)0x00004000) //!< RTC_INBREAK2 detection flag
#define RTC_STS_TAMP1F                         ((uint32_t)0x00002000) //!< RTC_INBREAK1 detection flag
#define RTC_STS_TSOVF                          ((uint32_t)0x00001000) //!< Time-stamp overflow flag
#define RTC_STS_TSF                            ((uint32_t)0x00000800) //!< Time-stamp flag
#define RTC_STS_ALRF                           ((uint32_t)0x00000100) //!< Alarm flag
#define RTC_STS_INITE                          ((uint32_t)0x00000080) //!< Initialization mode enbale
#define RTC_STS_INITF                          ((uint32_t)0x00000040) //!< Initialization mode endter flag
#define RTC_STS_RSF                            ((uint32_t)0x00000020) //!< Registers synchronization flag
#define RTC_STS_INITS                          ((uint32_t)0x00000010) //!<  Initialization status flag
#define RTC_STS_SHF_BUSY                       ((uint32_t)0x00000008) //!< Shift busy
#define RTC_STS_ALRWAF                         ((uint32_t)0x00000001) //!<  Alarm write access flag

/**
  * @brief RTC_PDIV register Bit definition
  */
#define RTC_PDIV_PDIV1                         ((uint32_t)0x007F0000) //!< first pre-divider factor
#define RTC_PDIV_PDIV2                         ((uint32_t)0x00007FFF) //!< second pre-divider factor

/**
  * @brief RTC_ACFG1 register Bit definition
  */
#define RTC_ACFG1_WDBYP                        ((uint32_t)0x80000000) //!< week/date bypass
#define RTC_ACFG1_WDSEL                        ((uint32_t)0x40000000) //!< week/date selection
#define RTC_ACFG1_DTEN                         ((uint32_t)0x30000000) //!< DTEN[1:0] Date tens (BCD)
#define RTC_ACFG1_DTEN_0                       ((uint32_t)0x10000000) //!< bit 0
#define RTC_ACFG1_DTEN_1                       ((uint32_t)0x20000000) //!< bit 1
#define RTC_ACFG1_DUNT                         ((uint32_t)0x0F000000) //!< DUNT[3:0] Date units (BCD)
#define RTC_ACFG1_DUNT_0                       ((uint32_t)0x01000000) //!< bit 0
#define RTC_ACFG1_DUNT_1                       ((uint32_t)0x02000000) //!< bit 1
#define RTC_ACFG1_DUNT_2                       ((uint32_t)0x04000000) //!< bit 2
#define RTC_ACFG1_DUNT_3                       ((uint32_t)0x08000000) //!< bit 3
#define RTC_ACFG1_HORBYP                       ((uint32_t)0x00800000) //!< hours bypass
#define RTC_ACFG1_PM                           ((uint32_t)0x00400000) //!< AM/PM notation
#define RTC_ACFG1_HORTEN                       ((uint32_t)0x00300000) //!< HORTEN[1:0] Hour tens (BCD)
#define RTC_ACFG1_HORTEN_0                     ((uint32_t)0x00100000) //!< bit 0
#define RTC_ACFG1_HORTEN_1                     ((uint32_t)0x00200000) //!< bit 1
#define RTC_ACFG1_HORUNT                       ((uint32_t)0x000F0000) //!< HORUNT[3:0]  Hour units (BCD)
#define RTC_ACFG1_HORUNT_0                     ((uint32_t)0x00010000) //!< bit 0
#define RTC_ACFG1_HORUNT_1                     ((uint32_t)0x00020000) //!< bit 1
#define RTC_ACFG1_HORUNT_2                     ((uint32_t)0x00040000) //!< bit 2
#define RTC_ACFG1_HORUNT_3                     ((uint32_t)0x00080000) //!< bit 3
#define RTC_ACFG1_MINBYP                       ((uint32_t)0x00008000) //!< minutes bypass
#define RTC_ACFG1_MINTEN                       ((uint32_t)0x00007000) //!< MINTEN[2:0] Minute tens (BCD)
#define RTC_ACFG1_MINTEN_0                     ((uint32_t)0x00001000) //!< bit 0
#define RTC_ACFG1_MINTEN_1                     ((uint32_t)0x00002000) //!< bit 1
#define RTC_ACFG1_MINTEN_2                     ((uint32_t)0x00004000) //!< bit 2
#define RTC_ACFG1_MINUNT                       ((uint32_t)0x00000F00) //!< MINUNT[3:0] Minute units (BCD)
#define RTC_ACFG1_MINUNT_0                     ((uint32_t)0x00000100) //!< bit 0
#define RTC_ACFG1_MINUNT_1                     ((uint32_t)0x00000200) //!< bit 1
#define RTC_ACFG1_MINUNT_2                     ((uint32_t)0x00000400) //!< bit 2
#define RTC_ACFG1_MINUNT_3                     ((uint32_t)0x00000800) //!< bit 3
#define RTC_ACFG1_SECBYP                       ((uint32_t)0x00000080) //!<  seconds bypass
#define RTC_ACFG1_SECTEN                       ((uint32_t)0x00000070) //!<SECTEN[2:0]     Second tens (BCD)
#define RTC_ACFG1_SECTEN_0                     ((uint32_t)0x00000010) //!<  bit 0
#define RTC_ACFG1_SECTEN_1                     ((uint32_t)0x00000020) //!< bit 1
#define RTC_ACFG1_SECTEN_2                     ((uint32_t)0x00000040) //!<  bit 2
#define RTC_ACFG1_SECUNT                       ((uint32_t)0x0000000F) //!< SECUNT[3:0] Second units (BCD)
#define RTC_ACFG1_SECUNT_0                     ((uint32_t)0x00000001) //!< bit 0
#define RTC_ACFG1_SECUNT_1                     ((uint32_t)0x00000002) //!< bit 1
#define RTC_ACFG1_SECUNT_2                     ((uint32_t)0x00000004) //!< bit 2
#define RTC_ACFG1_SECUNT_3                     ((uint32_t)0x00000008) //!< bit 3

/**
  * @brief RTC_CCODE register Bit definition
  */
#define RTC_CCODE_CCODE                        ((uint32_t)0x000000FF) //!< Control code

/**
  * @brief RTC_SSEC register Bit definition
  */
#define RTC_SSEC_SSEC                          ((uint32_t)0x0000FFFF) //!< subsecond

/**
  * @brief RTC_ADJ register Bit definition
  */
#define RTC_ADJ_SSEC_ADJ                       ((uint32_t)0x00007FFF) //!< subsecond adjustment
#define RTC_ADJ_INC1S                          ((uint32_t)0x80000000) //!< increase one second


/**
  * @brief RTC_TR2 register Bit definition
  */
#define RTC_TR2_PM                             ((uint32_t)0x00400000) //!< AM/PM notation
#define RTC_TR2_HORTEN                         ((uint32_t)0x00300000) //!<  HORTEN[1:0] Hour tens (BCD)
#define RTC_TR2_HORTEN_0                       ((uint32_t)0x00100000) //!< bit 0
#define RTC_TR2_HORTEN_1                       ((uint32_t)0x00200000) //!<  bit 1
#define RTC_TR2_HORUNT                         ((uint32_t)0x000F0000) //!< HORUNT[3:0] Hour units (BCD)
#define RTC_TR2_HORUNT_0                       ((uint32_t)0x00010000) //!< bit 0
#define RTC_TR2_HORUNT_1                       ((uint32_t)0x00020000) //!< bit 1
#define RTC_TR2_HORUNT_2                       ((uint32_t)0x00040000) //!< bit 2
#define RTC_TR2_HORUNT_3                       ((uint32_t)0x00080000) //!< bit 3
#define RTC_TR2_MINTEN                         ((uint32_t)0x00007000) //!< MINTEN[2:0]  Minute tens (BCD)
#define RTC_TR2_MINTEN_0                       ((uint32_t)0x00001000) //!< bit 0
#define RTC_TR2_MINTEN_1                       ((uint32_t)0x00002000) //!< bit 1
#define RTC_TR2_MINTEN_2                       ((uint32_t)0x00004000) //!< bit 2
#define RTC_TR2_MINUNT                         ((uint32_t)0x00000F00) //!< MINUNT[3:0] Minute units (BCD)
#define RTC_TR2_MINUNT_0                       ((uint32_t)0x00000100) //!< bit 0
#define RTC_TR2_MINUNT_1                       ((uint32_t)0x00000200) //!< bit 1
#define RTC_TR2_MINUNT_2                       ((uint32_t)0x00000400) //!< bit 2
#define RTC_TR2_MINUNT_3                       ((uint32_t)0x00000800) //!< bit 3
#define RTC_TR2_SECTEN                         ((uint32_t)0x00000070) //!< SECTEN[2:0] Second tens (BCD)
#define RTC_TR2_SECTEN_0                       ((uint32_t)0x00000010) //!< bit 0
#define RTC_TR2_SECTEN_1                       ((uint32_t)0x00000020) //!< bit 1
#define RTC_TR2_SECTEN_2                       ((uint32_t)0x00000040) //!< bit 2
#define RTC_TR2_SECUNT                         ((uint32_t)0x0000000F) //!< SECUNT[3:0]  Second units (BCD)
#define RTC_TR2_SECUNT_0                       ((uint32_t)0x00000001) //!< bit 0
#define RTC_TR2_SECUNT_1                       ((uint32_t)0x00000002) //!< bit 1
#define RTC_TR2_SECUNT_2                       ((uint32_t)0x00000004) //!< bit 2
#define RTC_TR2_SECUNT_3                       ((uint32_t)0x00000008) //!< bit 3

/**
  * @brief RTC_TR1 register Bit definition
  */
#define RTC_TR1_WUNT                           ((uint32_t)0x0000E000) //!< WEEKUNT[1:0] Week units
#define RTC_TR1_WUNT_0                         ((uint32_t)0x00002000) //!< bit  0
#define RTC_TR1_WUNT_1                         ((uint32_t)0x00004000) //!< bit 1
#define RTC_TR1_WUNT_2                         ((uint32_t)0x00008000) //!< bit 2
#define RTC_TR1_MTEN                           ((uint32_t)0x00001000) //!< Month tens (BCD)
#define RTC_TR1_MUNT                           ((uint32_t)0x00000F00) //!< MUNT[3:0]   Month units (BCD)
#define RTC_TR1_MUNT_0                         ((uint32_t)0x00000100) //!< bit 0
#define RTC_TR1_MUNT_1                         ((uint32_t)0x00000200) //!< bit 1
#define RTC_TR1_MUNT_2                         ((uint32_t)0x00000400) //!< bit 2
#define RTC_TR1_MUNT_3                         ((uint32_t)0x00000800) //!< bit 3
#define RTC_TR1_DTEN                           ((uint32_t)0x00000030) //!< DTEN[1:0] Date tens (BCD)
#define RTC_TR1_DTEN_0                         ((uint32_t)0x00000010) //!< bit 0
#define RTC_TR1_DTEN_1                         ((uint32_t)0x00000020) //!< bit 1
#define RTC_TR1_DUNT                           ((uint32_t)0x0000000F) //!< DUNT[3:0]   Date units (BCD)
#define RTC_TR1_DUNT_0                         ((uint32_t)0x00000001) //!< bit 0
#define RTC_TR1_DUNT_1                         ((uint32_t)0x00000002) //!< bit 1
#define RTC_TR1_DUNT_2                         ((uint32_t)0x00000004) //!< bit 2
#define RTC_TR1_DUNT_3                         ((uint32_t)0x00000008) //!< bit 3

/**
  * @brief RTC_TR3 register Bit definition
  */
#define RTC_TR3_SSEC                           ((uint32_t)0x0000FFFF) //!<Subsecond

/**
  * @brief RTC_1SCAL register Bit definition
  */
#define RTC_1SCAL_INSCLK                       ((uint32_t)0x00008000) //!< Insert RTC clock
#define RTC_1SCAL_WIN8S                        ((uint32_t)0x00004000) //!< 8-second calibration window
#define RTC_1SCAL_WIN16S                       ((uint32_t)0x00002000) //!< 16-second calibration window
#define RTC_1SCAL_SWACLK                       ((uint32_t)0x000001FF) //!< SWACLK[8:0] swallow RTC clock
#define RTC_1SCAL_SWACLK_0                     ((uint32_t)0x00000001) //!< bit 0
#define RTC_1SCAL_SWACLK_1                     ((uint32_t)0x00000002) //!< bit 1
#define RTC_1SCAL_SWACLK_2                     ((uint32_t)0x00000004) //!< bit 2
#define RTC_1SCAL_SWACLK_3                     ((uint32_t)0x00000008) //!< bit 3
#define RTC_1SCAL_SWACLK_4                     ((uint32_t)0x00000010) //!< bit 4
#define RTC_1SCAL_SWACLK_5                     ((uint32_t)0x00000020) //!< bit 5
#define RTC_1SCAL_SWACLK_6                     ((uint32_t)0x00000040) //!< bit 6
#define RTC_1SCAL_SWACLK_7                     ((uint32_t)0x00000080) //!< bit 7
#define RTC_1SCAL_SWACLK_8                     ((uint32_t)0x00000100) //!< bit 8

/**
  * @brief RTC_MF register Bit definition
  */
#define RTC_MF_PC15CFG                         ((uint32_t)0x00800000) //!< PC15 config
#define RTC_MF_PC15DATA                        ((uint32_t)0x00400000) //!< PC15 output data
#define RTC_MF_PC14CFG                         ((uint32_t)0x00200000) //!< PC14 config
#define RTC_MF_PC14DATA                        ((uint32_t)0x00100000) //!< PC14 output data
#define RTC_MF_PC13CFG                         ((uint32_t)0x00080000) //!< PC13 config
#define RTC_MF_PC13DATA                        ((uint32_t)0x00040000) //!< RTC_ALARM output type/PC13 output data
#define RTC_MF_INBRKPUDIS                      ((uint32_t)0x00008000) //!< RTC_INBREAKx pull-up disable
#define RTC_MF_INBRKPRCH                       ((uint32_t)0x00006000) //!< INBRKPRCH[1:0]   RTC_INBREAKx precharge duration
#define RTC_MF_INBRKPRCH_0                     ((uint32_t)0x00002000) //!< bit 0
#define RTC_MF_INBRKPRCH_1                     ((uint32_t)0x00004000) //!< bit 1
#define RTC_MF_INBRKFLT                        ((uint32_t)0x00001800) //!< INBRKFLT[1:0] RTC_INBREAKx filter count
#define RTC_MF_INBRKFLT_0                      ((uint32_t)0x00000800) //!< bit 0
#define RTC_MF_INBRKFLT_1                      ((uint32_t)0x00001000) //!< bit 1
#define RTC_MF_INBRKFREQ                       ((uint32_t)0x00000700) //!< INBRKFREQ[2:0] Tamper sampling frequency
#define RTC_MF_INBRKFREQ_0                     ((uint32_t)0x00000100) //!< bit  0
#define RTC_MF_INBRKFREQ_1                     ((uint32_t)0x00000200) //!< bit  1
#define RTC_MF_INBRKFREQ_2                     ((uint32_t)0x00000400) //!< bit  2
#define RTC_MF_INBRKTR                         ((uint32_t)0x00000080) //!< Activate time recording on inbreak detection event
#define RTC_MF_INBRK2TRG                       ((uint32_t)0x00000010) //!< Active level for RTC_INBREAK2 input
#define RTC_MF_INBRK2E                         ((uint32_t)0x00000008) //!< RTC_INBREAK2 input detection enable
#define RTC_MF_INBRKIE                         ((uint32_t)0x00000004) //!< Inbreak interrupt enable
#define RTC_MF_INBRK1TRG                       ((uint32_t)0x00000002) //!< Active level for RTC_INBREAK1 input
#define RTC_MF_INBRK1E                         ((uint32_t)0x00000001) //!< Active level for RTC_INBREAK1 input

/**
  * @brief RTC_ACFG2 register Bit definition
  */
#define RTC_ACFG2_SSECBYP                      ((uint32_t)0x0F000000) //!< SSECBYP[3:0]   Subsecond bypass
#define RTC_ACFG2_SSECBYP_0                    ((uint32_t)0x01000000) //!< bit 0
#define RTC_ACFG2_SSECBYP_1                    ((uint32_t)0x02000000) //!< bit 1
#define RTC_ACFG2_SSECBYP_2                    ((uint32_t)0x04000000) //!< bit 2
#define RTC_ACFG2_SSECBYP_3                    ((uint32_t)0x08000000) //!< bit 3
#define RTC_ACFG2_SSEC                         ((uint32_t)0x00007FFF) //!< Subsecond

/**
  * @brief RTC_AO0 register Bit definition
  */
#define RTC_AO0                                ((uint32_t)0xFFFFFFFF) //!< RTC always on registers 0

/**
  * @brief RTC_AO1 register Bit definition
  */
#define RTC_AO1                                ((uint32_t)0xFFFFFFFF) //!< RTC always on registers 1

/**
  * @brief RTC_AO2 register Bit definition
  */
#define RTC_AO2                                ((uint32_t)0xFFFFFFFF) //!< RTC always on registers 2


/**
  * @brief RTC_AO3 register Bit definition
  */
#define RTC_AO3                                ((uint32_t)0xFFFFFFFF) //!< RTC always on registers 3

/**
  * @brief RTC_AO4 register Bit definition
  */
#define RTC_AO4                                ((uint32_t)0xFFFFFFFF) //!<  RTC always on registers 4

/*----------------------------------------------------------------------------*/
/*           Serial Peripheral Interface (SPI)                                */
/*----------------------------------------------------------------------------*/

/**
  * @brief SPI_CTR1 register Bit definition
  */
#define  SPI_CTR1_CPHA                         ((uint16_t)0x0001)     //!< Clock Phase
#define  SPI_CTR1_CPOL                         ((uint16_t)0x0002)     //!< Clock Polarity
#define  SPI_CTR1_SPIM                         ((uint16_t)0x0004)     //!< SPI mode
#define  SPI_CTR1_CRSEL                        ((uint16_t)0x0038)     //!< Communication rate selection
#define  SPI_CTR1_CRSEL_0                      ((uint16_t)0x0008)     //!< Bit 0
#define  SPI_CTR1_CRSEL_1                      ((uint16_t)0x0010)     //!< Bit 1
#define  SPI_CTR1_CRSEL_2                      ((uint16_t)0x0020)     //!< Bit 2
#define  SPI_CTR1_SPIEN                        ((uint16_t)0x0040)     //!< SPI enable
#define  SPI_CTR1_LSBF                         ((uint16_t)0x0080)     //!< LSB first
#define  SPI_CTR1_NVSWNSSM                     ((uint16_t)0x0100)     //!< NSS value in software NSS mode
#define  SPI_CTR1_SWNSSM                       ((uint16_t)0x0200)     //!< software NSS mode
#define  SPI_CTR1_ROM                          ((uint16_t)0x0400)     //!< Receive only mode
#define  SPI_CTR1_CRC16                        ((uint16_t)0x0800)     //!< 16-bit CRC enable
#define  SPI_CTR1_NXTCRC                       ((uint16_t)0x1000)     //!< Next CRC transfer
#define  SPI_CTR1_CRCEN                        ((uint16_t)0x2000)     //!< CRC calculation enable
#define  SPI_CTR1_SBOEN                        ((uint16_t)0x4000)     //!< Single-wire bidirectional output enable
#define  SPI_CTR1_SBMODE                       ((uint16_t)0x8000)     //!< Single-wire bidirectional mode

/**
  * @brief SPI_CTR2 register Bit definition
  */
#define  SPI_CTR2_DMARXEN                      ((uint16_t)0x0001)     //!< DMA enable for receive
#define  SPI_CTR2_DMATXEN                      ((uint16_t)0x0002)     //!< DMA enable for transmit
#define  SPI_CTR2_NSSOEN                       ((uint16_t)0x0004)     //!< NSS output enable
#define  SPI_CTR2_NSSPM                        ((uint16_t)0x0008)     //!< NSS pulse mode
#define  SPI_CTR2_TIEN                         ((uint16_t)0x0010)     //!< SPI TI mode enable
#define  SPI_CTR2_ERRINTEN                     ((uint16_t)0x0020)     //!< Enable bit for error interrupt
#define  SPI_CTR2_RXNEINTEN                    ((uint16_t)0x0040)     //!< Enable bit for receive Buffer Not Empty Interrupt
#define  SPI_CTR2_TXEINTEN                     ((uint16_t)0x0080)     //!< Enable bit for transmit Buffer Empty Interrupt
#define  SPI_CTR2_DLEN                         ((uint16_t)0x0F00)     //!< DLEN Data length
#define  SPI_CTR2_DLEN_0                       ((uint16_t)0x0100)     //!< Bit 0
#define  SPI_CTR2_DLEN_1                       ((uint16_t)0x0200)     //!< Bit 1
#define  SPI_CTR2_DLEN_2                       ((uint16_t)0x0400)     //!< Bit 2
#define  SPI_CTR2_DLEN_3                       ((uint16_t)0x0800)     //!< Bit 3
#define  SPI_CTR2_RXNE8                        ((uint16_t)0x1000)     //!< RXNE generate condition selection
#define  SPI_CTR2_DMARXODD                     ((uint16_t)0x2000)     //!< Number of data to receive with DMA is odd
#define  SPI_CTR2_DMATXODD                     ((uint16_t)0x4000)     //!< Number of data to transmit with DMA is odd

/**
  * @brief SPI_STS register Bit definition
  */
#define  SPI_STS_RXNE                          ((uint16_t)0x0001)     //!< Receive buffer not empty
#define  SPI_STS_TXE                           ((uint16_t)0x0002)     //!< Transmit buffer empty
#define  SPI_STS_I2SCSF                        ((uint16_t)0x0004)     //!< I2S Channel side flag
#define  SPI_STS_TXUFERR                       ((uint16_t)0x0008)     //!< Transmitter data underflow error
#define  SPI_STS_CRCERR                        ((uint16_t)0x0010)     //!< CRC error
#define  SPI_STS_MMERR                         ((uint16_t)0x0020)     //!< Multi-master error
#define  SPI_STS_RXOFERR                       ((uint16_t)0x0040)     //!< Receiver data overflow error
#define  SPI_STS_BUSY                          ((uint16_t)0x0080)     //!< Busy
#define  SPI_STS_NWERR                         ((uint16_t)0x0100)     //!< Error of SPI NSS or I2S WS
#define  SPI_STS_RXFIFOS                       ((uint16_t)0x0600)     //!< Receive FIFO status
#define  SPI_STS_RXFIFOS_0                     ((uint16_t)0x0200)     //!< Bit 0
#define  SPI_STS_RXFIFOS_1                     ((uint16_t)0x0400)     //!< Bit 1
#define  SPI_STS_TXFIFOS                       ((uint16_t)0x1800)     //!< Transmit FIFO status
#define  SPI_STS_TXFIFOS_0                     ((uint16_t)0x0800)     //!< Bit 0
#define  SPI_STS_TXFIFOS_1                     ((uint16_t)0x1000)     //!< Bit 1

/**
  * @brief SPI_DATA register Bit definition
  */
#define  SPI_DATA_DATA                         ((uint16_t)0xFFFF)     //!< Transfer data

/**
  * @brief SPI_CRCPOLYR register Bit definition
  */
#define  SPI_CRCPOLYR_CRCPR                    ((uint16_t)0xFFFF)     //!< CRC polynomial register

/**
  * @brief SPI_RCRC register Bit definition
  */
#define  SPI_RCRC_RCR                          ((uint16_t)0xFFFF)     //!< RX CRC register

/**
  * @brief SPI_TCRC register Bit definition
  */
#define  SPI_TCRC_TCR                          ((uint16_t)0xFFFF)     //!< TX CRC register

/**
  * @brief SPI_I2SCTR register Bit definition
  */
#define  SPI_I2SCTR_I2SCL                      ((uint16_t)0x0001)     //!< I2S Channel length
#define  SPI_I2SCTR_I2SDL                      ((uint16_t)0x0006)     //!< I2SDL[1:0] I2S data length
#define  SPI_I2SCTR_I2SDL_0                    ((uint16_t)0x0002)     //!< Bit 0
#define  SPI_I2SCTR_I2SDL_1                    ((uint16_t)0x0004)     //!< Bit 1
#define  SPI_I2SCTR_CKPIS                      ((uint16_t)0x0008)     //!< clock polarity of Inactive state
#define  SPI_I2SCTR_I2SSTDS                    ((uint16_t)0x0030)     //!< I2SSTDS[1:0] I2S standard selection
#define  SPI_I2SCTR_I2SSTDS_0                  ((uint16_t)0x0010)     //!< Bit 0
#define  SPI_I2SCTR_I2SSTDS_1                  ((uint16_t)0x0020)     //!< Bit 1
#define  SPI_I2SCTR_PCMLONG                    ((uint16_t)0x0080)     //!< PCM long frame synchronization
#define  SPI_I2SCTR_I2SOM                      ((uint16_t)0x0300)     //!< I2SOM[1:0] I2S operation mode
#define  SPI_I2SCTR_I2SOM_0                    ((uint16_t)0x0100)     //!< Bit 0
#define  SPI_I2SCTR_I2SOM_1                    ((uint16_t)0x0200)     //!< Bit 1
#define  SPI_I2SCTR_I2SEN                      ((uint16_t)0x0400)     //!< I2S enable
#define  SPI_I2SCTR_I2SMS                      ((uint16_t)0x0800)     //!< I2S mode selection

/**
  * @brief SPI_I2SPDIV register Bit definition
  */
#define  SPI_I2SPDIV_I2SPDIV                  ((uint16_t)0x00FF)      //!< I2S pre-divider
#define  SPI_I2SPDIV_PDIVPS                   ((uint16_t)0x0100)      //!< Parity selection of pre-divider
#define  SPI_I2SPDIV_MCKOEN                   ((uint16_t)0x0200)      //!< MCK output enable

/*---------------------------------------------------------------------------*/
/*           System Configuration (SYSCFG)                                   */
/*---------------------------------------------------------------------------*/

/**
  * @brief SYSCFG_RMAPCFG register Bit definition
  */
#define SYSCFG_RMAPCFG_MEM_RMAP               ((uint32_t)0x00000003) //!< Memory remapping selection
#define SYSCFG_RMAPCFG_MEM_RMAP_0             ((uint32_t)0x00000001) //!< SYSCFG_Memory Remap Bit 0
#define SYSCFG_RMAPCFG_MEM_RMAP_1             ((uint32_t)0x00000002) //!< SYSCFG_Memory Remap Bit 1

#define SYSCFG_RMAPCFG_ADC_DMA_CHRMAP         ((uint32_t)0x00000100) //!< ADC DMA channel remapping
#define SYSCFG_RMAPCFG_USART1TX_DMA_CHRMAP    ((uint32_t)0x00000200) //!< USART1 TX DMA remap
#define SYSCFG_RMAPCFG_USART1RX_DMA_CHRMAP    ((uint32_t)0x00000400) //!< USART1 RX DMA remap
#define SYSCFG_RMAPCFG_TIM16_DMA_CHRMAP       ((uint32_t)0x00000800) //!< Timer 16 DMA remap
#define SYSCFG_RMAPCFG_TIM17_DMA_CHRMAP       ((uint32_t)0x00001000) //!< Timer 17 DMA remap

#define SYSCFG_RMAPCFG_I2C_FMPEN_PB6          ((uint32_t)0x00010000) //!< PB6 I2C Fast Mode Plus (FM+)
#define SYSCFG_RMAPCFG_I2C_FMPEN_PB7          ((uint32_t)0x00020000) //!< PB7 I2C Fast Mode Plus (FM+)
#define SYSCFG_RMAPCFG_I2C_FMPEN_PB8          ((uint32_t)0x00040000) //!< PB8 I2C Fast Mode Plus (FM+)
#define SYSCFG_RMAPCFG_I2C_FMPEN_PB9          ((uint32_t)0x00080000) //!< PB9 I2C Fast Mode Plus (FM+)

#define SYSCFG_RMAPCFG_I2C_FMPEN_PA9          ((uint32_t)0x00400000) //!< Fast Mode Plus on PA9
#define SYSCFG_RMAPCFG_I2C_FMPEN_PA10         ((uint32_t)0x00800000) //!< Fast Mode Plus on PA10


/**
  * @brief SYSCFG_EXTISRC1 register Bit definition
  */
#define SYSCFG_EXTISRC1_EXTI0SEL0             ((uint16_t)0x000F) //!< EXTI0SEL 0 configuration
#define SYSCFG_EXTISRC1_EXTI0SEL1             ((uint16_t)0x00F0) //!< EXTI0SEL 1 configuration
#define SYSCFG_EXTISRC1_EXTI0SEL2             ((uint16_t)0x0F00) //!< EXTI0SEL 2 configuration
#define SYSCFG_EXTISRC1_EXTI0SEL3             ((uint16_t)0xF000) //!< EXTI0SEL 3 configuration

/**
  * @brief  EXTI0SEL0  configuration
  */
#define SYSCFG_EXTISRC1_EXTI0SEL0_PA          ((uint16_t)0x0000) //!< PA[0] pin
#define SYSCFG_EXTISRC1_EXTI0SEL0_PB          ((uint16_t)0x0001) //!< PB[0] pin
#define SYSCFG_EXTISRC1_EXTI0SEL0_PC          ((uint16_t)0x0002) //!< PC[0] pin
#define SYSCFG_EXTISRC1_EXTI0SEL0_PF          ((uint16_t)0x0005) //!< PF[0] pin

/**
  * @brief  EXTI0SEL1 configuration
  */
#define SYSCFG_EXTISRC1_EXTI0SEL1_PA          ((uint16_t)0x0000) //!< PA[1] pin
#define SYSCFG_EXTISRC1_EXTI0SEL1_PB          ((uint16_t)0x0010) //!< PB[1] pin
#define SYSCFG_EXTISRC1_EXTI0SEL1_PC          ((uint16_t)0x0020) //!< PC[1] pin
#define SYSCFG_EXTISRC1_EXTI0SEL1_PF          ((uint16_t)0x0050) //!< PF[1] pin

/**
  * @brief  EXTI0SEL2 configuration
  */
#define SYSCFG_EXTISRC1_EXTI0SEL2_PA          ((uint16_t)0x0000) //!< PA[2] pin
#define SYSCFG_EXTISRC1_EXTI0SEL2_PB          ((uint16_t)0x0100) //!< PB[2] pin
#define SYSCFG_EXTISRC1_EXTI0SEL2_PC          ((uint16_t)0x0200) //!< PC[2] pin
#define SYSCFG_EXTISRC1_EXTI0SEL2_PF          ((uint16_t)0x0500) //!< PF[2] pin

/**
  * @brief  EXTI0SEL3 configuration
  */
#define SYSCFG_EXTISRC1_EXTI0SEL3_PA         ((uint16_t)0x0000) //!< PA[3] pin
#define SYSCFG_EXTISRC1_EXTI0SEL3_PB         ((uint16_t)0x1000) //!< PB[3] pin
#define SYSCFG_EXTISRC1_EXTI0SEL3_PC         ((uint16_t)0x2000) //!< PC[3] pin
#define SYSCFG_EXTISRC1_EXTI0SEL3_PF         ((uint16_t)0x5000) //!< PF[3] pin

/**
  * @brief SYSCFG_EXTISRC2 register Bit definition
  */
#define SYSCFG_EXTISRC2_EXTI0SEL4            ((uint16_t)0x000F) //!< EXTI0SEL 4 configuration
#define SYSCFG_EXTISRC2_EXTI0SEL5            ((uint16_t)0x00F0) //!< EXTI0SEL 5 configuration
#define SYSCFG_EXTISRC2_EXTI0SEL6            ((uint16_t)0x0F00) //!< EXTI0SEL 6 configuration
#define SYSCFG_EXTISRC2_EXTI0SEL7            ((uint16_t)0xF000) //!< EXTI0SEL 7 configuration

/**
  * @brief  EXTI0SEL4 configuration
  */
#define SYSCFG_EXTISRC2_EXTI0SEL4_PA         ((uint16_t)0x0000) //!< PA[4] pin
#define SYSCFG_EXTISRC2_EXTI0SEL4_PB         ((uint16_t)0x0001) //!< PB[4] pin
#define SYSCFG_EXTISRC2_EXTI0SEL4_PC         ((uint16_t)0x0002) //!< PC[4] pin
#define SYSCFG_EXTISRC2_EXTI0SEL4_PF         ((uint16_t)0x0005) //!< PF[4] pin

/**
  * @brief  EXTI0SEL5 configuration
  */
#define SYSCFG_EXTISRC2_EXTI0SEL5_PA         ((uint16_t)0x0000) //!< PA[5] pin
#define SYSCFG_EXTISRC2_EXTI0SEL5_PB         ((uint16_t)0x0010) //!< PB[5] pin
#define SYSCFG_EXTISRC2_EXTI0SEL5_PC         ((uint16_t)0x0020) //!< PC[5] pin
#define SYSCFG_EXTISRC2_EXTI0SEL5_PF         ((uint16_t)0x0050) //!< PF[5] pin

/**
  * @brief  EXTI0SEL6 configuration
  */
#define SYSCFG_EXTISRC2_EXTI0SEL6_PA         ((uint16_t)0x0000) //!< PA[6] pin
#define SYSCFG_EXTISRC2_EXTI0SEL6_PB         ((uint16_t)0x0100) //!< PB[6] pin
#define SYSCFG_EXTISRC2_EXTI0SEL6_PC         ((uint16_t)0x0200) //!< PC[6] pin
#define SYSCFG_EXTISRC2_EXTI0SEL6_PF         ((uint16_t)0x0500) //!< PF[6] pin

/**
  * @brief  EXTI0SEL7 configuration
  */
#define SYSCFG_EXTISRC2_EXTI0SEL7_PA         ((uint16_t)0x0000) //!< PA[7] pin
#define SYSCFG_EXTISRC2_EXTI0SEL7_PB         ((uint16_t)0x1000) //!< PB[7] pin
#define SYSCFG_EXTISRC2_EXTI0SEL7_PC         ((uint16_t)0x2000) //!< PC[7] pin
#define SYSCFG_EXTISRC2_EXTI0SEL7_PF         ((uint16_t)0x5000) //!< PF[7] pin

/**
  * @brief SYSCFG_EXTISRC3 register Bit definition
  */
#define SYSCFG_EXTISRC3_EXTI0SEL8            ((uint16_t)0x000F) //!< EXTI0SEL 8 configuration
#define SYSCFG_EXTISRC3_EXTI0SEL9            ((uint16_t)0x00F0) //!< EXTI0SEL 9 configuration
#define SYSCFG_EXTISRC3_EXTI0SEL10           ((uint16_t)0x0F00) //!< EXTI0SEL 10 configuration
#define SYSCFG_EXTISRC3_EXTI0SEL11           ((uint16_t)0xF000) //!< EXTI0SEL 11 configuration

/**
  * @brief  EXTI8 configuration
  */
#define SYSCFG_EXTISRC3_EXTI0SEL8_PA         ((uint16_t)0x0000) //!< PA[8] pin
#define SYSCFG_EXTISRC3_EXTI0SEL8_PB         ((uint16_t)0x0001) //!< PB[8] pin
#define SYSCFG_EXTISRC3_EXTI0SEL8_PC         ((uint16_t)0x0002) //!< PC[8] pin
#define SYSCFG_EXTISRC3_EXTI0SEL8_PF         ((uint16_t)0x0005) //!< PF[8] pin


/**
  * @brief  EXTI9 configuration
  */
#define SYSCFG_EXTISRC3_EXTI0SEL9_PA         ((uint16_t)0x0000) //!< PA[9] pin
#define SYSCFG_EXTISRC3_EXTI0SEL9_PB         ((uint16_t)0x0010) //!< PB[9] pin
#define SYSCFG_EXTISRC3_EXTI0SEL9_PC         ((uint16_t)0x0020) //!< PC[9] pin
#define SYSCFG_EXTISRC3_EXTI0SEL9_PF         ((uint16_t)0x0050) //!< PF[9] pin

/**
  * @brief  EXTI10 configuration
  */
#define SYSCFG_EXTISRC3_EXTI0SEL10_PA        ((uint16_t)0x0000) //!< PA[10] pin
#define SYSCFG_EXTISRC3_EXTI0SEL10_PB        ((uint16_t)0x0100) //!< PB[10] pin
#define SYSCFG_EXTISRC3_EXTI0SEL10_PC        ((uint16_t)0x0200) //!< PC[10] pin
#define SYSCFG_EXTISRC3_EXTI0SEL10_PF        ((uint16_t)0x0500) //!< PF[10] pin

/**
  * @brief EXTI11 configuration
  */
#define SYSCFG_EXTISRC3_EXTI0SEL11_PA        ((uint16_t)0x0000) //!< PA[11] pin
#define SYSCFG_EXTISRC3_EXTI0SEL11_PB        ((uint16_t)0x1000) //!< PB[11] pin
#define SYSCFG_EXTISRC3_EXTI0SEL11_PC        ((uint16_t)0x2000) //!< PC[11] pin
#define SYSCFG_EXTISRC3_EXTI0SEL11_PF        ((uint16_t)0x5000) //!< PF[11] pin


/**
  * @brief SYSCFG_EXTISRC4 register Bit definition
  */
#define SYSCFG_EXTISRC4_EXTI0SEL12           ((uint16_t)0x000F) //!< EXTI0SEL 12 configuration
#define SYSCFG_EXTISRC4_EXTI0SEL13           ((uint16_t)0x00F0) //!< EXTI0SEL 13 configuration
#define SYSCFG_EXTISRC4_EXTI0SEL14           ((uint16_t)0x0F00) //!< EXTI0SEL 14 configuration
#define SYSCFG_EXTISRC4_EXTI0SEL15           ((uint16_t)0xF000) //!< EXTI0SEL 15 configuration

/**
  * @brief  EXTI12 configuration
  */
#define SYSCFG_EXTISRC4_EXTI0SEL12_PA        ((uint16_t)0x0000) //!< PA[12] pin
#define SYSCFG_EXTISRC4_EXTI0SEL12_PB        ((uint16_t)0x0001) //!< PB[12] pin
#define SYSCFG_EXTISRC4_EXTI0SEL12_PC        ((uint16_t)0x0002) //!< PC[12] pin
#define SYSCFG_EXTISRC4_EXTI0SEL12_PF        ((uint16_t)0x0005) //!< PF[12] pin


/**
  * @brief  EXTI13 configuration
  */
#define SYSCFG_EXTISRC4_EXTI0SEL13_PA        ((uint16_t)0x0000) //!< PA[13] pin
#define SYSCFG_EXTISRC4_EXTI0SEL13_PB        ((uint16_t)0x0010) //!< PB[13] pin
#define SYSCFG_EXTISRC4_EXTI0SEL13_PC        ((uint16_t)0x0020) //!< PC[13] pin
#define SYSCFG_EXTISRC4_EXTI0SEL13_PF        ((uint16_t)0x0050) //!< PF[13] pin


/**
  * @brief  EXTI14 configuration
  */
#define SYSCFG_EXTISRC4_EXTI0SEL14_PA        ((uint16_t)0x0000) //!< PA[14] pin
#define SYSCFG_EXTISRC4_EXTI0SEL14_PB        ((uint16_t)0x0100) //!< PB[14] pin
#define SYSCFG_EXTISRC4_EXTI0SEL14_PC        ((uint16_t)0x0200) //!< PC[14] pin
#define SYSCFG_EXTISRC4_EXTI0SEL14_PF        ((uint16_t)0x0500) //!< PF[14] pin


/**
  * @brief  EXTI15 configuration
  */
#define SYSCFG_EXTISRC4_EXTI0SEL15_PA        ((uint16_t)0x0000) //!< PA[15] pin
#define SYSCFG_EXTISRC4_EXTI0SEL15_PB        ((uint16_t)0x1000) //!< PB[15] pin
#define SYSCFG_EXTISRC4_EXTI0SEL15_PC        ((uint16_t)0x2000) //!< PC[15] pin
#define SYSCFG_EXTISRC4_EXTI0SEL15_PF        ((uint16_t)0x5000) //!< PF[15] pin


/**
  * @brief SYSCFG_ERRLOCK register Bit definition
  */
#define SYSCFG_ERRLOCK_LOCKUP_TIMBRK_LOCK    ((uint32_t)0x00000001) //!< Cortex-M0 LOCKUP lock to tim break enable
#define SYSCFG_ERRLOCK_SRAM_PRTY_TIMBRK_LOCK ((uint32_t)0x00000002) //!< SRAM parity lock to tim break
#define SYSCFG_ERRLOCK_LVD_TIMBRK_LOCK       ((uint32_t)0x00000004) //!< PVD output lock to tim break enable
#define SYSCFG_ERRLOCK_SRAM_PRTY_ERR         ((uint32_t)0x00000100) //!< SRAM parity error flag

/**
  * @brief SYSCFG_GPIOA register Bit definition
  */
#define SYSCFG_GPIOA_PA9					 ((uint32_t)0x000C0000) //!< SYSCFG PA9 voltage threshold configuration
#define SYSCFG_GPIOA_PA10            		 ((uint32_t)0x00300000) //!< SYSCFG PA10 voltage threshold configuration

/**
  * @brief SYSCFG_GPIOB register Bit definition
  */
#define SYSCFG_GPIOB_PB6					 ((uint32_t)0x00003000) //!< SYSCFG PB6 voltage threshold configuration
#define SYSCFG_GPIOB_PB7            		 ((uint32_t)0x0000C000) //!< SYSCFG PB7 voltage threshold configuration
#define SYSCFG_GPIOB_PB8					 ((uint32_t)0x00030000) //!< SYSCFG PB8 voltage threshold configuration
#define SYSCFG_GPIOB_PB9           		 	 ((uint32_t)0x000C0000) //!< SYSCFG PB9 voltage threshold configuration


/*----------------------------------------------------------------------------*/
/*                     Timers (TIMx)                                          */
/*----------------------------------------------------------------------------*/

/**
  * @brief TIMx_CTR1 register Bit definition
  */
#define  TIM_CTR1_CEN                        ((uint16_t)0x0001)     //!< Counter enable
#define  TIM_CTR1_UPD                        ((uint16_t)0x0002)     //!< Update disable
#define  TIM_CTR1_URSEL                      ((uint16_t)0x0004)     //!< Update request selection
#define  TIM_CTR1_SPEN                       ((uint16_t)0x0008)     //!< Single pulse enable
#define  TIM_CTR1_DIR                        ((uint16_t)0x0010)     //!< Direction

#define  TIM_CTR1_CPS                        ((uint16_t)0x0060)     //!< Count pattern selection
#define  TIM_CTR1_CPS_0                      ((uint16_t)0x0020)     //!< Bit 0
#define  TIM_CTR1_CPS_1                      ((uint16_t)0x0040)     //!< Bit 1

#define  TIM_CTR1_UVALSEN                    ((uint16_t)0x0080)     //!< UVAL shadow enable

#define  TIM_CTR1_CKDIV                      ((uint16_t)0x0300)     //!< Clock division
#define  TIM_CTR1_CKDIV_0                    ((uint16_t)0x0100)     //!< Bit 0
#define  TIM_CTR1_CKDIV_1                    ((uint16_t)0x0200)     //!< Bit 1

/**
  * @brief TIMx_CTR2 register Bit definition
  */
#define  TIM_CTR2_CHPSEN                     ((uint16_t)0x0001)     //!< Preload shadow enable of channel
#define  TIM_CTR2_CHPUS                      ((uint16_t)0x0004)     //!< Preload update source of channel
#define  TIM_CTR2_CHDMARS                    ((uint16_t)0x0008)     //!< DMA request source of channel

#define  TIM_CTR2_MMTOC                      ((uint16_t)0x0070)     //!< Master mode trigger out control
#define  TIM_CTR2_MMTOC_0                    ((uint16_t)0x0010)     //!< Bit 0
#define  TIM_CTR2_MMTOC_1                    ((uint16_t)0x0020)     //!< Bit 1
#define  TIM_CTR2_MMTOC_2                    ((uint16_t)0x0040)     //!< Bit 2

#define  TIM_CTR2_TI1XOR                     ((uint16_t)0x0080)     //!< XOR input for TI1
#define  TIM_CTR2_IVO1                       ((uint16_t)0x0100)     //!< Idle value output of channel 1
#define  TIM_CTR2_IVO1N                      ((uint16_t)0x0200)     //!< Idle value output of channel 1 complementary
#define  TIM_CTR2_IVO2                       ((uint16_t)0x0400)     //!< Idle value output of channel 2
#define  TIM_CTR2_IVO2N                      ((uint16_t)0x0800)     //!< Idle value output of channel 2 complementary
#define  TIM_CTR2_IVO3                       ((uint16_t)0x1000)     //!< Idle value output of channel 3
#define  TIM_CTR2_IVO3N                      ((uint16_t)0x2000)     //!< Idle value output of channel 3 complementary
#define  TIM_CTR2_IVO4                       ((uint16_t)0x4000)     //!< Idle value output of channel 4

/**
  * @brief TIMx_SMCFG register Bit definition
  */
#define  TIM_SMCFG_SMCFG                     ((uint16_t)0x0007)      //!< SMCFG[2:0] bits (Slave mode configuration)
#define  TIM_SMCFG_SMCFG_0                   ((uint16_t)0x0001)      //!< Bit 0
#define  TIM_SMCFG_SMCFG_1                   ((uint16_t)0x0002)      //!< Bit 1
#define  TIM_SMCFG_SMCFG_2                   ((uint16_t)0x0004)      //!< Bit 2

#define  TIM_SMCFG_TRIGS                     ((uint16_t)0x0070)      //!< TRIGS[2:0] bits (Trigger source selection)
#define  TIM_SMCFG_TRIGS_0                   ((uint16_t)0x0010)      //!< Bit 0
#define  TIM_SMCFG_TRIGS_1                   ((uint16_t)0x0020)      //!< Bit 1
#define  TIM_SMCFG_TRIGS_2                   ((uint16_t)0x0040)      //!< Bit 2

#define  TIM_SMCFG_MSM                       ((uint16_t)0x0080)        //!< Master/slave mode

#define  TIM_SMCFG_ETFLT                     ((uint16_t)0x0F00)      //!< ETFLT[3:0] bits (External trigger filter)
#define  TIM_SMCFG_ETFLT_0                   ((uint16_t)0x0100)      //!< Bit 0
#define  TIM_SMCFG_ETFLT_1                   ((uint16_t)0x0200)      //!< Bit 1
#define  TIM_SMCFG_ETFLT_2                   ((uint16_t)0x0400)      //!< Bit 2
#define  TIM_SMCFG_ETFLT_3                   ((uint16_t)0x0800)      //!< Bit 3

#define  TIM_SMCFG_ETPDIV                    ((uint16_t)0x3000)      //!< ETPDIV[1:0] bits (External trigger pre-divide)
#define  TIM_SMCFG_ETPDIV_0                  ((uint16_t)0x1000)      //!< Bit 0
#define  TIM_SMCFG_ETPDIV_1                  ((uint16_t)0x2000)      //!< Bit 1

#define  TIM_SMCFG_ECMODE2                   ((uint16_t)0x4000)      //!< External clock mode 2 enable
#define  TIM_SMCFG_ETRINV                    ((uint16_t)0x8000)      //!< ETR invert

/**
  * @brief TIMx_DIEN register Bit definition
  */
#define  TIM_DIEN_UPINTEN                    ((uint16_t)0x0001)      //!<Enable bit for update interrupt
#define  TIM_DIEN_CH1INTEN                   ((uint16_t)0x0002)      //!< Enable bit for channel 1 interrupt
#define  TIM_DIEN_CH2INTEN                   ((uint16_t)0x0004)      //!< Enable bit for channel 2 interrupt
#define  TIM_DIEN_CH3INTEN                   ((uint16_t)0x0008)      //!< Enable bit for channel 3 interrupt
#define  TIM_DIEN_CH4INTEN                   ((uint16_t)0x0010)      //!< Enable bit for channel 4 interrupt
#define  TIM_DIEN_COMINTEN                   ((uint16_t)0x0020)      //!< Enable bit for COM event interrupt
#define  TIM_DIEN_TINTEN                     ((uint16_t)0x0040)      //!< Enable bit for trigger interrupt
#define  TIM_DIEN_BRKINTEN                   ((uint16_t)0x0080)      //!< Enable bit for break interrupt
#define  TIM_DIEN_UPDEN                      ((uint16_t)0x0100)      //!< Enable bit for update DMA request
#define  TIM_DIEN_CH1DEN                     ((uint16_t)0x0200)      //!< Enable bit for channel 1 DMA request
#define  TIM_DIEN_CH2DEN                     ((uint16_t)0x0400)      //!< Enable bit for channel 2 DMA request
#define  TIM_DIEN_CH3DEN                     ((uint16_t)0x0800)      //!< Enable bit for channel 3 DMA request
#define  TIM_DIEN_CH4DEN                     ((uint16_t)0x1000)      //!< Enable bit for channel 4 DMA request
#define  TIM_DIEN_COMDEN                     ((uint16_t)0x2000)      //!< Enable bit for COM event DMA request
#define  TIM_DIEN_TDREN                      ((uint16_t)0x4000)      //!< Enable bit for trigger DMA request

/**
  * @brief TIMx_STS register Bit definition
  */
#define  TIM_STS_UPIF                       ((uint16_t)0x0001)       //!< Interrupt flag of update
#define  TIM_STS_CH1CCIF                    ((uint16_t)0x0002)       //!< Channel 1 capture compare interrupt flag
#define  TIM_STS_CH2CCIF                    ((uint16_t)0x0004)       //!< Channel 2 capture compare interrupt flag
#define  TIM_STS_CH3CCIF                    ((uint16_t)0x0008)       //!< Channel 3 capture compare interrupt flag
#define  TIM_STS_CH4CCIF                    ((uint16_t)0x0010)       //!< Channel 4 capture compare interrupt flag
#define  TIM_STS_CHCOMIF                    ((uint16_t)0x0020)       //!< channel communication event interrupt flag
#define  TIM_STS_TRIGIF                     ((uint16_t)0x0040)       //!< Interrupt flag of trigger
#define  TIM_STS_BRKIF                      ((uint16_t)0x0080)       //!< Interrupt flag of break
#define  TIM_STS_CH1ICOF                    ((uint16_t)0x0200)       //!< Channel 1 input capture overflow
#define  TIM_STS_CH2ICOF                    ((uint16_t)0x0400)       //!< Channel 2 input capture overflow
#define  TIM_STS_CH3ICOF                    ((uint16_t)0x0800)       //!< Channel 3 input capture overflow
#define  TIM_STS_CH4ICOF                    ((uint16_t)0x1000)       //!< Channel 4 input capture overflow

/**
  * @brief TIMx_SWEGR register Bit definition
  */
#define  TIM_SWEGR_UEG                      ((uint16_t)0x0001)        //!< Update event generation
#define  TIM_SWEGR_CH1CCG                   ((uint16_t)0x0002)        //!< Channel 1 capture compare event generation
#define  TIM_SWEGR_CH2CCG                   ((uint16_t)0x0004)        //!< Channel 2 capture compare event generation
#define  TIM_SWEGR_CH3CCG                   ((uint16_t)0x0008)        //!< Channel 3 capture compare event generation
#define  TIM_SWEGR_CH4CCG                   ((uint16_t)0x0010)        //!< Channel 4 capture compare event generation
#define  TIM_SWEGR_COMEG                    ((uint16_t)0x0020)        //!< COM event generation
#define  TIM_SWEGR_TRIGEG                   ((uint16_t)0x0040)        //!< Trigger event generation
#define  TIM_SWEGR_BRKEG                    ((uint16_t)0x0080)        //!< Break event generation

/**
  * @brief TIMx_CH12CFGR register Bit definition
  */
#define  TIM_CH12CFGR_CH1FS                 ((uint16_t)0x0003)       //!<CH1FS[1:0] bits (Channel 1 function selection)
#define  TIM_CH12CFGR_CH1FS_0               ((uint16_t)0x0001)       //!<Bit 0
#define  TIM_CH12CFGR_CH1FS_1               ((uint16_t)0x0002)       //!<Bit 1

#define  TIM_CH12CFGR_CH1OCFEN              ((uint16_t)0x0004)       //!< Channel 1 output compare fast enable
#define  TIM_CH12CFGR_CH1OCVPEN             ((uint16_t)0x0008)       //!< Channel 1 output compare value preload enable

#define  TIM_CH12CFGR_CH1OCMSEL             ((uint16_t)0x0070)       //!<CH1OCMSEL[2:0] bits (Channel 1 output compare mode selection)
#define  TIM_CH12CFGR_CH1OCMSEL_0           ((uint16_t)0x0010)       //!<Bit 0
#define  TIM_CH12CFGR_CH1OCMSEL_1           ((uint16_t)0x0020)       //!<Bit 1
#define  TIM_CH12CFGR_CH1OCMSEL_2           ((uint16_t)0x0040)       //!<Bit 2

#define  TIM_CH12CFGR_CH1OCCEN              ((uint16_t)0x0080)       //!< Channel 1 output compare clear enable

#define  TIM_CH12CFGR_CH2FS                 ((uint16_t)0x0300)       //!<CH2FS[1:0] bits (Channel 2 function selection)
#define  TIM_CH12CFGR_CH2FS_0               ((uint16_t)0x0100)       //!<Bit 0
#define  TIM_CH12CFGR_CH2FS_1               ((uint16_t)0x0200)       //!<Bit 1

#define  TIM_CH12CFGR_CH2OCFEN              ((uint16_t)0x0400)       //!< Channel 2 output compare fast enable
#define  TIM_CH12CFGR_CH2OCVPEN             ((uint16_t)0x0800)       //!< Channel 2 output compare value preload enable

#define  TIM_CH12CFGR_CH2OCMSEL             ((uint16_t)0x7000)       //!<CH2OCMSEL[2:0] bits (Channel 2 output compare mode selection)
#define  TIM_CH12CFGR_CH2OCMSEL_0           ((uint16_t)0x1000)       //!<Bit 0
#define  TIM_CH12CFGR_CH2OCMSEL_1           ((uint16_t)0x2000)       //!<Bit 1
#define  TIM_CH12CFGR_CH2OCMSEL_2           ((uint16_t)0x4000)       //!<Bit 2

#define  TIM_CH12CFGR_CH2OCCEN              ((uint16_t)0x8000)       //!< Channel 2 output compare clear enable

/*----------------------------------------------------------------------------*/

#define  TIM_CH12CFGR_CH1ICPDIV             ((uint16_t)0x000C)       //!<CH1ICPDIV[1:0] bits (Channel 1 input capture pre-divide)
#define  TIM_CH12CFGR_CH1ICPDIV_0           ((uint16_t)0x0004)       //!<Bit 0
#define  TIM_CH12CFGR_CH1ICPDIV_1           ((uint16_t)0x0008)       //!<Bit 1

#define  TIM_CH12CFGR_CH1ICFLT              ((uint16_t)0x00F0)       //!<CH1ICFLT[3:0] bits (Channel 1 input capture filter)
#define  TIM_CH12CFGR_CH1ICFLT_0            ((uint16_t)0x0010)       //!<Bit 0
#define  TIM_CH12CFGR_CH1ICFLT_1            ((uint16_t)0x0020)       //!<Bit 1
#define  TIM_CH12CFGR_CH1ICFLT_2            ((uint16_t)0x0040)       //!<Bit 2
#define  TIM_CH12CFGR_CH1ICFLT_3            ((uint16_t)0x0080)       //!<Bit 3

#define  TIM_CH12CFGR_CH2ICPDIV             ((uint16_t)0x0C00)       //!<CH2ICPDIV[1:0] bits (Channel 2 input capture pre-divide)
#define  TIM_CH12CFGR_CH2ICPDIV_0           ((uint16_t)0x0400)       //!<Bit 0
#define  TIM_CH12CFGR_CH2ICPDIV_1           ((uint16_t)0x0800)       //!<Bit 1

#define  TIM_CH12CFGR_CH2ICFLT              ((uint16_t)0xF000)       //!<CH2ICFLT[3:0] bits (Channel 2 input capture filter)
#define  TIM_CH12CFGR_CH2ICFLT_0            ((uint16_t)0x1000)       //!<Bit 0
#define  TIM_CH12CFGR_CH2ICFLT_1            ((uint16_t)0x2000)       //!<Bit 1
#define  TIM_CH12CFGR_CH2ICFLT_2            ((uint16_t)0x4000)       //!<Bit 2
#define  TIM_CH12CFGR_CH2ICFLT_3            ((uint16_t)0x8000)       //!<Bit 3

/**
  * @brief TIMx_CH34CFGR register Bit definition
  */
#define  TIM_CH34CFGR_CH3FS                 ((uint16_t)0x0003)       //!< CH3FS[1:0] bits (Channel 3 function selection)
#define  TIM_CH34CFGR_CH3FS_0               ((uint16_t)0x0001)       //!<Bit 0
#define  TIM_CH34CFGR_CH3FS_1               ((uint16_t)0x0002)       //!<Bit 1

#define  TIM_CH34CFGR_CH3OCFEN              ((uint16_t)0x0004)       //!< Channel 3 output compare fast enable
#define  TIM_CH34CFGR_CH3OCVPEN             ((uint16_t)0x0008)       //!< Channel 3 output compare value preload enable

#define  TIM_CH34CFGR_CH3OCMSEL             ((uint16_t)0x0070)       //!<CH3OCMSEL[2:0] bits (Channel 3 output compare mode selection)
#define  TIM_CH34CFGR_CH3OCMSEL_0           ((uint16_t)0x0010)       //!<Bit 0
#define  TIM_CH34CFGR_CH3OCMSEL_1           ((uint16_t)0x0020)       //!<Bit 1
#define  TIM_CH34CFGR_CH3OCMSEL_2           ((uint16_t)0x0040)       //!<Bit 2

#define  TIM_CH34CFGR_CH3OCCEN              ((uint16_t)0x0080)       //!< Channel 3 output compare clear enable

#define  TIM_CH34CFGR_CH4FS                 ((uint16_t)0x0300)       //!<CH4FS[1:0] bits (Channel 4 function selection
#define  TIM_CH34CFGR_CH4FS_0               ((uint16_t)0x0100)       //!<Bit 0
#define  TIM_CH34CFGR_CH4FS_1               ((uint16_t)0x0200)       //!<Bit 1

#define  TIM_CH34CFGR_CH4OCFEN              ((uint16_t)0x0400)       //!< Channel 4 output compare fast enable
#define  TIM_CH34CFGR_CH4OCVPEN             ((uint16_t)0x0800)       //!< Channel 4 output compare value preload enable

#define  TIM_CH34CFGR_CH4OCMSEL             ((uint16_t)0x7000)       //!<CH4OCMSEL[2:0] bits (Channel 4 output compare mode selection)
#define  TIM_CH34CFGR_CH4OCMSEL_0           ((uint16_t)0x1000)       //!<Bit 0
#define  TIM_CH34CFGR_CH4OCMSEL_1           ((uint16_t)0x2000)       //!<Bit 1
#define  TIM_CH34CFGR_CH4OCMSEL_2           ((uint16_t)0x4000)       //!<Bit 2

#define  TIM_CH34CFGR_CH4OCCEN              ((uint16_t)0x8000)       //!< Channel 4 output compare clear enable

/*----------------------------------------------------------------------------*/

#define  TIM_CH34CFGR_CH3ICPDIV             ((uint16_t)0x000C)       //!< CH3ICPDIV[1:0] bits (Channel 3 input capture pre-divide)
#define  TIM_CH34CFGR_CH3ICPDIV_0           ((uint16_t)0x0004)       //!< Bit 0
#define  TIM_CH34CFGR_CH3ICPDIV_1           ((uint16_t)0x0008)       //!< Bit 1

#define  TIM_CH34CFGR_CH3ICFLT              ((uint16_t)0x00F0)       //!< CH3ICFLT[3:0] bits (Channel 3 input capture filter)
#define  TIM_CH34CFGR_CH3ICFLT_0            ((uint16_t)0x0010)       //!< Bit 0
#define  TIM_CH34CFGR_CH3ICFLT_1            ((uint16_t)0x0020)       //!< Bit 1
#define  TIM_CH34CFGR_CH3ICFLT_2            ((uint16_t)0x0040)       //!< Bit 2
#define  TIM_CH34CFGR_CH3ICFLT_3            ((uint16_t)0x0080)       //!< Bit 3

#define  TIM_CH34CFGR_CH4ICPDIV             ((uint16_t)0x0C00)       //!< CH4ICPDIV[1:0] bits (Channel 4 input capture pre-divide)
#define  TIM_CH34CFGR_CH4ICPDIV_0           ((uint16_t)0x0400)       //!< Bit 0
#define  TIM_CH34CFGR_CH4ICPDIV_1           ((uint16_t)0x0800)       //!< Bit 1

#define  TIM_CH34CFGR_CH4ICFLT              ((uint16_t)0xF000)       //!<CH4ICFLT[3:0] bits (Channel 4 input capture filter)
#define  TIM_CH34CFGR_CH4ICFLT_0            ((uint16_t)0x1000)       //!<Bit 0
#define  TIM_CH34CFGR_CH4ICFLT_1            ((uint16_t)0x2000)       //!<Bit 1
#define  TIM_CH34CFGR_CH4ICFLT_2            ((uint16_t)0x4000)       //!<Bit 2
#define  TIM_CH34CFGR_CH4ICFLT_3            ((uint16_t)0x8000)       //!<Bit 3

/**
  * @brief TIMx_CCCTR register Bit definition
  */
#define  TIM_CCCTR_CH1CCEN                  ((uint16_t)0x0001)       //!< Channel 1 capture compare enable
#define  TIM_CCCTR_CH1CCP                   ((uint16_t)0x0002)       //!< Channel 1 capture compare polarity
#define  TIM_CCCTR_CH1NCCEN                 ((uint16_t)0x0004)       //!< Channel 1 complementary capture compare    enable
#define  TIM_CCCTR_CH1NCCP                  ((uint16_t)0x0008)       //!< Channel 1 complementary capture compare    polarity
#define  TIM_CCCTR_CH2CCEN                  ((uint16_t)0x0010)       //!< Channel 2 capture compare enable
#define  TIM_CCCTR_CH2CCP                   ((uint16_t)0x0020)       //!< Channel 2 capture compare polarity
#define  TIM_CCCTR_CH2NCCEN                 ((uint16_t)0x0040)       //!< Channel 2 complementary capture compare enable
#define  TIM_CCCTR_CH2NCCP                  ((uint16_t)0x0080)       //!< Channel 2 complementary capture compare    polarity
#define  TIM_CCCTR_CH3CCEN                  ((uint16_t)0x0100)       //!< Channel 3 capture compare enable
#define  TIM_CCCTR_CH3CCP                   ((uint16_t)0x0200)       //!< Channel 3 capture compare polarity
#define  TIM_CCCTR_CH3NCCEN                 ((uint16_t)0x0400)       //!< Channel 3 complementary capture compare    enable
#define  TIM_CCCTR_CH3NCCP                  ((uint16_t)0x0800)       //!< Channel 3 complementary capture compare    polarity
#define  TIM_CCCTR_CH4CCEN                  ((uint16_t)0x1000)       //!< Channel 4 capture compare enable
#define  TIM_CCCTR_CH4CCP                   ((uint16_t)0x2000)       //!< Channel 4 capture compare polarity
#define  TIM_CCCTR_CH4NCCP                  ((uint16_t)0x8000)       //!< Channel 4 complementary capture compare    polarity

/**
  * @brief TIMx_CNT register Bit definition
  */
#define  TIM_CNT_CNT                        ((uint16_t)0xFFFF)       //!< Counter Value

/**
  * @brief TIMx_PDIV register Bit definition
  */
#define  TIM_PDIV_PDIV                      ((uint16_t)0xFFFF)       //!< Pre-divider Value

/**
  * @brief TIMx_UVAL register Bit definition
  */
#define  TIM_UVAL_UVAL                      ((uint16_t)0xFFFF)       //!< Counter update value

/**
  * @brief TIMx_UVALREP register Bit definition
  */
#define  TIM_UVALREP_UVALREP                ((uint8_t)0xFF)          //!< Counter update repetition value

/**
  * @brief TIMx_CH1CCVAL register Bit definition
  */
#define  TIM_CH1CCVAL_CH1CCVAL              ((uint16_t)0xFFFF)       //!< Channel 1 capture compare value

/**
  * @brief TIMx_CH2CCVAL register Bit definition
  */
#define  TIM_CH2CCVAL_CH2CCVAL              ((uint16_t)0xFFFF)       //!< Channel 2 capture compare value

/**
  * @brief TIMx_CH3CCVAL register Bit definition
  */
#define  TIM_CH3CCVAL_CH3CCVAL              ((uint16_t)0xFFFF)       //!< Channel 3 capture compare value

/**
* @brief TIMx_CH4CCVAL register Bit definition
*/
#define  TIM_CH4CCVAL_CH4CCVAL              ((uint16_t)0xFFFF)       //!< Channel 4 capture compare value

/**
  * @brief TIMx_CHOPR register Bit definition
  */
#define  TIM_CHOPR_DTCFG                    ((uint16_t)0x00FF)       //!< DTCFG[0:7] bits (Dead-time configuration)
#define  TIM_CHOPR_DTCFG_0                  ((uint16_t)0x0001)       //!< Bit 0
#define  TIM_CHOPR_DTCFG_1                  ((uint16_t)0x0002)       //!< Bit 1
#define  TIM_CHOPR_DTCFG_2                  ((uint16_t)0x0004)       //!< Bit 2
#define  TIM_CHOPR_DTCFG_3                  ((uint16_t)0x0008)       //!< Bit 3
#define  TIM_CHOPR_DTCFG_4                  ((uint16_t)0x0010)       //!< Bit 4
#define  TIM_CHOPR_DTCFG_5                  ((uint16_t)0x0020)       //!< Bit 5
#define  TIM_CHOPR_DTCFG_6                  ((uint16_t)0x0040)       //!< Bit 6
#define  TIM_CHOPR_DTCFG_7                  ((uint16_t)0x0080)       //!< Bit 7

#define  TIM_CHOPR_LCKLV                    ((uint16_t)0x0300)       //!< LCKLV[1:0] bits (Lock level control)
#define  TIM_CHOPR_LCKLV_0                  ((uint16_t)0x0100)       //!< Bit 0
#define  TIM_CHOPR_LCKLV_1                  ((uint16_t)0x0200)       //!< Bit 1

#define  TIM_CHOPR_IDLEOS                   ((uint16_t)0x0400)       //!< Idle mode off-state control
#define  TIM_CHOPR_RUNOS                    ((uint16_t)0x0800)       //!< Run mode off-state control
#define  TIM_CHOPR_BRKEN                    ((uint16_t)0x1000)       //!< Break enable
#define  TIM_CHOPR_BRKPOL                   ((uint16_t)0x2000)       //!< Break Polarity
#define  TIM_CHOPR_CHOPAEN                  ((uint16_t)0x4000)       //!< Channel output pad auto enable
#define  TIM_CHOPR_CHOPEN                   ((uint16_t)0x8000)       //!< Channel output pad enable

/**
  * @brief TIMx_DMAACR register Bit definition
  */
#define  TIM_DMAACR_DMASA                   ((uint16_t)0x001F)       //!< DMASA[4:0] (DMA start address)
#define  TIM_DMAACR_DMASA_0                 ((uint16_t)0x0001)       //!< Bit 0
#define  TIM_DMAACR_DMASA_1                 ((uint16_t)0x0002)       //!< Bit 1
#define  TIM_DMAACR_DMASA_2                 ((uint16_t)0x0004)       //!< Bit 2
#define  TIM_DMAACR_DMASA_3                 ((uint16_t)0x0008)       //!< Bit 3
#define  TIM_DMAACR_DMASA_4                 ((uint16_t)0x0010)       //!< Bit 4

#define  TIM_DMAACR_DMATL                   ((uint16_t)0x1F00)       //!< DMATL[4:0](DMA transfer length)
#define  TIM_DMAACR_DMATL_0                 ((uint16_t)0x0100)       //!< Bit 0
#define  TIM_DMAACR_DMATL_1                 ((uint16_t)0x0200)       //!< Bit 1
#define  TIM_DMAACR_DMATL_2                 ((uint16_t)0x0400)       //!< Bit 2
#define  TIM_DMAACR_DMATL_3                 ((uint16_t)0x0800)       //!< Bit 3
#define  TIM_DMAACR_DMATL_4                 ((uint16_t)0x1000)       //!< Bit 4

/**
  * @brief TIMx_DMAIR register Bit definition
  */
#define  TIM_DMAIR_DMAI                     ((uint16_t)0xFFFF)       //!< DMA access interface

/**
  * @brief TIM14_REMAP register Bit definition
  */
#define TIM14_REMAP_CH1IS                   ((uint16_t)0x0003)       //!< CH1IS[1:0] bits (Channel 1 input selection)
#define TIM14_REMAP_CH1IS_0                 ((uint16_t)0x0001)       //!< Bit 0
#define TIM14_REMAP_CH1IS_1                 ((uint16_t)0x0002)       //!< Bit 1


/*----------------------------------------------------------------------------*/
/*    Universal Synchronous Asynchronous Receiver Transmitter (USART)         */
/*----------------------------------------------------------------------------*/

/**
  * @brief USART_CTR1 register Bit definition
  */
#define  USART_CTR1_UEN                     ((uint32_t)0x00000001)   //!< USART Enable
#define  USART_CTR1_WKUPDSM                 ((uint32_t)0x00000002)   //!< Wakeup mcu from deepsleep mode enabl
#define  USART_CTR1_REN                     ((uint32_t)0x00000004)   //!< Receiver enable
#define  USART_CTR1_TEN                     ((uint32_t)0x00000008)   //!< Transmitter enable
#define  USART_CTR1_IDLEIE                  ((uint32_t)0x00000010)   //!< Enable bit for IDLE interrupt
#define  USART_CTR1_RXNEIE                  ((uint32_t)0x00000020)   //!< Enable bit for RXNE interrupt
#define  USART_CTR1_TCIE                    ((uint32_t)0x00000040)   //!< Enable bit for transmit complete interrupt
#define  USART_CTR1_TXEIE                   ((uint32_t)0x00000080)   //!< Enable bit for transmit empty interrupt
#define  USART_CTR1_PERRIE                  ((uint32_t)0x00000100)   //!< Enable bit for parity err interrupt
#define  USART_CTR1_ODDS                    ((uint32_t)0x00000200)   //!< Odd parity selection
#define  USART_CTR1_PEN                     ((uint32_t)0x00000400)   //!< Parity enable
#define  USART_CTR1_RXWKUPS                 ((uint32_t)0x00000800)   //!< Receiver wakeup selection
#define  USART_CTR1_DL                      ((uint32_t)0x00001000)   //!< Data length
#define  USART_CTR1_RXMSKEN                 ((uint32_t)0x00002000)   //!< Reception mask mode enable
#define  USART_CTR1_CMIE                    ((uint32_t)0x00004000)   //!< Enable bit for Character match interrupt
#define  USART_CTR1_OVRS                    ((uint32_t)0x00008000)   //!< Oversampling selection
#define  USART_CTR1_POSTDE                  ((uint32_t)0x001F0000)   //!< Pos-active time for Driver Enable POSTDE[4:0]
#define  USART_CTR1_POSTDE_0                ((uint32_t)0x00010000)   //!< POSTDE[0]
#define  USART_CTR1_POSTDE_1                ((uint32_t)0x00020000)   //!< POSTDE[1]
#define  USART_CTR1_POSTDE_2                ((uint32_t)0x00040000)   //!< POSTDE[2]
#define  USART_CTR1_POSTDE_3                ((uint32_t)0x00080000)   //!< POSTDE[3]
#define  USART_CTR1_POSTDE_4                ((uint32_t)0x00100000)   //!< POSTDE[4]
#define  USART_CTR1_PRETDE                  ((uint32_t)0x03E00000)   //!< Pre-active time for Driver Enable PRETDE[4:0]
#define  USART_CTR1_PRETDE_0                ((uint32_t)0x00200000)   //!< Bit 0
#define  USART_CTR1_PRETDE_1                ((uint32_t)0x00400000)   //!< Bit 1
#define  USART_CTR1_PRETDE_2                ((uint32_t)0x00800000)   //!< Bit 2
#define  USART_CTR1_PRETDE_3                ((uint32_t)0x01000000)   //!< Bit 3
#define  USART_CTR1_PRETDE_4                ((uint32_t)0x02000000)   //!< Bit 4
#define  USART_CTR1_OVRTIE                  ((uint32_t)0x04000000)   //!< Enable bit for Receiver overtime interrupt
#define  USART_CTR1_BTCIE                   ((uint32_t)0x08000000)   //!< Enable bit for Block transmit complete interrupt

/**
  * @brief USART_CTR2 register Bit definition
  */
#define  USART_CTR2_ADRM7                   ((uint32_t)0x00000010)   //!< 4bit/7bit Address Detection selection
#define  USART_CTR2_LINBRK11                ((uint32_t)0x00000020)   //!< 11-bit break frame detection
#define  USART_CTR2_LBDIE                   ((uint32_t)0x00000040)   //!< Enable bit for LIN break frame detection interrupt
#define  USART_CTR2_CKLEN                   ((uint32_t)0x00000100)   //!< CK length
#define  USART_CTR2_CPHA                    ((uint32_t)0x00000200)   //!< Clock phase
#define  USART_CTR2_CPOL                    ((uint32_t)0x00000400)   //!< Clock polarity
#define  USART_CTR2_CKEN                    ((uint32_t)0x00000800)   //!< CK pin enable
#define  USART_CTR2_STOPLEN                 ((uint32_t)0x00003000)   //!< STOP bits length STOPLEN[1:0]
#define  USART_CTR2_STOPLEN_0               ((uint32_t)0x00001000)   //!< Bit 0
#define  USART_CTR2_STOPLEN_1               ((uint32_t)0x00002000)   //!< Bit 1
#define  USART_CTR2_LINEN                   ((uint32_t)0x00004000)   //!< LIN mode enable
#define  USART_CTR2_TXRXSWAP                ((uint32_t)0x00008000)   //!< TX/RX pins swap enable
#define  USART_CTR2_RXINV                   ((uint32_t)0x00010000)   //!< RX pin inversion
#define  USART_CTR2_TXINV                   ((uint32_t)0x00020000)   //!< TX pin inversion
#define  USART_CTR2_DINV                    ((uint32_t)0x00040000)   //!< Data bit inversion
#define  USART_CTR2_MSBF                    ((uint32_t)0x00080000)   //!< MSB first
#define  USART_CTR2_ABREN                   ((uint32_t)0x00100000)   //!< Auto baud rate enable
#define  USART_CTR2_ABRSEL                  ((uint32_t)0x00600000)   //!< Auto baud rate mode selection ABRSEL[1:0]
#define  USART_CTR2_ABRSEL_0                ((uint32_t)0x00200000)   //!< Bit 0
#define  USART_CTR2_ABRSEL_1                ((uint32_t)0x00400000)   //!< Bit 1
#define  USART_CTR2_ROTEN                   ((uint32_t)0x00800000)   //!< Receiver overtime enable
#define  USART_CTR2_UADR                    ((uint32_t)0xFF000000)   //!< USART Address

/**
  * @brief USART_CTR3 register Bit definition
  */
#define  USART_CTR3_ERRIE                   ((uint32_t)0x00000001)   //!< Enable bit for Error interrupt
#define  USART_CTR3_IRDAEN                  ((uint32_t)0x00000002)   //!< IrDA mode enable
#define  USART_CTR3_IRMS                    ((uint32_t)0x00000004)   //!< IrDA mode selection
#define  USART_CTR3_HDEN                    ((uint32_t)0x00000008)   //!< Half-duplex enable
#define  USART_CTR3_SCNACK                  ((uint32_t)0x00000010)   //!< Smartcard transmit NACK in parity error
#define  USART_CTR3_SCEN                    ((uint32_t)0x00000020)   //!< Smartcard mode enable
#define  USART_CTR3_RXDMA                   ((uint32_t)0x00000040)   //!< Receive with DMA
#define  USART_CTR3_TXDMA                   ((uint32_t)0x00000080)   //!< Transmit with DMA
#define  USART_CTR3_RTSEN                   ((uint32_t)0x00000100)   //!< RTS enable
#define  USART_CTR3_CTSEN                   ((uint32_t)0x00000200)   //!< CTS enable
#define  USART_CTR3_CTSIE                   ((uint32_t)0x00000400)   //!< Enable bit for CTS interrupt
#define  USART_CTR3_SPMS                    ((uint32_t)0x00000800)   //!< Sample method selection
#define  USART_CTR3_NORXOF                  ((uint32_t)0x00001000)   //!< No Receive Overflow detection

#define  USART_CTR3_DRMRE                   ((uint32_t)0x00002000)   //!< DMA request mask on Reception Error
#define  USART_CTR3_DEN                     ((uint32_t)0x00004000)   //!< DE enable
#define  USART_CTR3_DEPS                    ((uint32_t)0x00008000)   //!< DE polarity selection
#define  USART_CTR3_SCANUM                  ((uint32_t)0x000E0000)   //!< Number of Smartcard auto-retry times SCANUM[2:0]
#define  USART_CR3_SCARCNT_0                ((uint32_t)0x00020000)   //!< Bit 0
#define  USART_CTR3_SCANUM_1                ((uint32_t)0x00040000)   //!< Bit 1
#define  USART_CTR3_SCANUM_2                ((uint32_t)0x00080000)   //!< Bit 2
#define  USART_CTR3_WKUPMTHD                ((uint32_t)0x00300000)   //!< Wakeup from Stop mode method WKUPMTHD[1:0]
#define  USART_CTR3_WKUPMTHD_0              ((uint32_t)0x00100000)   //!< Bit 0
#define  USART_CTR3_WKUPMTHD_1              ((uint32_t)0x00200000)   //!< Bit 1
#define  USART_CTR3_WKUPIE                  ((uint32_t)0x00400000)   //!< Enable bit for Wakeup from Stop mode interrupt

/**
  * @brief USART_BRT register Bit definition
  */
#define  USART_BRT_FRADIV                   ((uint16_t)0x000F)       //!< DIV Fraction value
#define  USART_BRT_INTDIV                   ((uint16_t)0xFFF0)       //!< DIV INT value

/**
  * @brief USART_GTPDIV register Bit definition
  */
#define  USART_GTPDIV_PDIV                  ((uint16_t)0x00FF)       //!< Pre-divider value PDIV[7:0]
#define  USART_GTPDIV_GUDT                  ((uint16_t)0xFF00)       //!< Guard time value GUDT[7:0]

/**
  * @brief USART_ROT register Bit definition
  */
#define  USART_ROT_RXOVR                    ((uint32_t)0x00FFFFFF)   //!< Receiver overtime value RXOVR[23:0]
#define  USART_ROT_NUMBLK                   ((uint32_t)0xFF000000)   //!< Unit number of block NUMBLK[7:0]

/**
  * @brief USART_SWTR register Bit definition
  */
#define  USART_SWTR_ABRT                    ((uint16_t)0x0001)       //!< Auto baud rate trigger
#define  USART_SWTR_BRKFST                  ((uint16_t)0x0002)       //!< Break frame send trigger
#define  USART_SWTR_RXMSKT                  ((uint16_t)0x0004)       //!< Reception mask mode trigger
#define  USART_SWTR_RXNECLR                 ((uint16_t)0x0008)       //!< RXNE clear trigger
#define  USART_SWTR_TXESET                  ((uint16_t)0x0010)       //!< TXE set trigger

/**
  * @brief USART_STS register Bit definition
  */
#define  USART_STS_PERRF                    ((uint32_t)0x00000001)   //!< Parity error flag
#define  USART_STS_FERRF                    ((uint32_t)0x00000002)   //!< Frame error flag
#define  USART_STS_NF                       ((uint32_t)0x00000004)   //!< Noise flag
#define  USART_STS_OVRERRF                  ((uint32_t)0x00000008)   //!< Reception overflow error flag
#define  USART_STS_IDLEF                    ((uint32_t)0x00000010)   //!< Idle frame detected flag
#define  USART_STS_RXNE                     ((uint32_t)0x00000020)   //!< receiver buffer not empty flag
#define  USART_STS_TCF                      ((uint32_t)0x00000040)   //!< Transmission complete flag
#define  USART_STS_TXE                      ((uint32_t)0x00000080)   //!< transmit buffer empty flag
#define  USART_STS_LINBKF                   ((uint32_t)0x00000100)   //!< LIN break frame detection flag
#define  USART_STS_CTSIF                    ((uint32_t)0x00000200)   //!< CTS interrupt flag
#define  USART_STS_CTSF                     ((uint32_t)0x00000400)   //!< CTS flag
#define  USART_STS_ROTF                     ((uint32_t)0x00000800)   //!< Receiver overtime flag
#define  USART_STS_ENDBLKF                  ((uint32_t)0x00001000)   //!< End of block flag
#define  USART_STS_ABRTERRF                 ((uint32_t)0x00004000)   //!< Auto baud rate error flag
#define  USART_STS_ABRTF                    ((uint32_t)0x00008000)   //!< Auto baud rate flag
#define  USART_STS_BSYF                     ((uint32_t)0x00010000)   //!< Busy flag
#define  USART_STS_CMF                      ((uint32_t)0x00020000)   //!< Character match flag
#define  USART_STS_BRKSF                    ((uint32_t)0x00040000)   //!< Break frame send flag
#define  USART_STS_RXMSKF                   ((uint32_t)0x00080000)   //!< Reception mask mode flag
#define  USART_STS_WKUPF                    ((uint32_t)0x00100000)   //!< Wakeup from Stop mode flag
#define  USART_STS_TENACTF                  ((uint32_t)0x00200000)   //!< TEN active flag
#define  USART_STS_RENACTF                  ((uint32_t)0x00400000)   //!< REN active flag

/**
  * @brief USART_IFCLR register Bit definition
  */
#define  USART_IFCLR_PERRC                  ((uint32_t)0x00000001)   //!< Parity error flag clear
#define  USART_IFCLR_FERRC                  ((uint32_t)0x00000002)   //!< Frame error flag clear
#define  USART_IFCLR_STARTNFC               ((uint32_t)0x00000004)   //!< Start bit Noise detected flag clear
#define  USART_IFCLR_OVRERRC                ((uint32_t)0x00000008)   //!< Overrun error flag clear
#define  USART_IFCLR_IDLEFC                 ((uint32_t)0x00000010)   //!< Idle frame detected flag clear
#define  USART_IFCLR_TCFC                   ((uint32_t)0x00000040)   //!< Transmission complete flag clear
#define  USART_IFCLR_LINBKFC                ((uint32_t)0x00000100)   //!< LIN break frame detection flag clear
#define  USART_IFCLR_CTSFC                  ((uint32_t)0x00000200)   //!< CTS flag clear
#define  USART_IFCLR_ROTFC                  ((uint32_t)0x00000800)   //!< Receiver overtime flag clear
#define  USART_IFCLR_ENDBLKFC               ((uint32_t)0x00001000)   //!< End of block flag clear
#define  USART_IFCLR_CMFC                   ((uint32_t)0x00020000)   //!< Character match flag clear
#define  USART_IFCLR_WKUPFC                 ((uint32_t)0x00100000)   //!< Wakeup from Stop mode flag clear

/**
  * @brief USART_RXBUF register Bit definition
  */
#define  USART_RXBUF_RXBUF                  ((uint16_t)0x01FF)       //!< Receive buffer RXBUF[8:0]

/**
  * @brief USART_TXBUF register Bit definition
  */
#define  USART_TXBUF_TXBUF                  ((uint16_t)0x01FF)       //!< Transmit buffer  TXBUF[8:0]

/*----------------------------------------------------------------------------*/
/*                WWDT(Window Watchdog Timer)                                 */
/*----------------------------------------------------------------------------*/

/**
  * @brief WWDT_CTR1 register Bit definition
  */
#define  WWDT_CTR1_CCODE                    ((uint8_t)0x7F)          //!< CCODE[6:0] bits (7-Bit counter (MSB to LSB))
#define  WWDT_CTR1_CCODE0                   ((uint8_t)0x01)          //!< Bit 0
#define  WWDT_CTR1_CCODE1                   ((uint8_t)0x02)          //!< Bit 1
#define  WWDT_CTR1_CCODE2                   ((uint8_t)0x04)          //!< Bit 2
#define  WWDT_CTR1_CCODE3                   ((uint8_t)0x08)          //!< Bit 3
#define  WWDT_CTR1_CCODE4                   ((uint8_t)0x10)          //!< Bit 4
#define  WWDT_CTR1_CCODE5                   ((uint8_t)0x20)          //!< Bit 5
#define  WWDT_CTR1_CCODE6                   ((uint8_t)0x40)          //!< Bit 6
#define  WWDT_CTR1_WWDTEN                   ((uint8_t)0x80)          //!< Window watchdog timer enable

/**
  * @brief WWDT_CTR2 register Bit definition
  */
#define  WWDT_CTR2_WVAL                     ((uint16_t)0x007F)       //!< WVAL[6:0] bits (7-bit window value)
#define  WWDT_CTR2_WVAL0                    ((uint16_t)0x0001)       //!< Bit 0
#define  WWDT_CTR2_WVAL1                    ((uint16_t)0x0002)       //!< Bit 1
#define  WWDT_CTR2_WVAL2                    ((uint16_t)0x0004)       //!< Bit 2
#define  WWDT_CTR2_WVAL3                    ((uint16_t)0x0008)       //!< Bit 3
#define  WWDT_CTR2_WVAL4                    ((uint16_t)0x0010)       //!< Bit 4
#define  WWDT_CTR2_WVAL5                    ((uint16_t)0x0020)       //!< Bit 5
#define  WWDT_CTR2_WVAL6                    ((uint16_t)0x0040)       //!< Bit 6

#define  WWDT_CTR2_PDIV                     ((uint16_t)0x0180)       //!< PDIV[1:0] bits (Pre-divider)
#define  WWDT_CTR2_PDIV0                    ((uint16_t)0x0080)       //!< Bit 0
#define  WWDT_CTR2_PDIV1                    ((uint16_t)0x0100)       //!< Bit 1
#define  WWDT_CTR2_RMDIE                    ((uint16_t)0x0200)       //!< Reminder interrupt enable

/**
  * @brief WWDT_STS register Bit definition
  */
#define  WWDT_STS_RMDIF                        ((uint8_t)0x01)               //!< Reminder interrupt flag

/* Hardware divider register definition */
typedef struct {
    uint32_t divdend;
    uint32_t divsor;
    uint32_t divquo;
    uint32_t divrem;
    uint32_t divsts;
} div_reg_t;

/**
  * @}
  */

#ifdef USE_STDPERIPH_DRIVER
    #include "cs32f0xx_conf.h"
#endif
extern uint32_t SystemCoreClock;
void SystemInit (void); 
void SystemCoreClockUpdate(void);

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

