#include "application.h"
#include "timer.h"
#include "gpio.h"
#include "uart.h"
#include "iic.h"
#include "adc.h"

void get_adc_value_deal(void)
{
    if(flag_adc_ok)
    {
        flag_adc_ok = 0;
        Adc_Val.Water_Pump = bubble_sort_average_value(&Adc_Value_Buff[WaterPump_Index][0],7);
        Adc_Val.Sol_Value  = bubble_sort_average_value(&Adc_Value_Buff[SolValue_Index][0],7);
        Adc_Val.Power_IN   = bubble_sort_average_value(&Adc_Value_Buff[PowerIN_Index][0],7);
        Adc_Val.Power_24V  = bubble_sort_average_value(&Adc_Value_Buff[Power24V_Index][0],7);//1795
        Adc_Val.Refint_IN  = bubble_sort_average_value(&Adc_Value_Buff[RefintIN_Index][0],7);
                            //1530          //1000/1260
        Vref_Cal = (3300 * VREFINT_CAL) / (Adc_Val.Refint_IN); //3300mV  //4999
        CalVal.Water_Pump = (Vref_Cal * Adc_Val.Water_Pump) / 4095;//mV
        CalVal.Sol_Value  = (Vref_Cal * Adc_Val.Sol_Value) / 4095; //232mv
        CalVal.Power_IN   = (Vref_Cal * Adc_Val.Power_IN) / 4095;  //1925mV
        CalVal.Power_24V  = (Vref_Cal * Adc_Val.Power_24V) / 4095; //2155mv
        
        if(CalVal.Power_IN >= POWER_IN_TYPE-50 && flag_fan_sw == 0 && CalVal.Power_24V >= Power_24V_TYPE-50)
        {
            flag_fan_sw = 1;
            Fan_Open();
        }
        
        if(CalVal.Sol_Value >= SOL_VALUE_TYPE-30)   Solenoid_state = 1;
        else Solenoid_state = 0;
        
        if(WATER_PUMP_IDLE_TYPE-23 <= CalVal.Water_Pump && CalVal.Water_Pump <= WATER_PUMP_IDLE_TYPE+20) //10-53
        {
            water_pump_state = 1;
        }
        else if(WATER_PUMP_NORMAL_TYPE-52 <= CalVal.Water_Pump && CalVal.Water_Pump <= WATER_PUMP_NORMAL_TYPE+30) //53-135
        {
            water_pump_state = 2;
        }
        else if(WATER_PUMP_HALF_TYPE-22 <= CalVal.Water_Pump && CalVal.Water_Pump <= WATER_PUMP_HALF_TYPE+30) //135-187
        {
            water_pump_state = 3;
        }
        else if(WATER_PUMP_COMP_TYPE-23 <= CalVal.Water_Pump)  //187
        {
            water_pump_state = 4;
        }
        else water_pump_state = 0;
    }
}

void water_pump_solenoid_deal(void)
{
    
    
}



u16 bubble_sort_average_value(u16 *buff,u16 len)
{
    u8 i=0,j=0;
    u16 temp = 0;
    if(len < 3) return 0;
    
    for (i = 0; i < len; i++)
	{
		for (j = 0; j < len - 1; j++) //sort from smallest to biggest
		{
			if (buff[j] > buff[j + 1])
			{
				temp = buff[j];
				buff[j] = buff[j + 1];
				buff[j + 1] = temp;
			}
		}
	}
    temp = 0;
    for(i = 1; i <= len-2; i++)
    {
        temp += buff[i];
    }
    
    return (temp / (len-2));
}
