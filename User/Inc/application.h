#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "sys.h"

#define SOL_VALUE_TYPE   232
#define POWER_IN_TYPE    1925
#define Power_24V_TYPE   2100
#define POWER_IN_20V     1700
#define POWER_IN_15V     1400
#define POWER_IN_12V     1000
#define POWER_IN_9V      700

/*
不工作：0mv
水泵空转：33    
水泵抽水：105   
水泵半堵：157   
水泵堵死：>210
*/
#define WATER_PUMP_IDLE_TYPE    80
#define WATER_PUMP_NORMAL_TYPE  150
#define WATER_PUMP_HALF_TYPE    200
#define WATER_PUMP_COMP_TYPE    210   

#define TIME_MINUTE             10 //10分钟
#define TIME_PUMP_WATER_AGAIN   (60 * 1000 * TIME_MINUTE) //interval time
#define TIME_FIRST_PUMP_WATER   (1000 * 15) //15s,The first pumping operation after power-on 
#define TIME_PUMP_WATER         (1000 * 10) //10s,Interval pumping
#define TIME_WAIT_AGAIN         (60 * 1000 * 5)//5 minute,Once again, draw water from the water tank

typedef enum
{
    TYPEC_5V,
    TYPEC_9V,
    TYPEC_12V,
    TYPEC_15V,
    TYPEC_20V
}TYPEC_SEL;


u16 bubble_sort_average_value(u16 *buff,u16 len);
void get_adc_value_deal(void);
void type_c_select(TYPEC_SEL sel);
u8 Power_supply_detection(void);
void AirCooler_Worke(void);
void error_deal(void);
void water_pump_worker(void);

#endif
