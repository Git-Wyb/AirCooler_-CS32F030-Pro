/**
  * @file    cs32f0xx_adc.h
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_ADC_H__
#define __CS32F0XX_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Exported_Constants
  * @{
  */

/** 
  * @struct adc_config_t
  * @brief ADC config struct definition  
  */ 
typedef struct
{
    uint32_t adc_resolution;      	//!< Selects the resolution of the conversion                                         
    enable_state_t continuous_mode;	//!< Specifies whether the conversion is performed in Continuous or Single mode   
    uint32_t trigger_mode;			//!< Selects the external trigger Edge and enables the trigger of a regular group
    uint32_t hardware_trigger;		//!< Defines the hardware trigger used to start the analog to digital conversion of regular channels
    uint32_t data_align;			//!< Specifies whether the ADC data alignment is left or right
    uint32_t scan_direction;		//!< Specifies in which direction the channels will be conversion in the sequence                                                  
}adc_config_t;

/** 
  * @brief Check ADC list definition  
  */ 
#define ADC_ALL_LIST_CHECK(bus)				((bus) == ADC1)

/** 
  * @brief ADC conversion channel selection definition
  */  
#define ADC_CONV_CHANNEL_0               	ADC_CHANSEL_CHANSEL0	//!< ADC Channel 0 selected
#define ADC_CONV_CHANNEL_1                	ADC_CHANSEL_CHANSEL1 	//!< ADC Channel 1 selected
#define ADC_CONV_CHANNEL_2            		ADC_CHANSEL_CHANSEL2 	//!< ADC Channel 2 selected
#define ADC_CONV_CHANNEL_3               	ADC_CHANSEL_CHANSEL3 	//!< ADC Channel 3 selected
#define ADC_CONV_CHANNEL_4             		ADC_CHANSEL_CHANSEL4 	//!< ADC Channel 4 selected
#define ADC_CONV_CHANNEL_5               	ADC_CHANSEL_CHANSEL5 	//!< ADC Channel 5 selected
#define ADC_CONV_CHANNEL_6              	ADC_CHANSEL_CHANSEL6 	//!< ADC Channel 6 selected
#define ADC_CONV_CHANNEL_7             		ADC_CHANSEL_CHANSEL7 	//!< ADC Channel 7 selected
#define ADC_CONV_CHANNEL_8               	ADC_CHANSEL_CHANSEL8 	//!< ADC Channel 8 selected
#define ADC_CONV_CHANNEL_9              	ADC_CHANSEL_CHANSEL9 	//!< ADC Channel 9 selected
#define ADC_CONV_CHANNEL_10              	ADC_CHANSEL_CHANSEL10 	//!< ADC Channel 10 selected, not available for CS32F031 devices 
#define ADC_CONV_CHANNEL_11           		ADC_CHANSEL_CHANSEL11 	//!< ADC Channel 11 selected, not available for CS32F031 devices 
#define ADC_CONV_CHANNEL_12           		ADC_CHANSEL_CHANSEL12 	//!< ADC Channel 12 selected, not available for CS32F031 devices  
#define ADC_CONV_CHANNEL_13            		ADC_CHANSEL_CHANSEL13 	//!< ADC Channel 13 selected, not available for CS32F031 devices 
#define ADC_CONV_CHANNEL_14             	ADC_CHANSEL_CHANSEL14 	//!< ADC Channel 14 selected, not available for CS32F031 devices 
#define ADC_CONV_CHANNEL_15            		ADC_CHANSEL_CHANSEL15 	//!< ADC Channel 15 selected, not available for CS32F031 devices 
#define ADC_CONV_CHANNEL_16             	ADC_CHANSEL_CHANSEL16 	//!< ADC Channel 16 selected
#define ADC_CONV_CHANNEL_17           		ADC_CHANSEL_CHANSEL17 	//!< ADC Channel 17 selected
#define ADC_CONV_CHANNEL_18           		ADC_CHANSEL_CHANSEL18 	//!< ADC Channel 18 selected

#define ADC_CONV_CHANNEL_TEMP        		((uint32_t)ADC_CONV_CHANNEL_16) //!< ADC temperature sensor channel 
#define ADC_CONV_CHANNEL_VREF        		((uint32_t)ADC_CONV_CHANNEL_17) //!< ADC Vrefint channel 
#define ADC_CONV_CHANNEL_VBAT        		((uint32_t)ADC_CONV_CHANNEL_18) //!< ADC VBAT/2 channel 

#define ADC_CONV_CHANNEL_CHECK(value) 		(((value) != (uint32_t)RESET)	&& \
											(((value) & 0xFFF80000) == (uint32_t)RESET))

/** 
  * @brief ADC Conversion data resolution definition
  */ 
#define ADC_CONV_RES_12BITS      			((uint32_t)0x00000000)	//!< Conversion data resolution is 12 bits
#define ADC_CONV_RES_10BITS       			ADC_CFG_DATRES_0		//!< Conversion data resolution is 10 bits
#define ADC_CONV_RES_8BITS        			ADC_CFG_DATRES_1		//!< Conversion data resolution is 8 bits
#define ADC_CONV_RES_6BITS        			ADC_CFG_DATRES			//!< Conversion data resolution is 6 bits

#define ADC_CONV_RES_CHECK(value) 			(((value) == ADC_CONV_RES_12BITS)||((value) == ADC_CONV_RES_10BITS) || \
                                  			((value) == ADC_CONV_RES_8BITS) || ((value) == ADC_CONV_RES_6BITS))

/**  
  * @brief ADC Converstion Trigger mode selection definition
  */ 
#define ADC_TRIG_MODE_NONE					((uint32_t)0x00000000)	//!< Disable ADC conversion trigger mode 
#define ADC_TRIG_MODE_RISING				ADC_CFG_TRGMODE_0		//!< ADC conversion trigger signal is rising edge 
#define ADC_TRIG_MODE_FALLING				ADC_CFG_TRGMODE_1		//!< ADC conversion trigger signal is falling edge 
#define ADC_TRIG_MODE_RISING_FALLING		ADC_CFG_TRGMODE			//!< ADC conversion trigger signal is rising_falling 

#define ADC_TRIG_MODE_CHECK(edge) 			(((edge) == ADC_TRIG_MODE_NONE)		|| \
                                       		((edge) == ADC_TRIG_MODE_RISING)	|| \
											((edge) == ADC_TRIG_MODE_FALLING) 	|| \
											((edge) == ADC_TRIG_MODE_RISING_FALLING))
                                                                                                              
/** 
  * @brief ADC Hardware trigger source selection definition
  */ 
#define ADC_HW_TRIG_0						((uint32_t)0x00000000)	//!< Hardware trigger source is TIM1_TRIGO
#define ADC_HW_TRIG_1 						((uint32_t)0x00000040) 	//!< Hardware trigger source is TIM1_CH4OCREF
#define ADC_HW_TRIG_2        				((uint32_t)0x00000080) 	//!< Hardware trigger source is TIM2_TRGO, only for CS32F031 devices.
#define ADC_HW_TRIG_3     					((uint32_t)0x000000C0)	//!< Hardware trigger source is TIM3_TRGO
#define ADC_HW_TRIG_4      					((uint32_t)0x00000100)	//!< Hardware trigger source is TIM15_TRIG0, not for CS32F036 devices.
#define ADC_HW_TRIG_5        				((uint32_t)0x00000140) 	//!< Hardware trigger source is Reserved
#define ADC_HW_TRIG_6     					((uint32_t)0x00000180)	//!< Hardware trigger source is Reserved
#define ADC_HW_TRIG_7      					((uint32_t)0x000001C0)	//!< Hardware trigger source is Reserved

#define ADC_HW_TRIG_CHECK(value) 			(((value) == ADC_HW_TRIG_0)  || ((value) == ADC_HW_TRIG_1) 	|| \
                                      		((value) == ADC_HW_TRIG_2) 	 || ((value) == ADC_HW_TRIG_3) 	|| \
                                      		((value) == ADC_HW_TRIG_4)   || ((value) == ADC_HW_TRIG_5)	|| \
											((value) == ADC_HW_TRIG_6)	 || ((value) == ADC_HW_TRIG_7)) 

/** 
  * @brief ADC Conversion data format alignment definition.
  */ 
#define ADC_DATA_ALIGN_RIGHT             	((uint32_t)0x00000000)	//!< ADC data format is right aligen 
#define ADC_DATA_ALIGN_LEFT               	ADC_CFG_DATALG			//!< ADC data format is left aligen 

#define ADC_DATA_ALIGN_CHECK(value) 		(((value) == ADC_DATA_ALIGN_RIGHT) || \
                                     		((value) == ADC_DATA_ALIGN_LEFT))

/** 
  * @brief ADC Conversion group scan direction definition
  */   
#define ADC_SCAN_DIR_UPWARD         		((uint32_t)0x00000000)	//!< ADC conversion group scan upward direction 
#define ADC_SCAN_DIR_BACKWARD       		ADC_CFG_CGDIR 			//!< ADC conversion group scan backward direction 

#define ADC_SCAN_DIR_CHECK(value) 			(((value) == ADC_SCAN_DIR_UPWARD) || \
                                       		((value) == ADC_SCAN_DIR_BACKWARD)) 

/** 
  * @brief ADC DMA mode definition
  */   
#define ADC_DMA_MODE_SINGLE     			((uint32_t)0x00000000)	//!< DMA single mode 
#define ADC_DMA_MODE_CIRCULAR      			ADC_CFG_DMAMODE       	//!< DMA circular mode

#define ADC_DMA_MODE_CHECK(mode) 			(((mode) == ADC_DMA_MODE_SINGLE) || \
                                  			((mode) == ADC_DMA_MODE_CIRCULAR))
                                  
/** 
  * @brief ADC analog watchdog monitor channel selection definition
  */  
#define ADC_WATCHDOG_CHANNEL_0              ((uint32_t)0x00000000) 	//!< Analog watchdog monitor channel 0
#define ADC_WATCHDOG_CHANNEL_1              ((uint32_t)0x04000000) 	//!< Analog watchdog monitor channel 1
#define ADC_WATCHDOG_CHANNEL_2              ((uint32_t)0x08000000) 	//!< Analog watchdog monitor channel 2
#define ADC_WATCHDOG_CHANNEL_3              ((uint32_t)0x0C000000) 	//!< Analog watchdog monitor channel 3
#define ADC_WATCHDOG_CHANNEL_4              ((uint32_t)0x10000000) 	//!< Analog watchdog monitor channel 4
#define ADC_WATCHDOG_CHANNEL_5              ((uint32_t)0x14000000) 	//!< Analog watchdog monitor channel 5
#define ADC_WATCHDOG_CHANNEL_6              ((uint32_t)0x18000000) 	//!< Analog watchdog monitor channel 6
#define ADC_WATCHDOG_CHANNEL_7              ((uint32_t)0x1C000000) 	//!< Analog watchdog monitor channel 7
#define ADC_WATCHDOG_CHANNEL_8              ((uint32_t)0x20000000) 	//!< Analog watchdog monitor channel 8
#define ADC_WATCHDOG_CHANNEL_9              ((uint32_t)0x24000000) 	//!< Analog watchdog monitor channel 9
#define ADC_WATCHDOG_CHANNEL_10             ((uint32_t)0x28000000)	//!< Analog watchdog monitor channel 10 
#define ADC_WATCHDOG_CHANNEL_11             ((uint32_t)0x2C000000)	//!< Analog watchdog monitor channel 11
#define ADC_WATCHDOG_CHANNEL_12             ((uint32_t)0x30000000)	//!< Analog watchdog monitor channel 12
#define ADC_WATCHDOG_CHANNEL_13             ((uint32_t)0x34000000)	//!< Analog watchdog monitor channel 13 
#define ADC_WATCHDOG_CHANNEL_14             ((uint32_t)0x38000000) 	//!< Analog watchdog monitor channel 14
#define ADC_WATCHDOG_CHANNEL_15             ((uint32_t)0x3C000000) 	//!< Analog watchdog monitor channel 15
#define ADC_WATCHDOG_CHANNEL_16             ((uint32_t)0x40000000) 	//!< Analog watchdog monitor channel 16
#define ADC_WATCHDOG_CHANNEL_17             ((uint32_t)0x44000000) 	//!< Analog watchdog monitor channel 17
#define ADC_WATCHDOG_CHANNEL_18             ((uint32_t)0x48000000) 	//!< Analog watchdog monitor channel 18

#define ADC_WATCHDOG_CHANNEL_CHECK(value) 	(((value) == ADC_WATCHDOG_CHANNEL_0) ||  ((value) == ADC_WATCHDOG_CHANNEL_1) 	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_2)  ||  ((value) == ADC_WATCHDOG_CHANNEL_3)	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_4)  ||  ((value) == ADC_WATCHDOG_CHANNEL_5)  	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_6)  ||  ((value) == ADC_WATCHDOG_CHANNEL_7)  	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_8)  ||  ((value) == ADC_WATCHDOG_CHANNEL_9)  	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_10) ||  ((value) == ADC_WATCHDOG_CHANNEL_11) 	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_12) ||  ((value) == ADC_WATCHDOG_CHANNEL_13) 	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_14) ||  ((value) == ADC_WATCHDOG_CHANNEL_15) 	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_16) ||  ((value) == ADC_WATCHDOG_CHANNEL_17) 	|| \
                                    		((value) == ADC_WATCHDOG_CHANNEL_18))

/**   
  * @brief ADC sampling times cycles definition
  */ 
#define ADC_SAMPLE_TIMES_1_5             	((uint32_t)0x00000000)	//!< Sampling time is 1.5 cycles 
#define ADC_SAMPLE_TIMES_7_5              	((uint32_t)0x00000001) 	//!< Sampling time is 7.5 cycles 
#define ADC_SAMPLE_TIMES_13_5          		((uint32_t)0x00000002) 	//!< Sampling time is 13.5 cycles 
#define ADC_SAMPLE_TIMES_28_5            	((uint32_t)0x00000003) 	//!< Sampling time is 28.5 cycles 
#define ADC_SAMPLE_TIMES_41_5          		((uint32_t)0x00000004) 	//!< Sampling time is 41.5 cycles 
#define ADC_SAMPLE_TIMES_55_5            	((uint32_t)0x00000005) 	//!< Sampling time is 55.5 cycles 
#define ADC_SAMPLE_TIMES_71_5           	((uint32_t)0x00000006) 	//!< Sampling time is 71.5 cycles 
#define ADC_SAMPLE_TIMES_239_5           	((uint32_t)0x00000007) 	//!< Sampling time is 239.5 cycles 

#define ADC_SAMPLE_TIMES_CHECK(value)		(((value) == ADC_SAMPLE_TIMES_1_5)  || ((value) == ADC_SAMPLE_TIMES_7_5)	|| \
                                       		((value) == ADC_SAMPLE_TIMES_13_5) || ((value) == ADC_SAMPLE_TIMES_28_5) 	|| \
                                       		((value) == ADC_SAMPLE_TIMES_41_5) || ((value) == ADC_SAMPLE_TIMES_55_5)	|| \
                                       		((value) == ADC_SAMPLE_TIMES_71_5) || ((value) == ADC_SAMPLE_TIMES_239_5))

/**
  * @brief ADC clock source selection definition
  */ 
#define ADC_CLK_SRC_HRC14            		((uint32_t)0x00000000)	//!< ADC clock source is HRC14(Asynchronous)  
#define ADC_CLK_SRC_PCLK_DIV2          		ADC_CLK_CKSRC_0			//!< ADC clock source is PCLK/2(Synchronous)
#define ADC_CLK_SRC_PCLK_DIV4          		ADC_CLK_CKSRC_1			//!< ADC clock source is PCLK/4(Synchronous)

/**
  * @brief The ADC function enable registers
  */
#define ADC_ENABLE_REG_AUTO_STANDBY     	CFG						//!< ADC auto standby enable reg
#define ADC_ENABLE_REG_CONV_PAUSE     		CFG  					//!< ADC conversion pause enable reg
#define ADC_ENABLE_REG_WDT     				CFG						//!< ADC analog watchdog enable reg
#define ADC_ENABLE_REG_WDT_CHANNEL_MODE		CFG  					//!< ADC watchdog channel mode enable reg
#define ADC_ENABLE_REG_CONT_MODE     		CFG  					//!< ADC continous mode enable reg
#define ADC_ENABLE_REG_DISCONT_MODE    		CFG						//!< ADC discontinous mode enable reg
#define ADC_ENABLE_REG_OVERRUN_MODE    		CFG  					//!< ADC overrum mode enable reg
#define ADC_ENABLE_REG_DMA_CIRCLE_MODE    	CFG						//!< ADC DMA circular mode enable reg
#define ADC_ENABLE_REG_TEMP_SENSOR     		INNCHEN					//!< ADC temp sensor enable reg
#define ADC_ENABLE_REG_VREFINT     			INNCHEN					//!< ADC VREFINT enable reg
#define ADC_ENABLE_REG_VBAT     			INNCHEN					//!< ADC VBAT enable reg

/**
  * @brief The ADC function enable bits
  */		
#define ADC_ENABLE_BIT_AUTO_STANDBY     	ADC_CFG_ATSTDBY			//!< ADC auto standby enable bit
#define ADC_ENABLE_BIT_CONV_PAUSE     		ADC_CFG_PAUSE			//!< ADC conversion pause enable bit
#define ADC_ENABLE_BIT_WDT     				ADC_CFG_WDGEN			//!< ADC analog watchdog enable bit
#define ADC_ENABLE_BIT_WDT_CHANNEL_MODE		ADC_CFG_WDGCHMODE		//!< ADC watchdog channel mode enable bit
#define ADC_ENABLE_BIT_CONT_MODE     		ADC_CFG_GCONT			//!< ADC continous mode enable bit
#define ADC_ENABLE_BIT_DISCONT_MODE    		ADC_CFG_DISCONT			//!< ADC discontinous mode enable bit
#define ADC_ENABLE_BIT_OVERRUN_MODE    		ADC_CFG_DOVRWRT  		//!< ADC overrum mode enable bit
#define ADC_ENABLE_BIT_DMA_CIRCLE_MODE    	ADC_CFG_DMAMODE			//!< ADC DMA circular mode enable bit
#define ADC_ENABLE_BIT_TEMP_SENSOR     		ADC_INNCHEN_TSEN		//!< ADC temp sensor enable bit
#define ADC_ENABLE_BIT_VREFINT     			ADC_INNCHEN_VREFINTEN 	//!< ADC VREFINT enable bit
#define ADC_ENABLE_BIT_VBAT     			ADC_INNCHEN_VBATMEN		//!< ADC VBAT enable bit

/** 
  * @brief ADC interrupts definition
  */   
#define ADC_INTR_EOI                		ADC_INTEN_EOIIE			//!< End of ADC initialization interrupt enable 
#define ADC_INTR_EOSP             			ADC_INTEN_EOSPIE		//!< End of sampling phase interrupt enable 
#define ADC_INTR_EOC                		ADC_INTEN_EOCIE			//!< End of channel conversion interrupt enable 
#define ADC_INTR_EOG                		ADC_INTEN_EOGIE			//!< End of conversion group interrupt enable 
#define ADC_INTR_DOVR	            		ADC_INTEN_DOVRIE		//!< ADC data overrun interrupt enable 
#define ADC_INTR_WDEVT              		ADC_INTEN_WDEVTIE		//!< Analog watchdog event interrupt enable

/**
  * @brief The ADC FLAG get registers
  */	
#define ADC_FLAG_REG_EOI           			STAT					//!< End of ADC initialization interrupt flag
#define ADC_FLAG_REG_EOSP          			STAT					//!< End of sampling phase interrupt flag 
#define ADC_FLAG_REG_EOC          			STAT 					//!< End of channel conversion interrupt flag 
#define ADC_FLAG_REG_EOG          			STAT					//!< End of conversion group interrupt flag 
#define ADC_FLAG_REG_DOVR          			STAT					//!< ADC data overrun interrupt flag 
#define ADC_FLAG_REG_WDEVT         			STAT					//!< Analog watchdog event interrupt flag 
#define ADC_FLAG_REG_ADCON         			CTR 					//!< ADC power on command flag 
#define ADC_FLAG_REG_ADCOFF        			CTR 	 				//!< ADC power off command flag 
#define ADC_FLAG_REG_ADSTRT        			CTR 	 				//!< ADC start conversion command flag 
#define ADC_FLAG_REG_ADSTOP        			CTR 	 				//!< ADC stop conversion command flag 
#define ADC_FLAG_REG_CALB          			CTR 	 				//!< ADC calibration control flag

/**
  * @brief The ADC FLAG get bits
  */	
#define ADC_FLAG_BIT_EOI           			ADC_STAT_EOI  			//!< End of ADC initialization interrupt flag
#define ADC_FLAG_BIT_EOSP          			ADC_STAT_EOSP 			//!< End of sampling phase interrupt flag 
#define ADC_FLAG_BIT_EOC          			ADC_STAT_EOCH 			//!< End of channel conversion interrupt flag 
#define ADC_FLAG_BIT_EOG         	 		ADC_STAT_EOCG 			//!< End of conversion group interrupt flag 
#define ADC_FLAG_BIT_DOVR          			ADC_STAT_DOVR 			//!< ADC data overrun interrupt flag 
#define ADC_FLAG_BIT_WDEVT         			ADC_STAT_WDEVT			//!< Analog watchdog event interrupt flag 
#define ADC_FLAG_BIT_ADCON         			ADC_CTR_ADCON 			//!< ADC power on command flag 
#define ADC_FLAG_BIT_ADCOFF        			ADC_CTR_ADCOFF 			//!< ADC power off command flag 
#define ADC_FLAG_BIT_ADSTRT        			ADC_CTR_ADSTRT 			//!< ADC start conversion command flag 
#define ADC_FLAG_BIT_ADSTOP        			ADC_CTR_ADSTOP 			//!< ADC stop conversion command flag 
#define ADC_FLAG_BIT_CALB          			ADC_CTR_CALB 			//!< ADC calibration control flag 

/** 
  * @brief ADC flags clear bits
  */ 
#define ADC_FLAG_EOI           				ADC_STAT_EOI  			//!< End of ADC initialization interrupt flag
#define ADC_FLAG_EOSP          				ADC_STAT_EOSP 			//!< End of sampling phase interrupt flag 
#define ADC_FLAG_EOC          				ADC_STAT_EOCH 			//!< End of channel conversion interrupt flag 
#define ADC_FLAG_EOG          				ADC_STAT_EOCG 			//!< End of conversion group interrupt flag 
#define ADC_FLAG_DOVR          				ADC_STAT_DOVR 			//!< ADC data overrun interrupt flag 
#define ADC_FLAG_WDEVT         				ADC_STAT_WDEVT			//!< Analog watchdog event interrupt flag 

/**
  * @}
  */ 

/**
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ADCx: pointer to ADCx where x can be 1.
  * @return None
  */
#define __ADC_DEF_INIT(ADCx)					adc_def_init(ADCx)

/**
  * @brief Selects the ADC to either be clocked by the asynchronous clock(which is independent,
  *        the dedicated 14MHz clock) or the synchronous clock derived from the APB clock of the
  *        ADC bus interface divided by 2 or 4.
  * @note  This can be called only when ADC is disabled.
  * @param ADCx: pointer to ADCx where x can be 1.  
  * @param SRC: Specifies the clock.
  *			It can be one of the following values:
  *         @arg ADC_CLK_SRC_HRC14(ADC clocked by the HRC14(14MHz))
  *         @arg ADC_CLK_SRC_PCLK_DIV2(ADC clocked by the PCLK/2)
  *         @arg ADC_CLK_SRC_PCLK_DIV4(ADC clocked by the PCLK/4) 
  * @return None
  */ 
#define __ADC_CLK_SOURCE_SET(ADCx, SRC)			((ADCx)->CLK = SRC)

/**
  * @brief  Configures the high and low thresholds of the analog watchdog.
  * @note   This is only available for CS32F036, CS32F03X-RA devices.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  HIGH: the ADC analog watchdog High threshold value( 12bit value).
  * @param  LOW: the ADC analog watchdog Low threshold value( 12bit value).
  * @return None
  */
#define __ADC_WDT_THRESH_SET(ADCx, HIGH, LOW)	((ADCx)->WDTH = ((uint32_t)LOW)|((uint32_t)HIGH << 16))

/**
  * @brief  Returns the last ADCx conversion result data for ADC channel.  
  * @param  ADCx: pointer to ADCx where x can be 1.
  * @return The Data conversion value.
  */
#define __ADC_CONV_VALUE_GET(ADCx)				((uint16_t)(ADCx)->OUTDAT)

/**
  * @brief  Enables the specified ADC peripheral.
  * @param  ADCx: pointer to ADCx where x can be 1.
  * @return None
  */
#define __ADC_ENABLE(ADCx)						((ADCx)->CTR |= ADC_CTR_ADCON)

/**
  * @brief  Enables the ADC peripheral.
  * @param  ADCx: pointer to ADCx where x can be 1.
  * @return None
  */
#define __ADC_DISABLE(ADCx)						((ADCx)->CTR |= ADC_CTR_ADCOFF)

/**
  * @brief  Enables or disables the specified ADC function.   
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  FUNC: specifies the ADC function.
  *         It can be one of the following values:
  *          @arg AUTO_STANDBY (Auto standby, only available for CS32F036, CS32F03X-RA devices)
  *          @arg CONV_PAUSE (Conversion pause, only available for CS32F036, CS32F03X-RA devices, 
  *							  a hardware delay can be introduced between ADC conversions to reduce data rate)
  *          @arg WDT 		 (Analog watchdog, only available for CS32F036, CS32F03X-RA devices)
  *          @arg WDT_CHANNEL_MODE (Watchdog channel mode, only available for CS32F036, CS32F03X-RA devices)
  *          @arg CONT_MODE (Continuous mode)
  *          @arg DISCONT_MODE (Discontinuous mode)
  *          @arg OVERRUN_MODE (Overrun mode)
  *          @arg DMA_MODE (DMA mode)
  *          @arg TEMP_SENSOR (Temperature sensor channel)
  *          @arg VREFINT	(Internal voltage reference channel)
  *          @arg VBAT		(VBAT channel)  
  * @return None
  */
#define __ADC_FUNC_ENABLE(ADCx, FUNC)			((ADCx)->ADC_ENABLE_REG_##FUNC |= ADC_ENABLE_BIT_##FUNC)

/**
  * @brief  Disables the specified ADC function.   
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  FUNC: specifies the ADC function.
  *         It can be one of the following values:
  *          @arg AUTO_STANDBY (Auto standby, only available for CS32F036, CS32F03X-RA devices)
  *          @arg CONV_PAUSE (Conversion pause, only available for CS32F036, CS32F03X-RA devices)
  *          @arg WDT 		 (Analog watchdog, only available for CS32F036, CS32F03X-RA devices)
  *          @arg WDT_CHANNEL_MODE (Watchdog channel mode, only available for CS32F036, CS32F03X-RA devices)
  *          @arg TEMP_SENSOR (Temperature sensor channel)
  *          @arg VREFINT	(Internal voltage reference channel)
  *          @arg VBAT		(VBAT channel)
  *          @arg CONT_MODE (Continuous mode)
  *          @arg DISCONT_MODE (Discontinuous mode)
  *          @arg OVERRUN_MODE (Overrun mode)
  *          @arg DMA_CIRCLE_MODE (DMA circle mode)
  * @return None
  */
#define __ADC_FUNC_DISABLE(ADCx, FUNC)			((ADCx)->ADC_ENABLE_REG_##FUNC &=~ (ADC_ENABLE_BIT_##FUNC))

/**
  * @brief  Enables the specified ADC DMA request.
  * @param  ADCx: pointer to ADCx where x can be 1.
  * @return None
  */
#define __ADC_DMA_ENABLE(ADCx)					((ADCx)->CFG |= ADC_CFG_DMAEN)

/**
  * @brief  Disables the specified ADC DMA request.
  * @param  ADCx: pointer to ADCx where x can be 1.
  * @return None
  */
#define __ADC_DMA_DISABLE(ADCx)					((ADCx)->CFG &= ~(ADC_CFG_DMAEN))

/**
  * @brief  Enables the specified ADC interrupts.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  INT: specifies the ADC interrupt sources to be enabled.
  *          It can be one of the following values:
  *          @arg ADC_INTR_EOI(End of ADC initialization interrupt)
  *          @arg ADC_INTR_EOSP(End of sampling phase interrupt)
  *          @arg ADC_INTR_EOC(End of channel conversion interrupt)
  *          @arg ADC_INTR_EOG(End of conversion group interrupt)
  *          @arg ADC_INTR_DOVR(ADC data overrun interrupt)
  *          @arg ADC_INTR_WDEVT(analog watchdog event interrupt)
  * @return None
  */
#define __ADC_INTR_ENABLE(ADCx, INT)			((ADCx)->INTEN |= INT)

/**
  * @brief  Disables the specified ADC interrupts.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  INT: specifies the ADC interrupt sources to be disabled.
  *          It can be one of the following values:
  *          @arg ADC_INTR_EOI(End of ADC initialization interrupt)
  *          @arg ADC_INTR_EOSP(End of sampling phase interrupt)
  *          @arg ADC_INTR_EOC(End of channel conversion interrupt)
  *          @arg ADC_INTR_EOG(End of conversion group interrupt)
  *          @arg ADC_INTR_DOVR(ADC data overrun interrupt)
  *          @arg ADC_INTR_WDEVT(analog watchdog event interrupt)
  * @return None
  */
#define __ADC_INTR_DISABLE(ADCx, INT)			((ADCx)->INTEN &= ~(INT))

/**
  * @brief  Checks whether the specified ADC interrupt enabled or not.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  INT: specifies the ADC interrupt source to check.
  *			It can be one of the following values:
  *          @arg EOI(End of ADC initialization interrupt)
  *          @arg EOSP(End of sampling phase interrupt)
  *          @arg EOC(End of channel conversion interrupt)
  *          @arg EOG(End of conversion group)
  *          @arg DOVR(ADC data overrun interrupt)
  *          @arg WDEVT(analog watchdog event interrupt)    
  * @return SET or RESET.
  */
#define __ADC_INTR_ENABLE_STATUS_GET(ADCx, INT)	(((ADCx)->INTEN & (ADC_INTR_##INT)) ? SET : RESET)

/**
  * @brief  Checks whether the specified ADC interrupt has occured or not.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  INT: specifies the ADC interrupt source to check.
  *			It can be one of the following values:
  *          @arg EOI(End of ADC initialization interrupt)
  *          @arg EOSP(End of sampling phase interrupt)
  *          @arg EOC(End of channel conversion interrupt)
  *          @arg EOG(End of conversion group)
  *          @arg DOVR(ADC data overrun interrupt)
  *          @arg WDEVT(analog watchdog event interrupt)    
  * @return SET or RESET.
  */
#define __ADC_INTR_STATUS_GET(ADCx, INT)		(__ADC_INTR_ENABLE_STATUS_GET(ADCx, INT) && __ADC_FLAG_STATUS_GET(ADCx, INT))

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  FLAG: specifies the flag to check.
  *			It can be one of the following values:
  *          @arg EOI(End of ADC initialization interrupt flag)  
  *          @arg EOSP(End of sampling phase interrupt flag)  
  *          @arg EOC(End of channel conversion interrupt flag)  
  *          @arg EOG(End of conversion group interrupt flag)
  *          @arg DOVR(ADC data overrun interrupt flag)  
  *          @arg WDEVT(analog watchdog event interrupt flag)  
  *          @arg ADCON(ADC power on flag)
  *          @arg ADCOFF(ADC power off flag)
  *          @arg ADSTRT(ADC start conversion flag)
  *          @arg ADSTOP(ADC stop conversion flag)
  *          @arg CALB(ADC calibration start flag)
  * @return SET or RESET.
  */
#define __ADC_FLAG_STATUS_GET(ADCx, FLAG)		(((ADCx)->ADC_FLAG_REG_##FLAG & (ADC_FLAG_BIT_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the ADCx's flags.
  * @param  ADCx: pointer to ADCx where x can be 1.  
  * @param  FLAG: specifies the flag to clear.
  *			It can be any combination of the following values:
  *          @arg ADC_FLAG_EOI(End of ADC initialization)    
  *          @arg ADC_FLAG_EOSP(End of sampling phase flag)  
  *          @arg ADC_FLAG_EOC(End of channel conversion flag)
  *          @arg ADC_FLAG_EOG(End of conversion group flag)  
  *          @arg ADC_FLAG_DOVR(ADC data overrun flag)
  *          @arg ADC_FLAG_WDEVT(analog watchdog event flag)  
  * @return None
  */
#define __ADC_FLAG_CLEAR(ADCx, FLAG)			((ADCx)->STAT = FLAG)

/**
  * @fn void adc_def_init(adc_reg_t* ptr_adc)
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc_def_init(adc_reg_t* ptr_adc);

/* Initialization and Configuration functions *********************************/ 

/**
  * @fn void adc_init(adc_reg_t* ptr_adc, adc_config_t* ptr_config)
  * @brief  Initializes the ADCx peripheral according to the specified parameters.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @param  ptr_config: pointer to an adc_config_t structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @return None
  */
void adc_init(adc_reg_t* ptr_adc, adc_config_t* ptr_config);

/**
  * @fn void adc_config_struct_init(adc_config_t* ptr_config)
  * @brief  Fills each ptr_config member with its default value.
  * @param  ptr_config: pointer to an adc_config_t structure which will be initialized.
  * @return None
  */
void adc_config_struct_init(adc_config_t* ptr_config);

/* Power saving functions *****************************************************/
/**
  * @fn void adc_watchdog_channel_select(adc_reg_t* ptr_adc, uint32_t value)
  * @brief  Selection the analog watchdog monitor channel.
  * @note   This is only available for CS32F036, CS32F03X-RA devices.    
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @param  value: the ADC channel to configure for the analog watchdog.
  *         It can be a values between ADC_WATCHDOG_CHANNEL_0 ~ ADC_WATCHDOG_CHANNEL_18  
  *          (ADC Channel1 ~ ADC Channel18).
  * @note   The channel selected on the WDGCHAN must be also set into the CHANSEL register.     
  * @return None
  */
void adc_watchdog_channel_select(adc_reg_t* ptr_adc, uint32_t value);

/* Channels Configuration functions *******************************************/

/**
  * @fn void adc_channel_config(adc_reg_t* ptr_adc, uint32_t channel, uint32_t time)
  * @brief  Selection ADC conversion channel and its sampling time.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @param  channel: the ADC channel to configure , it can be any combination of the following values:
  *          @arg ADC_CONV_CHANNEL_0(ADC Channel0 selected)
  *          @arg ADC_CONV_CHANNEL_1(ADC Channel1 selected)
  *          @arg ADC_CONV_CHANNEL_2(ADC Channel2 selected)
  *          @arg ADC_CONV_CHANNEL_3(ADC Channel3 selected)
  *          @arg ADC_CONV_CHANNEL_4(ADC Channel4 selected)
  *          @arg ADC_CONV_CHANNEL_5(ADC Channel5 selected)
  *          @arg ADC_CONV_CHANNEL_6(ADC Channel6 selected)
  *          @arg ADC_CONV_CHANNEL_7(ADC Channel7 selected)
  *          @arg ADC_CONV_CHANNEL_8(ADC Channel8 selected)
  *          @arg ADC_CONV_CHANNEL_9(ADC Channel9 selected)
  *          @arg ADC_CONV_CHANNEL_10(ADC Channel0 selected)
  *          @arg ADC_CONV_CHANNEL_11(ADC Channel1 selected)
  *          @arg ADC_CONV_CHANNEL_12(ADC Channel2 selected)
  *          @arg ADC_CONV_CHANNEL_13(ADC Channel3 selected)
  *          @arg ADC_CONV_CHANNEL_14(ADC Channel4 selected)
  *          @arg ADC_CONV_CHANNEL_15(ADC Channel5 selected)
  *          @arg ADC_CONV_CHANNEL_16(ADC Channel6 selected)
  *          @arg ADC_CONV_CHANNEL_17(ADC Channel7 selected)
  *          @arg ADC_CONV_CHANNEL_18(ADC Channel8 selected) 
  * @param  time: The sample time value to be set. It can be one of the following values:
  *          @arg ADC_SAMPLE_TIMES_1_5(Sample time equal to 1.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_7_5(Sample time equal to 7.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_13_5(Sample time equal to 13.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_28_5(Sample time equal to 28.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_41_5(Sample time equal to 41.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_55_5(Sample time equal to 55.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_71_5(Sample time equal to 71.5 cycles)
  *          @arg ADC_SAMPLE_TIMES_239_5(Sample time equal to 239.5 cycles)
  * @return None
  */
void adc_channel_config(adc_reg_t* ptr_adc, uint32_t channel, uint32_t time);

/**
  * @fn uint32_t adc_calibration_value_get(adc_reg_t* ptr_adc)
  * @brief  Active the Calibration operation for the selected ADC, the Calibration can be 
  *         initiated only when ADC is still in the reset configuration (ADCON must be equal to 0).    
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return ADC Calibration factor 
  */
uint32_t adc_calibration_value_get(adc_reg_t* ptr_adc);

/**
  * @fn void adc_conversion_start(adc_reg_t* ptr_adc)
  * @brief  Start Conversion for the selected ADC channels.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc_conversion_start(adc_reg_t* ptr_adc);

/**
  * @fn void adc_conversion_stop(adc_reg_t* ptr_adc)
  * @brief  Stop the on going conversions for the selected ADC. When ADSTOP is set, any on going
  *         conversion is aborted, and the ADC data register is not updated with current conversion.    
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc_conversion_stop(adc_reg_t* ptr_adc);

/**
  * @fn void adc_dma_mode_set(adc_reg_t* ptr_adc, uint32_t mode)
  * @brief  Enables or disables the ADC DMA request after last transfer (Single-ADC mode)
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @param  mode: the ADC channel to configure, it can be
  *          @arg ADC_DMA_MODE_SINGLE(DMA single mode)
  *          @arg ADC_DMA_MODE_CIRCULAR (DMA circular mode)
  *  @return None
  */
void adc_dma_mode_set(adc_reg_t* ptr_adc, uint32_t mode);



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

