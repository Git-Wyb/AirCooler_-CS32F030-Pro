/**
  * @file    cs32f0xx_gpio.h
  * @brief   This file contains all the functions prototypes for the GPIO firmware library.          
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.10         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_GPIO_H__
#define __CS32F0XX_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"
#include "cs32f0xx_rcu.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */
  
/** 
  * @enum gpio_speed_t 
  * @brief GPIO Output Maximum frequency enumeration    
  */
typedef enum
{
    GPIO_SPEED_LOW      = 0x00, //!< I/O output speed: Low 2 MHz 
    GPIO_SPEED_MEDIUM   = 0x01, //!< I/O output speed: Medium 10 MHz 
    GPIO_SPEED_HIGH     = 0x03  //!< I/O output speed: High 50 MHz 
}gpio_speed_t;

#define GPIO_SPEED_CHECK(flag)              (((flag) == GPIO_SPEED_LOW) || ((flag) == GPIO_SPEED_MEDIUM) || \
                                            ((flag) == GPIO_SPEED_HIGH))
    
/**     
  * @brief Check GPIO port definition   
  */    
#define GPIO_PORT_LIST1_CHECK(port)         (((port) == GPIOA) || ((port) == GPIOB))
    
#define GPIO_ALL_PORT_CHECK(port)           (((port) == GPIOA) || ((port) == GPIOB) || ((port) == GPIOC) || \
                                            ((port) == GPIOD) || ((port) == GPIOE) || ((port) == GPIOF))

/** 
  * @brief  GPIO pins definition
  */    
#define GPIO_PIN_0                          ((uint16_t)0x0001)  //!< select Pin 0 
#define GPIO_PIN_1                          ((uint16_t)0x0002)  //!< select Pin 1 
#define GPIO_PIN_2                          ((uint16_t)0x0004)  //!< select Pin 2 
#define GPIO_PIN_3                          ((uint16_t)0x0008)  //!< select Pin 3 
#define GPIO_PIN_4                          ((uint16_t)0x0010)  //!< select Pin 4 
#define GPIO_PIN_5                          ((uint16_t)0x0020)  //!< select Pin 5 
#define GPIO_PIN_6                          ((uint16_t)0x0040)  //!< select Pin 6 
#define GPIO_PIN_7                          ((uint16_t)0x0080)  //!< select Pin 7 
#define GPIO_PIN_8                          ((uint16_t)0x0100)  //!< select Pin 8 
#define GPIO_PIN_9                          ((uint16_t)0x0200)  //!< select Pin 9 
#define GPIO_PIN_10                         ((uint16_t)0x0400)  //!< select Pin 10
#define GPIO_PIN_11                         ((uint16_t)0x0800)  //!< select Pin 11
#define GPIO_PIN_12                         ((uint16_t)0x1000)  //!< select Pin 12
#define GPIO_PIN_13                         ((uint16_t)0x2000)  //!< select Pin 13
#define GPIO_PIN_14                         ((uint16_t)0x4000)  //!< select Pin 14
#define GPIO_PIN_15                         ((uint16_t)0x8000)  //!< select Pin 15
#define GPIO_PIN_ALL                        ((uint16_t)0xFFFF)  //!< All pins selected
    
#define GPIO_PIN_CHECK(pin)                 ((pin & 0xFFFF) != 0) 
#define GPIO_PIN_LIST_CHECK(pin)            (((pin) == GPIO_PIN_0)  || ((pin) == GPIO_PIN_1)  || ((pin) == GPIO_PIN_2) || \
                                            ((pin) == GPIO_PIN_3)  || ((pin) == GPIO_PIN_4)  || ((pin) == GPIO_PIN_5)  || \
                                            ((pin) == GPIO_PIN_6)  || ((pin) == GPIO_PIN_7)  || ((pin) == GPIO_PIN_8)  || \
                                            ((pin) == GPIO_PIN_9)  || ((pin) == GPIO_PIN_10) || ((pin) == GPIO_PIN_11) || \
                                            ((pin) == GPIO_PIN_12) || ((pin) == GPIO_PIN_13) || ((pin) == GPIO_PIN_14) || \
                                            ((pin) == GPIO_PIN_15))

/**
  * @brief  Reads the specified input port pin.
  * @param  SPEED: GPIO Output Maximum frequency. This parameter can be one of @ref gpio_speed_t.
  * @param  MUX: GPIO MF definition. This parameter is GPIO_MF_SELx, where x can be 0,1,2,3,4,5,6,7.
  * @retval None.
  */
#define GPIO_MODE_ANALOG                    0xC0                //!< GPIO Analog In/Out Mode   
#define GPIO_MODE_IN_FLOAT                  0x00                //!< GPIO input 
#define GPIO_MODE_IN_PU                     0x10                //!< GPIO input pull up 
#define GPIO_MODE_IN_PD                     0x20                //!< GPIO input pull down
#define GPIO_MODE_OUT_PP(SPEED)             (0x48 + SPEED)      //!< GPIO output no pull push-pull 
#define GPIO_MODE_OUT_PP_PU(SPEED)          (0x58 + SPEED)      //!< GPIO output pull up push-pull 
#define GPIO_MODE_OUT_PP_PD(SPEED)          (0x68 + SPEED)      //!< GPIO output pull down push-pull 
#define GPIO_MODE_OUT_OD(SPEED)             (0x4C + SPEED)      //!< GPIO output no pull open drain 
#define GPIO_MODE_OUT_OD_PU(SPEED)          (0x5C + SPEED)      //!< GPIO output pull up open drain 
#define GPIO_MODE_OUT_OD_PD(SPEED)          (0x6C + SPEED)      //!< GPIO output pull down open drain 
                                      
#define GPIO_MODE_MF_PP(SPEED)              (0x88 + SPEED)      //!< GPIO multiplex no pull push-pull 
#define GPIO_MODE_MF_PP_PU(SPEED)           (0x98 + SPEED)      //!< GPIO multiplex pull up push-pull 
#define GPIO_MODE_MF_PP_PD(SPEED)           (0xA8 + SPEED)      //!< GPIO multiplex pull down push-pull 
#define GPIO_MODE_MF_OD(SPEED)              (0x8C + SPEED)      //!< GPIO multiplex no pull open drain 
#define GPIO_MODE_MF_OD_PU(SPEED)           (0x9C + SPEED)      //!< GPIO multiplex pull up open drain 
#define GPIO_MODE_MF_OD_PD(SPEED)           (0xAC + SPEED)      //!< GPIO multiplex pull down open drain 

#define GPIO_MODE_CHECK(MODE)               (((MODE) == GPIO_MODE_IN_FLOAT)        || ((MODE) == GPIO_MODE_IN_PU)            || \
                                            ((MODE) == GPIO_MODE_IN_PD)            || ((MODE) == GPIO_MODE_ANALOG)           || \
                                            (((MODE) <= 0x4F) && ((MODE) >= 0x48)) || (((MODE) <= 0x5F) && ((MODE) >= 0x58)) || \
                                            (((MODE) <= 0x6F) && ((MODE) >= 0x68)) || (((MODE) <= 0x8F) && ((MODE) >= 0x88)) || \
                                            (((MODE) <= 0x9F) && ((MODE) >= 0x98)) || (((MODE) <= 0xAF) && ((MODE) >= 0xA8)))

/** 
  * @brief  GPIO MF definition
  */  
#define GPIO_MF_SEL0                        ((uint8_t)0x00)     //!< GPIO MF0(multi-function 0 selection) definition
#define GPIO_MF_SEL1                        ((uint8_t)0x01)     //!< GPIO MF1(multi-function 1 selection) definition
#define GPIO_MF_SEL2                        ((uint8_t)0x02)     //!< GPIO MF2(multi-function 2 selection) definition
#define GPIO_MF_SEL3                        ((uint8_t)0x03)     //!< GPIO MF3(multi-function 3 selection) definition
#define GPIO_MF_SEL4                        ((uint8_t)0x04)     //!< GPIO MF4(multi-function 4 selection) definition
#define GPIO_MF_SEL5                        ((uint8_t)0x05)     //!< GPIO MF5(multi-function 5 selection) definition
#define GPIO_MF_SEL6                        ((uint8_t)0x06)     //!< GPIO MF6(multi-function 6 selection) definition
#define GPIO_MF_SEL7                        ((uint8_t)0x07)     //!< GPIO MF7(multi-function 7 selection) definition

#define GPIO_MF_CHECK(SEL)                  (((SEL) == GPIO_MF_SEL0) || ((SEL) == GPIO_MF_SEL1) || ((SEL) == GPIO_MF_SEL2) || \
                                            ((SEL) == GPIO_MF_SEL3) || ((SEL) == GPIO_MF_SEL4) || ((SEL) == GPIO_MF_SEL5) || \
                                            ((SEL) == GPIO_MF_SEL6) || ((SEL) == GPIO_MF_SEL7))

/**
  * @}
  */

/**
  * @brief  Clears the selected data port bits.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @param  PIN: specifies the port bits to be clear (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @retval None.
  */
#define __GPIO_PIN_RESET(PORT, PIN)         (PORT->CLRR = (uint16_t)PIN)

/**
  * @brief  Sets the selected data port bits.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @param  PIN: specifies the port bits to be sets (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @retval None.
  */
#define __GPIO_PIN_SET(PORT, PIN)           (PORT->SCR = (uint16_t)PIN) 

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @param  DATA: specifies the value to be written to the port output data register.
  * @retval None.
  */
#define __GPIO_DATA_SET(PORT, DATA)         (PORT->DO = DATA) 
    
/**
  * @brief  Reads the specified input port pin.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @retval The input port pin value.
  */
#define __GPIO_INPUT_DATA_GET(PORT)         ((uint16_t)PORT->DI)

/**
  * @brief  Checks the specified input data port bit is set or not.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @param  PIN: specifies the port bits to be check (one of the GPIO_PIN_0 to GPIO_PIN_15).
  * @retval Input data port bit status.
  */
#define __GPIO_INPUT_PIN_GET(PORT, PIN)     ((PORT->DI & (uint16_t)PIN) ? SET : RESET)  

/**
  * @brief  Reads the specified output port data.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @retval The input port output value.
  */
#define __GPIO_OUTPUT_DATA_GET(PORT)        ((uint16_t)PORT->DO)

/**
  * @brief  Checks the specified output data port bit is set or not.
  * @param  PORT: pointer to GPIOx, where x can be A or B.
  * @param  PIN: specifies the port bits to be check (one of the GPIO_PIN_0 to GPIO_PIN_15).
  * @retval Output data port bit status.
  */
#define __GPIO_OUTPUT_PIN_GET(PORT, PIN)    ((PORT->DO & (uint16_t)PIN) ? SET : RESET)

/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset values.
  * @param  PORT: pointer to GPIOx where x can be A, B, C, D, E or F.
  * @return None
  */
#define __GPIO_DEF_INIT(PORT)               do{ \
                                                (RCU->AHBRST |= RCU_AHB_PERI_##PORT); \
                                                (RCU->AHBRST &= ~RCU_AHB_PERI_##PORT); \
                                              } while(0U)

/**
  * @fn void gpio_mode_set(gpio_reg_t * ptr_gpio, uint16_t pin, uint32_t mode)
  * @brief  Sets the specified IO as specified mode.
  * @param  ptr_gpio: pointer to GPIOx, where x can be A or B.
  * @param  pin: specifies the port pin to be set (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @param  mode: Mode selection. This parameter can be one of @ref GPIO_mode_selection.
  * @return None
  */
void gpio_mode_set(gpio_reg_t * ptr_gpio, uint16_t pin, uint32_t mode);                              

/**
  * @fn void gpio_pin_lock_config(gpio_reg_t * ptr_gpio, uint16_t pin)
  * @brief  Locks GPIO Pins configuration registers, The locked registers are GPIOx_PFR,
  *         GPIOx_PODENR, GPIOx_POSR, GPIOx_PUPDR, GPIOx_MFSELL, GPIOx_MFSELH.     
  * @note   The configuration of the locked GPIO pins can no be modified until the device reset.
  * @param  ptr_gpio: pointer to GPIOx where x can be (A or B).
  * @param  pin: specifies the port pin to be written (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @return None
  */
void gpio_pin_lock_config(gpio_reg_t * ptr_gpio, uint16_t pin);

/**
  * @fn void gpio_mf_config(gpio_reg_t* ptr_gpio, uint16_t pin, uint8_t select)
  * @brief  Config the specified GPIO data port multi-function selection .
  * @param  ptr_gpio: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  pin: specifies the port pin to be written (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @param  select: selects the pin to used as multi-function selection.
  *         It can be one of the following value: 
  *         @arg GPIO_MF_SEL0.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL1.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL2.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL3.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL4.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL5.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL6.(See the data sheet for specific multiplexing functions)
  *         @arg GPIO_MF_SEL7.(See the data sheet for specific multiplexing functions)
  * @return None
  */
void gpio_mf_config(gpio_reg_t* ptr_gpio, uint16_t pin, uint8_t select);

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

