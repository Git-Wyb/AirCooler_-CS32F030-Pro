#ifndef __ADC_H__
#define __ADC_H__

#include "sys.h"

typedef enum{
    WaterPump_Index = 0,
    SolValue_Index,
    PowerIN_Index,
    Power24V_Index,
    RefintIN_Index
}index_enum;

void adc_config(void);
static void adc_dma_config(void);
void Init_ADC1(void);
u16 bubble_sort_average_value(u16 *buff,u16 len);
uint16_t Read_VREFINT_CAL(void);

#endif
