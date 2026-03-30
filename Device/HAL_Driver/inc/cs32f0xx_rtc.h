/**
  * @file    cs32f0xx_rtc.h  
  * @brief   This file contains all the functions prototypes for the RTC firmware 
  *          library. This is not available for CS32F036 devices.
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2020 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_RTC_H__
#define __CS32F0XX_RTC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */ 
  
/** @defgroup RTC_Exported_Constants
  * @{
  */


/** 
  * @struct rtc_init_t
  * @brief  RTC Init structures definition  
  */ 
typedef struct
{
    uint32_t hour_format;       //!< Specifies the RTC hour format                             
    uint32_t rtc_divider1;      //!< Specifies the RTC first pre-divider factor  lower than 0x7F                             
    uint32_t rtc_divider2;      //!< Specifies the RTC second pre-divider factor lower than 0x1FFF                             
}rtc_init_t;

/** 
  * @struct rtc_time_t
  * @brief  RTC Time structure definition  
  */
typedef struct
{
    uint8_t rtc_hours;          //!< Specifies the RTC hour, HourFormat_12 (0~11), HourFormat_24 (0~23)                      
    uint8_t rtc_minutes;        //!< Specifies the RTC minutes (0~59)                          
    uint8_t rtc_seconds;        //!< Specifies the RTC seconds (0~59)                        
    uint8_t am_pm_sel;          //!< Specifies the RTC AM/PM                        
}rtc_time_t; 

/** 
  * @struct rtc_date_t
  * @brief  RTC Date structure definition  
  */
typedef struct
{
    uint8_t rtc_weekday;        //!< Specifies weekday                        
    uint8_t rtc_month;          //!< Specifies month
    uint8_t rtc_date;           //!< Specifies date (value in the 1-31)
    uint8_t rtc_year;           //!< Specifies year (value in the 0-99)                         
}rtc_date_t;

/**
  * @struct rtc_alarm_t
  * @brief  RTC Alarm structure definition  
  */
typedef struct
{
    rtc_time_t alarm_time;      //!< Specifies the RTC alarm time members
    uint32_t alarm_mask;        //!< Specifies the RTC alarm masks                                     
    uint32_t date_weekday_sel;  //!< Specifies the RTC alarm is on date or weekday  
    uint8_t date_weekday;       //!< Specifies the RTC alarm date/weekday          
    uint8_t reserved0;
    uint16_t reserved1;
}rtc_alarm_t;

/** 
  * @brief RTC hour format definition  
  */ 
#define RTC_HOUR_FORMAT_24                          ((uint32_t)0x00000000)  //!< Specifies the RTC Hour Format ,vaule in 0~23
#define RTC_HOUR_FORMAT_12                          ((uint32_t)0x00000040)  //!< Specifies the RTC Hour Format, vaule in 0~11

#define RTC_HOUR_FORMAT_CHECK(format)               (((format) == RTC_HOUR_FORMAT_12) || ((format) == RTC_HOUR_FORMAT_24))

/** 
  * @brief check first pre-divider factor
  */ 
#define RTC_PDIV1_CHECK(prediv)                     ((prediv) <= 0x7F)      //!< pre-divider factor
 
/** 
  * @brief check second pre-divider factor
  */ 
#define RTC_PDIV2_CHECK(prediv)                     ((prediv) <= 0x7FFF)    //!< pre-divider factor

/** 
  * @brief check rtc time definitions 
  */ 
#define RTC_HOUR12_CHECK(hour)                      (((hour) > 0) && ((hour) <= 12)) 
#define RTC_HOUR24_CHECK(hour)                      ((hour) <= 23)                   
#define RTC_MINUTES_CHECK(minutes)                  ((minutes) <= 59)                 
#define RTC_SECONDS_CHECK(seconds)                  ((seconds) <= 59)                 

/** 
  * @brief rtc AM/PM defintion 
  */ 
#define RTC_AM_HOUR12                               ((uint8_t)0x00)         //!< select AM
#define RTC_PM_HOUR12                               ((uint8_t)0x40)         //!< select PM

#define RTC_AM_PM_HOUR12_CHECK(pm)                  (((pm) == RTC_AM_HOUR12) || ((pm) == RTC_PM_HOUR12))

/** 
  * @brief year check
  */ 
#define RTC_YEAR_CHECK(year)                        ((year) <= 99)          //!< check year 

/** @defgroup Month_Date_Definitions 
  * @{
  */ 
#define MONTH_JANUARY                               ((uint8_t)0x01)         //!< January
#define MONTH_FEBRUARY                              ((uint8_t)0x02)         //!< February
#define MONTH_MARCH                                 ((uint8_t)0x03)         //!< March
#define MONTH_APRIL                                 ((uint8_t)0x04)         //!< April
#define MONTH_MAY                                   ((uint8_t)0x05)         //!< May
#define MONTH_JUNE                                  ((uint8_t)0x06)         //!< Jun
#define MONTH_JULY                                  ((uint8_t)0x07)         //!< July
#define MONTH_AUGUST                                ((uint8_t)0x08)         //!< August
#define MONTH_SEPTEMBER                             ((uint8_t)0x09)         //!< September 
#define MONTH_OCTOBER                               ((uint8_t)0x10)         //!< October
#define MONTH_NOVEMBER                              ((uint8_t)0x11)         //!< November
#define MONTH_DECEMBER                              ((uint8_t)0x12)         //!< December

#define MONTH_CHECK(month)                          (((month) >= 1) && ((month) <= 12))

#define DATE_CHECK(date)                            (((date) >= 1) && ((date) <= 31))

/**
  * @}
  */ 

/** @defgroup WeekDay_Definitions 
  * @{
  */   
#define	WEEKDAY_MONDAY                              ((uint8_t)0x01)         //!< Monday
#define	WEEKDAY_TUESDAY                             ((uint8_t)0x02)         //!< Tuesday
#define	WEEKDAY_WEDNESDAY                           ((uint8_t)0x03)         //!< Wednesday
#define	WEEKDAY_THURSDAY                            ((uint8_t)0x04)         //!< Thursday
#define	WEEKDAY_FRIDAY                              ((uint8_t)0x05)         //!< Friday
#define	WEEKDAY_SATURDAY                            ((uint8_t)0x06)         //!< Saturday
#define	WEEKDAY_SUNDAY                              ((uint8_t)0x07)         //!< Sunday

#define WEEKDAY_CHECK(weekday)                      (((weekday) == WEEKDAY_MONDAY)    || ((weekday) == WEEKDAY_TUESDAY)  || \
                                                     ((weekday) == WEEKDAY_WEDNESDAY) || ((weekday) == WEEKDAY_THURSDAY) || \
                                                     ((weekday) == WEEKDAY_FRIDAY)    || ((weekday) == WEEKDAY_SATURDAY) || \
                                                     ((weekday) == WEEKDAY_SUNDAY))
/**
  * @}
  */ 

/** 
  * @brief rtc date/weekday select definitions
  */ 
#define RTC_DATE_WEEKDAY_SEL_DATE                   ((uint32_t)0x00000000)  //!<select date 
#define RTC_DATE_WEEKDAY_SEL_WEEKDAY                ((uint32_t)0x40000000)  //!<select weekday 

#define RTC_DATE_WEEKDAY_SEL_CHECK(sel)             (((sel) == RTC_DATE_WEEKDAY_SEL_DATE) || \
                                                     ((sel) == RTC_DATE_WEEKDAY_SEL_WEEKDAY))
                                            
/** 
  * @brief rtc alarm mask Definitions
  */ 
#define RTC_ALARM_MASK_NONE                         ((uint32_t)0x00000000)  //!< all fields are not masked 
#define RTC_ALARM_MASK_DATE_WEEKDAY                 ((uint32_t)0x80000000)  //!< date_weekday field is masked
#define RTC_ALARM_MASK_HOURS                        ((uint32_t)0x00800000)  //!< hours field is masked
#define RTC_ALARM_MASK_MINUTES                      ((uint32_t)0x00008000)  //!< minutes field is masked
#define RTC_ALARM_MASK_SECONDS                      ((uint32_t)0x00000080)  //!< seconds field is masked
#define RTC_ALARM_MASK_ALL                          ((uint32_t)0x80808080)  //!< all fields are masked 

#define RTC_ALARM_MASK_CHECK(mask)                  (((mask) & 0x7F7F7F7F) == (uint32_t)RESET)

/** 
  * @brief rtc alarm subseconds masks definitions.
  */ 
#define RTC_SUB_SECOND_MASK_ALL                     ((uint8_t)0x00)         //!< RTC_SSEC All Alarm  SSEC fields are masked. 
#define RTC_SUB_SECOND_MASK_SSEC14_1                ((uint8_t)0x01)         //!< SSEC[14:1] are don't care, Only SSEC[0] valid.                                                                
#define RTC_SUB_SECOND_MASK_SSEC14_2                ((uint8_t)0x02)         //!< SSEC[14:2] are don't care, Only SSEC[1:0]valid.                                                                 
#define RTC_SUB_SECOND_MASK_SSEC14_3                ((uint8_t)0x03)         //!< SSEC[14:3] are don't care, Only SSEC[2:0]valid.                                                                
#define RTC_SUB_SECOND_MASK_SSEC14_4                ((uint8_t)0x04)         //!< SSEC[14:4] are don't care, Only SSEC[3:0]valid.                                                                 
#define RTC_SUB_SECOND_MASK_SSEC14_5                ((uint8_t)0x05)         //!< SSEC[14:5] are don't care, Only SSEC[4:0]valid.                                                              
#define RTC_SUB_SECOND_MASK_SSEC14_6                ((uint8_t)0x06)         //!< SSEC[14:6] are don't care, Only SSEC[5:0]valid.                                                              
#define RTC_SUB_SECOND_MASK_SSEC14_7                ((uint8_t)0x07)         //!< SSEC[14:7] are don't care, Only SSEC[6:0]valid.                                                               
#define RTC_SUB_SECOND_MASK_SSEC14_8                ((uint8_t)0x08)         //!< SSEC[14:8] are don't care, Only SSEC[7:0]valid.                                                               
#define RTC_SUB_SECOND_MASK_SSEC14_9                ((uint8_t)0x09)         //!< SSEC[14:9] are don't care, Only SSEC[8:0]valid.                                                             
#define RTC_SUB_SECOND_MASK_SSEC14_10               ((uint8_t)0x0A)         //!< SSEC[14:10] are don't care, Only SSEC[9:0]valid.                                                               
#define RTC_SUB_SECOND_MASK_SSEC14_11               ((uint8_t)0x0B)         //!< SSEC[14:11] are don't care, Only SSEC[10:0]valid.                                                              
#define RTC_SUB_SECOND_MASK_SSEC14_12               ((uint8_t)0x0C)         //!< SSEC[14:12] are don't care, Only SSEC[11:0]valid.                                                                
#define RTC_SUB_SECOND_MASK_SSEC14_13               ((uint8_t)0x0D)         //!< SSEC[14:13] are don't care, Only SSEC[12:0]valid.                                                                
#define RTC_SUB_SECOND_MASK_SSEC14                  ((uint8_t)0x0E)         //!< SSEC[14] are don't care, Only SSEC[13:0]valid.                                                               
#define RTC_SUB_SECOND_MASK_NONE                    ((uint8_t)0x0F)         //!< SSEC[14:0] valid and must match to activate alarm. 

/** 
  * @brief rtc Time recording edge select
  */ 
#define RTC_RECORD_RISING_EDGE                      ((uint32_t)0x00000000)  //!< select rising edge triggle
#define RTC_RECORD_FALLING_EDGE                     ((uint32_t)0x00000008)  //!< select falling edge triggle

#define RTC_RECORD_EDGE_CHECK(edge)                 (((edge) == RTC_RECORD_RISING_EDGE) || ((edge) == RTC_RECORD_FALLING_EDGE))

/** 
  * @brief rtc output source selection definitions
  */ 
#define RTC_OUTPUT_SOURCE_DISABLE                   ((uint32_t)0x00000000)  //!< rtc output clock suorce disable
#define RTC_OUTPUT_SOURCE_ALARM                     ((uint32_t)0x00200000)  //!< select alarm output clock suorce
        
#define RTC_OUTPUT_SOURCE_CHECK(output)             (((output) == RTC_OUTPUT_SOURCE_DISABLE) || \
                                                     ((output) == RTC_OUTPUT_SOURCE_ALARM))

/**   
  * @brief rtc output polarity definitions
  */ 
#define RTC_OUTPUT_POLARITY_HIGH                    ((uint32_t)0x00000000)  //!< set alarm polarity output high
#define RTC_OUTPUT_POLARITY_LOW                     ((uint32_t)0x00100000)  //!< set alarm polarity output low

#define RTC_OUTPUT_POLARITY_CHECK(pol)              (((pol) == RTC_OUTPUT_POLARITY_HIGH) || ((pol) == RTC_OUTPUT_POLARITY_LOW))

/** 
  * @brief rtc calibration output selection definitions
  */ 
#define RTC_CALI_OUTPUT_512HZ                       ((uint32_t)0x00000000)  //!< select calibration output 512 HZ
#define RTC_CALI_OUTPUT_1HZ                         ((uint32_t)0x00080000)  //!< select calibration output 1 HZ
    
#define RTC_CALI_OUTPUT_CHECK(output)               (((output) == RTC_CALI_OUTPUT_512HZ) || ((output) == RTC_CALI_OUTPUT_1HZ))

/** 
  * @brief rtc calibration period definitions 
  */ 
#define RTC_CALI_PERIOD_32SECOND                    ((uint32_t)0x00000000)  //!< if RTCCLK = 32768 Hz, then the calibation period is 32s, else 2exp20 RTCCLK seconds. 
#define RTC_CALI_PERIOD_16SECOND                    ((uint32_t)0x00002000)  //!< if RTCCLK = 32768 Hz, then the calibation period is 16s, else 2exp19 RTCCLK seconds.                                                              
#define RTC_CALI_PERIOD_8SECOND                     ((uint32_t)0x00004000)  //!< if RTCCLK = 32768 Hz, then the claibation period is 8s, else 2exp18 RTCCLK seconds. 

#define RTC_CALI_PERIOD_CHECK(period)               (((period) == RTC_CALI_PERIOD_32SECOND) || \
                                                     ((period) == RTC_CALI_PERIOD_16SECOND) || \
                                                     ((period) == RTC_CALI_PERIOD_8SECOND))                                         

/**
  * @brief rtc insert rtc clock definitions 
  */ 
#define RTC_CALI_INSERT_CLOCK_SET                   ((uint32_t)0x00008000)  //!< set Insert RTC clock bit                                                                                                                             
#define RTC_CALI_INSERT_CLOCK_RESET                 ((uint32_t)0x00000000)  //!< reset Insert RTC clock bit

#define RTC_CALI_INSERT_CLOCK_CHECK(plus)           (((plus) == RTC_CALI_INSERT_CLOCK_SET) || \
                                                     ((plus) == RTC_CALI_INSERT_CLOCK_RESET))

/** 
  * @brief swallow RTC clock value check
  */ 
#define  RTC_SWALLOW_CLOCK_VALUE_CHECK(value)       ((value) <= 0x000001FF)  //!< check swallow clock value

/**  
  * @brief rtc daylight saving definitions
  */ 
#define RTC_DAYLIGHT_SAVING_DEC1H                   ((uint32_t)0x00020000)  //!< select winter time (sub one hour)
#define RTC_DAYLIGHT_SAVING_INC1H                   ((uint32_t)0x00010000)  //!< select summer time (add one hour) 

#define RTC_DAYLIGHT_SAVING_CHECK(saving)           (((saving) == RTC_DAYLIGHT_SAVING_DEC1H) || \
                                                     ((saving) == RTC_DAYLIGHT_SAVING_INC1H))

#define RTC_DAYLIGHT_SAVING_FLAG_RESET              ((uint32_t)0x00000000)  //!< no effect
#define RTC_DAYLIGHT_SAVING_FLAG_SET                ((uint32_t)0x00040000)  //!< select daylight-saving

#define RTC_DAYLIGHT_SAVING_FLAG_CHECK(operation)   (((operation) == RTC_DAYLIGHT_SAVING_FLAG_RESET) || \
                                                     ((operation) == RTC_DAYLIGHT_SAVING_FLAG_SET))               
/** 
  * @brief rtc inbreak filter definitions
  */ 
#define RTC_INBREAK_FILTER_DISABLE                  ((uint32_t)0x00000000)  //!< inbreak filter is disabled 
#define RTC_INBREAK_FILTER_2SAMPLE                  ((uint32_t)0x00000800)  //!< filter is activated after 2 consecutive samples.                                                          
#define RTC_INBREAK_FILTER_4SAMPLE                  ((uint32_t)0x00001000)  //!< filter is activated after 4 consecutive samples.                                                          
#define RTC_INBREAK_FILTER_8SAMPLE                  ((uint32_t)0x00001800)  //!< filter is activated after 8 consecutive samples.
                                                         
#define RTC_INBREAK_FILTER_CHECK(filter)            (((filter) == RTC_INBREAK_FILTER_DISABLE) || \
                                                     ((filter) == RTC_INBREAK_FILTER_2SAMPLE) || \
                                                     ((filter) == RTC_INBREAK_FILTER_4SAMPLE) || \
                                                     ((filter) == RTC_INBREAK_FILTER_8SAMPLE))

/**  
  * @brief rtc inbreak sampling frequencies definitions
  */ 
#define RTC_INBREAK_SAMPLE_FREQ_PDIV32768           ((uint32_t)0x00000000)  //!< sampling frequency =  RTCCLK / 32768                                                                      
#define RTC_INBREAK_SAMPLE_FREQ_PDIV16384           ((uint32_t)0x00000100)  //!< sampling frequency =  RTCCLK / 16384                                                                      
#define RTC_INBREAK_SAMPLE_FREQ_PDIV8192            ((uint32_t)0x00000200)  //!< sampling frequency =  RTCCLK / 8192                                                                      
#define RTC_INBREAK_SAMPLE_FREQ_PDIV4096            ((uint32_t)0x00000300)  //!< sampling frequency =  RTCCLK / 4096                                                                   
#define RTC_INBREAK_SAMPLE_FREQ_PDIV2048            ((uint32_t)0x00000400)  //!< sampling frequency =  RTCCLK / 2048                                                                     
#define RTC_INBREAK_SAMPLE_FREQ_PDIV1024            ((uint32_t)0x00000500)  //!< sampling frequency =  RTCCLK / 1024                                                                    
#define RTC_INBREAK_SAMPLE_FREQ_PDIV512             ((uint32_t)0x00000600)  //!< sampling frequency =  RTCCLK / 512                                                                     
#define RTC_INBREAK_SAMPLE_FREQ_PDIV256             ((uint32_t)0x00000700)  //!< sampling frequency =  RTCCLK / 256                                                                     

#define RTC_INBREAK_SAMPLE_FREQ_CHECK(freq)         (((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV32768) || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV16384) || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV8192)  || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV4096)  || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV2048)  || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV1024)  || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV512)   || \
                                                     ((freq) == RTC_INBREAK_SAMPLE_FREQ_PDIV256))
                                          
/**  
  * @brief rtc inbreak precharge duration definitions
  */ 
#define RTC_INBREAK_PRECHARGE_1RTCCLK               ((uint32_t)0x00000000)  //!< pre_charged before 1 RTCCLK cycle duration                                                                        
#define RTC_INBREAK_PRECHARGE_2RTCCLK               ((uint32_t)0x00002000)  //!< pre_charged before 2 RTCCLK cycle duration                                                                       
#define RTC_INBREAK_PRECHARGE_4RTCCLK               ((uint32_t)0x00004000)  //!< pre_charged before 4 RTCCLK cycle duration                                                                  
#define RTC_INBREAK_PRECHARGE_8RTCCLK               ((uint32_t)0x00006000)  //!< pre_charged before 8 RTCCLK cycle duration
                                                                       
#define RTC_INBREAK_PRECHARGE_CHECK(duration)       (((duration) == RTC_INBREAK_PRECHARGE_1RTCCLK) || \
                                                     ((duration) == RTC_INBREAK_PRECHARGE_2RTCCLK) || \
                                                     ((duration) == RTC_INBREAK_PRECHARGE_4RTCCLK) || \
                                                     ((duration) == RTC_INBREAK_PRECHARGE_8RTCCLK))                                                                                             

/** 
  * @brief rtc inbreak trigger definitions
  */
#define RTC_INBREAK1_TRG                            RTC_MF_INBRK1TRG        //!< inbreak pin 1 trigger 
#define RTC_INBREAK2_TRG                            RTC_MF_INBRK2TRG        //!< inbreak pin 2 trigger

/** 
  * @brief rtc output type definitions
  */ 
#define RTC_OUTPUT_OPEN_DRAIN                       ((uint32_t)0x00000000)  //!< output type open_drain
#define RTC_OUTPUT_PUSH_PULL                        ((uint32_t)0x00040000)  //!< output type push_pull
#define RTC_OUTPUT_TYPE_CHECK(type)                 (((type) == RTC_OUTPUT_OPEN_DRAIN) || ((type) == RTC_OUTPUT_PUSH_PULL))

/** 
  * @brief rtc increase one second definitions
  */ 
#define RTC_ADJ_INC1S_RESET                         ((uint32_t)0x00000000)  //!< no effect
#define RTC_ADJ_INC1S_SET                           ((uint32_t)0x80000000)  //!< add one second to the clock/calendar

#define RTC_ADJ_INC1S_CHECK(sel)                    (((sel) == RTC_ADJ_INC1S_RESET) || ((sel) == RTC_ADJ_INC1S_SET))

/** 
  * @brief rtc substract fraction of second value
  */ 
#define RTC_ADJ_SSEC_CHECK(fs)                      ((fs) <= 0x00007FFF)    //!<check substract a fraction of a second 

/** 
  * @brief rtc always on registers definitions
  */
#define RTC_AO_REGISTER0                            ((uint32_t)0x00000000)  //!< RTC always on register0
#define RTC_AO_REGISTER1                            ((uint32_t)0x00000001)  //!< RTC always on register1
#define RTC_AO_REGISTER2                            ((uint32_t)0x00000002)  //!< RTC always on register2
#define RTC_AO_REGISTER3                            ((uint32_t)0x00000003)  //! <RTC always on register3
#define RTC_AO_REGISTER4                            ((uint32_t)0x00000004)  //!< RTC always on register4

/**
  * @brief rtc BIN/DCB format definitions 
  */ 
#define RTC_FORMAT_BIN                              ((uint32_t)0x00000000)  //!< data format BIN
#define RTC_FORMAT_BCD                              ((uint32_t)0x00000001)  //!< data format BCD

#define RTC_FORMAT_CHECK(format)                    (((format) == RTC_FORMAT_BIN) || ((format) == RTC_FORMAT_BCD))

/** 
  * @brief rtc function register definitions
  */ 
#define RTC_ENABLE_REG_DIR_ACCESS                   RTC->CTR                //!< direct access register   
#define RTC_ENABLE_REG_CAL_OUTPUT                   RTC->CTR                //!< calibration output         
#define RTC_ENABLE_REG_INBREAK1                     RTC->MF                 //!< inbreak1 detection    
#define RTC_ENABLE_REG_INBREAK2                     RTC->MF                 //!< inbreak2 detection     
#define RTC_ENABLE_REG_INBREAK_REC                  RTC->MF                 //!< recording on inbreak detection event 
#define RTC_ENABLE_REG_PULLUP_DIS                   RTC->MF                 //!< inbreak disable pull up  

/** 
  * @brief rtc function bit definitions
  */ 
#define RTC_ENABLE_BIT_DIR_ACCESS                   RTC_CTR_DAR             //!< direct access register   
#define RTC_ENABLE_BIT_CAL_OUTPUT                   RTC_CTR_CALOE           //!< calibration output         
#define RTC_ENABLE_BIT_INBREAK1                     RTC_MF_INBRK1E          //!< inbreak1 detection    
#define RTC_ENABLE_BIT_INBREAK2                     RTC_MF_INBRK2E          //!< inbreak2 detection     
#define RTC_ENABLE_BIT_INBREAK_REC                  RTC_MF_INBRKTR          //!< recording on inbreak detection event 
#define RTC_ENABLE_BIT_PULLUP_DIS                   RTC_MF_INBRKPUDIS       //!< inbreak disable pull up 

/** 
  * @brief rtc interrupt source register definitions
  */ 
#define RTC_INTR_REG_TIME_RECORD                    RTC->CTR                //!< time recording interrupt enable
#define RTC_INTR_REG_ALARM                          RTC->CTR                //!< alarm interrupt enable
#define RTC_INTR_REG_INBREAK1                       RTC->MF                 //!< inbreak interrupt enable
#define RTC_INTR_REG_INBREAK2                       RTC->MF                 //!< inbreak interrupt enable

/** 
  * @brief rtc interrupt source bit definitions
  */     
#define RTC_INTR_BIT_TIME_RECORD                    ((uint32_t)0x00008000)  //!< time recording interrupt enable
#define RTC_INTR_BIT_ALARM                          ((uint32_t)0x00001000)  //!< alarm interrupt enable
#define RTC_INTR_BIT_INBREAK1                       ((uint32_t)0x00000004)  //!< inbreak interrupt enable
#define RTC_INTR_BIT_INBREAK2                       ((uint32_t)0x00000004)  //!< inbreak interrupt enable 

/**  
  * @brief rtc flag register definitions
  */
#define RTC_FLAG_REG_DAYLIGHT_SAVING                RTC->CTR                //!< daylight saving flag          
#define RTC_FLAG_REG_CALBSY                         RTC->STS                //!< calibration busy flag
#define RTC_FLAG_REG_INBREAK2                       RTC->STS                //!< RTC_INBREAK2 detection flag
#define RTC_FLAG_REG_INBREAK1                       RTC->STS                //!< RTC_INBREAK1 detection flag
#define RTC_FLAG_REG_TSOV                           RTC->STS                //!< Time-stamp overflow flag
#define RTC_FLAG_REG_TIME_RECORD                    RTC->STS                //!< Time-stamp flag
#define RTC_FLAG_REG_ALARM                          RTC->STS                //!< alarm flag
#define RTC_FLAG_REG_INIT                           RTC->STS                //!< initialization mode enter flag
#define RTC_FLAG_REG_RS                             RTC->STS                //!< synchronization flag
#define RTC_FLAG_REG_INITS                          RTC->STS                //!< initialization status flag
#define RTC_FLAG_REG_SHF_BUSY                       RTC->STS                //!< shift busy flag

/**  
  * @brief rtc flag bit definitions
  */ 
#define RTC_FLAG_BIT_DAYLIGHT_SAVING                RTC_CTR_SAVEF           //!<  daylight saving flag              
#define RTC_FLAG_BIT_CALBSY                         RTC_STS_CALBSY          //!< calibration busy flag
#define RTC_FLAG_BIT_INBREAK2                       RTC_STS_TAMP2F          //!< RTC_INBREAK2 detection flag
#define RTC_FLAG_BIT_INBREAK1                       RTC_STS_TAMP1F          //!< RTC_INBREAK1 detection flag
#define RTC_FLAG_BIT_TSOV                           RTC_STS_TSOVF           //!< Time-stamp overflow flag
#define RTC_FLAG_BIT_TIME_RECORD                    RTC_STS_TSF             //!< Time-stamp flag
#define RTC_FLAG_BIT_ALARM                          RTC_STS_ALRF            //!< alarm flag
#define RTC_FLAG_BIT_INIT                           RTC_STS_INITF           //!< initialization mode enter flag
#define RTC_FLAG_BIT_RS                             RTC_STS_RSF             //!< synchronization flag
#define RTC_FLAG_BIT_INITS                          RTC_STS_INITS           //!< initialization status flag
#define RTC_FLAG_BIT_SHF_BUSY                       RTC_STS_SHF_BUSY        //!< shift busy flag

/**
  * @}
  */

/**
  * @brief  Deinitializes the RTC registers to their default reset values. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  None.
  * @return Deinitialization status: SUCCESS or ERROR.
  */
#define __RTC_DEF_INIT()                            ((rtc_def_init() & SUCCESS) ? SUCCESS: ERROR)

/**
  * @brief  Enables the RTC registers write protection. It can be writed to a wrong key reactivates the write protection.
  *         The protection mechanism is not affected by system reset.
  * @param  None.
  * @return None.
  */
#define __RTC_WRITE_PROTECTION_ENABLE()             (RTC->CCODE = 0xFF)

/**
  * @brief  Disables the RTC registers write protection.
  * @param  None.  
  * @return None.
  */
#define __RTC_WRITE_PROTECTION_DISABLE()             do{ \
                                                         (RTC->CCODE = 0xCA); \
                                                         (RTC->CCODE = 0x53); \
                                                    }while(0)

/**
  * @brief  Exits the RTC initialization mode.      
  * @param  None.
  * @return None.
  */
#define __RTC_INIT_MODE_EXIT()                      (RTC->STS &= ~RTC_STS_INITE)

/**
  * @brief  Configures the RTC alarm subseconds value and mask. 
  * @note   This function is performed only when the Alarm is disabled. The precondition of calling this interface is 
  *         the write protection is disabled.
  * @param  VALUE: It can be a value from 0 to 0x00007FFF.
  * @param  MASK: specifies the subseconds mask bits (RTC_ACFG2 SSEC[14:0]). It can be one of following values:
  *         @arg RTC_SUB_SECOND_MASK_ALL      
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_1 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_2 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_3 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_4 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_5 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_6 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_7 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_8 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_9 
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_10
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_11
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_12
  *         @arg RTC_SUB_SECOND_MASK_SSEC14_13
  *         @arg RTC_SUB_SECOND_MASK_SSEC14   
  *         @arg RTC_SUB_SECOND_MASK_NONE     
  * @return None.
  */
#define __RTC_ALARM_SUBSEC_CONFIG(VALUE, MASK)      (RTC->ACFG2 = (VALUE | ((uint32_t)MASK << 24)))

/**
  * @brief  Gets the RTC alarm subseconds value.
  * @param  None.
  * @return RTC alarm subseconds value.
  */
#define __RTC_ALARM_SUBSEC_GET()                    (RTC->ACFG2 & RTC_ACFG2_SSEC)

/**
  * @brief  Get the RTC recording subseconds(SSEC) value.
  * @param  None.
  * @return RTC current subseconds value.
  */
#define __RTC_TIME_REC_SUBSEC_GET()                 (RTC->TR3)

/**
  * @brief  Configures trigger inbreak detection event condition (low level or rising edge) for the the selected inbreak 
  *         input enable pin.
  * @param  PIN: selected inbreak pin. It can be any combination of the following values:          
  *         @arg RTC_INBREAK1_TRG
  *         @arg RTC_INBREAK2_TRG
  * @return None.
  */
#define __RTC_INBREAK_TRG_LOW_RISING_CONFIG(PIN)    (RTC->MF &= ~(PIN))

/**
  * @brief  Configures trigger inbreak detection event condition (high level or fallin edge) for the the selected inbreak 
  *         input enable pin.
  * @param  PIN: selected inbreak pin. It can be any combination of the following values:          
  *         @arg RTC_INBREAK1_TRG
  *         @arg RTC_INBREAK2_TRG                 
  * @return None.
  */
#define __RTC_INBREAK_TRG_HIGH_FALLING_CONFIG(PIN)  (RTC->MF |= PIN)

/**
  * @brief Writes a data in the specified AO (always on) registers.
  * @param  REG: AO (always on) registers number, it can beo one of following values:
  *         @arg RTC_AO_REGISTER0 (RTC always on register0)
  *         @arg RTC_AO_REGISTER1 (RTC always on register1)
  *         @arg RTC_AO_REGISTER2 (RTC always on register2)
  *         @arg RTC_AO_REGISTER3 (RTC always on register3)
  *         @arg RTC_AO_REGISTER4 (RTC always on register4)  
  * @param  VALUE: Data to be written in the specified AO (always on) registers.                    
  * @return None.
  */
#define __RTC_AO_REGISTER_WRITE(REG, VALUE)         (*(__IO uint32_t *)(RTC_BASE + 0x50 + REG * 4) = VALUE)
/**
  * @brief  Reads data from the specified AO (always on) registers.
  * @param  REG: AO (always on) registers number, it can beo one of following values:
  *         @arg RTC_AO_REGISTER0 (RTC always on register0)
  *         @arg RTC_AO_REGISTER1 (RTC always on register1)
  *         @arg RTC_AO_REGISTER2 (RTC always on register2)
  *         @arg RTC_AO_REGISTER3 (RTC always on register3)
  *         @arg RTC_AO_REGISTER4 (RTC always on register4)                                         
  * @return the value of the specified AO (always on) registers.
  */
#define __RTC_AO_REGISTER_READ(REG)                 (*(__IO uint32_t *)(RTC_BASE + 0x50 + REG * 4))

/**
  * @brief  Enables the specified RTC function. Note that the precondition of is the write protection is disabled when 
  *         direct access register and calibration output is enabled.          
  * @param  FUNC: specifies the I2C function, it can be one of the following values:
  *         @arg DIR_ACCESS (direct access register)
  *         @arg CAL_OUTPUT (calibration output) 
  *         @arg INBREAK1 (inbreak1 detection)   
  *         @arg INBREAK2 (inbreak2 detection)   
  *         @arg INBREAK_REC (recording on inbreak detection event)
  *         @arg PULLUP_DIS (inbreak disable pull up)         
  * @return None.
  */
#define __RTC_FUNC_ENABLE(FUNC)                     ((RTC_ENABLE_REG_##FUNC) |= (RTC_ENABLE_BIT_##FUNC))     

/**
  * @brief  Disables the specified RTC function. Note that the precondition of is the write protection is disabled when 
  *         direct access register and calibration output is disabled.           
  * @param  FUNC: specifies the I2C function, it can be one of the following values:
  *         @arg DIR_ACCESS (direct access register)
  *         @arg CAL_OUTPUT (calibration output) 
  *         @arg INBREAK1 (inbreak1 detection)   
  *         @arg INBREAK2 (inbreak2 detection)   
  *         @arg INBREAK_REC (recording on inbreak detection event)
  *         @arg PULLUP_DIS (inbreak disable pull up)         
  * @return None.
  */
#define __RTC_FUNC_DISABLE(FUNC)                    ((RTC_ENABLE_REG_##FUNC) &= ~(RTC_ENABLE_BIT_##FUNC))

/**
  * @brief  Enables the specified RTC interrupts. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  INT: specifies the RTC interrupt sources to be enabled. It can be any combination of following values:
  *         @arg RTC_INTR_BIT_TIME_RECORD (time recording interrupt)
  *         @arg RTC_INTR_BIT_ALARM (alarm interrupt)
  *         @arg RTC_INTR_BIT_INBREAK (inbreak interrupt)
  * @return None.                   
  */
#define __RTC_INTR_ENABLE(INT)                      do{ \
                                                         (RTC->CTR |= (uint32_t)(INT & (~RTC_MF_INBRKIE))); \
                                                         (RTC->MF |= (uint32_t)(INT & RTC_MF_INBRKIE)); \
                                                    }while(0)

/**
  * @brief  Disables the specified RTC interrupts. 
  * @note   The precondition of calling this interface is the write protection is disabled.                                    
  * @param  INT: specifies the RTC interrupt sources to be disabled. It can be any combination of following values:
  *         @arg RTC_INTR_BIT_TIME_RECORD (time recording interrupt)
  *         @arg RTC_INTR_BIT_ALARM (alarm interrupt)
  *         @arg RTC_INTR_BIT_INBREAK (inbreak interrupt)
  * @return None.
  */                                    
#define __RTC_INTR_DISABLE(INT)                     do{ \
                                                        RTC->CTR &= ~(INT & (~RTC_MF_INBRKIE)); \
                                                        RTC->MF &= ~(INT & RTC_MF_INBRKIE); \
                                                    }while(0)

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  INT: specifies the RTC interrupt sources. It can be one of following values:
  *         @arg TIME_RECORD (time recording interrupt)
  *         @arg ALARM (alarm interrupt)
  *         @arg INBREAK1 (inbreak1 interrupt)
  *         @arg INBREAK2 (inbreak2 interrupt)                                    
  * @return None.
  */                                      
#define __RTC_INTR_ENABLE_STATUS_GET(INT)           (((RTC_INTR_REG_##INT) & (RTC_INTR_BIT_##INT)) ? SET : RESET)

/**
  * @brief  Checks whether the specified RTC interrupt enabled or not.
  * @param  INT: specifies the RTC interrupt source to check. It can be one of the following values:
  *         @arg TIME_RECORD (time recording interrupt)
  *         @arg ALARM (alarm interrupt)
  *         @arg INBREAK1 (inbreak1 interrupt)
  *         @arg INBREAK2 (inbreak2 interrupt)
  * @return SET or RESET.
  */
#define __RTC_INTR_STATUS_GET(INT)                  (__RTC_INTR_ENABLE_STATUS_GET(INT) && __RTC_FLAG_STATUS_GET(INT))

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  FLAG: specifies the RTC_STS register status bit. It can be one of following values:
  *         @arg DAYLIGHT_SAVING (daylight saving flag)
  *         @arg CALBSY (calibration busy flag)
  *         @arg INBREAK1 (inbreak1 detection flag)
  *         @arg INBREAK2 (inbreak2 detection flag)
  *         @arg TSOV (time recording overflow flag)
  *         @arg TIME_RECORD (time recording flag)
  *         @arg ALARM (alarm flag)
  *         @arg INIT (initialization mode enter flag)
  *         @arg RS (synchronization flag)
  *         @arg INITS (nitialization status flag)
  *         @arg SHF_BUSY (shift busy flag) 
  * @return The new state of set_flag (SET or RESET).
  */
#define __RTC_FLAG_STATUS_GET(FLAG)                 (((RTC_FLAG_REG_##FLAG) & (RTC_FLAG_BIT_##FLAG)) ? SET : RESET) 

/**
  * @brief  Clears the RTC's pending flags.
  * @param  FLAG: specifies the flag to clear. It can be any combination of the following values:
  *         @arg RTC_FLAG_BIT_INBREAK1 
  *         @arg RTC_FLAG_BIT_INBREAK2 
  *         @arg RTC_FLAG_BIT_TSOV     
  *         @arg RTC_FLAG_BIT_TIME_RECORD            
  *         @arg RTC_FLAG_BIT_ALR          
  *         @arg RTC_FLAG_BIT_RS                
  * @return None.
  */
#define __RTC_FLAG_CLEAR(FLAG)                      (RTC->STS = (~(((FLAG) | RTC_STS_INITE) & 0x0001FFFF) | (RTC->STS & RTC_STS_INITE)))

/**
  * @fn error_status_t rtc_def_init(void)
  * @brief  Deinitializes the RTC registers to their default reset values.                     
  * @param  None.
  * @return error_status_t value:SUCCESS or ERROR.
  */
error_status_t rtc_def_init(void);

/**
  * @fn error_status_t rtc_init(rtc_init_t* ptr_init_struct)
  * @brief  Initializes the RTC registers according to the specified parameters in ptr_init_struct. RTC prescaler  
  *         register can be written in initialization step only. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  ptr_init_struct: pointer to a rtc_init_t structure that contains the configuration information for the RTC 
  *         peripheral.
  * @return Initialization status: SUCCESS or ERROR.
  */
error_status_t rtc_init(rtc_init_t* ptr_init_struct);

/**
  * @fn void rtc_struct_init(rtc_init_t* ptr_init_struct)
  * @brief  Fills each rtc_init_struct member with its default value.
  * @param  ptr_init_struct: pointer to a ptr_init_struct structure which will be initialized.         
  * @return None.
  */
void rtc_struct_init(rtc_init_t* ptr_init_struct);

/**
  * @fn error_status_t rtc_init_mode_enter(void)
  * @brief  Enters the RTC Initialization mode. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  None.
  * @return The RTC Initialization mode enter status: SUCCESS or ERROR.
  */
error_status_t rtc_init_mode_enter(void);

/**
  * @fn error_status_t rtc_synchro_wait(void)
  * @brief  Waits until the RTC time and date registers (RTC_TIME and RTC_DATE) are synchronized with RTC APB clock.                 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  None.
  * @return error_status_t value:SUCCESS or ERROR.
  */
error_status_t rtc_synchro_wait(void);

/**
  * @fn error_status_t rtc_outside_clock_enable_ctrl(enable_state_t enable_flag)
  * @brief  Enables or disables outside precise clock enable detection. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  enable_flag: It can be ENABLE or DISABLE.
  * @return Configuration status: SUCCESS or ERROR.
  */
error_status_t rtc_outside_clock_enable_ctrl(enable_state_t enable_flag);

/**
  * @fn error_status_t rtc_time_set(uint32_t format_flag, rtc_time_t* ptr_time_struct)
  * @brief  Set the RTC current time. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).        
  * @param  ptr_time_struct: pointer to a rtc_time_t structure that contains the time configuration information for the RTC.
  * @return Setting status: SUCCESS or ERROR.
  */
error_status_t rtc_time_set(uint32_t format_flag, rtc_time_t* ptr_time_struct);

/**
  * @fn void rtc_time_struct_init(rtc_time_t* ptr_time_struct)
  * @brief  Fill each rtc ptr_time_struct member with its default value (00h: 00min: 00sec).          
  * @param  ptr_time_struct: pointer to a rtc_time_t structure which will be initialized.
  * @return None.
  */
void rtc_time_struct_init(rtc_time_t* ptr_time_struct);

/**
  * @fn void rtc_time_get(uint32_t format_flag, rtc_time_t* ptr_time_struct)
  * @brief  Get the RTC current Time.
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_time_struct: pointer to a rtc_time_t structure that will contain the returned current time configuration.
  * @return None.
  */
void rtc_time_get(uint32_t format_flag, rtc_time_t* ptr_time_struct);

/**
  * @fn uint32_t rtc_subsecond_get(void)
  * @brief  Gets the RTC current calendar subseconds value.
  * @param  None.
  * @return RTC current calendar subseconds value.
  */
uint32_t rtc_subsecond_get(void);

/**
  * @fn error_status_t rtc_date_set(uint32_t format_flag, rtc_date_t* ptr_date_struct)
  * @brief  Set the RTC current date. 
  * @note   The precondition of calling this interface is the write protection is disabled. 
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_date_struct: pointer to a rtc_date_t structure that contains the date configuration information for the RTC.
  * @return Date setting status: SUCCESS or ERROR.
  */
error_status_t rtc_date_set(uint32_t format_flag, rtc_date_t* ptr_date_struct);

/**
  * @fn void rtc_date_struct_init(rtc_date_t* ptr_date_struct)
  * @brief  Fills each rtc_date_struct member with its default value (Monday, January 01 xx00).          
  * @param  ptr_date_struct: pointer to a rtc_date_t structure which will be initialized.
  * @return None.
  */
void rtc_date_struct_init(rtc_date_t* ptr_date_struct);

/**
  * @fn void rtc_date_get(uint32_t format_flag, rtc_date_t* ptr_date_struct)
  * @brief  Get the RTC current date.
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_date_struct: pointer to a rtc_date_t structure that will contain the returned current date configuration.
  * @return None
  */
void rtc_date_get(uint32_t format_flag, rtc_date_t* ptr_date_struct);

/**
  * @fn void rtc_alarm_set(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct)
  * @brief  Set the specified RTC Alarm. The Alarm register can only be written when the corresponding alarm is disabled
  *         (Use the rtc_alarm_enable_ctrl(DISABLE)). 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  format_flag: It can be Binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_alarm_struct: pointer to a rtc_alarm_t structure that contains the alarm configuration parameters.
  * @return None.
  */
void rtc_alarm_set(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct);

/**
  * @fn void rtc_alarm_struct_init(rtc_alarm_t* ptr_alarm_struct)
  * @brief  Fill each rtc ptr_alarm_struct member with its default value (time  = 00h: 00mn: 00sec // Date = 1st day of 
  *         the month // Mask = all fields are not masked).
  * @param  ptr_alarm_struct: pointer to a @ref rtc_alarm_t structure which will be initialized.
  * @return None.
  */
void rtc_alarm_struct_init(rtc_alarm_t* ptr_alarm_struct);

/**
  * @fn void rtc_alarm_get(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct)
  * @brief  Get the RTC alarm value and masks.
  * @param  format_flag: It can be binary data format (RTC_FORMAT_BIN), or BCD data format (RTC_FORMAT_BCD).  
  * @param  ptr_alarm_struct: pointer to a rtc_alarm_t structure that will contains the output alarm configuration values.
  * @return None.
  */
void rtc_alarm_get(uint32_t format_flag, rtc_alarm_t* ptr_alarm_struct);

/**
  * @fn error_status_t rtc_alarm_enable_ctrl(enable_state_t enable_flag)
  * @brief  Enables or disables the specified RTC alarm. 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  enable_flag: It can be: ENABLE or DISABLE.
  * @return Configuration status: SUCCESS or ERROR.
  */
error_status_t rtc_alarm_enable_ctrl(enable_state_t enable_flag);

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
void rtc_daylight_saving_config(uint32_t save_time_value, uint32_t flag);

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
  * @return None.
  */
void rtc_output_config(uint32_t config_value, uint32_t config_polarity);

/**
  * @fn void rtc_cali_output_config(uint32_t config_value)
  * @brief  Configures the calibration pinout (RTC_CTR_CALSRC) selection (1Hz or 512Hz). 
  * @note   The precondition of calling this interface is the write protection is disabled.
  * @param  config_value: It can be one of the following values:
  *         @arg RTC_CALI_OUTPUT_512HZ(regular waveform at 512Hz) 
  *         @arg RTC_CALI_OUTPUT_1HZ(regular waveform at 1Hz)
  * @return None.
  */
void rtc_cali_output_config(uint32_t config_value);

/**
  * @fn error_status_t rtc_swallow_config(uint32_t period_value,uint32_t insert_value, uint32_t swallow_value) 
  * @brief  Configures swallow rtc clock settings.
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
error_status_t rtc_swallow_config(uint32_t period_value,uint32_t insert_value, uint32_t swallow_value); 
                                  
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
void rtc_time_recording_config(uint32_t edge_flag, enable_state_t enable_flag);

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
void rtc_time_recording_get(uint32_t format_flag, rtc_time_t* ptr_time_struct, rtc_date_t* ptr_date_struct);

/**
  * @fn void rtc_inbreak_filter_config(uint32_t set_value)
  * @brief  Configures the inbreak Filter.
  * @param  set_value: Specifies the inbreak filter, it can be one of the following values:
  *         @arg RTC_INBREAK_FILTER_DISABLE(inbreak filter is disabled)
  *         @arg RTC_INBREAK_FILTER_2SAMPLE(inbreak is activated after 2 consecutive samples at the active level) 
  *         @arg RTC_INBREAK_FILTER_4SAMPLE(inbreak is activated after 4 consecutive samples at the active level) 
  *         @arg RTC_INBREAK_FILTER_8SAMPLE(inbreak is activated after 8 consecutive samples at the active level)   
  * @return None
  */
void rtc_inbreak_filter_config(uint32_t set_value);

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
void rtc_inbreak_sample_freq_config(uint32_t freq_vale);

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
void rtc_inbreak_precharge_duration(uint32_t set_value);

/**
  * @fn void rtc_output_type_config(uint32_t output_type)
  * @brief  Configures the RTC output pin mode. 
  * @param  output_type: specifies the RTC Output (PC13) pin mode. It can be one of the following values:
  *         @arg RTC_OUTPUT_OPEN_DRAIN(RTC output is configured in open drain mode)                                     
  *         @arg RTC_OUTPUT_PUSH_PULL(RTC output is configured in push pull mode)                                    
  * @return None.
  */
void rtc_output_type_config(uint32_t output_type);

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
error_status_t rtc_adj_register_config(uint32_t second_flag, uint32_t subsecond_value);


#define UNUSED(x) (void)x
    
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

