#include "BSP/Inc/mcu.h"


void MPU_Config(void)
{
  uint32_t primask_bit = __get_PRIMASK();

  __disable_irq();

  /* disable the MPU */
  HAL_MPU_Disable();

  // This setting are done in FSBL bootcode, there is no need to reprogram this MPU sections
#if 1
  MPU_Region_InitTypeDef default_config = {0};
  MPU_Attributes_InitTypeDef attr_config = {0};
  uint32_t addr_start;
  uint32_t addr_end;

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
  default_config.BaseAddress =  addr_start;
  default_config.LimitAddress = addr_end - 1;
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
#endif

  ///////////////////// REGION 3 /////////////////////
  // Command list RAM

  extern uint8_t * _scmdlistram[];
  extern uint8_t * _ecmdlistram[];
  addr_start = (uint32_t) _scmdlistram;
  addr_end   = (uint32_t) _ecmdlistram;

  default_config.Enable = MPU_REGION_ENABLE;
  default_config.Number = MPU_REGION_NUMBER3;
  default_config.BaseAddress  = addr_start;
  default_config.LimitAddress = addr_end - 1;
  default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER3;
  default_config.AccessPermission = MPU_REGION_ALL_RW;
  default_config.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  default_config.DisablePrivExec = MPU_PRIV_INSTRUCTION_ACCESS_ENABLE;
  default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&default_config);

  /** Initializes and configures the Attribute 3 and the memory to be protected
  */
  attr_config.Number = MPU_ATTRIBUTES_NUMBER3;
  attr_config.Attributes = MPU_DEVICE_GRE;

  HAL_MPU_ConfigMemoryAttributes(&attr_config);

  ///////////////////// REGION 4 /////////////////////
  // FBRAM

  extern uint8_t * _sfbram[];
  extern uint8_t * _efbram[];
  addr_start = (uint32_t) _sfbram;
  addr_end   = (uint32_t) _efbram;

  default_config.Enable = MPU_REGION_ENABLE;
  default_config.Number = MPU_REGION_NUMBER4;
  default_config.BaseAddress  = addr_start;
  default_config.LimitAddress = addr_end - 1;
  default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER4;
  default_config.AccessPermission = MPU_REGION_ALL_RW;
  default_config.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  default_config.DisablePrivExec = MPU_PRIV_INSTRUCTION_ACCESS_ENABLE;
  default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  HAL_MPU_ConfigRegion(&default_config);

  /** Initializes and configures the Attribute 2 and the memory to be protected
  */
  attr_config.Number = MPU_ATTRIBUTES_NUMBER4;
  attr_config.Attributes = MPU_DEVICE_NGNRNE;

  HAL_MPU_ConfigMemoryAttributes(&attr_config);

  ///////////////////// REGION 5 /////////////////////
  // Asset ROM touchGFX

  extern uint8_t * _sassetsrom[];
  extern uint8_t * _eassetsrom[];
  addr_start = (uint32_t) _sassetsrom;
  addr_end   = (uint32_t) _eassetsrom;

  default_config.Enable = MPU_REGION_ENABLE;
  default_config.Number = MPU_REGION_NUMBER5;
  default_config.BaseAddress  = addr_start;
  default_config.LimitAddress = addr_end - 1;
  default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER5;
  default_config.AccessPermission = MPU_REGION_ALL_RO;
  default_config.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  default_config.DisablePrivExec = MPU_PRIV_INSTRUCTION_ACCESS_ENABLE;
  default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  HAL_MPU_ConfigRegion(&default_config);

  /** Initializes and configures the Attribute 0 and the memory to be protected
  */
  attr_config.Number = MPU_ATTRIBUTES_NUMBER5;
  attr_config.Attributes = INNER_OUTER(MPU_WRITE_BACK|MPU_TRANSIENT |MPU_R_ALLOCATE);

  HAL_MPU_ConfigMemoryAttributes(&attr_config);

  ///////////////////////////////////////////////////

  /* enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

  /* Exit critical section to lock the system and avoid any issue around MPU mechanisme */
  __set_PRIMASK(primask_bit);

}

