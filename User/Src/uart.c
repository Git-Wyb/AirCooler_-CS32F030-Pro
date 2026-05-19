#include "uart.h"

u8 rx_buf[10] = {0};
u8 rx_index = 0;

//PA9  -> TX
//PA10 -> RX
void Init_Uart1(void)
{
    usart_config_t usart_config_struct = {0};
    nvic_config_t nvic_config_struct;
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
    
     /* Enable the USART Interrupt */
    nvic_config_struct.IRQn = IRQn_USART1;
    nvic_config_struct.priority = 4;
    nvic_config_struct.enable_flag = ENABLE;
    nvic_init(&nvic_config_struct);
    __USART_INTR_ENABLE(USART1, RXNE); // Enable the USART Receive interrupt
    
    __USART_ENABLE(USART1); // Enable USART
}

u8 rxdata = 0;
void USART1_IRQHandler(void)
{   /*
    if (__USART_FLAG_STATUS_GET(USART1, TXE) == SET)
    {   /* When key Pressed send the command then send the data 
        if(tx_index != buf_len-1)
        {
            __USART_DATA_SEND(USART1, tx_buf[tx_index++]);
        }
        else if (tx_index == buf_len-1)
        {
            __USART_DATA_SEND(USART1, CMD_END);
            tx_index = 0x00;
            /* Disable the USART transmit data register empty interrupt 
            __USART_INTR_DISABLE(USART1, TXE);
        }
    }*/

    /* USART Receiver*/
    if (__USART_FLAG_STATUS_GET(USART1, RXNE) == SET)
    {
        rxdata = (u8)__USART_DATA_RECV(USART1);
        if(rxdata == '(' || flag_rx_head == 1)
        {
            flag_rx_head = 1;
            rx_buf[rx_index++] = rxdata;
            if(rx_index > 9 || rx_buf[rx_index-1] == ')') //"(R)"
            {
                //__USART_INTR_DISABLE(USART1, RXNE);
                if(rx_buf[1] == 'R' && rx_buf[2] == ')')
                {
                    flag_rx_done = 1;
                }
                rx_index = 0;
                rx_buf[2] = 0;
                rx_buf[0] = 0;
                flag_rx_head = 0;
            }
        }
    }
}

int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    __USART_DATA_SEND(USART1, (uint8_t)ch);
    while(__USART_FLAG_STATUS_GET(USART1, TXE) == RESET);
    return ch;
}

