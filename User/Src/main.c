#include "main.h"
#include "sys.h"
#include "timer.h"
#include "gpio.h"
#include "uart.h"

extern uint32_t SystemCoreClock;
static volatile uint32_t timing_delay;

void delay(uint32_t value);

//static void set_sys_clock(void);

/**
 * @fn int main(void)
 * @brief  Main program.   MCU clock setting is  configured  through SystemInit()
 *          in startup file (startup_cs32f0xx.s) before to enter to application main.
 * @param  None
 * @return None
 */

int main(void)
{
    Init_system_clock();
    Init_Gpio();
    Init_Timer6();
    //Init_Uart1();
    //Init_Timer3();
    while (1)
    {
        pump_user();
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
