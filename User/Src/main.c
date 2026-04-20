#include "main.h"
#include "sys.h"
#include "timer.h"
#include "gpio.h"
#include "uart.h"
#include "iic.h"

extern uint32_t SystemCoreClock;
static volatile uint32_t timing_delay;

void delay(uint32_t value);
void Send_Logo(void);
//static void set_sys_clock(void);

/**
 * @fn int main(void)
 * @brief  Main program.   MCU clock setting is  configured  through SystemInit()
 *          in startup file (startup_cs32f0xx.s) before to enter to application main.
 * @param  None
 * @return None
 */
u8 readreg = 0;
u8 setvol = 0;
u8 ret = 0xff;
int main(void)
{
    //Init_FWDT();
    Init_system_clock();
    Init_Gpio();
    Init_Timer6();
    Init_Uart1();
    Init_Timer3();
    
    while (1)
    {
        FWDT_Clear();
        if(time_run == 0) //抽水结束，吹10分钟之后再次抽水
        {
            //user_switch_pump(ON,20000);
        }
        Send_Logo();
    }
}

void Send_Logo(void)
{
    if(flag_fan_sw && time_ms == 0)
    {
        time_ms = 1000;
        printf("FAN RPM = %d\r\n",fan_rpm);
    }
}

/**
 * @fn void Delay(volatile uint32_t value)
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in milliseconds.
 * @return None
 */
void delay(volatile uint32_t value)
{
    timing_delay = value;

    while (timing_delay != 0)
        ;
}

/**
 * @fn void TimingDelay_Decrement(void)
 * @brief  Decrements the timing_delay variable.
 * @param  None
 * @return None
 */
void timing_delay_decrement(void)
{
    if (timing_delay != 0x00)
    {
        timing_delay--;
    }
}

/**
 * @}
 */

/**
 * @}
 */
