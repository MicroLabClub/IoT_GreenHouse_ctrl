#ifndef SRV_OS_TASK_H
#define SRV_OS_TASK_H

// Include any necessary libraries or headers
#include "ecu_config.h"

// Define any constants or macros


//=============================================================================
// time base definitions
//-----------------------------------------------------------------------------
#ifdef SYS_TICK
#define SYS_TICK (10.0)
#endif
#ifndef TIME_SEC
#define TIME_SEC (1000 )
#endif
#ifndef TIME_MIN
#define TIME_MIN (60 * TIME_SEC)
#endif
#ifndef TIME_HOUR
#define TIME_HOUR (60 * TIME_MIN)
#endif
#ifndef TIME_DAY
#define TIME_DAY (24 * TIMTIME_HOUR)   
#endif

//=============================================================================
// Task Scheduling definitions
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_VENT
#ifndef CTRL_TEMP_VENT_REC
#define CTRL_TEMP_VENT_REC (60 * TIME_SEC)
#endif
#ifndef CTRL_TEMP_VENT_OFFSET
#define CTRL_TEMP_VENT_OFFSET (61 * TIME_SEC)
#endif
#endif

#ifdef USE_CTRL_SOIL_MOIST
#ifndef CTRL_SOIL_MOIST_REC
#define CTRL_SOIL_MOIST_REC (60 * TIME_SEC)
#endif
#ifndef CTRL_SOIL_MOIST_OFFSET
#define CTRL_SOIL_MOIST_OFFSET
#endif
#endif

#ifdef USE_CTRL_TEMP_HEAT
#ifndef CTRL_TEMP_HEAT_REC
#define CTRL_TEMP_HEAT_REC (10000 )
#endif
#ifndef CTRL_TEMP_HEAT_OFFSET
#define CTRL_TEMP_HEAT_OFFSET CTRL_TEMP_HEAT_REC + 3
#endif
#endif

#ifdef USE_CTRL_LIGHTS
#ifndef CTRL_LIGHTS_REC
#define CTRL_LIGHTS_REC (10000 )
#endif
#ifndef CTRL_LIGHTS_OFFSET
#define CTRL_LIGHTS_OFFSET CTRL_LIGHTS_REC + 4
#endif
#endif

#ifdef USE_CTRL_PRESS_ISOL
#ifndef CTRL_PRESS_ISOL_REC
#define CTRL_PRESS_ISOL_REC (100 )
#endif
#ifndef CTRL_PRESS_ISOL_OFFSET
#define CTRL_PRESS_ISOL_OFFSET CTRL_PRESS_ISOL_REC + 5
#endif
#endif

#ifdef USE_CTRL_AIR_HUM
#ifndef CTRL_AIR_HUM_REC
#define CTRL_AIR_HUM_REC (60000 )
#endif
#ifndef CTRL_AIR_HUM_OFFSET
#define CTRL_AIR_HUM_OFFSET CTRL_AIR_HUM_REC + 6
#endif
#endif

#ifdef USE_SRV_UI_SERIAL
#ifndef TERMINAL_IN_REC
#define TERMINAL_IN_REC (1 )
#endif
#ifndef TERMINAL_IN_OFFSET
#define TERMINAL_IN_OFFSET 4
#endif

#endif

#ifdef USE_SRV_UI_SERIAL
#ifndef TERMINAL_OUT_REC
#define TERMINAL_OUT_REC (2000 )
#endif

#ifndef TERMINAL_OUT_OFFSET
#define TERMINAL_OUT_OFFSET 5
#endif

#endif

#ifdef USE_SRV_COM_MQTT
#ifndef SRV_COM_MQTT_REC
#define SRV_COM_MQTT_REC (1 * TIME_SEC)
#endif
#ifndef SRV_COM_MQTT_OFFSET
#define SRV_COM_MQTT_OFFSET (5 * TIME_SEC)
#endif
#endif

#ifdef USE_SRV_SNS_AIR_TEMP
#ifndef SRV_SNS_AIR_TEMP_REC
#define SRV_SNS_AIR_TEMP_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AIR_TEMP_OFFSET
#define SRV_SNS_AIR_TEMP_OFFSET 50
#endif
#endif

#ifdef USE_SRV_SNS_AIR_HUM
#ifndef SRV_SNS_AIR_HUM_REC
#define SRV_SNS_AIR_HUM_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AIR_HUM_OFFSET
#define SRV_SNS_AIR_HUM_OFFSET 50
#endif
#endif

#ifdef USE_ED_DHT
#ifndef ED_DHT_REC
#define ED_DHT_REC (100 )
#endif
#ifndef ED_DHT_OFFSET
#define ED_DHT_OFFSET 2
#endif
#endif

#ifdef USE_ED_BMP
#ifndef ED_BMP_REC
#define ED_BMP_REC (100 )
#endif
#ifndef ED_BMP_OFFSET
#define ED_BMP_OFFSET 1
#endif
#endif

#ifdef USE_ed_sns_soil_moist
#ifndef ed_sns_soil_moist_REC
#define ed_sns_soil_moist_REC (100 )
#endif
#ifndef ed_sns_soil_moist_OFFSET
#define ed_sns_soil_moist_OFFSET 3
#endif
#endif

// Actuators definitions

#ifdef USE_ED_RELAY
#ifndef ED_RELAY_REC
#define ED_RELAY_REC (100 )
#endif
#ifndef ED_RELAY_OFFSET
#define ED_RELAY_OFFSET 5
#endif
#endif

#ifdef USE_DD_HEATER
#ifndef DD_HEATER_REC
#define DD_HEATER_REC (100 )
#endif
#ifndef DD_HEATER_OFFSET
#define DD_HEATER_OFFSET 11
#endif
#endif

#ifdef USE_DD_LIGHTS
#ifndef DD_LIGHTS_REC
#define DD_LIGHTS_REC (100 )
#endif
#ifndef DD_LIGHTS_OFFSET
#define DD_LIGHTS_OFFSET 12
#endif
#endif

#ifdef USE_DD_VALVE
#ifndef DD_VALVE_REC
#define DD_VALVE_REC (100 )
#endif
#ifndef DD_VALVE_OFFSET
#define DD_VALVE_OFFSET 13
#endif
#endif

#ifdef USE_DD_WINDOW
#ifndef DD_WINDOW_REC
#define DD_WINDOW_REC (100 )
#endif
#ifndef DD_WINDOW_OFFSET
#define DD_WINDOW_OFFSET 14
#endif
#endif

#ifdef USE_SRV_HERTBEAT
#ifndef SRV_BLINK_REC
#define SRV_BLINK_REC (500 )
#endif
#ifndef SRV_BLINK_OFFSET
#define SRV_BLINK_OFFSET 10
#endif
#endif



// Declare any global variables or functions

#endif // SRV_OS_TASK_H
