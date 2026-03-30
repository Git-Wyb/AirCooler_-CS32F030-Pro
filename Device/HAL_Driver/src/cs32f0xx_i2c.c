/**
  * @file    cs32f0xx_i2c.c  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Inter-Integrated circuit (I2C):
  *           + Initialization and Configuration
  *           + Communications handling
  *           + SMBUS management
  *           + I2C registers management
  *           + Data transfers management
  *           + DMA transfers management
  *           + Interrupts and flags management
  * @note     SMBUS is not supported for CS32F036 and CS32F03X-RA devices.
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2020 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
   1. Enable peripheral clock using  for I2C1 or I2C2.       
   2. Enable SDA, SCL and SMBA (when used) GPIO clocks.        
   3. Peripherals  multi-function: 
       a. Connect the pin to the desired peripherals' multi-function (MF) .            
       b. Configure the desired pin in  multi-function. 
       c.Select the type, OpenDrain and speed.
       d. Call gpio_init() function.
   4. Config the Mode, Timing , slave address, Ack and Ack Address using the i2c_init().       
   5. Optionally you can enable/configure the following parameters without
       a. Enable the acknowledge feature using i2c_ack_config() function.
       b. Enable the dual addressing mode using i2c_slave_address2_enable_ctrl() function.
       c. Enable the general call using the i2c_call_enable_ctrl() function.
       d. Enable the clock stretching using i2c_stretch_clock_enable_ctrl() function.
       e. Enable the PEC Calculation using i2c_pec_enable_ctrl() function.
       f.  Enable the SMBusAlert pin using i2c_smbus_alert_enable_ctrl() function.
   6. Enable the NVIC and the corresponding interrupt using the function
       i2c_interrupt_config() if you need to use interrupt mode.
   7. When using the DMA mode 
      a. Configure the DMA using dma_init() function.
      b. Active the needed channel Request using i2c_dma_enable_ctrl() function.
   8. Enable the I2C using the i2c_enable_ctrl() function.
   9. Enable the DMA using the dma_enable_ctrl() function when using DMA mode in the  transfers.       
    @endverbatim
  *
  */

#include "cs32f0xx_i2c.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup I2C 
  * @{
  */


/** 
  * @brief I2C CTR2 clear register mask definition
  */
#define I2C_CTR2_CLEAR_MASK     ((uint32_t)0x07FF7FFF)

/** 
  * @brief I2C TMR clear register mask definition
  */
#define I2C_TMR_CLEAR_MASK      ((uint32_t)0xF0FFFFFF) 


/**
  * @fn  void i2c_struct_init(i2c_config_t* ptr_struct)
  * @brief  Config each ptr_struct member with its default value.
  * @param  ptr_struct: pointer to an i2c_config_t structure which will be initialized.
  * @return None.
  */
void i2c_struct_init(i2c_config_t* ptr_struct)
{
    ptr_struct->tmr_value = 0;
    ptr_struct->analog_flag = I2C_ANALOG_FILTER_ENABLE;
    ptr_struct->digital_value = 0;
    ptr_struct->mode = I2C_BUS_MODE_I2C;
    ptr_struct->slave_addr1 = 0;
    ptr_struct->ack_flag = I2C_ACK_DISABLE;
    ptr_struct->ack_addr = I2C_ACK_ADDR_7BITS;
}


/**
  * @fn void i2c_init(i2c_reg_t* ptr_i2c, i2c_config_t* ptr_struct)
  * @brief  Initializes the ptr_i2c peripheral according to  the ptr_struct.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  ptr_struct: pointer to a i2c_config_t structure containing configuration value.          
  * @return None.
  */
void i2c_init(i2c_reg_t* ptr_i2c, i2c_config_t* ptr_struct)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_ANALOG_FILTER_CHECK(ptr_struct->analog_flag));
    ASSERT(I2C_DIGITAL_FILTER_CHECK(ptr_struct->digital_value));
    ASSERT(I2C_BUS_MODE_CHECK(ptr_struct->mode));
    ASSERT(I2C_SLAVE_ADDR1_CHECK(ptr_struct->slave_addr1));
    ASSERT(I2C_ACK_CONFIG_CHECK(ptr_struct->ack_flag));
    ASSERT(I2C_ACK_ADDR_CHECK(ptr_struct->ack_addr));

    /* Disable I2C function */
    ptr_i2c->CTR1 &= (uint32_t)~((uint32_t)I2C_CTR1_I2CEN);
    
    MODIFY_REG(ptr_i2c->CTR1, (I2C_CTR1_DFCFG | I2C_CTR1_AFDIS), ptr_struct->analog_flag | (ptr_struct->digital_value << 8));
    
    /* Set Timing */
    ptr_i2c->TMR = ptr_struct->tmr_value & I2C_TMR_CLEAR_MASK;
    
    /* Enable I2C  */
    ptr_i2c->CTR1 |= I2C_CTR1_I2CEN;
    
    MODIFY_REG(ptr_i2c->SADR1, (I2C_SADR1_SADR1EN | I2C_SADR1_SADR1 | I2C_SADR1_SADR1MODE), ptr_struct->ack_addr | ptr_struct->slave_addr1);
    
    /* Enable slave Address1 acknowledgement */
    ptr_i2c->SADR1 |= I2C_SADR1_SADR1EN;
    
    /* Configure I2C: mode */
    ptr_i2c->CTR1 |= ptr_struct->mode;
    
    MODIFY_REG(ptr_i2c->CTR2, I2C_CTR2_NACKGEN, ptr_struct->ack_flag);
}

/**
  * @fn void i2c_software_reset(i2c_reg_t* ptr_i2c)
  * @brief  Active the specified I2C software reset.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None.
  */
void i2c_software_reset(i2c_reg_t* ptr_i2c)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    
    /* Disable bus */
    ptr_i2c->CTR1 &= (uint32_t)~((uint32_t)I2C_CTR1_I2CEN);

    /* Wait for 3 APB clock cycles to perform the software reset */     
    *(__IO uint32_t *)(uint32_t)ptr_i2c; 

    /* Enable bus */
    ptr_i2c->CTR1 |= I2C_CTR1_I2CEN;
}

/**
  * @fn void i2c_slave_address2_config(i2c_reg_t* ptr_i2c, uint16_t addr, uint8_t mask)
  * @brief  Configures the I2C slave address 2 and mask.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  addr: specifies the slave address.
  * @param  mask: specifies own address 2 mask to be programmed.
  * @return None.
  */
void i2c_slave_address2_config(i2c_reg_t* ptr_i2c, uint16_t addr, uint8_t mask)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_SLAVE_ADDR2_CHECK(addr));
    ASSERT(I2C_SLAVE_ADDR2_MASK_CHECK(mask));
    
    MODIFY_REG(ptr_i2c->SADR2, (I2C_SADR2_SADR2 | I2C_SADR2_SADR2MSK), ((uint32_t)addr & I2C_SADR2_SADR2) | \
               (((uint32_t)mask << 8) & I2C_SADR2_SADR2MSK));
}

/**
  * @fn  void i2c_slave_address_config(i2c_reg_t* ptr_i2c, uint32_t addr)
  * @brief  Configures the slave address to be transmitted after start generation.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral. 
  * @param  addr: specifies the slave address.
  * @note   This function should be called before generating start condition.
  * @return None.
  */
void i2c_slave_address_config(i2c_reg_t* ptr_i2c, uint32_t addr)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_SLAVE_ADDR1_CHECK(addr));
             
    MODIFY_REG(ptr_i2c->CTR2, I2C_CTR2_MTADR, addr & I2C_CTR2_MTADR);
}

/**
  * @fn void i2c_request_direction_config(i2c_reg_t* ptr_i2c, uint16_t direction)
  * @brief  Configures the type of transfer request for the master.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  direction: specifies the transfer request direction, it can be one of the following values:
  *         @arg I2C_DIRECTION_TX (Master request a write transfer)
  *         @arg I2C_DIRECTION_RX (Master request a read transfer)  
  * @return None.
  */
void i2c_request_direction_config(i2c_reg_t* ptr_i2c, uint16_t direction)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_DIRECTION_CHECK(direction));
  
    MODIFY_REG(ptr_i2c->CTR2, I2C_CTR2_TDIR, (uint32_t)direction);   
}

/**
  * @fn void i2c_bytes_number_config(i2c_reg_t* ptr_i2c, uint8_t counter)
  * @brief  Configures the number of bytes to be transmitted/received.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  counter: specifies the number of bytes.
  * @return None.
  */
void i2c_bytes_number_config(i2c_reg_t* ptr_i2c, uint8_t counter)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    
    MODIFY_REG(ptr_i2c->CTR2, I2C_CTR2_BNUM, ((uint32_t)counter << 16) & I2C_CTR2_BNUM);
}    

/**
  * @fn void i2c_transfer_handle(i2c_reg_t* ptr_i2c, uint32_t addr, uint8_t counter, uint32_t end_select, uint32_t operate_set)
  * @brief  Handles I2C communication when starting transfer or during transfer.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  addr: specifies the slave address to be programmed.
  * @param  counter: specifies the number of bytes between 0 and 255.
  * @param  end_select: It can be one of the following values:
  *         @arg I2C_RELOAD_MODE (Enable Reload mode)
  *         @arg I2C_TRANFER_END_MODE (Enable Automatic end mode)
  *         @arg I2C_SOFTWARE_END_MODE (Enable Software end mode)
  * @param  operate_set: It can be one of the following values:
  *         @arg I2C_RELEASE_CONFIG(Don't Generate stop and start condition)
  *         @arg I2C_STOP_CONFIG (Generate stop condition, Number_Bytes should be set to 0)
  *         @arg I2C_READ_CONFIG (Generate Restart for read request)
  *         @arg I2C_WRITE_CONFIG (Generate Restart for write request).
  * @return 0 is fail. 1 is successful.
  */
uint32_t i2c_transfer_handle(i2c_reg_t* ptr_i2c, uint32_t addr, uint8_t counter, uint32_t end_select, uint32_t operate_set)
{
    ASSERT(I2C_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_SLAVE_ADDR1_CHECK(addr));  
    ASSERT(I2C_END_MODE_CHECK(end_select));
    ASSERT(I2C_OPERATE_CONFIG_CHECK(operate_set));
  
    if (((ptr_i2c->CTR1 & I2C_BUS_MODE_SMBUS_DEVICE) == I2C_BUS_MODE_SMBUS_DEVICE) && (counter == 1) && \
        (end_select == I2C_RELOAD_MODE))
    {
        return 0;
    }
        MODIFY_REG(ptr_i2c->CTR2, (I2C_CTR2_MTADR | I2C_CTR2_BNUM | I2C_CTR2_RELOADM | I2C_CTR2_TENDSEL | I2C_CTR2_TDIR | \
                   I2C_CTR2_STARTGEN | I2C_CTR2_STOPGEN), (addr & I2C_CTR2_MTADR) | (((uint32_t)counter << 16 ) & I2C_CTR2_BNUM) | \
                   end_select | operate_set);
    return 1;
}   

/**
  * @fn  void i2c_overtime_a_config(i2c_reg_t* ptr_i2c, uint16_t value)
  * @brief  Configures I2C timer A  for overtime control .
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @param  value: specifies the overtime value. 
  * @return None
  */
void i2c_overtime_a_config(i2c_reg_t* ptr_i2c, uint16_t value)
{
    ASSERT(I2C1_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_OVERTIME_CHECK(value));
    
    MODIFY_REG(ptr_i2c->OVRT, I2C_OVRT_TIMA, (uint32_t)value & I2C_OVRT_TIMA);
}

/**
  * @fn  void i2c_overtime_b_config(i2c_reg_t* ptr_i2c, uint16_t value)
  * @brief  Configures I2C timer B  for overtime control .
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @param  value: specifies the TimeoutB value. 
  * @return None
  */
void i2c_overtime_b_config(i2c_reg_t* ptr_i2c, uint16_t value)
{
    ASSERT(I2C1_BUS_CHECK(ptr_i2c));
    ASSERT(I2C_OVERTIME_CHECK(value));
    
    MODIFY_REG(ptr_i2c->OVRT, I2C_OVRT_TIMB, ((uint32_t)value << 16) & I2C_OVRT_TIMB);
}

/**
  * @fn void i2c_pec_enable_ctrl(i2c_reg_t* ptr_i2c, enable_state_t enable_flag)
  * @brief  Enables or disables I2C PEC calculation.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @param  enable_flag: It can be ENABLE or DISABLE.
  * @return None
  */
void i2c_pec_enable_ctrl(i2c_reg_t* ptr_i2c, enable_state_t enable_flag)
{   
    ASSERT(I2C1_BUS_CHECK(ptr_i2c));
    ASSERT(FUNCTIONAL_STATE_CHECK(enable_flag));
  
    if (enable_flag != DISABLE)
    {
        ptr_i2c->CTR2 &= (uint32_t)~((uint32_t)I2C_CTR2_NACKGEN);   
        if (((ptr_i2c->CTR1 & I2C_BUS_MODE_I2C) == I2C_BUS_MODE_I2C) && (ptr_i2c->SADR1 != 0x00))
        {
            ptr_i2c->CTR2 |= I2C_CTR2_STOPGEN;
        }
        /* Enable PEC calculation */
        ptr_i2c->CTR1 |= I2C_CTR1_PECMEN;   
    }
    else
    {
        /* Disable PEC calculation */    
        ptr_i2c->CTR1 &= (uint32_t)~((uint32_t)I2C_CTR1_PECMEN); 
    }
}


/**
  * @}
  */

/**
  * @}
  */

