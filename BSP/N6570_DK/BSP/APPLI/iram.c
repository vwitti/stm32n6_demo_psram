
#include <stdio.h>
#include "tcsglobal/system_constants.h"
#include "BSP/Inc/iram.h"
#include "Common/Inc/Init/error_handler.h"
#include "stm32n6xx_hal.h"

// Handling of internal RAMs

void Enable_NPU_RAM_ForCore(void)
{
  RAMCFG_HandleTypeDef hramcfg  = {0};

  /* Power On AXSRAM3 to AXISRAM6 */
  __HAL_RCC_AXISRAM3_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM4_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM5_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM6_MEM_CLK_ENABLE();

  hramcfg.Instance = RAMCFG_SRAM3_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);

  hramcfg.Instance = RAMCFG_SRAM4_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);

  hramcfg.Instance = RAMCFG_SRAM5_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);

  hramcfg.Instance = RAMCFG_SRAM6_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
}

void Enable_AXICACHE_RAM_ForCore(void)
{
  __HAL_RCC_CACHEAXIRAM_MEM_CLK_ENABLE();
  __HAL_RCC_CACHEAXI_CLK_ENABLE();
}

void Enable_VENCRAM_ForCore(void)
{
  RAMCFG_HandleTypeDef hramcfg  = {0};

  /* Power on and clock VENCRAM */
  __HAL_RCC_VENCRAM_MEM_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_VENC_CLK_ENABLE();

  hramcfg.Instance = RAMCFG_VENC_RAM;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);

  HAL_SYSCFG_DisableVENCRAMReserved();
}
