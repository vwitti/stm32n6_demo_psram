#include "BSP/Inc/mcu.h"
#include <stdio.h>

/* MPU Configuration */
void MPU_Config(void)
{
  MPU_Region_InitTypeDef default_config = {0};
  MPU_Attributes_InitTypeDef attr_config = {0};
  uint32_t primask_bit = __get_PRIMASK();
  uint32_t addr_start;
  uint32_t addr_end;

  __disable_irq();

  /* disable the MPU */
  HAL_MPU_Disable();

  ///////////////////// REGION 0 /////////////////////
  /* create an attribute configuration for the MPU */
  attr_config.Attributes = INNER_OUTER(MPU_WRITE_BACK | MPU_NON_TRANSIENT | MPU_RW_ALLOCATE);
  attr_config.Number = MPU_ATTRIBUTES_NUMBER0;

  HAL_MPU_ConfigMemoryAttributes(&attr_config);

  extern uint8_t * _sfwrom[];
  extern uint8_t * _efwrom[];
  addr_start = (uint32_t) _sfwrom;
  addr_end   = (uint32_t) _efwrom;

  /* Create a region associated with memory address of XSPI2_BASE */
  /*Normal memory type, code execution allowed */
  default_config.Enable = MPU_REGION_ENABLE;
  default_config.Number = MPU_REGION_NUMBER0;
  default_config.BaseAddress = addr_start;
  default_config.LimitAddress = addr_end - 1;
  default_config.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  default_config.AccessPermission = MPU_REGION_ALL_RO;
  default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
  HAL_MPU_ConfigRegion(&default_config);

  /* Create a non cacheable region */
  /*Normal memory type, code execution allowed */

  /* create an attribute configuration for the MPU */
  attr_config.Attributes = INNER_OUTER(MPU_DEVICE_NGNRNE);
  attr_config.Number = MPU_ATTRIBUTES_NUMBER1;

  HAL_MPU_ConfigMemoryAttributes(&attr_config);

  extern uint8_t * _sethram[];
  extern uint8_t * _eethram[];
  addr_start = (uint32_t) _sethram;
  addr_end   = (uint32_t) _eethram;

  default_config.Enable = MPU_REGION_ENABLE;
  default_config.Number = MPU_REGION_NUMBER1;
  default_config.BaseAddress =   addr_start;
  default_config.LimitAddress =  addr_end - 1;
  default_config.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  default_config.AccessPermission = MPU_REGION_ALL_RW;
  default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER1;
  HAL_MPU_ConfigRegion(&default_config);

  /* MPU Region 1 Config */
  attr_config.Attributes = INNER_OUTER(MPU_RW_ALLOCATE);
  attr_config.Number = MPU_ATTRIBUTES_NUMBER2;

  HAL_MPU_ConfigMemoryAttributes(&attr_config);

  extern uint8_t * _snetxduo[];
  extern uint8_t * _enetxduo[];
  addr_start = (uint32_t) _snetxduo;
  addr_end   = (uint32_t) _enetxduo;

  default_config.Enable = MPU_REGION_ENABLE;
  default_config.Number = MPU_REGION_NUMBER2;
  default_config.BaseAddress =  addr_start;
  default_config.LimitAddress = addr_end - 1;
  default_config.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  default_config.AccessPermission = MPU_REGION_ALL_RW;
  default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER2;
  HAL_MPU_ConfigRegion(&default_config);


  /* enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

  /* Exit critical section to lock the system and avoid any issue around MPU mechanisme */
  __set_PRIMASK(primask_bit);
}

