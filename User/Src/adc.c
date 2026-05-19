#include "adc.h"

#define ADC1_OUTDAT_REG_ADDRESS    0x40012440
static volatile uint16_t adc_conv[6];

uint16_t VREFINT_CAL = 0;
// 定义校准值存储地址
#define VREFINT_CAL_ADDR  ((uint16_t *)(0x1FFFF7BA))
uint16_t Read_VREFINT_CAL(void)
{
    return *VREFINT_CAL_ADDR;  // 直接读取寄存器值
}

/* ADC 
Water_Pump:     PA6 -> CH6 //水泵检测
Solenoid_Value: PA7 -> CH7 //电磁阀检测
Power_IN:       PB0 -> CH8 //输入电源检测
Power_24V:      PB1 -> CH9 //DC24检测
Refint_IN:      CH17 //内部参考电压
*/
void Init_ADC1(void)
{
    VREFINT_CAL = Read_VREFINT_CAL();
    
    adc_dma_config();
    adc_config();
}

void adc_config(void)
{
    adc_config_t   adc_config_struct;

    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOA|RCU_AHB_PERI_GPIOB);
    __RCU_APB2_CLK_ENABLE(RCU_APB2_PERI_ADC);
    
    //GPIO Config
    gpio_mode_set(GPIOA, GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_ANALOG); 
    gpio_mode_set(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_MODE_ANALOG);

    //ADC1 Config 
    adc_def_init(ADC1);   
    adc_config_struct_init(&adc_config_struct);  // Initialize ADC structure 

    //Configure the ADC1 in continuous mode 
    adc_config_struct.adc_resolution = ADC_CONV_RES_12BITS;
    adc_config_struct.continuous_mode = ENABLE; 
    adc_config_struct.trigger_mode = ADC_TRIG_MODE_NONE;
    adc_config_struct.data_align = ADC_DATA_ALIGN_RIGHT;
    adc_config_struct.scan_direction = ADC_SCAN_DIR_UPWARD;
    adc_init(ADC1, &adc_config_struct); 

    adc_channel_config(ADC1, ADC_CONV_CHANNEL_6, ADC_SAMPLE_TIMES_239_5);  
    adc_channel_config(ADC1, ADC_CONV_CHANNEL_7, ADC_SAMPLE_TIMES_239_5);  
    adc_channel_config(ADC1, ADC_CONV_CHANNEL_8, ADC_SAMPLE_TIMES_239_5);
    adc_channel_config(ADC1, ADC_CONV_CHANNEL_9, ADC_SAMPLE_TIMES_239_5);
    adc_channel_config(ADC1, ADC_CONV_CHANNEL_VREF, ADC_SAMPLE_TIMES_239_5);
    
    __ADC_FUNC_ENABLE(ADC1,VREFINT); //启用 VREFINT 通道

    adc_calibration_value_get(ADC1);                //ADC Calibration
    adc_dma_mode_set(ADC1, ADC_DMA_MODE_CIRCULAR);  // ADC DMA request in circular mode.
    
    __DMA_ENABLE(DMA1_CHANNEL1);        //DMA1 Channel1 enable

    // Enable ADC_DMA 
    __ADC_DMA_ENABLE(ADC1); 
    __ADC_ENABLE(ADC1);                             // Enable the ADC.    

    while(!__ADC_FLAG_STATUS_GET(ADC1, EOI));   
    adc_conversion_start(ADC1);                     // ADC1 regular Software Start Conv.
}

static void adc_dma_config(void)
{
    dma_config_t  dma_configStruct;
//    nvic_config_t nvic_config_struct;
    //Enable DMA1 clock  
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_DMA);
    
    // DMA1 Channel 1 Config
    dma_def_init(DMA1_CHANNEL1);
    dma_configStruct.peri_base_addr = (uint32_t)ADC1_OUTDAT_REG_ADDRESS;
    dma_configStruct.mem_base_addr = (uint32_t)adc_conv;
    dma_configStruct.transfer_direct = DMA_TRANS_DIR_FROM_PERI;
    dma_configStruct.buf_size = 5;
    dma_configStruct.peri_inc_flag = DMA_PERI_INC_DISABLE;
    dma_configStruct.mem_inc_flag = DMA_MEM_INC_ENABLE;
    dma_configStruct.peri_data_width = DMA_PERI_DATA_WIDTH_HALFWORD;
    dma_configStruct.mem_data_width = DMA_MEM_DATA_WIDTH_HALFWORD;
    dma_configStruct.operate_mode = DMA_OPERATE_MODE_CIRCULAR;
    dma_configStruct.priority_level = DMA_CHANNEL_PRIORITY_HIGH;
    dma_configStruct.m2m_flag = DMA_M2M_MODE_DISABLE;
    dma_init(DMA1_CHANNEL1, &dma_configStruct);
    
     /* Enable and set DMA1_CHANNEL1 Interrupt */
    //nvic_config_struct.IRQn = IRQn_DMA1_CHANNEL1;
    //nvic_config_struct.priority = 1;
    //nvic_config_struct.enable_flag = ENABLE;
    //nvic_init(&nvic_config_struct);
}

u8 vy = 0;
u8 vx = 0;
void DMA1_Channel1_IRQHandler(void)
{
    if(__DMA_FLAG_STATUS_GET(CMP1) == SET)
    {
        __DMA_FLAG_CLEAR(DMA1_FLAG_CMP1);
        for(vx = 0; vx < 5; vx++)
        {
            Adc_Value_Buff[vx][vy] = adc_conv[vx];
        }
        vy++;
        if(vy >= 7)
        {
            vy = 0;
            flag_adc_ok = 1;
        }
    }
}

void adc_dma_value(void)
{
    //while((__DMA_FLAG_STATUS_GET(CMP1)) == RESET );     // wait DMA1 CMP1 flag.
    //__DMA_FLAG_CLEAR(DMA1_FLAG_CMP1);                   // Clear DMA CMP1 flag.
    if(__DMA_FLAG_STATUS_GET(CMP1) == SET)
    {
        __DMA_FLAG_CLEAR(DMA1_FLAG_CMP1);
        
        for(vx = 0; vx < 5; vx++)
        {
            Adc_Value_Buff[vx][vy] = adc_conv[vx];
        }
        vy++;
        if(vy >= 7)
        {
            vy = 0;
            flag_adc_ok = 1;
        }
    }
}

/* ADC 
Water_Pump:     PA6 -> CH6 //水泵检测
Solenoid_Value: PA7 -> CH7 //电磁阀检测
Power_IN:       PB0 -> CH8 //输入电源检测
Power_24V:      PB1 -> CH9 //DC24检测
Refint_IN:      CH17 //内部参考电压
*/
void Init_Adc(void)
{
    adc_config_t   adc_config_struct;
    
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOA);
    __RCU_APB2_CLK_ENABLE(RCU_APB2_PERI_ADC);   
    
    //Configure ADC CH6 GPIO as analog input.
    gpio_mode_set(GPIOB, GPIO_PIN_1, GPIO_MODE_ANALOG);
    
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
    adc_channel_config(ADC1, ADC_CONV_CHANNEL_17 , ADC_SAMPLE_TIMES_239_5); 
    
    __ADC_FUNC_ENABLE(ADC1,VREFINT); //启用 VREFINT 通道 1000
    
    adc_calibration_value_get(ADC1);    // ADC Calibration.  
    __ADC_ENABLE(ADC1);                     // Enable the ADC.    
    
    while(!__ADC_FLAG_STATUS_GET(ADC1, EOI)); // Wait the EOI flag.    
    adc_conversion_start(ADC1);         //ADC1 regular Software Start Conv. 
}

u8 adc_value(u8 *pbuf,u8 length)
{
    u8 i = 0;
    
    for(i=0; i<length; i++)
    {
        while(__ADC_FLAG_STATUS_GET(ADC1, EOC) == RESET); // Check EOC flag
        pbuf[i] = __ADC_CONV_VALUE_GET(ADC1);
    }
    return 1;
}
