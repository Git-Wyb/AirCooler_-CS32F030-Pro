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

        //if(CalVal.Power_24V >= Power_24V_TYPE-50) Error_Stu.err_24v = 0;
        //else Error_Stu.err_24v = 1;
        
        if(CalVal.Sol_Value >= SOL_VALUE_TYPE-30)   Solenoid_state = 1;
        else Solenoid_state = 0;
        
        if(CalVal.Water_Pump <= WATER_PUMP_IDLE_TYPE) //80
        {
            water_pump_state = 1;
        }
        else if(WATER_PUMP_IDLE_TYPE < CalVal.Water_Pump && CalVal.Water_Pump <= WATER_PUMP_NORMAL_TYPE) //80-150
        {
            water_pump_state = 2;
            flag_hydropenia = 0;
        }
        else if(WATER_PUMP_NORMAL_TYPE < CalVal.Water_Pump && CalVal.Water_Pump <= WATER_PUMP_HALF_TYPE) //150-200
        {
            water_pump_state = 3;
            flag_hydropenia = 0;
        }
        else if(WATER_PUMP_HALF_TYPE < CalVal.Water_Pump)  //>200
        {
            water_pump_state = 4;
        }
        
        flag_fan_worker = 1;
        flag_adc_pump = 1;
    }
}

void AirCooler_Worke(void)
{
    if(flag_fan_worker==1 && flag_fan_sw==0 && Error_Stu.err_cover==0 && Error_Stu.err_24v==0)
    {
        if(PowerIN_state >= 2)
        {
            flag_fan_sw = 1;
            Fan_Open();
            led_fan(fan_pwm_set);
            time_wait = 2000; //2s
            if(flag_water_last == 1)
            {
                flag_water_last = 0;
                worker_step = 0;
                time_pump_water_again = time_pump_water_again_last;
            }
            else
            {
                worker_step = 1;
            }
        }
    }
    error_deal();
    water_pump_worker();
} 

u32 nexttime = 0;
u8 pump_idle_cnt = 0;
u8 pump_comp_cnt = 0;
void water_pump_worker(void)
{
    if(flag_fan_sw)
    {
        switch(worker_step)
        {
            case 0:
                time_pump = 0;
                time_wait = 0;
                flag_pump = 0;
                flag_water_tank = 0;
                pump_idle_cnt = 0;
                pump_comp_cnt = 0;
                if(first_water_pump == 1 && time_pump_water_again == 0)
                {
                    worker_step = 1;
                }
                break;
            
            case 1:
                if(time_wait == 0)
                {
                    if(first_water_pump == 0) time_pump = TIME_FIRST_PUMP_WATER; //20s
                    else time_pump = TIME_PUMP_WATER; //10s
                    first_water_pump = 1;
                    SWITCH_PUMP(ON);
                    flag_pump = 1;
                    flag_water_tank = 0;
                    flag_adc_pump = 0;
                    time_wait = 500;
                    worker_step = 2;
                }
                break;
            
            case 2:
                if(time_wait == 0)
                {
                    time_wait = 500;
                    if(flag_adc_pump == 1 && flag_pump == 1)
                    {
                        flag_adc_pump = 0;
                        switch(water_pump_state)
                        {
                            case 1: //Ë®±Ã³é¿Õ
                                pump_comp_cnt = 0;
                                pump_idle_cnt++;
                                if(pump_idle_cnt >= 6) //3s
                                {
                                    pump_idle_cnt = 0;
                                    SWITCH_PUMP(OFF);
                                    flag_pump = 0;
                                    flag_water_tank = 0;
                                    nexttime = time_pump; 
                                    SWITCH_SOLEN(ON); //Next,open the solenoid valve to draw water from the tank.
                                    worker_step = 3;
                                    time_wait = 500;
                                }
                                break;
                                
                            case 4: //Ë®±Ã¶ÂËÀ
                                pump_idle_cnt = 0;
                                pump_comp_cnt++;
                                if(pump_comp_cnt >= 10)
                                {
                                    pump_comp_cnt = 0;
                                    SWITCH_PUMP(OFF);
                                    SWITCH_SOLEN(OFF);
                                    time_pump = 0;
                                    flag_pump = 0;
                                    flag_water_tank = 0;
                                    flag_COMP_TYPE = 1;
                                    time_pump_water_again = 0;
                                    first_water_pump = 0;
                                    worker_step = 0;
                                }
                                break;
                                
                            default:
                                pump_idle_cnt = 0;
                                pump_comp_cnt = 0;
                                break;
                        }
                    }
                }
                if(time_pump == 0 || flag_level == 1)
                {
                    SWITCH_PUMP(OFF);
                    SWITCH_SOLEN(OFF);
                    flag_pump = 0;
                    flag_water_tank = 0;
                    time_wait = 0;
                    time_pump = 0;
                    worker_step = 0;
                    if(first_water_pump)
                    {
                        time_pump_water_again = TIME_PUMP_WATER_AGAIN;
                    }
                }
                break;
                
            case 3:
                if(time_wait == 0)
                {
                    SWITCH_PUMP(ON);
                    flag_water_tank = 1;
                    flag_pump = 1;
                    flag_adc_pump = 0;
                    time_pump = nexttime + 4000; //Add 4 seconds,pump idle time
                    worker_step = 4;
                    pump_comp_cnt = 0;
                    pump_idle_cnt = 0;
                    time_wait = 500;
                }
                if(time_pump == 0 || flag_level == 1)
                {
                    SWITCH_PUMP(OFF);
                    flag_adc_pump = 0;
                    flag_pump = 0;
                    flag_water_tank = 0;
                    time_pump = 0;
                    time_wait = 0;
                    SWITCH_SOLEN(OFF);
                    worker_step = 0;
                    if(first_water_pump)
                    {
                        time_pump_water_again = TIME_PUMP_WATER_AGAIN;
                    }
                }
                break;
                
            case 4:
                if(time_wait == 0)
                {
                    time_wait = 500;
                    if(flag_adc_pump == 1 && flag_pump == 1)
                    {
                        flag_adc_pump = 0;
                        switch(water_pump_state)
                        {
                            case 1:
                                pump_comp_cnt = 0;
                                pump_idle_cnt++;
                                if(pump_idle_cnt >= 6) //3s
                                {
                                    pump_idle_cnt = 0;
                                    SWITCH_PUMP(OFF);
                                    flag_pump = 0;
                                    flag_water_tank = 0;
                                    SWITCH_SOLEN(OFF); 
                                    flag_hydropenia = 1; //È±Ë®
                                    first_water_pump = 0;
                                    worker_step = 0;
                                }
                                break;
                            case 4: //Ë®±Ã¶ÂËÀ
                                pump_idle_cnt = 0;
                                pump_comp_cnt++;
                                if(pump_comp_cnt >= 10)
                                {
                                    pump_comp_cnt = 0;
                                    SWITCH_PUMP(OFF);
                                    flag_pump = 0;
                                    flag_water_tank = 0;
                                    flag_COMP_TYPE = 1;
                                    worker_step = 0;
                                    time_pump_water_again = 0;
                                    first_water_pump = 0;
                                }
                                break;
                                
                            default:
                                pump_idle_cnt = 0;
                                pump_comp_cnt = 0;
                                break;
                        }
                    }
                }
                if(time_pump == 0 || flag_level == 1)
                {
                    SWITCH_PUMP(OFF);
                    flag_pump = 0;
                    flag_water_tank = 0;
                    time_pump = 0;
                    time_wait = 0;
                    SWITCH_SOLEN(OFF);
                    worker_step = 0;
                    if(first_water_pump)
                    {
                        time_pump_water_again = TIME_PUMP_WATER_AGAIN;
                    }
                }
                break;
                       
            default:
                break;
        }
    }
}

void error_deal(void)
{
    if(flag_fan_sw == 1)
    {
        if(Error_Stu.err_byte != 0)
        {
            flag_fan_sw = 0;
            flag_fan_worker = 0;
            worker_step = 0;
            SWITCH_PUMP(OFF);
            flag_pump = 0;
            flag_water_tank = 0;
            pump_comp_cnt = 0;
            pump_idle_cnt = 0;
            time_wait = 0;
            SWITCH_SOLEN(OFF);
            Fan_Off();
            if(Error_Stu.err_cover == 1)
            {
                flag_water_last = 1;
                time_pump_water_again_last = time_pump_water_again;
            }
        }
        //if(first_water_pump == 1 && fan_rpm < 1500) Error_Stu.err_rpm = 1;
    }
    if(PowerIN_state < 2)
    {
        Fan_Off();
        first_water_pump = 0;
        SWITCH_PUMP(OFF);
        flag_pump = 0;
        flag_water_tank = 0;
        time_wait = 0;
        SWITCH_SOLEN(OFF);
        flag_fan_sw = 0;
        worker_step = 0;
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
            CH224A_CFG2(1);
            CH224A_CFG3(1); //9V
            typec_sel = TYPEC_9V;
            break;
        
        case TYPEC_12V:
            CH224A_CFG2(1);
            CH224A_CFG3(0); //12V
            typec_sel = TYPEC_12V;
            break;
        
        case TYPEC_20V:
            CH224A_CFG2(0);
            CH224A_CFG3(0); //20V
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
