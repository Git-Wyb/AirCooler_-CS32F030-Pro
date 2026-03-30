/**
  * @file    cs32f0xx_rcu.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Reset and clock unit (RCU) peripheral:
  *           + Internal/external clocks, PLL, CSS and CLKOUT configuration
  *           + System, AHB and APB busses clocks configuration
  *           + Peripheral clocks configuration
  *           + Interrupts and flags management
  *
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.11.01         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
    1. After reset the device is running from HRC (8 MHz) ,all peripherals  are off except
          internal SRAM, Flash and SWD.
         a. There is no prescaler on High speed (AHB) and Low speed (APB) busses;
             all peripherals mapped on these busses are running at HRC speed.
         b. The clock for all peripherals is switched off, except the SRAM and FLASH.
         c. All GPIOs are in input floating state, except the SWD pins which are assigned
              to be used for debug purpose.
    2. Once the device started from reset, the user application has to:
         a. Configure the clock source to be used to drive the System clock
             (if the application needs higher frequency/performance)
         b. Configure the System clock frequency and Flash settings
         c. Configure the AHB and APB busses prescalers
         d. Enable the clock for the peripheral(s) to be used
         e. Configure the clock source(s) for peripherals which clocks are not
             derived from the System clock (ADC, CEC, I2C, USART, RTC and FWDT)

 @endverbatim
  *
  */
  
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup RCU
  * @brief RCU driver modules
  * @{
  */ 


static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @fn void rcu_def_init(void)
  * @brief  Resets the RCU clock configuration to the default reset state.
  * @note   The default reset state including HRC ON and used as system clock source HRC14, HXT and PLL OFF AHB, APB 
  *         prescaler is set to 1, CSS and CLKOUT is off.  All interrupts is disabled, but it doesn't modify the
  *         configuration of the peripheral clocks LRC, LXT and RTC clocks.
  * @param  None.
  * @return None.
  */
void rcu_def_init(void)
{
    /* Set HRCEN bit */
    RCU->CTR |= RCU_CTR_HRCEN;

    /* Reset SYSSW[1:0], HCLKPDIV[3:0], PCLKPDIV[2:0], ADCPDIV, CKOSEL[2:0], CKOPDIV[2:0] and CKOPLLND bits */
    RCU->CFG &= ~(RCU_CFG_SYSSW | RCU_CFG_HCLKPDIV | RCU_CFG_PCLKPDIV | RCU_CFG_ADCPDIV | RCU_CFG_CKOSEL | \
                  RCU_CFG_CKOPDIV | RCU_CFG_CKOPLLND);
  
    /* Reset HXTON, HXTME and PLLEN bits */
    RCU->CTR &= ~(RCU_CTR_HXTEN | RCU_CTR_HXTME | RCU_CTR_PLLEN);

    /* Reset HXTBPS bit */
    RCU->CTR &= ~RCU_CTR_HXTBPS;   

    /* Reset PLLSEL, PLLHXTPDIV and PLLMUF[3:0] bits */
    RCU->CFG &= ~(RCU_CFG_PLLSEL | RCU_CFG_PLLHXTPDIV | RCU_CFG_PLLMUF);
    
    /* Reset PLLPDIV[3:0] bits */
    RCU->CFG2 &= ~RCU_CFG2_PLLPDIV1;

    /* Reset USARTSEL[1:0], I2CSEL bits */
    RCU->CFG3 &= ~(RCU_CFG3_USART1SEL | RCU_CFG3_I2C1SEL);
  
    /* Reset HRC14 bit */
    RCU->CTR2 &= ~RCU_CTR2_HRC14EN;

    /* Disable all interrupts */
    RCU->INTR = 0x00000000;
}

/**
  * @fn error_status_t rcu_hxt_stabilization_wait(void)
  * @brief  Waits for HXT stabilization. It waits on HSERDY flag to be set and return SUCCESS. The HXT is stopped by  
  *         hardware when entering STOP and STANDBY modes.
  * @param  None.
  * @return SUCCESS(oscillator is stable) or ERROR(oscillator not yet stable).
  */
error_status_t rcu_hxt_stabilization_wait(void)
{
    __IO uint32_t counter = 0;
    error_status_t flag = ERROR;
    uint32_t status = 0;
  
    /* Wait till HXT is stable and if timeout is reached exit */
    do
    {
        status = RCU->CTR & RCU_CTR_HXTSTAB;
        counter++;  
    }while((counter != HXT_STARTUP_TIMEOUT) && (status == 0));
  
    if(RCU->CTR & RCU_CTR_HXTSTAB)
    {
        flag = SUCCESS;
    }
    else
    {
        flag = ERROR;
    } 
    
    return flag;
}

/**
  * @fn void rcu_hrc_calibration_adjust(uint8_t value)
  * @brief  Adjusts the internal high speed RC (HRC) calibration value.
  * @param  value: specifies the HRC calibration trimming value (between 0 and 0x1F).
  * @return None.
  */
void rcu_hrc_calibration_adjust(uint8_t value)
{
    ASSERT(RCU_HRC_CALI_VALUE_CHECK(value));
    
    MODIFY_REG(RCU->CTR, RCU_CTR_HRCTRIM, (uint32_t)value << 3);
}

/**
  * @fn void rcu_hrc14_calibration_adjust(uint8_t value)
  * @brief  Adjusts the Internal high speed RC14 for ADC (HRC14) calibration value.
  * @param  value: specifies the HRC14 calibration trimming value. This parameter must be a number between 0 and 0x1F.
  * @return None.
  */
void rcu_hrc14_calibration_adjust(uint8_t value)
{
    ASSERT(RCU_HRC14_CALI_VALUE_CHECK(value));
    
    MODIFY_REG(RCU->CTR2, RCU_CTR2_HRC14TRIM, (uint32_t)value << 3);
}

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
void rcu_hxt_drive_config(uint32_t value)
{ 
    ASSERT(RCU_HXT_DRIVE_CHECK(value));

    MODIFY_REG(RCU->CTR, RCU_CTR_HXTDRV, value);
}

/**
  * @fn void rcu_lxt_drive_config(uint32_t value)
  * @brief  Configures the external low speed crystal oscillator (LXT) drive capability.
  * @param  value: specifies the new state of the LXT drive capability. It can be one of the following values:
  *         @arg RCU_LXT_DRIVE_LEVEL_0(LXT oscillator low drive capability)
  *         @arg RCU_LXT_DRIVE_LEVEL_1(LXT oscillator medium low drive capability)
  *         @arg RCU_LXT_DRIVE_LEVEL_2(LXT oscillator medium high drive capability)
  *         @arg RCU_LXT_DRIVE_LEVEL_3(LXT oscillator high drive capability)
  * @return None.
  */
void rcu_lxt_drive_config(uint32_t value)
{ 
    ASSERT(RCU_LXT_DRIVE_CHECK(value));

    MODIFY_REG(RCU->VBDC, RCU_VBDC_LXTDRV, value);
}

/**
  * @fn void rcu_pll_config(uint32_t sel_value, uint32_t multiple)
  * @brief  Configures the PLL clock source and multiplication factor. It must be used only when the PLL is disabled.
  * @param  sel_value: specifies the PLL selected clock source. It can be one of the following values:
  *         @arg RCU_PLL_CFG_HRC (HRC oscillator clock selected as PLL clock source)
  *         @arg RCU_PLL_CFG_HXT_DIV1 (HXT/1 clock selected as PLL clock source)
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
void rcu_pll_config(uint32_t source, uint32_t multiple)
{
    ASSERT(RCU_PLL_CFG_CHECK(source));
    ASSERT(RCU_PLL_MULTI_CHECK(multiple));
    
	MODIFY_REG(RCU->CFG2, RCU_CFG2_PLLPDIV1, source & RCU_CFG2_PLLPDIV1);
	MODIFY_REG(RCU->CFG, (RCU_CFG_PLLMUF | RCU_CFG_PLLSEL), (source & RCU_CFG_PLLSEL) | multiple);
}

/**
  * @fn void rcu_clkout_config(uint8_t sel_value, uint32_t prescaler)
  * @brief  Selects the clock source to output on CLKOUT pin (PA8). It should be configured in  multi-function mode.
  * @param  sel_value: specifies the clock source to output, it can be one of the following values:
  *         @arg RCU_CLKOUT_SEL_NO_CLK(No clock selected)
  *         @arg RCU_CLKOUT_SEL_HRC14(HRC14 oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_LRC(LRC oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_LXT( LXT oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_SYSCLK(System clock selected)
  *         @arg RCU_CLKOUT_SEL_HRC(HRC oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_HXT(HXT oscillator clock selected)
  *         @arg RCU_CLKOUT_SEL_PLL_DIV2(PLL clock divided by 2 selected)
  * @param  prescaler: specifies the prescaler on CLKOUT pin, it can be one of the following values:
  *         @arg RCU_CLKOUT_PDIV_1(CLKOUT clock is divided by 1)
  *         @arg RCU_CLKOUT_PDIV_2(CLKOUT clock is divided by 2)
  *         @arg RCU_CLKOUT_PDIV_4(CLKOUT clock is divided by 4)
  *         @arg RCU_CLKOUT_PDIV_8(CLKOUT clock is divided by 8)
  *         @arg RCU_CLKOUT_PDIV_16(CLKOUT clock is divided by 16)
  *         @arg RCU_CLKOUT_PDIV_32(CLKOUT clock is divided by 32)
  *         @arg RCU_CLKOUT_PDIV_64(CLKOUT clock is divided by 64)
  *         @arg RCU_CLKOUT_PDIV_128(CLKOUT clock is divided by 128)   
  * @return None.
  */
void rcu_clkout_config(uint8_t sel_value, uint32_t prescaler)
{
    ASSERT(RCU_CLKOUT_SEL_CHECK(sel_value));
    ASSERT(RCU_CLKOUT_PDIV_CHECK(prescaler));
    
    MODIFY_REG(RCU->CFG, (RCU_CFG_CKOPDIV | RCU_CFG_CKOSEL | RCU_CFG_CKOPLLND),  prescaler | ((uint32_t)sel_value << 24));
}

/**
  * @fn void rcu_sysclk_config(uint32_t value)
  * @brief  Configures the system clock (SYSCLK).  
  * @param  value: specifies the clock source used as system clock. It can be one of the following values:
  *         @arg RCU_SYSCLK_SEL_HRC (HRC selected as system clock)
  *         @arg RCU_SYSCLK_SEL_HXT (HXT selected as system clock)
  *         @arg RCU_SYSCLK_SEL_PLL (PLL selected as system clock)
  * @return None.
  */
void rcu_sysclk_config(uint32_t value)
{
    ASSERT(RCU_SYSCLK_SEL_CHECK(value));
    
    MODIFY_REG(RCU->CFG, RCU_CFG_SYSSW, value);
}

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
void rcu_hclk_config(uint32_t value)
{ 
    ASSERT(RCU_HCLK_CFG_CHECK(value));
    
    MODIFY_REG(RCU->CFG, RCU_CFG_HCLKPDIV, value);
}

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
void rcu_pclk_config(uint32_t value)
{
    ASSERT(RCU_PCLK_CFG_CHECK(value));

    MODIFY_REG(RCU->CFG, RCU_CFG_PCLKPDIV, value);
}

/**
  * @fn void rcu_i2cclk_config(uint32_t value)
  * @brief  Configures the I2C1 clock (I2C1CLK).
  * @param  value: defines the I2C1 clock source which is derived from the HRC or system clock. It can be one of the 
  *         following values:
  *         @arg RCU_I2C1CLK_CFG_HRC (I2C1 clock = HRC)
  *         @arg RCU_I2C1CLK_CFG_SYSCLK (I2C1 clock = System Clock)
  * @return None.
  */
void rcu_i2cclk_config(uint32_t value)
{   
    ASSERT(RCU_I2C1CLK_CFG_CHECK(value));
    
    MODIFY_REG(RCU->CFG3, RCU_CFG3_I2C1SEL, value); 
}

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
void rcu_usartclk_config(uint32_t value)
{
    ASSERT(RCU_USARTxCLK_CFG_CHECK(value));

     MODIFY_REG(RCU->CFG3, RCU_CFG3_USART1SEL, value); 
}

/**
  * @fn void rcu_rtcclk_config(uint32_t value)
  * @brief  Configures the RTC clock (RTCCLK).           
  * @param  value: specifies the RTC clock source, it can be one of the following values:
  *         @arg RCU_RTCCLK_SEL_LXT(LXT selected as RTC clock)
  *         @arg RCU_RTCCLK_SEL_LRC(LRC selected as RTC clock)
  *         @arg RCU_RTCCLK_SEL_HXT_DIV32(HXT divided by 32 selected as RTC clock)                                  
  * @return None.
  */
void rcu_rtcclk_config(uint32_t value)
{
    ASSERT(RCU_RTCCLK_SEL_CHECK(value));
  
    /* Select the RTC clock source */
    RCU->VBDC |= value;
}

/**
  * @fn void rcu_clk_freq_get(rcu_clock_t* ptr_clock)
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.             
  * @param  ptr_clock: pointer to a rcu_clock_t structure which will hold the clocks frequencies.  
  * @return None.
  */
void rcu_clk_freq_get(rcu_clock_t* ptr_clock)
{
    uint32_t temp = 0;
    uint32_t divide = 0;  
    uint32_t presc = 0;
    uint32_t pll_mull = 0;
    uint32_t pll_sel = 0;
    uint32_t pll_clk = 0;

    temp = RCU->CFG & RCU_CFG_SYSSS;
  
    switch (temp)
    {
        case 0x00:  /* HRC used as system clock */
            ptr_clock->system_clk_freq = HRC_VALUE;
            break;

        case 0x04:  /* HXT used as system clock */
            ptr_clock->system_clk_freq = HXT_VALUE;
            break;

        case 0x08:  /* PLL used as system clock */
            pll_mull = RCU->CFG & RCU_CFG_PLLMUF;
            pll_sel = RCU->CFG & RCU_CFG_PLLSEL;
            pll_mull = ( pll_mull >> 18) + 2;
      
            if (pll_sel == 0x00)
            {
                /* HRC oscillator clock divided by 2 selected as PLL clock entry */
                pll_clk = (HRC_VALUE >> 1) * pll_mull;
            }
            else
            {
                divide = (RCU->CFG2 & RCU_CFG2_PLLPDIV1) + 1;
                /* HXT oscillator clock selected as PLLPDIV clock entry */
                pll_clk = (HXT_VALUE / divide) * pll_mull; 
            }
            ptr_clock->system_clk_freq = pll_clk;      
            break;

        default: /* HRC used as system clock */
            ptr_clock->system_clk_freq = HRC_VALUE;
            break;
    }
  
    /* Get HCLK prescaler */
    temp = RCU->CFG & RCU_CFG_HCLKPDIV;
    temp = temp >> 4;
    presc = APBAHBPrescTable[temp]; 
    /* HCLK clock frequency */
    ptr_clock->hclk_freq = ptr_clock->system_clk_freq >> presc;

    /* Get PCLK prescaler */
    temp = RCU->CFG & RCU_CFG_PCLKPDIV;
    temp = temp >> 8;
    presc = APBAHBPrescTable[temp];
    /* PCLK clock frequency */
    ptr_clock->pclk_freq = ptr_clock->hclk_freq >> presc;

    /* I2C1CLK clock frequency */
    if((RCU->CFG3 & RCU_CFG3_I2C1SEL) != RCU_CFG3_I2C1SEL)
    {
        /* I2C1 Clock is HRC Osc. */
        ptr_clock->i2c1_clk_freq = HRC_VALUE;
    }
    else
    {
        /* I2C1 Clock is System Clock */
        ptr_clock->i2c1_clk_freq = ptr_clock->system_clk_freq;
    }

    /* USART1CLK clock frequency */
    if((RCU->CFG3 & RCU_CFG3_USART1SEL) == 0x0)
    {
        /* USART1 Clock is PCLK */
        ptr_clock->usart1_clk_freq = ptr_clock->pclk_freq;
    }
    else if((RCU->CFG3 & RCU_CFG3_USART1SEL) == RCU_CFG3_USART1SEL_0)
    {
        /* USART1 Clock is System Clock */
        ptr_clock->usart1_clk_freq = ptr_clock->system_clk_freq;
    }
    else if((RCU->CFG3 & RCU_CFG3_USART1SEL) == RCU_CFG3_USART1SEL_1)
    {
        /* USART1 Clock is LXT Osc. */
        ptr_clock->usart1_clk_freq = LXT_VALUE;
    }
    else if((RCU->CFG3 & RCU_CFG3_USART1SEL) == RCU_CFG3_USART1SEL)
    {
        /* USART1 Clock is HRC Osc. */
        ptr_clock->usart1_clk_freq = HRC_VALUE;
    }
}


/**
  * @}
  */

/**
  * @}
  */

