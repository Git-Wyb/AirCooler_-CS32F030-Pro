/**
  * @file    cs32f0xx_spi.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Serial peripheral interface (SPI):
  *           a. Initialization and Configuration;
  *           b. Data transfers functions;
  *           c. Hardware CRC Calculation;
  *           d. DMA transfers management;
  *           e. Interrupts and flags management;
  *
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2021.08.10         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
        1. Enable peripheral clock using __RCU_APB2_CLK_ENABLE(RCU_APB2_PERI_SPI1)
            function for SPI1 or using __RCU_APB1_CLK_ENABLE(RCU_APB1_PERI_SPI2)
            function for SPI2.
  
        2. Enable SCK, MOSI, MISO and NSS GPIO clocks using 
            __RCU_AHB_CLK_ENABLE() function. 
  
        3. Peripherals  multi-function: 
            a. Connect the pin to the desired peripherals' multi-function(MF) 
                 using gpio_mf_config() function.
            b. Call gpio_mode_set() function.
  
        4. Program the Polarity, Phase, First Data, Baud Rate Prescaler, Slave 
            Management, Peripheral Mode and CRC Polynomial values using the spi_init()
            function.In I2S mode, program the Mode, Standard, Data Format, MCLK 
            Output, Audio frequency and Polarity using i2s_init() function.
  
        5. Configure the FIFO threshold using spi_fifo_recv_threshold_set() to select 
            at which threshold the RXNE event is generated.
            
        6. Enable the NVIC and the corresponding interrupt using the function 
            __SPI_INTR_ENABLE() if you need to use interrupt mode. 
  
        7. When using the DMA mode 
            a. Configure the DMA using dma_init() function.
            b. Active the needed channel Request using __SPI_ENABLE() function.
   
        8. Enable the SPI using the spi_enable_ctrl() function or enable the I2S using
            __I2S_ENABLE().
   
        9. Enable the DMA using the __DMA_ENABLE() function when using DMA mode. 
  
        10. Optionally, you can enable/configure the following parameters without
            re-initialization (i.e there is no need to call again spi_init() function):
            a. When bidirectional mode (SPI_DIR_1LINES_RX or SPI_DIR_1LINES_TX)
                 is programmed as Data direction parameter using the spi_init() 
                 function it can be possible to switch between SPI_TRANSMIT_DIR_TX 
                 or SPI_TRANSMIT_DIR_RX using the spi_transmit_direct_set() function.
            b. When SPI_SSM_SW is selected as Slave Select Management parameter 
                 using the spi_init() function it can be possible to manage the 
                 NSS internal signal using the spi_software_nss_config() function.
            c. Reconfigure the data size using the spi_data_width_set() function.
            d. Enable or disable the SS output using the __SPI_FUNC_ENABLE(SPIx, NSS_OUT) function.  
  
        11. To use the CRC Hardware calculation feature refer to the Peripheral 
            CRC hardware Calculation subsection.
  
    @endverbatim 
  *
  */
#include "cs32f0xx_spi.h"
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */


/* SPI registers Masks */
#define SPI_CTR1_CLEAR_MASK  ((uint16_t)0x3040)
#define CR1_CLEAR_MASK2      ((uint16_t)0xFFFB)

#define I2SCFGR_CLEAR_Mask   ((uint16_t)0xF040)


/**
  * @fn void spi_config_struct_init(spi_config_t* ptr_config)
  * @brief  Fills each spi_config_t member with its default value.
  * @param  ptr_config: pointer to a spi_config_t structure which will be initialized.
  * @return None
  */
void spi_config_struct_init(spi_config_t* ptr_config)
{
    ptr_config->spi_direct = SPI_DIR_2LINES_FULL_DUPLEX;
    ptr_config->spi_mode = SPI_MODE_SLAVE;
    ptr_config->data_width = SPI_DATA_WIDTH_8BIT;
    
    ptr_config->spi_cpol = SPI_CPOL_LOW;
    ptr_config->spi_cpha = SPI_CPHA_1EDGE;
    ptr_config->spi_nss = SPI_SSM_HW;
  
    ptr_config->spi_predivid = SPI_BAUD_RATE_PDIV_2;
    ptr_config->first_bit = SPI_FIRST_BIT_MSB;
    ptr_config->crc_polynomial = 7;
}

/**
  * @fn void spi_init(spi_reg_t* ptr_spi, spi_config_t* ptr_config)
  * @brief  Initializes the SPIx peripheral according to the ptr_config.
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral .
  * @param  ptr_config: pointer to a spi_config_t structure that
  *         contains the configuration for the specified SPI peripheral.
  * @return None
  */
void spi_init(spi_reg_t* ptr_spi, spi_config_t* ptr_config)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));

    ASSERT(SPI_DIR_LINES_CHECK(ptr_config->spi_direct));
    ASSERT(SPI_MODE_CHECK(ptr_config->spi_mode));
    ASSERT(IS_SPI_DATA_SIZE(ptr_config->data_width));
    ASSERT(SPI_CPOL_CHECK(ptr_config->spi_cpol));
    ASSERT(SPI_CPHA_CHECK(ptr_config->spi_cpha));
    ASSERT(SPI_SSM_CHECK(ptr_config->spi_nss));
    ASSERT(SPI_BAUD_RATE_PDIV_CHECK(ptr_config->spi_predivid));
    ASSERT(SPI_FIRST_BIT_CHECK(ptr_config->first_bit));
    ASSERT(SPI_CRC_POLYNOMIAL_CHECK(ptr_config->crc_polynomial));

    MODIFY_REG(ptr_spi->CTR1, ~SPI_CTR1_CLEAR_MASK, (ptr_config->spi_direct | ptr_config->first_bit |
               ptr_config->spi_cpol | ptr_config->spi_cpha | ptr_config->spi_nss | ptr_config->spi_predivid));

    MODIFY_REG(ptr_spi->CTR2, SPI_CTR2_DLEN, ptr_config->data_width);

    ptr_spi->CRCPOLYR = ptr_config->crc_polynomial;
    
    MODIFY_REG(ptr_spi->CTR1, ~CR1_CLEAR_MASK2, ptr_config->spi_mode);
  
    ptr_spi->I2SCTR &= ~SPI_I2SCTR_I2SMS;
}

/**
  * @fn void i2s_config_struct_init(i2s_config_t* ptr_i2s_config)
  * @brief  Fills each I2S_InitStruct member with its default value.
  * @note   I2S mode is not supported for CS32F030, CS32F036 devices.   
  * @param  ptr_i2s_config: pointer to a i2s_config_t structure which will be initialized.
  * @return None
  */
void i2s_config_struct_init(i2s_config_t* ptr_i2s_config)
{
    ptr_i2s_config->i2s_mode = I2S_MODE_SLAVE_TX;

    ptr_i2s_config->i2s_standard = I2S_STANDARD_HP;

    ptr_i2s_config->i2s_data_len = I2S_DATA_LEN_16BIT;

    ptr_i2s_config->i2s_mck_output = I2S_MCK_OUTPUT_DISABLE;
    
    ptr_i2s_config->audio_freq = I2S_AUDIO_FREQ_DEFAULT;

    ptr_i2s_config->i2s_cpol = I2S_CPOL_LOW;
}

/**
  * @fn void i2s_init(spi_reg_t* ptr_spi, i2s_config_t* ptr_i2s_config)
  * @brief  Initializes the SPIx peripheral according to the specified parameters
  *         in the ptr_i2s_config.
  * @note   I2S mode is not supported for CS32F030, CS32F036 devices.   
  * @param  ptr_spi: pointer to SPIx (x can be 1) peripheral (configured in I2S mode).
  * @param  ptr_i2s_config: pointer to an i2s_config_t structure that contains the configuration
  *         information for the specified SPI peripheral configured in I2S mode.
  * @return None
  */
void i2s_init(spi_reg_t* ptr_spi, i2s_config_t* ptr_i2s_config)
{
    rcu_clock_t rcu_clock;
    uint16_t div = 2;
    uint16_t odd = 0;  
    uint16_t packet = 1;  
    uint32_t clock_freq = 0;
    uint32_t temp = 0;

    ASSERT(SPI_SPI1_CHECK(ptr_spi));
    ASSERT(I2S_MODE_CHECK(ptr_i2s_config->i2s_mode));
    ASSERT(I2S_STANDARD_CHECK(ptr_i2s_config->i2s_standard));
    ASSERT(I2S_DATA_LEN_CHECK(ptr_i2s_config->i2s_data_len));
    ASSERT(I2S_MCK_OUTPUT_CHECK(ptr_i2s_config->i2s_mck_output));
    ASSERT(IS_I2S_AUDIO_FREQ(ptr_i2s_config->audio_freq));
    ASSERT(I2S_CPOL_CHECK(ptr_i2s_config->i2s_cpol));  

    /* Clear I2SMS, I2SEN, I2SOM, PCMLONG, I2SSTD, CKPIS, I2SDL and I2SCL bits */
    ptr_spi->I2SCTR &= I2SCFGR_CLEAR_Mask; 
    ptr_spi->I2SPDIV = 0x0002;

    if(ptr_i2s_config->audio_freq == I2S_AUDIO_FREQ_DEFAULT)
    {
        odd = (uint16_t)0;
        div = (uint16_t)2;   
    }
    else
    {
        if(ptr_i2s_config->i2s_data_len == I2S_DATA_LEN_16BIT)
        {
            /* Packet length is 16 bits */
            packet = 1;
        }
        else
        {
            /* Packet length is 32 bits */
            packet = 2;
        }

        rcu_clk_freq_get(&rcu_clock);      
        clock_freq = rcu_clock.system_clk_freq;    

        if(ptr_i2s_config->i2s_mck_output == I2S_MCK_OUTPUT_ENABLE)
        {
            /* MCK output is enabled */
            temp = (uint16_t)(((((clock_freq / 256) * 10) / ptr_i2s_config->audio_freq)) + 5);
        }
        else
        {
            /* MCLK output is disabled */
            temp = (uint16_t)(((((clock_freq / (32 * packet)) *10 ) / ptr_i2s_config->audio_freq)) + 5);
        }
    
        temp = temp / 10;

        /* Check the parity of the divider */
        odd = (uint16_t)(temp & (uint16_t)0x0001);
        div = (uint16_t)((temp - odd) / 2);

        /* Get the Mask for the Odd bit (SPI_I2SPDIV[8]) register */
        odd = (uint16_t) (odd << 8);
    }
    
    if ((div < 2) || (div > 0xFF))
    {
        /* Set the default values */
        div = 2;
        odd = 0;
    }

    ptr_spi->I2SPDIV = (uint16_t)(div | (uint16_t)(odd | (uint16_t)ptr_i2s_config->i2s_mck_output));

    MODIFY_REG(ptr_spi->I2SCTR, ~I2SCFGR_CLEAR_Mask, (SPI_I2SCTR_I2SMS | ptr_i2s_config->i2s_mode | \
               ptr_i2s_config->i2s_standard | ptr_i2s_config->i2s_data_len | ptr_i2s_config->i2s_cpol));
}

/**
  * @fn void spi_data_width_set(spi_reg_t* ptr_spi, uint16_t value)
  * @brief  Configures the data width for the selected SPI.
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral.
  * @param  value: specifies the SPI data size, it can be one of the following values:
  *          @arg SPI_DATA_WIDTH_4BIT    
  *          @arg SPI_DATA_WIDTH_5BIT
  *          @arg SPI_DATA_WIDTH_6BIT     
  *          @arg SPI_DATA_WIDTH_7BIT
  *          @arg SPI_DATA_WIDTH_8BIT     
  *          @arg SPI_DATA_WIDTH_9BIT
  *          @arg SPI_DATA_WIDTH_10BIT 
  *          @arg SPI_DATA_WIDTH_11BIT
  *          @arg SPI_DATA_WIDTH_12BIT  
  *          @arg SPI_DATA_WIDTH_13BIT
  *          @arg SPI_DATA_WIDTH_14BIT  
  *          @arg SPI_DATA_WIDTH_15BIT
  *          @arg SPI_DATA_WIDTH_16BIT
  * @return None
  */
void spi_data_width_set(spi_reg_t* ptr_spi, uint16_t value)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));
    ASSERT(IS_SPI_DATA_SIZE(value));
  
    MODIFY_REG(ptr_spi->CTR2, SPI_CTR2_DLEN, value);
}

/**
  * @fn void spi_fifo_recv_threshold_set(spi_reg_t* ptr_spi, uint16_t value)
  * @brief  Configures the FIFO reception threshold for the selected SPI.
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral .
  * @param  value: specifies the FIFO reception threshold, it can be one of the following values:
  *          @arg SPI_FIFO_RX_THRESHOLD_HF (event is generated if the FIFO level is greater or equal to 1/2)        
  *          @arg SPI_FIFO_RX_THRESHOLD_QF (event is generated if the FIFO  level is greater or equal to 1/4)                           
  * @return None
  */
void spi_fifo_recv_threshold_set(spi_reg_t* ptr_spi, uint16_t value)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));
    ASSERT(SPI_FIFO_RX_THRESHOLD_CHECK(value));

    MODIFY_REG(ptr_spi->CTR2, SPI_CTR2_RXNE8, value);
}

/**
  * @fn void spi_transmit_direct_set(spi_reg_t* ptr_spi, uint16_t value)
  * @brief  config the data transfer direction.
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral.
  * @param  value: specifies the data transfer direction. It can be one of the
  *         following values:
  *          @arg SPI_TRANSMIT_DIR_TX
  *          @arg SPI_TRANSMIT_DIR_RX
  * @return None
  */
void spi_transmit_direct_set(spi_reg_t* ptr_spi, uint16_t value)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));
    ASSERT(SPI_TRANSMIT_DIR_CHECK(value));

    MODIFY_REG(ptr_spi->CTR1, SPI_TRANSMIT_DIR_TX, value);
}

/**
  * @fn void spi_software_nss_config(spi_reg_t* ptr_spi, uint16_t value)
  * @brief  Configures NSS value in software NSS mode. It can be called
  *         only after the spi_init() function has  been called.     
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral.
  * @param  value: specifies the SPI NSS internal state, it can be:
  *          @arg SPI_SOFTWARE_NSS_SET (Set NSS pin internally) 
  *          @arg SPI_SOFTWARE_NSS_RESET (Reset NSS pin internally)
  * @return None
  */
void spi_software_nss_config(spi_reg_t* ptr_spi, uint16_t value)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));
    ASSERT(SPI_SOFTWARE_NSS_CHECK(value));

    MODIFY_REG(ptr_spi->CTR1, SPI_SOFTWARE_NSS_SET, value);
}

/**
  * @fn void spi_crc_length_set(spi_reg_t* ptr_spi, uint16_t value)
  * @brief  Configures the CRC calculation length. 
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral.
  * @param  value: specifies the SPI CRC calculation length.It can be 
  *          @arg SPI_CRC_LEN_8BIT (Set CRC Calculation to 8 bits)
  *          @arg SPI_CRC_LEN_16BIT (Set CRC Calculation to 16 bits)
  * @return None
  */
void spi_crc_length_set(spi_reg_t* ptr_spi, uint16_t value)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));
    ASSERT(SPI_CRC_LEN_CHECK(value));
  
    MODIFY_REG(ptr_spi->CTR1, SPI_CTR1_CRC16, value);
}

/**
  * @fn void spi_dma_odd_even_set(spi_reg_t* ptr_spi, uint16_t value)
  * @brief  Configures the number of data Even/Odd for the DMA transfers.
  * @param  ptr_spi: pointer to SPIx (x can be 1 or 2) peripheral.
  * @param  value: specifies the SPI last DMA transfers state, it can be:
  *          @arg SPI_DMA_TX_EVEN_RX_EVEN (TX and RX transmission data Number are all Even)                                                   .
  *          @arg SPI_DMA_TX_ODD_RX_EVEN (TX data number is Odd, RX data number is Even)
  *          @arg SPI_DMA_TX_EVEN_RX_ODD (TX data number is Even, RX data number is Odd)
  *          @arg SPI_DMA_TX_ODD_RX_ODD (TX data number is Odd, RX data number is Odd)
  * @return None
  */
void spi_dma_odd_even_set(spi_reg_t* ptr_spi, uint16_t value)
{
    ASSERT(SPI_LIST_CHECK(ptr_spi));
    ASSERT(SPI_DMA_TX_RX_NUMBER_CHECK(value));

    MODIFY_REG(ptr_spi->CTR2, SPI_DMA_TX_ODD_RX_ODD, value);
}


/**
  * @}
  */ 

/**
  * @}
  */

