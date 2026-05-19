#include "sys.h"
#include "timer.h"

//static u8 fac_us=0;						 
//static u16 fac_ms=0;

u16 fan_pwm_set = D_PWM_MAX;
u8 fan_speed_set = 2;
BaseFlagStu Un_Flag0 = {0};
BaseFlagStu Un_Flag1 = {0};
BaseValueStu Adc_Val = {0};
BaseValueStu CalVal = {0};

u16 time_ms = 0;
u32 time_pump = 0;
u32 time_run = 0;
u32 run_cnt = 0;
u16 Adc_Value_Buff[5][7] = {0};
uint32_t Vref_Cal = 0;
u8 water_pump_state = 0;
u8 Solenoid_state = 0;
u8 PowerIN_state = 0;


void Init_system_clock(void)
{
    rcu_def_init();

    __RCU_FUNC_ENABLE(HRC_CLK);

    if (__RCU_FLAG_STATUS_GET(HRC_STAB) == SET)
    {
        /* Enable Prefetch Buffer and set Flash Latency */
        FLASH->WCR = FMC_WCR_WE | FMC_WCR_WCNT;
        /* HCLK = SYSCLK */
        rcu_hclk_config(RCU_HCLK_CFG_SYSCLK_DIV1);
        rcu_pclk_config(RCU_PCLK_CFG_HCLK_DIV1);
        rcu_pll_config(RCU_PLL_CFG_HRC_DIV2, RCU_CFG_PLLMUF4); //8MHz / 2(DIV2) * 4(PLLMUF4) = 16MHz
        __RCU_FUNC_ENABLE(PLL_CLK);
        while (__RCU_FLAG_STATUS_GET(PLL_STAB) == 0)
        {
            ;
        }
        rcu_sysclk_config(RCU_SYSCLK_SEL_PLL);
        while ((RCU->CFG & (uint32_t)RCU_CFG_SYSSS) != (uint32_t)RCU_CFG_SYSSS_PLL)
        {
            ;
        }
    }

    else
    { /* If HXT fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
    }
    
    rcu_hrc_calibration_adjust(0x12);
}

void Init_FWDT(void) //独立看门狗
{
    __RCU_FUNC_ENABLE(LRC_CLK);
    while (__RCU_FLAG_STATUS_GET(LRC_STAB) == RESET)
        ; // Wait till LRC stabilization
    
    __FWDT_WRITE_ACCESS_ENABLE(); // Enable write access
    __FWDT_PRESCALER_SET(FWDT_PRESCALER_32);
    __FWDT_RELOAD_VALUE_SET(312); //约250ms
    while ((__FWDT_FLAG_STATUS_GET(DRF) & __FWDT_FLAG_STATUS_GET(UVRF)) != RESET)
        ;
    __FWDT_RELOAD_COUNTER();
    __FWDT_ENABLE();
}

void FWDT_Clear(void)
{
    __FWDT_RELOAD_COUNTER();
}

void waiting_ms(u16 ms)
{
    time_ms = ms;
    while(time_ms)
    {
        FWDT_Clear();
    }
}

#if 0
void Init_IWDG(void)
{
    RCC_LSICmd(ENABLE);
    /*!< Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {}
    
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    
    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescaler(IWDG_Prescaler_32);
    
    /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms/IWDG counter clock period??
    f = 1.25k
    */
    IWDG_SetReload(313);    //250ms???
    
    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
}

void R_WDT_Restart(void)
{
    IWDG_ReloadCounter();
}
#endif
