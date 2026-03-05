#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#if defined(FORTE_NO_SIMULATOR)
#include "stm32n6xx.h"
#include "tcsglobal/asg_evo.h"
#include "threadx/common/inc/tx_api.h"
#include "Common/Inc/IoSubSystem/iosubsystem.h"
#include "Common/Inc/IoSubSystem/sensors.h"
#include "Common/Inc/IoSubSystem/valves.h"
#include "Common/Inc/Parameter/ShieldPara.h"
#include "Common/Inc/Parameter/FacePara.h"
#else
#include "forte/ASGEVO_PACKAGE/iosubsystem.h"
#include "forte/ASGEVO_PACKAGE/sensors.h"
#include "forte/ASGEVO_PACKAGE/valves.h"
#include "forte/ASGEVO_PACKAGE/ShieldPara.h"
#include "forte/ASGEVO_PACKAGE/FacePara.h"
#endif

#if defined(FORTE_NO_SIMULATOR)

#define s32Time_Akt HAL_GetTick

#else

#include <stdint.h>
#include <time.h>

int32_t s32Time_Akt(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    int64_t ms = (int64_t)ts.tv_sec * 1000 +
                 ts.tv_nsec / 1000000;

    return (int32_t)ms;  // bewusst Overflow erlaubt
}

#endif

// IDs of simulated sensors and resources
#define NUMBER_SIMULATED_SENSORS		3
#define SIMULATED_SENSORS_ID_LEG_LEFT	0
#define SIMULATED_SENSORS_ID_LEG_RIGHT	1
#define SIMULATED_SENSORS_ID_RAMSTROKE	2

#define SENSOR_TYPE_PRESSURE		    0
#define SENSOR_TYPE_RAMSTROKE		    1

#define INIT_VALUE_RAMSTROKE            90  	// [%] Offset in percent for the initial RamStroke value

// A full push takes approx. 2-3s, full lowering also 2-3s, current values are
// push/pull : 3s
// set/lower : 3s
#define PRESSURE_SENSOR_LOWER_TIME		3000    // [ms] time for lowering pressure from max to 0 bar (valve SK_RAUBEN is activated)
#define PRESSURE_SENSOR_SET_TIME		3000    // [ms] time for setting pressure from 0 bar  to max (valve SK_SETZEN is activated)

#define RAMSTROKE_SENSOR_PUSH_TIME		3000    // [ms] time for push ram stroke from 0% to 100% (valve SK_FOERDERERRUECKEN is activated)
#define RAMSTROKE_SENSOR_PULL_TIME		3000	// [ms] time for pull ram stroke from 100% to 0% (valve SK_SCHILDZIEHEN is activated)

#define MAX_PRESSURE_BAR                600		// Default value for absolute maximum if no value is configured
#define MAX_RAMSTROKE_MM                1400	// Default value for absolute maximum if no value is configured
#define MIN_PRESSURE_BAR                0
#define MIN_RAMSTROKE_MM                0
#define BLEEDING_025					25		// Max bleeding 0.25% / sec in Bezug auf pSensor->s16MaxValue */
#define NUMBER_OF_PRESSURE_SENSORS		2

#define OVERSHOOT_RAM_STROKE_DIST_PERCENT	10	// [%] in percent absolute of total RAM stroke distance when pulling has stopped
#define CREEPADVANCE_SLOWDOWN				90  // [%] We simply use the existing already implemented wear 'pullWear'

#define RELOAD_PARAMETER_TIMEOUT		2000	// [ms] timeout for reloading parameter(s) for simulation

// Scaling defines
#define MM_TO_UM(x)						((x)*1000)	// Scale from [mm] to [um]
#define UM_TO_MM(x)						((x)/1000)	// Scale from [um] to [mm]
#define BAR_TO_MBAR(x)					((x)*1000)	// Scale from [bar] to [mbar]
#define MBAR_TO_BAR(x)					((x)/1000)	// Scale from [mbar] to [bar]

// Overshootstate
#define OVERSHOOT_STATE_IDLE			(0)			// Wait for start
#define OVERSHOOT_STATE_START			(1)			// Start load target value
#define OVERSHOOT_STATE_EXEC			(2)			// Exec

#if OVERSHOOT_RAM_STROKE_DIST_PERCENT > 15
  #error "There is no reason to exceed this value above this limit. If you do so, please check calculation in respect to this value"
#endif

typedef struct
{
    bool bValveSetEnabled;			// On rising edge set valve has been enabled and sensor value calculation is reset
    bool bValveLowerEnabled;		// On rising edge lower valve has been enabled and sensor value calculation is reset
	int32_t s32_set_dp_dT;				// [bar/s] change rate in bar / s when setting (valve SK_SETZEN is activated)
	int32_t s32_lower_dp_dT;			// [bar/s] change rate in bar / s when lowering (valve SK_RAUBEN is activated)
	int32_t s32_sensval_mbar;			// [mbar]  sensor pressure in mbar
} tSensorSimPressure;

typedef struct
{
    bool bValvePushEnabled;			// On rising edge push valve has been enabled and sensor value calculation is reset
    bool bValvePullEnabled;			// On rising edge pull valve has been enabled and sensor value calculation is reset
	bool bHasNeighborTG;			// TRUE if shield is not a face end shield at TG and has a neighbor
	bool bHasNeighborHG;			// TRUE if shield is not a face end shield at HG and has a neighbor
	uint8_t   u8OvershootState;			// State for handling LAS Overshoot when pull valve is switched off
	int32_t s32_push_dx_dT;				// [mm/s] change rate in mm / s when pushing shield (bankpush) (valve SK_FOERDERERRUECKEN is activated)
	uint8_t  pushWear;					// [%] push, slow down default 0 %
	int32_t s32_pull_dx_dT;				// [mm/s] change rate in mm / s when pulling shield (pullback) (valve SK_SCHILDZIEHEN is activated)
	uint8_t  pullWear;					// [%] pull, slow down default 0 %
	int32_t s32_overshootdistance_um;	// [um]  overshoot distance val for sensor ramstroke in um
	int32_t s32_overshoottargetval_um;	// [um]  overshoot target val for sensor ramstroke in um
	int32_t s32_last_delta;				// [um] last calculated delta
	int32_t s32_sensval_um;				// [um]  sensor ramstroke in um
	int32_t s32_sensval_nbtg_um;		// [um]  sensor ramstroke of tailgate neighbor in um
	int32_t s32_sensval_nbhg_um;		// [um]  sensor ramstroke of headgate neighbor in um
	int32_t s32_sensval_delta_nbtg_um;	// [um]  gradient of ramstroke between own shield and tailgate neighbor in um
	int32_t s32_sensval_delta_nbhg_um;	// [um]  gradient of ramstroke between own shield and headgate neighbor in um
} tSensorSimRamStroke;

typedef struct
{
    int32_t s32LastUpdate;			// Last update of simulated sensor value
    // Sensor type specific values
    union {
    	tSensorSimPressure pressure;
    	tSensorSimRamStroke ramstroke;
    };
    int16_t s16MaxValue;
    int16_t s16MinValue;
    //struct STimeoutTime tBleedTimer;
    uint8_t u8SensorType;
} tSensorSim;

// State struct of simulated sensor
tSensorSim m_SensorSimulated[NUMBER_SIMULATED_SENSORS];

static int32_t vSensorCom_SimulateSensor_PressureSet_calculate(tSensorSim *pSensor, int32_t tIntervalMs);
static int32_t vSensorCom_SimulateSensor_PressureLower_calculate(tSensorSim *pSensor, int32_t tIntervalMs);
static int32_t vSensorCom_SimulateSensor_RamStrokePush_calculate(tSensorSim *pSensor, int32_t tIntervalMs);
static int32_t vSensorCom_SimulateSensor_RamStrokePull_calculate(tSensorSim *pSensor, int32_t tIntervalMs);

static void vSensorCom_SimulateSensor_Pressure_ScaleMin(tSensorSim *pSensor, int16_t *ps16SensorValue);
static void vSensorCom_SimulateSensor_Pressure_ScaleMax(tSensorSim *pSensor, int16_t *ps16SensorValue);
static void vSensorCom_SimulateSensor_RamStroke_ScaleMin(tSensorSim *pSensor, int16_t *ps16SensorValue);
static void vSensorCom_SimulateSensor_RamStroke_ScaleMax(tSensorSim *pSensor, int16_t *ps16SensorValue);

static void vSensorCom_SimulateSensor_PressureSet(uint32_t u32SensorIdx);
static void vSensorCom_SimulateSensor_PressureLower(uint32_t u32SensorIdx);
static void vSensorCom_SimulateSensor_RamStrokePush(uint32_t u32SensorIdx);
static void vSensorCom_SimulateSensor_RamStrokePull(uint32_t u32SensorIdx);

void IoSubSystem_Simulation_SetInitialSensorValue(uint8_t u8SensorType, uint16_t val)
{
	switch(u8SensorType)
	{
	case  SIMULATED_SENSORS_ID_LEG_LEFT:
		IoSubSystemSensor_SetPressureLeft(val);
		break;
	case  SIMULATED_SENSORS_ID_LEG_RIGHT:
		IoSubSystemSensor_SetPressureRight(val);
		break;
	case  SIMULATED_SENSORS_ID_RAMSTROKE:
		{
		uint32_t val32 = (uint32_t) val;

		val32 = (val32 *100) / Parameter_Face_Get_DepthOfCut();
		IoSubSystemSensor_SetRamStroke((uint16_t) val32);
		break;
		}
	}
}

uint16_t IoSubSystem_Simulation_GetInitialSensorValue(uint8_t u8SensorType)
{
	switch(u8SensorType)
	{
	case  SIMULATED_SENSORS_ID_LEG_LEFT:
		return IoSubSystemSensor_GetPressureLeft();
	case  SIMULATED_SENSORS_ID_LEG_RIGHT:
		return IoSubSystemSensor_GetPressureRight();
	case  SIMULATED_SENSORS_ID_RAMSTROKE:
		{
		uint32_t val32= (uint32_t) IoSubSystemSensor_GetRamStroke();

		return (uint16_t) ((val32 * Parameter_Face_Get_DepthOfCut() / 100));
		}
	}
	return 0;
}

bool bCreepAdvance_IsActive()
{
	return false;
}

void IoSubSystem_Simulation_Init(void)
{
	//printf("IoSubSystem_Simulation_Init\n");

	// Assign Sensor indexes
	m_SensorSimulated[SIMULATED_SENSORS_ID_LEG_LEFT].u8SensorType = SENSOR_TYPE_PRESSURE;
	m_SensorSimulated[SIMULATED_SENSORS_ID_LEG_RIGHT].u8SensorType = SENSOR_TYPE_PRESSURE;
	m_SensorSimulated[SIMULATED_SENSORS_ID_RAMSTROKE].u8SensorType = SENSOR_TYPE_RAMSTROKE;

    for (int u32SensorIdx = 0; u32SensorIdx < NUMBER_SIMULATED_SENSORS; u32SensorIdx++)
    {
        tSensorSim *pSensor = &m_SensorSimulated[u32SensorIdx];
        switch (pSensor->u8SensorType)
        {
        case SENSOR_TYPE_PRESSURE:
        	if(u32SensorIdx == SIMULATED_SENSORS_ID_LEG_LEFT)  Parameter_Shield_Get_MaxPressureSensor(SENSOR_LEG_LEFT);
        	if(u32SensorIdx == SIMULATED_SENSORS_ID_LEG_RIGHT)  Parameter_Shield_Get_MaxPressureSensor(SENSOR_LEG_RIGHT);
            if (0 == pSensor->s16MaxValue)
            {
                pSensor->s16MaxValue = MAX_PRESSURE_BAR;
            }
            pSensor->s16MinValue = MIN_PRESSURE_BAR;
            pSensor->pressure.bValveSetEnabled = false;
            pSensor->pressure.bValveLowerEnabled = false;
            pSensor->pressure.s32_set_dp_dT   = BAR_TO_MBAR(pSensor->s16MaxValue) / PRESSURE_SENSOR_SET_TIME;
            pSensor->pressure.s32_lower_dp_dT = BAR_TO_MBAR(pSensor->s16MaxValue) / PRESSURE_SENSOR_LOWER_TIME;
            //printf("SSim:DS%i: Min=%d Max=%d setdT=%ld lowdT=%ld\r\n", u32SensorIdx, pSensor->s16MinValue, pSensor->s16MaxValue, pSensor->pressure.s32_set_dp_dT, pSensor->pressure.s32_lower_dp_dT);
            // Set initial value for simulation
            if(u32SensorIdx == SIMULATED_SENSORS_ID_LEG_LEFT) IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, Parameter_Shield_Get_MaxPressureNSA(SENSOR_LEG_LEFT));
            if(u32SensorIdx == SIMULATED_SENSORS_ID_LEG_RIGHT) IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, Parameter_Shield_Get_MaxPressureNSA(SENSOR_LEG_RIGHT));
            pSensor->pressure.s32_sensval_mbar = BAR_TO_MBAR((int32_t) pSensor->s16MaxValue);
            break;

        case SENSOR_TYPE_RAMSTROKE:
            pSensor->s16MaxValue = Parameter_Shield_Get_LengthRamCylinder();
            if (0 == pSensor->s16MaxValue)
            {
                pSensor->s16MaxValue = MAX_RAMSTROKE_MM;
            }
            pSensor->s16MinValue = MIN_RAMSTROKE_MM;
            pSensor->ramstroke.bValvePushEnabled = false;
            pSensor->ramstroke.bValvePullEnabled = false;
            pSensor->ramstroke.u8OvershootState = OVERSHOOT_STATE_IDLE;
            pSensor->ramstroke.s32_push_dx_dT = MM_TO_UM(pSensor->s16MaxValue) / RAMSTROKE_SENSOR_PUSH_TIME;
			pSensor->ramstroke.pushWear = 0;
            pSensor->ramstroke.s32_pull_dx_dT = MM_TO_UM(pSensor->s16MaxValue) / RAMSTROKE_SENSOR_PULL_TIME;
            pSensor->ramstroke.pullWear = 0;
            //printf ("SSim:RAM%i Min=%d Max=%d pushdT=%ld pulldT=%ld\r\n", u32SensorIdx, pSensor->s16MinValue, pSensor->s16MaxValue, pSensor->ramstroke.s32_push_dx_dT, pSensor->ramstroke.s32_pull_dx_dT);
            pSensor->ramstroke.bHasNeighborHG = false; //bNBData_HasLeft_NachbarStrebschild();
            pSensor->ramstroke.bHasNeighborTG = false; //bNBData_HasRight_NachbarStrebschild();
            pSensor->ramstroke.s32_sensval_nbhg_um = (int32_t) -1;	// Force to initialize
			pSensor->ramstroke.s32_sensval_nbtg_um = (int32_t) -1;
#if 0
			// Use ASG Number to have diffrent target values per shield
			pSensor->ramstroke.s32_overshootdistance_um = MM_TO_UM(((1 + (FRAMVARIABLEN.u16ShieldNr % OVERSHOOT_RAM_STROKE_DIST_PERCENT)) * pSensor->s16MaxValue) / 100);
#else
			// Use constant overshoot offset
			pSensor->ramstroke.s32_overshootdistance_um = MM_TO_UM((OVERSHOOT_RAM_STROKE_DIST_PERCENT * Parameter_Face_Get_DepthOfCut()) / 100);
#endif
			pSensor->ramstroke.s32_overshoottargetval_um = (int32_t) -1;
            //printf("SSim:RAM%i:NB:TG=%d HG=%d\r\n", u32SensorIdx, pSensor->ramstroke.bHasNeighborTG, pSensor->ramstroke.bHasNeighborHG);
            // Set initial value for simulation
            IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, (Parameter_Face_Get_DepthOfCut() * INIT_VALUE_RAMSTROKE) / 100);
            pSensor->ramstroke.s32_sensval_um = MM_TO_UM((int32_t) IoSubSystem_Simulation_GetInitialSensorValue(u32SensorIdx));
            break;

        default:
            break;
        }
    } // for (u32SensorIdx = 0; ....
}

/*!
 * \brief  Simuliert den entsprechenden Sensor
 * \param  Kartenindex (Adresse minus eins)
 * \param  Sensorindex (0, 1 oder 2)
 *
 * Called in 10ms from MainTask
 * --> tatsaechliche Zeit merken und Ventil über angegebene Rate veraendern
 * #define
 */
void vSensorCom_SimulateSensorExecute(void)
{
    uint32_t u32SensorIdx;

	for (u32SensorIdx = 0; u32SensorIdx < NUMBER_SIMULATED_SENSORS; u32SensorIdx++)
	{
		tSensorSim *pSensor = &m_SensorSimulated[u32SensorIdx]; //[u32BoardIdx].pSensor[u32SensorIdx];

		switch (pSensor->u8SensorType)
		{
		case SENSOR_TYPE_PRESSURE:
			if (IoSubSystemValves_GetValve_Setting() == true)
			{
				pSensor->pressure.bValveLowerEnabled = false;
				vSensorCom_SimulateSensor_PressureSet(u32SensorIdx);
			}
			else if (IoSubSystemValves_GetValve_Lowering() == true)
			{
				pSensor->pressure.bValveSetEnabled = false;
				vSensorCom_SimulateSensor_PressureLower(u32SensorIdx);
			}
			else
			{
				pSensor->pressure.bValveSetEnabled = false;
				pSensor->pressure.bValveLowerEnabled = false;
			}
			break;

		case SENSOR_TYPE_RAMSTROKE:
			if (IoSubSystemValves_GetValve_PushShield() == true)
			{
				pSensor->ramstroke.bValvePullEnabled = false;
				vSensorCom_SimulateSensor_RamStrokePush(u32SensorIdx);
			}
			else if (IoSubSystemValves_GetValve_PullShield() == true)
			{
				pSensor->ramstroke.bValvePushEnabled = false;
				vSensorCom_SimulateSensor_RamStrokePull(u32SensorIdx);
			}
			break;

		default:
			break;
		}	// switch (pSensor->u8SensorID)
	}	// for (u32SensorIdx = 0; .....
}


// Valid pointer ensured by called
// tIntervalMs : time difference between two sensor value calculations
static int32_t vSensorCom_SimulateSensor_PressureSet_calculate(tSensorSim *pSensor, int32_t tIntervalMs)
{
	// Currently we assume a linear characteric curve for change of the pressure over time
	// but in future a more sophisticated calculation is possible
	return tIntervalMs * pSensor->pressure.s32_set_dp_dT;
}

// Valid pointer ensured by called
// tIntervalMs : time difference between two sensor value calculations
static int32_t vSensorCom_SimulateSensor_PressureLower_calculate(tSensorSim *pSensor, int32_t tIntervalMs)
{
	// Currently we assume a linear characteric curve for change of the pressure over time
	// but in future a more sophisticated calculation is possible
	return tIntervalMs * pSensor->pressure.s32_lower_dp_dT;
}

// Valid pointer ensured by called
// tIntervalMs : time difference between two sensor value calculations
static int32_t vSensorCom_SimulateSensor_RamStrokePush_calculate(tSensorSim *pSensor, int32_t tIntervalMs)
{
	// Currently we assume a linear characteric curve for change of ram stroke over time
	// but in future a more sophisticated calculation is possible
	return tIntervalMs * pSensor->ramstroke.s32_push_dx_dT * (100 - pSensor->ramstroke.pushWear) / 100;
}

// Valid pointer ensured by called
// tIntervalMs : time difference between two sensor value calculations
static int32_t vSensorCom_SimulateSensor_RamStrokePull_calculate(tSensorSim *pSensor, int32_t tIntervalMs)
{
	// Currently we assume a linear characteric curve for change of ram stroke over time
	// but in future a more sophisticated calculation is possible
	if(bCreepAdvance_IsActive())
	{
		pSensor->ramstroke.pullWear = CREEPADVANCE_SLOWDOWN;
	}
	else
	{
		pSensor->ramstroke.pullWear = 0;		// Return to normal
	}
	return tIntervalMs * pSensor->ramstroke.s32_pull_dx_dT * (100 - pSensor->ramstroke.pullWear) / 100;
}

static void vSensorCom_SimulateSensor_Pressure_ScaleMin(tSensorSim *pSensor, int16_t *ps16SensorValue)
{
	int32_t s32PresVal_bar = MBAR_TO_BAR(pSensor->pressure.s32_sensval_mbar);	// scale back to [bar]

	*ps16SensorValue = (int16_t) s32PresVal_bar;			// Set new sensor value and scale back to 16bit
	if (*ps16SensorValue < pSensor->s16MinValue)		// Limit
	{
		*ps16SensorValue = pSensor->s16MinValue;
		pSensor->pressure.s32_sensval_mbar = BAR_TO_MBAR((int32_t) pSensor->s16MinValue);
	}
}

static void vSensorCom_SimulateSensor_Pressure_ScaleMax(tSensorSim *pSensor, int16_t *ps16SensorValue)
{
	int32_t s32PresVal_bar = MBAR_TO_BAR(pSensor->pressure.s32_sensval_mbar);	// scale back to [bar]

	*ps16SensorValue = (int16_t) s32PresVal_bar;			// Set new sensor value and scale back to 16bit
	if (*ps16SensorValue > pSensor->s16MaxValue)		// Limit
	{
		*ps16SensorValue = pSensor->s16MaxValue;
		pSensor->pressure.s32_sensval_mbar = BAR_TO_MBAR((int32_t) pSensor->s16MaxValue);
	}
}

static void vSensorCom_SimulateSensor_RamStroke_ScaleMin(tSensorSim *pSensor, int16_t *ps16SensorValue)
{
	int32_t s32RamStrokeVal_mm = UM_TO_MM(pSensor->ramstroke.s32_sensval_um);	// scale back to [mm]

	*ps16SensorValue = (int16_t) s32RamStrokeVal_mm;		// Set new sensor value and scale back to 16bit
    if (*ps16SensorValue < pSensor->s16MinValue)		// Limit
    {
        *ps16SensorValue = pSensor->s16MinValue;
        pSensor->ramstroke.s32_sensval_um = MM_TO_UM((int32_t) pSensor->s16MinValue);
    }
}

static void vSensorCom_SimulateSensor_RamStroke_ScaleMax(tSensorSim *pSensor, int16_t *ps16SensorValue)
{
	int32_t s32RamStrokeVal_mm = UM_TO_MM(pSensor->ramstroke.s32_sensval_um);	// scale back to [mm]

	*ps16SensorValue = (int16_t) s32RamStrokeVal_mm;		// Set new sensor value and scale back to 16bit
    if (*ps16SensorValue > pSensor->s16MaxValue)		// Limit
    {
        *ps16SensorValue = pSensor->s16MaxValue;
        pSensor->ramstroke.s32_sensval_um = MM_TO_UM((int32_t) pSensor->s16MaxValue);
    }
}

static void vSensorCom_SimulateSensor_PressureSet(uint32_t u32SensorIdx)
{
	// Valid boundaries ensured by caller
	tSensorSim *pSensor = &m_SensorSimulated[u32SensorIdx];
	int16_t s16SensorValue = IoSubSystem_Simulation_GetInitialSensorValue(u32SensorIdx);
	//s16 *ps16SensorValue = &m_pSensorBoardSimulated[u32BoardIdx].nData.s16_ValueS[u32SensorIdx];
	int32_t tInterval;

	if(pSensor->pressure.bValveSetEnabled == false)
	{
		// Valve has been enabled prepare calculation
		pSensor->pressure.bValveSetEnabled = true;
		pSensor->s32LastUpdate = s32Time_Akt();
		pSensor->pressure.s32_sensval_mbar = BAR_TO_MBAR((int32_t) s16SensorValue);
	}

	tInterval = s32Time_Akt() - pSensor->s32LastUpdate; // [ms]
	if(tInterval > 0)
	{
		int32_t s32Delta_mbar = vSensorCom_SimulateSensor_PressureSet_calculate(pSensor, tInterval); // [mbar] Pressure change in mbar for given interval in [ms]

		pSensor->pressure.s32_sensval_mbar += s32Delta_mbar;
		vSensorCom_SimulateSensor_Pressure_ScaleMax(pSensor, &s16SensorValue);
		IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, s16SensorValue); // Set val was done before via pointer
        //printf("SSim:SET:DS%li: p=%d d=%ld mbar=%ld\r\n", u32SensorIdx, s16SensorValue, s32Delta_mbar, pSensor->pressure.s32_sensval_mbar);
    	// Store last time for next call
    	pSensor->s32LastUpdate = s32Time_Akt();
	}
}

static void vSensorCom_SimulateSensor_PressureLower(uint32_t u32SensorIdx)
{
	// Valid boundaries ensured by caller
	tSensorSim *pSensor = &m_SensorSimulated[u32SensorIdx];
	int16_t s16SensorValue = IoSubSystem_Simulation_GetInitialSensorValue(u32SensorIdx);
	//s16 *ps16SensorValue = &m_pSensorBoardSimulated[u32BoardIdx].nData.s16_ValueS[u32SensorIdx];
	int32_t tInterval;

	if(pSensor->pressure.bValveLowerEnabled == false)
	{
		// Valve has been enabled prepare calculation
		pSensor->pressure.bValveLowerEnabled = true;
		pSensor->s32LastUpdate = s32Time_Akt();
		pSensor->pressure.s32_sensval_mbar = BAR_TO_MBAR((int32_t) s16SensorValue);
	}

	tInterval = s32Time_Akt() - pSensor->s32LastUpdate; // [ms]
	if(tInterval > 0)
	{
		int32_t s32Delta_mbar = vSensorCom_SimulateSensor_PressureLower_calculate(pSensor, tInterval); // [mbar] Pressure change in mbar for given interval in [ms]

		pSensor->pressure.s32_sensval_mbar -= s32Delta_mbar;
		vSensorCom_SimulateSensor_Pressure_ScaleMin(pSensor, &s16SensorValue);
		IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, s16SensorValue); // Set val was done before via pointer
		//printf("SSim:LOW:DS%li: p=%d d=%ld mbar=%ld\r\n", u32SensorIdx, s16SensorValue, s32Delta_mbar, pSensor->pressure.s32_sensval_mbar);
		// Store last time for next call
		pSensor->s32LastUpdate = s32Time_Akt();
	}
}

static void vSensorCom_SimulateSensor_RamStrokePush(uint32_t u32SensorIdx)
{
	// Valid boundaries ensured by caller
	tSensorSim *pSensor = &m_SensorSimulated[u32SensorIdx];
	int16_t s16SensorValue = IoSubSystem_Simulation_GetInitialSensorValue(u32SensorIdx);
	//s16 *ps16SensorValue = &m_pSensorBoardSimulated[u32BoardIdx].nData.s16_ValueS[u32SensorIdx];
	int32_t tInterval;

	if(pSensor->ramstroke.bValvePushEnabled == false)
	{
		// Valve has been enabled prepare calculation
		pSensor->ramstroke.bValvePushEnabled = true;
		pSensor->s32LastUpdate = s32Time_Akt();
		pSensor->ramstroke.s32_sensval_um = MM_TO_UM((int32_t) s16SensorValue);
	}

	tInterval = s32Time_Akt() - pSensor->s32LastUpdate; // [ms]
	if(tInterval > 0)
	{
		int32_t s32Delta_um = vSensorCom_SimulateSensor_RamStrokePush_calculate(pSensor, tInterval); // [um] ram stroke change in um for given interval in [ms]

		pSensor->ramstroke.s32_sensval_um += s32Delta_um;
		vSensorCom_SimulateSensor_RamStroke_ScaleMax(pSensor, &s16SensorValue);
		IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, s16SensorValue); // Set val was done before via pointer
        //printf("SSim:PUSH:RS%li: p=%d d=%ld um=%ld\r\n", u32SensorIdx, s16SensorValue, s32Delta_um, pSensor->ramstroke.s32_sensval_um);
    	// Store last time for next call
    	pSensor->s32LastUpdate = s32Time_Akt();
	}
}

static void vSensorCom_SimulateSensor_RamStrokePull(uint32_t u32SensorIdx)
{
	// Valid boundaries ensured by caller
	tSensorSim *pSensor = &m_SensorSimulated[u32SensorIdx];
	int16_t s16SensorValue = IoSubSystem_Simulation_GetInitialSensorValue(u32SensorIdx);
	//s16 *ps16SensorValue = &m_pSensorBoardSimulated[u32BoardIdx].nData.s16_ValueS[u32SensorIdx];
	int32_t tInterval;

	if(pSensor->ramstroke.bValvePullEnabled == false)
	{
		// Valve has been enabled prepare calculation
		pSensor->ramstroke.bValvePullEnabled = true;
		pSensor->s32LastUpdate = s32Time_Akt();
		pSensor->ramstroke.s32_sensval_um = MM_TO_UM((int32_t) s16SensorValue);
	}

	tInterval = s32Time_Akt() - pSensor->s32LastUpdate; // [ms]
	if(tInterval > 0)
	{
		int32_t s32Delta_um = vSensorCom_SimulateSensor_RamStrokePull_calculate(pSensor, tInterval); // [um] ram stroke change in um for given interval in [ms]

		pSensor->ramstroke.s32_last_delta = s32Delta_um;
		pSensor->ramstroke.s32_sensval_um -= s32Delta_um;
		vSensorCom_SimulateSensor_RamStroke_ScaleMin(pSensor, &s16SensorValue);
		IoSubSystem_Simulation_SetInitialSensorValue(u32SensorIdx, s16SensorValue); // Set val was done before via pointer
		//printf("SSim:PULL:RS%li: p=%d d=%ld um=%ld\r\n", u32SensorIdx, s16SensorValue, s32Delta_um, pSensor->ramstroke.s32_sensval_um);
		// Store last time for next call
		pSensor->s32LastUpdate = s32Time_Akt();
	}
}

