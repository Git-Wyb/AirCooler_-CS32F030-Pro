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
    u16 Cover_Value;
    u16 Water_Pump;
    u16 Sol_Value;
    u16 Power_IN;
    u16 Power_24V;
    u16 Refint_IN;
}BaseValueStu;

typedef union{
    u8 sw2_input;
    struct
    {
        u8 low_input : 1;
        u8 mid_input : 1;
        u8 max_input : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
}SW2_STU;

typedef union{
    u8 err_byte;
    struct
    {
        u8 err_cover : 1;
        u8 err_sol   : 1;
        u8 err_pump  : 1;
        u8 err_24v   : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
}ERR_STU;

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
extern BaseFlagStu Un_Flag2;
extern ERR_STU Error_Stu;
    
#define key_power_sta           Un_Flag0.Bit.b0
#define key_fan_sta             Un_Flag0.Bit.b1
#define key_pump_sta            Un_Flag0.Bit.b2
#define flag_rx_head            Un_Flag0.Bit.b3
#define flag_rx_done            Un_Flag0.Bit.b4
#define flag_fan_worker         Un_Flag0.Bit.b5
#define flag_adc_pump           Un_Flag0.Bit.b6

#define flag_fan_sw             Un_Flag1.Bit.b0
#define flag_power_24v          Un_Flag1.Bit.b1
#define flag_pump               Un_Flag1.Bit.b2 //水泵
#define flag_flow               Un_Flag1.Bit.b3 //水流
#define flag_level              Un_Flag1.Bit.b4 //水位
#define flag_cover_state        Un_Flag1.Bit.b5 //盖板
#define flag_adc_ok             Un_Flag1.Bit.b6 
#define flag_power              Un_Flag1.Bit.b7 //power

#define flag_hydropenia         Un_Flag2.Bit.b0 //缺水
#define flag_COMP_TYPE          Un_Flag2.Bit.b1 //水泵堵死

extern u16 fan_pwm_set;
extern u8 fan_speed_set;
extern u16 time_ms;
extern u32 time_pump;
extern u32 time_run;
extern u32 run_cnt;
extern u16 ms_cnt;
extern u16 Adc_Value_Buff[6][7];
extern BaseValueStu Adc_Val;
extern BaseValueStu CalVal;
extern uint32_t Vref_Cal;
extern u8 water_pump_state;
extern u8 Solenoid_state;
extern u8 PowerIN_state;
extern SW2_STU Sw2Input_Stu;
extern SW2_STU Sw2LastInput_Stu;
extern u8 typec_sel;
extern u16 time_wait;
extern u8 worker_step;
extern u8 first_water_pump;
extern u32 time_pump_water_again;

//void Init_IWDG(void);
//void R_WDT_Restart(void);
//void Init_Delay(void);
//void delay_us(u32 nus);
//void delay_ms(u16 nms);

void Init_FWDT(void);
void FWDT_Clear(void);
void Init_system_clock(void);
void waiting_ms(u16 ms);
u16 DataFlash_Write_half_word(u16 addroffset,u16 data);
u16 DataFlash_Read_half_word(u16 addroffset);

#endif
