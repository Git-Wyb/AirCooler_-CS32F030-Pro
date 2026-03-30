/**
  * @file    cs32f0xx_usart.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Universal synchronous asynchronous receiver
  *          transmitter (USART), This module Initialization and Configuration 
  *          includes: STOP Mode; AutoBaudRate; Data transfers;LIN mode;
  *            Multi-Processor Communication;Half-duplex mode;Smartcard mode;
  *            IrDA mode;RS485 mode;DMA transfers management;
  *            Interrupts and flags management.
  *           
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
    1. Enable peripheral clock using rcu_apb2_periph_clock_enable_ctrl(RCC_APB2Periph_USART1, ENABLE)
        function for USART1 or using rcu_apb1_periph_clock_enable_ctrl(RCC_APB1Periph_USARTx, ENABLE)
        function for USART2 and USART3.
    2.According to the USART mode, enable the GPIO clocks using 
        rcu_ahb_periph_clock_enable_ctrl() function. (The I/O can be TX, RX, CTS, 
        or and SCLK). 
    3. Peripheral's  multi-function: 
        a. Connect the pin to the desired peripherals' MFSEL (multi-function selection)
              using gpio_mf_config() function.
        b. Configure the desired pin in  multi-function by:
             gpio_configStruct->gpio_mode = GPIO_MODE_MF.
        c. Select the type, pull-up/pull-down and output speed via 
             gpio_pull, gpio_out_type and gpio_speed members.
        d. Call gpio_init() function.        
    4. Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware 
        flow control and Mode(Receiver/Transmitter) using the spi_init()
        function.  
   5. For synchronous mode, enable the clock and program the polarity,
        phase and last bit using the usart_clock_config() function.  
   6.Enable the NVIC and the corresponding interrupt using the function 
        usart_interrupt_config() if you need to use interrupt mode.   
    7.When using the DMA mode: 
        a. Configure the DMA using dma_init() function.
        b. Active the needed channel Request using usart_dma_enable_ctrl() function.   
    8. Enable the USART using the usart_enable_ctrl() function.   
    9.Enable the DMA using the dma_enable_ctrl() function, when using DMA mode.        
    @endverbatim
  *
  */

#include "cs32f0xx_usart.h"
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup USART 
  * @brief USART driver modules
  * @{
  */


#define USART_CTR1_CLEAR_MASK     		((uint32_t)(USART_CTR1_DL | USART_CTR1_PEN | \
                                   		USART_CTR1_ODDS | USART_CTR1_TEN | USART_CTR1_REN))
                                   		
/*!< USART CR2 register clock bits clear Mask ((~(uint32_t)0xFFFFF0FF)) */
#define USART_CTR2_CLOCK_CLEAR_MASK     ((uint32_t)(USART_CTR2_CKEN | USART_CTR2_CPOL | \
                                              USART_CTR2_CPHA | USART_CTR2_CKLEN))

#define USART_CTR3_CLEAR_MASK			((uint32_t)(USART_CTR3_RTSEN | USART_CTR3_CTSEN))

//!< USART Interrupts mask */
#define USART_INT_MASK					((uint32_t)0x000000FF)


 

/**
  * @fn void usart_init(usart_reg_t* ptr_usart, usart_config_t* ptr_config)
  * @brief  Initializes the ptr_usart peripheral according to the specified parameters
  *         in the ptr_config .
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  ptr_config: pointer to a usart_config_t structure containing
  *         the configuration for the specified USART peripheral.
  * @return None
  */
void usart_init(usart_reg_t* ptr_usart, usart_config_t* ptr_config)
{
    uint32_t divider = 0;
    uint32_t freq = 0;
    uint32_t reg = 0;
    rcu_clock_t rcu_clock;
  
    ASSERT(USART_SELECT_CHECK(ptr_usart));
    ASSERT(USART_BAUD_RATE_CHECK(ptr_config->baud_rate));  
    ASSERT(USART_DATA_WIDTH_CHECK(ptr_config->data_width));
    ASSERT(USART_STOP_BIT_CHECK(ptr_config->stop_bits));
    ASSERT(USART_PARITY_CHECK(ptr_config->parity));
    ASSERT(USART_MODE_CHECK(ptr_config->usart_mode));
    ASSERT(USART_FLOW_CONTROL_CHECK(ptr_config->flow_control));
  
    /* Disable USART */
    ptr_usart->CTR1 &= (uint32_t)~((uint32_t)USART_CTR1_UEN);  

	  /* Set STOPLEN[13:12] */   
	  MODIFY_REG(ptr_usart->CTR2, USART_CTR2_STOPLEN, ptr_config->stop_bits);
    
    /* Configure the USART data width, Parity and mode  */
	  MODIFY_REG(ptr_usart->CTR1, USART_CTR1_CLEAR_MASK, (uint32_t)(ptr_config->data_width | 
		ptr_config->parity | ptr_config->usart_mode));
  
	  MODIFY_REG(ptr_usart->CTR3, USART_CTR3_CLEAR_MASK, ptr_config->flow_control);
  
    /* Configure the USART Baud Rate*/
    rcu_clk_freq_get(&rcu_clock);  
    if (ptr_usart == USART1)
    {
        freq = rcu_clock.usart1_clk_freq;
    }
    else
    {
        freq = rcu_clock.pclk_freq;
    }
  
    if ((ptr_usart->CTR1 & USART_CTR1_OVRS) != 0)
    {
        /* (divider * 10) computing in case Oversampling mode is 8 Samples */
        divider = (uint32_t)((2 * freq) / (ptr_config->baud_rate));
        reg  = (uint32_t)((2 * freq) % (ptr_config->baud_rate));
    }
    else 
    {
        /* (divider * 10) computing in case Oversampling mode is 16 Samples */
        divider = (uint32_t)((freq) / (ptr_config->baud_rate));
        reg  = (uint32_t)((freq) % (ptr_config->baud_rate));
    }
  
    /* Round the divider : if fractional part i greater than 0.5 increment divider */
    if (reg >=  (ptr_config->baud_rate) / 2)
    {
        divider++;
    } 
  
    /* Implement the divider in case Oversampling mode is 8 Samples */
    if ((ptr_usart->CTR1 & USART_CTR1_OVRS) != 0)
    {
        /* Get the LSB of divider and shift it to the right by 1 bit, update the divider value */
        reg = (divider & (uint16_t)0x000F) >> 1;
        divider = (divider & (uint16_t)0xFFF0) | reg;
    }
  
    /* Write divider to baud rate register */
    ptr_usart->BRT = (uint16_t)divider;
}

/**
  * @fn void usart_config_struct_init(usart_config_t* ptr_config)
  * @brief  Fills each ptr_config member with its default value.
  * @param  ptr_config: pointer to a usart_config_t structure to be initialized.
  * @return None
  */
void usart_config_struct_init(usart_config_t* ptr_config)
{
    /* ptr_config members initialized with default value*/
    ptr_config->baud_rate = 9600;
    ptr_config->data_width = USART_DATA_WIDTH_8;
    ptr_config->stop_bits = USART_STOP_BIT_1;
    ptr_config->parity = USART_PARITY_NO;
    ptr_config->usart_mode = USART_MODE_RX | USART_MODE_TX;
    ptr_config->flow_control = USART_FLOW_CONTROL_NONE;  
}

/**
  * @brief  Initializes the USARTx peripheral Clock according to the 
  *         specified parameters in the ptr_clock.
  * @param  ptr_usart: where x can be from 1 to 8 to select the USART peripheral.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  ptr_clock: pointer to a usart_clock_t structure that contains
  *         the configuration information for the specified USART peripheral.  
  * @return None
  */
void usart_clock_init(usart_reg_t* ptr_usart, usart_clock_t* ptr_clock)
{
  	/* Check the parameters */
  	ASSERT(USART_SELECT_CHECK(ptr_usart));
  	ASSERT(USART_CLOCK_CHECK(ptr_clock->clock_flag));
  	ASSERT(USART_CPOL_CHECK(ptr_clock->usart_cpol));
  	ASSERT(USART_CPHA_CHECK(ptr_clock->usart_cpha));
  	ASSERT(USART_LAST_BIT_CHECK(ptr_clock->usart_lastbit));
	
  	/* Configure the USART Clock, CPOL, CPHA, CKLEN ------------*/
  	/* Clear CLKEN, CPOL, CPHA, LBCL and SSM bits */
  	/* Set CKEN bit according to clock_flag value */
  	/* Set CPOL bit according to usart_cpol value */
  	/* Set CPHA bit according to usart_cpha value */
  	/* Set CKLEN bit according to clock_length value */
	  MODIFY_REG(ptr_usart->CTR2, USART_CTR2_CLOCK_CLEAR_MASK, (uint32_t)(ptr_clock->clock_flag | 
		ptr_clock->usart_cpol | ptr_clock->usart_cpha | ptr_clock->usart_lastbit));
}

/**
  * @brief  Fills each ptr_clock member with its default value.
  * @param  ptr_clock: pointer to a usart_clock_t
  *         structure which will be initialized.
  * @return None
  */
void usart_clock_struct_init(usart_clock_t* ptr_clock)
{
	/* ptr_clock members default value */
  	ptr_clock->clock_flag = USART_CLOCK_DISABLE;
  	ptr_clock->usart_cpol = USART_CPOL_LOW;
  	ptr_clock->usart_cpha = USART_CPHA_EDGE_1;
  	ptr_clock->usart_lastbit = USART_LAST_BIT_DISABLE;
}

/**
  * @fn void usart_prescaler_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the system clock prescaler.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  value: specifies the prescaler clock.
  * @note   This function has to be called before calling usart_enable_ctrl() function.    
  * @return None
  */
void usart_prescaler_set(usart_reg_t* ptr_usart, uint8_t value)
{ 
    ASSERT(USART_SELECT_CHECK(ptr_usart));
  
    /* Set the USART prescaler */
	  MODIFY_REG(ptr_usart->GTPDIV, USART_GTPDIV_PDIV, value);		
}

/**
  * @fn void usart_stop_mode_wakeup_config(usart_reg_t* ptr_usart, uint32_t wakeup_source)
  * @brief  Selects the USART WakeUp method for stop mode.
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  wakeup_source: specifies the selected USART wakeup method.
  *         This parameter can be one of the following values:
  *           @arg USART_WAKEUP_SOURCE_ADDR_MATCH: wakeup on address match.
  *           @arg USART_WAKEUP_SOURCE_START_BIT: wakeup on Start bit detection.
  *           @arg USART_WAKEUP_SOURCE_RXNE: wakeup on RXNE.  
  * @note   This function has to be called before calling usart_enable_ctrl() function.   
  * @return None
  */
void usart_stop_mode_wakeup_config(usart_reg_t* ptr_usart, uint32_t wakeup_source)
{
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));
    ASSERT(USART_WAKEUP_SOURCE_CHECK(wakeup_source));

	  /* Set the USART WakeUp method for stop mode */
	  MODIFY_REG(ptr_usart->CTR3, USART_CTR3_WKUPMTHD, wakeup_source);	
}

/**
  * @fn void usart_auto_baud_rate_config(usart_reg_t* ptr_usart, uint32_t rate_value)
  * @brief  Selects the USART auto baud rate method.
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  rate_value: specifies the selected USART auto baud rate method.
  *          This parameter can be one of the following values:
  *            @arg USART_AUTO_RATE_MEASURE_START_BIT(Start Bit duration measurement)
  *            @arg USART_AUTO_RATE_MEASURE_FALLING_EDGE(Falling edge to falling edge measurement)
  * @note   This function has to be called before calling usart_enable_ctrl() function.  
  * @return None
  */
void usart_auto_baud_rate_config(usart_reg_t* ptr_usart, uint32_t rate_value)
{
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));
    ASSERT(USART_AUTO_RATE_MEASURE_CHECK(rate_value));

	  /* Set the USART auto baud rate method */
	  MODIFY_REG(ptr_usart->CTR2, USART_CTR2_ABRSEL, rate_value);
}

/**
  * @fn void usart_address_set(usart_reg_t* ptr_usart, uint8_t addr)
  * @brief  Sets the address of the USART node.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  addr: Indicates the address of the USART node.
  * @return None
  */
void usart_address_set(usart_reg_t* ptr_usart, uint8_t addr)
{
    ASSERT(USART_SELECT_CHECK(ptr_usart));
  
    /* Set the USART address */
	  MODIFY_REG(ptr_usart->CTR2, USART_CTR2_UADR, (uint32_t)addr << 24);
}

/**
  * @fn void usart_recv_wakeup_config(usart_reg_t* ptr_usart, uint32_t flag)
  * @brief  Selects the USART WakeUp method from mute mode.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  flag: specifies the USART wakeup method.
  *          This parameter can be one of the following values:
  *            @arg USART_RX_WAKEUP_IDLE_LINE(WakeUp by an idle line detection)
  *            @arg USART_RX_WAKEUP_ADDR_MARK(WakeUp by an address mark)
  * @return None
  */
void usart_recv_wakeup_config(usart_reg_t* ptr_usart, uint32_t flag)
{
    ASSERT(USART_SELECT_CHECK(ptr_usart));
    ASSERT(USART_RX_WAKEUP_CHECK(flag));

    /* Set the  USART WakeUp method from mute mode */
	  MODIFY_REG(ptr_usart->CTR1, USART_CTR1_RXWKUPS, flag);
}

/**
  * @fn void usart_addr_detect_set(usart_reg_t* ptr_usart, uint32_t addr)
  * @brief  Configure the the USART Address detection length.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  addr: specifies the USART address length detection.
  *          This parameter can be one of the following values:
  *            @arg USART_ADDRESS_4BIT(4-bit address length detection) 
  *            @arg USART_ADDRESS_7BIT(7-bit address length detection) 
  * @return None
  */
void usart_addr_detect_set(usart_reg_t* ptr_usart, uint32_t addr)
{
    ASSERT(USART_SELECT_CHECK(ptr_usart));
    ASSERT(USART_ADDRESS_BIT_CHECK(addr));

    /* Set the USART Address detection length */
	  MODIFY_REG(ptr_usart->CTR2, USART_CTR2_ADRM7, addr);
}

/**
  * @fn void usart_lin_break_detect_set(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Sets the USART LIN Break detection length.
  * @note   This function is not available for CS32F036 devices.   
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  value: specifies the LIN break detection length.
  *          This parameter can be one of the following values:
  *            @arg USART_LIN_BREAK_10BIT(10-bit break detection)
  *            @arg USART_LIN_BREAK_11BIT(11-bit break detection)
  * @return None
  */
void usart_lin_break_detect_set(usart_reg_t* ptr_usart, uint32_t value)
{
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));
    ASSERT(USART_LIN_BREAK_BIT_CHECK(value));

    /* Set the LIN Break detection length */
	  MODIFY_REG(ptr_usart->CTR2, USART_CTR2_LINBRK11, value);
}

/**
  * @fn void usart_guard_time_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the specified USART guard time for smart card mode.
  * @note   This function is not available for CS32F036 devices.    
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.  
  * @param  value: specifies the guard time.
  * @note   The value must be greater than 0x0.    
  * @return None
  */
void usart_guard_time_set(usart_reg_t* ptr_usart, uint8_t value)
{    
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));

    /* Set the USART guard time */
	  MODIFY_REG(ptr_usart->GTPDIV, USART_GTPDIV_GUDT, (uint16_t)((uint16_t)value << 8));
}

/**
  * @fn void usart_auto_retry_times_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the Smart Card number of retries in transmit and receive.
  * @note   This function is not available for CS32F036 devices.  
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral. 
  * @param  value: specifies the Smart Card auto retry times.
  * @return None
  */
void usart_auto_retry_times_set(usart_reg_t* ptr_usart, uint8_t value)
{    
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));
    ASSERT(USART_RETRY_NUM_CHECK(value));
  
    /* Set the USART auto retry count*/
	  MODIFY_REG(ptr_usart->CTR3, USART_CTR3_SCANUM, (uint32_t)value << 17);
}

/**
  * @fn void usart_block_value_set(usart_reg_t* ptr_usart, uint8_t block_number)
  * @brief  Sets the Smar Card Block number.
  * @note   This function is not available for CS32F036 devices.  
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  block_number: specifies the Smart Card block number.
  * @return None
  */
void usart_block_value_set(usart_reg_t* ptr_usart, uint8_t block_number)
{    
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));

    /* Set the Smartcard block number */
	  MODIFY_REG(ptr_usart->ROT, USART_ROT_NUMBLK, (uint32_t)block_number << 24);
}

/**
  * @fn void usart_recv_overtime_set(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Sets the receiver Time Out value.
  * @note   This function is not available for CS32F036 devices.    
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  value: specifies the Receiver Time Out value.
  * @return None
  */
void usart_recv_overtime_set(usart_reg_t* ptr_usart, uint32_t value)
{    
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));
    ASSERT(USART_TIMEOUT_CHECK(value));
  
    /* Set the receiver time_out value */
	  MODIFY_REG(ptr_usart->ROT, USART_ROT_RXOVR, value);
}

/**
  * @fn void usart_irda_config(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Configures the USART's IrDA interface.
  * @note   This function is not available for CS32F036 devices.  
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral. 
  * @param  value: specifies the IrDA mode,it can be one of the following values:
  *          @arg USART_IRDA_MODE_LP(IRDA in low power mode) 
  *          @arg USART_IRDA_MODE_NORMAL(IRDA in normal mode) 
  * @return None
  */
void usart_irda_config(usart_reg_t* ptr_usart, uint32_t value)
{
    ASSERT(USART_SELECT_1_CHECK(ptr_usart));
    ASSERT(USART_IRDA_MODE_CHECK(value));

    /* Set the new value for the IrDA interface */
	  MODIFY_REG(ptr_usart->CTR3, USART_CTR3_IRMS, value);
}

/**
  * @fn void usart_driver_enable_polarity_config(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Configures the USART's DE polarity
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  value: specifies the DE polarity, it can be one of the following values:
  *          @arg USART_DE_POLARITY_LOW 
  *          @arg USART_DE_POLARITY_HIGH
  * @return None
  */
void usart_driver_enable_polarity_config(usart_reg_t* ptr_usart, uint32_t value)
{
    ASSERT(USART_SELECT_CHECK(ptr_usart));
    ASSERT(USART_DE_POLARITY_CHECK(value));

    /* Set the new value for the DE polarity */
	  MODIFY_REG(ptr_usart->CTR3, USART_CTR3_DEPS, value);
}

/**
  * @fn void usart_driver_enable_preactive_time_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the specified RS485 DE Pre-active time 
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  value: specifies DE Pre-active time between the activation of the DE
  *         signal and the the beginning of the start bit
  * @return None
  */
void usart_driver_enable_preactive_time_set(usart_reg_t* ptr_usart, uint8_t value)
{
    ASSERT(USART_SELECT_CHECK(ptr_usart));
    ASSERT(USART_DE_PREACTIVE_TIME_CHECK(value)); 

    /* Set the new value for the DE Pre-active time */
	  MODIFY_REG(ptr_usart->CTR1, USART_CTR1_PRETDE, (uint32_t)value << 21);
}

/**
  * @fn void usart_driver_enable_posactive_time_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the specified RS485 DE Pos-active time
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  value: specifies the time between the middle of the last stop bit 
  *         in a transmitted message and the Pos_activation of the DE signal .
  * @return None
  */
void usart_driver_enable_posactive_time_set(usart_reg_t* ptr_usart, uint8_t value)
{
    ASSERT(USART_SELECT_CHECK(ptr_usart));
    ASSERT(USART_DE_PROACTIVE_TIME_CHECK(value)); 
    
    /* Set the new value for the DE Pos-active time */
	  MODIFY_REG(ptr_usart->CTR1, USART_CTR1_POSTDE, (uint32_t)value << 16);
}


/**
  * @}
  */

/**
  * @}
  */

