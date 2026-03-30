/**
  * @file    cs32f0xx_i2c.h
  * @brief   This file contains all the functions prototypes for the I2C firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2020 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_I2C_H__
#define __CS32F0XX_I2C_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"
#include "cs32f0xx_rcu.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Constants
  * @{
  */


/**
  * @struct i2c_config_t
  * @brief  I2C Init structure definition
  */

typedef struct
{
    uint32_t tmr_value;     //!< Specifies the I2C_TMR register value(referring to I2C Timing).                                         
    uint32_t analog_flag;   //!< Enables or disables analog noise filter.                                      
    uint32_t digital_value; //!< Sets the digital noise filter. range in 0x00 ~ 0x0F.                                        
    uint32_t mode;          //!< Sets the I2C mode.                                        
    uint32_t slave_addr1;   //!< Sets slave address 1. It can be a 7bits or 10bits address.                                       
    uint32_t ack_flag;      //!< Enables or disables the acknowledgement.                                    
    uint32_t ack_addr;      //!< Sets acknowledge address.It can be a 7bits or 10bits address.                                       
}i2c_config_t;

/**
  * @brief I2C bus check definition
  */
#define I2C_BUS_CHECK(bus)                  (((bus) == I2C1) || ((bus) == I2C2))  

#define I2C1_BUS_CHECK(bus)                 ((bus) == I2C1) 

/** 
  * @ brief I2C analog filter definition
  */
#define I2C_ANALOG_FILTER_ENABLE            ((uint32_t)0x00000000)  //!< enable analog Filter 
#define I2C_ANALOG_FILTER_DISABLE           I2C_CTR1_AFDIS          //!< disable analog Filter

#define I2C_ANALOG_FILTER_CHECK(flag)       (((flag) == I2C_ANALOG_FILTER_ENABLE) || ((flag) == I2C_ANALOG_FILTER_DISABLE))

/**
  * @ brief I2C digital filter value check
  */
#define I2C_DIGITAL_FILTER_CHECK(filter)    ((filter) <= 0x0000000F)

/** 
  * @ brief I2C bus mode definition
  */
#define I2C_BUS_MODE_I2C                    ((uint32_t)0x00000000)  //!< I2C mode
#define I2C_BUS_MODE_SMBUS_DEVICE           I2C_CTR1_SMBDDAEN       //!< SMBus Device mode (SMBUS is not supported for CS32F036 and CS32F03X-RA devices)
#define I2C_BUS_MODE_SMBUS_HOST             I2C_CTR1_SMBHAEN        //!< SMBus Host mode (SMBUS is not supported for CS32F036 and CS32F03X-RA devices)

#define I2C_BUS_MODE_CHECK(mode)            (((mode) == I2C_BUS_MODE_I2C) || ((mode) == I2C_BUS_MODE_SMBUS_DEVICE) || \
											((mode) == I2C_BUS_MODE_SMBUS_HOST))
/** 
  * @ brief I2C ACK and check definition
  */
#define I2C_ACK_ENABLE                      ((uint32_t)0x00000000)  //!< enable ACK
#define I2C_ACK_DISABLE                     I2C_CTR2_NACKGEN        //!< disable ACK

#define I2C_ACK_CONFIG_CHECK(ACK)           (((ACK) == I2C_ACK_ENABLE) || ((ACK) == I2C_ACK_DISABLE))  

/** 
  * @ brief I2C Addressing format definition
  */
#define I2C_ACK_ADDR_7BITS                  ((uint32_t)0x00000000)  //!< Slave Address 7bits
#define I2C_ACK_ADDR_10BITS                 I2C_SADR1_SADR1MODE     //!< Slave Address 10bits

#define I2C_ACK_ADDR_CHECK(addr)            (((addr) == I2C_ACK_ADDR_7BITS) || ((addr) == I2C_ACK_ADDR_10BITS))
                                          
/** 
  * @ brief I2C slave addr1 check definition
  */
#define I2C_SLAVE_ADDR1_CHECK(addr)         ((addr) <= (uint32_t)0x000003FF) 

/** 
  * @ brief I2C slave addr2 check definition
  */
#define I2C_SLAVE_ADDR2_CHECK(addr)         ((addr) <= (uint16_t)0x00FF)

/** 
  * @ brief I2C data Tx/Rx direction definition
  */
#define I2C_DIRECTION_TX                    ((uint16_t)0x0000)      //!<set data Transfer direction for writing 
#define I2C_DIRECTION_RX                    ((uint16_t)0x0400)      //!<set data Transfer direction for reading 

#define I2C_DIRECTION_CHECK(direct)         (((direct) == I2C_DIRECTION_TX) || ((direct) == I2C_DIRECTION_RX))
                                         
/** 
  * @ brief check  I2c slave address2 mask value definition
  */
#define I2C_SLAVE_ADDR2_MASK_CHECK(mask)    ((mask) < ((uint8_t)0x08)) 
                                         
/** 
  * @ brief I2C  timer overtime value check definition
  */
#define I2C_OVERTIME_CHECK(value)           ((value) <= (uint16_t)0x0FFF)

/** 
  * @brief I2C interrupts definition
  */
#define I2C_INTR_TXINT                      I2C_CTR1_TXINTFIE       //!< Enable bit for TX interrupt
#define I2C_INTR_RXNE                       I2C_CTR1_RXNEIE         //!< Enable bit for RX interrupt
#define I2C_INTR_ADRM                       I2C_CTR1_ADRMIE         //!< Enable bit for address match interrupt
#define I2C_INTR_NACK                       I2C_CTR1_NACKRIE        //!< Enable bit for not acknowledge received interrupt
#define I2C_INTR_STOP                       I2C_CTR1_STOPDIE        //!< Enable bit for STOP detection interrupt
#define I2C_INTR_CMP                        I2C_CTR1_CMPIE          //!< Enable bit for transfer complete interrupt
#define I2C_INTR_RLD                        I2C_CTR1_CMPIE          //!< Enable bit for transfer complete reload interrupt
#define I2C_INTR_BUSERR                     I2C_CTR1_ERRDIE         //!< Enable bit for bus error detection interrupt
#define I2C_INTR_ARBLO                      I2C_CTR1_ERRDIE         //!< Enable bit for arbitration lost interrupt
#define I2C_INTR_OVR                        I2C_CTR1_ERRDIE         //!< Enable bit for overflow or underflow interrupt
#define I2C_INTR_PECERR                     I2C_CTR1_ERRDIE         //!< Enable bit for PEC error interrupt
#define I2C_INTR_TIMEOUT                    I2C_CTR1_ERRDIE         //!< Enable bit for overtime or tLOW detection interrupt
#define I2C_INTR_SMBA                       I2C_CTR1_ERRDIE         //!< Enable bit for SMBus alert interrupt

/** 
  * @brief I2C flags definition
  */
#define I2C_FLAG_TXE                        I2C_STS_TXEF            //!< Data register empty flag in transmitting mode       
#define I2C_FLAG_TXINT                      I2C_STS_TXINTF          //!< Transmit interrupt flag
#define I2C_FLAG_RXNE                       I2C_STS_RXNEF           //!< Data register not empty in receiving mode
#define I2C_FLAG_ADRM                       I2C_STS_ADRF            //!< Slave mode address matched flag
#define I2C_FLAG_NACK                       I2C_STS_NACKF           //!< NACK received flag
#define I2C_FLAG_STOP                       I2C_STS_STOPF           //!< Stop detection flag
#define I2C_FLAG_CMP                        I2C_STS_CMPF            //!< Master mode transfer complete flag
#define I2C_FLAG_RLD                        I2C_STS_RLDF            //!< Reload flag
#define I2C_FLAG_BUSERR                     I2C_STS_BUSERRF         //!< Bus error flag
#define I2C_FLAG_ARBLO                      I2C_STS_ARBLOF          //!< Arbitration lost flag
#define I2C_FLAG_OVR                        I2C_STS_OVRF            //!< overflow or underflow flag
#define I2C_FLAG_PECERR                     I2C_STS_PECERRF         //!< PEC Error flag
#define I2C_FLAG_TIMEOUT                    I2C_STS_TIMEOUT         //!< Overtime or tLOW detection flag
#define I2C_FLAG_SMBA                       I2C_STS_SMBAF           //!< SMBus alert flag
#define I2C_FLAG_BUSY                       I2C_STS_BUSYF           //!< Bus busy flag
                               
/** 
  * @brief I2C transfer end mode definition
  */
#define  I2C_RELOAD_MODE                    I2C_CTR2_RELOADM        //!<  bytes number reload mode
#define  I2C_TRANFER_END_MODE               I2C_CTR2_TENDSEL        //!< tranfer end mode 
#define  I2C_SOFTWARE_END_MODE              ((uint32_t)0x00000000)  //!< software end mode
                              
#define I2C_END_MODE_CHECK(mode)            (((mode) == I2C_RELOAD_MODE) || ((mode) == I2C_TRANFER_END_MODE) || \
											((mode) == I2C_SOFTWARE_END_MODE))                                                                       
/** 
  * @brief I2C bus operation config definition
  */
#define  I2C_RELEASE_CONFIG                 ((uint32_t)0x00000000)  //!< I2C BUS release
#define  I2C_STOP_CONFIG                    I2C_CTR2_STOPGEN        //!< I2C BUS stop config
#define  I2C_WRITE_CONFIG                   I2C_CTR2_STARTGEN       //!< I2C BUS  write config                 
#define  I2C_READ_CONFIG                    (uint32_t)(I2C_CTR2_STARTGEN | I2C_CTR2_TDIR)  //!<I2C BUS read config
                              
#define I2C_OPERATE_CONFIG_CHECK(mode)      (((mode) == I2C_STOP_CONFIG) || ((mode) == I2C_READ_CONFIG) || \
											((mode) == I2C_WRITE_CONFIG) || ((mode) == I2C_RELEASE_CONFIG))
                                                                                 
/**
  * @brief I2C function register definition
  */
#define I2C_ENABLE_REG_CLK_DISSTRETCH       CTR1                    //!< clock stretching disable
#define I2C_ENABLE_REG_WAKEUP               CTR1                    //!< Wakeup from deepsleep mode enable
#define I2C_ENABLE_REG_GENERAL_CALL         CTR1                    //!< General call 
#define I2C_ENABLE_REG_SLV_RESPONSE         CTR1                    //!< Slave response
#define I2C_ENABLE_REG_ALERT                CTR1                    //!< SMBus alert enable
#define I2C_ENABLE_REG_PEC_MODE             CTR1                    //!< PEC mode enable
#define I2C_ENABLE_REG_RELOAD_MODE          CTR2                    //!< Reload mode enable
#define I2C_ENABLE_REG_AUTO_END_MODE        CTR2                    //!< Automatic end mode
#define I2C_ENABLE_REG_SLAVE_ADDR2          SADR2                   //!< Slave address 2
#define I2C_ENABLE_REG_OVERTIME_A           OVRT                    //!< Overtime A enable
#define I2C_ENABLE_REG_OVERTIME_B           OVRT                    //!< Overtime B enable
#define I2C_ENABLE_REG_OVERTIME_IDLE        OVRT                    //!< Idle overtime enable

/**
  * @brief I2C function bit definition
  */
#define I2C_ENABLE_BIT_CLK_DISSTRETCH       I2C_CTR1_DISSTRETCH     //!< clock stretching disable
#define I2C_ENABLE_BIT_WAKEUP               I2C_CTR1_WKUPEN         //!< Wakeup from deepsleep mode enable
#define I2C_ENABLE_BIT_GENERAL_CALL         I2C_CTR1_GCEN           //!< General call 
#define I2C_ENABLE_BIT_SLV_RESPONSE         I2C_CTR1_SLVRC          //!< Slave response
#define I2C_ENABLE_BIT_ALERT                I2C_CTR1_SMBAEN         //!< SMBus alert enable
#define I2C_ENABLE_BIT_PEC_MODE             I2C_CTR1_PECMEN         //!< PEC mode enable
#define I2C_ENABLE_BIT_RELOAD_MODE          I2C_CTR2_RELOADM        //!< Reload mode enable
#define I2C_ENABLE_BIT_AUTO_END_MODE        I2C_CTR2_TENDSEL        //!< Automatic end mode
#define I2C_ENABLE_BIT_SLAVE_ADDR2          I2C_SADR2_SADR2EN       //!< Slave address 2
#define I2C_ENABLE_BIT_OVERTIME_A           I2C_OVRT_TIMAEN         //!< Overtime A enable
#define I2C_ENABLE_BIT_OVERTIME_B           I2C_OVRT_TIMBEN         //!< Overtime B enable
#define I2C_ENABLE_BIT_OVERTIME_IDLE        I2C_OVRT_IDLEDEN        //!< Idle overtime enable

/**
  * @ brief I2C DMA transfer requests definition
  */
#define I2C_DMA_TX_REQUEST                  I2C_CTR1_TXDMAREQEN     //!< Enable  transmission DMA requests
#define I2C_DMA_RX_REQUEST                  I2C_CTR1_RXDMAREQEN     //!< Enable bit for reception DMA requests

/**
  * @}
  */

/**
  * @brief  Configures the I2C registers to their default reset values.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None.
  */
#define __I2C_DEF_INIT(I2Cx)                    do{ \
                                                    ((RCU_PERI_RST_REG_##I2Cx) |= (RCU_PERI_RST_BIT_##I2Cx)); \
                                                    ((RCU_PERI_RST_REG_##I2Cx) &= ~(RCU_PERI_RST_BIT_##I2Cx)); \
                                                }while(0)

/**
  * @brief  Sends a data byte through the I2C bus.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  VALUE: Byte to be transmitted.
  * @return None
  */
#define __I2C_DATA_SEND(I2Cx, VALUE)            ((I2Cx)->TXBUF = (uint8_t)VALUE)

/**
  * @brief  Returns the most recent received data by the I2C bus..
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return The value of the received data.
  */
#define __I2C_DATA_RECV(I2Cx)                   ((uint8_t)((I2Cx)->RXBUF))

/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None
  */
#define __I2C_START_GENERATE(I2Cx)              ((I2Cx)->CTR2 |= I2C_CTR2_STARTGEN)

/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None
  */
#define __I2C_STOP_GENERATE(I2Cx)               ((I2Cx)->CTR2 |= I2C_CTR2_STOPGEN)

/**
  * @brief  Generates NACK.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None
  */
#define __I2C_NACK_GENERATE(I2Cx)               ((I2Cx)->CTR2 |= I2C_CTR2_NACKGEN)

/**
  * @brief  Request PECCODE transfer.
  * @param  I2Cx: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @return None
  */
#define __I2C_PEC_REQUEST(I2Cx)                 ((I2Cx)->CTR2 |= I2C_CTR2_PECCTR)

/**
  * @brief  Enables the specified I2C peripheral.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None.
  */
#define __I2C_ENABLE(I2Cx)                      ((I2Cx)->CTR1 |= I2C_CTR1_I2CEN)

/**
  * @brief  Disables the specified I2C peripheral.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None.
  */
#define __I2C_DISABLE(I2Cx)                     ((I2Cx)->CTR1 &= ~I2C_CTR1_I2CEN)

/**
  * @brief  Returns the I2C slave received request.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return The value of the received request. It can be a value of the following values:
  *         @arg I2C_DIRECTION_RX (the slave is to transmit data)
  *         @arg I2C_DIRECTION_TX (the slave is to receive data)  
  */                                              
#define __I2C_TRANSFER_DIR_GET(I2Cx)            (((I2Cx)->STS & I2C_STS_DIRF) ? I2C_DIRECTION_RX : I2C_DIRECTION_TX)

/**
  * @brief  Returns the I2C matched slave address.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return The value of the slave matched address.
  */
#define __I2C_MATCH_ADDR_GET(I2Cx)              ((uint8_t)(((I2Cx)->STS & I2C_STS_MSLVA) >> 16))

/**
  * @brief  Returns the I2C received PEC value .
  * @param  I2Cx: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @return The value of the PEC .
  */
#define __I2C_PECCODE_GET(I2Cx)                 ((uint8_t)((I2Cx)->PECCODE & I2C_PECCODE_PECCODE))

/**
  * @brief  Enables the specified I2C function.           
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.  
  * @param  FUNC: specifies the I2C function, it can be one of the following values:
  *         @arg CLK_DISSTRETCH (clock stretching disable)
  *         @arg WAKEUP (wakeup from deepsleep mode oly for I2C1, not available for CS32F030 devices)
  *         @arg SLAVE_ADDR2 (salve address 2)     
  *         @arg GENERAL_CALL (general call)  
  *         @arg SLV_RESPONSE (slave response)  
  *         @arg RELOAD_MODE (reload mode, available for CS32F036 or CS32F03X-RA devices) 
  *         @arg AUTO_END_MODE (automatic end mode)   
  *         @arg OVERTIME_A (overtime A oly for I2C1)  
  *         @arg OVERTIME_B (overtime B oly for I2C1) 
  *         @arg OVERTIME_IDLE (overtime IDLE oly for I2C1)
  *         @arg ALERT (SMBus alert)(SMBUS is not supported for CS32F036 and CS32F03X-RA devices)  
  * @return None.
  */
#define __I2C_FUNC_ENABLE(I2Cx, FUNC)           ((I2Cx)->I2C_ENABLE_REG_##FUNC |= (I2C_ENABLE_BIT_##FUNC))

/**
  * @brief  Disables the specified I2C function. 
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.  
  * @param  FUNC: specifies the I2C function, it can be one of the following values:
  *         @arg CLK_DISSTRETCH (clock stretching disable)
  *         @arg WAKEUP (wakeup from deepsleep mode oly for I2C1, not available for CS32F030 devices)
  *         @arg SLAVE_ADDR2 (salve address 2)     
  *         @arg GENERAL_CALL (general call)  
  *         @arg SLV_RESPONSE (slave response)  
  *         @arg RELOAD_MODE (reload mode, available for CS32F036 or CS32F03X-RA devices) 
  *         @arg AUTO_END_MOE (automatic end mode)  
  *         @arg OVERTIME_A (overtime A oly for I2C1)  
  *         @arg OVERTIME_B (overtime B oly for I2C1) 
  *         @arg OVERTIME_IDLE (overtime IDLE oly for I2C1)
  *         @arg ALERT (SMBus alert)(SMBUS is not supported for CS32F036 and CS32F03X-RA devices)  
  * @return None.
  */
#define __I2C_FUNC_DISABLE(I2Cx, FUNC)          ((I2Cx)->I2C_ENABLE_REG_##FUNC &= ~(I2C_ENABLE_BIT_##FUNC))

/**
  * @brief  Enables the I2C DMA transfer.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  REQ: specifies the I2C DMA transfer request to be enabled. This parameter can be any combination of the
  *         following values:
  *         @arg I2C_DMA_TX_REQUEST(Tx DMA transfer request)
  *         @arg I2C_DMA_RX_REQUEST(Rx DMA transfer request)
  * @return None.
  */
#define __I2C_DMA_ENABLE(I2Cx, REQ)             ((I2Cx)->CTR1 |= REQ) 

/**
  * @brief  Disables the I2C DMA transfer.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  REQ: specifies the I2C DMA transfer request to be disabled. This parameter can be any combination of the
  *         following values:
  *         @arg I2C_DMA_TX_REQUEST(Tx DMA transfer request)
  *         @arg I2C_DMA_RX_REQUEST(Rx DMA transfer request)
  * @return None.
  */
#define __I2C_DMA_DISABLE(I2Cx, REQ)            ((I2Cx)->CTR1 &= ~(REQ))

/**
  * @brief  Enables the specified I2C interrupts.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  INT: specifies the I2C interrupts sources to be enabled. It can be any combination of the following values:
  *         @arg I2C_INTR_TXINT (TX interrupt)
  *         @arg I2C_INTR_RXNE (RX interrupt)
  *         @arg I2C_INTR_ADRM (Address match interrupt)
  *         @arg I2C_INTR_NACK (Not acknowledge received interrupt)
  *         @arg I2C_INTR_STOP (STOP detection interrupt)
  *         @arg I2C_INTR_CMP (Transfer complete interrupt)
  *         @arg I2C_INTR_RLD (Transfer complete reload interrupt, available for CS32F036 or CS32F03X-RA devices)
  *         @arg I2C_INTR_BUSERR (Bus error detection interrupt)
  *         @arg I2C_INTR_ARBLO (Arbitration lost interrupt)
  *         @arg I2C_INTR_OVR (overflow or underflow interrupt)
  *         @arg I2C_INTR_PECERR (PEC error interrupt)
  *         @arg I2C_INTR_TIMEOUT (Overtime or tLOW detection interrupt)
  *         @arg I2C_INTR_SMBA (SMBus alert interrupt)(SMBUS is not supported for CS32F036 and CS32F03X-RA devices)

  * @return None.
  */
#define __I2C_INTR_ENABLE(I2Cx, INT)            ((I2Cx)->CTR1 |= INT)

/**
  * @brief  Disables the specified I2C interrupts.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  INT: specifies the I2C interrupts sources to be disabled. It can be any combination of the following values:
  *         @arg I2C_INTR_TXINT (TX interrupt)
  *         @arg I2C_INTR_RXNE (RX interrupt)
  *         @arg I2C_INTR_ADRM (Address match interrupt)
  *         @arg I2C_INTR_NACK (Not acknowledge received interrupt)
  *         @arg I2C_INTR_STOP (STOP detection interrupt)
  *         @arg I2C_INTR_CMP (Transfer complete interrupt)
  *         @arg I2C_INTR_RLD (Transfer complete reload interrupt, available for CS32F036 or CS32F03X-RA devices)
  *         @arg I2C_INTR_BUSERR (Bus error detection interrupt)
  *         @arg I2C_INTR_ARBLO (Arbitration lost interrupt)
  *         @arg I2C_INTR_OVR (overflow or underflow interrupt)
  *         @arg I2C_INTR_PECERR (PEC error interrupt)
  *         @arg I2C_INTR_TIMEOUT (Overtime or tLOW detection interrupt)
  *         @arg I2C_INTR_SMBA (SMBus alert interrupt)(SMBUS is not supported for CS32F036 and CS32F03X-RA devices)
  * @return None.
  */
#define __I2C_INTR_DISABLE(I2Cx, INT)           ((I2Cx)->CTR1 &= ~(INT))

/**
  * @brief  Checks whether the specified I2C interrupt enable bit is set or not.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  INT: specifies the I2C interrupts sources. It can be any combination of the following values:
  *         @arg TXINT (TX interrupt)
  *         @arg RXNE (RX interrupt)
  *         @arg ADRM (Address match interrupt)
  *         @arg NACK (Not acknowledge received interrupt)
  *         @arg STOP (STOP detection interrupt)
  *         @arg CMP (Transfer complete interrupt)
  *         @arg RLD (Transfer complete reload interrupt, available for CS32F036 or CS32F03X-RA devices)
  *         @arg BUSERR (Bus error detection interrupt)
  *         @arg ARBLO (Arbitration lost interrupt)
  *         @arg OVR (overflow or underflow interrupt)
  *         @arg PECERR (PEC error interrupt)
  *         @arg TIMEOUT (Overtime or tLOW detection interrupt)
  *         @arg SMBA (SMBus alert interrupt)(SMBUS is not supported for CS32F036 and CS32F03X-RA devices)
  * @return The state (SET or RESET).
  */
#define __I2C_INTR_ENABLE_STATUS_GET(I2Cx, INT) (((I2Cx)->CTR1 & (I2C_INTR_##INT)) ? SET : RESET)

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.  
  * @param  INT: specifies the I2C interrupt source to check. It can be one of the following values:
  *         @arg TXINT (Transmit interrupt status flag)
  *         @arg RXNE (Receive data register not empty)
  *         @arg ADRM (Slave mode Address matched flag)
  *         @arg NACK (NACK received flag)
  *         @arg STOP (STOP detection flag)
  *         @arg CMP (Transfer complete, master mode)
  *         @arg RLD (Transfer complete reload, available for CS32F036 or CS32F03X-RA devices)
  *         @arg BUSERR (Bus error)
  *         @arg ARBLO (Arbitration lost)
  *         @arg OVR (Slave Overflow/Underflow)
  *         @arg PECERR (PEC error in reception)
  *         @arg TIMEOUT (Overtime or tLOW detection flag)
  *         @arg SMBA (SMBus Alert)(SMBUS is not supported for CS32F036 or CS32F03X-RA devices)
  * @return SET or RESET.
  */
#define __I2C_INTR_STATUS_GET(I2Cx, INT)        (__I2C_INTR_ENABLE_STATUS_GET(I2Cx, INT) && __I2C_FALG_STATUS_GET(I2Cx, INT))

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  FLAG: specifies the flag to check. It can be one of the following values:
  *         @arg TXE (Data register empty flag in transmitting mode)
  *         @arg TXINT (Transmit interrupt status flag)
  *         @arg RXNE (Receive data register not empty)
  *         @arg ADRM (Slave mode Address matched flag)
  *         @arg NACK (NACK received flag)
  *         @arg STOP (STOP detection flag)
  *         @arg CMP (Transfer complete, master mode)
  *         @arg RLD (Transfer complete reload, available for CS32F036 or CS32F03X-RA devices)
  *         @arg BUSERR (Bus error)
  *         @arg ARBLO (Arbitration lost)
  *         @arg OVR (Slave Overflow/Underflow)
  *         @arg PECERR (PEC error in reception)
  *         @arg TIMEOUT (Overtime or tLOW detection flag)
  *         @arg SMBA (SMBus Alert)(SMBUS is not supported for CS32F036 or CS32F03X-RA devices)
  *         @arg BUSY (Bus busy)
  * @return The state (SET or RESET).
  */
#define __I2C_FALG_STATUS_GET(I2Cx, FLAG)       (((I2Cx)->STS & (I2C_FLAG_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the I2Cx's pending flags.
  * @param  I2Cx: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  FLAG: specifies the flag to check. It can be any combination of the following values:
  *         @arg I2C_FLAG_ADRM (Slave mode Address matched flag)
  *         @arg I2C_FLAG_NACK (NACK received flag)
  *         @arg I2C_FLAG_STOP (STOP detection flag)
  *         @arg I2C_FLAG_BUSERR (Bus error)
  *         @arg I2C_FLAG_ARBLO (Arbitration lost)
  *         @arg I2C_FLAG_OVR (Slave Overflow/Underflow)
  *         @arg I2C_FLAG_PECERR (PEC error in reception)
  *         @arg I2C_FLAG_TIMEOUT (Overtime or tLOW detection flag)
  *         @arg I2C_FLAG_SMBA (SMBus Alert)(SMBUS is not supported for CS32F036 or CS32F03X-RA devices)
  * @return None.
  */
#define __I2C_FLAG_CLEAR(I2Cx, FLAG)            ((I2Cx)->STSC = FLAG)

/**
  * @fn  void i2c_struct_init(i2c_config_t* ptr_struct)
  * @brief Config each ptr_struct member with its default value.
  * @param  ptr_struct: pointer to an i2c_config_t structure which will be initialized.
  * @return None.
  */
void i2c_struct_init(i2c_config_t* ptr_struct);

/**
  * @fn void i2c_init(i2c_reg_t* ptr_i2c, i2c_config_t* ptr_struct)
  * @brief  Initializes the ptr_i2c peripheral according to  the ptr_struct.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  ptr_struct: pointer to a i2c_config_t structure containing configuration value.          
  * @return None.
  */
void i2c_init(i2c_reg_t* ptr_i2c, i2c_config_t* ptr_struct);

/**
  * @fn void i2c_software_reset(i2c_reg_t* ptr_i2c)
  * @brief  Active the specified I2C software reset.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @return None.
  */
void i2c_software_reset(i2c_reg_t* ptr_i2c);

/**
  * @fn void i2c_slave_address2_config(i2c_reg_t* ptr_i2c, uint16_t addr, uint8_t mask)
  * @brief  Configures the I2C slave  address 2 and mask.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  addr: specifies the slave address.
  * @param  mask: specifies own address 2 mask to be programmed.
  * @return None.
  */
void i2c_slave_address2_config(i2c_reg_t* ptr_i2c, uint16_t addr, uint8_t mask);

/**
  * @fn  void i2c_slave_address_config(i2c_reg_t* ptr_i2c, uint32_t addr)
  * @brief  Configures the slave address to be transmitted after start generation.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral. 
  * @param  addr: specifies the slave address.
  * @note   This function should be called before generating start condition.
  * @return None.
  */
void i2c_slave_address_config(i2c_reg_t* ptr_i2c, uint32_t addr);

/**
  * @fn void i2c_request_direction_config(i2c_reg_t* ptr_i2c, uint16_t direction)
  * @brief  Configures the type of transfer request for the master.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  direction: specifies the transfer request direction, it can be one of the following values:
  *         @arg I2C_DIRECTION_TX (Master request a write transfer)
  *         @arg I2C_DIRECTION_RX (Master request a read transfer)  
  * @return None.
  */
void i2c_request_direction_config(i2c_reg_t* ptr_i2c, uint16_t direction);

/**
  * @fn void i2c_bytes_number_config(i2c_reg_t* ptr_i2c, uint8_t counter)
  * @brief  Configures the number of bytes to be transmitted/received.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 or 2 to select I2C peripheral.
  * @param  counter: specifies the number of bytes.
  * @return None.
  */
void i2c_bytes_number_config(i2c_reg_t* ptr_i2c, uint8_t counter);

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
uint32_t i2c_transfer_handle(i2c_reg_t* ptr_i2c, uint32_t addr, uint8_t counter, uint32_t end_select, uint32_t operate_set);

/**
  * @fn  void i2c_overtime_a_config(i2c_reg_t* ptr_i2c, uint16_t value)
  * @brief  Configures I2C timer A  for overtime control .
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @param  value: specifies the overtime value. 
  * @return None
  */
void i2c_overtime_a_config(i2c_reg_t* ptr_i2c, uint16_t value);

/**
  * @fn  void i2c_overtime_b_config(i2c_reg_t* ptr_i2c, uint16_t value)
  * @brief  Configures I2C timer B  for overtime control .
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @param  value: specifies the TimeoutB value. 
  * @return None
  */
void i2c_overtime_b_config(i2c_reg_t* ptr_i2c, uint16_t value);

/**
  * @fn void i2c_pec_enable_ctrl(i2c_reg_t* ptr_i2c, enable_state_t enable_flag)
  * @brief  Enables or disables I2C PEC calculation.
  * @param  ptr_i2c: pointer to I2Cx where x can be 1 to select I2C peripheral.
  * @param  enable_flag: It can be ENABLE or DISABLE.
  * @return None
  */
void i2c_pec_enable_ctrl(i2c_reg_t* ptr_i2c, enable_state_t enable_flag);


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

