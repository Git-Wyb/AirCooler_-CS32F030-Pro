#include "gpio.h"
#include "timer.h"
#include "uart.h"

void Init_Gpio(void)
{
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOA); // Enable the GPIOA Clock
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOB); // Enable the GPIOB Clock
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOC); // Enable the GPIOC Clock
    
    gpio_mode_set(GPIOA, GPIO_PIN_0, GPIO_MODE_IN_PU);
    gpio_mode_set(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_PU);
    gpio_mode_set(GPIOA, GPIO_PIN_2, GPIO_MODE_IN_PU);
    gpio_mode_set(GPIOA, GPIO_PIN_4, GPIO_MODE_IN_PU);
    gpio_mode_set(GPIOA, GPIO_PIN_5, GPIO_MODE_IN_PU);
    gpio_mode_set(GPIOF, GPIO_PIN_7, GPIO_MODE_IN_PU); //test pin
    
    gpio_mode_set(GPIOA, GPIO_PIN_11, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    gpio_mode_set(GPIOB, GPIO_PIN_10, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    gpio_mode_set(GPIOB, GPIO_PIN_11, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    gpio_mode_set(GPIOB, GPIO_PIN_12, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    gpio_mode_set(GPIOB, GPIO_PIN_13, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    gpio_mode_set(GPIOB, GPIO_PIN_14, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    gpio_mode_set(GPIOB, GPIO_PIN_15, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    
    gpio_mode_set(GPIOC, GPIO_PIN_13, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    
    LED_WATER(OFF);
    LED_FAN_MAX(OFF);
    LED_FAN_MID(OFF);
    LED_FAN_LOW(OFF);
    LED_ABNORMAL(OFF);
    SWITCH_PUMP(OFF);
    SWITCH_FAN(OFF);
    
    LED_POWER(ON);
}

void led_fan(u16 grade)
{
    switch(grade)
    {
        case D_PWM_LOW:
            LED_FAN_LOW(ON);
            LED_FAN_MID(OFF);
            LED_FAN_MAX(OFF);
            break;
        case D_PWM_MID:
            LED_FAN_LOW(OFF);
            LED_FAN_MID(ON);
            LED_FAN_MAX(OFF);
            break;
        case D_PWM_MAX:
            LED_FAN_LOW(OFF);
            LED_FAN_MID(OFF);
            LED_FAN_MAX(ON);
            break;
        default:
            LED_FAN_LOW(ON);
            LED_FAN_MID(OFF);
            LED_FAN_MAX(OFF);
            break;
    }
}

void input_detection(void)
{
    key_switch_fan();
    key_fan_detec();
    key_pump_detec();
    water_level_detec();
    cover_detec();
}

u8 key_power_ms = 0;
void key_switch_fan(void)
{
    if(key_power_sta == 0 && KEY_POWER == 0)
    {
        key_power_ms++;
        if(key_power_ms > 50)
        {
            key_power_ms = 0;
            if(KEY_POWER == 0)
            {
                key_power_sta = 1;
                if(flag_fan_sw == 0)
                {
                    Fan_Open();
                }
                else
                {
                    Fan_Off();
                }
            }
        }
    }
    else
    {
        key_power_ms = 0;
        if(KEY_POWER == 1) key_power_sta = 0;
    }
}

u8 key_fan_ms = 0;
void key_fan_detec(void)
{
    if(key_fan_sta == 0 && KEY_FAN == 0 && flag_fan_sw == 1)
    {
        key_fan_ms++;
        if(key_fan_ms > 50)
        {
            key_fan_ms = 0;
            if(KEY_FAN == 0)
            {
                key_fan_sta = 1;
                fan_speed_set++;
                if(fan_speed_set > 2) fan_speed_set = 0;
                switch(fan_speed_set)
                {
                    case 0:
                        fan_pwm_set = D_PWM_LOW;
                        Fan_Pwm(fan_pwm_set);
                        led_fan(fan_pwm_set);
                        break;
                    case 1:
                        fan_pwm_set = D_PWM_MID;
                        Fan_Pwm(fan_pwm_set);
                        led_fan(fan_pwm_set);
                        break;
                    case 2:
                        fan_pwm_set = D_PWM_MAX;
                        Fan_Pwm(fan_pwm_set);
                        led_fan(fan_pwm_set);
                        break;
                    default:
                        fan_pwm_set = D_PWM_LOW;
                        Fan_Pwm(fan_pwm_set);
                        led_fan(fan_pwm_set);
                        break;
                }
            }
        }
    }
    else
    {
        key_fan_ms = 0;
        if(KEY_FAN == 1) key_fan_sta = 0;
    }
}

u8 key_pump_ms = 0;
void key_pump_detec(void)
{
    if(key_pump_sta == 0 && KEY_PUMP == 0)
    {
        key_pump_ms++;
        if(key_pump_ms > 50)
        {
            key_pump_ms = 0;
            if(KEY_PUMP == 0)
            {
                key_pump_sta = 1;
                if(flag_pump == 0)
                {
                    user_switch_pump(ON,20000);
                }
                else
                {
                    user_switch_pump(OFF,0);
                }
            }
        }
    }
    else
    {
        key_pump_ms = 0;
        if(KEY_PUMP == 1) key_pump_sta = 0;
    }
}

void user_switch_pump(u8 onoff,u32 utime)
{
    if(onoff == OFF)
    {
        flag_pump = 0;
        time_pump = 0;
        LED_WATER(OFF);
        SWITCH_PUMP(OFF);
    }
    else
    {
        flag_pump = 1;
        time_pump = utime;
        LED_WATER(ON);
        SWITCH_PUMP(ON);
        time_run = 600000 + utime;
    }
}

void pump_wait_off(void)
{
    if(flag_pump == 1 && time_pump == 0)
    {
        user_switch_pump(OFF,0);
    }
}

u8 water_level_ms = 0;
void water_level_detec(void)
{
    if(WATER_LEVEL_DETEC == 0 && flag_level == 0)
    {
        water_level_ms++;
        if(water_level_ms > 50)
        {
            water_level_ms = 0;
            if(WATER_LEVEL_DETEC == 0)
            {
                flag_level = 1;
                LED_WATER(ON);
            }
        }
    }
    else
    {
        if(WATER_LEVEL_DETEC == 1 && flag_level == 1)
        {
            water_level_ms++;
            if(water_level_ms > 50)
            {
                water_level_ms = 0;
                if(WATER_LEVEL_DETEC == 1)
                {
                    flag_level = 0;
                    LED_WATER(OFF);
                }
            }
        }
    }
}

u8 cover_ms = 0;
void cover_detec(void)
{
    if(COVER_DETEC == 0 && flag_cover == 0)
    {
        cover_ms++;
        if(cover_ms > 50)
        {
            cover_ms = 0;
            if(COVER_DETEC == 0)
            {
                flag_cover = 1;
                LED_ABNORMAL(ON);
            }
        }
    }
    else
    {
        if(COVER_DETEC == 1 && flag_cover == 1)
        {
            cover_ms++;
            if(cover_ms > 50)
            {
                cover_ms = 0;
                if(COVER_DETEC == 1)
                {
                    flag_cover = 0;
                    LED_ABNORMAL(OFF);
                }
            }
        }
    }
}

