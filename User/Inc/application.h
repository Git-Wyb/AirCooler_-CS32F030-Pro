#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "sys.h"

#define SOL_VALUE_TYPE   232
#define POWER_IN_TYPE    1925
#define Power_24V_TYPE   2155

/*
不工作：0mv
水泵空转：33    
水泵抽水：105   
水泵半堵：157   
水泵堵死：>210
*/
#define WATER_PUMP_IDLE_TYPE    33
#define WATER_PUMP_NORMAL_TYPE  105
#define WATER_PUMP_HALF_TYPE    157
#define WATER_PUMP_COMP_TYPE    210    


u16 bubble_sort_average_value(u16 *buff,u16 len);
void get_adc_value_deal(void);



#endif
