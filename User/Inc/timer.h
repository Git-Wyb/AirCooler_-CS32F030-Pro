#ifndef __TIMER_H__
#define __TIMER_H__

#include "sys.h"
#include "gpio.h"

#define D_PWM_MAX  320 //50% //192 //70%  //192//70%   //0  //100%
#define D_PWM_MID  384 //40% //352 //45%  //288//55%   //160  //75%
#define D_PWM_LOW  448 //30% //409 //30%  //384//40%   //320  //50%

#define COEFFICIENT 10000

extern u32 fan_rpm;

void Init_Timer6(void);
void Fan_Open(void);
void Fan_Off(void);
void Init_Timer1(u16 pwm);
void Fan_Pwm(u16 pwm);
void Init_Timer3(void);
void wait_ms(u16 ms);
void Fan_Disbale(void);

#endif


/* 兄弟: LOW 6.5, MID 9, MAX 10.7
风机进风口遮挡一半
PWM    m/s
420    6.0
320    8.6
240    9.8

390    6.8
290    9.2
210    10.5

384    6.9
288    9.2
192    10.8

风机进风口无遮挡
409    8.4
352    10.5
192    14.3

风机进风口无遮挡，把风速调整跟兄弟风机一样
320    11.2
384    9.1
448    7.0
*/

