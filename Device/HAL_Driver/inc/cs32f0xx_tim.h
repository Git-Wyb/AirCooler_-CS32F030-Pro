/**
  * @file    cs32f0xx_tim.h
  * @brief   This file contains all the functions prototypes for the TIM 
  *          firmware library. 
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_TIM_H__
#define __CS32F0XX_TIM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 
  
/** @defgroup TIM_Exported_Constants
  * @{
  */

/** 
  * @struct timer_config_t  
  * @brief TIM Time Base Init structure definition
  */
typedef struct
{
    uint16_t predivider;  		//!< Specifies the prescaler value used to divide the TIM clock( between 0x0000 and 0xFFFF).
    uint16_t count_mode;   		//!< Specifies the counter mode
    uint32_t period;  			//!< Specifies the period value to be loaded (between 0x0000 and 0xFFFF)  
    uint16_t clk_division; 		//!< Specifies the clock division
    uint8_t repeate_count; 		//!< Specifies the repetition counter value(only for TIM1, between 0x00 and 0xFF)
    uint8_t reserved0;
} tim_base_t;       

/** 
  * @struct tim_choc_t  
  * @brief  TIM Output Compare Init structure definition  
  */
typedef struct
{
	uint16_t channel;
    uint16_t mode;        		//!< Specifies the TIM mode
    uint16_t output_state;     	//!< Specifies the TIM Output Compare state
    uint16_t output_state_n;   	//!< Specifies the TIM complementary Output Compare state ( only for TIM1)
    uint16_t reserved0;
    uint32_t pulse;      		//!< Specifies the pulse value to be loaded into the Capture Compare Value Register                                   
    uint16_t polarity;  		//!< Specifies the output polarity
    uint16_t polarity_n;		//!< Specifies the complementary output polarity (only for TIM1)                            
    uint16_t idle_state;       	//!< Specifies the TIM Output Compare pin state during Idle state (only for TIM1)                                 
    uint16_t idle_state_n;     	//!< Specifies the TIM Output Compare pin state during Idle state (only for TIM1)
} tim_choc_t;

/** 
  * @struct timer_capture_t  
  * @brief TIM Input Capture Init structure definition  
  */
typedef struct
{
    uint16_t channel;     		//!< Specifies the TIM channel
    uint16_t polarity;   		//!< Specifies the active edge of the input signal
    uint16_t select;     		//!< Specifies the input capure selection
    uint16_t predivider;  		//!< Specifies the input capture prescaler
    uint16_t filter;     		//!< Specifies the input capture filter (between 0x0 and 0xF)
}tim_chic_t;

/** 
  * @struct tim_protect_t  
  * @brief  TIMx CHOPR (channel output protect register) structure definition (used with TIM1)
  */
typedef struct
{
    uint16_t run_offstate;  	//!< Specifies the Off-State selection used in Run mode
    uint16_t idle_offstate; 	//!< Specifies the Off-State used in Idle state
    uint16_t lock_level;    	//!< Specifies the LOCK level parameters
    uint16_t dead_time;     	//!< Specifies the delay time between the switch off and on of the outputs (between 0x00 and 0xFF).                                     
    uint16_t break_flag;    	//!< Specifies whether the TIM Break input is enabled or not
    uint16_t break_polarity;	//!< Specifies the TIM Break Input pin polarity
    uint16_t auto_output;   	//!< Specifies whether the TIM Automatic Output feature is enabled or not
}tim_protect_t;

  
/** 
  * @brief check all TIMx(1,2,3,6,7,14,15,16,17) definition 
  */
#define TIM_ALL_TIMx_CHECK(value) 				(((value) == TIM1) || ((value) == TIM2)  || \
												((value) == TIM3)  || ((value) == TIM6)  || \
												((value) == TIM14) || ((value) == TIM15) || \
                                   				((value) == TIM16) || ((value) == TIM17)) 
                                   				

/** 
  * @brief check list1 TIM1 definition 
  */
#define TIM_LIST1_TIMx_CHECK(value)  			((value) == TIM1)

/** 
  * @brief check list2 TIMx(1,15,16,17) definition 
  */
#define TIM_LIST2_TIMx_CHECK(value)    			(((value) == TIM1)  || ((value) == TIM15) || \
                                        		((value) == TIM16) || ((value) == TIM17))

/** 
  * @brief check list3 TIMx(1,2,3) definition 
  */
#define TIM_LIST3_TIMx_CHECK(value) 			(((value) == TIM1) || ((value) == TIM2) || \
												((value) == TIM3)) 
                                      

/** 
  * @brief check list4 TIMx(1,2,3,14,15,16,17) definition 
  */
#define TIM_LIST4_TIMx_CHECK(value) 			(((value) == TIM1)  || ((value) == TIM2) || \
												((value) == TIM3)  || ((value) == TIM14) || \
												((value) == TIM15) || ((value) == TIM16) || \
                                     			((value) == TIM17))
/** 
  * @brief check list5 TIMx(1,2,3,15,16,17) definition 
  */
#define TIM_LIST5_TIMx_CHECK(value) 			(((value) == TIM1)  || ((value) == TIM2) || \
												((value) == TIM3) || ((value) == TIM15)  || \
												((value) == TIM16) || ((value) == TIM17))
                                                                         
/** 
  * @brief check list6 TIMx(1,2,3,15) definition 
  */
#define TIM_LIST6_TIMx_CHECK(value) 			(((value) == TIM1) || ((value) == TIM2)	 || \
                                     			((value) == TIM3) || ((value) == TIM15))                                                                         
/** 
  * @brief check list7 TIMx(1,2,3,6,7,14) definition 
  */
#define TIM_LIST7_TIMx_CHECK(value)  			(((value) == TIM1) || ((value) == TIM2)	 || \
												((value) == TIM3) || ((value) == TIM6)	 || \
												((value) == TIM14))                                                                                                                 
/** 
  * @brief check list8 TIMx(1,2,3,14) definition 
  */
#define TIM_LIST8_TIMx_CHECK(value)  			(((value) == TIM1) || ((value) == TIM2)	 || \
                                      			((value) == TIM3) || ((value) == TIM14))
/** 
  * @brief check list9 TIMx(1,2,3,6,7,15) definition 
  */
#define TIM_LIST9_TIMx_CHECK(value)  			(((value) == TIM1) || ((value) == TIM2)	 || \
												((value) == TIM3) || ((value) == TIM6)	 || \
												((value) == TIM15))
/** 
  * @brief check list4 TIMx(1,2,3,6,7,15,16,17) definition 
  */
#define TIM_LIST10_TIMx_CHECK(value) 			(((value) == TIM1) || ((value) == TIM2)	 || \
												((value) == TIM3)  || ((value) == TIM6)	 || \
												((value) == TIM15) || ((value) == TIM16) || \
                                      		    ((value) == TIM17))
/** 
  * @brief check list4 TIM14 definition 
  */
#define TIM_LIST11_TIMx_CHECK(value)  			((value) == TIM14)                                    

/**
  * @brief TIM channel definition
  */ 
#define TIM_CHANNEL_1							((uint8_t)0x00)		//!< Specifies the TIMx channel 1, for TIM1/2/3/14/15/16/17
#define TIM_CHANNEL_2							((uint8_t)0x01)		//!< Specifies the TIMx channel 2, for TIM1/2/3/15.  
#define TIM_CHANNEL_3							((uint8_t)0x02)		//!< Specifies the TIMx channel 3, for TIM1/2/3.
#define TIM_CHANNEL_4							((uint8_t)0x03)		//!< Specifies the TIMx channel 4, for TIM1/2/3.

#define TIM_ALL_CHANNEL_CHECK(ch) 				(((ch) == TIM_CHANNEL_1) || ((ch) == TIM_CHANNEL_2) || \
                                      			((ch) == TIM_CHANNEL_3) || ((ch) == TIM_CHANNEL_4))
                                      
#define TIM_COMPLEMENTARY_CHANNEL_CHECK(ch) 	(((ch) == TIM_CHANNEL_1) || ((ch) == TIM_CHANNEL_2) || \
                                            	((ch) == TIM_CHANNEL_3))


/**
  * @brief TIM Channel x output compare mode selection(forced active) definition
  */
#define TIM_CHxOCMSEL_FORCED_ACTIVE            	((uint16_t)0x0050)
#define TIM_CHxOCMSEL_FORCED_INACTIVE          	((uint16_t)0x0040)

#define TIM_CHxOCMSEL_FORCED_CHECK(flag) 		(((flag) == TIM_CHxOCMSEL_FORCED_ACTIVE) || ((flag) == TIM_CHxOCMSEL_FORCED_INACTIVE))

/**
  * @brief TIM Channelx output compare mode selection definition
  */
#define TIM_CHxOCMSEL_TIMING                  	((uint16_t)0x0000)
#define TIM_CHxOCMSEL_ACTIVE                  	((uint16_t)0x0010)
#define TIM_CHxOCMSEL_INACTIVE                	((uint16_t)0x0020)
#define TIM_CHxOCMSEL_TOGGLE                  	((uint16_t)0x0030)
#define TIM_CHxOCMSEL_PWM1                    	((uint16_t)0x0060)
#define TIM_CHxOCMSEL_PWM2                    	((uint16_t)0x0070)

#define TIM_CHxOCMSEL_CHECK(value) 				(((value) == TIM_CHxOCMSEL_TIMING) || ((value) == TIM_CHxOCMSEL_ACTIVE)		|| \
                                    			((value) == TIM_CHxOCMSEL_INACTIVE) || ((value) == TIM_CHxOCMSEL_TOGGLE)	|| \
                                    			((value) == TIM_CHxOCMSEL_PWM1) || ((value) == TIM_CHxOCMSEL_PWM2))
                              
#define TIM_ALL_CHxOCMSEL_CHECK(value) 			(((value) == TIM_CHxOCMSEL_TIMING) || ((value) == TIM_CHxOCMSEL_ACTIVE)		|| \
                                        		((value) == TIM_CHxOCMSEL_INACTIVE)  || ((value) == TIM_CHxOCMSEL_TOGGLE)	|| \
                                        		((value) == TIM_CHxOCMSEL_PWM1) || ((value) == TIM_CHxOCMSEL_PWM2)			|| \
                                        		((value) == TIM_CHxOCMSEL_FORCED_ACTIVE) || ((value) == TIM_CHxOCMSEL_FORCED_INACTIVE))

/** 
  * @brief TIM Single pulse  mode definition
  */
#define TIM_PULSE_MODE_SINGLE           		((uint16_t)0x0008) //!< Specifies the TIMx pulse mode (single)
#define TIM_PULSE_MODE_REPETITIVE       		((uint16_t)0x0000) //!< Specifies the TIMx pulse mode (repeititive)

#define TIM_PULSE_MODE_CHECK(value) 			(((value) == TIM_PULSE_MODE_SINGLE) || ((value) == TIM_PULSE_MODE_REPETITIVE))                               
                                     
/** 
  * @brief TIM_Clock_Division_CKD definition
  */
#define TIM_CKDIV_DIV1                       	((uint16_t)0x0000) //!< Specified the TIMx clock division factor is 1
#define TIM_CKDIV_DIV2                       	((uint16_t)0x0100) //!< Specified the TIMx clock division factor is 2
#define TIM_CKDIV_DIV4                       	((uint16_t)0x0200) //!< Specified the TIMx clock division factor is 4

#define TIM_CKDIV_CHECK(div) 					(((div) == TIM_CKDIV_DIV1) || ((div) == TIM_CKDIV_DIV2) || \
                              					((div) == TIM_CKDIV_DIV4))

/** 
  * @brief TIMx count pattern definition
  */
#define TIM_COUNT_PATTERN_UP                   	((uint16_t)0x0000) //!< Specifies the TIMx count pattern (count up)
#define TIM_COUNT_PATTERN_DOWN                 	((uint16_t)0x0010) //!< Specifies the TIMx count pattern (count down)
#define TIM_COUNT_PATTERN_CENTER_ALIGNED1      	((uint16_t)0x0020) //!< Specifies the TIMx count pattern (center aligned 1)
#define TIM_COUNT_PATTERN_CENTER_ALIGNED2      	((uint16_t)0x0040) //!< Specifies the TIMx count pattern (center aligned 2)
#define TIM_COUNT_PATTERN_CENTER_ALIGNED3      	((uint16_t)0x0060) //!< Specifies the TIMx count pattern (center aligned 3)

#define TIM_COUNT_PATTERN_CHECK(value)      	(((value) == TIM_COUNT_PATTERN_UP)   || \
                                             	((value) == TIM_COUNT_PATTERN_DOWN) || \
                                             	((value) == TIM_COUNT_PATTERN_CENTER_ALIGNED1) || \
                                             	((value) == TIM_COUNT_PATTERN_CENTER_ALIGNED2) || \
                                             	((value) == TIM_COUNT_PATTERN_CENTER_ALIGNED3))

/** 
  * @brief TIMx channelx capture compare polarity definition
  */
#define TIM_CHxCCP_POLARITY_HIGH                ((uint16_t)0x0000) //!< Specifies the caputure compare polarity is high level 
#define TIM_CHxCCP_POLARITY_LOW                 ((uint16_t)0x0002) //!< Specifies the caputure compare polarity is low level

#define TIM_CHxCCP_POLARITY_CHECK(polarity) 	(((polarity) == TIM_CHxCCP_POLARITY_HIGH) || \
                                             	((polarity) == TIM_CHxCCP_POLARITY_LOW))

/** 
  * @brief TIM channelx complementary capture compare  polarity definition
  */
#define TIM_CHxNCCP_POLARITY_HIGH               ((uint16_t)0x0000) //!< Specifies the complementary caputure compare polarity is high level 
#define TIM_CHxNCCP_POLARITY_LOW                ((uint16_t)0x0008) //!< Specifies the complementary caputure compare polarity is low level

#define TIM_CHxNCCP_POLARITY_CHECK(flag) 		(((flag) == TIM_CHxNCCP_POLARITY_HIGH) || ((flag) == TIM_CHxNCCP_POLARITY_LOW))
                                       
/** 
  * @brief TIM channel output compare state definition
  */

#define TIM_CHx_OUTPUT_DISABLE            		((uint16_t)0x0000) //!< Disable output compare state 
#define TIM_CHx_OUTPUT_ENABLE             		((uint16_t)0x0001) //!< Enable output compare state 

#define TIM_CHx_OUTPUT_CHECK(flag) 				(((flag) == TIM_CHx_OUTPUT_DISABLE) || ((flag) == TIM_CHx_OUTPUT_ENABLE)) 
                                   
/**
  * @brief TIM CHxNCCEN (channel complementary capture compare enable) definition
  */
#define TIM_CHxNCCEN_DISABLE           			((uint16_t)0x0000) //!< Disable complementary caputure compare state
#define TIM_CHxNCCEN_ENABLE            			((uint16_t)0x0004) //!< Enable complementary caputure compare state 

#define TIM_CHxNCCEN_CHECK(state) 				(((state) == TIM_CHxNCCEN_DISABLE) || ((state) == TIM_CHxNCCEN_ENABLE))

/** 
  * @brief TIM channelx capture compare state definition
  */
#define TIM_CHxCC_ENABLE                  		((uint16_t)0x0001) //!< Enable caputure compare state 
#define TIM_CHxCC_DISABLE                 		((uint16_t)0x0000) //!< Disable capture compare state 

#define TIM_CHxCC_STATE_CHECK(flag) 			(((flag) == TIM_CHxCC_ENABLE) || ((flag) == TIM_CHxCC_DISABLE))
                         
/** 
  * @brief TIM channelx complementary capture compare state definition
  */
#define TIM_CHxNCC_ENABLE                     	((uint16_t)0x0004) //!< Enable complementary caputure compare state 
#define TIM_CHxNCC_DISABLE                    	((uint16_t)0x0000) //!< Disable complementary caputure compare state 

#define TIM_CHxNCC_STATE_CHECK(value) 			(((value) == TIM_CHxNCC_ENABLE) || ((value) == TIM_CHxNCC_DISABLE))
                           
/** 
  * @brief TIM Break input enable/disable definition
  */
#define TIM_BREAK_EANBLE          				((uint16_t)0x1000) //!< Enable break input 
#define TIM_BREAK_DISABLE         				((uint16_t)0x0000) //!< Disbale break input 

#define TIM_BREAK_CHECK(falg) 					(((falg) == TIM_BREAK_EANBLE) || ((falg) == TIM_BREAK_DISABLE))
                                   
/** 
  * @brief TIM Break Polarity definition
  */
#define TIM_BREAK_POLARITY_LOW              	((uint16_t)0x0000) //!< Specifies the polarity is low level 
#define TIM_BREAK_POLARITY_HIGH             	((uint16_t)0x2000) //!< Specifies the polarity is high level 

#define TIM_BREAK_POLARITY_CHECK(flag) 			(((flag) == TIM_BREAK_POLARITY_LOW) || \
                                        		((flag) == TIM_BREAK_POLARITY_HIGH))
                                         
/** 
  * @brief TIM CHOPAEN(Channel output pad auto enable) definition
  */
#define TIM_CHOPAEN_ENABLE         				((uint16_t)0x4000) //!< Channel output pad auto enable 
#define TIM_CHOPAEN_DISABLE        				((uint16_t)0x0000) //!< Channel output pad auto disable 

#define TIM_CHOPAEN_CHECK(flag) 				(((flag) == TIM_CHOPAEN_ENABLE) || ((flag) == TIM_CHOPAEN_DISABLE))
                                              
/** 
  * @brief TIM lock level control definition
  */
#define TIM_LOCK_LEVEL_OFF                  	((uint16_t)0x0000) //!< Specifies no lock level 
#define TIM_LOCK_LEVEL_1                    	((uint16_t)0x0100) //!< Specifies lock level 1
#define TIM_LOCK_LEVEL_2                    	((uint16_t)0x0200) //!< Specifies lock level 2
#define TIM_LOCK_LEVEL_3                    	((uint16_t)0x0300) //!< Specifies lock level 3

#define TIM_LOCK_LEVEL_CHECK(level) 			(((level) == TIM_LOCK_LEVEL_OFF) || ((level) == TIM_LOCK_LEVEL_1) || \
                                     			((level) == TIM_LOCK_LEVEL_2)    || ((level) == TIM_LOCK_LEVEL_3))       

/** 
  * @brief Idle mode off-state control definition
  */
#define TIM_IDLEOS_ENABLE               		((uint16_t)0x0400) //!< Idel mode off-state enable
#define TIM_IDLEOS_DISABLE              		((uint16_t)0x0000) //!< Idel mode off-state disable 

#define TIM_IDLEOS_CHECK(state) 				(((state) == TIM_IDLEOS_ENABLE) || ((state) == TIM_IDLEOS_DISABLE))

/** 
  * @brief Run mode off-state control definition
  */
#define TIM_RUNOS_ENABLE               			((uint16_t)0x0800) //!< Run mode off-state enable 
#define TIM_RUNOS_DISABLE              			((uint16_t)0x0000) //!< Run mode off-state disable 

#define TIM_RUNOS_CHECK(flag) 					(((flag) == TIM_RUNOS_ENABLE) || ((flag) == TIM_RUNOS_DISABLE))                               

/** 
  * @brief IVOx (Idle value output of channelx) definition 
  */
#define TIM_IVOx_SET                			((uint16_t)0x0100) //!< Set idle output value of channelx compare
#define TIM_IVOx_RESET              			((uint16_t)0x0000) //!< Reste idle output value of channelx compare 

#define TIM_IVOx_CHECK(flag) 					(((flag) == TIM_IVOx_SET) || ((flag) == TIM_IVOx_RESET)) 
                                    
/**
  * @brief IVOxN (Idle value output of channelx complementary)  definition
  */
#define TIM_IVOxN_SET               			((uint16_t)0x0200) //!< Set idle output value of channelx complementary compare 
#define TIM_IVOxN_RESET             			((uint16_t)0x0000) //!< Reset idle output value of channelx complementary compare 

#define TIM_IVOxN_CHECK(flag) 					(((flag) == TIM_IVOxN_SET) || ((flag) == TIM_IVOxN_RESET))
                                     
/**   
  * @brief TIM channel input capture polarity definition
  */
#define TIM_CHxIC_POLARITY_RISING             	((uint16_t)0x0000) //!< Specifies channelx input caputure polarity (edge rising)
#define TIM_CHxIC_POLARITY_FALLING            	((uint16_t)0x0002) //!< Specifies channelx input caputure polarity (edge falling)
#define TIM_CHxIC_POLARITY_BOTH_EDGE          	((uint16_t)0x000A) //!< Specifies channelx input caputure polarity (both edges)

#define TIM_CHxIC_POLARITY_CHECK(value) 		(((value) == TIM_CHxIC_POLARITY_RISING)  || \
                                         		((value) == TIM_CHxIC_POLARITY_FALLING) || \
                                         		((value) == TIM_CHxIC_POLARITY_BOTH_EDGE)) 

/** 
  * @brief TIM channel Input Capture Selection definition 
  */
#define TIM_CHIC_SEL_DIRECT_INTR           		((uint16_t)0x0001) //!< TIM input 1, 2, 3 or 4 is selected to beconnected to IC1, IC2, IC3 or IC4, respectively                                                                    
#define TIM_CHIC_SEL_INDIRECT_INTR         		((uint16_t)0x0002) //!< TIM Input 1, 2, 3 or 4 is selected to beconnected to IC2, IC1, IC4 or IC3, respectively                                                                   
#define TIM_CHIC_SEL_TRC                   		((uint16_t)0x0003) //!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC

#define TIM_CHIC_SEL_CHECK(value) 				(((value) == TIM_CHIC_SEL_DIRECT_INTR)   || \
                                   				((value) == TIM_CHIC_SEL_INDIRECT_INTR) || \
                                   				((value) == TIM_CHIC_SEL_TRC))

/** 
  * @brief TIM channel Input Capture pre-divide definition 
  */
#define TIM_CHIC_PREDIVIDE_DIV1               	((uint16_t)0x0000) //!< Capture performed each time an edge is detected on the capture input
#define TIM_CHIC_PREDIVIDE_DIV2               	((uint16_t)0x0004) //!< Capture performed once every 2 events
#define TIM_CHIC_PREDIVIDE_DIV4           		((uint16_t)0x0008) //!< Capture performed once every 4 events
#define TIM_CHIC_PREDIVIDE_DIV8              	((uint16_t)0x000C) //!< Capture performed once every 8 events

#define TIM_CHIC_PREDIVIDE_CHECK(value) 		(((value) == TIM_CHIC_PREDIVIDE_DIV1) || \
                                         		((value) == TIM_CHIC_PREDIVIDE_DIV2) || \
                                         		((value) == TIM_CHIC_PREDIVIDE_DIV4) || \
                                         		((value) == TIM_CHIC_PREDIVIDE_DIV8))

/** 
  * @brief TIM interrupt Event Source definition
  */
#define TIM_EVENT_SOURCE_UPDATE             	((uint16_t)0x0001) //!< Specifies interrupt event source (update) 
#define TIM_EVENT_SOURCE_CH1                	((uint16_t)0x0002) //!< Specifies interrupt event source (channel1)
#define TIM_EVENT_SOURCE_CH2                	((uint16_t)0x0004) //!< Specifies interrupt event source (channel2)
#define TIM_EVENT_SOURCE_CH3                	((uint16_t)0x0008) //!< Specifies interrupt event source (channel3)
#define TIM_EVENT_SOURCE_CH4                	((uint16_t)0x0010) //!< Specifies interrupt event source (channel4)
#define TIM_EVENT_SOURCE_COM                	((uint16_t)0x0020) //!< Specifies interrupt event source (com event)
#define TIM_EVENT_SOURCE_TRIGGER            	((uint16_t)0x0040) //!< Specifies interrupt event source (trigger)
#define TIM_EVENT_SOURCE_BREAK              	((uint16_t)0x0080) //!< Specifies interrupt event source (break)

#define TIM_EVENT_SOURCE_CHECK(value) 			((((value) & (uint16_t)0xFF00) == 0x0000) && ((value) != 0x0000))

/**   
  * @brief TIM DMA base address definition
  */
#define TIM_DMA_BASE_CTR1                    	((uint16_t)0x0000) //!< Specifies TIMx DMA start address (CTR1)
#define TIM_DMA_BASE_CTR2                    	((uint16_t)0x0001) //!< Specifies TIMx DMA start address (CTR2)
#define TIM_DMA_BASE_SMCFG                   	((uint16_t)0x0002) //!< Specifies TIMx DMA start address (SMCFG)
#define TIM_DMA_BASE_DIEN                    	((uint16_t)0x0003) //!< Specifies TIMx DMA start address (DIEN)
#define TIM_DMA_BASE_STS                     	((uint16_t)0x0004) //!< Specifies TIMx DMA start address (STS)
#define TIM_DMA_BASE_SWEGR                   	((uint16_t)0x0005) //!< Specifies TIMx DMA start address (SWEGR)
#define TIM_DMA_BASE_CH12CFGR                	((uint16_t)0x0006) //!< Specifies TIMx DMA start address (CH12CFGR)
#define TIM_DMA_BASE_CH34CFGR                	((uint16_t)0x0007) //!< Specifies TIMx DMA start address (CH34CFGR)
#define TIM_DMA_BASE_CCCTR                   	((uint16_t)0x0008) //!< Specifies TIMx DMA start address (CCCTR )
#define TIM_DMA_BASE_CNT                     	((uint16_t)0x0009) //!< Specifies TIMx DMA start address (CNT)
#define TIM_DMA_BASE_PDIV                    	((uint16_t)0x000A) //!< Specifies TIMx DMA start address (PDIV)
#define TIM_DMA_BASE_UVAL                    	((uint16_t)0x000B) //!< Specifies TIMx DMA start address (UVAL)
#define TIM_DMA_BASE_UVALREP                 	((uint16_t)0x000C) //!< Specifies TIMx DMA start address (UVALREP)
#define TIM_DMA_BASE_CH1CCVAL                	((uint16_t)0x000D) //!< Specifies TIMx DMA start address (CH1CCVAL)
#define TIM_DMA_BASE_CH2CCVAL                	((uint16_t)0x000E) //!< Specifies TIMx DMA start address (CH2CCVAL)
#define TIM_DMA_BASE_CH3CCVAL                	((uint16_t)0x000F) //!< Specifies TIMx DMA start address (CH3CCVAL)
#define TIM_DMA_BASE_CH4CCVAL                	((uint16_t)0x0010) //!< Specifies TIMx DMA start address (CH4CCVAL)
#define TIM_DMA_BASE_CHOPR                   	((uint16_t)0x0011) //!< Specifies TIMx DMA start address (CHOPR)
#define TIM_DMA_BASE_DMAACR                  	((uint16_t)0x0012) //!< Specifies TIMx DMA start address (DMAACR)
#define TIM_DMA_BASE_REMAP                   	((uint16_t)0x0013) //!< Specifies TIMx DMA start address (REMAP)

#define TIM_DMA_BASE_CHECK(value) 				(((value) == TIM_DMA_BASE_CTR1)     ||  ((value) == TIM_DMA_BASE_CTR2)     || \
                                   				((value) == TIM_DMA_BASE_SMCFG)    ||  ((value) == TIM_DMA_BASE_DIEN)     || \
                                   				((value) == TIM_DMA_BASE_STS)      ||  ((value) == TIM_DMA_BASE_SWEGR)    || \
                                   				((value) == TIM_DMA_BASE_CH12CFGR) ||  ((value) == TIM_DMA_BASE_CH34CFGR) || \
                                   				((value) == TIM_DMA_BASE_CCCTR)    ||  ((value) == TIM_DMA_BASE_CNT)      || \
                                   				((value) == TIM_DMA_BASE_PDIV)     ||  ((value) == TIM_DMA_BASE_UVAL)     || \
                                   				((value) == TIM_DMA_BASE_UVALREP)  ||  ((value) == TIM_DMA_BASE_CH1CCVAL) || \
                                   				((value) == TIM_DMA_BASE_CH2CCVAL) ||  ((value) == TIM_DMA_BASE_CH3CCVAL) || \
                                   				((value) == TIM_DMA_BASE_CH4CCVAL) ||  ((value) == TIM_DMA_BASE_CHOPR)    || \
                                   				((value) == TIM_DMA_BASE_DMAACR)   ||  ((value) == TIM_DMA_BASE_REMAP)) 
                              
/**  
  * @brief TIM DMA transfer length definition
  */
#define TIM_DMA_TRANSFER_LEN_1BYTE           	((uint16_t)0x0000) //!< Specifies DMA transfre length is 1 byte
#define TIM_DMA_TRANSFER_LEN_2BYTES          	((uint16_t)0x0100) //!< Specifies DMA transfre length is 2 bytes
#define TIM_DMA_TRANSFER_LEN_3BYTES          	((uint16_t)0x0200) //!< Specifies DMA transfre length is 3 bytes
#define TIM_DMA_TRANSFER_LEN_4BYTES          	((uint16_t)0x0300) //!< Specifies DMA transfre length is 4 bytes
#define TIM_DMA_TRANSFER_LEN_5BYTES          	((uint16_t)0x0400) //!< Specifies DMA transfre length is 5 bytes
#define TIM_DMA_TRANSFER_LEN_6BYTES          	((uint16_t)0x0500) //!< Specifies DMA transfre length is 6 bytes
#define TIM_DMA_TRANSFER_LEN_7BYTES          	((uint16_t)0x0600) //!< Specifies DMA transfre length is 7 bytes
#define TIM_DMA_TRANSFER_LEN_8BYTES          	((uint16_t)0x0700) //!< Specifies DMA transfre length is 8 bytes
#define TIM_DMA_TRANSFER_LEN_9BYTES          	((uint16_t)0x0800) //!< Specifies DMA transfre length is 9 bytes
#define TIM_DMA_TRANSFER_LEN_10BYTES         	((uint16_t)0x0900) //!< Specifies DMA transfre length is 10 bytes
#define TIM_DMA_TRANSFER_LEN_11BYTES         	((uint16_t)0x0A00) //!< Specifies DMA transfre length is 11 bytes
#define TIM_DMA_TRANSFER_LEN_12BYTES         	((uint16_t)0x0B00) //!< Specifies DMA transfre length is 12 bytes
#define TIM_DMA_TRANSFER_LEN_13BYTES         	((uint16_t)0x0C00) //!< Specifies DMA transfre length is 13 bytes
#define TIM_DMA_TRANSFER_LEN_14BYTES         	((uint16_t)0x0D00) //!< Specifies DMA transfre length is 14 bytes
#define TIM_DMA_TRANSFER_LEN_15BYTES         	((uint16_t)0x0E00) //!< Specifies DMA transfre length is 15 bytes
#define TIM_DMA_TRANSFER_LEN_16BYTES         	((uint16_t)0x0F00) //!< Specifies DMA transfre length is 16 bytes
#define TIM_DMA_TRANSFER_LEN_17BYTES         	((uint16_t)0x1000) //!< Specifies DMA transfre length is 17 bytes
#define TIM_DMA_TRANSFER_LEN_18BYTES         	((uint16_t)0x1100) //!< Specifies DMA transfre length is 18 bytes

#define TIM_DMA_TRANSFER_LEN_CHECK(len)			(((len) == TIM_DMA_TRANSFER_LEN_1BYTE)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_2BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_3BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_4BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_5BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_6BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_7BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_8BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_9BYTES)  || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_10BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_11BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_12BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_13BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_14BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_15BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_16BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_17BYTES) || \
                                         		((len) == TIM_DMA_TRANSFER_LEN_18BYTES))

/** 
  * @brief TIM DMA source definition
  */
#define TIM_DMA_UPDATE                     		((uint16_t)0x0100) //!< Specifies DMA source (update)
#define TIM_DMA_CH1CC                      		((uint16_t)0x0200) //!< Specifies DMA source (channel 1)
#define TIM_DMA_CH2CC                      		((uint16_t)0x0400) //!< Specifies DMA source (channel 2)
#define TIM_DMA_CH3CC                      		((uint16_t)0x0800) //!< Specifies DMA source (channel 3)
#define TIM_DMA_CH4CC                      		((uint16_t)0x1000) //!< Specifies DMA source (channel 4)
#define TIM_DMA_CHCOM                      		((uint16_t)0x2000) //!< Specifies DMA source (com event)
#define TIM_DMA_TRIGGER                    		((uint16_t)0x4000) //!< Specifies DMA source (trigger)

#define TIM_DMA_SOURCE_CHECK(value) 			((((value) & (uint16_t)0x80FF) == 0x0000) && ((value) != 0x0000))

/**   
  * @brief TIM external trigger pre-divide definition
  */
#define TIM_EXT_TRG_PDIV_OFF              		((uint16_t)0x0000) //!< Specifies external trigger pre-divide OFF 
#define TIM_EXT_TRG_PDIV2                 		((uint16_t)0x1000) //!< External trigger frequency divided by 2
#define TIM_EXT_TRG_PDIV4                 		((uint16_t)0x2000) //!< External trigger frequency divided by 4
#define TIM_EXT_TRG_PDIV8                 		((uint16_t)0x3000) //!< External trigger frequency divided by 8

#define TIM_EXT_TRG_PDIV_CHECK(value) 			(((value) == TIM_EXT_TRG_PDIV_OFF) 	|| \
                                       			((value) == TIM_EXT_TRG_PDIV2)    	|| \
                                       			((value) == TIM_EXT_TRG_PDIV4)    	|| \
                                       			((value) == TIM_EXT_TRG_PDIV8))
/**  
  * @brief TIM internal trigger selection definition
  */
#define TIM_TRIGGER_SEL_ITR0                  	((uint16_t)0x0000) //!< Internal trigger 0
#define TIM_TRIGGER_SEL_ITR1                 	((uint16_t)0x0010) //!< Internal trigger 1
#define TIM_TRIGGER_SEL_ITR2                 	((uint16_t)0x0020) //!< Internal trigger 2
#define TIM_TRIGGER_SEL_ITR3                  	((uint16_t)0x0030) //!< Internal trigger 3
#define TIM_TRIGGER_SEL_EDGE                  	((uint16_t)0x0040) //!< TI1 edge detecting
#define TIM_TRIGGER_SEL_FILTER1               	((uint16_t)0x0050) //!< Filtered timer1 input 
#define TIM_TRIGGER_SEL_FILTER2              	((uint16_t)0x0060) //!< Filtered timer2 input 
#define TIM_TRIGGER_SEL_EXTERNAL				((uint16_t)0x0070) //!< External trigger input 

#define TIM_TRIGGER_SEL_CHECK(select) 			(((select) == TIM_TRIGGER_SEL_ITR0)	|| \
                                       			((select) == TIM_TRIGGER_SEL_ITR1) 	|| \
                                       			((select) == TIM_TRIGGER_SEL_ITR2) 	|| \
                                       			((select) == TIM_TRIGGER_SEL_ITR3) 	|| \
                                       			((select) == TIM_TRIGGER_SEL_EDGE) 	|| \
                                       			((select) == TIM_TRIGGER_SEL_FILTER1) || \
                                       			((select) == TIM_TRIGGER_SEL_FILTER2) || \
                                       			((select) == TIM_TRIGGER_SEL_EXTERNAL))

#define TIM_INTERNAL_TRIGGER_SEL_CHECK(select)	(((select) == TIM_TRIGGER_SEL_ITR0)	|| \
                                                ((select) == TIM_TRIGGER_SEL_ITR1) 	|| \
                                                ((select) == TIM_TRIGGER_SEL_ITR2)	|| \
                                                ((select) == TIM_TRIGGER_SEL_ITR3))

/** 
  * @brief TIMx External Clock Source definition
  */
#define TIM_TIMx_EXTlCLK1_SOURCE_TI1ED			((uint16_t)0x0040) //!< TI1 edge detecting
#define TIM_TIMx_EXTlCLK1_SOURCE_TI1      		((uint16_t)0x0050) //!< Filtered timer input 1
#define TIM_TIMx_EXTlCLK1_SOURCE_TI2      		((uint16_t)0x0060) //!< Filtered timer input 2

/** 
  * @brief TIM external trigger polarity definition
  */ 
#define TIM_EXT_TRG_POLARITY_INVERTED        	((uint16_t)0x8000) //!< Active at falling edge
#define TIM_EXT_TRG_POLARITY_NON_INVERTED    	((uint16_t)0x0000) //!< Active at rising edge 

#define TIM_EXT_TRG_POLARITY_CHECK(value) 		(((value) == TIM_EXT_TRG_POLARITY_INVERTED) || \
                                           		((value) == TIM_EXT_TRG_POLARITY_NON_INVERTED))                                     

/** 
  * @brief TIM pre-divider reload mode definition
  */
#define TIM_PDIV_MODE_UPDATE          			((uint16_t)0x0000) //!< Specifies pre-divider loaded at update event 
#define TIM_PDIV_MODE_IMMEDIATE       			((uint16_t)0x0001) //!< Specifies pre-divider loaded immediatly 

#define TIM_PDIV_MODE_CHECK(flag) 				(((flag) == TIM_PDIV_MODE_UPDATE) || \
                                   				((flag) == TIM_PDIV_MODE_IMMEDIATE))
                                         
/** 
  * @brief TIM Encoder mode definition 
  */
#define TIM_ENCODER_MODE_TI1                	((uint16_t)0x0001) //!< Specifies encoder mode: counter counts on TI1
#define TIM_ENCODER_MODE_TI2                	((uint16_t)0x0002) //!< Specifies encoder mode: counter counts on TI2
#define TIM_ENCODER_MODE_TI12               	((uint16_t)0x0003) //!< Specifies encoder mode: counter counts on both TI1 and TI2

#define TIM_ENCODER_MODE_CHECK(value) 			(((value) == TIM_ENCODER_MODE_TI1) 	|| \
                                      	 		((value) == TIM_ENCODER_MODE_TI2) 	||\
                                       			((value) == TIM_ENCODER_MODE_TI12))                                    
/**
  * @brief update request selection definition
  */
#define TIM_UPDATE_SEL_GLOBAL            		((uint16_t)0x0000) //!< Source of update is overrun, or UEG bit is set, or an update generated
#define TIM_UPDATE_SEL_REGULAR           		((uint16_t)0x0004) //!< Source of update is overrun

#define TIM_UPDATE_SEL_CHECK(flag) 				((((flag)) == TIM_UPDATE_SEL_GLOBAL) || (((flag)) == TIM_UPDATE_SEL_REGULAR))

/** 
  * @brief TIM CHxOC(channelx output compare) preload enable definition 
  */
#define TIM_CHxOC_PRELOAD_ENABLE          		((uint16_t)0x0008) //!< Enable channelx output reload
#define TIM_CHxOC_PRELOAD_DISABLE              	((uint16_t)0x0000) //!< Disable channelx output reload 

#define TIM_CHxOC_PRELOAD_CHECK(flag) 			(((flag) == TIM_CHxOC_PRELOAD_ENABLE) || ((flag) == TIM_CHxOC_PRELOAD_DISABLE))

/** 
  * @brief TIM CHxOC(channelx output compare) Fast enable definition 
  */
#define TIM_CHxOC_FAST_ENABLE                  	((uint16_t)0x0004) //!< Channelx output compare fast enable
#define TIM_CHxOC_FAST_DISABLE                 	((uint16_t)0x0000) //!< Channelx output compare fast disable 

#define TIM_CHxOC_FAST_CHECK(flag) 				(((flag) == TIM_CHxOC_FAST_ENABLE) || ((flag) == TIM_CHxOC_FAST_DISABLE))
                                     
/** 
  * @brief TIM CHxOC(channelx output compare) Clear enable definition 
  */
#define TIM_CHxOC_CLEAR_ENABLE					((uint16_t)0x0080) //!< Channelx output clear fast enable
#define TIM_CHxOC_CLEAR_DISABLE					((uint16_t)0x0000) //!< Channelx output clear fast disable 

#define TIM_CHxOC_CLEAR_CHECK(state) 			(((state) == TIM_CHxOC_CLEAR_ENABLE) || ((state) == TIM_CHxOC_CLEAR_DISABLE))
                                     
/** 
  * @brief TIM Trigger output source definition
  */
#define TIM_TRG_OUTPUT_SEL_RESET				((uint16_t)0x0000) //!< The UEG bit is used as the trigger output 
#define TIM_TRG_OUTPUT_SEL_ENABLE				((uint16_t)0x0010) //!< The CEN bit is usd as the trigger output 
#define TIM_TRG_OUTPUT_SEL_UPDATE				((uint16_t)0x0020) //!< The update event is used as the trigger output
#define TIM_TRG_OUTPUT_SEL_CH1OC				((uint16_t)0x0030) //!< The trigger output sends out a positive pulse when the CH1CCIF is set
#define TIM_TRG_OUTPUT_SEL_CH1OC_REF			((uint16_t)0x0040) //!< The CH1OCREF signal is used as the trigger output
#define TIM_TRG_OUTPUT_SEL_CH2OC_REF			((uint16_t)0x0050) //!< The CH2OCREF signal is used as the trigger output
#define TIM_TRG_OUTPUT_SEL_CH3OC_REF			((uint16_t)0x0060) //!< The CH3OCREF signal is used as the trigger output
#define TIM_TRG_OUTPUT_SEL_CH4OC_REF			((uint16_t)0x0070) //!< The CH4OCREF signal is used as the trigger output

#define TIM_TRG_OUTPUT_SEL_CHECK(source) 		(((source) == TIM_TRG_OUTPUT_SEL_RESET)	|| \
												((source) == TIM_TRG_OUTPUT_SEL_ENABLE)	|| \
												((source) == TIM_TRG_OUTPUT_SEL_UPDATE)	|| \
												((source) == TIM_TRG_OUTPUT_SEL_CH1OC)	|| \
												((source) == TIM_TRG_OUTPUT_SEL_CH1OC_REF) || \
												((source) == TIM_TRG_OUTPUT_SEL_CH2OC_REF) || \
												((source) == TIM_TRG_OUTPUT_SEL_CH3OC_REF) || \
												((source) == TIM_TRG_OUTPUT_SEL_CH4OC_REF))

/**  
  * @brief TIM slave mode definition
  */
#define TIM_SLAVE_MODE_RESET                	((uint16_t)0x0004) //!< Reinitialize the counter and trigger 
#define TIM_SLAVE_MODE_GATED                	((uint16_t)0x0005) //!< Enable the counter clock when the trigger signal is high 
#define TIM_SLAVE_MODE_TRIGGER              	((uint16_t)0x0006) //!< Start the counter at the rising edge of the trigger 
#define TIM_SLAVE_MODE_EXTERNAL1            	((uint16_t)0x0007) //!< Rising edge of the selected trigger clock the counter 

#define TIM_SLAVE_MODE_CHECK(value) 			(((value) == TIM_SLAVE_MODE_RESET)	|| \
												((value) == TIM_SLAVE_MODE_GATED)	|| \
												((value) == TIM_SLAVE_MODE_TRIGGER)	|| \
												((value) == TIM_SLAVE_MODE_EXTERNAL1))


/**
  * @brief TIM Master Slave Mode definition
  */
#define TIM_MASTER_SLAVE_MODE_ENABLE			((uint16_t)0x0080) //!< Enable TIMx master slave mode 
#define TIM_MASTER_SLAVE_MODE_DISABLE			((uint16_t)0x0000) //!< Disable TIMx msater slave mode 

#define TIM_MASTER_SLAVE_MODE_CHECK(value) 		(((value) == TIM_MASTER_SLAVE_MODE_ENABLE) || \
                                            	((value) == TIM_MASTER_SLAVE_MODE_DISABLE))

/** 
  * @brief check TIM channel input capture filer value 
  */
#define TIM_CHxIC_FILTER_CHECK(value) 			((value) <= 0xF) 

/** 
  * @brief check TIM external filer value 
  */
#define TIM_EXT_FILTER_CHECK(filter) 			((filter) <= 0xF)

/**  
  * @brief TIM OCREF Clear definition
  */
#define TIM_OCREF_CLEAR_ETRF          			((uint16_t)0x0008) //!< The OCREF clear is bonded with ETRF 
#define TIM_OCREF_CLEAR_CLR           			((uint16_t)0x0000) //!< The OCREF clear is bonded with CLR 

#define TIM_OCREF_CLEAR_CHECK(value) 			(((value) == TIM_OCREF_CLEAR_ETRF) || \
                                      			((value) == TIM_OCREF_CLEAR_CLR)) 

/**
  * @brief TIM14 remap definition
  */
#define TIM14_REMAP_PORT                      	((uint16_t)0x0000) //!< TIM14 channel 1 is connected to GPIO port
#define TIM14_REMAP_RTC_CLK                   	((uint16_t)0x0001) //!< TIM14 channel 1 is connected to RTC clock 
#define TIM14_REMAP_HXT_DIV32                 	((uint16_t)0x0002) //!< TIM14 channel 1 is connected to HXT/32 clock 
#define TIM14_REMAP_MCO                       	((uint16_t)0x0003) //!< TIM14 channel 1 is connected to MCO 

#define TIM14_REMAP_CHECK(value) 				(((value) == TIM14_REMAP_PORT)		|| \
                                  				((value) == TIM14_REMAP_RTC_CLK)   	|| \
                                  				((value) == TIM14_REMAP_HXT_DIV32) 	|| \
                                  				((value) == TIM14_REMAP_MCO))                                 

/** 
  * @brief TIM interrupt sources definition
  */
#define TIM_INTR_UPDATE                      	((uint16_t)0x0001) //!< Specifies update interrupt
#define TIM_INTR_CH1CC                       	((uint16_t)0x0002) //!< Specifies channel 1 interrupt
#define TIM_INTR_CH2CC                       	((uint16_t)0x0004) //!< Specifies channel 2 interrupt 
#define TIM_INTR_CH3CC                       	((uint16_t)0x0008) //!< Specifies channel 3 interrupt 
#define TIM_INTR_CH4CC                       	((uint16_t)0x0010) //!< Specifies channel 4 interrupt 
#define TIM_INTR_CHCOM                       	((uint16_t)0x0020) //!< Specifies com event interrupt 
#define TIM_INTR_TRIGGER                     	((uint16_t)0x0040) //!< Specifies trigger interrupt 
#define TIM_INTR_BREAK                       	((uint16_t)0x0080) //!< Specifies break interrupt 

/** 
  * @brief TIM Flag definition
  */
#define TIM_FLAG_UPDATE                    		((uint16_t)0x0001) //!< Update flag 
#define TIM_FLAG_CH1CC                     		((uint16_t)0x0002) //!< Channel 1 capture compare flag 
#define TIM_FLAG_CH2CC                     		((uint16_t)0x0004) //!< Channel 2 capture compare flag 
#define TIM_FLAG_CH3CC                     		((uint16_t)0x0008) //!< Channel 3 capture compare flag 
#define TIM_FLAG_CH4CC                     		((uint16_t)0x0010) //!< Channel 4 capture compare flag 
#define TIM_FLAG_CHCOM                     		((uint16_t)0x0020) //!< TIMx CHCOM flag 
#define TIM_FLAG_TRIGGER                   		((uint16_t)0x0040) //!< TIMx trigger flag 
#define TIM_FLAG_BREAK                     		((uint16_t)0x0080) //!< TIMx break flag 
#define TIM_FLAG_CH1ICOF                   		((uint16_t)0x0200) //!< Overcapture flag of channel 1 capture compare
#define TIM_FLAG_CH2ICOF                   		((uint16_t)0x0400) //!< Overcapture flag of channel 2 capture compare
#define TIM_FLAG_CH3ICOF                   		((uint16_t)0x0800) //!< Overcapture flag of channel 3 capture compare
#define TIM_FLAG_CH4ICOF                   		((uint16_t)0x1000) //!< Overcapture flag of channel 4 capture compare

/** 
  * @brief TIM function enable bits definition
  */
#define TIM_ENABLE_REG_PRELOAD_SHADOW			CTR2
#define TIM_ENABLE_REG_PRELOAD_UPDATE			CTR2
#define TIM_ENABLE_REG_UPDATE_DIS				CTR1
#define TIM_ENABLE_REG_UVAL_SHADOW				CTR1
#define TIM_ENABLE_REG_CH_OUTPUT				CHOPR
#define TIM_ENABLE_REG_DMA_REQUEST				CTR2
#define TIM_ENABLE_REG_XOR_INPUT				CTR2

/** 
  * @brief TIM function enable registers definition
  */
#define TIM_ENABLE_BIT_PRELOAD_SHADOW			TIM_CTR2_CHPSEN  
#define TIM_ENABLE_BIT_PRELOAD_UPDATE			TIM_CTR2_CHPUS   
#define TIM_ENABLE_BIT_UPDATE_DIS				TIM_CTR1_UPD     
#define TIM_ENABLE_BIT_UVAL_SHADOW				TIM_CTR1_UVALSEN 
#define TIM_ENABLE_BIT_CH_OUTPUT				TIM_CHOPR_CHOPEN 
#define TIM_ENABLE_BIT_DMA_REQUEST				TIM_CTR2_CHDMARS 
#define TIM_ENABLE_BIT_XOR_INPUT				TIM_CTR2_TI1XOR  

/** 
  * @brief TIM interrupt enable bits definition
  */
#define TIM_INTR_ENABLE_BIT_UPDATE				((uint16_t)0x0001) 	//!< Specifies update interrupt
#define TIM_INTR_ENABLE_BIT_CH1CC				((uint16_t)0x0002) 	//!< Specifies channel 1 interrupt
#define TIM_INTR_ENABLE_BIT_CH2CC				((uint16_t)0x0004) 	//!< Specifies channel 2 interrupt 
#define TIM_INTR_ENABLE_BIT_CH3CC				((uint16_t)0x0008) 	//!< Specifies channel 3 interrupt 
#define TIM_INTR_ENABLE_BIT_CH4CC				((uint16_t)0x0010) 	//!< Specifies channel 4 interrupt 
#define TIM_INTR_ENABLE_BIT_CHCOM				((uint16_t)0x0020) 	//!< Specifies com event interrupt 
#define TIM_INTR_ENABLE_BIT_TRIGGER				((uint16_t)0x0040) 	//!< Specifies trigger interrupt 
#define TIM_INTR_ENABLE_BIT_BREAK				((uint16_t)0x0080) 	//!< Specifies break interrupt 

/**
  * @}
  */ 


/**
  * @brief	Deinitializes the TIMx peripheral registers to their default reset values.
  * @param	TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note	TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @return None
  */
#define __TIM_DEF_INIT(TIMx)					do{ \
													((RCU_PERI_RST_REG_##TIMx) |= (RCU_PERI_RST_BIT_##TIMx)); \
													((RCU_PERI_RST_REG_##TIMx) &= ~(RCU_PERI_RST_BIT_##TIMx)); \
												}while(0U)

/**
  * @brief  Sets the TIMx Counter Register value
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  VALUE: specifies the Counter register new value.
  * @return None
  */
#define __TIM_COUNTER_SET(TIMx, VALUE)			((TIMx)->CNT = VALUE)

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @return Counter Register value.
  */
#define __TIM_COUNTER_GET(TIMx)					((TIMx)->CNT)

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.
  * @return Prescaler Register value.
  */
#define __TIM_PRESCALER_GET(TIMx)				((TIMx)->PDIV)

/**
  * @brief  Sets the TIMx CHxCC(channel capture compare) value.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.
  * @param  CH: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.  
  * @param  VALUE: specifies value.  
  * @return Capture Compare value.
  */
#define __TIM_CC_VALUE_SET(TIMx, CH, VALUE)		((TIMx)->CHxCCVAL[CH] = VALUE)	

/**
  * @brief  Gets the TIMx CHxCC(channel capture compare) value.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.
  * @param  CH: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.  
  * @return Capture Compare value.
  */
#define __TIM_CC_VALUE_GET(TIMx, CH)			((TIMx)->CHxCCVAL[CH])	

/**
  * @brief  Sets the TIM14 Remapping input Capabilities.
  * @param  TIMx: pointer to TIMx where x can be 14.  
  * @param  VALUE: specifies the TIM input reampping source, it can be one of the following values:
  *          @arg TIM14_REMAP_PORT (TIM14 Channel 1 is connected to PORT)
  *          @arg TIM14_REMAP_RTC_CLK (TIM14 Channel 1 is connected to RTC input clock)
  *          @arg TIM14_REMAP_HXT_DIV32 (TIM14 Channel 1 is connected to HXT/32 clock)  
  *          @arg TIM14_REMAP_MCO (TIM14 Channel 1 is connected to CLKOUT clock) 
  * @return None
  */
#define __TIM_REMAP_SET(TIMx, VALUE)			((TIMx)->REMAP = VALUE)

/**
  * @brief  Sets the counter update register value,
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  VALUE: specifies the counter update register value.
  * @return None
  */
#define __TIM_COUNTER_UPDATE_SET(TIMx, VALUE)	((TIMx)->UVAL = VALUE)

/**
  * @brief  Configures the TIMx event to be generated by software.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  EVENT: specifies the event source, it can be one or more of the following values:  
  *          @arg TIM_EVENT_SOURCE_UPDATE(TIM update Interrupt Event source, for TIM1/2/3/6/14/15/16/17)
  *          @arg TIM_EVENT_SOURCE_CH1 (TIMx channel 1 Capture Compare Interrupt Event, for TIM1/2/3/14/15/16/17)
  *          @arg TIM_EVENT_SOURCE_CH2 (TIMx channel 2 Capture Compare Interrupt Event, for TIM1/2/3/15)
  *          @arg TIM_EVENT_SOURCE_CH3 (TIMx channel 3 Capture Compare Interrupt Event, for TIM1/2/3)
  *          @arg TIM_EVENT_SOURCE_CH4 (TIMx channel 4 Capture Compare Interrupt Event, for TIM1/2/3)
  *          @arg TIM_EVENT_SOURCE_COM (TIMx Commutation Interrupt Event source, for TIM1/15/16/17)
  *          @arg TIM_EVENT_SOURCE_TRIGGER (TIMx Trigger Interrupt Event source, for TIM1/2/3/15) 
  *          @arg TIM_EVENT_SOURCE_BREAK (TIMx Break Interrupt Event source, TIM1/15/16/17)         
  * @return None
  */
#define __TIM_EVENT_GENERATE(TIMx, EVENT)		((TIMx)->SWEGR = EVENT)	

/**
  * @brief  Enables the specified TIM peripheral.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @return None
  */
#define __TIM_ENABLE(TIMx)						((TIMx)->CTR1 |= TIM_CTR1_CEN)

/**
  * @brief Disables the specified TIM peripheral.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @return None
  */
#define __TIM_DISABLE(TIMx)						((TIMx)->CTR1 &= ~(TIM_CTR1_CEN))

/**
  * @brief  Enables the specified TIM function.   
  * @param  TIMx: pointer to TIMx where x can be 1, 2 ,3 or 15.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is note available for CS32F036 devices.  
  * @param  FUNC: specifies the USART function.
  *         It can be one of the following values:
  *          @arg PRELOAD_SHADOW (TIM1/15/16/17)
  *          @arg PRELOAD_UPDATE TIM1/15/16/17)
  *          @arg UPDATE_DIS (TIM1/2/3/14/15/16/17)
  *          @arg UVAL_SHADOW (TIM1/2/3/14/15/16/17)
  *          @arg CH_OUTPUT (TIM1/15/16/17)
  *          @arg DMA_REQUEST (TIM1/2/315/16/17)
  *          @arg XOR_INPUT (TIM1/2/3)
  * @return None
  */
#define __TIM_FUNC_ENABLE(TIMx, FUNC)			(((TIMx)->TIM_ENABLE_REG_##FUNC) |= TIM_ENABLE_BIT_##FUNC)

/**
  * @brief  Disables the specified TIM function.   
  * @param  TIMx: pointer to TIMx where x can be 1, 2 ,3 or 15.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is note available for CS32F036 devices.  
  * @param  FUNC: specifies the USART function.
  *         It can be one of the following values:
  *          @arg PRELOAD_SHADOW (TIM1/15/16/17)
  *          @arg PRELOAD_UPDATE TIM1/15/16/17)
  *          @arg UPDATE_DIS (TIM1/2/3/14/15/16/17)
  *          @arg UVAL_SHADOW (TIM1/2/3/14/15/16/17)
  *          @arg CH_OUTPUT (TIM1/15/16/17)
  *          @arg DMA_REQUEST (TIM1/2/315/16/17)
  *          @arg XOR_INPUT (TIM1/2/3)
  * @return None
  */
#define __TIM_FUNC_DISABLE(TIMx, FUNC)			(((TIMx)->TIM_ENABLE_REG_##FUNC) &= ~(TIM_ENABLE_BIT_##FUNC))

/**
  * @brief Enables the TIMx's DMA Requests.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  DMA: specifies the DMA Request sources, it can be any combination of the following values:
  *          @arg TIM_DMA_UPDATE (TIMx update Interrupt source, for TIM1/2/3/6/14/15/16/17)
  *          @arg TIM_DMA_CH1CC (TIMx channel 1 Capture Compare DMA, for TIM1/2/3/14/15/16/17)
  *          @arg TIM_DMA_CH2CC (TIMx channel 2 Capture Compare DMA, for TIM1/2/3/15)
  *          @arg TIM_DMA_CH3CC (TIMx channel 3 Capture Compare DMA, for TIM1/2/3)
  *          @arg TIM_DMA_CH4CC (TIMx channel 4 Capture Compare DMA, for TIM1/2/3)
  *          @arg TIM_DMA_CHCOM (TIMx Commutation DMA source, for TIM1)
  *          @arg TIM_DMA_TRIGGER (TIMx Trigger DMA source, for TIM1/2/3/15)
  * @return None
  */
#define __TIM_DMA_ENABLE(TIMx, DMA)				((TIMx)->DIEN |= DMA)

/**
  * @brief Disables the TIMx's DMA Requests.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is note available for CS32F036 devices.  
  * @param  DMA: specifies the DMA Request sources, it can be any combination of the following values:
  *          @arg TIM_DMA_UPDATE (TIMx update Interrupt source, for TIM1/2/3/6/14/15/16/17)
  *          @arg TIM_DMA_CH1CC (TIMx channel 1 Capture Compare DMA, for TIM1/2/3/14/15/16/17)
  *          @arg TIM_DMA_CH2CC (TIMx channel 2 Capture Compare DMA, for TIM1/2/3/15)
  *          @arg TIM_DMA_CH3CC (TIMx channel 3 Capture Compare DMA, for TIM1/2/3)
  *          @arg TIM_DMA_CH4CC (TIMx channel 4 Capture Compare DMA, for TIM1/2/3)
  *          @arg TIM_DMA_CHCOM (TIMx Commutation DMA source, for TIM1)
  *          @arg TIM_DMA_TRIGGER (TIMx Trigger DMA source, for TIM1/2/3/15)
  * @return None
  */
#define __TIM_DMA_DISABLE(TIMx, DMA)			((TIMx)->DIEN &=~ (DMA))

/**
  * @brief  Enables the specified TIM interrupts.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  INT: enabled or disabled specifies the TIM interrupts sources.
  *          It can be any combination of the following values:
  *           @arg TIM_INTR_UPDATE(TIM update Interrupt source, for TIM1/2/3/6/14/15/16/17);
  *           @arg TIM_INTR_CH1CC (TIMx channel 1 Capture Compare Interrupt, for TIM1/2/3/14/15/16/17)
  *           @arg TIM_INTR_CH2CC (TIMx channel 2 Capture Compare Interrupt, for TIM1/2/3/15)
  *           @arg TIM_INTR_CH3CC (TIMx channel 3 Capture Compare Interrupt, for TIM1/2/3)
  *           @arg TIM_INTR_CH4CC (TIMx channel 4 Capture Compare Interrupt, for TIM1/2/3)
  *           @arg TIM_INTR_CHCOM (TIMx Commutation Interrupt source, for TIM1/15/16/17)
  *           @arg TIM_INTR_TRIGGER (TIM Trigger Interrupt source, for TIM1/2/3/15)
  *           @arg TIM_INTR_BREAK (TIM Break Interrupt source, for TIM1/15/16/17) 
  * @return None
  */
#define __TIM_INTR_ENABLE(TIMx, INT)			((TIMx)->DIEN |= INT)

/**
  * @brief  Disables the specified TIM interrupts.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  INT: enabled or disabled specifies the TIM interrupts sources.
  *          It can be any combination of the following values:
  *           @arg TIM_INTR_UPDATE(TIM update Interrupt source, for TIM1/2/3/6/14/15/16/17);
  *           @arg TIM_INTR_CH1CC (TIMx channel 1 Capture Compare Interrupt, for TIM1/2/3/14/15/16/17)
  *           @arg TIM_INTR_CH2CC (TIMx channel 2 Capture Compare Interrupt, for TIM1/2/3/15)
  *           @arg TIM_INTR_CH3CC (TIMx channel 3 Capture Compare Interrupt, for TIM1/2/3)
  *           @arg TIM_INTR_CH4CC (TIMx channel 4 Capture Compare Interrupt, for TIM1/2/3)
  *           @arg TIM_INTR_CHCOM (TIMx Commutation Interrupt source, for TIM1/15/16/17)
  *           @arg TIM_INTR_TRIGGER (TIM Trigger Interrupt source, for TIM1/2/3/15)
  *           @arg TIM_INTR_BREAK (TIM Break Interrupt source, for TIM1/15/16/17) 
  * @return None
  */
#define __TIM_INTR_DISABLE(TIMx, INT)			((TIMx)->DIEN &= ~(INT))

/**
  * @brief  Checks whether the TIM interrupt has enabled or not.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.  
  * @note   TIM2 is only available for CS32F031 devices.  
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  INT: specifies the TIM interrupt source.
  *			It can be one of the following values:
  *          @arg UPDATE (TIMx update Interrupt source, for TIM1/2/3/6/14/15/16/17)
  *          @arg CH1CC  (TIMx channel 1 Capture Compare Interrupt, for TIM1/2/3/14/15/16/17)
  *          @arg CH2CC  (TIMx channel 2 Capture Compare Interrupt, for TIM1/2/3/15)
  *          @arg CH3CC  (TIMx channel 3 Capture Compare Interrupt, for TIM1/2/3)
  *          @arg CH4CC  (TIMx channel 4 Capture Compare Interrupt, for TIM1/2/3)
  *          @arg CHCOM  (TIMx Commutation Interrupt source, for TIM1/15/16/17)//yudz??
  *          @arg TRIGGER (TIMx Trigger Interrupt source, for TIM1/2/3/15) 
  *          @arg BREAK (TIMx Break Interrupt source, for TIM1/15/16/17)
  * @return SET or RESET.
  */
#define __TIM_INTR_ENABLE_STATUS_GET(TIMx, INT)	((((TIMx)->DIEN) & (TIM_INTR_ENABLE_BIT_##INT)) ? SET : RESET)

/**
  * @brief  Checks whether the TIM interrupt has occured or not.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  INT: specifies the TIM interrupt source.
  *			It can be one of the following values:
  *          @arg UPDATE (TIMx update Interrupt source, for TIM1/2/3/6/14/15/16/17)
  *          @arg CH1CC  (TIMx channel 1 Capture Compare Interrupt, for TIM1/2/3/14/15/16/17)
  *          @arg CH2CC  (TIMx channel 2 Capture Compare Interrupt, for TIM1/2/3/15)
  *          @arg CH3CC  (TIMx channel 3 Capture Compare Interrupt, for TIM1/2/3)
  *          @arg CH4CC  (TIMx channel 4 Capture Compare Interrupt, for TIM1/2/3)
  *          @arg CHCOM  (TIMx Commutation Interrupt source, for TIM1/15/16/17)
  *          @arg TRIGGER (TIMx Trigger Interrupt source, for TIM1/2/3/15) 
  *          @arg BREAK (TIMx Break Interrupt source, for TIM1/15/16/17) 
  * @return SET or RESET.
  */
#define __TIM_INTR_STATUS_GET(TIMx, INT)		(__TIM_INTR_ENABLE_STATUS_GET(TIMx, INT) && __TIM_FLAG_STATUS_GET(TIMx, INT))

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices. 
  * @param  FLAG: specifies the flag to check, it can be one of the following values:
  *          @arg UPDATE (TIMx update Flag, for TIM1/2/3/6/14/15/16/17)
  *          @arg CH1CC (TIMx chnnel 1 Capture Compare Flag, for TIM1/2/3/14/15/16/17)
  *          @arg CH2CC (TIMx chnnel 2 Capture Compare Flag, for TIM1/2/3/15)
  *          @arg CH3CC (TIMx chnnel 3 Capture Compare Flag, for TIM1/2/3)
  *          @arg CH4CC (TIMx chnnel 4 Capture Compare Flag, for TIM1/2/3)
  *          @arg CHCOM (TIMx Commutation Flag, for TIM1/15/16/17)
  *          @arg TRIGGER (TIMx Trigger Flag, for TIM1/2/3/15)
  *          @arg BREAK (TIMx Break Flag, for TIM1/15/16/17)
  *          @arg CH1ICOF (TIMx chnnel 1 Capture Compare overflow Flag, for TIM1/2/14/15/16/17)
  *          @arg CH2ICOF (TIMx chnnel 2 Capture Compare overflow Flag, for TIM1/2/15)
  *          @arg CH3ICOF (TIMx chnnel 3 Capture Compare overflow Flag, for TIM1/2)
  *          @arg CH4ICOF (TIMx chnnel 4 Capture Compare overflow Flag, for TIM1/2)
  * @return SET or RESET.
  */
#define __TIM_FLAG_STATUS_GET(TIMx, FLAG)		((((TIMx)->STS) & (TIM_FLAG_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the TIMx's flags.
  * @param  TIMx: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices. 
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  FLAG: specifies the flag to check,it can be one of the following values:
  *          @arg TIM_FLAG_UPDATE (TIMx update Flag, for TIM1/2/3/6/14/15/16/17)
  *          @arg TIM_FLAG_CH1CC (TIMx chnnel 1Capture Compare Flag, for TIM1/2/3/14/15/16/17)
  *          @arg TIM_FLAG_CH2CC (TIMx chnnel 2Capture Compare Flag, for TIM1/2/3/15)
  *          @arg TIM_FLAG_CH3CC (TIMx chnnel 3Capture Compare Flag, for TIM1/2/3)
  *          @arg TIM_FLAG_CH4CC (TIMx chnnel 4Capture Compare Flag, for TIM1/2/3)
  *          @arg TIM_FLAG_CHCOM (TIMx Commutation Flag, for TIM1/15/16/17)
  *          @arg TIM_FLAG_TRIGGER (TIMx Trigger Flag, for TIM1/2/3/15)
  *          @arg TIM_FLAG_BREAK (TIM Break Flag, for TIM1/15/16/17)
  *          @arg TIM_FLAG_CH1ICOF (TIMx chnnel 1 Capture Compare overflow Flag, for TIM1/2/14/15/16/17)
  *          @arg TIM_FLAG_CH2ICOF (TIMx chnnel 2 Capture Compare overflow Flag, for TIM1/2/15)
  *          @arg TIM_FLAG_CH3ICOF (TIMx chnnel 3 Capture Compare overflow Flag, for TIM1/2)
  *          @arg TIM_FLAG_CH4ICOF (TIMx chnnel 4 Capture Compare overflow Flag, for TIM1/2)
  * @return None
  */
#define __TIM_FLAG_CLEAR(TIMx, FLAG)			((TIMx)->STS = (uint16_t)~(FLAG))

/**
  * @fn void tim_base_init(tim_reg_t* ptr_timer, tim_base_t* ptr_base)
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices. 
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  ptr_base: pointer to a tim_base_t structure that contains the configuration 
  *         information for the specified TIM peripheral.
  * @return None
  */
void tim_base_init(tim_reg_t* ptr_timer, tim_base_t* ptr_base);

/**
  * @fn void tim_base_struct_init(tim_base_t* ptr_base)
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  ptr_base: pointer to a tim_base_t structure which will be initialized.
  * @return None
  */
void tim_base_struct_init(tim_base_t* ptr_base);

/**
  * @fn void tim_prescaler_set(tim_reg_t* ptr_timer, uint16_t value, uint16_t flag)
  * @brief  Configures the TIMx PDIV (pre-divider).
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  value: specifies the Prescaler Register value
  * @param  flag: specifies the TIM Prescaler Reload mode, it be one of the following values:
  *          @arg TIM_PDIV_MODE_UPDATE (The Prescaler is loaded at the update event)
  *          @arg TIM_PDIV_MODE_IMMEDIATE (The Prescaler is loaded immediatly)
  * @return None
  */
void tim_prescaler_set(tim_reg_t* ptr_timer, uint16_t value, uint16_t flag);

/**
  * @fn void tim_count_pattern_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief Specifies the TIMx Counter Mode to be used.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, or 3 to select the TIM peripheral
  * @note   TIM2 is only available for CS32F031 devices. 
  * @param  value: specifies the Counter Mode to be used ,it can be one of the following values:
  *          @arg TIM_COUNT_PATTERN_UP (TIM Up Counting)
  *          @arg TIM_COUNT_PATTERN_DOWN (TIM Down Counting)
  *          @arg TIM_COUNT_PATTERN_CENTER_ALIGNED1 (TIM Center Aligned 1)
  *          @arg TIM_COUNT_PATTERN_CENTER_ALIGNED2 (TIM Center Aligned 2)
  *          @arg TIM_COUNT_PATTERN_CENTER_ALIGNED3 (TIM Center Aligned 3)
  * @return None
  */
void tim_count_pattern_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_update_request_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  select the TIMx Update Request Interrupt source.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.    
  * @param  value: specifies the Update source, it can be one of the following values:
  *          @arg TIM_UPDATE_SEL_REGULAR (Source of update is the counter overrun/underrun or
  *               the setting of UG bit, or an update generation through the slave mode controller)
  *          @arg TIM_UPDATE_SEL_GLOBAL (Source of update is counter overflow/underflow)
  * @return None
  */
void tim_update_request_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_pulse_mode_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief set the TIMx's Single pulse  Mode or repetitive mode.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices. 
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  value: It can be one of the following values:
  *          @arg TIM_PULSE_MODE_SINGLE 
  *          @arg TIM_PULSE_MODE_REPETITIVE
  * @return None
  */
void tim_pulse_mode_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_clock_division_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  Sets the TIMx Clock Division value.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17,
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  value: specifies the clock division value, it can be one of the following value:
  *          @arg TIM_CKDIV_DIV1
  *          @arg TIM_CKDIV_DIV2
  *          @arg TIM_CKDIV_DIV4
  * @return None
  */
void tim_clock_division_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_protect_config(tim_reg_t* ptr_timer, tim_protect_t *ptr_protect)
  * @brief  Configures the: Break feature, dead time, Lock level, OSSI/OSSR State
  *         and the AOE(automatic output enable).
  * @param  ptr_timer: pointer to TIMx where x can be 1, 15, 16 or 17. 
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ptr_protect: pointer to a tim_protect_t structure that contains the CHOPR 
  *         Register configuration for the TIM peripheral.
  * @return None
  */
void tim_protect_config(tim_reg_t* ptr_timer, tim_protect_t *ptr_protect);

/**
  * @fn void tim_protect_struct_init(tim_protect_t* ptr_protect)
  * @brief  Fills each ptr_protect member with its default value.
  *         CHOPR(TIMx channel output protect register)
  * @param  ptr_protect: pointer to a tim_protect_t structure be initialized.
  * @return None
  */
void tim_protect_struct_init(tim_protect_t* ptr_protect);

/**
  * @fn void tim_choc_init(tim_reg_t* ptr_timer, tim_choc_t* ptr_choc)
  * @brief  Initializes the TIMx channel4 output compare(CH4OC).
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16, 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  ptr_choc: pointer to a tim_choc_t structure that contains the 
  *         configuration for the specified TIM peripheral.
  * @return None
  */
void tim_choc_init(tim_reg_t* ptr_timer, tim_choc_t* ptr_choc);

/**
  * @fn tim_choc_struct_init(tim_choc_t* ptr_choc)
  * @brief  Fills each ptr_choc member with its default value.
  * @param  ptr_choc: pointer to a tim_choc_t structure being initialized.    
  * @return None
  */
void tim_choc_struct_init(tim_choc_t* ptr_choc);  

/**
  * @fn void tim_choc_mode_set(tim_reg_t* ptr_timer, uint16_t ch, uint16_t mode)
  * @brief  Set the TIMx CHxOC mode selection.It must be disable the selected channel
  *         before changing the Output Compare Mode.     
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ch: specifies the TIM Channel,it can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.  
  * @param  mode: specifies the TIM Output Compare Mode, it can be one of the following values:
  *          @arg TIM_CHxOCMSEL_TIMING
  *          @arg TIM_CHxOCMSEL_ACTIVE
  *          @arg TIM_CHxOCMSEL_INACTIVE
  *          @arg TIM_CHxOCMSEL_TOGGLE
  *          @arg TIM_CHxOCMSEL_PWM1
  *          @arg TIM_CHxOCMSEL_PWM2
  * @return None
  */
void tim_choc_mode_set(tim_reg_t* ptr_timer, uint16_t ch, uint16_t mode);

/**
  * @fn void tim_choc_forced_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Forces the TIMx channel waveform to active or inactive level.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.    
  * @param  value: specifies the forced Action to be set to the output waveform.
  *          It can be one of the following values:
  *           @arg TIM_CHxOCMSEL_FORCED_ACTIVE
  *           @arg TIM_CHxOCMSEL_FORCED_INACTIVE
  * @return None
  */
void tim_choc_forced_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_choc_preload_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Enables or disables the TIMx CH4OC(channel 4 output compare) Preload value.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.   
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.    
  * @param  value: new state of the TIMx peripheral Preload register
  *          It can be one of the following values:
  *           @arg TIM_CHxOC_PRELOAD_ENABLE
  *           @arg TIM_CHxOC_PRELOAD_DISABLE
  * @return None
  */
void tim_choc_preload_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_choc_fast_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Set the TIMx CH1OC(channel 1 Output Compare) Fast feature.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.  
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.    
  * @param  value: new state of the Output Compare Fast Enable Bit.
  *          It can be one of the following values:
  *           @arg TIM_CHxOC_FAST_ENABLE (output compare fast enable)
  *           @arg TIM_CHxOC_FAST_DISABLE (output compare fast disable)
  * @return None
  */
void tim_choc_fast_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_choc_clear_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Clears or safeguards the TIMx CH4OC(channel 4 Output Compare) signal on an external event.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.  
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.    
  * @param  value: new state of the Output Compare Clear Enable Bit.
  *          It can be one of the following values:
  *           @arg TIM_CHxOC_CLEAR_ENABLE (output compare clear enable)
  *           @arg TIM_CHxOC_CLEAR_DISABLE (output compare clear disable)
  * @return None
  */
void tim_choc_clear_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_chcc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Configures the TIMx CHCC (channel capture compare) polarity.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.  
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.    
  * @param  value: specifies the Polarity, It can be one of the following values:
  *          @arg TIM_CHxCCP_POLARITY_HIGH (Compare active high)
  *          @arg TIM_CHxCCP_POLARITY_LOW (Compare active low)    
  * @return None
  */
void tim_chcc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_chncc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Configures the TIMx CHNCC (channel complementary capture compare) polarity.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  * @param  value: specifies the Polarity, It can be one of the following values:
  *          @arg TIM_CHxNCCP_POLARITY_HIGH (Compare active high)
  *          @arg TIM_CHxNCCP_POLARITY_LOW (Compare active low)    
  * @return None
  */
void tim_chncc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_chcc_enable_ctrl(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value)
  * @brief  Enables or disables the TIM channelx Capture Compare .
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ch: specifies the TIM Channel.
  *         It can be one of the following values:
  *          @arg TIM_CHANNEL_1 (Channel 1)
  *          @arg IIM_CHANNEL_2 (Channel 2)
  *          @arg TIM_CHANNEL_3 (Channel 3)
  *          @arg TIM_CHANNEL_4 (Channel 4)
  * @param  value: Enable or disable specifies the TIM Channel.
  *         It can be: TIM_CHxCC_ENABLE or TIM_CHxCC_DISABLE. 
  * @return None
  */
void tim_chcc_enable_ctrl(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value);

/**
  * @fn void tim_chncc_enable_ctrl(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value)
  * @brief  Enables or disables the TIM channel complementary Capture Compare .
  * @param  ptr_timer: pointer to TIMx where x can be 1, 15, 16 or 17.  
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ch: specifies the TIM Channel.
  *         It can be one of the following values:
  *          @arg TIM_CHANNEL_1 (Channel 1)
  *          @arg TIM_CHANNEL_2 (Channel 2)
  *          @arg TIM_CHANNEL_3 (Channel 3)
  * @param  value: Enable or disable specifies the TIM Channel.
  *         It can be: TIM_CHxNCC_ENABLE or TIM_CHxNCC_DISABLE. 
  * @return None
  */
void tim_chncc_enable_ctrl(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value);

/**
  * @fn void tim_chic_init(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic)
  * @brief  Initializes TIM CHxIC(channel input capture) according to the specified
  *         parameters in the ptr_chic.
  * @param  ptr_timer: pointer to TIMx where x can be  1, 2, 3, 14, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices. 
  * @note   TIM15 is not available for CS32F036 devices.       
  * @param  ptr_chic: pointer to a tim_chic_t structure that contains 
  *         the configuration information for the specified TIM peripheral.
  * @return None
  */
void tim_chic_init(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic);

/**
  * @fn void tim_chic_struct_init(tim_chic_t* ptr_chic)
  * @brief  Fills each ptr_chic member with its default value.
  * @param  ptr_chic: pointer to a tim_chic_t structure which will be initialized.        
  * @return None
  */
void tim_chic_struct_init(tim_chic_t* ptr_chic);

/**
  * @fn void tim_pwmi_config(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic)
  * @brief  Configures the TIM peripheral according to the specified
  *         parameters in the ptr_chic to measure an external PWM signal.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3 or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  ptr_chic: pointer to a tim_chic_t structurethat contains 
  *         the configuration for the specified TIM peripheral.
  * @return None
  */
void tim_pwmi_config(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic);

/**
  * @fn void tim_chic_predivider_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Sets the TIMx CH4IC (channel 4 Input Capture) pre-divide.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2 or 3, 14, 15, 16 or 17..  
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.   
  * @param  value: specifies pre-divide value,it can be one of the following values:
  *          @arg TIM_CHIC_PREDIVIDE_DIV1 (no prescaler)
  *          @arg TIM_CHIC_PREDIVIDE_DIV2 (capture is done once every 2 events)
  *          @arg TIM_CHIC_PREDIVIDE_DIV4 (capture is done once every 4 events)
  *          @arg TIM_CHIC_PREDIVIDE_DIV8 (capture is done once every 8 events)
  * @return None
  */
void tim_chic_predivider_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value);

/**
  * @fn void tim_dma_access_config(tim_reg_t* ptr_timer, uint16_t addr, uint16_t len)
  * @brief  Configures the TIMx's DMA interface.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 15, 16 or 17, 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  addr: DMA Base address, it can be one of the following values:         
  *          @arg TIM_DMA_BASE_CTR1
  *          @arg TIM_DMA_BASE_CTR2
  *          @arg TIM_DMA_BASE_SMCFG
  *          @arg TIM_DMA_BASE_DIEN
  *          @arg TIM_DMA_BASE_STS
  *          @arg TIM_DMA_BASE_SWEGR 
  *          @arg TIM_DMA_BASE_CH12CFGR
  *          @arg TIM_DMA_BASE_CH34CFGR
  *          @arg TIM_DMA_BASE_CCCTR
  *          @arg TIM_DMA_BASE_CNT
  *          @arg TIM_DMA_BASE_PDIV
  *          @arg TIM_DMA_BASE_UVAL
  *          @arg TIM_DMA_BASE_CH1CCVAL
  *          @arg TIM_DMA_BASE_CH2CCVAL
  *          @arg TIM_DMA_BASE_CH3CCVAL
  *          @arg TIM_DMA_BASE_CH4CCVAL
  *          @arg TIM_DMA_BASE_DMAACR
  *          @arg TIM_DMA_BASE_REMAP
  * @param  len: DMA Burst length. This parameter can be one value
  *         between: TIM_DMA_TRANSFER_LEN_1BYTE and TIM_DMA_TRANSFER_LEN_18BYTES.
  * @return None
  */
void tim_dma_access_config(tim_reg_t* ptr_timer, uint16_t addr, uint16_t len);

/**
  * @fn void tim_internal_clock_config(tim_reg_t* ptr_timer)
  * @brief  Configures the TIMx internal Clock
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @return None
  */
void tim_internal_clock_config(tim_reg_t* ptr_timer);

/**
  * @fn void tim_internal_trigger_external_clock_config(tim_reg_t* ptr_timer, uint16_t value) 
  * @brief  Config the TIMx Internal Trigger as EXTCLK (External Clock)
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  value: Trigger source, it can be one of the following values:
  *          @arg TIM_TRIGGER_SEL_ITRO (Internal Trigger 0)
  *          @arg TIM_TRIGGER_SEL_ITR1 (Internal Trigger 1)
  *          @arg TIM_TRIGGER_SEL_ITR2 (Internal Trigger 2)
  *          @arg TIM_TRIGGER_SEL_ITR3 (Internal Trigger 3)
  * @return None
  */
void tim_internal_trigger_external_clock_config(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_ti_external_clock_config(tim_reg_t* ptr_timer, uint16_t value,uint16_t polarity, uint16_t filter) 
  * @brief  Configures the TIMx Trigger as EXTCLK(External Clock)
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  value: Trigger source,it can be one of the following values:
  *          @arg TIM_TIMx_EXTlCLK1_SOURCE_TI1ED (TI1 Edge Detector)
  *          @arg TIM_TIMx_EXTlCLK1_SOURCE_TI1 (Filtered Timer Input 1)
  *          @arg TIM_TIMx_EXTlCLK1_SOURCE_TI2 (Filtered Timer Input 2)
  * @param  polarity: specifies the TIx Polarity,it can be one of the following values:
  *          @arg TIM_CHxIC_POLARITY_RISING
  *          @arg TIM_CHxIC_POLARITY_FALLING
  * @param  filter: specifies the filter value (between 0x0 and 0xF).
  * @return None
  */
void tim_ti_external_clock_config(tim_reg_t* ptr_timer, uint16_t value, uint16_t polarity, uint16_t filter);

/**
  * @fn void tim_external_clock_mode1_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity,uint16_t filter)
  * @brief  Configures the EXTCLK(External clock) Mode1
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, or 3.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  divide: The external Trigger Pre-divide, it can be one of the following values:
  *          @arg TIM_EXT_TRG_PDIV_OFF (Prescaler OFF)
  *          @arg TIM_EXT_TRG_PDIV2 (divided by 2)
  *          @arg TIM_EXT_TRG_PDIV4 (divided by 4)
  *          @arg TIM_EXT_TRG_PDIV8 (divided by 8)
  * @param  polarity: The external Trigger Polarity, it can be one of the following values:
  *          @arg TIM_EXT_TRG_POLARITY_INVERTED (active low or falling edge active)
  *          @arg TIM_EXT_TRG_POLARITY_NON_INVERTED (active high or rising edge active)
  * @param  filter: External Trigger Filter. It is a value between 0x00 and 0x0F.
  * @return None
  */
void tim_external_clock_mode1_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity,uint16_t filter);

/**
  * @fn void tim_external_clock_mode2_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity,uint16_t filter)
  * @brief  Configures the EXTCLK(External clock) Mode 2.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, or 3.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  divide: The external Trigger Pre-divide, it can be one of the following values:
  *          @arg TIM_EXT_TRG_PDIV_OFF (Prescaler OFF)
  *          @arg TIM_EXT_TRG_PDIV2 (divided by 2)
  *          @arg TIM_EXT_TRG_PDIV4 (divided by 4)
  *          @arg TIM_EXT_TRG_PDIV8 (divided by 8)
  * @param  polarity: The external Trigger Polarity, it can be one of the following values:
  *          @arg TIM_EXT_TRG_POLARITY_INVERTED (active low or falling edge active)
  *          @arg TIM_EXT_TRG_POLARITY_NON_INVERTED (active high or rising edge active)
  * @param  filter: External Trigger Filter.It is a value between 0x00 and 0x0F.
  * @return None
  */
void tim_external_clock_mode2_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity, uint16_t filter);         

/**
  * @fn void tim_external_trigger_config(tim_reg_t* ptr_timer, uint16_t divide, 
                                                          uint16_t polarity, uint16_t filter) 
  * @brief  Configures the TIMx External Trigger .
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2 or 3.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  divide: The external Trigger Pre-divide, it can be one of the following values:
  *          @arg TIM_EXT_TRG_PDIV_OFF (Prescaler OFF)
  *          @arg TIM_EXT_TRG_PDIV2 (divided by 2)
  *          @arg TIM_EXT_TRG_PDIV4 (divided by 4)
  *          @arg TIM_EXT_TRG_PDIV8 (divided by 8)
  * @param  polarity: The external Trigger Polarity, it can be one of the following values:
  *          @arg TIM_EXT_TRG_POLARITY_INVERTED (active low or falling edge active)
  *          @arg TIM_EXT_TRG_POLARITY_NON_INVERTED (active high or rising edge active)
  * @param  filter: External Trigger Filter. It is a value between 0x00 and 0x0F.
  * @return None
  */
void tim_external_trigger_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity, uint16_t filter);

/**
  * @fn void tim_input_trigger_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  Selects the Input Trigger source
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3 or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  value: The Input Trigger source, it can be one of the following values:
  *          @arg TIM_TRIGGER_SEL_ITRO (Internal Trigger 0)
  *          @arg TIM_TRIGGER_SEL_ITR1 (Internal Trigger 1)
  *          @arg TIM_TRIGGER_SEL_ITR2 (Internal Trigger 2)
  *          @arg TIM_TRIGGER_SEL_ITR3 (Internal Trigger 3)
  *          @arg TIM_TRIGGER_SEL_EDGE (TI1 Edge Detector)
  *          @arg TIM_TRIGGER_SEL_FILTER1 (Filtered Timer Input 1) 
  *          @arg TIM_TRIGGER_SEL_FILTER2 (Filtered Timer Input 2) 
  *          @arg TIM_TRIGGER_SEL_EXTERNAL (External Trigger input)
  * @return None
  */
void tim_input_trigger_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_trigger_output_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  Selects the TIMx Trigger Output Mode.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 7, or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.    
  * @param  value: specifies the Trigger Output source, it can be one of the following values:
  *         for all TIMx: 
  *          @arg TIM_TRG_OUTPUT_SEL_RESET
  *          @arg TIM_TRG_OUTPUT_SEL_ENABLE
  *          @arg TIM_TRG_OUTPUT_SEL_UPDATE
  *         for all TIMx except TIM6 and TIM7: 
  *          @arg TIM_TRG_OUTPUT_SEL_CH1OC
  *          @arg TIM_TRG_OUTPUT_SEL_CH1OC_REF
  *          @arg TIM_TRG_OUTPUT_SEL_CH2OC_REF
  *          @arg TIM_TRG_OUTPUT_SEL_CH3OC_REF
  *          @arg TIM_TRG_OUTPUT_SEL_CH4OC_REF 
  * @return None
  */
void tim_trigger_output_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_slave_mode_set(tim_reg_t* ptr_timer, uint16_t value) 
  * @brief  Selects the TIMx Slave Mode.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3 or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.
  * @param  value: specifies the Timer Slave Mode.
  *         It can be one of the following values:
  *          @arg TIM_SLAVE_MODE_RESET
  *          @arg TIM_SLAVE_MODE_GATED	(only available for CS32F036)
  *          @arg TIM_SLAVE_MODE_TRIGGER 
  *          @arg TIM_SLAVE_MODE_EXTERNAL1
  * @return None
  */
void tim_slave_mode_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_master_slave_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  Sets or Resets the TIMx Master/Slave Mode.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3 or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.  
  * @param  value: specifies the Timer Master Slave Mode.
  *         It can be one of the following values:
  *          @arg TIM_MASTER_SLAVE_MODE_ENABLE
  *          @arg TIM_MASTER_SLAVE_MODE_DISABLE
  * @return None
  */
void tim_master_slave_set(tim_reg_t* ptr_timer, uint16_t value);

/**
  * @fn void tim_encoder_interface_set(tim_reg_t* ptr_timer, uint16_t mode, uint16_t polarity, uint16_t value) 
  * @brief  Configures the TIMx Encoder Interface.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2 or 3.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  mode: specifies the TIMx Encoder Mode, it can be one of the following values:
  *          @arg TIM_ENCODER_MODE_TI1 (Counter counts on TI1FP1 edge depending on TI2FP2 level)
  *          @arg TIM_ENCODER_MODE_TI2 (Counter counts on TI2FP2 edge depending on TI1FP1 level)
  *          @arg TIM_ENCODER_MODE_TI12 (Counter counts on both TI1FP1 and TI2FP2 edges depending
  *               on the level of the other input)
  * @param  polarity: specifies the CH1IC Polarity, it can be one of the following values:
  *          @arg TIM_CHxIC_POLARITY_FALLING
  *          @arg TIM_CHxIC_POLARITY_RISING
  *          @arg TIM_CHxIC_POLARITY_BOTH_EDGE
  * @param  value: specifies the CH2IC Polarity, it can be one of the following values:
  *          @arg TIM_CHxIC_POLARITY_FALLING
  *          @arg TIM_CHxIC_POLARITY_RISING
  *          @arg TIM_CHxIC_POLARITY_BOTH_EDGE
  * @return None
  */
void tim_encoder_interface_set(tim_reg_t* ptr_timer, uint16_t mode, uint16_t polarity, uint16_t value);                               


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

