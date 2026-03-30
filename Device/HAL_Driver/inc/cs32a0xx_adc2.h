/**
  * @file    cs32a0xx_adc2.h
  * @brief   This file contains all the functions prototypes for the ADC2 firmware 
  *          library
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04       
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32A0XX_ADC_H__
#define __CS32A0XX_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32a0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup ADC2
  * @{
  */
  
/**
  * @fn void adc2_init(void)
  * @brief  Initializes the ADCx peripheral according to the specified parameters.
  * @param  None
  * @return None
  */
void adc2_init(void);

/**
  * @fn int32_t adc2_io_read(uint8_t addr, uint8_t* buf)
  * @brief  Read the sigma-delta ADC register value with address addr and store its value in the buf.
  * @param  addr:8-bit sigma-delta ADC register address value
  * @param  buf: 8-bit sigma-delta ADC register address value output value
  * @return 0:OK 
  */
int32_t adc2_io_read(uint8_t addr, uint8_t* buf);

/**
  * @fn int32_t adc2_io_write(uint8_t addr, uint8_t value)
  * @brief  Write the sigma-delta ADC register value with address addr
  * @param  addr:8-bit sigma-delta ADC register address value
  * @param  value: 8-bit sigma-delta ADC register address value output value
  * @return 0:OK 
  */
int32_t adc2_io_write(uint8_t addr, uint8_t value);

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

