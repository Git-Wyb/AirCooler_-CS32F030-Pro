/**
  * @file    cs32f0xx_pmu.c
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of Power management unit (PMU) peripheral:
  *           VBAT Domain Access; LDV configuration
  *           WakeUp pins configuration; Low Power modes configuration.
  * @author  ChipSea MCU Group
  * @version V1.0.0
  * @date   2021.08.04        
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note 
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#include "cs32f0xx_pmu.h"
#include "cs32f0xx_rcu.h"
/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @defgroup PMU
  * @{
  */ 

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
void pmu_low_vol_detector_config(uint32_t level)
{
    ASSERT(PMU_LVDSEL_LEVEL_CHECK(level));
    MODIFY_REG(PMU->CTR, PMU_CTR_LVDSEL_LEVEL7, level);
}

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
void pmu_sleep_mode_set(uint8_t value)
{
    ASSERT(PMU_SLEEP_ENTRY_CHECK(value));

    /* Clear SLEEPDEEP bit */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  
    if(value == PMU_SLEEP_ENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE(); 
        __WFE();
    }
}

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
void pmu_deep_sleep_mode_enter(uint32_t value, uint8_t flag)
{
    ASSERT(PMU_LDO_CHECK(value));
    ASSERT(PMU_STOP_ENTRY_CHECK(flag));
  
    MODIFY_REG(PMU->CTR, PMU_CTR_LDOLM, value);
    
    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    if(flag == PMU_DSM_ENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk); 
    }
    else if (flag == PMU_DSM_ENTRY_WFE)
    {
        /* Request Wait For Event */
        __WFE();
        /* Reset SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);   
    }
    else
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
}

/**
  * @fn void pmu_power_down_enter(void)
  * @brief  Enters power down mode. The Wakeup flag (WUF) need to be cleared
  *         at application level before to call this function.    
  * @param  None
  * @return None
  */
void pmu_power_down_enter(void)
{
    uint16_t i = 0;
    for(i = 0; i < 1450; i++)
    {
        __NOP();
    }
    PMU->CTR |= PMU_CTR_DSMODE;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    /* Request Wait For Interrupt */
    __WFI();
}

/**
  * @}
  */

/**
  * @}
  */

