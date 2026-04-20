#include "timer.h"
#include "sys.h"
#include "gpio.h"
#include "uart.h"

u16 read_value1 = 0;
u16 read_value2 = 0;
u16 capture = 0;
u16 t_cycle1 = 0;
u16 t_cycle2 = 0;
u8 capture_flag = 0;

u32 fan_rpm = 0;

void Init_Timer6(void)
{
    tim_base_t timer_config_struct;
    nvic_config_t nvic_config_struct;

    __RCU_APB1_CLK_ENABLE(RCU_APB1_PERI_TIM6); // TIM6 clock enable
    
    // Time base configuration
    timer_config_struct.period = 1000 - 1; //ARR自动重载值
    timer_config_struct.predivider = 0;
    timer_config_struct.clk_division = 0;
    timer_config_struct.count_mode = TIM_COUNT_PATTERN_UP;
    tim_base_init(TIM6, &timer_config_struct);
    //f = fCK_PSC / (PSC[15:0] + 1) = 16MHz / (15+1) = 1MHz.
    tim_prescaler_set(TIM6, 15, TIM_PDIV_MODE_IMMEDIATE); // Prescaler configuration,
    
    nvic_config_struct.IRQn = IRQn_TIM6;
    nvic_config_struct.priority = 4;
    nvic_config_struct.enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);
    
    __TIM_INTR_ENABLE(TIM6,TIM_INTR_UPDATE);
    __TIM_ENABLE(TIM6);
}

void TIM6_IRQHandler(void)
{
    if(__TIM_FLAG_STATUS_GET(TIM6,UPDATE) != RESET)
    {
        __TIM_FLAG_CLEAR(TIM6,TIM_FLAG_UPDATE);
        
        if(time_ms) time_ms--;
        if(time_pump) time_pump--;
        if(time_run)  time_run--;
        input_detection();
        pump_wait_off();
    }
}

//FAN PWM TIM1_CH4
void Init_Timer1(u16 pwm)
{
    tim_base_t timer_config_struct;
    tim_choc_t timer_compare_struct;

    __RCU_APB2_CLK_ENABLE(RCU_APB2_PERI_TIM1); // TIM1 clock enable  (PCLK=16MHZ)
    
    gpio_mf_config(GPIOA, GPIO_PIN_11, GPIO_MF_SEL2);
    gpio_mode_set(GPIOA, GPIO_PIN_11, GPIO_MODE_MF_PP_PU(GPIO_SPEED_HIGH));
    
    // Time Base configuration
    timer_config_struct.period = 640;  //pwm_f=25KHz / clk=16MHz = 640
    timer_config_struct.predivider = 0;
    timer_config_struct.count_mode = TIM_COUNT_PATTERN_UP;
    timer_config_struct.clk_division = 0;
    timer_config_struct.repeate_count = 0;
    tim_base_init(TIM1, &timer_config_struct);
    
    // Channel 4 Configuration in PWM mode.
    timer_compare_struct.mode = TIM_CHxOCMSEL_PWM2;
    timer_compare_struct.output_state = TIM_CHx_OUTPUT_ENABLE;
    timer_compare_struct.output_state_n = TIM_CHxNCCEN_ENABLE;
    timer_compare_struct.polarity = TIM_CHxCCP_POLARITY_LOW;
    timer_compare_struct.polarity_n = TIM_CHxNCCP_POLARITY_HIGH;
    timer_compare_struct.idle_state = TIM_IVOx_SET;
    timer_compare_struct.idle_state_n = TIM_IVOx_RESET;
    
    timer_compare_struct.channel = TIM_CHANNEL_4;
    timer_compare_struct.pulse = pwm;
    tim_choc_init(TIM1, &timer_compare_struct);
}

void Fan_Open(void)
{
    Init_Timer1(fan_pwm_set);
    __TIM_ENABLE(TIM1);                 // TIM1 counter enable
    __TIM_FUNC_ENABLE(TIM1, CH_OUTPUT); // TIM1 PWM Output Enable.
    led_fan(fan_pwm_set);
    flag_fan_sw = 1;
    
    read_value1 = 0;
    read_value2 = 0;
    capture = 0;
    t_cycle1 = 0;
    t_cycle2 = 0;
    capture_flag = 0;
    fan_rpm = 0;
}

void Fan_Off(void)
{
    __TIM_FUNC_DISABLE(TIM1, CH_OUTPUT);
    __TIM_DISABLE(TIM1);
    gpio_mode_set(GPIOA, GPIO_PIN_11, GPIO_MODE_OUT_PP(GPIO_SPEED_HIGH));
    SWITCH_FAN(OFF);
    LED_FAN_LOW(OFF);
    LED_FAN_MID(OFF);
    LED_FAN_MAX(OFF);
    flag_fan_sw = 0;
    
    read_value1 = 0;
    read_value2 = 0;
    capture = 0;
    t_cycle1 = 0;
    t_cycle1 = 0;
    capture_flag = 0;
    fan_rpm = 0;
}

void Fan_Pwm(u16 pwm)
{
    TIM1->CHxCCVAL[TIM_CHANNEL_4] = pwm;
}

//fan FG: PB4 -> TIM3_CH1 //PB4 -> Reusability Function 1 TIM3_CH1
void Init_Timer3(void)
{
    tim_chic_t timer_capture_struct;
    nvic_config_t nvic_config_struct;

    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOB);  // GPIOB clock enable
    __RCU_APB1_CLK_ENABLE(RCU_APB1_PERI_TIM3); // TIM3 clock enable

    gpio_mf_config(GPIOB, GPIO_PIN_4, GPIO_MF_SEL1); // Connect TIM pins to MF_SEL1
    gpio_mode_set(GPIOB, GPIO_PIN_4, GPIO_MODE_MF_PP(GPIO_SPEED_HIGH));
    
    //f = fCK_PSC / (PSC[15:0] + 1) = 16MHz / (15+1) = 1MHz.
    tim_prescaler_set(TIM3, 15, TIM_PDIV_MODE_IMMEDIATE); // Prescaler configuration,
    
    timer_capture_struct.channel = TIM_CHANNEL_1;
    timer_capture_struct.polarity = TIM_CHxIC_POLARITY_RISING;
    timer_capture_struct.select = TIM_CHIC_SEL_DIRECT_INTR;
    timer_capture_struct.predivider = TIM_CHIC_PREDIVIDE_DIV1;
    timer_capture_struct.filter = 0xf;

    tim_chic_init(TIM3, &timer_capture_struct);
    __TIM_ENABLE(TIM3);                      // TIM enable counter
    __TIM_INTR_ENABLE(TIM3, TIM_INTR_CH1CC); // Enable the CC1 Interrupt Request

    // Enable the TIM3 Interrupt
    nvic_config_struct.IRQn = IRQn_TIM3;
    nvic_config_struct.priority = 0;
    nvic_config_struct.enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);
}

u8 c_cnt = 0;
void TIM3_IRQHandler(void)
{
    if(__TIM_FLAG_STATUS_GET(TIM3, CH1CC) == SET) 
    {
        __TIM_FLAG_CLEAR(TIM3, TIM_FLAG_CH1CC); //Clear TIM3  interrupt 
        
        if(capture_flag == 0)
        {
            read_value1 = __TIM_CC_VALUE_GET(TIM3, TIM_CHANNEL_1); //Get the Input capture value
            capture_flag = 1;
        }
        else if(capture_flag == 1)
        { 
            capture_flag = 0;            
            read_value2 = __TIM_CC_VALUE_GET(TIM3, TIM_CHANNEL_1);  // Get the Input capture value
      
            //capture computation 
            if (read_value2 > read_value1) 
            {
                capture = (read_value2 - read_value1); 
            }
            else if (read_value2 < read_value1)
            {
                capture = ((0xFFFF - read_value1) + read_value2); 
            }
            else
            {
                capture = 0;
            }
            c_cnt++;
            if(c_cnt == 1)      t_cycle1 = capture * COEFFICIENT / 1000000;//To facilitate the calculation of the magnification = COEFFICIENT
            else if(c_cnt == 2) 
            {
                c_cnt = 0;
                t_cycle2 = capture * COEFFICIENT / 1000000;
                
                //RPM = 60 * (1 / T); T = Two cycles;
                fan_rpm = 60 * COEFFICIENT / (t_cycle1 + t_cycle2);
            }
        }
        
    }
}    

//water flow Hall signal: PA3 -> TIM15_CH2
void Init_Timer15(void)
{
    
}
