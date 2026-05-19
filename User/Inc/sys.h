#ifndef __SYS_H__
#define __SYS_H__

#include <stdio.h>
#include <string.h>
#include "cs32f0xx.h"
#include "cs32f0xx_conf.h"

#define SYS_CLK 16000000

typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct{
    u16 Water_Pump;
    u16 Sol_Value;
    u16 Power_IN;
    u16 Power_24V;
    u16 Refint_IN;
}BaseValueStu;

typedef union{
    u8 Flag;
    struct
    {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    }Bit;
}BaseFlagStu;

extern BaseFlagStu Un_Flag0;
extern BaseFlagStu Un_Flag1;
    
#define key_power_sta           Un_Flag0.Bit.b0
#define key_fan_sta             Un_Flag0.Bit.b1
#define key_pump_sta            Un_Flag0.Bit.b2
#define flag_rx_head            Un_Flag0.Bit.b3
#define flag_rx_done            Un_Flag0.Bit.b4

#define flag_fan_sw             Un_Flag1.Bit.b0
#define flag_fan                Un_Flag1.Bit.b1
#define flag_pump               Un_Flag1.Bit.b2 //水泵
#define flag_flow               Un_Flag1.Bit.b3 //水流
#define flag_level              Un_Flag1.Bit.b4 //水位
#define flag_cover              Un_Flag1.Bit.b5 //盖板
#define flag_adc_ok             Un_Flag1.Bit.b6 //盖板
#define flag_power              Un_Flag1.Bit.b7 //power

extern u16 fan_pwm_set;
extern u8 fan_speed_set;
extern u16 time_ms;
extern u32 time_pump;
extern u32 time_run;
extern u32 run_cnt;
extern u16 Adc_Value_Buff[5][7];
extern BaseValueStu Adc_Val;
extern BaseValueStu CalVal;
extern uint32_t Vref_Cal;
extern u8 water_pump_state;
extern u8 Solenoid_state;
extern u8 PowerIN_state;

//void Init_IWDG(void);
//void R_WDT_Restart(void);
//void Init_Delay(void);
//void delay_us(u32 nus);
//void delay_ms(u16 nms);

void Init_FWDT(void);
void FWDT_Clear(void);
void Init_system_clock(void);
void waiting_ms(u16 ms);

#endif
