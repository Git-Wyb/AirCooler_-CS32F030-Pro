/**
  * @file    cs32f0xx_flash.h
  * @brief   This file contains all the functions prototypes for the FLASH 
  *          firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_FLASH_H__
#define __CS32F0XX_FLASH_H__


#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/** @defgroup FLASH_Exported_Constants
  * @{
  */

/** 
  * @struct flash_status_t
  * @brief Flash operate Status 
  */ 
typedef enum
{
    FLASH_STATUS_ERROR    = 0,  //!< Flash erase/program protection error  
    FLASH_STATUS_COMPLETE,      //!< Flash Program complete  
    FLASH_STATUS_TIMEOUT        //!< Flash operate timeout  
}flash_status_t;

/**   
  * @brief FMC_WCR_WCNT
  */ 
#define FMC_WCR_WCNT_0                          ((uint32_t)0x00000000)      //!< FLASH wait 0 cycle  
#define FMC_WCR_WCNT_1                          FMC_WCR_WCNT                //!< FLASH wati 1 cycle  

#define FMC_WCR_WCNT_CHECK(wcnt)                (((wcnt) == FMC_WCR_WCNT_0) || ((wcnt) == FMC_WCR_WCNT_1))

/**   
  * @brief  FLASH_Interrupts
  */   
#define FLASH_INT_END                           FMC_CTR_ENDIE               //!< End of operation interrupt  
#define FLASH_INT_ERR                           FMC_CTR_ERRIE               //!< Error interrupt  

#define FLASH_INT_CHECK(flag)                   ((((flag) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((flag) != 0x00000000)))

/** 
  * @brief Flash memory address 
  */  
#if defined(CS32F031)      						  /*64K Flash devices */
    #define FLASH_PROGRAM_ADDRESS_CHECK(address) (((address) >= 0x08000000) && ((address) <= 0x0800FFFF))
#elif defined(CS32F030)                           /*64K Flash devices */
    #define FLASH_PROGRAM_ADDRESS_CHECK(address) (((address) >= 0x08000000) && ((address) <= 0x0800FFFF))
#elif defined(CS32F036)                           /*32K Flash devices */
    #define FLASH_PROGRAM_ADDRESS_CHECK(address) (((address) >= 0x08000000) && ((address) <= 0x08007FFF))	
#else                                         	  /*64K Flash Flash devices */
    #define FLASH_PROGRAM_ADDRESS_CHECK(address) (((address) >= 0x08000000) && ((address) <= 0x0800FFFF))
#endif 

/** 
  * @brief Flash OB byte address check
  */  
#define FLASH_OB_BYTE_ADDRESS_CHECK(address)    (((address) >= 0x1FFFF800) && ((address) <= 0x1FFFF80A)) 

/** 
  * @brief FLASH Sector Write Protection 
  */ 
#define FLASH_WPROT_NONE 						((uint32_t)0x00000000)		//!< Disable write protection of all sectors
#define FLASH_WPROT_SECTOR0	                	((uint32_t)0x00000001)   	//!< Write protection of sector 0	  
#define FLASH_WPROT_SECTOR1		                ((uint32_t)0x00000002)   	//!< Write protection of sector 1	  
#define FLASH_WPROT_SECTOR2                		((uint32_t)0x00000004)   	//!< Write protection of sector 2   
#define FLASH_WPROT_SECTOR3                		((uint32_t)0x00000008)   	//!< Write protection of sector 3   
#define FLASH_WPROT_SECTOR4                		((uint32_t)0x00000010)   	//!< Write protection of sector 4   
#define FLASH_WPROT_SECTOR5                		((uint32_t)0x00000020)   	//!< Write protection of sector 5   
#define FLASH_WPROT_SECTOR6                		((uint32_t)0x00000040)   	//!< Write protection of sector 6   
#define FLASH_WPROT_SECTOR7                		((uint32_t)0x00000080)   	//!< Write protection of sector 7   
#define FLASH_WPROT_SECTOR8                		((uint32_t)0x00000100)   	//!< Write protection of sector 8   
#define FLASH_WPROT_SECTOR9                		((uint32_t)0x00000200)   	//!< Write protection of sector 9   
#define FLASH_WPROT_SECTOR10                	((uint32_t)0x00000400)   	//!< Write protection of sector 10  
#define FLASH_WPROT_SECTOR11                	((uint32_t)0x00000800)  	//!< Write protection of sector 11  
#define FLASH_WPROT_SECTOR12                	((uint32_t)0x00001000)   	//!< Write protection of sector 12  
#define FLASH_WPROT_SECTOR13                	((uint32_t)0x00002000)   	//!< Write protection of sector 13  
#define FLASH_WPROT_SECTOR14                	((uint32_t)0x00004000)   	//!< Write protection of sector 14  
#define FLASH_WPROT_SECTOR15                	((uint32_t)0x00008000)   	//!< Write protection of sector 15  
#define FLASH_WPROT_SECTOR_ALL                  ((uint32_t)0x0000FFFF)     	//!< Write protection of all Sectors      

/** 
  * @brief FLASH_FUNC Definition
  */ 
#define  FLASH_FUNC_VBUF              			FMC_CFGU_VBUF_EN        	//!<  0.8V VBUF enable/disable in deepsleep mode
#define  FLASH_FUNC_FWUP              		  	FMC_CFGU_FWUP_EN       	 	//!<  FLASH fast wake-up in deepsleep mode

/** 
  * @brief FLASH_Read Protection Level  
  */ 
#define OB_RPROT_LEVEL_0                        ((uint8_t)0xAA)             //!< Flash read protection level 0  
#define OB_RPROT_LEVEL_1                        ((uint8_t)0xBB)             //!< Flash read protection level 1  
#define OB_RPROT_LEVEL_2                        ((uint8_t)0xCC)             //!< Flash read protection level 2  

#define OB_RPROT_LEVEL_CHECK(level)             ((((level) == OB_RPROT_LEVEL_0) || ((level) == OB_RPROT_LEVEL_1)) || \
                                                ((level) == OB_RPROT_LEVEL_2))
                          
/** 
  * @brief Flash Option Bytes FWDT
  */   
#define OB_FWDT_SW      ((uint8_t)0x01)                                     //!< Software FWDT selected  
#define OB_FWDT_HW      ((uint8_t)0x00)                                     //!< Hardware FWDT selected  

#define OB_FWDT_SELECT_CHECK(source)            (((source) == OB_FWDT_SW) || ((source) == OB_FWDT_HW))

/** 
  * @brief Flash Option Bytes STOP control by  reset select. 
  */    
#define OB_DSM_NO_RST                           ((uint8_t)0x02)             //!< No reset generated when entering in DSM  
#define OB_DSM_RST                              ((uint8_t)0x00)             //!< Reset generated when entering in DSM  

#define OB_DSM_RST_SELECT_CHECK(source)         (((source) == OB_DSM_NO_RST) || ((source) == OB_DSM_RST))

/**  
  * @brief Flash Option Bytes STDBY control by  reset select.
  */
#define OB_PWD_NO_RST                           ((uint8_t)0x04)             //!< No reset generated when entering in PWD  
#define OB_PWD_RST                              ((uint8_t)0x00)             //!< Reset generated when entering in PWD  

#define OB_PWD_RST_SELECT_CHECK(source)         (((source) == OB_PWD_NO_RST) || ((source) == OB_PWD_RST))

/** 
  * @brief Flash Option Bytes BOOT1 
  */
#define FLASH_OB_BOOT1_RESET                    ((uint8_t)0x00)             //!< BOOT1 Reset  
#define FLASH_OB_BOOT1_SET                      ((uint8_t)0x10)             //!< BOOT1 Set  

#define FLASH_OB_BOOT1_CHECK(boot1)             (((boot1) == FLASH_OB_BOOT1_RESET) || ((boot1) == FLASH_OB_BOOT1_SET))

/** 
  * @brief Flash Option Bytes VDD detect 
  */
#define FLASH_OB_VDDA_ON                        ((uint8_t)0x20)             //!< Analog detecting on VDDA Power source ON  
#define FLASH_OB_VDDA_OFF                       ((uint8_t)0x00)             //!< Analog detecting on VDDA Power source OFF  

#define FLASH_OB_VDDA_CHECK(analog)             (((analog) == FLASH_OB_VDDA_ON) || ((analog) == FLASH_OB_VDDA_OFF))

/** 
  * @brief Flash Option Bytes SRAM Parity enable Set 
  */
#define FLASH_OB_SRAM_PARITY_SET                ((uint8_t)0x00)             //!< SRAM parity enable Set  
#define FLASH_OB_SRAM_PARITY_RESET              ((uint8_t)0x40)             //!< SRAM parity enable reset  

#define FLASH_OB_SRAM_PARITY_CHECK(parity)      (((parity) == FLASH_OB_SRAM_PARITY_SET) || ((parity) == FLASH_OB_SRAM_PARITY_RESET))
                                               
/** 
  * @brief Flash status flag and status check
  */
#define FLASH_FLAG_BUSY                         FMC_STS_BUSY                //!< FLASH busy flag  
#define FLASH_FLAG_PGERR                        FMC_STS_PGERR               //!< FLASH programming error flag  
#define FLASH_FLAG_WPERR                        FMC_STS_WPERR               //!< FLASH write protected error flag  
#define FLASH_FLAG_ENDF                         FMC_STS_ENDF                //!< FLASH end of programming flag  

/** 
  * @brief Flash operate timeou value
  */ 
#define FLASH_OPERATE_TIMEOUT                   ((uint32_t)0x000B0000)      //!< FLASH operate timeout   

/**
  * @}
  */ 

/**
  * @brief  Enables the FMC wait.
  * @param  None    
  * @return None
  */
#define __FLASH_WAIT_ENABLE()               (FLASH->WCR |= FMC_WCR_WE)

/**
  * @brief  Disables the FMC wait.
  * @param  None    
  * @return None
  */
#define __FLASH_WAIT_DISABLE()              (FLASH->WCR &= ~FMC_WCR_WE)

/**
  * @brief  Checks whether the FLASH wait status is set or not.
  * @param  None
  * @return Flash wait status (SET or RESET).
  */
#define __FLASH_WAIT_STATUS_GET()           ((FLASH->WCR & FMC_WCR_WS) ? SET : RESET)

/**
  * @brief  Enables the specified FLASH function.      
  * @param  FUNC: specifies the FLASH function, it can be one of the following values:
  *         @arg FLASH_FUNC_VBUF (0.8V VBUF enable/disable in deepsleep mode, only available for CS32F03X-RA devices)
  *         @arg FLASH_FUNC_FWUP (FLASH fast wake-up in deepsleep mode, only available for CS32F03X-RA devices)
  * @return None.
  */
#define __FLASH_FUNC_ENABLE(FUNC)           (FLASH->CFGU |= FUNC)

/**
  * @brief  Disables the specified FLASH function.      
  * @param  FUNC: specifies the FLASH function, it can be one of the following values:
  *         @arg FLASH_FUNC_VBUF (0.8V VBUF enable/disable in deepsleep mode, only available for CS32F03X-RA devices)
  *         @arg FLASH_FUNC_FWUP (FLASH fast wake-up in deepsleep mode, only available for CS32F03X-RA devices)
  * @return None.
  */
#define __FLASH_FUNC_DISABLE(FUNC)          (FLASH->CFGU &= ~(FUNC))


/**
  * @brief  Update OB (option bytes).
  * @param  None
  * @return None
  */
#define __FLASH_OPT_UPDATE()                (FLASH->CTR |= FMC_CTR_OBUPDATE)

/**
  * @brief  Get the FLASH User Option Bytes values.
  * @param  None
  * @return The flash User Option Bytes .
  */
#define __FLASH_OPT_USER_GET()              ((uint8_t)(FLASH->OBSTS >> 8))

/**
  * @brief  Get the flash Write Protection Option Bytes value.
  * @param  None
  * @return Flash Write Protection Option Bytes register value(WPSTS).
  */
#define __FLASH_OPT_WRITE_PROTECT_GET()     (FLASH->WPSTS)

/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @param  None
  * @return status(SET or RESET)
  */
#define __FLASH_OPT_READ_PROTECT_GET()      ((FLASH->OBSTS & (FMC_OBSTS_RPROT1 | FMC_OBSTS_RPROT2)) ? SET : RESET)

/**
  * @brief  Enables the specified flash interrupts.
  * @param  FLAG: specifies the FLASH interrupt sources.
  *         It can be any combination of the following values:
  *          @arg FLASH_INT_END(end of programming Interrupt)
  *          @arg FLASH_INT_ERR(Error Interrupt)
  * @return None 
  */
#define __FLASH_INTR_ENABLE(FLAG)           (FLASH->CTR |= FLAG)

/**
  * @brief  Disables the specified flash interrupts.
  * @param  FLAG: specifies the FLASH interrupt sources.
  *         It can be any combination of the following values:
  *          @arg FLASH_INT_END(end of programming Interrupt)
  *          @arg FLASH_INT_ERR(Error Interrupt)
  * @return None 
  */
#define __FLASH_INTR_DISABLE(FLAG)          (FLASH->CTR &= ~(FLAG))

/**
  * @brief  Checks whether the specified  flash interrupts is enabled or not.
  * @param  FLAG: specifies the FLASH interrupt sources enable get.
  *         It can be one of the following values:
  *          @arg FLASH_INT_END(end of programming Interrupt)
  *          @arg FLASH_INT_ERR(Error Interrupt)
  * @return SET or RESET
  */
#define __FLASH_INTR_ENABLE_GET(FLAG)       ((FLASH->CTR & FLAG) ? SET : RESET)

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLAG: specifies the FLASH flag to check. It can be the one of the following values:
  *          @arg BUSY(FLASH write/erase operations in progress flag)
  *          @arg PGERR(FLASH Programming error flag flag)
  *          @arg WPERR(FLASH Write protected error flag)
  *          @arg ENDF(FLASH End of Programming flag)
  * @return The new state of status_flag (SET or RESET).
  */
#define __FLASH_FLAG_STATUS_GET(FLAG)       ((FLASH->STS & FLASH_FLAG_##FLAG) ? SET : RESET)

/**
  * @brief  Clears the FLASH's flags.
  * @param  FLAG: specifies the FLASH flags to clear.It can be any combination of the following values:
  *          @arg FLASH_FLAG_PGERR(FLASH Programming error flag flag)
  *          @arg FLASH_FLAG_WPERR(FLASH Write protected error flag)
  *          @arg FLASH_FLAG_ENDF(FLASH End of Programming flag)
  * @return None
  */
#define __FLASH_FLAG_CLEAR(FLAG)            (FLASH->STS = FLAG)

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
void flash_wait_counter_set(uint32_t counter);

/**
  * @fn void flash_unlock(void)
  * @brief  Unlock the flash control register and program memory access.
  * @param  None
  * @return None
  */
void flash_unlock(void);

/**
  * @fn void flash_lock(void)
  * @brief  Lock the Program memory access.
  * @param  None
  * @return None
  */
void flash_lock(void);

/**
  * @fn flash_status_t flash_page_erase(uint32_t page_addr)
  * @brief  Erases a specified page in program memory. 
  *         The flash_unlock() function must be called before runing this function.
  * @param  page_addr: The page address in program memory to be erased.       
  * @return flash current status.         
  */
flash_status_t flash_page_erase(uint32_t page_addr);

/**
  * @fn flash_status_t flash_all_pages_erase(void)
  * @brief  Erases all flash pages.
  *         The flash_unlock() function must be called before runing this function.
  * @param  None
  * @return flash status.
  */
flash_status_t flash_all_pages_erase(void);

/**
  * @fn flash_status_t flash_word_program(uint32_t addr, uint32_t value)
  * @brief  Programs a word at a specified address.
  *         The flash_unlock() function must be called before runing this function.
  * @param  addr: specifies the address to be programmed.
  * @param  value: specifies the data to be programmed.
  * @return flash status. 
  */
flash_status_t flash_word_program(uint32_t addr, uint32_t value);

/**
  * @fn flash_status_t flash_half_word_program(uint32_t addr, uint16_t value)
  * @brief  Programs a half word at a specified address.
  *         The flash_unlock() function must be called before runing this function.
  * @param  addr: specifies the address to be programmed.
  * @param  value: specifies the data to be programmed.
  * @return flash status. 
  */
flash_status_t flash_half_word_program(uint32_t addr, uint16_t value);

/**
  * @fn void flash_option_bytes_unlock(void)
  * @brief  Unlocks OB (option bytes) block access.
  * @param  None
  * @return None
  */
void flash_option_bytes_unlock(void);

/**
  * @fn void flash_option_bytes_lock(void)
  * @brief  Locks OB (option bytes) block access
  * @param  None
  * @return None
  */
void flash_option_bytes_lock(void);


/**
  * @fn flash_status_t flash_option_bytes_erase(void)
  * @brief  Erases all option bytes except the Read protection (RPROT).
  *         The flash_option_bytes_unlock() function must be called before runing this function.   
  * @param  None
  * @return flash status.
  */
flash_status_t flash_option_bytes_erase(void);

/**
  * @fn flash_status_t flash_option_bytes_user_set(uint8_t value)
  * @brief  Programs the FLASH User Option Byte, It can be FWDT_SW, RST_DSM, RST_PWD,
  *         BOOT1 and VDDA detection. The flash_option_bytes_unlock() function must be called before runing
  *         this function.
  * @param  value: This parameter can be a combination of 
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
flash_status_t flash_option_bytes_user_set(uint8_t value);

/**
  * @fn flash_status_t flash_option_bytes_write_protect_enable(uint16_t value)
  * @brief  Write protects (WPROT) the desired pages.
  *         The flash_option_bytes_unlock() function must be called before runing this function.  
  * @param  value: specifies the address of the pages to be write protected.
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
flash_status_t flash_option_bytes_write_protect_enable(uint16_t value);

/**
  * @fn flash_status_t flash_option_bytes_read_protect_config(uint8_t level)
  * @brief  Enables or disables RPROT (the read out protection).
  *         The flash_option_bytes_unlock() function must be called before runing this function. 
  * @param  level: flash read protection level, it can be:
  *          @arg OB_RPROT_LEVEL_0(No protection)
  *          @arg OB_RPROT_LEVEL_1(Read protection of the memory)
  *          @arg OB_RPROT_LEVEL_2(Chip protection)
  * @note   When enabling set level 2, it's no more possible to go back to level 1 or 0
  * @return flash status. 
  */
flash_status_t flash_option_bytes_read_protect_config(uint8_t level);

/**
  * @fn flash_status_t flash_option_bytes_set(uint32_t addr, uint8_t value)
  * @brief  Programs a half word at a specified Option Byte address.
  * @note   The flash_option_bytes_unlock() function must be called before runing this function.
  * @note   Call the flash_option_bytes_lock() to disable the flash register access and the option bytes.   
  * @param  addr: specifies the address to be programmed can be 0x1FFFF800 to 0x1FFFF80A.
  * @param  value: specifies the data to be programmed.
  * @return flash status.
  */
flash_status_t flash_option_bytes_set(uint32_t addr, uint8_t value);

/**
  * @fn flash_status_t flash_operation_wait(uint32_t counter)
  * @brief  Waits for a FLASH operation to complete or  delay timeout.
  * @param  counter: FLASH programming Timeout
  * @return flash status.
  */
flash_status_t flash_operation_wait(uint32_t counter);

#ifdef __cplusplus
}
#endif


#endif 

/**
  * @}
  */

/**
  * @}
  */ 

