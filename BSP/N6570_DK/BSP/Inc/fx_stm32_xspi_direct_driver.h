
/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FX_STM32_XSPI_DIRECT_DRIVER_H
#define FX_STM32_XSPI_DIRECT_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tcsglobal/system_constants.h"
#include "fx_api.h"

#include "stm32n6xx_hal.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* Default sector size, used by the driver */
#define FX_SRAM_DISK_DEFAULT_SECTOR_SIZE  512

#define FX_SRAM_DISK_BASE_ADDRESS         (XSPI_OFFSET_TCS_ROMFS) // Relative in SPI Flash

/* define the SRAM DISK size */
#define FX_SRAM_DISK_SIZE                 (XSPI_SIZE_TCS_ROMFS)


/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

VOID fx_stm32_xspi_direct(FX_MEDIA *media_ptr);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

#ifdef __cplusplus
}
#endif
#endif /* FX_STM32_XSPI_DIRECT_DRIVER_H */
