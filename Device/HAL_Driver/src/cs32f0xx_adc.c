/**
  * @file    cs32f0xx_adc.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + Power saving
  *           + Analog Watchdog configuration
  *           + Temperature Sensor, Vrefint (Internal Reference Voltage) and 
  *             Vbat (Voltage battery) management 
  *           + ADC Channels Configuration
  *           + ADC Channels DMA Configuration
  *           + Interrupts and flags management
  *
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim
  ----------------------- this driver instruction for use--------------------------- 
    1.ADC clock configuration:
      a. Enable the ADC interface clock using 
        rcu_apb2_periph_clock_enable_ctrl(RCU_APB2_PERI_ADC, ENABLE); 
      b. ADC pins configuration:
       (1) Enable the clock for the ADC GPIOs using the following function:
            rcu_ahb_periph_clock_enable_ctrl(RCC_AHBPeriph_GPIOx, ENABLE);   
       (2) Configure these ADC pins in analog mode using gpio_init();  
      c. Configure the ADC conversion resolution, data alignment, external
        trigger and edge, scan direction and Enable/Disable the continuous mode
        using the adc_init() function.
      d. Activate the ADC peripheral using adc_enable_ctrl() function.

    2.ADC channels group configuration:
      a. To configure the ADC channels features, use adc_init() and 
        adc_channel_config() functions.
      b. To activate the continuous mode, use the adc_continuous_mode_enable_ctrl()
        function.
      c. To activate the Discontinuous mode, use the adc_discontinuous_mode_enable_ctrl() functions. 
      d. To activate the overrun mode, use the adc_overrun_mode_enable_ctrl() functions.
      e. To activate the calibration mode, use the adc_calibration_value_get() functions.
      f. To read the ADC converted values, use the adc_conversion_value_get()
        function.

    3.DMA for ADC channels features configuration:
      a. To enable the DMA mode for ADC channels group, use the adc_dma_enable_ctrl() function.
      b. To configure the DMA transfer request, use adc_dma_mode_set() function.
  * @endverbatim
  *
  */

#include "cs32f0xx_adc.h"
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup ADC
  * @{
  */


/** 
  * @brief ADC CFG mask definition
  */ 
#define ADC_CFG_CLEAR_MASK			((uint32_t)0x00002DFC)

/** 
  * @brief ADC Calibration time out definition  
  */ 
#define ADC_CALIBRATION_TIMEOUT		((uint32_t)0x0000F000)


/**
  * @fn void adc_def_init(adc_reg_t* ptr_adc)
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc_def_init(adc_reg_t* ptr_adc)
{
    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));

    if (ptr_adc == ADC1)
    {
        /* Enable ADC1 reset state */
		__RCU_PERI_RST_ENABLE(ADC);
		
        /* Release ADC1 from reset state */
		__RCU_PERI_RST_DISABLE(ADC);
		
#if defined (CS32F030) || defined (CS32F031)		
        ptr_adc->STAT = 0x00000000;
        ptr_adc->INTEN = 0x00000000;
        ptr_adc->CTR = 0x00000000;
        ptr_adc->CFG = 0x00000000;
        ptr_adc->CLK = 0x00000000;
        ptr_adc->SMPLR = 0x00000000;
        ptr_adc->WDTH = 0x0FFF0000;
        ptr_adc->CHANSEL = 0x00000000;
        ptr_adc->OUTDAT = 0x00000000;
        ptr_adc->INTEN = 0x00000000;
#endif
    }
}

/**
  * @fn void adc_init(adc_reg_t* ptr_adc, adc_config_t* ptr_config)
  * @brief  Initializes the ADCx peripheral according to the specified parameters.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @param  ptr_config: pointer to an adc_config_t structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @return None
  */
void adc_init(adc_reg_t* ptr_adc, adc_config_t* ptr_config)
{
    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
    ASSERT(ADC_CONV_RES_CHECK(ptr_config->adc_resolution));
    ASSERT(FUNCTIONAL_STATE_CHECK(ptr_config->continuous_mode));
    ASSERT(ADC_TRIG_MODE_CHECK(ptr_config->trigger_mode));
    ASSERT(ADC_HW_TRIG_CHECK(ptr_config->hardware_trigger));
    ASSERT(ADC_DATA_ALIGN_CHECK(ptr_config->data_align));
    ASSERT(ADC_SCAN_DIR_CHECK(ptr_config->scan_direction)); 

    /* Config CGDIR, DATRES[1:0], DATALG, HTRGSEL[2:0], TRGMODE[1:0] and GCONT bits in ADCx CFG register*/
	MODIFY_REG(ptr_adc->CFG, ADC_CFG_CLEAR_MASK, (uint32_t)(ptr_config->adc_resolution | ((uint32_t)(ptr_config->continuous_mode) << 13) |
             ptr_config->trigger_mode | ptr_config->hardware_trigger | ptr_config->data_align | ptr_config->scan_direction));
}

/**
  * @fn void adc_config_struct_init(adc_config_t* ptr_config)
  * @brief  Fills each ptr_config member with its default value.
  * @param  ptr_config: pointer to an adc_config_t structure which will be initialized.
  * @return None
  */
void adc_config_struct_init(adc_config_t* ptr_config)
{
    /* Initialize the adc_resolution parameter */
    ptr_config->adc_resolution = ADC_CONV_RES_12BITS;
    ptr_config->continuous_mode = DISABLE;
    ptr_config->trigger_mode = ADC_TRIG_MODE_NONE;
    ptr_config->hardware_trigger = ADC_HW_TRIG_0;
    ptr_config->data_align = ADC_DATA_ALIGN_RIGHT;
    ptr_config->scan_direction = ADC_SCAN_DIR_UPWARD;
}

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
void adc_watchdog_channel_select(adc_reg_t* ptr_adc, uint32_t value)
{
	ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
  	ASSERT(ADC_WATCHDOG_CHANNEL_CHECK(value));

  	/* Set the Analog watchdog channel value */
  	MODIFY_REG(ptr_adc->CFG, ADC_CFG_WDGCHAN, value);
}

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
void adc_channel_config(adc_reg_t* ptr_adc, uint32_t channel, uint32_t time)
{
    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
    ASSERT(ADC_CONV_CHANNEL_CHECK(channel));
    ASSERT(ADC_SAMPLE_TIMES_CHECK(time));

    /* Configure the ADC Channel */
    ptr_adc->CHANSEL |= channel;
  
    /* Set the Sampling time register */
    ptr_adc->SMPLR = time;
}

/**
  * @fn uint32_t adc_calibration_value_get(adc_reg_t* ptr_adc)
  * @brief  Active the Calibration operation for the selected ADC, the Calibration can be 
  *         initiated only when ADC is still in the reset configuration (ADCON must be equal to 0).    
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return ADC Calibration factor 
  */
uint32_t adc_calibration_value_get(adc_reg_t* ptr_adc)
{
    uint32_t reg = 0;
    uint32_t count = 0;
    uint32_t status = 0;

    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
  
    /* Set the ADC calibartion */
    ptr_adc->CTR |= ADC_CTR_CALB;
  
    /* Wait until no ADC calibration is completed */
    do
    {
        status = ptr_adc->CTR & ADC_CTR_CALB;
        count++;  
    } while ((count != ADC_CALIBRATION_TIMEOUT) && (status != 0x00));
    
    if ((uint32_t)(ptr_adc->CTR & ADC_CTR_CALB) == RESET)
    {
        /*Get the calibration data */
        reg = ptr_adc->OUTDAT;
    }
    else
    {
        /* Error factor */
        reg = 0x00000000;
    }
	
    return reg;
}

/**
  * @fn void adc_conversion_start(adc_reg_t* ptr_adc)
  * @brief  Start Conversion for the selected ADC channels.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc_conversion_start(adc_reg_t* ptr_adc)
{
    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
  
    ptr_adc->CTR |= ADC_CTR_ADSTOP; 
    ptr_adc->CTR |= ADC_CTR_ADSTRT;
}

/**
  * @fn void adc_conversion_stop(adc_reg_t* ptr_adc)
  * @brief  Stop the on going conversions for the selected ADC. When ADSTOP is set, any on going
  *         conversion is aborted, and the ADC data register is not updated with current conversion.    
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc_conversion_stop(adc_reg_t* ptr_adc)
{
    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
    ptr_adc->CTR |= ADC_CTR_ADSTOP;
}

/**
  * @fn void adc_dma_mode_set(adc_reg_t* ptr_adc, uint32_t mode)
  * @brief  Enables or disables the ADC DMA request after last transfer (Single-ADC mode)
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @param  mode: the ADC channel to configure, it can be
  *          @arg ADC_DMA_MODE_SINGLE(DMA single mode)
  *          @arg ADC_DMA_MODE_CIRCULAR (DMA circular mode)
  *  @return None
  */
void adc_dma_mode_set(adc_reg_t* ptr_adc, uint32_t mode)
{
    ASSERT(ADC_ALL_LIST_CHECK(ptr_adc));
	ASSERT(ADC_DMA_MODE_CHECK(mode));
	
	MODIFY_REG(ptr_adc->CFG, ADC_CFG_DMAMODE, mode);
}


/**
  * @}
  */ 

/**
  * @}
  */ 

