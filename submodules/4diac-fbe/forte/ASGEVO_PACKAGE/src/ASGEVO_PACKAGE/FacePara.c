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
#include "Common/Inc/Parameter/FacePara.h"
#else
#include "forte/ASGEVO_PACKAGE/FacePara.h"
#endif

static uint16_t depth_of_cut                 = 1090;
static uint16_t LAS_creep_advance_min_target = 0;
static uint16_t LAS_creep_advance_window     = 0;
static uint16_t LAS_sensor_controlled        = 0;

uint16_t Parameter_Face_Get_DepthOfCut()
{
	return depth_of_cut;
}

uint16_t Parameter_Face_Get_LAS_CreepAdvanceMinTarget()
{
	return LAS_creep_advance_min_target;
}

uint16_t Parameter_Face_Get_LAS_CreepAdvanceWindow()
{
	return LAS_creep_advance_window;
}

uint16_t Parameter_Face_Get_LAS_Sensorgesteuert()
{
	return LAS_sensor_controlled;
}

void Parameter_Face_Set_DepthOfCut(uint16_t val)
{

}

void Parameter_Face_Set_LAS_CreepAdvanceMinTarget(uint16_t val)
{

}

void Parameter_Face_Set_LAS_CreepAdvanceWindow(uint16_t val)
{

}

void Parameter_Face_Set_LAS_Sensorgesteuert(uint16_t val)
{

}


