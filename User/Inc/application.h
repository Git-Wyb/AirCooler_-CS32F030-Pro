#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "sys.h"

#define SOL_VALUE_TYPE   232
#define Power_24V_TYPE   1925//2100 //AD 2187
#define POWER_IN_20V     1700//1900 //AD 1828
#define POWER_IN_15V     1590//18V
#define POWER_IN_12V     1000//11.0V
#define POWER_IN_9V       760//8.5V

/*
不工作：0mv
水泵空转：33    
水泵抽水：105   
水泵半堵：157   
水泵堵死：>210
*/
#define WATER_PUMP_IDLE_TYPE    60
#define WATER_PUMP_NORMAL_TYPE  150
#define WATER_PUMP_HALF_TYPE    200
#define WATER_PUMP_COMP_TYPE    210   

#define TIME_MINUTE             5 //10分钟
#define TIME_PUMP_WATER_AGAIN   (60 * 1000 * TIME_MINUTE) //interval time
#define TIME_FIRST_PUMP_WATER   (1000 * 15) //15//33s,The first pumping operation after power-on 
#define TIME_PUMP_WATER         (1000 * 5) //5s,Interval pumping
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
