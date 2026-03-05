/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#if defined(FORTE_NO_SIMULATOR)
#include "Common/Inc/Parameter/ShieldPara.h"
#else
#include "forte/ASGEVO_PACKAGE/ShieldPara.h"
#endif

static uint16_t length_of_ram_cylinder= 1100;
static uint16_t max_pressure_sensors[MAX_NUM_PRESSURE_SENSORS]= { 500, 501 }; // Just to show if values are transported correct
static uint16_t max_pressure_nsa[MAX_NUM_PRESSURE_SENSORS]= { 450, 451 };

uint16_t Parameter_Shield_Get_LengthRamCylinder()
{
	return length_of_ram_cylinder;
}

uint16_t Parameter_Shield_Get_MaxPressureSensor(uint32_t sensor)
{
	switch(sensor)
	{
	case SENSOR_LEG_LEFT:
	case SENSOR_LEG_RIGHT:
		return max_pressure_sensors[sensor];
	}
	return 0;
}

uint16_t Parameter_Shield_Get_MaxPressureNSA(uint32_t sensor)
{
	switch(sensor)
	{
	case SENSOR_LEG_LEFT:
	case SENSOR_LEG_RIGHT:
		return max_pressure_nsa[sensor];
	}
	return 0;
}

#if 0

// Neben funktionen
getParaAsgBool(eP_B_AA_MitBaseliftAusf, FRAMVARIABLEN.u16ShieldNr //
getParaAsgU8(eP_BL_T_AA_StartAusf, FRAMVARIABLEN.u16ShieldNr) > 0 //
getParaAsgU8(eP_BL_T_AA_Ausf, FRAMVARIABLEN.u16ShieldNr);

getParaAsgBool(eP_B_AA_MitEckAusf, FRAMVARIABLEN.u16ShieldNr)
getParaAsgU8(eP_ECK_T_AA_StartAusf, FRAMVARIABLEN.u16ShieldNr
getParaAsgU8(eP_ECK_T_AA_Ausf, FRAMVARIABLEN.u16ShieldNr)

getParaAsgBool(eP_B_AA_MitEckEinf, FRAMVARIABLEN.u16ShieldNr)
getParaAsgU8(eP_ECK_T_AA_PreStartEinf, FRAMVARIABLEN.u16ShieldNr)
getParaAsgU8(eP_ECK_T_AA_PreEinf, FRAMVARIABLEN.u16ShieldNr)

getParaAsgBool(eP_B_AA_MitBaseliftEinf, FRAMVARIABLEN.u16ShieldNr))
getParaAsgU8(eP_BL_T_AA_Einf, FRAMVARIABLEN.u16ShieldNr);

getParaAsgBool(eP_B_AA_MitEckEinf, FRAMVARIABLEN.u16ShieldNr)
getParaAsgU8(eP_ECK_T_AA_Einf, FRAMVARIABLEN.u16ShieldNr);

// LAS
u32)getParaAsgU8(eP_AA_T_StartLAS, FRAMVARIABLEN.u16ShieldNr);
getParaAsgU8(eP_AA_T_TimeoutLoweringSensor, FRAMVARIABLEN.u16ShieldNr));
getParaAsgU8(eP_AA_T_StartSchreiten, FRAMVARIABLEN.u16ShieldNr));
etParaAsgU8(eP_AA_T_RaubenTC, FRAMVARIABLEN.u16ShieldNr));

getParaAsgU8(eP_AA_T_RaubNachStartSchreit, FRAMVARIABLEN.u16ShieldNr);
getParaAsgU8(eP_AA_N_Nachrauben, FRAMVARIABLEN.u16ShieldNr);

getParaAsgU8(eP_AA_V_MinSchreiten, FRAMVARIABLEN.u16ShieldNr));
getParaAsgU8(eP_AA_T_StartNachrauben, FRAMVARIABLEN.u16ShieldNr));
getParaAsgU8(eP_AA_T_Schreiten, FRAMVARIABLEN.u16ShieldNr));

getParaAsgU8(eP_AA_T_Setzen, FRAMVARIABLEN.u16ShieldNr));
getParaAsgU8(eP_AA_T_Nachrauben, FRAMVARIABLEN.u16ShieldNr));








#endif













