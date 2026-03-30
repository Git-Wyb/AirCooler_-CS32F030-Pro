/**
  * @file    cs32f0xx_tim.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the TIM peripheral(TimeBase management;
  *             Output Compare management; Input Capture management;
  *             Interrupts, DMA and flags management; Clocks management;
  *             Synchronization management; Specific interface management;
  *             Specific remapping management).
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2020 ChipSea</center></h2>
  *
  * @verbatim
  *
  ----------------------- this driver instruction for use--------------------------- 
    1. TIM TimeBase management includes all needed functions to configure the TM Timebase unit:        
          Set/Get Prescaler; Set/Get Update; Counter modes configuration; Set Clock division;
          Single pulse enable; Update Request selection; Update Disable Configuration;
          UVAL shadow enable; nable/Disable the counter.
         
    2. TIM Output Compare management includes all needed functions to configure the Capture/Compare: 
          Configure each channel, independently; Select the output compare modes;
          Select the Polarities of each channel; Set/Get the Capture/Compare register values;
          Select the Output Compare Fast mode; Select the Output Compare Forced mode;
          Output Compare-Preload Configuration; Clear Output Compare Reference;
          Select the OCREF Clear selection; Enable/Disable the Capture/Compare Channels.
 
    3. TIM Input Capture management includes all needed functions to configure the Capture/Compare:         
          Configure each channel in input capture mode; Configure Channel1/2 in PWM Input mode;
          Set the Input Capture Prescaler; Get the Capture/Compare values.
         
   4. Advanced-control timers (TIM1) specific features:
         Configures the Break input, dead time, Lock level, the OSSI, the OSSR State and the 
         AOE(automatic output enable); Enable/Disable the TIM peripheral Main Outputs; 
         Select the Commutation event; Set/Reset the Capture Compare Preload Control bit.

    5. TIM interrupts, DMA and flags management.
         Enable/Disable interrupt sources; Get flags status; Clear flags/ Pending bits;
         Enable/Disable DMA requests; Configure DMA burst mode; Select CaptureCompare DMA request

    6. TIM clocks management: this group includes all needed functions to configure
        the clock controller unit:
         Select Internal/External clock; Select the external clock mode: ETR(Mode1/Mode2), TIx or ITRx.        

    7. TIM synchronization management: this group includes all needed functions to configure
        the Synchronization unit:
         Select Input Trigger; Select Output Trigger;  
         Select Master Slave Mode; ETR Configuration when used as external trigger. 

    8. TIM specific interface management, this group includes all needed functions to 
       use the specific TIM interface:
         Encoder Interface Configuration; Select Hall Sensor.   

    9.TIM specific remapping management includes the Remapping configuration of specific timers.

    @endverbatim
  *
  */  

#include "cs32f0xx_tim.h"
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup TIM 
  * @brief TIM driver modules
  * @{
  */

#define TIM_SMCFG_ET_MASK             ((uint16_t)0xFF00) 
#define TIM_CHxxCFGR_OFFSET           ((uint16_t)0x0018)
#define TIM_CCCTR_CHxCCEN_SET         ((uint16_t)0x0001)
#define TIM_CCCTR_CHxNCCEN_SET        ((uint16_t)0x0004) 
  

static void tim_chic_config(tim_reg_t* ptr_timer, uint8_t ch, uint16_t polarity, uint16_t select, uint16_t filter);


/**
  * @fn void tim_base_init(tim_reg_t* ptr_timer, tim_base_t* ptr_base)
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  ptr_base: pointer to a tim_base_t structure that contains the configuration 
  *         information for the specified TIM peripheral.
  * @return None
  */
void tim_base_init(tim_reg_t* ptr_timer, tim_base_t* ptr_base)
{
    ASSERT(TIM_ALL_TIMx_CHECK(ptr_timer)); 
    ASSERT(TIM_COUNT_PATTERN_CHECK(ptr_base->count_mode));
    ASSERT(TIM_CKDIV_CHECK(ptr_base->clk_division));

    if ((ptr_timer == TIM1) || (ptr_timer == TIM2) || (ptr_timer == TIM3))
    {
        /* Select the Counter  */
		    MODIFY_REG(ptr_timer->CTR1, TIM_CTR1_DIR | TIM_CTR1_CPS, ptr_base->count_mode);
    }
 
    if (ptr_timer != TIM6)
    {
        /* Set the clock division */
		    MODIFY_REG(ptr_timer->CTR1, TIM_CTR1_CKDIV, ptr_base->clk_division);		
    }

    /* Set the Autoreload value */
    ptr_timer->UVAL = ptr_base->period ; 
    ptr_timer->PDIV = ptr_base->predivider;
    
    if ((ptr_timer == TIM1) || (ptr_timer == TIM15)|| (ptr_timer == TIM16) || (ptr_timer == TIM17))  
    {
#if defined (CS32F036) || defined (CS32F03X_RA)
        /* Set the Repetition Counter value */
        ptr_timer->UVALREP = ptr_base->repeate_count;
#else		
        if (ptr_base->count_mode == TIM_COUNT_PATTERN_DOWN)
        {
            /* Set the Repetition Counter value */
            ptr_timer->UVALREP = ptr_base->repeate_count + 1;
        }
        else {
            /* Set the Repetition Counter value */
            ptr_timer->UVALREP = ptr_base->repeate_count;
        }
#endif		
    }

    /*  update event to reload the Prescaler and the Repetition counter values  */    
    ptr_timer->SWEGR = TIM_PDIV_MODE_IMMEDIATE;           
}

/**
  * @fn void tim_base_struct_init(tim_base_t* ptr_base)
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  ptr_base: pointer to a tim_base_t structure which will be initialized.
  * @return None
  */
void tim_base_struct_init(tim_base_t* ptr_base)
{
    ptr_base->period = 0xFFFFFFFF;
    ptr_base->predivider = 0x0000;
    ptr_base->clk_division = TIM_CKDIV_DIV1;
    ptr_base->count_mode = TIM_COUNT_PATTERN_UP;
    ptr_base->repeate_count = 0x0000;
}

/**
  * @fn void tim_prescaler_set(tim_reg_t* ptr_timer, uint16_t value, uint16_t flag)
  * @brief  Configures the TIMx PDIV (pre-divider).
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.  
  * @param  value: specifies the Prescaler Register value
  * @param  flag: specifies the TIM Prescaler Reload mode, it be one of the following values:
  *          @arg TIM_PDIV_MODE_UPDATE (The Prescaler is loaded at the update event)
  *          @arg TIM_PDIV_MODE_IMMEDIATE (The Prescaler is loaded immediatly)
  * @return None
  */
void tim_prescaler_set(tim_reg_t* ptr_timer, uint16_t value, uint16_t flag)
{
    ASSERT(TIM_ALL_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_PDIV_MODE_CHECK(flag));
  
    /* Set the pre-divider value */
    ptr_timer->PDIV = value;
    /* Set or reset the UEG Bit */
    ptr_timer->SWEGR = flag;
}

/**
  * @fn void tim_count_pattern_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief Specifies the TIMx Counter Mode to be used.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, or 3.
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  value: specifies the Counter Mode to be used.
  *			It can be one of the following values:
  *          @arg TIM_COUNT_PATTERN_UP (TIM Up Counting)
  *          @arg TIM_COUNT_PATTERN_DOWN (TIM Down Counting)
  *          @arg TIM_COUNT_PATTERN_CENTER_ALIGNED1 (TIM Center Aligned 1)
  *          @arg TIM_COUNT_PATTERN_CENTER_ALIGNED2 (TIM Center Aligned 2)
  *          @arg TIM_COUNT_PATTERN_CENTER_ALIGNED3 (TIM Center Aligned 3)
  * @return None
  */
void tim_count_pattern_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST3_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_COUNT_PATTERN_CHECK(value));
  
    /* Set the count pattern selection */
	  MODIFY_REG(ptr_timer->CTR1, (uint16_t)(TIM_CTR1_DIR | TIM_CTR1_CPS), value);
}

/**
  * @fn void tim_update_request_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  select the TIMx Update Request Interrupt source.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, 7, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM6/15 is not available for CS32F036 devices.   
  * @param  value: specifies the Update source, it can be one of the following values:
  *          @arg TIM_UPDATE_SEL_REGULAR (Source of update is the counter overrun/underrun or
  *               the setting of UG bit, or an update generation through the slave mode controller)
  *          @arg TIM_UPDATE_SEL_GLOBAL (Source of update is counter overflow/underflow)
  * @return None
  */
void tim_update_request_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_ALL_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_UPDATE_SEL_CHECK(value));
  
	  MODIFY_REG(ptr_timer->CTR1, TIM_CTR1_URSEL, value);
}

/**
  * @fn void tim_pulse_mode_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief set the TIMx's Single pulse  Mode or repetitive mode.
  * @param  ptr_timer:pointer to TIMx where x can be 1, 2, 3, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices. 
  * @note   TIM15 is not available for CS32F036 devices.   
  * @param  value: It can be one of the following values:
  *          @arg TIM_PULSE_MODE_SINGLE 
  *          @arg TIM_PULSE_MODE_REPETITIVE
  * @return None
  */
void tim_pulse_mode_set(tim_reg_t* ptr_timer, uint16_t value)
{
	  ASSERT(TIM_ALL_TIMx_CHECK(ptr_timer));
  	ASSERT(TIM_PULSE_MODE_CHECK(value));
  
  	/* Configure the SPEN Mode */
  	MODIFY_REG(ptr_timer->CTR1, TIM_CTR1_SPEN, value);
}

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
void tim_clock_division_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_CKDIV_CHECK(value));

    /* Set the CKDIV value */
	  MODIFY_REG(ptr_timer->CTR1, TIM_CTR1_CKDIV, value);
}

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
void tim_protect_config(tim_reg_t* ptr_timer, tim_protect_t *ptr_protect)
{
    ASSERT(TIM_LIST2_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_RUNOS_CHECK(ptr_protect->run_offstate));
    ASSERT(TIM_IDLEOS_CHECK(ptr_protect->idle_offstate));
    ASSERT(TIM_LOCK_LEVEL_CHECK(ptr_protect->lock_level));
    ASSERT(TIM_BREAK_CHECK(ptr_protect->break_flag));
    ASSERT(TIM_BREAK_POLARITY_CHECK(ptr_protect->break_polarity));
    ASSERT(TIM_CHOPAEN_CHECK(ptr_protect->auto_output));
  
    ptr_timer->CHOPR = ptr_protect->run_offstate | ptr_protect->idle_offstate  |
                       ptr_protect->lock_level   | ptr_protect->dead_time      |
                       ptr_protect->break_flag   | ptr_protect->break_polarity |
                       ptr_protect->auto_output;
}

/**
  * @fn void tim_protect_struct_init(tim_protect_t* ptr_protect)
  * @brief  Fills each ptr_protect member with its default value.
  *         CHOPR(TIMx channel output protect register)
  * @param  ptr_protect: pointer to a tim_protect_t structure be initialized.
  * @return None
  */
void tim_protect_struct_init(tim_protect_t* ptr_protect)
{
    ptr_protect->run_offstate = TIM_RUNOS_DISABLE;
    ptr_protect->idle_offstate = TIM_IDLEOS_DISABLE;
    ptr_protect->lock_level = TIM_LOCK_LEVEL_OFF;
    ptr_protect->dead_time = 0x00;
    ptr_protect->break_flag = TIM_BREAK_DISABLE;
    ptr_protect->break_polarity = TIM_BREAK_POLARITY_LOW;
    ptr_protect->auto_output = TIM_CHOPAEN_DISABLE;
}

/**
  * @fn void tim_choc_init(tim_reg_t* ptr_timer, tim_choc_t* ptr_choc)
  * @brief  Initializes the TIMx channel4 output compare(CH4OC).
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16, 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @param  ptr_choc: pointer to a tim_choc_t structure that contains the 
  *         configuration for the specified TIM peripheral.
  * @return None
  */
void tim_choc_init(tim_reg_t* ptr_timer, tim_choc_t* ptr_choc)
{
	  uint8_t ch = 0x00;

    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer)); 
    ASSERT(TIM_ALL_CHANNEL_CHECK(ptr_choc->channel));		
    ASSERT(TIM_CHxOCMSEL_CHECK(ptr_choc->mode));
    ASSERT(TIM_CHx_OUTPUT_CHECK(ptr_choc->output_state));
    ASSERT(TIM_CHxCCP_POLARITY_CHECK(ptr_choc->polarity)); 
	  ASSERT(TIM_IVOx_CHECK(ptr_choc->idle_state));	
	  ASSERT(TIM_CHxNCCEN_CHECK(ptr_choc->output_state_n));
	  ASSERT(TIM_CHxNCCP_POLARITY_CHECK(ptr_choc->polarity_n));
	  ASSERT(TIM_IVOxN_CHECK(ptr_choc->idle_state_n));
		
    if((ptr_choc->mode == TIM_CHxOCMSEL_PWM1) && ((ptr_timer->CTR1 & 0x0010) == 0x10) && (ptr_timer->PDIV != 0))
    {
		    return;
    }

	  ch = ptr_choc->channel;

	  /* Disable the Channel : Reset the CH1CCEN Bit */
    ptr_timer->CCCTR &= ~(TIM_CCCTR_CH1CCEN << (ch * 4));
    
	  /* Select the Output Compare Mode */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], (TIM_CH12CFGR_CH1FS|TIM_CH12CFGR_CH1OCMSEL) << ((ch & 0x1) * 8), ptr_choc->mode << ((ch & 0x1) * 8));
    
	  /* Set the Output Compare Polarity and Output State */
  	MODIFY_REG(ptr_timer->CCCTR, (TIM_CCCTR_CH1CCP|TIM_CCCTR_CH1CCEN) << (ch * 4), (ptr_choc->polarity | ptr_choc->output_state) << (ch * 4));
        
	  if((ptr_timer == TIM1) || (ptr_timer == TIM15) || (ptr_timer == TIM16) || (ptr_timer == TIM17))
	  { 
		    /* Set the Output N Polarity and Output N State */
		    MODIFY_REG(ptr_timer->CCCTR, (TIM_CCCTR_CH1NCCP|TIM_CCCTR_CH1NCCEN) << (ch * 4), (ptr_choc->polarity_n | ptr_choc->output_state_n) << (ch * 4));		
        
		    /* Set the Output Idle state and Output N Idle state */
		    MODIFY_REG(ptr_timer->CTR2, (TIM_CTR2_IVO1|TIM_CTR2_IVO1N) << (ch * 2), (ptr_choc->idle_state | ptr_choc->idle_state_n) << (ch * 2));
	  }
      
	  ptr_timer->CHxCCVAL[ch] = ptr_choc->pulse;  
}

/**
  * @fn tim_choc_struct_init(tim_choc_t* ptr_choc)
  * @brief  Fills each ptr_choc member with its default value.
  * @param  ptr_choc: pointer to a tim_choc_t structure being initialized.    
  * @return None
  */
void tim_choc_struct_init(tim_choc_t* ptr_choc)
{
    ptr_choc->mode = TIM_CHxOCMSEL_TIMING;
    ptr_choc->output_state = TIM_CHx_OUTPUT_DISABLE;
    ptr_choc->output_state_n = TIM_CHxNCCEN_DISABLE;
    ptr_choc->pulse = 0;
    ptr_choc->polarity = TIM_CHxCCP_POLARITY_HIGH;
    ptr_choc->polarity_n = TIM_CHxCCP_POLARITY_HIGH;
    ptr_choc->idle_state = TIM_IVOx_RESET;
    ptr_choc->idle_state_n = TIM_IVOxN_RESET;
}   

/**
  * @fn void tim_choc_mode_set(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value)
  * @brief  Set the TIMx CHxOC mode selection.It must be disable the selected channel
  *         before changing the Output Compare Mode.     
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.     
  * @param  ch: specifies the TIM Channel.
  *			It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, for TIM1/2/3/14/15/16/17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, for TIM1/2/3/15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, for TIM1/2/3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, for TIM1/2/3.  
  * @param  mode: specifies the TIM Output Compare Mode
  *			It can be one of the following values:
  *          @arg TIM_CHxOCMSEL_TIMING
  *          @arg TIM_CHxOCMSEL_ACTIVE
  *          @arg TIM_CHxOCMSEL_INACTIVE
  *          @arg TIM_CHxOCMSEL_TOGGLE
  *          @arg TIM_CHxOCMSEL_PWM1
  *          @arg TIM_CHxOCMSEL_PWM2
  * @return None
  */
void tim_choc_mode_set(tim_reg_t* ptr_timer, uint16_t ch, uint16_t mode)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));  
    ASSERT(TIM_ALL_CHxOCMSEL_CHECK(mode));

	  /* Disable the Channel: clear the CHxCCEN Bit */
    ptr_timer->CCCTR &= ~(TIM_CCCTR_CH1CCEN << (ch * 4));
	
	  /* Configure The Forced output Mode */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], TIM_CH12CFGR_CH1OCMSEL << ((ch & 0x1) * 8), mode << ((ch & 0x1) * 8));
}

/**
  * @fn void tim_choc_forced_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Forces the TIMx channel waveform to active or inactive level.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.     
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.    
  * @param  value: specifies the forced Action to be set to the output waveform.
  *          It can be one of the following values:
  *           @arg TIM_CHxOCMSEL_FORCED_ACTIVE
  *           @arg TIM_CHxOCMSEL_FORCED_INACTIVE
  * @return None
  */
void tim_choc_forced_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));	
    ASSERT(TIM_CHxOCMSEL_FORCED_CHECK(value));

    /* Configure The Forced output Mode */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], TIM_CH12CFGR_CH1OCMSEL << ((ch & 0x1) * 8), value << ((ch & 0x1) * 8));
}

/**
  * @fn void tim_choc_preload_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Enables or disables the TIMx CH4OC(channel 4 output compare) Preload value.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.     
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.     
  * @param  value: new state of the TIMx peripheral Preload register
  *          It can be one of the following values:
  *           @arg TIM_CHxOC_PRELOAD_ENABLE
  *           @arg TIM_CHxOC_PRELOAD_DISABLE
  * @return None
  */
void tim_choc_preload_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
	  ASSERT(TIM_ALL_CHANNEL_CHECK(ch));		
    ASSERT(TIM_CHxOC_PRELOAD_CHECK(value));
  
    /* Enable or disable channel 4 output compare preload value */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], TIM_CH12CFGR_CH1OCVPEN << ((ch & 0x1) * 8), value << ((ch & 0x1) * 8));
}

/**
  * @fn void tim_choc_fast_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Set the TIMx CH1OC(channel 1 Output Compare) Fast feature.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.   
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.    
  * @param  value: new state of the Output Compare Fast Enable Bit.
  *          It can be one of the following values:
  *           @arg TIM_CHxOC_FAST_ENABLE (output compare fast enable)
  *           @arg TIM_CHxOC_FAST_DISABLE (output compare fast disable)
  * @return None
  */
void tim_choc_fast_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));	
    ASSERT(TIM_CHxOC_FAST_CHECK(value));

    /* Enable or disable channel 1 output compare fast feature */
    /* Config the CH1OCFEN bit */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], TIM_CH12CFGR_CH1OCFEN << ((ch & 0x1) * 8), value << ((ch & 0x1) * 8));
}

/**
  * @fn void tim_choc_clear_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Clears or safeguards the TIMx CH4OC(channel 4 Output Compare) signal on an external event.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.   
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.    
  * @param  value: new state of the Output Compare Clear Enable Bit.
  *          It can be one of the following values:
  *           @arg TIM_CHxOC_CLEAR_ENABLE (output compare clear enable)
  *           @arg TIM_CHxOC_CLEAR_DISABLE (output compare clear disable)
  * @return None
  */
void tim_choc_clear_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));	
    ASSERT(TIM_CHxOC_CLEAR_CHECK(value));

    /* Enable or disable channel 1 output compare fast feature */
    /* Config the CH1OCFEN bit */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], TIM_CH12CFGR_CH1OCCEN << ((ch & 0x1) * 8), value << ((ch & 0x1) * 8));
}

/**
  * @fn void tim_chcc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Configures the TIMx CHCC (channel complementary capture compare) polarity.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17.
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.   
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.   
  * @param  value: specifies the Polarity, It can be one of the following values:
  *          @arg TIM_CHxCCP_POLARITY_HIGH (Compare active high)
  *          @arg TIM_CHxCCP_POLARITY_LOW (Compare active low)    
  * @return None
  */
void tim_chcc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));		
    ASSERT(TIM_CHxCCP_POLARITY_CHECK(value));
    
    /* Config CHCCP bBit */
	  MODIFY_REG(ptr_timer->CCCTR, TIM_CCCTR_CH1CCP << (ch * 4), value << (ch * 4));	
}

/**
  * @fn void tim_chncc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Configures the TIMx CHNCC (channel complementary capture compare) polarity.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 15, 16 or 17.
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
void tim_chncc_polarity_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));		
    ASSERT(TIM_CHxNCCP_POLARITY_CHECK(value));
    
    /* Config CHNCCP bBit */
	  MODIFY_REG(ptr_timer->CCCTR, TIM_CCCTR_CH1NCCP << (ch * 4), value << (ch * 4));	
}


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
void tim_chcc_enable_ctrl(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer)); 
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));		    
    ASSERT(TIM_CHxCC_STATE_CHECK(value));

    /* config CHxCCEN bit */ 
    MODIFY_REG(ptr_timer->CCCTR, TIM_CCCTR_CHxCCEN_SET << (ch * 4), value << (ch * 4));	
}

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
void tim_chncc_enable_ctrl(tim_reg_t* ptr_timer, uint16_t ch, uint16_t value)
{
    ASSERT(TIM_LIST2_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_COMPLEMENTARY_CHANNEL_CHECK(ch));
    ASSERT(TIM_CHxNCC_STATE_CHECK(value));

    /* config CHxNCCEN bit */ 
    MODIFY_REG(ptr_timer->CCCTR, TIM_CCCTR_CHxNCCEN_SET << (ch * 4), value << (ch * 4));	    
}

/**
  * @fn void tim_chic_init(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic)
  * @brief  Initializes TIM CHxIC(channel input capture) according to the specified
  *         parameters in the ptr_chic.
  * @param  ptr_timer: pointer to TIMx where x can be  1, 2, 3, 14, 15, 16 or 17. 
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.   
  * @param  ch: specifies the channel.
  * 		It can be one of the following values:
  *			 @arg TIM_CHANNEL_1: TIM channel 1, only for TIM1, 2, 3, 14, 15, 16 or 17.
  *			 @arg TIM_CHANNEL_2: TIM channel 2, only for TIM1, 2, 3, 15.  
  *			 @arg TIM_CHANNEL_3: TIM channel 3, only for TIM1, 2, 3. 
  *			 @arg TIM_CHANNEL_4: TIM channel 4, only for TIM1, 2, 3.      
  * @param  ptr_chic: pointer to a tim_chic_t structure that contains 
  *         the configuration information for the specified TIM peripheral.
  * @return None
  */
void tim_chic_init(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ptr_chic->channel));  
    ASSERT(TIM_CHIC_SEL_CHECK(ptr_chic->select));
    ASSERT(TIM_CHIC_PREDIVIDE_CHECK(ptr_chic->predivider));
    ASSERT(TIM_CHxIC_FILTER_CHECK(ptr_chic->filter));
    ASSERT(TIM_CHxIC_POLARITY_CHECK(ptr_chic->polarity));
    
	  /* TIx Configuration */
	  tim_chic_config(ptr_timer, ptr_chic->channel, ptr_chic->polarity, ptr_chic->select,ptr_chic->filter);
	
	  /* Set the Input Capture Prescaler value */
	  tim_chic_predivider_set(ptr_timer, ptr_chic->channel, ptr_chic->predivider);
}

/**
  * @fn void tim_chic_struct_init(tim_chic_t* ptr_chic)
  * @brief  Fills each ptr_chic member with its default value.
  * @param  ptr_chic: pointer to a tim_chic_t structure which will be initialized.        
  * @return None
  */
void tim_chic_struct_init(tim_chic_t* ptr_chic)
{
    ptr_chic->channel = TIM_CHANNEL_1;
    ptr_chic->polarity = TIM_CHxIC_POLARITY_RISING;
    ptr_chic->select = TIM_CHIC_SEL_DIRECT_INTR;
    ptr_chic->predivider = TIM_CHIC_PREDIVIDE_DIV1;
    ptr_chic->filter = 0x00;
}

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
void tim_pwmi_config(tim_reg_t* ptr_timer, tim_chic_t* ptr_chic)
{
    uint16_t polarity = TIM_CHxIC_POLARITY_RISING;
    uint16_t select = TIM_CHIC_SEL_DIRECT_INTR;
  
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer));
  
    /* Select the Opposite Input Polarity */
    if (ptr_chic->polarity == TIM_CHxIC_POLARITY_RISING)
    {
        polarity = TIM_CHxIC_POLARITY_FALLING;
    }
    else
    {
        polarity = TIM_CHxIC_POLARITY_RISING;
    }
    /* Select the Opposite Input */
    if (ptr_chic->select == TIM_CHIC_SEL_DIRECT_INTR)
    {
        select = TIM_CHIC_SEL_INDIRECT_INTR;
    }
    else
    {
        select = TIM_CHIC_SEL_DIRECT_INTR;
    }
    if (ptr_chic->channel == TIM_CHANNEL_1)
    {
		    /* TI1 Configuration */
		    tim_chic_config(ptr_timer, TIM_CHANNEL_1, ptr_chic->polarity, ptr_chic->select,
                ptr_chic->filter);

		    /* Set the Input Capture Prescaler value */
		    tim_chic_predivider_set(ptr_timer, TIM_CHANNEL_1, ptr_chic->predivider);

        /* TI2 Configuration */
        tim_chic_config(ptr_timer, TIM_CHANNEL_2, polarity, select, ptr_chic->filter);
        /* Set the Input Capture Prescaler value */
		    tim_chic_predivider_set(ptr_timer, TIM_CHANNEL_2, ptr_chic->predivider);	
    }
    else
    { 
        /* TI2 Configuration */
        tim_chic_config(ptr_timer, TIM_CHANNEL_2, ptr_chic->polarity, ptr_chic->select,
               ptr_chic->filter);

        /* Set the Input Capture Prescaler value */
        tim_chic_predivider_set(ptr_timer, TIM_CHANNEL_2, ptr_chic->predivider);

        /* TI1 Configuration */
        tim_chic_config(ptr_timer, TIM_CHANNEL_1, polarity, select, ptr_chic->filter);
        /* Set the Input Capture Prescaler value */
        tim_chic_predivider_set(ptr_timer, TIM_CHANNEL_1, ptr_chic->predivider);
    }
}

/**
  * @fn void tim_chic_predivider_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
  * @brief  Sets the TIMx CH4IC (channel 4 Input Capture) pre-divide.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2 or 3, 14, 15, 16 or 17.  
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
void tim_chic_predivider_set(tim_reg_t* ptr_timer, uint8_t ch, uint16_t value)
{
    ASSERT(TIM_LIST4_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ALL_CHANNEL_CHECK(ch));	
    ASSERT(TIM_CHIC_PREDIVIDE_CHECK(value));

    /* Set the CH4ICPDIV  bits */
	  MODIFY_REG(ptr_timer->CHxCFGR[ch >> 1], TIM_CH12CFGR_CH1ICPDIV << ((ch & 0x1) * 8), value << ((ch & 0x1) * 8));
}

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
void tim_dma_access_config(tim_reg_t* ptr_timer, uint16_t addr, uint16_t len)
{
    ASSERT(TIM_LIST5_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_DMA_BASE_CHECK(addr)); 
    ASSERT(TIM_DMA_TRANSFER_LEN_CHECK(len));
    
    /* Set the DMA Base and the DMA Burst Length */
    ptr_timer->DMAACR = addr | len;
}

/**
  * @fn void tim_internal_clock_config(tim_reg_t* ptr_timer)
  * @brief  Configures the TIMx internal Clock
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.  
  * @return None
  */
void tim_internal_clock_config(tim_reg_t* ptr_timer)
{
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer));
  
    /* Disable slave mode to clock the prescaler directly with the internal clock */
    ptr_timer->SMCFG &= ~(TIM_SMCFG_SMCFG);
}

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
void tim_internal_trigger_external_clock_config(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_INTERNAL_TRIGGER_SEL_CHECK(value));
  
    /* Select the Internal Trigger */
    tim_input_trigger_set(ptr_timer, value);
	
    /* Select the External clock mode1 */
    ptr_timer->SMCFG |= TIM_SLAVE_MODE_EXTERNAL1;
}

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
void tim_ti_external_clock_config(tim_reg_t* ptr_timer, uint16_t value, uint16_t polarity, uint16_t filter)                                
{
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_CHxIC_POLARITY_CHECK(polarity));
    ASSERT(TIM_CHxIC_FILTER_CHECK(filter));
  
    /* Configure the Timer Input Clock Source */
    if (value == TIM_TIMx_EXTlCLK1_SOURCE_TI2)
    {
        tim_chic_config(ptr_timer, TIM_CHANNEL_2, polarity, TIM_CHIC_SEL_DIRECT_INTR, filter);
    }
    else
    {
        tim_chic_config(ptr_timer, TIM_CHANNEL_1, polarity, TIM_CHIC_SEL_DIRECT_INTR, filter);
    }
  
    /* Select the Trigger source */
    tim_input_trigger_set(ptr_timer, value); 
	
    /* Set the External Clock mode1 */ 
    ptr_timer->SMCFG |= TIM_SLAVE_MODE_EXTERNAL1;
}

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
void tim_external_clock_mode1_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity,uint16_t filter)                             
{
    ASSERT(TIM_LIST3_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_EXT_TRG_PDIV_CHECK(divide));
    ASSERT(TIM_EXT_TRG_POLARITY_CHECK(polarity));
    ASSERT(TIM_EXT_FILTER_CHECK(filter));
  
    /* Configure the ETR Clock source */
    tim_external_trigger_config(ptr_timer, divide, polarity, filter);
  
    /* Select the External clock mode1 */
	  MODIFY_REG(ptr_timer->SMCFG, (TIM_SMCFG_SMCFG|TIM_SMCFG_TRIGS), (TIM_SLAVE_MODE_EXTERNAL1|TIM_TRIGGER_SEL_EXTERNAL));
}

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
void tim_external_clock_mode2_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity, uint16_t filter)                            
{
    ASSERT(TIM_LIST3_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_EXT_TRG_PDIV_CHECK(divide));
    ASSERT(TIM_EXT_TRG_POLARITY_CHECK(polarity));
    ASSERT(TIM_EXT_FILTER_CHECK(filter));
  
    /* Configure the ETR Clock source */
    tim_external_trigger_config(ptr_timer, divide, polarity, filter);
	
    /* Enable the External clock mode2 */
    ptr_timer->SMCFG |= TIM_SMCFG_ECMODE2;
}

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
void tim_external_trigger_config(tim_reg_t* ptr_timer, uint16_t divide, uint16_t polarity, uint16_t filter)                                                                             
{
    ASSERT(TIM_LIST3_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_EXT_TRG_PDIV_CHECK(divide));
    ASSERT(TIM_EXT_TRG_POLARITY_CHECK(polarity));
    ASSERT(TIM_EXT_FILTER_CHECK(filter));
    
	  MODIFY_REG(ptr_timer->SMCFG, TIM_SMCFG_ET_MASK, divide | polarity | (filter << 8));
}

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
void tim_input_trigger_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer)); 
    ASSERT(TIM_TRIGGER_SEL_CHECK(value));

    /* Write to SMCFG */
	  MODIFY_REG(ptr_timer->SMCFG, TIM_SMCFG_TRIGS, value);
}

/**
  * @fn void tim_trigger_output_set(tim_reg_t* ptr_timer, uint16_t value)
  * @brief  Selects the TIMx Trigger Output Mode.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 6, or 15.  
  * @note   TIM2 is only available for CS32F031 devices.
  * @note   TIM15 is not available for CS32F036 devices.
  * @param  value: specifies the Trigger Output source, it can be one of the following values:
  *         for all TIMx: 
  *          @arg TIM_TRG_OUTPUT_SEL_RESET
  *          @arg TIM_TRG_OUTPUT_SEL_ENABLE
  *          @arg TIM_TRG_OUTPUT_SEL_UPDATE
  *         for all TIMx except TIM6: 
  *          @arg TIM_TRG_OUTPUT_SEL_CH1OC
  *          @arg TIM_TRG_OUTPUT_SEL_CH1OC_REF
  *          @arg TIM_TRG_OUTPUT_SEL_CH2OC_REF
  *          @arg TIM_TRG_OUTPUT_SEL_CH3OC_REF
  *          @arg TIM_TRG_OUTPUT_SEL_CH4OC_REF 
  * @return None
  */
void tim_trigger_output_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST9_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_TRG_OUTPUT_SEL_CHECK(value));

    /* Reset the MMTOC bits */
	  MODIFY_REG(ptr_timer->CTR2, TIM_CTR2_MMTOC, value);
}

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
void tim_slave_mode_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer)); 
    ASSERT(TIM_SLAVE_MODE_CHECK(value));
  
    /* Select the slave mode */
	  MODIFY_REG(ptr_timer->SMCFG, TIM_SMCFG_SMCFG, value);	
}

/**
  * @fn void tim_master_slave_control(tim_reg_t* ptr_timer, uint16_t value)
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
void tim_master_slave_set(tim_reg_t* ptr_timer, uint16_t value)
{
    ASSERT(TIM_LIST6_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_MASTER_SLAVE_MODE_CHECK(value));
    
    /* config the SMCFG_MSM bit */
	  MODIFY_REG(ptr_timer->SMCFG, TIM_SMCFG_MSM, value);
}

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
void tim_encoder_interface_set(tim_reg_t* ptr_timer, uint16_t mode, uint16_t polarity, uint16_t value)                               
{
    ASSERT(TIM_LIST3_TIMx_CHECK(ptr_timer));
    ASSERT(TIM_ENCODER_MODE_CHECK(mode));
    ASSERT(TIM_CHxIC_POLARITY_CHECK(polarity));
    ASSERT(TIM_CHxIC_POLARITY_CHECK(value));

	  /* Set the encoder Mode */
	  MODIFY_REG(ptr_timer->SMCFG, TIM_SMCFG_SMCFG, mode);
	
	  MODIFY_REG(ptr_timer->CHxCFGR[0], TIM_CH12CFGR_CH1FS|TIM_CH12CFGR_CH2FS, TIM_CH12CFGR_CH1FS_0|TIM_CH12CFGR_CH2FS_0);

	  /* Set the TI1 and the TI2 Polarities */
	  MODIFY_REG(ptr_timer->CCCTR , TIM_CCCTR_CH1CCP|TIM_CCCTR_CH1NCCP|TIM_CCCTR_CH2CCP|TIM_CCCTR_CH2NCCP, polarity | (value << 4));
}

/**
  * @fn static void tim_chic_config(tim_reg_t* ptr_timer, uint16_t polarity, uint16_t select, uint16_t filter) 
  * @brief  Configure the Channel1 as Input.
  * @param  ptr_timer: pointer to TIMx where x can be 1, 2, 3, 14, 15, 16 or 17 .  
  * @note   TIM2 is only available for CS32F031 devices.   
  * @note   TIM15 is not available for CS32F036 devices.  
  * @param  polarity: The Input Polarity, it can be one of the following values:
  *          @arg TIM_CHxIC_POLARITY_RISING
  *          @arg TIM_CHxIC_POLARITY_FALLING
  * @param  select: specifies the input to be used, it can be one of the following values:
  *          @arg TIM_CHIC_SEL_DIRECT_INTR
  *          @arg TIM_CHIC_SEL_INDIRECT_INTR
  *          @arg TIM_CHIC_SEL_TRC
  * @param  filter: Specifies the Input Capture Filter, the value between 0x00 and 0x0F
  * @return None
  */
static void tim_chic_config(tim_reg_t* ptr_timer, uint8_t ch, uint16_t polarity, uint16_t select, uint16_t filter)                       
{
    uint8_t idx = 0x00;
	  uint8_t shift = 0x00;

	  idx = ch >> 1;
	  shift = ch & 0x1;

    /* Disable the Channel 1: clear the CH1CCEN Bit */
    ptr_timer->CCCTR &= ~(TIM_CCCTR_CH1CCEN << (ch * 4));

	  /* Select the Input and set the filter */
	  MODIFY_REG(ptr_timer->CHxCFGR[idx], (TIM_CH12CFGR_CH1FS|TIM_CH12CFGR_CH1ICFLT) << (shift * 8), (select | (filter << 4)) << (shift * 8));

	  /* Select the Polarity and set the CH1CCEN bit */	
	  MODIFY_REG(ptr_timer->CCCTR, (TIM_CCCTR_CH1CCP|TIM_CCCTR_CH1NCCP) << (ch * 4), (polarity | TIM_CCCTR_CH1CCEN) << (ch * 4));
}

/**
  * @}
  */
 
/**
  * @}
  */

