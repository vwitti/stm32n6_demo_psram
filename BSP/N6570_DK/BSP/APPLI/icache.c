
#include <stdio.h>
#include "tcsglobal/system_constants.h"
#include "BSP/Inc/icache.h"
#include "Common/Inc/Init/error_handler.h"
#include "stm32n6xx_hal.h"

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache (default 2-ways set associative cache)
  */
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler("ICACHE");
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief This function handles GPU2D cache interrupt.
  */
void ICACHE_IRQHandler(void)
{
  /* USER CODE BEGIN ICACHE_IRQn 0 */

  /* USER CODE END ICACHE_IRQn 0 */
  HAL_ICACHE_IRQHandler();
  /* USER CODE BEGIN ICACHE_IRQn 1 */

  /* USER CODE END ICACHE_IRQn 1 */
}
