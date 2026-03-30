/**
  * @file    cs32f0xx_rtc.c  
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Real-Time Clock (RTC) peripheral and 
  *          is not applicable for CS32F036 devices:
  *           + Initialization
  *           + Calendar (Time and Date) configuration
  *           + Alarms configuration
  *           + Daylight Saving configuration
  *           + Output pin Configuration
  *           + Digital Calibration configuration  
  *           + Output Type Config configuration
  *           + Shift control synchronisation  
  *           + Interrupts and flags management
  *
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2020 ChipSea</center></h2>
  *
  * @verbatim  
  *
  ----------------------- this driver instruction for use--------------------------- 
     1. Backup Domain Operating Condition 
       a.The real-time clock (RTC) and the RTC backup registers can be powered
         from the VBAT voltage when the main VDD supply is powered off.
         To retain the content of the RTC backup registers and supply the RTC 
         when VDD is turned off, VBAT pin can be connected to an optional
         standby voltage supplied by a battery or by another source.
  
       b.To allow the RTC to operate even when the main digital supply (VDD) 
         is turned off, the VBAT pin powers the The RTC,The LXT oscillator,
         and PC13 to PC15 I/Os I/Os (when available)blocks.

      c. If the backup domain is supplied by VDD (analog switch connected 
         to VDD), PC14 and PC15 can be used as either GPIO or LXT pins,
         PC13 can be used as a GPIO or as the RTC_MF1 pin.
                                                                                           
     2. Time and Date configuration 
        a. Configuring the RTC Calendar (Time and Date),can use the rtc_time_set()
            and rtc_date_set() functions.
        b. Reading the RTC Calendar, can use the rtc_time_get() and rtc_date_get()functions.            
        c. Reading the RTC subsecond,can use the rtc_subsecond_get() function.
        d. Use the rtc_daylight_saving_config() function to add or sub one
            hour to the RTC Calendar.

     3. Alarm configuration
        a. To configure the RTC Alarm use the rtc_alarm_set() function.
        b. Enable the selected RTC Alarm using the rtc_alarm_enable_ctrl() function  
        c. To read the RTC Alarm, use the rtc_alarm_get() function.
        d. To read the RTC alarm SubSecond, use the rtc_alarm_subsecond_get() function.

    4. RTC Wakeup configuration 
        a. Configure the RTC Wakeup Clock source use the rtc_wakeup_clock_config() function.            
        b. Configure the RTC WakeUp Counter using the rtc_wakeup_value_set() function .              
        c. Enable the RTC WakeUp using the rtc_wakeup_enable_ctrl() function.  
        d.To read the RTC WakeUp Counter register, use the rtc_wakeup_value_get() function.
              
    5. Outputs configuration the RTC has 2 different outputs
        a. To manage the RTC Alarm, use the rtc_output_config().                      
        b.  The output is 512Hz signal or 1Hz use the rtc_cali_output_enable_ctrl().           
  
    6. Original Digital Calibration configuration 
        a. Configure the RTC Original Digital Calibration Value and the corresponding
         calibration cycle period (32s,16s and 8s) using the rtc_swallow_config().
  
   7.Recording configuration      
        a. Configure the trigger and enables the RTC  
            using the rtc_time_recording_config() function.
        b. To read the RTC recording Time and Date register, use the 
            rtc_time_recording_get() function.
        c. To read the RTC recording SubSecond register, use the 
            rtc_time_recording_subsecond_get() function.
  
   8. Rtc inbreak configuration 
        a. Configure the inbreak filter count using rtc_inbreak_filter_config().            
        b. Configure the RTC recording trigger Edge or Level according to the recording 
            filter value.
        c. Configure the inbreak sampling frequency using rtc_inbreak_sample_freq_config().
        d. Configure the inbreak precharge or discharge duration using rtc_inbreak_precharge_duration().            
        e. Enable the inbreak Pull-UP using rtc_inbreak_pull_up_enable_ctrl() .
        f. Enable the RTC inbreak using the rtc_inbreak_enable_ctrl() .
        g. Enable the Time recording on detection event .       
  
   9. RTC always on registers configuration 
        a.To write to the RTC always on registers, use the rtc_ao_register_write().
        b. To read the RTC always on registers, use the rtc_ao_register_read().

   10. RTC and low power modes
    a. The MCU can be woken up from a low power mode by an RTC multi-function. 
    b.The RTC  multi-functions are the RTC alarm , RTC inbreak 
         event detection and RTC time recording event detection.
         These RTC  multi-function can wake up the system from the Stop 
         and Standby lowpower modes.
         The system can also wake up from low power modes without depending 
         on an external interrupt (Auto-wakeup mode), by using the RTC alarm events.
    c.The RTC provides a programmable time base for waking up from the 
         Stop or Standby mode at regular intervals.
         Wakeup from STOP and Standby modes is possible only when the RTC 
         clock source is LXT or LRC.
   @endverbatim
  *
  */

#include "cs32f0xx_rtc.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup RTC 
  * @brief RTC driver modules
  * @{
  */

/** 
  * @brief  RTC register bit mask  definition  
  */ 
#define RTC_TIME_RESERVED_MASK  ((uint32_t)0x007F7F7F)  //!< RTC time register RESERVED mask
#define RTC_DATE_RESERVED_MASK  ((uint32_t)0x00FFFF3F)  //!< RTC date register RESERVED mask
#define RTC_INIT_MASK           ((uint32_t)0xFFFFFFFF)  //!< RTC date register RESERVED mask 
#define RTC_RSF_MASK            ((uint32_t)0xFFFFFF5F)  //!< RTC status register synchronization flag mask

/** 
  * @brief RTC timeout definition	
  */ 
#define RTC_INIT_MODE_TIMEOUT   ((uint32_t) 0x00004000)  //!< RTC INIT state timeout
#define RTC_SYNCHRO_TIMEOUT     ((uint32_t) 0x00008000)  //!< synchro timeout 
#define RTC_CALI_TIMEOUT        ((uint32_t) 0x00001000)  //!< Calibration timeout
#define RTC_SHPF_TIMEOUT        ((uint32_t) 0x00001000)  //!< Shitf timeout


static uint8_t rtc_byte_convert_bcd(uint8_t value);
static uint8_t rtc_bcd_convert_byte(uint8_t value);

/**
  * @fn error_status_t rtc_def_init(void)
  * @brief  Deinitializes the RTC registers to their default reset values. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  None.
  * @return Deinitialization status: SUCCESS or ERROR.
  */
error_status_t rtc_def_init(void)
{
    error_status_t status = ERROR;

    /* Set Initialization mode */
    if (rtc_init_mode_enter() == ERROR)
    {
        status = ERROR;
    }  
    else
    {
        /* Reset TIME, DATE and CTR registers */
        RTC->TIME      = (uint32_t)0x00000000;
        RTC->DATE      = (uint32_t)0x00002101;
        RTC->CTR      &= (uint32_t)0x00000000;
        RTC->PDIV      = (uint32_t)0x007F00FF;
        RTC->ACFG1     = (uint32_t)0x00000000;
        RTC->ADJ       = (uint32_t)0x00000000;
        RTC->RTC_1SCAL = (uint32_t)0x00000000;
        RTC->ACFG2     = (uint32_t)0x00000000;

        /* Reset STS register and exit initialization mode */
        RTC->STS = (uint32_t)0x00000000;
    
        /* Reset  multi-function configuration register */
        RTC->MF = 0x00000000;
      
        /* Wait till the RTC RSF flag is set */
        if (rtc_synchro_wait() == ERROR)
        {
            status = ERROR;
        }
        else
        {
            status = SUCCESS;
        }

    }

    return status;
}

/**
  * @fn error_status_t rtc_init(rtc_init_t* ptr_init_struct)
  * @brief  Initializes the RTC registers according to the specified parameters in ptr_init_struct. RTC prescaler  
  *         register can be written in initialization step only. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  ptr_init_struct: pointer to a rtc_init_t structure that contains the configuration information for the RTC 
  *         peripheral.
  * @return Initialization status: SUCCESS or ERROR.
  */
error_status_t rtc_init(rtc_init_t* ptr_init_struct)
{
    error_status_t status = ERROR;

    ASSERT(RTC_HOUR_FORMAT_CHECK(ptr_init_struct->hour_format));
    ASSERT(RTC_PDIV1_CHECK(ptr_init_struct->rtc_divider1));
    ASSERT(RTC_PDIV2_CHECK(ptr_init_struct->rtc_divider2));

    /* Set Initialization mode */
    if (rtc_init_mode_enter() == ERROR)
    {
        status = ERROR;
    }
    else
    {        
        MODIFY_REG(RTC->CTR, RTC_CTR_FMT12, ptr_init_struct->hour_format);
        
        /* Configure the RTC PDIV */
        RTC->PDIV = (ptr_init_struct->rtc_divider1 << 16) | ptr_init_struct->rtc_divider2;
        
        /* Exit Initialization mode */
        __RTC_INIT_MODE_EXIT();
        status = SUCCESS;
    }

    return status;
}

/**
  * @fn void rtc_struct_init(rtc_init_t* ptr_init_struct)
  * @brief  Fills each rtc_init_struct member with its default value.
  * @param  ptr_init_struct: pointer to a ptr_init_struct structure which will be initialized.         
  * @return None.
  */
void rtc_struct_init(rtc_init_t* ptr_init_struct)
{
    /* Initialize the hour_format member */
    ptr_init_struct->hour_format = RTC_HOUR_FORMAT_24;
    
    /* Init the first pre-divider factor member */
    ptr_init_struct->rtc_divider1 = (uint32_t)0x7F;

    /* Init the second pre-divider factor member */
    ptr_init_struct->rtc_divider2 = (uint32_t)0xFF; 
}   

/**
  * @fn error_status_t rtc_init_mode_enter(void)
  * @brief  Enters the RTC Initialization mode. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  None.
  * @return The RTC Initialization mode enter status: SUCCESS or ERROR.
  */
error_status_t rtc_init_mode_enter(void)
{
    __IO uint32_t init_counter = 0x00;
    uint32_t status_value = 0x00;
    error_status_t status = ERROR;

    /* Check if the Initialization mode is set */
    if ((RTC->STS & RTC_STS_INITF) == (uint32_t)RESET)
    {
        /* Set the Initialization mode */
        RTC->STS = (uint32_t)RTC_INIT_MASK;
        
        /* Wait till RTC is in INIT state and if Time out is reached exit */
        do
        {
            status_value = RTC->STS & RTC_STS_INITF;
            init_counter++;  
        } while ((init_counter != RTC_INIT_MODE_TIMEOUT) && (status_value == 0x00));
        
        if ((RTC->STS & RTC_STS_INITF) != RESET)
        {
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }
    }
    else
    {
        status = SUCCESS;
    }

    return status;
}

/**
  * @fn error_status_t rtc_synchro_wait(void)
  * @brief  Waits until the RTC time and date registers (RTC_TIME and RTC_DATE) are synchronized with RTC APB clock.                 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  None.
  * @return error_status_t value:SUCCESS or ERROR.
  */
error_status_t rtc_synchro_wait(void)
{
    __IO uint32_t sync_counter = 0;
    uint32_t temp_status = 0x00;
    error_status_t status = ERROR;

    if ((RTC->CTR & RTC_CTR_DAR) != RESET)
    {
        /* direct access mode */
        status = SUCCESS;
    }
    else
    {
        /* Clear RSF flag */
        RTC->STS &= (uint32_t)RTC_RSF_MASK;

        /* Wait the registers to be synchronised */
        do
        {
            temp_status = RTC->STS & RTC_STS_RSF;
            sync_counter++;  
        } while((sync_counter != RTC_SYNCHRO_TIMEOUT) && (temp_status == 0x00));

        if ((RTC->STS & RTC_STS_RSF) != RESET)
        {
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }
    }

    return (status);
}

/**
  * @fn error_status_t rtc_outside_clock_enable_ctrl(enable_state_t enable_flag)
  * @brief  Enables or disables outside precise clock enable detection. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  enable_flag: It can be ENABLE or DISABLE.
  * @return Configuration status: SUCCESS or ERROR.
  */
error_status_t rtc_outside_clock_enable_ctrl(enable_state_t enable_flag)
{
    error_status_t status = ERROR;

    ASSERT(FUNCTIONAL_STATE_CHECK(enable_flag));

    /* Set Initialization mode */
    if (rtc_init_mode_enter() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        if (enable_flag != DISABLE)
        {
            /* Enable the RTC outside precise clock detection */
            RTC->CTR |= RTC_CTR_OPCLKEN;
        }
        else
        {
            /* Disable the RTC outside precise clock detection */
            RTC->CTR &= ~RTC_CTR_OPCLKEN;
        }
        
        /* Exit Initialization mode */
        __RTC_INIT_MODE_EXIT();

        status = SUCCESS;
    }

    return status;
}


/**
  * @fn error_status_t rtc_time_set(uint32_t format_flag, rtc_time_t* ptr_time_struct)
  * @brief  Set the RTC current time. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).        
  * @param  ptr_time_struct: pointer to a rtc_time_t structure that contains the time configuration information for the RTC.
  * @return Setting status: SUCCESS or ERROR.
  */
error_status_t rtc_time_set(uint32_t format_flag, rtc_time_t* ptr_time_struct)
{
    uint32_t reg = 0;
    error_status_t status = ERROR;

    ASSERT(RTC_FORMAT_CHECK(format_flag));
  
    if (format_flag == RTC_FORMAT_BIN)
    {
        if ((RTC->CTR & RTC_CTR_FMT12) != (uint32_t)RESET)
        {
            ASSERT(RTC_HOUR12_CHECK(ptr_time_struct->rtc_hours));
            ASSERT(RTC_AM_PM_HOUR12_CHECK(ptr_time_struct->am_pm_sel));
        }
        else
        {
            ptr_time_struct->am_pm_sel = 0x00;
            ASSERT(RTC_HOUR24_CHECK(ptr_time_struct->rtc_hours));
        }
        
        ASSERT(RTC_MINUTES_CHECK(ptr_time_struct->rtc_minutes));
        ASSERT(RTC_SECONDS_CHECK(ptr_time_struct->rtc_seconds));
    }
    else
    {
        if ((RTC->CTR & RTC_CTR_FMT12) != (uint32_t)RESET)
        {
            reg = rtc_bcd_convert_byte(ptr_time_struct->rtc_hours);
            ASSERT(RTC_HOUR12_CHECK(reg));
            ASSERT(RTC_AM_PM_HOUR12_CHECK(ptr_time_struct->am_pm_sel)); 
        } 
        else
        {
            ptr_time_struct->am_pm_sel = 0x00;
            ASSERT(RTC_HOUR24_CHECK(rtc_bcd_convert_byte(ptr_time_struct->rtc_hours)));
        }
        
        ASSERT(RTC_MINUTES_CHECK(rtc_bcd_convert_byte(ptr_time_struct->rtc_minutes)));
        ASSERT(RTC_SECONDS_CHECK(rtc_bcd_convert_byte(ptr_time_struct->rtc_seconds)));
    }
  
    /* Check the input parameters format */
    if (format_flag != RTC_FORMAT_BIN)
    {
        reg = (((uint32_t)(ptr_time_struct->rtc_hours) << 16) | ((uint32_t)(ptr_time_struct->rtc_minutes) << 8) | \
              ((uint32_t)ptr_time_struct->rtc_seconds) | ((uint32_t)(ptr_time_struct->am_pm_sel) << 16)); 
    }
    else
    {
        reg = (uint32_t)(((uint32_t)rtc_byte_convert_bcd(ptr_time_struct->rtc_hours) << 16) | \
                    ((uint32_t)rtc_byte_convert_bcd(ptr_time_struct->rtc_minutes) << 8) | \
                    ((uint32_t)rtc_byte_convert_bcd(ptr_time_struct->rtc_seconds)) | \
                    (((uint32_t)ptr_time_struct->am_pm_sel) << 16));
    } 

    /* Set Initialization mode */
    if (rtc_init_mode_enter() == ERROR)
    {
        status = ERROR;
    } 
    else
    {
        /* Set the RTC_TIME register */
        RTC->TIME = (uint32_t)(reg & RTC_TIME_RESERVED_MASK);

        /* Exit Initialization mode */
        __RTC_INIT_MODE_EXIT(); 

        /* If RTC_CTR_DAR bit = 0, wait for synchro else this check is not needed */
        if ((RTC->CTR & RTC_CTR_DAR) == RESET)
        {
            if (rtc_synchro_wait() == ERROR)
            {
                status = ERROR;
            }
            else
            {
                status = SUCCESS;
            }
        }       
        else
        {
            status = SUCCESS;
        }
  
    }
    
    return status;
}

/**
  * @fn void rtc_time_struct_init(rtc_time_t* ptr_time_struct)
  * @brief  Fill each rtc ptr_time_struct member with its default value (00h: 00min: 00sec).          
  * @param  ptr_time_struct: pointer to a rtc_time_t structure which will be initialized.
  * @return None.
  */
void rtc_time_struct_init(rtc_time_t* ptr_time_struct)
{
    /* Time = 00h:00min:00sec */
    ptr_time_struct->am_pm_sel = RTC_AM_HOUR12;
    ptr_time_struct->rtc_hours = 0;
    ptr_time_struct->rtc_minutes = 0;
    ptr_time_struct->rtc_seconds = 0; 
}

/**
  * @fn void rtc_time_get(uint32_t format_flag, rtc_time_t* ptr_time_struct)
  * @brief  Get the RTC current Time.
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_time_struct: pointer to a rtc_time_t structure that will contain the returned current time configuration.
  * @return None.
  */
void rtc_time_get(uint32_t format_flag, rtc_time_t* ptr_time_struct)
{
    uint32_t reg = 0;

    /* Check the parameters */
    ASSERT(RTC_FORMAT_CHECK(format_flag));

    /* Get the RTC_TIME register */
    reg = (uint32_t)(RTC->TIME & RTC_TIME_RESERVED_MASK); 
  
    /* Fill the structure fields with the read parameters */
    ptr_time_struct->rtc_hours = (uint8_t)((reg & (RTC_TIME_HORTEN | RTC_TIME_HORUNT)) >> 16);
    ptr_time_struct->rtc_minutes = (uint8_t)((reg & (RTC_TIME_MINTEN | RTC_TIME_MINUNT)) >>8);
    ptr_time_struct->rtc_seconds = (uint8_t)(reg & (RTC_TIME_SECTEN | RTC_TIME_SECUNT));
    ptr_time_struct->am_pm_sel = (uint8_t)((reg & (RTC_TIME_PM)) >> 16);  
    
    /* Check the input parameters format */
    if (format_flag == RTC_FORMAT_BIN)
    {
        /* Convert the structure parameters to Binary format */
        ptr_time_struct->rtc_hours = (uint8_t)rtc_bcd_convert_byte(ptr_time_struct->rtc_hours);
        ptr_time_struct->rtc_minutes = (uint8_t)rtc_bcd_convert_byte(ptr_time_struct->rtc_minutes);
        ptr_time_struct->rtc_seconds = (uint8_t)rtc_bcd_convert_byte(ptr_time_struct->rtc_seconds);
    }
}

/**
  * @fn uint32_t rtc_subsecond_get(void)
  * @brief  Gets the RTC current calendar subseconds value.
  * @param  None.
  * @return RTC current calendar subseconds value.
  */
uint32_t rtc_subsecond_get(void)
{
    uint32_t reg = 0;
  
    /* Get subseconds values from the correspondent registers */
    reg = (uint32_t)(RTC->SSEC);
  
    /* Read DATE register to unfroze calendar registers */
    (void) (RTC->DATE);
  
    return (reg);
}

/**
  * @fn error_status_t rtc_date_set(uint32_t format_flag, rtc_date_t* ptr_date_struct)
  * @brief  Set the RTC current date. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_date_struct: pointer to a rtc_date_t structure that contains the date configuration information for the RTC.
  * @return Date setting status: SUCCESS or ERROR.
  */
error_status_t rtc_date_set(uint32_t format_flag, rtc_date_t* ptr_date_struct)
{
    uint32_t reg = 0;
    error_status_t status = ERROR;
  
    ASSERT(RTC_FORMAT_CHECK(format_flag));

    if ((format_flag == RTC_FORMAT_BIN) && ((ptr_date_struct->rtc_month & 0x10) == 0x10))
    {
        ptr_date_struct->rtc_month = (ptr_date_struct->rtc_month & (uint32_t)~(0x10)) + 0x0A;
    }  
    if (format_flag == RTC_FORMAT_BIN)
    {
        ASSERT(RTC_YEAR_CHECK(ptr_date_struct->rtc_year));
        ASSERT(MONTH_CHECK(ptr_date_struct->rtc_month));
        ASSERT(DATE_CHECK(ptr_date_struct->rtc_date));
    }
    else
    {
        ASSERT(RTC_YEAR_CHECK(rtc_bcd_convert_byte(ptr_date_struct->rtc_year)));
        reg = rtc_bcd_convert_byte(ptr_date_struct->rtc_month);
        ASSERT(MONTH_CHECK(reg));
        reg = rtc_bcd_convert_byte(ptr_date_struct->rtc_date);
        ASSERT(DATE_CHECK(reg));
    }
    ASSERT(WEEKDAY_CHECK(ptr_date_struct->rtc_weekday));

    /* Check the input parameters format */
    if (format_flag != RTC_FORMAT_BIN)
    {
        reg = ((((uint32_t)ptr_date_struct->rtc_year) << 16) | \
              (((uint32_t)ptr_date_struct->rtc_month) << 8) | \
              ((uint32_t)ptr_date_struct->rtc_date) | \
              (((uint32_t)ptr_date_struct->rtc_weekday) << 13)); 
    }  
    else
    {
        reg = (((uint32_t)rtc_byte_convert_bcd(ptr_date_struct->rtc_year) << 16) | \
              ((uint32_t)rtc_byte_convert_bcd(ptr_date_struct->rtc_month) << 8) | \
              ((uint32_t)rtc_byte_convert_bcd(ptr_date_struct->rtc_date)) | \
              ((uint32_t)ptr_date_struct->rtc_weekday << 13));
    }

    /* Set Initialization mode */
    if (rtc_init_mode_enter() == ERROR)
    {
        status = ERROR;
    } 
    else
    {
        /* Set the RTC_DATE register */
        RTC->DATE = (uint32_t)(reg & RTC_DATE_RESERVED_MASK);
    
        /* Exit Initialization mode */
        __RTC_INIT_MODE_EXIT(); 
    
        /* If RTC_CTR_DAR bit = 0, wait for synchro else this check is not needed */
        if ((RTC->CTR & RTC_CTR_DAR) == RESET)
        {
            if (rtc_synchro_wait() == ERROR)
            {
                status = ERROR;
            }
            else
            {
                status = SUCCESS;
            }
        }
        else
        {
            status = SUCCESS;
        }
    }

    return status;
}

/**
  * @fn void rtc_date_struct_init(rtc_date_t* ptr_date_struct)
  * @brief  Fills each rtc_date_struct member with its default value (Monday, January 01 xx00).          
  * @param  ptr_date_struct: pointer to a rtc_date_t structure which will be initialized.
  * @return None.
  */
void rtc_date_struct_init(rtc_date_t* ptr_date_struct)
{
    /* Monday, January 01 xx00 */
    ptr_date_struct->rtc_weekday = WEEKDAY_MONDAY;
    ptr_date_struct->rtc_date = 1;
    ptr_date_struct->rtc_month = MONTH_JANUARY;
    ptr_date_struct->rtc_year = 0;
}

/**
  * @fn void rtc_date_get(uint32_t format_flag, rtc_date_t* ptr_date_struct)
  * @brief  Get the RTC current date.
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_date_struct: pointer to a rtc_date_t structure that will contain the returned current date configuration.
  * @return None
  */
void rtc_date_get(uint32_t format_flag, rtc_date_t* ptr_date_struct)
{
    uint32_t reg = 0;

    ASSERT(RTC_FORMAT_CHECK(format_flag));
  
    /* Get the RTC_TIME register */
    reg = (uint32_t)(RTC->DATE & RTC_DATE_RESERVED_MASK); 

    /* Fill the structure fields with the read parameters */
    ptr_date_struct->rtc_year = (uint8_t)((reg & (RTC_DATE_YTEN | RTC_DATE_YUNT)) >> 16);
    ptr_date_struct->rtc_month = (uint8_t)((reg & (RTC_DATE_MTEN | RTC_DATE_MUNT)) >> 8);
    ptr_date_struct->rtc_date = (uint8_t)(reg & (RTC_DATE_DTEN | RTC_DATE_DUNT));
    ptr_date_struct->rtc_weekday = (uint8_t)((reg & (RTC_DATE_WUNT)) >> 13);  

    /* Check the input parameters format */
    if (format_flag == RTC_FORMAT_BIN)
    {
        /* Convert the structure parameters to Binary format */
        ptr_date_struct->rtc_year = (uint8_t)rtc_bcd_convert_byte(ptr_date_struct->rtc_year);
        ptr_date_struct->rtc_month = (uint8_t)rtc_bcd_convert_byte(ptr_date_struct->rtc_month);
        ptr_date_struct->rtc_date = (uint8_t)rtc_bcd_convert_byte(ptr_date_struct->rtc_date);
        ptr_date_struct->rtc_weekday = (uint8_t)(ptr_date_struct->rtc_weekday);   
    }
}

/**
  * @fn void rtc_alarm_set(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct)
  * @brief  Set the specified RTC Alarm. The Alarm register can only be written when the corresponding alarm is disabled
  *         (Use the rtc_alarm_enable_ctrl(DISABLE)). 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_alarm_struct: pointer to a rtc_alarm_t structure that contains the alarm configuration parameters.
  * @return None.
  */
void rtc_alarm_set(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct)
{
    uint32_t reg = 0;
  
    ASSERT(RTC_FORMAT_CHECK(format_flag));
    ASSERT(RTC_ALARM_MASK_CHECK(ptr_alarm_struct->alarm_mask));
    ASSERT(RTC_DATE_WEEKDAY_SEL_CHECK(ptr_alarm_struct->date_weekday_sel));

    if (format_flag == RTC_FORMAT_BIN)
    {
        if ((RTC->CTR & RTC_CTR_FMT12) != (uint32_t)RESET)
        {
            ASSERT(RTC_HOUR12_CHECK(ptr_alarm_struct->alarm_time.rtc_hours));
            ASSERT(RTC_AM_PM_HOUR12_CHECK(ptr_alarm_struct->alarm_time.am_pm_sel));
        } 
        else
        {
            ptr_alarm_struct->alarm_time.am_pm_sel = 0x00;
            ASSERT(RTC_HOUR24_CHECK(ptr_alarm_struct->alarm_time.rtc_hours));
        }
        ASSERT(RTC_MINUTES_CHECK(ptr_alarm_struct->alarm_time.rtc_minutes));
        ASSERT(RTC_SECONDS_CHECK(ptr_alarm_struct->alarm_time.rtc_seconds));
    
        if(ptr_alarm_struct->date_weekday_sel == RTC_DATE_WEEKDAY_SEL_DATE)
        {
            ASSERT(DATE_CHECK(ptr_alarm_struct->date_weekday));
        }
        else
        {
            ASSERT(WEEKDAY_CHECK(ptr_alarm_struct->date_weekday));
        }
    }
    else
    {
        if ((RTC->CTR & RTC_CTR_FMT12) != (uint32_t)RESET)
        {
            reg = rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_hours);
            ASSERT(RTC_HOUR12_CHECK(reg));
            ASSERT(RTC_AM_PM_HOUR12_CHECK(ptr_alarm_struct->alarm_time.am_pm_sel));
        } 
        else
        {
            ptr_alarm_struct->alarm_time.am_pm_sel = 0x00;
            ASSERT(RTC_HOUR24_CHECK(rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_hours)));
        }
        
        ASSERT(RTC_MINUTES_CHECK(rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_minutes)));
        ASSERT(RTC_SECONDS_CHECK(rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_seconds)));
    
        if(ptr_alarm_struct->date_weekday_sel == RTC_DATE_WEEKDAY_SEL_DATE)
        {
            reg = rtc_bcd_convert_byte(ptr_alarm_struct->date_weekday);
            ASSERT(DATE_CHECK(reg));    
        }
        else
        {
            reg = rtc_bcd_convert_byte(ptr_alarm_struct->date_weekday);
            ASSERT(WEEKDAY_CHECK(reg));      
        }    
    }
    
    /* Check the input parameters format */
    if (format_flag != RTC_FORMAT_BIN)
    {
        reg = (((uint32_t)(ptr_alarm_struct->alarm_time.rtc_hours) << 16) | \
              ((uint32_t)(ptr_alarm_struct->alarm_time.rtc_minutes) << 8) | \
              ((uint32_t)ptr_alarm_struct->alarm_time.rtc_seconds) | \
              ((uint32_t)(ptr_alarm_struct->alarm_time.am_pm_sel) << 16) | \
              ((uint32_t)(ptr_alarm_struct->date_weekday) << 24) | \
              ((uint32_t)ptr_alarm_struct->date_weekday_sel) | \
              ((uint32_t)ptr_alarm_struct->alarm_mask)); 
    }  
    else
    {
        reg = (((uint32_t)rtc_byte_convert_bcd(ptr_alarm_struct->alarm_time.rtc_hours) << 16) | \
              ((uint32_t)rtc_byte_convert_bcd(ptr_alarm_struct->alarm_time.rtc_minutes) << 8) | \
              ((uint32_t)rtc_byte_convert_bcd(ptr_alarm_struct->alarm_time.rtc_seconds)) | \
              ((uint32_t)(ptr_alarm_struct->alarm_time.am_pm_sel) << 16) | \
              ((uint32_t)rtc_byte_convert_bcd(ptr_alarm_struct->date_weekday) << 24) | \
              ((uint32_t)ptr_alarm_struct->date_weekday_sel) | \
              ((uint32_t)ptr_alarm_struct->alarm_mask)); 
    }

    /* Configure the Alarm register */
    RTC->ACFG1 = (uint32_t)reg;
}

/**
  * @fn void rtc_alarm_struct_init(rtc_alarm_t* ptr_alarm_struct)
  * @brief  Fill each rtc ptr_alarm_struct member with its default value (time  = 00h: 00mn: 00sec // Date = 1st day of 
  *         the month // Mask = all fields are not masked).
  * @param  ptr_alarm_struct: pointer to a @ref rtc_alarm_t structure which will be initialized.
  * @return None.
  */
void rtc_alarm_struct_init(rtc_alarm_t* ptr_alarm_struct)
{
    /* Alarm Time Settings : Time = 00h:00mn:00sec */
    ptr_alarm_struct->alarm_time.am_pm_sel = RTC_AM_HOUR12;
    ptr_alarm_struct->alarm_time.rtc_hours = 0;
    ptr_alarm_struct->alarm_time.rtc_minutes = 0;
    ptr_alarm_struct->alarm_time.rtc_seconds = 0;

    /* Alarm Date Settings : Date = 1st day of the month */
    ptr_alarm_struct->date_weekday_sel = RTC_DATE_WEEKDAY_SEL_DATE;
    ptr_alarm_struct->date_weekday = 1;

    /* Alarm Masks Settings : Mask =  all fields are not masked */
    ptr_alarm_struct->alarm_mask = RTC_ALARM_MASK_NONE;
}

/**
  * @fn void rtc_alarm_get(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct)
  * @brief  Get the RTC alarm value and masks.
  * @param  format_flag: It can be binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_alarm_struct: pointer to a rtc_alarm_t structure that will contains the output alarm configuration values.
  * @return None.
  */
void rtc_alarm_get(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct)
{
    uint32_t reg = 0;

    ASSERT(RTC_FORMAT_CHECK(format_flag));

    /* Get the RTC_ACFG1 register */
    reg = (uint32_t)(RTC->ACFG1);

    /* Fill the structure with the read parameters */
    ptr_alarm_struct->alarm_time.rtc_hours = (uint8_t)((reg & (RTC_ACFG1_HORTEN | RTC_ACFG1_HORUNT)) >> 16);
    ptr_alarm_struct->alarm_time.rtc_minutes = (uint8_t)((reg & (RTC_ACFG1_MINTEN | RTC_ACFG1_MINUNT)) >> 8);
    ptr_alarm_struct->alarm_time.rtc_seconds = (uint8_t)(reg & (RTC_ACFG1_SECTEN | RTC_ACFG1_SECUNT));
    ptr_alarm_struct->alarm_time.am_pm_sel = (uint8_t)((reg & RTC_ACFG1_PM) >> 16);
    ptr_alarm_struct->date_weekday = (uint8_t)((reg & (RTC_ACFG1_DTEN | RTC_ACFG1_DUNT)) >> 24);
    ptr_alarm_struct->date_weekday_sel = (uint8_t)(reg & RTC_ACFG1_WDSEL);
    ptr_alarm_struct->alarm_mask = reg & RTC_ALARM_MASK_ALL;

    if (format_flag == RTC_FORMAT_BIN)
    {
        ptr_alarm_struct->alarm_time.rtc_hours = rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_hours);
        ptr_alarm_struct->alarm_time.rtc_minutes = rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_minutes);
        ptr_alarm_struct->alarm_time.rtc_seconds = rtc_bcd_convert_byte(ptr_alarm_struct->alarm_time.rtc_seconds);
        ptr_alarm_struct->date_weekday = rtc_bcd_convert_byte(ptr_alarm_struct->date_weekday);
    }  
}

/**
  * @fn error_status_t rtc_alarm_enable_ctrl(enable_state_t enable_flag)
  * @brief  Enables or disables the specified RTC alarm. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  enable_flag: It can be: ENABLE or DISABLE.
  * @return Configuration status: SUCCESS or ERROR.
  */
error_status_t rtc_alarm_enable_ctrl(enable_state_t enable_flag)
{
    __IO uint32_t alarm_counter = 0x00;
    uint32_t alarm_status = 0x00;
    error_status_t status = ERROR;
    
    ASSERT(FUNCTIONAL_STATE_CHECK(enable_flag));

    /* Configure the Alarm state */
    if (enable_flag != DISABLE)
    {
        RTC->CTR |= RTC_CTR_ALRE;

        status = SUCCESS;    
    }
    else
    { 
        /* Disable the Alarm in RTC_CTR register */
        RTC->CTR &= ~RTC_CTR_ALRE;
   
        /* Wait till RTC ALR flag is set and if time out is reached exit */
        do
        {
            alarm_status = RTC->STS & RTC_STS_ALRWAF;
            alarm_counter++;  
        } while ((alarm_counter != RTC_INIT_MODE_TIMEOUT) && (alarm_status == 0x00));
    
        if ((RTC->STS & RTC_STS_ALRWAF) == RESET)
        {
            status = ERROR;
        } 
        else
        {
            status = SUCCESS;
        }        
    } 
  
    return status;
}

/**
  * @fn void rtc_daylight_saving_config(uint32_t save_time_value, uint32_t flag)
  * @brief  Adds or substract one hour from the current time. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  save_time_value: It can be one of the following values:
  *         @arg RTC_DAYLIGHT_SAVING_DEC1H(substract one hour)
  *         @arg RTC_DAYLIGHT_SAVING_INC1H(add one hour)
  * @param  flag: specifies the value to be written in the SAVEF bit. It can be one of the following values:
  *         @arg RTC_DAYLIGHT_SAVING_FLAG_RESET 
  *         @arg RTC_DAYLIGHT_SAVING_FLAG_SET
  * @return None.
  */
void rtc_daylight_saving_config(uint32_t save_time_value, uint32_t flag)
{
    ASSERT(RTC_DAYLIGHT_SAVING_CHECK(save_time_value));
    ASSERT(RTC_DAYLIGHT_SAVING_FLAG_CHECK(flag));
    
    MODIFY_REG(RTC->CTR, RTC_CTR_SAVEF, save_time_value | flag);
}

/**
  * @fn void rtc_output_config(uint32_t config_value, uint32_t config_polarity)
  * @brief  Configures the RTC output source. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  config_value: It can be one of the following values:
  *         @arg RTC_OUTPUT_SOURCE_DISABLE(rtc output clock suorce disable)
  *         @arg RTC_OUTPUT_SOURCE_ALARM(select alarm output clock suorce)
  *         @arg RTC_OUTPUT_SOURCE_WAKEUP(select wakeup output clock suorce)
  * @param  config_polarity: It can be one of the following values:
  *         @arg RTC_OUTPUT_POLARITY_High(output pin is high)                                          
  *         @arg RTC_OUTPUT_POLARITY_LOW(output pin is low)                        
  * @return None
  */
void rtc_output_config(uint32_t config_value, uint32_t config_polarity)
{
    ASSERT(RTC_OUTPUT_SOURCE_CHECK(config_value));
    ASSERT(RTC_OUTPUT_POLARITY_CHECK(config_polarity));
    
    MODIFY_REG(RTC->CTR, (RTC_CTR_OUTSRC | RTC_CTR_APOL), config_value | config_polarity);
}


/**
  * @fn void rtc_cali_output_config(uint32_t config_value)
  * @brief  Configures the calibration pinout (RTC_CTR_CALSRC) selection (1Hz or 512Hz). 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  config_value: It can be one of the following values:
  *         @arg RTC_CALI_OUTPUT_512HZ(regular waveform at 512Hz) 
  *         @arg RTC_CALI_OUTPUT_1HZ(regular waveform at 1Hz)
  * @return None
*/
void rtc_cali_output_config(uint32_t config_value)
{
    ASSERT(RTC_CALI_OUTPUT_CHECK(config_value));
  
    MODIFY_REG(RTC->CTR, RTC_CTR_CALSRC, config_value);
}

/**
  * @fn error_status_t rtc_swallow_config(uint32_t period_value,uint32_t insert_value, uint32_t swallow_value) 
  * @brief  Configures swallow rtc clock Settings.
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  period_value: It can be can be one of the following values:
  *         @arg RTC_CALI_PERIOD_32SECOND(calibration periode is 32s)
  *         @arg RTC_CALI_PERIOD_16SECOND(calibration periode is 16s)
  *         @arg RTC_CALI_PERIOD_8SECOND(calibartion periode is 8s)
  * @param  insert_value: It can be one of the following values:
  *         @arg RTC_CALI_INSERT_CLOCK_SET(Add one RTCCLK puls every 2**11 pulses)
  *         @arg RTC_CALI_INSERT_CLOCK_RESET(No RTCCLK pulses are added)
  * @param  swallow_value: Select the value of SWACLK[8:0] bits, value from 0 to 0x000001FF.
  * @return Configuration: SUCCESS or ERROR.
 */
error_status_t rtc_swallow_config(uint32_t period_value,uint32_t insert_value, uint32_t swallow_value)
{
    error_status_t status = ERROR;
    uint32_t counter = 0;

    ASSERT(RTC_CALI_PERIOD_CHECK(period_value));
    ASSERT(RTC_CALI_INSERT_CLOCK_CHECK(insert_value));
    ASSERT(RTC_SWALLOW_CLOCK_VALUE_CHECK(swallow_value));

    /* check if a calibration is pending */
    if ((RTC->STS & RTC_STS_CALBSY) != RESET)
    {
        /* wait until the Calibration is completed */
        while (((RTC->STS & RTC_STS_CALBSY) != RESET) && (counter != RTC_CALI_TIMEOUT))
        {
            counter++;
        }
    }

    /* check if the calibration pending is completed or if there is no calibration operation at all */
    if ((RTC->STS & RTC_STS_CALBSY) == RESET)
    {
        /* Configure the calibration settings */
        RTC->RTC_1SCAL = (uint32_t)((uint32_t)period_value | (uint32_t)insert_value | (uint32_t)swallow_value);

        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
  
    return status;
}

/**
  * @fn void rtc_time_recording_config(uint32_t edge_flag, enable_state_t enable_flag)
  * @brief  Configures the RTC recording functionality. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  edge_flag: specified the edge to generate time recording event. It can be one of the following values:
  *         @arg RTC_RECORD_RISING_EDGE(the time stamp event occurs on the rising edge)                                          
  *         @arg RTC_RECORD_FALLING_EDGE(the time stamp event occurs on the falling edge)
  * @param  enable_flag: It can be: ENABLE or DISABLE.
  * @return None.
  */     
void rtc_time_recording_config(uint32_t edge_flag, enable_state_t enable_flag)
{
    uint32_t temp = 0;

    ASSERT(RTC_RECORD_EDGE_CHECK(edge_flag));
    ASSERT(FUNCTIONAL_STATE_CHECK(enable_flag));

    /* Get the new configuration */
    if (enable_flag != DISABLE)
    {
        temp |= (uint32_t)(edge_flag | RTC_CTR_TRE);
    }
    else
    {
        temp |= (uint32_t)(edge_flag);
    }

    MODIFY_REG(RTC->CTR, (RTC_CTR_TRESEL | RTC_CTR_TRE), temp);
}

/**
  * @fn void rtc_time_recording_get(uint32_t format_flag, rtc_time_t* ptr_time_struct, rtc_date_t* ptr_date_struct)
  * @brief  Get the RTC time recording value and masks.
  * @param  format_flag: It can be one of the following values:
  *         @arg RTC_FORMAT_BIN(Binary data format) 
  *         @arg RTC_FORMAT_BCD(BCD data format)
  * @param  ptr_time_struct: pointer to a rtc_time_t structure that will contains the recording time values. 
  * @param  ptr_date_struct: pointer to a rtc_date_t structure that will contains the recording date values.     
  * @return None.
  */
void rtc_time_recording_get(uint32_t format_flag, rtc_time_t* ptr_time_struct, rtc_date_t* ptr_date_struct)
{
    uint32_t temp_time = 0;
    uint32_t temp_date = 0;

    ASSERT(RTC_FORMAT_CHECK(format_flag));

    /* Get the recording time and date registers values */
    temp_time = (uint32_t)(RTC->TR2 & RTC_TIME_RESERVED_MASK);
    temp_date = (uint32_t)(RTC->TR1 & RTC_DATE_RESERVED_MASK);

    /* Fill the Time structure fields with the read parameters */
    ptr_time_struct->rtc_hours = (uint8_t)((temp_time & (RTC_TIME_HORTEN | RTC_TIME_HORUNT)) >> 16);
    ptr_time_struct->rtc_minutes = (uint8_t)((temp_time & (RTC_TIME_MINTEN | RTC_TIME_MINUNT)) >> 8);
    ptr_time_struct->rtc_seconds = (uint8_t)(temp_time & (RTC_TIME_SECTEN | RTC_TIME_SECUNT));
    ptr_time_struct->am_pm_sel = (uint8_t)((temp_time & (RTC_TIME_PM)) >> 16);  

    /* Fill the Date structure fields with the read parameters */
    ptr_date_struct->rtc_year = 0;
    ptr_date_struct->rtc_month = (uint8_t)((temp_date & (RTC_DATE_MTEN | RTC_DATE_MUNT)) >> 8);
    ptr_date_struct->rtc_date = (uint8_t)(temp_date & (RTC_DATE_DTEN | RTC_DATE_DUNT));
    ptr_date_struct->rtc_weekday = (uint8_t)((temp_date & (RTC_DATE_WUNT)) >> 13);

    /* Check the input parameters format */
    if (format_flag == RTC_FORMAT_BIN)
    {
        /* Convert the Time structure parameters to Binary format */
        ptr_time_struct->rtc_hours = (uint8_t)rtc_bcd_convert_byte(ptr_time_struct->rtc_hours);
        ptr_time_struct->rtc_minutes = (uint8_t)rtc_bcd_convert_byte(ptr_time_struct->rtc_minutes);
        ptr_time_struct->rtc_seconds = (uint8_t)rtc_bcd_convert_byte(ptr_time_struct->rtc_seconds);

        /* Convert the Date structure parameters to Binary format */
        ptr_date_struct->rtc_month = (uint8_t)rtc_bcd_convert_byte(ptr_date_struct->rtc_month);
        ptr_date_struct->rtc_date = (uint8_t)rtc_bcd_convert_byte(ptr_date_struct->rtc_date);
        ptr_date_struct->rtc_weekday = (uint8_t)rtc_bcd_convert_byte(ptr_date_struct->rtc_weekday);
    }
}

/**
  * @fn void rtc_inbreak_filter_config(uint32_t set_value)
  * @brief  Configures the inbreak Filter.
  * @param  set_value: specifies the inbreak filter, it can be one of the following values:
  *         @arg RTC_INBREAK_FILTER_DISABLE(inbreak filter is disabled)
  *         @arg RTC_INBREAK_FILTER_2SAMPLE(inbreak is activated after 2 consecutive samples at the active level) 
  *         @arg RTC_INBREAK_FILTER_4SAMPLE(inbreak is activated after 4 consecutive samples at the active level) 
  *         @arg RTC_INBREAK_FILTER_8SAMPLE(inbreak is activated after 8 consecutive samples at the active level)   
  * @return None.
  */
void rtc_inbreak_filter_config(uint32_t set_value)
{
    ASSERT(RTC_INBREAK_FILTER_CHECK(set_value));
    
    MODIFY_REG(RTC->MF, RTC_MF_INBRKFLT, set_value);
}

/**
  * @fn void rtc_inbreak_sample_freq_config(uint32_t freq_vale)
  * @brief  Configures the inbreak sampling frequency.
  * @param  freq_vale: Specifies the inbreak sampling frequency, it can be one of the following values:
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV32768(each of the inbreak inputs are sampled with freq RTCCLK / 32768)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV16384(each of the inbreak inputs are sampled with freq RTCCLK / 16384)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV8192(each of the inbreak inputs are sampled with freq RTCCLK / 8192)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV4096(each of the inbreak inputs are sampled with freq RTCCLK / 4096)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV2048(each of the inbreak inputs are sampled with freq RTCCLK / 2048)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV1024(each of the inbreak inputs are sampled with freq RTCCLK / 1024)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV512(each of the inbreak inputs are sampled with freq RTCCLK / 512)
  *         @arg RTC_INBREAK_SAMPLE_FREQ_PDIV256(each of the inbreak inputs are sampled with freq RTCCLK / 256)                                                       
  * @return None.
  */
void rtc_inbreak_sample_freq_config(uint32_t freq_vale)
{
    ASSERT(RTC_INBREAK_SAMPLE_FREQ_CHECK(freq_vale));
    
    MODIFY_REG(RTC->MF, RTC_MF_INBRKFREQ, freq_vale);
}

/**
  * @fn void rtc_inbreak_precharge_duration(uint32_t set_value)
  * @brief  Configures the inbreak pins input precharge duration.
  * @param  set_value: it can be one of the following values:
  *         @arg RTC_INBREAK_PRECHARGE_1RTCCLK(inbreak pins are precharged before sampling during 1 RTCCLK cycle)
  *         @arg RTC_INBREAK_PRECHARGE_2RTCCLK(inbreak pins are precharged before sampling during 2 RTCCLK cycle) 
  *         @arg RTC_INBREAK_PRECHARGE_4RTCCLK(inbreak pins are precharged before sampling during 4 RTCCLK cycle) 
  *         @arg RTC_INBREAK_PRECHARGE_8RTCCLK(inbreak pins are precharged before sampling during 8 RTCCLK cycle)  
  * @return None.
  */
void rtc_inbreak_precharge_duration(uint32_t set_value)
{
    ASSERT(RTC_INBREAK_PRECHARGE_CHECK(set_value));

    MODIFY_REG(RTC->MF, RTC_MF_INBRKPRCH, set_value);
}

/**
  * @fn void rtc_output_type_config(uint32_t output_type)
  * @brief  Configures the RTC output pin mode. 
  * @param  output_type: specifies the RTC Output (PC13) pin mode. It can be one of the following values:
  *         @arg RTC_OUTPUT_OPEN_DRAIN(RTC output is configured in open drain mode)                                     
  *         @arg RTC_OUTPUT_PUSH_PULL(RTC output is configured in push pull mode)                                    
  * @return None.
  */
void rtc_output_type_config(uint32_t output_type)
{
    ASSERT(RTC_OUTPUT_TYPE_CHECK(output_type));
 
    MODIFY_REG(RTC->MF, RTC_MF_PC13DATA, output_type);
}

/**
  * @fn error_status_t rtc_adj_register_config(uint32_t second_flag, uint32_t subsecond_value)
  * @brief  Configures the adjustment(ADJ) register. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  second_flag: select to add or not 1 second to the time Calendar. It can be one of the following values:
  *         @arg RTC_ADJ_INC1S_SET(add one second to the clock calendar)
  *         @arg RTC_ADJ_INC1S_RESET(no effect)
  * @param  subsecond_value: It can be one any value from 0 to 0x7FFF.
  * @return Configuration status: SUCCESS or ERROR.
  */
error_status_t rtc_adj_register_config(uint32_t second_flag, uint32_t subsecond_value)
{
    error_status_t status = ERROR;
    uint32_t count = 0;

    ASSERT(RTC_ADJ_INC1S_CHECK(second_flag));
    ASSERT(RTC_ADJ_SSEC_CHECK(subsecond_value));
    
    /* Check if a Shift is pending */
    if ((RTC->STS & RTC_STS_SHF_BUSY) != RESET)
    {
        /* Wait until the shift is completed */
        while (((RTC->STS & RTC_STS_SHF_BUSY) != RESET) && (count != RTC_SHPF_TIMEOUT))
        {
            count++;
        }
    }

    /* Check if the Shift pending is completed or if there is no Shift operation at all */
    if ((RTC->STS & RTC_STS_SHF_BUSY) == RESET)
    {
        /* check if the reference clock detection is disabled */
        if((RTC->CTR & RTC_CTR_OPCLKEN) == RESET)
        {
            /* Configure the adjustment register */
            RTC->ADJ = (uint32_t)(uint32_t)(subsecond_value) | (uint32_t)(second_flag);
    
            if(rtc_synchro_wait() == ERROR)
            {
                status = ERROR;
            }
            else
            {
                status = SUCCESS;
            }
        }
        else
        {
            status = ERROR;
        }
    }
    else
    {
        status = ERROR;
    }
  
    return (error_status_t)(status);
}

/**
  * @fn static uint8_t rtc_byte_convert_bcd(uint8_t value)
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  value: Byte to be converted.
  * @return Converted byte
  */
static uint8_t rtc_byte_convert_bcd(uint8_t value)
{
    uint8_t bcd_high = 0;
  
    while (value >= 10)
    {
        bcd_high++;
        value -= 10;
    }
  
    return  ((uint8_t)(bcd_high << 4) | value);
}

/**
  * @fn static uint8_t rtc_bcd_convert_byte(uint8_t value)
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  value: BCD value to be converted.
  * @return Converted byte.
  */
static uint8_t rtc_bcd_convert_byte(uint8_t value)
{
    uint8_t temp = 0;
  
    temp = ((uint8_t)(value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (temp + (value & (uint8_t)0x0F));
}


/**
  * @}
  */ 

/**
  * @}
  */ 

