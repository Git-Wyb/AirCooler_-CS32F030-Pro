/**
 * @file    cs32a0xx.h
 * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer Header File.
 *          This file contains all the peripheral register's definitions, bits
 *          definitions and memory mapping fr CS32F0xx devices.
 *
 *          The file is the unique include fle that the application programme
 *          is using in the C source code, uually in main.c. This file contai
 *           - Configuration section that alows to select:
 *              - The device used in the taret application
 *              - To use or not the peripherl drivers in application code(i.e
 *                code will be based on diret access to peripheral registers
 *                rather than drivers API), his option is controlled by
 *                "#define USE_STDPERIPH_DRIER"
 *              - To change few application-pecific parameters such as the HX
 *                crystal frequency
 *           - Data structures and the addres mapping for all peripherals
 *           - Peripheral's registers declartions and bits definition
 *           - Macros to access peripheral rgisters hardware
 * @author  ChipSea MCU Group
 * @version V1.0.0
 * @date   2021.11.01
 * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN CORP.
 * @note
 * <h2><center>&copy; COPYRIGHT 2021 ChipSea/center></h2>
 *
 */

#ifndef __CS32A0XX_H__
#define __CS32A0XX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32A0xx
* @{
*/

/** @addtogroup Library_configuration_sectio
* @{
*/

#define ADC2_SYS   0x0
#define ADC2_ADC0  0x1
#define ADC2_ADC1  0x2
#define ADC2_ADC2  0x3
#define ADC2_ADC3  0x4
#define ADC2_ADC4  0x5
#define ADC2_ADC5  0x6
#define ADC2_ADO   0x9
#define ADC2_ADS   0xA


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
