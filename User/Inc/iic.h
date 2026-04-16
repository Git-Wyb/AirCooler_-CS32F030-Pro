#ifndef __IIC_H__
#define __IIC_H__

#include "sys.h"
#include "gpio.h"
#include "timer.h"

#define I2C_LONG_TIMEOUT         25//ms//((uint32_t)(10 * I2C_FLAG_TIMEOUT))

#define OWN_ADDRESS             0xA0
#define I2C_TIMING              (0x10420F13 / 3)
#define SLAVE_ADDR  0x23//0x26
#define WRITE_ADDR  (u8)(SLAVE_ADDR << 1)
#define READ_ADDR   (u8)(SLAVE_ADDR << 1 | 1)



void iic_master_config(void);
void Init_IIC(void);
u32 iic_master_write(u32 addr,u8 *pbuffer,u8 length);
u32 iic_master_read(u32 addr,u8 *pbuffer,u8 length);
u8 CH224A_Set_Voltage(u8 vol);
void init_iic_m(void);
void Write_CH224A(u8 ucAddr,u8 ucData);
u8 Read_CH224A(u8 ucAddr);
void delay_us(u32 us);

#endif
