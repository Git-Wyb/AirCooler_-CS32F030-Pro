/**
  * @file    cs32f0xx_gpio.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the GPIO peripheral:
  *           + Initialization and Configuration functions
  *           + GPIO Read and Write functions
  *           + GPIO multi-function configuration functions
  *
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.10                  
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
      1. Enable the GPIO AHB clock using __RCU_AHB_CLK_ENABLE().
      2. Configure the GPIO pin(s) to input mode, using gpio_mode_set(), there is three possible configuration for           
         each pin: 
            a.Input: Floating, Pull-up, Pull-down.
            b.Output: Push-Pull (Pull-up, Pull-down or no Pull). Open Drain (Pull-up, Pull-down or no Pull). In this 
              mode, the speed is configurable: Low, Medium, Fast or High.
            c.Multiplex: Push-Pull (Pull-up, Pull-down or no Pull). Open Drain (Pull-up, Pull-down or no 
              Pull). In this mode, the speed is configurable: Low, Medium, Fast or High.
            d.analog: Analog. Required mode when a pin is to be used as ADC channel,DAC output or comparator input.              
      3. Peripherals multi-function:
         a. For ADC, DAC and comparator, use gpio_mode_set() and set the third parameter to GPIO_MODE_AN.
         b. For other peripherals (TIM, USART...), use gpio_mode_set() and set the third parameter to
              (1).  GPIO_MODE_MF_PP(SPEED)   
              (2).  GPIO_MODE_MF_PP_PU(SPEED)
              (3).  GPIO_MODE_MF_PP_PD(SPEED)
              (4).  GPIO_MODE_MF_OD(SPEED)   
              (5).  GPIO_MODE_MF_OD_PU(SPEED)
              (6).  GPIO_MODE_MF_OD_PD(SPEED)
            The parameter MUX needs to be set to GPIO_MF_SELx, where x can be 0, 1, 2, 3, 4, 5, 6, 7.
      4. To get the level of a pin configured in input mode use __GPIO_INPUT_PIN_GET(PORT, PIN)
      5. To set/reset the level of a pin configured in output mode use
           __GPIO_PIN_RESET(PORT, PIN)/__GPIO_PIN_SET(PORT, PIN)
      6. During and just after reset, the  multi-functions are not active and 
          the GPIO pins are configured in input floating mode (except JTAG pins).
      7. The LXT oscillator pins OSC32_IN and OSC32_OUT can be used as 
          general-purpose (PC14 and PC15, respectively) when the LXT oscillator 
          is off. The LXT has priority over the GPIO function.
      8. The HXT oscillator pins OSC_IN/OSC_OUT can be used as general-purpose 
          PD0 and PD1, respectively, when the HXT oscillator is off. The HXT has 
          priority over the GPIO function.
    @endverbatim
  *
  */
#include "cs32f0xx_gpio.h"
#include "cs32f0xx_rcu.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup GPIO
  * @{
  */ 
  
/** 
  * @brief GPIO parameter mask definition  
  */ 
#define GPIO_MODE_MASK          ((uint8_t)0xC0)     //!< GPIO mode Masks 
#define GPIO_PUPD_MASK          ((uint8_t)0x30)     //!< GPIO pull up/down Masks 
#define GPIO_OUTYPE_MASK        ((uint8_t)0x0C)     //!< GPIO output type Masks 
#define GPIO_SPEED_MASK         ((uint8_t)0x03)     //!< GPIO speed Masks 

/**
  * @fn void gpio_mode_set(gpio_reg_t * ptr_gpio, uint16_t pin, uint32_t mode)
  * @brief  Sets the specified IO as specified mode.
  * @param  ptr_gpio: pointer to GPIOx, where x can be A or B.
  * @param  pin: specifies the port pin to be set (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @param  mode: Mode selection. This parameter can be one of @ref GPIO_mode_selection.
  * @return None
  */
void gpio_mode_set(gpio_reg_t * ptr_gpio, uint16_t pin, uint32_t mode)
{
    uint8_t pos = 0;
    uint32_t clearmask = 0x00;
    uint32_t setmask[3] = {0x00};
    uint32_t mode_temp = (mode & GPIO_MODE_MASK) >> 6;
    uint32_t pupd_temp = (mode & GPIO_PUPD_MASK) >> 4;
    uint32_t outype_temp = (mode & GPIO_OUTYPE_MASK);

    ASSERT(GPIO_PORT_LIST1_CHECK(ptr_gpio));
    ASSERT(GPIO_PIN_CHECK(pin));
    ASSERT(GPIO_MODE_CHECK(mode));
    
    if(outype_temp == GPIO_OUTYPE_MASK)
    {
        ptr_gpio->PODENR |= pin;
    }
    else if(outype_temp == 0x08)
    {
        ptr_gpio->PODENR &= ~pin;
    }

    while(pin)
    {
        if(pin & 0x01)
        {
            clearmask |= (uint32_t)GPIO_SPEED_MASK << (pos *2);
            setmask[0] |= (uint32_t)((mode & GPIO_SPEED_MASK) << (pos * 2));
            setmask[1] |= (uint32_t)(mode_temp << (pos * 2));
            setmask[2] |= (uint32_t)(pupd_temp << (pos * 2));
        }
        pos++;
        pin = pin >> 1;
    }

    MODIFY_REG(ptr_gpio->POSR, clearmask, setmask[0]);
    MODIFY_REG(ptr_gpio->PFR, clearmask, setmask[1]);
    MODIFY_REG(ptr_gpio->PUPDR, clearmask, setmask[2]);    
}

/**
  * @fn void gpio_pin_lock_config(gpio_reg_t * ptr_gpio, uint16_t gpio_pin)
  * @brief  Locks GPIO Pins configuration registers, The locked registers are GPIOx_PFR,
  *         GPIOx_PODENR, GPIOx_POSR, GPIOx_PUPDR, GPIOx_MFSELL, GPIOx_MFSELH.     
  * @note   The configuration of the locked GPIO pins can no be modified until the device reset.
  * @param  ptr_gpio: pointer to GPIOx where x can be (A or B).
  * @param  pin: specifies the port pin to be written (Support any combination of GPIO_PIN_0 to GPIO_PIN_15).
  * @return None
  */
void gpio_pin_lock_config(gpio_reg_t * ptr_gpio, uint16_t pin)
{
    __IO uint32_t temp = 0x00010000;

    ASSERT(GPIO_PORT_LIST1_CHECK(ptr_gpio));
    ASSERT(GPIO_PIN_CHECK(pin));
    
    temp |= pin;
    /* Set LOCK */  
    ptr_gpio->LOCK = temp;  
    /* Reset LOCK */ 
    ptr_gpio->LOCK = pin;
    /* Set LOCK */ 
    ptr_gpio->LOCK = temp; 
    /* Get LOCK */  
    (void)ptr_gpio->LOCK;
    /* Get LOCK */
    (void)ptr_gpio->LOCK;
}

/**
  * @fn void gpio_mf_config(gpio_reg_t* ptr_gpio, uint16_t pin_num, uint8_t select)
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
void gpio_mf_config(gpio_reg_t* ptr_gpio, uint16_t pin, uint8_t select)
{
    uint8_t pos = 0;
    uint32_t reg[2] = {0};

    ASSERT(GPIO_PORT_LIST1_CHECK(ptr_gpio));
    ASSERT(GPIO_PIN_CHECK(pin));
    ASSERT(GPIO_MF_CHECK(select));

	reg[0] = ptr_gpio->MFSEL[0];
	reg[1] = ptr_gpio->MFSEL[1];
	
    while(pin)
    {
        if(pin & 0x01)
        {
            reg[pos >> 3] &= ~(uint32_t)((0x07) << (pos & 0x07) * 4);
            reg[pos >> 3] |= (uint32_t)((select) << (pos & 0x07) * 4);
        }
        pos++;
        pin = pin >> 1;
    }
    ptr_gpio->MFSEL[0] = reg[0];
    ptr_gpio->MFSEL[1] = reg[1];
}

/**
  * @}
  */

/**
  * @}
  */

