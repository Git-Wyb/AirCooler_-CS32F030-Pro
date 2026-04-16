#include "iic.h"

void delay_us(u32 us)
{
    u32 i = us * 5;
    while(i--);
}

void Init_IIC(void)
{
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOB);
    __RCU_APB1_CLK_ENABLE(RCU_APB1_PERI_I2C1);

    // I2C Pin Config
    gpio_mf_config(GPIOB, GPIO_PIN_8, GPIO_MF_SEL1); // PB8--I2C_SCL
    gpio_mf_config(GPIOB, GPIO_PIN_9, GPIO_MF_SEL1); // PB9--I2C_SDA

    gpio_mode_set(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_MF_OD_PU(GPIO_SPEED_MEDIUM)); // PB8--I2C_SCL; PB9--I2C_SDA
    
    iic_master_config();
}

void iic_master_config(void)
{
    i2c_config_t i2c_config_struct;

    // I2C configuration
    i2c_config_struct.mode = I2C_BUS_MODE_I2C;
    i2c_config_struct.analog_flag = I2C_ANALOG_FILTER_ENABLE;
    i2c_config_struct.digital_value = 0x00;
    i2c_config_struct.slave_addr1 = SLAVE_ADDR;
    i2c_config_struct.ack_flag = I2C_ACK_ENABLE;
    i2c_config_struct.ack_addr = I2C_ACK_ADDR_7BITS;
    i2c_config_struct.tmr_value = I2C_TIMING;
    i2c_init(I2C1, &i2c_config_struct);

    __I2C_ENABLE(I2C1); 
}

u32 iic_master_write(u32 addr,u8 *pbuffer,u8 length)
{
    uint32_t data_num = 0;

    time_ms = I2C_LONG_TIMEOUT;
    while (__I2C_FALG_STATUS_GET(I2C1, BUSY) != RESET)
    {
        if (time_ms == 0)   return 0;
    }
    i2c_slave_address_config(I2C1, addr);
    i2c_request_direction_config(I2C1, I2C_DIRECTION_TX);
    i2c_bytes_number_config(I2C1, length);
    __I2C_START_GENERATE(I2C1);

    while (data_num != length)
    {
        time_ms = I2C_LONG_TIMEOUT;
        while (__I2C_FALG_STATUS_GET(I2C1, TXINT) == RESET)
        {
            if (time_ms == 0) return 0;
        }
        __I2C_DATA_SEND(I2C1, (uint8_t)(pbuffer[data_num]));
        data_num++;
    }

    time_ms = I2C_LONG_TIMEOUT;
    while (__I2C_FALG_STATUS_GET(I2C1, CMP) == RESET)
    {
        if (time_ms == 0)   return 0;
    }

    __I2C_STOP_GENERATE(I2C1);
    time_ms = I2C_LONG_TIMEOUT;
    while (__I2C_FALG_STATUS_GET(I2C1, STOP) == RESET) // Wait until STOPF flag is set
    {
        if (time_ms == 0)   return 0;
    }
    __I2C_FLAG_CLEAR(I2C1, I2C_FLAG_STOP);

    return 1;
}

u32 iic_master_read(u32 addr,u8 *pbuffer,u8 length)
{
    uint32_t data_num;

    time_ms = I2C_LONG_TIMEOUT;
    while (__I2C_FALG_STATUS_GET(I2C1, BUSY) != RESET)
    {
        if (time_ms == 0)   return 0;
    }
    i2c_slave_address_config(I2C1, addr);
    i2c_request_direction_config(I2C1, I2C_DIRECTION_RX);
    /* Update CR2 : set Slave Address , set read request, generate Start and set end mode */
    i2c_bytes_number_config(I2C1, length);
    __I2C_START_GENERATE(I2C1);
    data_num = 0;

    while (data_num != length) // Wait until all data are received
    {
        time_ms = I2C_LONG_TIMEOUT;
        while (__I2C_FALG_STATUS_GET(I2C1, RXNE) == RESET) // Wait until RXNE flag is set
        {
            if (time_ms == 0)   return 0;
        }
        pbuffer[data_num] = __I2C_DATA_RECV(I2C1);
        data_num++;
    }

    time_ms = I2C_LONG_TIMEOUT;
    while (__I2C_FALG_STATUS_GET(I2C1, CMP) == RESET)
    {
        if (time_ms == 0)   return 0;
    }
    __I2C_STOP_GENERATE(I2C1);

    time_ms = I2C_LONG_TIMEOUT;
    while (__I2C_FALG_STATUS_GET(I2C1, STOP) == RESET) // Wait until STOPF flag is set
    {
        if (time_ms == 0)   return 0;
    }
    __I2C_FLAG_CLEAR(I2C1, I2C_FLAG_STOP);
    
    return 1;
}

u8 CH224A_Set_Voltage(u8 vol)
{
    u8 re = 0;
    if(0<vol && vol<=5)         vol = 0; //5V
    else if(5<vol && vol<=9)    vol = 1; //9V
    else if(9<vol && vol<=12)   vol = 2; //12V
    else if(12<vol && vol<=15)  vol = 3; //15V
    else if(15<vol && vol<=20)  vol = 4; //20V
    else if(20<vol && vol<=28)  vol = 5; //28V
    else vol = 0; //5V
    
    re = iic_master_write(0x0A,&vol,1); //write Voltage
    waiting_ms(10);
    //iic_master_read(0x09,&re,1); //read state
    //if(re != 0x1F)  return 0;
    
    return re;
}


void init_iic_m(void)
{
    __RCU_AHB_CLK_ENABLE(RCU_AHB_PERI_GPIOB);

    // I2C Pin Config
    gpio_mode_set(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUT_OD(GPIO_SPEED_MEDIUM)); // PB8--I2C_SCL; PB9--I2C_SDA
    
    IIC_SCL(OFF);
    IIC_SDA(OFF);
}

void Start(void)
 {
    IIC_SCL(ON);
    IIC_SDA(ON);
    delay_us(5);
    IIC_SDA(OFF);
    delay_us(5);
    IIC_SCL(OFF);
 }

void Stop(void)
 {
    IIC_SDA(OFF);
    IIC_SCL(ON);
    delay_us(5);
    IIC_SDA(ON);
    delay_us(5);
}
 
void Reack(void)
{
    u8 i=0;
    IIC_SDA_MODE_IN();
    IIC_SCL(ON); //准备检测SDA Delay5us();
    delay_us(5);
    while((IIC_SDA_IN == 1)&&(i < 200))
    {
        i++;//SDA=0为应该信号,SDA=1为非应答</P>
    }
    IIC_SDA_MODE_OUT();
    delay_us(5);
    IIC_SCL(OFF); //准备下一变化数据</P>
}

void WriteByte(u8 ucByte)
 {
    u8 i;
    for(i=0; i<8; i++)
    {
        IIC_SCL(OFF); 
        delay_us(5);
        if(ucByte & 0x80)
        {
            IIC_SDA(ON);
        }
        else
        {
            IIC_SDA(OFF);
        }

        ucByte <<= 1;
        delay_us(5);
        IIC_SCL(ON); 
        delay_us(5);
    }
    IIC_SCL(OFF); 
    IIC_SDA(ON);
     /*
    IIC_SCL(OFF);
    for(i=0;i<8;i++)
    {
      if(ucByte&0x80)//先写入高位</P>
      {
        IIC_SDA(ON);
      }
      else
      {
         IIC_SDA(OFF);
      }
      IIC_SCL(ON);
      waiting_ms(2);
      IIC_SCL(OFF);
      ucByte <<= 1;
    }
    IIC_SDA(ON); //释放数据线</P>
     */
 }

u8 ReadByte(void)
{
    u8 i,ucByte=0;

    IIC_SDA_MODE_IN();
    delay_us(5);

    IIC_SCL(OFF);
    for(i=0;i<8;i++)
    {
        ucByte <<= 1;
        if(IIC_SDA_IN)
        ucByte++;
        IIC_SCL(ON);
        delay_us(5);
        IIC_SCL(OFF);
    }

    IIC_SDA_MODE_OUT();
    delay_us(5);

    return ucByte;
}

void Write_CH224A(u8 ucAddr,u8 ucData)
 {
      delay_us(5);
      Start();
      WriteByte(WRITE_ADDR);
      Reack();
      WriteByte(ucAddr);
      Reack();
      WriteByte(ucData);
      Reack();
      Stop();
}
 
u8 Read_CH224A(u8 ucAddr)
 {
    u8 ucData;
    delay_us(5);
    Start();
    WriteByte(WRITE_ADDR); //写器件地址</P>
    Reack();
    WriteByte(ucAddr); //写字节地址</P>
    Reack();
    Start();
    WriteByte(READ_ADDR); //写器件地址,最低为1表示读</P>
    Reack();
    ucData = ReadByte(); //写字节地址</P>
    Stop();
    return ucData; //读数据</P>
}

