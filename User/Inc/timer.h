#ifndef __TIMER_H__
#define __TIMER_H__

#include "sys.h"
#include "gpio.h"

#define D_PWM_MAX 192//70%   //0  //100%
#define D_PWM_MID 288//55%   //160  //75%
#define D_PWM_LOW 384//40%   //320  //50%

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


/* ÐÖµÜ: LOW 6.5, MID 9, MAX 10.7
420    6.0
320    8.6
240    9.8

390    6.8
290    9.2
210    10.5

384    6.9
288    9.2
192    10.8
*/

