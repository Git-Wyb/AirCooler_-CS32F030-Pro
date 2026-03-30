/**
  * @file    cs32f0xx_dma.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Direct Memory Access controller (DMA):
  *           + Initialization and Configuration
  *           + Data Counter
  *           + Interrupts and flags management
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04               
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
    1. First enable the DMA controller clock,then enable and configure the peripheral 
       to be connected to the DMA channel.
    2. Initializes the DMA Channelx according to the parameters in the dma_config_t.          
    3. Enable the NVIC and the corresponding interrupt using __DMA_INTR_ENABLE() ,
       if needing to use DMA interrupts.
    4. Enable the DMA channel using the __DMA_ENABLE() .   
    5. Using one of the following two methods to control DMA events:
        a.Check on DMA channel flags using the function __DMA_FLAG_STATUS_GET().
        b.Configure DMA interrupts by __DMA_INTR_ENABLE() at initialization
          and check interrupt flag by __DMA_FLAG_STATUS_GET() during communication.  
          using __DMA_FLAG_CLEAR() to clear flag,clear an interrupt flag  using 
          __DMA_FLAG_CLEAR().
    @endverbatim
  *
  */

#include "cs32f0xx_dma.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup DMA
  * @brief DMA driver modules
  * @{
  */

/** 
  * @brief DMA register bit mask  definition  
  */ 
#define DMA_CHxCTR_CONFIG_MASK      ((uint32_t)0xFFFF800F)      //!< DMA channel x controller register Masks 

/**
  * @fn void dma_def_init(dma_channel_reg_t* ptr_chx)
  * @brief  Deinitializes the DMA Channelx registers to their default reset values.   
  * @param  ptr_chx: DMA channelx,it can be DMA1_CHANNELx, where x can be 1,2,3,4,5,6,7
  * @return None
  */
void dma_def_init(dma_channel_reg_t* ptr_chx)
{
    ASSERT(DMA_CHANNEL_CHECK(ptr_chx));

    /* Disable the selected DMA Channel */
    ptr_chx->CHxCTR &= (uint16_t)(~DMA_CHxCTR_CEN);

    /* clear DMA Channelx register value*/
    ptr_chx->CHxCTR = 0;
    ptr_chx->CHxNUM = 0;
    ptr_chx->CHxPA = 0;
    ptr_chx->CHxMA = 0;
    /* clear specifies DMA Channel interrupt intergral flag bits */
    DMA1->INTFC |= (uint32_t)0x0F << (((uint32_t)ptr_chx - DMA1_BASE - 0x08) / 5);
}

/**
  * @fn void dma_init(dma_channel_reg_t* ptr_chx, dma_config_t* ptr_config)
  * @brief  Initializes the DMA Channel according to the specified parameters 
  *         in the ptr_config.
  * @param  ptr_chx: DMA channelx,it can be DMA1_CHANNELx, where x can be 1,2,3,4,5,6,7
  * @param  ptr_config: pointer to a dma_config_t structure containing the configuration
  *         for the specified DMA Channel.
  * @return None
  */
void dma_init(dma_channel_reg_t* ptr_chx, dma_config_t* ptr_config)
{
    uint32_t reg = 0;

    ASSERT(DMA_CHANNEL_CHECK(ptr_chx));
    ASSERT(DMA_TRANS_DIR_CHECK(ptr_config->transfer_direct));
    ASSERT(DMA_BUFFER_SIZE_CHECK(ptr_config->buf_size));
    ASSERT(DMA_PERI_INC_CHECK(ptr_config->peri_inc_flag));
    ASSERT(DMA_MEM_INC_CHECK(ptr_config->mem_inc_flag));
    ASSERT(DMA_PERI_DATA_WIDTH_CHECK(ptr_config->peri_data_width));
    ASSERT(DMA_MEM_DATA_WIDTH_CHECK(ptr_config->mem_data_width));
    ASSERT(DMA_OPERATE_MODE_CHECK(ptr_config->operate_mode));
    ASSERT(DMA_CHANNEL_PRIORITY_CHECK(ptr_config->priority_level));
    ASSERT(DMA_M2M_MODE_CHECK(ptr_config->m2m_flag));

    if (ptr_config->peri_base_addr == 0x40005428 || ptr_config->peri_base_addr == 0x40005828)
    {
        ptr_config->priority_level = DMA_CHANNEL_PRIORITY_HIGHEST;
    }
	
    /* Get the ptr_chx CHxCTR value */
    reg = ptr_chx->CHxCTR;

    /* Clear M2MM, PRIL, MWDH, PWDH, MAGM, PAGM, CIRM and DIR bits */
    reg &= DMA_CHxCTR_CONFIG_MASK;

    /* Configurate DMA's CHxCTR, CHxNum, CHxPA, CHxMA */
    reg |= ptr_config->transfer_direct | ptr_config->operate_mode |
           ptr_config->peri_inc_flag | ptr_config->mem_inc_flag |
           ptr_config->peri_data_width | ptr_config->mem_data_width |
           ptr_config->priority_level | ptr_config->m2m_flag;
  
    ptr_chx->CHxCTR = reg;
    ptr_chx->CHxNUM = ptr_config->buf_size;
    
    ptr_chx->CHxPA = ptr_config->peri_base_addr;  
    ptr_chx->CHxMA = ptr_config->mem_base_addr;
}

/**
  * @fn dma_transfer_config(dma_channel_reg_t* ptr_chx, uint32_t mem_addr, uint32_t peri_addr, uint32_t len)
  * @brief  Sets the both memory address and peripheral address of specified DMA Channel.
  * @param ptr_chx: DMA channelx,it can be DMA1_CHANNELx, where x can be 1,2,3,4,5,6,7
  * @param  mem_addr: Memory address.
  * @param  peri_addr: Peripheral address.
  * @param  len: Transfer data lenth.
  * @return None
  */
void dma_transfer_config(dma_channel_reg_t* ptr_chx, uint32_t mem_addr, uint32_t prti_addr, uint32_t len)
{
    ASSERT(DMA_CHANNEL_CHECK(ptr_chx));
    ASSERT(DMA_BUFFER_SIZE_CHECK(len));
	
  	/* Clear all flags */
    DMA1->INTFC |= (uint32_t)0x0F << (((uint32_t)ptr_chx - DMA1_BASE - 0x08) / 5);

  	/* Configure DMA Channel data length */
    ptr_chx->CHxNUM = len;
	
    /* Configure DMA Channel memory address */
    ptr_chx->CHxMA = mem_addr;
	
    /* Configure DMA Channel source address */
    ptr_chx->CHxPA = prti_addr;
}

/**
  * @fn void dma_struct_config(dma_config_t* ptr_config)
  * @brief  config each ptr_config member with its default value.
  * @param  ptr_config: pointer to a dma_config_t structure being initialized.        
  * @return None
  */
void dma_struct_config(dma_config_t* ptr_config)
{
    ptr_config->peri_base_addr = 0;
    ptr_config->mem_base_addr = 0;
  
    ptr_config->transfer_direct = DMA_TRANS_DIR_FROM_PERI;
    ptr_config->buf_size = 0;
    
    ptr_config->peri_inc_flag = DMA_PERI_INC_DISABLE;
    ptr_config->mem_inc_flag = DMA_MEM_INC_DISABLE;
  
    ptr_config->peri_data_width = DMA_PERI_DATA_WIDTH_BYTE;
    ptr_config->mem_data_width = DMA_MEM_DATA_WIDTH_BYTE;
    
    ptr_config->operate_mode = DMA_OPERATE_MODE_NORMAL;
    ptr_config->priority_level = DMA_CHANNEL_PRIORITY_LOW;
    
    ptr_config->m2m_flag = DMA_M2M_MODE_DISABLE;
}

/**
  * @}
  */

/**
  * @}
  */

