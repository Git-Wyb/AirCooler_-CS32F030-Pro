/**
  * @file    cs32a0xx_adc2.c
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
  * @date   2021.08.10         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#include "cs32a0xx_adc2.h"
#include "cs32f0xx_rcu.h"
#include "cs32f0xx_spi.h"
#include "cs32f0xx_gpio.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup ADC2
  * @{
  */
  
#define SPI_ADC2_CS_LOW()        __GPIO_PIN_RESET(GPIOB, GPIO_PIN_3)
#define SPI_ADC2_CS_HIGH()       __GPIO_PIN_SET(GPIOB, GPIO_PIN_3)

/**
  * @fn void adc2_init(void)
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ptr_adc: pointer to ADCx where x can be 1.
  * @return None
  */
void adc2_init(void)
{
	spi_config_t   spi_config_struct;  

    __SPI_DEF_INIT(SPI2);
    
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOB);
    __RCU_APB1_CLK_ENABLE(RCU_APB1_PERI_SPI2);

    gpio_mode_set(GPIOB, (uint16_t)GPIO_PIN_3, GPIO_MODE_OUT_PP_PU(GPIO_SPEED_LOW));
    

    gpio_mode_set(GPIOB, GPIO_PIN_13|GPIO_PIN_15, GPIO_MODE_MF_PP_PU(GPIO_SPEED_LOW));
    
    gpio_mf_config(GPIOB, GPIO_PIN_13|GPIO_PIN_15, GPIO_MF_SEL0);
    
    spi_config_struct.spi_direct = SPI_DIR_1LINES_TX;
	spi_config_struct.spi_mode = SPI_MODE_MASTER;
	spi_config_struct.data_width = SPI_DATA_WIDTH_8BIT;
	spi_config_struct.spi_cpol = SPI_CPOL_LOW;
	spi_config_struct.spi_cpha = SPI_CPHA_2EDGE;
	spi_config_struct.spi_nss = SPI_SSM_SW;
	spi_config_struct.spi_predivid = SPI_BAUD_RATE_PDIV_32;
	spi_config_struct.first_bit = SPI_FIRST_BIT_MSB;
	spi_config_struct.crc_polynomial = 7;
	spi_init(SPI2, &spi_config_struct);

    __SPI_ENABLE(SPI2);
    SPI_ADC2_CS_HIGH();
}

/**
  * @fn int32_t adc2_io_read(uint8_t addr, uint8_t* buf)
  * @brief  Read the sigma-delta ADC register value with address addr and store its value in the buf.
  * @param  addr:8-bit sigma-delta ADC register address value
  * @param  buf: 8-bit sigma-delta ADC register address value output value
  * @return 0:OK 
  */
int32_t adc2_io_read(uint8_t addr, uint8_t* buf)
{
    SPI_ADC2_CS_LOW();
    
    while (__SPI_FLAG_STATUS_GET(SPI2, TXE) == RESET);
    
    __SPI_8BITS_DATA_SEND(SPI2, addr&0x7F);
    
    while (__SPI_FLAG_STATUS_GET(SPI2, TXE) == RESET);
    
    while (__SPI_FLAG_STATUS_GET(SPI2, BUSY) != RESET);
    
    spi_transmit_direct_set(SPI2, SPI_TRANSMIT_DIR_RX);
    
    if (addr == ADC2_ADO)
    {
        while (__SPI_FLAG_STATUS_GET(SPI2, RXNE) == RESET);
        buf[0] = (uint8_t)__SPI_8BITS_DATA_RECV(SPI2);
        
        while (__SPI_FLAG_STATUS_GET(SPI2, RXNE) == RESET);
        buf[1] = (uint8_t)__SPI_8BITS_DATA_RECV(SPI2);
        
        while (__SPI_FLAG_STATUS_GET(SPI2, RXNE) == RESET);
        buf[2] = (uint8_t)__SPI_16BITS_DATA_RECV(SPI2);
    }
    else 
    {
        while (__SPI_FLAG_STATUS_GET(SPI2, RXNE) == RESET);
        buf[0] = (uint8_t)__SPI_16BITS_DATA_RECV(SPI2);
    }
        
    SPI_ADC2_CS_HIGH();
    
    __SPI_ENABLE(SPI2);
    
    spi_transmit_direct_set(SPI2, SPI_TRANSMIT_DIR_TX);
    __SPI_ENABLE(SPI2);
    
    while (__SPI_FLAG_STATUS_GET(SPI2, BUSY) != RESET);
    
    return 0;
}

/**
  * @fn int32_t adc2_io_write(uint8_t addr, uint8_t value)
  * @brief  Write the sigma-delta ADC register value with address addr
  * @param  addr:8-bit sigma-delta ADC register address value
  * @param  value: 8-bit sigma-delta ADC register address value output value
  * @return 0:OK 
  */
int32_t adc2_io_write(uint8_t addr, uint8_t value)
{
    SPI_ADC2_CS_LOW();
    
    while (__SPI_FLAG_STATUS_GET(SPI2, TXE) == RESET);
    __SPI_8BITS_DATA_SEND(SPI2, addr|0x80);
    
    while (__SPI_FLAG_STATUS_GET(SPI2, TXE) == RESET);
    __SPI_8BITS_DATA_SEND(SPI2, value);
    
    while (__SPI_FLAG_STATUS_GET(SPI2, BUSY) != RESET);
    
//    ndelay(0x2FF);
    SPI_ADC2_CS_HIGH();
    
    return 0;
}

/**
  * @}
  */ 

/**
  * @}
  */ 

