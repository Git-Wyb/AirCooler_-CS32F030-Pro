/**
  * @file    cs32f0xx_flash.c  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *            - FLASH Interface configuration
  *            - FLASH Memory Programming
  *            - Option Bytes Programming
  *            - Interrupts and flags management
  *
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
    The driver provides functions to configure and program the Flash memory of  CS32F0xx devices.          
         1. FLASH Interface configuration functions: 
           a.Set the wait conuter. 
           b.Option enable or disable wait.
           
         2. FLASH Memory Programming functions: 
             a. Lock and Unlock the Flash.
             b. Erase function: Erase Page, erase all pages.
             c.Program functions: Half Word and Word write.

         3. FLASH Option Bytes Programming functions: 
             a. Lock and Unlock the Flash Option bytes.
             b. Update the Option Bytes.
             c. Erase the Option Bytes.
             d.Set or Reset the write protection.
             e.Set the Read protection Level
             f. Program the user option Bytes.
             g.Set or Reset the BOOT1 bit.
             h. Enable or Disable the VDDA detect.
             i. Get the user option bytes.
             j. Get the Write protection.
             k. Get the read protection status.

        4. FLASH Interrupts and flag management functions: 
             a. Enable or Disable the flash interrupt sources
             b. Get flags status
             c. Clear flags
             d. Get Flash operation status
             e. Wait for last flash operation
    @endverbatim
  *
  */  

#include "cs32f0xx_flash.h"


/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup FLASH
  * @brief FLASH driver modules
  * @{
  */ 


/**
  * @fn void flash_wait_counter_set(uint32_t counter)
  * @brief  Sets WCNT (wait conuter).
  * @param  counter: set wait count value. It can be one of the following values:
  *          @arg FMC_WCR_WCNT_0(0 cycle)
  *          @arg FMC_WCR_WCNT_1(1 cycle)
  * @note   For reading data from Flash memory, the number of wait states
  * @note   must be correctly programmed according to  the CPU clock (HCLK) 
  * @note   -------------------------------------------------
  *         |  Wait states      |   HCLK  frequency (MHz)   |
  *         |-------------------|---------------------------|
  *         |0WS(1CPU cycle)    |    0 < HCLK <= 24         |
  *         |1WS(2CPU cycle)    |    24 < HCLK <= 48        |
  *         -------------------------------------------------
  * @return None
  */
void flash_wait_counter_set(uint32_t counter)
{
    ASSERT(FMC_WCR_WCNT_CHECK(counter));
    
    MODIFY_REG(FLASH->WCR, FMC_WCR_WCNT, counter);
}

/**
  * @fn void flash_unlock(void)
  * @brief  Unlock the flash control register and program memory access.
  * @param  None
  * @return None
  */
void flash_unlock(void)
{
    if((FLASH->CTR & FMC_CTR_LOCK) != RESET)
    {
        /* Unlocking the program memory access */
        FLASH->CCODE = FMC_CCODE_VALUE1;
        FLASH->CCODE = FMC_CCODE_VALUE2;
    }
}

/**
  * @fn void flash_lock(void)
  * @brief  Lock the Program memory access.
  * @param  None
  * @return None
  */
void flash_lock(void)
{
    /* Set the lock bit*/
    FLASH->CTR |= FMC_CTR_LOCK;
}

/**
  * @fn flash_status_t flash_page_erase(uint32_t page_addr)
  * @brief  Erases a specified page in program memory. 
  *         The flash_unlock() function must be called before runing this function.
  * @param  page_addr: The page address in program memory to be erased.       
  * @return flash current status.         
  */
flash_status_t flash_page_erase(uint32_t page_addr)
{
    flash_status_t status = FLASH_STATUS_COMPLETE;

    ASSERT(FLASH_PROGRAM_ADDRESS_CHECK(page_addr));
    /* Wait for last operation to be completed */
    status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);
  
    if(status == FLASH_STATUS_COMPLETE)
    { 
        /* If the previous operation is completed, proceed to erase the page */
        FLASH->CTR |= FMC_CTR_PERS;
        FLASH->ERSADR  = page_addr;
        FLASH->CTR |= FMC_CTR_START;
        
        /* Wait for last operation to be completed */
        status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);
    
        /* Disable the PERS Bit */
        FLASH->CTR &= ~FMC_CTR_PERS;
    }
    
    /* Return the Erase Status */
    return status;
}

/**
  * @fn flash_status_t flash_all_pages_erase(void)
  * @brief  Erases all flash pages.
  *         The flash_unlock() function must be called before runing this function.
  * @param  None
  * @return flash status.
  */
flash_status_t flash_all_pages_erase(void)
{
    flash_status_t status = FLASH_STATUS_COMPLETE;

    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CTR |= FMC_CTR_CHIPERS;
    FLASH->CTR |= FMC_CTR_START;
    
    /* Wait for last operation to be completed */
    status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);

    /* Disable the CHIPERS Bit */
    FLASH->CTR &= ~FMC_CTR_CHIPERS;

    /* Return the Erase Status */
    return status;
}

/**
  * @fn flash_status_t flash_word_program(uint32_t addr, uint32_t value)
  * @brief  Programs a word at a specified address.
  *         The flash_unlock() function must be called before runing this function.
  * @param  addr: specifies the address to be programmed.
  * @param  value: specifies the data to be programmed.
  * @return flash status. 
  */
flash_status_t flash_word_program(uint32_t addr, uint32_t value)
{
    flash_status_t status = FLASH_STATUS_COMPLETE;

    ASSERT(FLASH_PROGRAM_ADDRESS_CHECK(addr));

    /* Enable the word program */ 
	FLASH->CFG |= FMC_CFG_PGWORD;
	
    /* Proceed to program the word */    
    FLASH->CTR |= FMC_CTR_PG;
    
    *(__IO uint32_t*)addr = value;
	
    /* Wait for last operation to be completed */
    status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);

    /* Disable the PG Bit */
    FLASH->CTR &= ~FMC_CTR_PG;

    /* Return the Program Status */
    return status;
}

/**
  * @fn flash_status_t flash_half_word_program(uint32_t addr, uint16_t value)
  * @brief  Programs a half word at a specified address.
  *         The flash_unlock() function must be called before runing this function.
  * @param  addr: specifies the address to be programmed.
  * @param  value: specifies the data to be programmed.
  * @return flash status. 
  */
flash_status_t flash_half_word_program(uint32_t addr, uint16_t value)
{
    flash_status_t status = FLASH_STATUS_COMPLETE;

    ASSERT(FLASH_PROGRAM_ADDRESS_CHECK(addr));

	/*Proceed to program the new data */
   	FLASH->CTR |= FMC_CTR_PG;
  
   	*(__IO uint16_t*)addr = value;

   	/* Wait for last operation to be completed */
   	status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);
   
   	/* Disable the PG Bit */
   	FLASH->CTR &= ~FMC_CTR_PG;
  
    /* Return the Program Status */
    return status;
}

/**
  * @fn void flash_option_bytes_unlock(void)
  * @brief  Unlocks option bytes block access.
  * @param  None
  * @return None
  */
void flash_option_bytes_unlock(void)
{
    if((FLASH->CTR & FMC_CTR_OBWEN) == RESET)
    { 
        /* Unlocking the option bytes block access */
        FLASH->OBCCODE = FMC_OBCCODE_VALUE1;
        FLASH->OBCCODE = FMC_OBCCODE_VALUE2;
    }
}

/**
  * @fn void flash_option_bytes_lock(void)
  * @brief  Locks option bytes block access
  * @param  None
  * @return None
  */
void flash_option_bytes_lock(void)
{
    /* Set the OBWEN bit to lock the option bytes block access */
    FLASH->CTR &= ~FMC_CTR_OBWEN;
}

/**
  * @fn flash_status_t flash_option_bytes_erase(void)
  * @brief  Erases all option bytes except the Read protection (RPROT).
  *         The flash_option_bytes_unlock() function must be called before runing this function.   
  * @param  None
  * @return flash status.
  */
flash_status_t flash_option_bytes_erase(void)
{
    uint16_t temp = OB_RPROT_LEVEL_0;
    flash_status_t status = FLASH_STATUS_COMPLETE;

    /* Get the actual read protection Option Byte value */ 
    if(__FLASH_OPT_READ_PROTECT_GET() != RESET)
    {
        temp = 0x00;  
    }

    /* Proceed to erase the option bytes */
    FLASH->CTR |= FMC_CTR_OBERS;
    FLASH->CTR |= FMC_CTR_START;

    /* Wait for last operation to be completed */
    status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);

    if(status == FLASH_STATUS_COMPLETE)
    {
        /* Disable the OBERS bit if the erase operation is complete */
        FLASH->CTR &= ~FMC_CTR_OBERS;
    
        /* Enable the Option Bytes Programming operation */
        FLASH->CTR |= FMC_CTR_OBPG;

        /* Restore the last read protection Option Byte value */
        OB->RPROT = (uint16_t)temp; 

        /* Wait for last operation to be completed */
        status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);
        if(status != FLASH_STATUS_TIMEOUT)
        {
            /* Disable the OBPG bit if the program operation is complete */
            FLASH->CTR &= ~FMC_CTR_OBPG;
        }
    }
    else
    {
        if (status != FLASH_STATUS_TIMEOUT)
        {
            /* Disable the OBPG bit */
            FLASH->CTR &= ~FMC_CTR_OBPG;
        }
    }
    
    /* Return the erase status */
    return status;
}

/**
  * @fn flash_status_t flash_option_bytes_user_set(uint8_t value)
  * @brief  Programs the FLASH User Option Byte, It can be FWDT_SW, RST_DSM, RST_PWD,
  *         BOOT1 and VDDA detection. The flash_option_bytes_unlock() function must be called before runing
  *         this function.
  * @param  set_value: This parameter can be a combination of 
  *         one of @arg OB_FWDT_HW(Hardware WDG selected), @arg OB_FWDT_SW(Software WDG selected), and 
  *         one of @arg OB_DSM_RST(reset generated when entering in DSM), 
  *                @arg OB_DSM_NO_RST(No reset generated when entering in DSM) and 
  *         one of @arg OB_PWD_NO_RST(reset generated when entering in PWD), 
  *                @arg OB_PWD_RST(reset generated when entering in PWD) and
  *         one of @arg FLASH_OB_BOOT1_RESET(BOOT1 reset), @arg FLASH_OB_BOOT1_SET(BOOT1 set) and
  *         one of @arg FLASH_OB_VDDA_ON(Analog monitoring on VDDA Power source ON),
  *                @arg FLASH_OB_VDDA_OFF(Analog monitoring on VDDA Power source OFF) and 
  *         one of @arg FLASH_OB_SRAM_PARITY_SET(SRAM Parity SET),
  *                @arg FLASH_OB_SRAM_PARITY_RESET(SRAM Parity RESET).
  * @return flash status.
  */
flash_status_t flash_option_bytes_user_set(uint8_t value)
{
    flash_status_t status = FLASH_STATUS_COMPLETE;
    
    status = flash_option_bytes_set(OB_BASE + 0x02, value);

    /* Return the erase status */
    return status;
}

/**
  * @fn flash_status_t flash_option_bytes_write_protect_enable(uint16_t value)
  * @brief  Write protects (WPROT) the desired pages.
  *         The flash_option_bytes_unlock() function must be called before runing this function.  
  * @param  set_value: specifies the address of the pages to be write protected.
  *          It can be any combinations of the following values:
  *           @arg FLASH_WPROT_NONE (Disable write protection of all sectors)    
  *           @arg FLASH_WPROT_SECTOR0 (Write protection of sector 0)  
  *           @arg FLASH_WPROT_SECTOR1 (Write protection of sector 1)   
  *           @arg FLASH_WPROT_SECTOR2 (Write protection of sector 2)   
  *           @arg FLASH_WPROT_SECTOR3 (Write protection of sector 3)  
  *           @arg FLASH_WPROT_SECTOR4 (Write protection of sector 4)  
  *           @arg FLASH_WPROT_SECTOR5 (Write protection of sector 5)  
  *           @arg FLASH_WPROT_SECTOR6 (Write protection of sector 6)  
  *           @arg FLASH_WPROT_SECTOR7 (Write protection of sector 7)  
  *           @arg FLASH_WPROT_SECTOR8 (Write protection of sector 8)  
  *           @arg FLASH_WPROT_SECTOR9 (Write protection of sector 9)  
  *           @arg FLASH_WPROT_SECTOR10 (Write protection of sector 10)  
  *           @arg FLASH_WPROT_SECTOR11 (Write protection of sector 11)  
  *           @arg FLASH_WPROT_SECTOR12 (Write protection of sector 12)  
  *           @arg FLASH_WPROT_SECTOR13 (Write protection of sector 13)  
  *           @arg FLASH_WPROT_SECTOR14 (Write protection of sector 14)  
  *           @arg FLASH_WPROT_SECTOR15 (Write protection of sector 15)  
  *           @arg FLASH_WPROT_SECTOR_ALL (Write protection of all sectors)   
  * @return flash status. 
  */
flash_status_t flash_option_bytes_write_protect_enable(uint16_t value)
{
    uint8_t wport0 = 0xFF;
    uint8_t wport1 = 0xFF;

    flash_status_t status = FLASH_STATUS_COMPLETE;

    value = ~value;
    wport0 = value & OB_WPROT0_WPROT0;
    wport1 = (value >> 8) & OB_WPROT0_WPROT0;
 

    status = flash_option_bytes_set(OB_BASE + 0x08, wport0);
    
    if(status == FLASH_STATUS_COMPLETE)
    {
        status = flash_option_bytes_set(OB_BASE + 0x0A, wport1);
    }

    /* Return the write protection operation Status */
    return status;
}

/**
  * @fn flash_status_t flash_option_bytes_read_protect_config(uint8_t level)
  * @brief  Enables or disables RPROT (the read out protection).
  *         The flash_option_bytes_unlock() function must be called before runing this function. 
  * @param  set_level: flash read protection level, it can be:
  *          @arg OB_RPROT_LEVEL_0(No protection)
  *          @arg OB_RPROT_LEVEL_1(Read protection of the memory)
  *          @arg OB_RPROT_LEVEL_2(Chip protection)
  * @note   When enabling set level 2, it's no more possible to go back to level 1 or 0
  * @return flash status. 
  */
flash_status_t flash_option_bytes_read_protect_config(uint8_t level)
{
    flash_status_t status = FLASH_STATUS_COMPLETE;
  
    ASSERT(OB_RPROT_LEVEL_CHECK(level));
    
    status = flash_option_bytes_set(OB_BASE, level);
    
    /* Return the protection operation Status */
    return status;
}

/**
  * @fn flash_status_t flash_option_bytes_set(uint32_t addr, uint8_t value)
  * @brief  Programs a half word at a specified Option Byte address.
  * @note   The flash_option_bytes_unlock() function must be called before runing this function.
  * @note   Call the flash_option_bytes_lock() to disable the flash register access and the option bytes.   
  * @param  addr: specifies the address to be programmed can be 0x1FFFF800 to 0x1FFFF80A.
  * @param  value: specifies the data to be programmed.
  * @return flash status.
  */
flash_status_t flash_option_bytes_set(uint32_t addr, uint8_t value)
{
    uint8_t times = 0;
	uint16_t reg[6] = {0};
		
    flash_status_t status = FLASH_STATUS_COMPLETE;
    
    ASSERT(FLASH_OB_BYTE_ADDRESS_CHECK(addr));
	
	/* Read the option bytes */
	reg[0] = OB->RPROT;
	reg[1] = OB->USER;
	reg[2] = OB->DATA0;
	reg[3] = OB->DATA1;
	reg[4] = OB->WPROTOB0;
	reg[5] = OB->WPROTOB1;

    /* Proceed to erase the option bytes */
    FLASH->CTR |= FMC_CTR_OBERS;
    FLASH->CTR |= FMC_CTR_START;

    /* Wait for last operation to be completed */
    status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);
    
    if(status == FLASH_STATUS_COMPLETE)
    {
        FLASH->CTR &= ~FMC_CTR_OBERS;
        FLASH->CTR |= FMC_CTR_OBPG;
        
        while(times < 0x0B)
        {
            if(addr == (OB_BASE + times))
            {
                *(__IO uint16_t*)addr = value;
            }
            else
            {
                *(__IO uint16_t*)(OB_BASE + times) = reg[times >> 1];
            }
            times = times + 2;
        }
        /* Wait for last operation to be completed */
        status = flash_operation_wait(FLASH_OPERATE_TIMEOUT);
        
        if(status != FLASH_STATUS_TIMEOUT)
        {
            /* Disable the OBPG bit if tht program operation is completed*/
            FLASH->CTR &= ~FMC_CTR_OBPG;
        }
    }

    /* Return the Option Byte Data Program Status */
    return status;
}

/**
  * @fn flash_status_t flash_operation_wait(uint32_t counter)
  * @brief  Waits for a FLASH operation to complete or  delay timeout.
  * @param  counter: FLASH programming Timeout
  * @return flash status.
  */
flash_status_t flash_operation_wait(uint32_t counter)
{ 
    while((FLASH->STS & FMC_STS_BUSY) && (counter != 0x00))
    {
        counter--;
    }
    if(FLASH->STS & (FMC_STS_PGERR|FMC_STS_WPERR))
    {
        return FLASH_STATUS_ERROR;
    }

    if(counter == 0)
    {
        return FLASH_STATUS_TIMEOUT;
    }
    
    return FLASH_STATUS_COMPLETE;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
