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
        Adc_Val.Cover_Value = bubble_sort_average_value(&Adc_Value_Buff[Cover_Index][0],7);
        Adc_Val.Water_Pump = bubble_sort_average_value(&Adc_Value_Buff[WaterPump_Index][0],7);
        Adc_Val.Sol_Value  = bubble_sort_average_value(&Adc_Value_Buff[SolValue_Index][0],7);
        Adc_Val.Power_IN   = bubble_sort_average_value(&Adc_Value_Buff[PowerIN_Index][0],7);
        Adc_Val.Power_24V  = bubble_sort_average_value(&Adc_Value_Buff[Power24V_Index][0],7);//1795
        Adc_Val.Refint_IN  = bubble_sort_average_value(&Adc_Value_Buff[RefintIN_Index][0],7);
                            //1530          //1000/1260
        Vref_Cal = (3300 * VREFINT_CAL) / (Adc_Val.Refint_IN); //3300mV  //4999
        CalVal.Cover_Value = (Vref_Cal * Adc_Val.Cover_Value) / 4095;//mV
        CalVal.Water_Pump = (Vref_Cal * Adc_Val.Water_Pump) / 4095;//mV
        CalVal.Sol_Value  = (Vref_Cal * Adc_Val.Sol_Value) / 4095; //232mv
        CalVal.Power_IN   = (Vref_Cal * Adc_Val.Power_IN) / 4095;  //1925mV
        CalVal.Power_24V  = (Vref_Cal * Adc_Val.Power_24V) / 4095; //2155mv
        
        if(CalVal.Cover_Value >= 1500) //±ÕºÏ2500mv£¬´ò¿ª290mv
        {
            Error_Stu.err_cover = 0;
        }
        else
        {
            Error_Stu.err_cover = 1;
        }
        
        if(CalVal.Power_IN > POWER_IN_15V)     PowerIN_state = 3;
        else if(CalVal.Power_IN > POWER_IN_9V) PowerIN_state = 2;
        else PowerIN_state = 1;
        
        if(CalVal.Power_24V >= Power_24V_TYPE-50) Error_Stu.err_24v = 0;
        else Error_Stu.err_24v = 1;
        
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

void AirCooler_Worke(void)
{
    if(flag_fan_sw==0 && Error_Stu.err_cover==0 && Error_Stu.err_24v==0)
    {
        flag_fan_sw = 1;
        Fan_Open();
    }
    if(flag_fan_sw)
    {
        
    }
    error_deal();
}

void error_deal(void)
{
    if(Error_Stu.err_byte != 0)
    {
        LED_ABNORMAL(ON);
    }
    else LED_ABNORMAL(OFF);
    
    if(flag_fan_sw == 1)
    {
        if(Error_Stu.err_cover==1 || Error_Stu.err_24v==1) Fan_Off();
    }
}

u8 Power_supply_detection(void)
{
    adc_dma_value();
    if(flag_adc_ok && time_ms == 0)
    {
        flag_adc_ok = 0;
        time_ms = 100;
        Adc_Val.Power_IN   = bubble_sort_average_value(&Adc_Value_Buff[PowerIN_Index][0],7);
        Adc_Val.Refint_IN  = bubble_sort_average_value(&Adc_Value_Buff[RefintIN_Index][0],7);
        Vref_Cal = (3300 * VREFINT_CAL) / (Adc_Val.Refint_IN); //3300mV  //4999
        CalVal.Power_IN = (Vref_Cal * Adc_Val.Power_IN) / 4095;  //1925mV

        if(typec_sel == TYPEC_20V && CalVal.Power_IN < POWER_IN_20V)//1844
        {
            type_c_select(TYPEC_12V);
            return 1;
        }
        else if(typec_sel == TYPEC_12V && CalVal.Power_IN < POWER_IN_12V)//1175
        {
            type_c_select(TYPEC_9V);
            return 1;
        }
        else if(typec_sel == TYPEC_9V && CalVal.Power_IN < POWER_IN_9V)//818
        {
            type_c_select(TYPEC_5V);
            return 1;
        }
        return 0;
    }
    return 1;
}

void type_c_select(TYPEC_SEL sel)
{
    switch(sel)
    {
        case TYPEC_9V:
            CH224A_CFG2(0);
            CH224A_CFG3(0); //9V
            typec_sel = TYPEC_9V;
            break;
        
        case TYPEC_12V:
            CH224A_CFG2(0);
            CH224A_CFG3(1); //12V
            typec_sel = TYPEC_12V;
            break;
        
        case TYPEC_20V:
            CH224A_CFG2(1);
            CH224A_CFG3(1); //20V
            typec_sel = TYPEC_20V;
            break;
        
        default:
            typec_sel = TYPEC_5V;
            break;
    }
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
