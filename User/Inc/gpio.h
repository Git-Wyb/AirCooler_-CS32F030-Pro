#ifndef __GPIO_H__
#define __GPIO_H__

#include "cs32f0xx.h"
#include "Sys.h"

#define ON  1
#define OFF 0

#define GPIOx_IN(GPIOx,PINx)    (u8)__GPIO_INPUT_PIN_GET(GPIOx, PINx)//(u8){(GPIOx->IDR & PINx) ? 1 : 0}
#define GPIOx_OUT(GPIOx,PINx,y) {if(y){__GPIO_PIN_SET(GPIOx, PINx);}else{__GPIO_PIN_RESET(GPIOx, PINx);}}//{if(y){GPIOx->BSRR = PINx;}else{GPIOx->BRR = PINx;}}
#define FAN_GPIOx_OUT(GPIOx,PINx,y) {if(y){__GPIO_PIN_RESET(GPIOx, PINx);}else{__GPIO_PIN_SET(GPIOx, PINx);}}
//INPUT
#define KEY_POWER           GPIOx_IN(GPIOA,GPIO_PIN_0)  
#define KEY_FAN             GPIOx_IN(GPIOA,GPIO_PIN_1)
#define KEY_PUMP            GPIOx_IN(GPIOA,GPIO_PIN_2)
#define WATER_FLOW_DETEC    GPIOx_IN(GPIOA,GPIO_PIN_3)
#define WATER_LEVEL_DETEC   GPIOx_IN(GPIOA,GPIO_PIN_4)
#define COVER_DETEC         GPIOx_IN(GPIOA,GPIO_PIN_5)
#define TEST_PIN            GPIOx_IN(GPIOF,GPIO_PIN_7)

//OUTPUT
#define LED_WATER(x)        GPIOx_OUT(GPIOB,GPIO_PIN_15,x)
#define LED_FAN_MAX(x)      GPIOx_OUT(GPIOB,GPIO_PIN_14,x)
#define LED_FAN_MID(x)      GPIOx_OUT(GPIOB,GPIO_PIN_13,x)
#define LED_FAN_LOW(x)      GPIOx_OUT(GPIOB,GPIO_PIN_12,x)
#define LED_ABNORMAL(x)     GPIOx_OUT(GPIOB,GPIO_PIN_11,x)
#define LED_POWER(x)        GPIOx_OUT(GPIOB,GPIO_PIN_10,x)    
#define SWITCH_PUMP(x)      GPIOx_OUT(GPIOC,GPIO_PIN_13,x)
#define SWITCH_FAN(x)       FAN_GPIOx_OUT(GPIOA,GPIO_PIN_11,x)


void Init_Gpio(void);
void key_switch_fan(void);
void key_fan_detec(void);
void key_pump_detec(void);
void water_level_detec(void);
void cover_detec(void);
void input_detection(void);
void led_fan(u16 grade);
void pump_user(void);

#endif
