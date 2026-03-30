/**
  * @file    cs32f0xx_crc.h
  * @brief   This file contains all the functions prototypes for the CRC firmware library.   
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_CRC_H
#define __CS32F0XX_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/** @defgroup CRC_Exported_Constants
  * @{
  */

/**  
  * @brief CRC Reverse Input Data definition
  */
#define CRC_REVERSE_INPUT_DATA_NO			((uint32_t)0x00000000)	//!< No reverse operation of Input Data 
#define CRC_REVERSE_INPUT_DATA_8BITS      	CRC_CTR_DINREVMOD_0		//!< Reverse operation of Input Data on 8 bits 
#define CRC_REVERSE_INPUT_DATA_16BITS      	CRC_CTR_DINREVMOD_1   	//!< Reverse operation of Input Data on 16 bits
#define CRC_REVERSE_INPUT_DATA_32BITS     	CRC_CTR_DINREVMOD    	//!< Reverse operation of Input Data on 32 bits

#define CRC_REVERSE_INPUT_DATA_CHECK(value)	(((value) == CRC_REVERSE_INPUT_DATA_NO)		|| \
                                           	((value) == CRC_REVERSE_INPUT_DATA_8BITS)  	|| \
                                        	((value) == CRC_REVERSE_INPUT_DATA_16BITS)	|| \
                                          	((value) == CRC_REVERSE_INPUT_DATA_32BITS))

/**
  * @}
  */


/**
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @param  None
  * @return None
  */
#define __CRC_DEF_INIT()					crc_def_init()

/**
  * @brief  Resets the CRC calculation unit and sets INITCFG register content to DATA register.
  * @param  None
  * @return None
  */
#define __CRC_RESET()						(CRC->CTR |= CRC_CTR_RST)

/**
  * @brief  Set the initial value of crc calculation to INITCFG register.
  * @note   The initial value will be loaded to DATA register, after resetting CRC calculation unit.
  * @param  VALUE: Programmable initial CRC value.
  * @return None
  */
#define __CRC_INIT_VALUE_SET(VALUE)			(CRC->INITCFG = VALUE)

/**
  * @brief  Returns the CRC polynomial.
  * @param  None
  * @return 32-bit polynomial
  */
#define __CRC_POLYNOMIAL_GET()				(CRC->POL)

/**
  * @brief  Enables the reverse operation on output data.
  *         The reverse operation on output data is performed on 32-bit.
  * @param  None
  * @return None
  */
#define __CRC_OUTPUT_DATA_REVERSE_ENABLE()	(CRC->CTR |= CRC_CTR_DOREVEN)

/**
  * @brief  Disables the reverse operation on output data.
  *         The reverse operation on output data is performed on 32-bit.
  * @param  None
  * @return None
  */
#define __CRC_OUTPUT_DATA_REVERSE_DISABLE()	(CRC->CTR &= ~(CRC_CTR_DOREVEN))

/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @return 32-bit CRC
  */
#define __CRC_VALUE_GET()					(CRC->DATA)

/**
  * @brief Set an 8-bit data in Free Data register (FREDATA).
  * @param  VALUE: set 8-bit value in the FREDATA register. 
  * @return None
  */
#define __CRC_FREDATA_REG_SET(VALUE)		(CRC->FREDATA = (uint8_t)VALUE)

/**
  * @brief  Get the 8-bit data stored in Free Data register (FREDATA).
  * @param  None
  * @return 8-bit value of the FREDATA register. 
  */
#define __CRC_FREDATA_REG_GET()				((uint8_t)CRC->FREDATA)

/**
  * @fn void crc_def_init(void) 
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @param  None
  * @return None
  */
void crc_def_init(void);

/**
  * @fn void crc_input_data_reverse(uint32_t value)
  * @brief  Selects the reverse operation to be performed on input data.
  * @param  value: Specifies the reverse operation on input data.
  *         It can be one of the following values: 
  *          @arg CRC_REVERSE_INPUT_DATA_NO(No reverse operation is performed)
  *          @arg CRC_REVERSE_INPUT_DATA_8BITS(reverse operation performed on 8 bits)
  *          @arg CRC_REVERSE_INPUT_DATA_16BITS(reverse operation performed on 16 bits)
  *          @arg CRC_REVERSE_INPUT_DATA_32BITS(reverse operation performed on 32 bits)
  * @return None
  */
void crc_input_data_reverse(uint32_t value);

/**
  * @fn uint32_t crc_crc32_calc(uint32_t value)
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  value: data word(32-bit) to compute its CRC
  * @return 32-bit CRC
  */
uint32_t crc_crc32_calc(uint32_t value);

/**
  * @fn uint32_t crc_crc16_calc(uint16_t value)
  * @brief  Computes the 16-bit CRC of a given 16-bit data . 
  * @param  value: data half-word(16-bit) to compute its CRC
  * @return 16-bit CRC
  */
uint32_t crc_crc16_calc(uint16_t value);

/**
  * @fn uint32_t crc_crc8_calc(uint8_t value)
  * @brief  Computes the 8-bit CRC of a given 8-bit data. 
  * @param  value: 8-bit data to compute its CRC
  * @return 8-bit CRC
  */
uint32_t crc_crc8_calc(uint8_t value);

/**
  * @fn uint32_t crc_data_buffer_calc(uint32_t buf[], uint32_t length)
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  buf: pointer to the buffer containing the data to be computed
  * @param  length: length of the buffer to be computed
  * @return 32-bit CRC
  */
uint32_t crc_data_buffer_calc(uint32_t buf[], uint32_t length);


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

