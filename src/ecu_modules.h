#ifndef ECU_MODULES_H
#define ECU_MODULES_H

// Include any necessary libraries or headers here

#include "ecu_config.h"

//=============================================================================
// Control Modules
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_VENT
#include "ctrl_temp_vent/ctrl_temp_vent.h"
#endif
#ifdef USE_CTRL_TEMP_HEAT
#include "ctrl_temp_heat/ctrl_temp_heat.h"
#endif
#ifdef USE_CTRL_AIR_HUM
#include "ctrl_air_humidity/ctrl_air_humidity.h"
#endif
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moisture/ctrl_soil_moisture.h"
#endif
#ifdef USE_CTRL_PRESS_ISOL
#include "ctrl_press_isol/ctrl_press_isol.h"
#endif
#ifdef USE_CTRL_LIGHTS
#include "ctrl_lights/ctrl_lights.h"
#endif

//=============================================================================
// Platform Services
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HERTBEAT
#include "srv_hertbeat/srv_hertbeat.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_OS_TASK_SEQ
#include "srv_os_task/srv_os_task_seq.h"
#endif
//-----------------------------------------------------------------------------
#ifndef USE_SRV_OS_TASK
#include "srv_os_task/srv_os_task_freertos.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
#include "srv_ui_serial/srv_ui_serial.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MQTT
#include "srv_com_mqtt/srv_com_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_HUM
#include "srv_sns_air_hum/srv_sns_air_hum.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
#include "srv_sns_soil_moist/srv_sns_soil_moist.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMBIENT_LIGHT
#include "srv_sns_amb_light/srv_sns_amb_light.h"
#endif


//=============================================================================
// Device abstraction components
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
#include "dd_heater/dd_heater.h"
#endif
#ifdef USE_DD_LIGHTS
#include "dd_lights/dd_lights.h"
#endif
#ifdef USE_DD_VALVE
#include "dd_valve/dd_valve.h"
#endif
#ifdef USE_DD_AIR_PUMP
#include "dd_air_pump/dd_air_pump.h"
#endif
#ifdef USE_DD_WINDOW
#include "dd_window/dd_window.h"
#endif

//=============================================================================
// ECU Abstraction components
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
#include "ed_dht/ed_dht.h"
#endif
#ifdef USE_ED_BMP
#include "ed_bmp/ed_bmp.h"
#endif
#ifdef USE_ED_SN_MOIST
#include "ed_sns_moist/ed_sns_moist.h"
#endif
#ifdef USE_ED_BH1750
#include "ed_bh1750/ed_bh1750.h"
#endif
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay.h"
#endif


// Define any constants or macros here

// Declare any classes or structs here

// Declare any function prototypes here

#endif // ECU_MODULES_H
