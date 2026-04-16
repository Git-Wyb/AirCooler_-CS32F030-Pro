#include "adc.h"



void Init_Adc(void)
{
    adc_config_t   adc_config_struct;
    
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOA);
    __RCU_APB2_CLK_ENABLE(RCU_APB2_PERI_ADC);   
    
    //Configure ADC CH6 GPIO as analog input.
    gpio_mode_set(GPIOA, GPIO_PIN_6, GPIO_MODE_ANALOG);
    
    adc_def_init(ADC1);   
    adc_config_struct_init(&adc_config_struct);  

    // Configure the ADC1 in continuous mode 
    adc_config_struct.adc_resolution = ADC_CONV_RES_12BITS;
    adc_config_struct.continuous_mode = ENABLE; 
    adc_config_struct.trigger_mode = ADC_TRIG_MODE_NONE;
    adc_config_struct.data_align = ADC_DATA_ALIGN_RIGHT;
    adc_config_struct.scan_direction = ADC_SCAN_DIR_UPWARD;
    adc_init(ADC1, &adc_config_struct); 

    // Set the ADC1 CH6 with 239.5 Cycles
    adc_channel_config(ADC1, ADC_CONV_CHANNEL_6 , ADC_SAMPLE_TIMES_239_5); 
    adc_calibration_value_get(ADC1);    // ADC Calibration.  
    __ADC_ENABLE(ADC1);                     // Enable the ADC.    
    
    while(!__ADC_FLAG_STATUS_GET(ADC1, EOI)); // Wait the EOI flag.    
    adc_conversion_start(ADC1);         //ADC1 regular Software Start Conv. 
}

u8 get_adc_value(u8 *pbuf,u8 length)
{
    u8 i = 0;
    
    for(i=0; i<length; i++)
    {
        while(__ADC_FLAG_STATUS_GET(ADC1, EOC) == RESET); // Check EOC flag
        pbuf[i] = __ADC_CONV_VALUE_GET(ADC1);
    }
    return 1;
}
