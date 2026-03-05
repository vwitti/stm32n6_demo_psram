/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IOSUBSYSTEM_SENSORS__H__
#define __IOSUBSYSTEM_SENSORS__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN VARIABLES */

/* USER CODE END VARIABLES */

void IoSubSystemSensor_Init(void);
void IoSubSystemSensor_Modify(void);
uint16_t IoSubSystemSensor_GetPressureLeft();
uint16_t IoSubSystemSensor_GetPressureRight();
uint16_t IoSubSystemSensor_GetRamStroke();
void IoSubSystemSensor_SetPressureLeft(uint16_t val);
void IoSubSystemSensor_SetPressureRight(uint16_t val);
void IoSubSystemSensor_SetRamStroke(uint16_t val);

#ifdef __cplusplus
}
#endif

#endif /* __IOSUBSYSTEM_SENSORS__H__ */

