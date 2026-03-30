/**
  * @file    cs32f0xx_pmu.h
  * @brief   This file contains all the functions prototypes for the PMU firmware 
  *          library.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */
  
#ifndef __CS32F0XX_PMU_H__
#define __CS32F0XX_PMU_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup PMU
  * @{
  */ 

/** @defgroup PMU_Exported_Constants
  * @{
  */ 
  
/**
  * @brief The PMU function registers.
  */
#define PMU_ENABLE_REG_WAKEUP_PIN1          (PMU->CS)               //!< PMU wake up pin1 enable reg
#define PMU_ENABLE_REG_WAKEUP_PIN2          (PMU->CS)               //!< PMU wake up pin2 enable reg
#define PMU_ENABLE_REG_VBAT_WRITE           (PMU->CTR)              //!< PMU vbat write enable reg
#define PMU_ENABLE_REG_LVD                  (PMU->CTR)              //!< PMU LVD enable reg

/**
  * @brief The PMU function enable bits.
  */
#define PMU_ENABLE_BIT_WAKEUP_PIN1          (PMU_WAKEUP_PIN1)       //!< PMU wake up pin1 enable bit
#define PMU_ENABLE_BIT_WAKEUP_PIN2          (PMU_WAKEUP_PIN2)       //!< PMU wake up pin2 enable bit
#define PMU_ENABLE_BIT_VBAT_WRITE           (PMU_CTR_VBTWEN)        //!< PMU vbat write enable bit
#define PMU_ENABLE_BIT_LVD                  (PMU_CTR_LVDEN)         //!< PMU LVD enable bit

/** 
  * @brief PMU LVDSEL level definition 
  */ 
#define PMU_LVDSEL_LEVEL0                   PMU_CTR_LVDSEL_LEVEL0   //!< PMU LVD (low voltage detector) level 0 
#define PMU_LVDSEL_LEVEL1                   PMU_CTR_LVDSEL_LEVEL1   //!< PMU LVD (low voltage detector) level 1 
#define PMU_LVDSEL_LEVEL2                   PMU_CTR_LVDSEL_LEVEL2   //!< PMU LVD (low voltage detector) level 2 
#define PMU_LVDSEL_LEVEL3                   PMU_CTR_LVDSEL_LEVEL3   //!< PMU LVD (low voltage detector) level 3 
#define PMU_LVDSEL_LEVEL4                   PMU_CTR_LVDSEL_LEVEL4   //!< PMU LVD (low voltage detector) level 4 
#define PMU_LVDSEL_LEVEL5                   PMU_CTR_LVDSEL_LEVEL5   //!< PMU LVD (low voltage detector) level 5 
#define PMU_LVDSEL_LEVEL6                   PMU_CTR_LVDSEL_LEVEL6   //!< PMU LVD (low voltage detector) level 6 
#define PMU_LVDSEL_LEVEL7                   PMU_CTR_LVDSEL_LEVEL7   //!< PMU LVD (low voltage detector) level 7 

#define PMU_LVDSEL_LEVEL_CHECK(value)       (((value) == PMU_LVDSEL_LEVEL0) || ((value) == PMU_LVDSEL_LEVEL1)|| \
                                            ((value) == PMU_LVDSEL_LEVEL2) || ((value) == PMU_LVDSEL_LEVEL3)|| \
                                            ((value) == PMU_LVDSEL_LEVEL4) || ((value) == PMU_LVDSEL_LEVEL5)|| \
                                            ((value) == PMU_LVDSEL_LEVEL6) || ((value) == PMU_LVDSEL_LEVEL7))

/** 
  * @brief PMU WakeUp Pins definition
  */
#define PMU_WAKEUP_PIN1                     PMU_CS_WUPEN1           //!< PMU wakeup pin 1 
#define PMU_WAKEUP_PIN2                     PMU_CS_WUPEN2           //!< PMU wakeup pin 2 

/** 
  * @brief PMU LDO low power Control definition
  */
#define PMU_LDO_ON                          ((uint32_t)0x00000000)
#define PMU_LDO_LOW_POWER                   PMU_CTR_LDOLM

#define PMU_LDO_CHECK(flag)                 (((flag) == PMU_LDO_ON) || ((flag) == PMU_LDO_LOW_POWER))

/** 
  * @brief PMU SLEEP mode entry 
  */
#define PMU_SLEEP_ENTRY_WFI                 ((uint8_t)0x01)         //!< Enter SLEEP mode with WFI instruction 
#define PMU_SLEEP_ENTRY_WFE                 ((uint8_t)0x02)         //!< Enter SLEEP mode with WFE instruction 

#define PMU_SLEEP_ENTRY_CHECK(value)        (((value) == PMU_SLEEP_ENTRY_WFI) || ((value) == PMU_SLEEP_ENTRY_WFE))

/** 
  * @brief PMU STOP mode entry
  */
#define PMU_DSM_ENTRY_WFI                   ((uint8_t)0x01)         //!< Enter STOP mode with WFI instruction          
#define PMU_DSM_ENTRY_WFE                   ((uint8_t)0x02)         //!< Enter STOP mode with WFE instruction          
#define PMU_DSM_ENTRY_SLEEPONEXIT           ((uint8_t)0x03)         //!< Enter STOP mode with SLEEPONEXIT instruction 
    
#define PMU_STOP_ENTRY_CHECK(value)         (((value) == PMU_DSM_ENTRY_WFI) || ((value) == PMU_DSM_ENTRY_WFE) || \
                                            ((value) == PMU_DSM_ENTRY_SLEEPONEXIT))

/** 
  * @brief PMU flag definition
  */
#define PMU_FLAG_WUPF                       PMU_CS_WUPF             //!< PMU wakeup flag 
#define PMU_FLAG_PWDF                       PMU_CS_PWDF             //!< PMU power down flag 
#define PMU_FLAG_LVDO                       PMU_CS_LVDO             //!< PMU LVDO flag 

/**
  * @}
  */

/**
  * @brief  Deinitializes the PMU peripheral registers to their default reset values.
  * @param  None.
  * @return None
  */
#define __PMU_DEF_INIT()                do{ \
                                            (RCU->APB1RST |= RCU_PERI_RST_BIT_PMU); \
                                            (RCU->APB1RST &= ~RCU_PERI_RST_BIT_PMU); \
                                     	}while(0U)

/**
  * @brief  Enables the PMU functionality.
  * @param  FUNC: specifies the function, it can be one of the following values:
  *            @arg WAKEUP_PIN1
  *            @arg WAKEUP_PIN2
  *            @arg VBAT_WRITE
  *            @arg LVD
  * @return None
  */
#define __PMU_FUNC_ENABLE(FUNC)         ((PMU_ENABLE_REG_##FUNC) |= (PMU_ENABLE_BIT_##FUNC))
           
/**
  * @brief  Disables the PMU functionality.
  * @param  FUNC: specifies the function, it can be one of the following values:
  *            @arg WAKEUP_PIN1
  *            @arg WAKEUP_PIN2
  *            @arg VBAT_WRITE
  *            @arg LVD
  * @return None
  */                                  
#define __PMU_FUNC_DISABLE(FUNC)        ((PMU_ENABLE_REG_##FUNC) &= ~(PMU_ENABLE_BIT_##FUNC))

/**
  * @brief  Checks whether the specified PMU flag is set or not.
  * @param  FLAG: specifies the flag to check, it can be one of the following values:
  *            @arg WUPF(Wake Up flag)
  *            @arg PWDF(power down flag)
  *            @arg LVDO(low vlotage detector Output)
  * @return SET or RESET.
  */
#define __PMU_FLAG_STATUS_GET(FLAG)     ((PMU->CS & (PMU_FLAG_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the PMU's pending flags.
  * @param  FLAG: specifies the flag to clear, it can be one of the following values:
  *            @arg PMU_FLAG_WUPF(Wake Up flag)
  *            @arg PMU_FLAG_PWDF(power down flag)
  * @return None
  */
#define __PMU_FLAG_CLEAR(FLAG)          (PMU->CTR |= (FLAG << 2))

/**
  * @fn void pmu_low_vol_detector_config(uint32_t level)
  * @brief  Selection LVD (low voltage detector) threshold.
  * @param  level: specifies the LVD detection level, it can be one of
  *         the following values:
  *            @arg PMU_LVDSEL_LEVEL0
  *            @arg PMU_LVDSEL_LEVEL1
  *            @arg PMU_LVDSEL_LEVEL2
  *            @arg PMU_LVDSEL_LEVEL3
  *            @arg PMU_LVDSEL_LEVEL4
  *            @arg PMU_LVDSEL_LEVEL5
  *            @arg PMU_LVDSEL_LEVEL6
  *            @arg PMU_LVDSEL_LEVEL7
  * @return None
  */
void pmu_low_vol_detector_config(uint32_t level);

/**
  * @fn void pmu_sleep_mode_set(uint8_t value)
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  value: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PMU_SLEEP_ENTRY_WFI (enter SLEEP mode with WFI instruction)
  *            @arg PMU_SLEEP_ENTRY_WFE (enter SLEEP mode with WFE instruction)
  * @return None
  */
void pmu_sleep_mode_set(uint8_t value);

/**
  * @fn void pmu_deep_sleep_mode_enter(uint32_t value, uint8_t flag)
  * @brief  Enters STOP mode.
  * @param  value: specifies the regulator state in STOP mode. It can be:
  *          PMU_LDO_ON or PMU_LDO_LOW_POWER().
  * @param  flag: specifies if STOP mode in entered with WFI or WFE instruction.
  *          It can be one of the following values:
  *            @arg PMU_DSM_ENTRY_WFI(enter STOP mode with WFI instruction)
  *            @arg PMU_DSM_ENTRY_WFE(enter STOP mode with WFE instruction)
  *            @arg PMU_DSM_ENTRY_SLEEPONEXIT(enter STOP mode with SLEEPONEXIT instruction)
  * @return None
  */
void pmu_deep_sleep_mode_enter(uint32_t value, uint8_t flag);

/**
  * @fn void pmu_power_down_enter(void)
  * @brief  Enters power down mode. The Wakeup flag (WUF) need to be cleared
  *         at application level before to call this function.    
  * @param  None
  * @return None
  */
void pmu_power_down_enter(void);

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

