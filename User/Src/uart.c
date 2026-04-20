#include "uart.h"


//PA9  -> TX
//PA10 -> RX
void Init_Uart1(void)
{
    usart_config_t usart_config_struct = {0};

	// Clock Config	
	__RCU_APB2_CLK_ENABLE(RCU_APB2_PERI_USART1);

	// GPIO MF Config
    gpio_mf_config(GPIOA, GPIO_PIN_9, GPIO_MF_SEL1);   
    gpio_mf_config(GPIOA, GPIO_PIN_10, GPIO_MF_SEL1);
        
	gpio_mode_set(GPIOA, GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_MF_PP(GPIO_SPEED_MEDIUM));
	
    // USART Config	
    __USART_DEF_INIT(USART1);
    usart_config_struct.baud_rate = 9600;
    usart_config_struct.data_width = USART_DATA_WIDTH_8;
    usart_config_struct.stop_bits = USART_STOP_BIT_1;
    usart_config_struct.parity = USART_PARITY_NO;
    usart_config_struct.flow_control = USART_FLOW_CONTROL_NONE;
    usart_config_struct.usart_mode = USART_MODE_RX | USART_MODE_TX;
    usart_init(USART1, &usart_config_struct);

    __USART_ENABLE(USART1);	
}

int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    __USART_DATA_SEND(USART1, (uint8_t)ch);
    while(__USART_FLAG_STATUS_GET(USART1, TXE) == RESET);
    return ch;
}

