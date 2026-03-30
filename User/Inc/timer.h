#ifndef __TIMER_H__
#define __TIMER_H__

#include "sys.h"
#include "gpio.h"

#define D_PWM_MAX 0  //100%
#define D_PWM_MID 160  //75%
#define D_PWM_LOW 320  //50%

extern u32 fan_rpm;
extern u32 c_freq1;
extern u32 c_freq2;

void Init_Timer6(void);
void Fan_Open(void);
void Fan_Off(void);
void Init_Timer1(u16 pwm);
void Fan_Pwm(u16 pwm);
void Init_Timer3(void);

#endif
