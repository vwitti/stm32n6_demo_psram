#ifndef KV11_KEYS_H
#define KV11_KEYS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ########################## IDS FOR IO VALUES ##########################
#define KV11_ID_VALVE_LOWER					(1)
#define KV11_ID_VALVE_SET					(2)
#define KV11_ID_VALVE_PULL					(3)
#define KV11_ID_VALVE_PUSH					(4)
#define KV11_ID_VALVE_PULL_CREEP			(5)
#define KV11_ID_VALVE_BASELIFT_EXT			(6)
#define KV11_ID_VALVE_BASELIFT_RET			(7)
#define KV11_ID_VALVE_STABCYL_EXT			(8)
#define KV11_ID_VALVE_STABCYL_RET			(9)
#define KV11_ID_SENSOR_PRESSURE_LEG_LEFT	(10)
#define KV11_ID_SENSOR_PRESSURE_LEG_RIGHT	(12)
#define KV11_ID_SENSOR_RAM_STROKE			(13)
#define KV11_ID_EVENTS_LAS_PREWARN_ACTIVE	(14)
#define KV11_ID_EVENTS_LAS_ERROR_CODE		(15)

#ifdef __cplusplus
}
#endif

#endif /* KV11_KEYS_H */
