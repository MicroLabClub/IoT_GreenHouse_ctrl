#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

#define SYS_TICK (10.0) // ms
#define TIME_uSEC (1)

#define TIME_SEC (1000 * TIME_uSEC)
#define TIME_MIN (60 * TIME_SEC)
#define TIME_HOUR (60 * TIME_MIN)
#define TIME_DAY (24 * TIMTIME_HOURE_MIN)


#define ECU_ALL 0
#define ECU_CTRL_TEMP_VENT 1
#define ECU_CTRL_TEMP_HEAT 2
#define ECU_CTRL_SOIL_MOISTURE 3
#define ECU_CTRL_LIGHT 4
#define ECU_CTRL_PRESS_ISOL 5
#define ECU_CTRL_AIR_HUMIDITY 6

//==============================================================================
// Select configuration for ECU HERE !!
#define ECU_CONFIG ECU_CTRL_LIGHT
//==============================================================================

#if ECU_CONFIG == ECU_ALL

#define USE_SRV_UI_SERIAL

#elif ECU_CONFIG == ECU_CTRL_TEMP_VENT
#include "ecu_config_ctrl_temp_vent.h"

#elif ECU_CONFIG == ECU_CTRL_TEMP_HEAT

#include "ecu_config_ctrl_temp_heat.h"

#elif ECU_CONFIG == ECU_CTRL_LIGHT

#include "ecu_config_ctrl_lights.h"

#elif ECU_CONFIG == ECU_CTRL_PRESS_ISOL

#include "ecu_config_ctrl_press_isol.h"

#elif ECU_CONFIG == ECU_CTRL_SOIL_MOISTURE

#include "ecu_config_ctrl_soil_moisture.h"

#elif ECU_CONFIG == ECU_CTRL_AIR_HUMIDITY

#include "ecu_config_ctrl_air_hum.h"

#endif

#endif