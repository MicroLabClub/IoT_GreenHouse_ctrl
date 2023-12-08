
#include "ecu_config.h"

#include <Arduino.h>

#include <SPI.h>
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
#ifdef USE_CTRL_LIGHTS
#include "ctrl_lights/ctrl_lights.h"
#endif
#ifdef USE_CTRL_PRESS_ISOL
#include "ctrl_press_isol/ctrl_press_isol.h"
#endif
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moisture/ctrl_soil_moisture.h"
#endif

//=============================================================================
// Platform Services
//-----------------------------------------------------------------------------
#ifdef USE_OS_SEQ_TASK
#include "os_seq_task/os_seq_task.h"
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
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay.h"
#endif
#ifdef USE_ED_SN_MOIST
#include "ed_sns_moist/ed_sns_moist.h"
#endif

//=============================================================================
// time base definitions
//-----------------------------------------------------------------------------
#define SYS_TICK 10
#define TIME_SEC (1000 / SYS_TICK)
#define TIME_MIN (60 * TIME_SEC)
#define TIME_HOUR (60 * TIME_MIN)
#define TIME_DAY (24 * TIMTIME_HOURE_MIN)

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
int ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_OFFSET;
#endif

#ifdef USE_CTRL_SOIL_MOIST
#ifndef CTRL_SOIL_MOIST_REC
#define CTRL_SOIL_MOIST_REC (60 * TIME_SEC)
#endif
#ifndef CTRL_SOIL_MOIST_OFFSET
#define CTRL_SOIL_MOIST_OFFSET
int ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC + 1;
#endif
#endif

#ifdef USE_CTRL_TEMP_HEAT
#ifndef CTRL_TEMP_HEAT_REC
#define CTRL_TEMP_HEAT_REC (10000 / SYS_TICK)
#endif
#ifndef CTRL_TEMP_HEAT_OFFSET
#define CTRL_TEMP_HEAT_OFFSET CTRL_TEMP_HEAT_REC + 3
#endif
int ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_OFFSET;
#endif

#ifdef USE_CTRL_LIGHTS
#ifndef
#define CTRL_LIGHTS_REC (10000 / SYS_TICK)
#endif
#ifndef CTRL_LIGHTS_OFFSET
#define CTRL_LIGHTS_OFFSET CTRL_LIGHTS_REC + 4
#endif
int ctrl_lights_rec_cnt = CTRL_LIGHTS_OFFSET;
#endif

#ifdef USE_CTRL_PRESS_ISOL
#ifndef CTRL_PRESS_ISOL_REC
#define CTRL_PRESS_ISOL_REC (100 / SYS_TICK)
#endif
#ifndef CTRL_PRESS_ISOL_OFFSET
#define CTRL_PRESS_ISOL_OFFSET CTRL_PRESS_ISOL_REC + 5
#endif
int ctrl_press_isol_rec_cnt = CTRL_PRESS_ISOL_OFFSET;
#endif

#ifdef USE_CTRL_AIR_HUM
#ifndef CTRL_AIR_HUM_REC
#define CTRL_AIR_HUM_REC (60000 / SYS_TICK)
#endif
#ifndef CTRL_AIR_HUM_OFFSET
#define CTRL_AIR_HUM_OFFSET CTRL_AIR_HUM_REC + 6
#endif
int ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_OFFSET;
#endif

#ifdef USE_SRV_UI_SERIAL
#ifndef TERMINAL_IN_REC
#define TERMINAL_IN_REC (1 / SYS_TICK)
#endif
#ifndef TERMINAL_IN_OFFSET
#define TERMINAL_IN_OFFSET 4
#endif

int terminal_in_rec_cnt = TERMINAL_IN_OFFSET;
#endif

#ifdef USE_SRV_UI_SERIAL
#ifndef TERMINAL_OUT_REC
#define TERMINAL_OUT_REC (2000 / SYS_TICK)
#endif

#ifndef TERMINAL_OUT_OFFSET
#define TERMINAL_OUT_OFFSET 5
#endif

int terminal_our_rec_cnt = TERMINAL_OUT_OFFSET;
#endif

#ifdef USE_SRV_SNS_AIR_TEMP
#ifndef SRV_SNS_AIR_TEMP_REC
#define SRV_SNS_AIR_TEMP_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AIR_TEMP_OFFSET
#define SRV_SNS_AIR_TEMP_OFFSET 50
#endif
int srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_OFFSET;
#endif


#ifdef USE_ED_DHT
#ifndef ED_DHT_REC
#define ED_DHT_REC (100 / SYS_TICK)
#endif
#ifndef ED_DHT_OFFSET
#define ED_DHT_OFFSET 2
#endif
int ed_dht_rec_cnt = ED_DHT_OFFSET;
#endif

#ifdef USE_ED_BMP
#ifndef ED_BMP_REC
#define ED_BMP_REC (100 / SYS_TICK)
#endif
#ifndef ED_BMP_OFFSET
#define ED_BMP_OFFSET 1
#endif
int ed_bmp_rec_cnt = ED_BMP_OFFSET;
#endif

#ifdef USE_ED_SNS_MOIST
#ifndef ED_SNS_MOIST_REC
#define ED_SNS_MOIST_REC (100 / SYS_TICK)
#endif
#ifndef ED_SNS_MOIST_OFFSET
#define ED_SNS_MOIST_OFFSET 3
#endif
int ed_sns_moist_rec_cnt = ED_SNS_MOIST_OFFSET;
#endif

// Actuators definitions

#ifdef USE_ED_RELAY
#ifndef ED_RELAY_REC
#define ED_RELAY_REC (100 / SYS_TICK)
#endif
#ifndef ED_RELAY_OFFSET
#define ED_RELAY_OFFSET 5
#endif
int ed_relay_rec_cnt = ED_RELAY_OFFSET;
#endif

#ifdef USE_DD_HEATER
#ifndef DD_HEATER_REC
#define DD_HEATER_REC (100 / SYS_TICK)
#endif
#ifndef DD_HEATER_OFFSET
#define DD_HEATER_OFFSET 11
#endif
int dd_heater_rec_cnt = DD_HEATER_OFFSET;
#endif

#ifdef USE_DD_LIGHTS
#ifndef DD_LIGHTS_REC
#define DD_LIGHTS_REC (100 / SYS_TICK)
#endif
#ifndef DD_LIGHTS_OFFSET
#define DD_LIGHTS_OFFSET 12
#endif
int dd_lights_rec_cnt = DD_LIGHTS_OFFSET;
#endif

#ifdef USE_DD_VALVE
#ifndef DD_VALVE_REC
#define DD_VALVE_REC (100 / SYS_TICK)
#endif
#ifndef DD_VALVE_OFFSET
#define DD_VALVE_OFFSET 13
#endif
int dd_valve_rec_cnt = DD_VALVE_OFFSET;
#endif

#ifdef USE_DD_WINDOW
#ifndef DD_WINDOW_REC
#define DD_WINDOW_REC (100 / SYS_TICK)
#endif
#ifndef DD_WINDOW_OFFSET
#define DD_WINDOW_OFFSET 14
#endif
int dd_window_rec_cnt = DD_WINDOW_OFFSET;
#endif



void os_seq_scheduler();

void setup()
{
  // initialize services
#ifdef USE_SRV_UI_SERIAL
  srv_ui_serial_setup();
#endif
#ifdef USE_SRV_COM_MQTT
  srv_com_mqtt_setup();
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
  srv_sns_air_temp_setup();
#endif

  // Initialize electronic devices
#ifdef USE_ED_DHT
  ed_dht_setup();
#endif
#ifdef USE_ED_BMP
  ed_bmp_setup();
#endif
#ifdef USE_ED_RELAY
  ed_relay_setup();
#endif
#ifdef USE_ED_SN_MOIST
  ed_sns_moist_setup();
#endif

  // initialize device drivers
#ifdef USE_DD_WINDOW
  dd_window_setup();
#endif
#ifdef USE_DD_HEATER
  dd_heater_setup();
#endif
#ifdef USE_DD_LIGHTS
  dd_lights_setup();
#endif
#ifdef USE_DD_VALVE
  dd_valve_setup();
#endif

  // initialize control components
#ifdef USE_CTRL_TEMP_VENT
  ctrl_temp_vent_setup();
#endif
#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_setup();
#endif
#ifdef USE_CTRL_LIGHTS
  ctrl_lights_setup();
#endif
#ifdef USE_CTRL_PRESS_ISOL
  ctrl_press_isol_setup();
#endif
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_setup();
#endif
#ifdef USE_CTRL_TEMP_HEAT
  ctrl_temp_heat_setup();
#endif
}

void loop()
{
  // Task Scheduler
  os_seq_scheduler();
  // Ensuring a pause for recurrence
  delay(SYS_TICK);
}

void os_seq_scheduler()
{
#ifdef USE_SRV_UI_SERIAL
  // Task Scheduler
  // Task for periodic reporting of signals in serial terminal
  if (--terminal_our_rec_cnt <= 0)
  {
    srv_ui_serial_out_loop();
    terminal_our_rec_cnt = TERMINAL_OUT_REC;
  }
#endif

#ifdef USE_SRV_UI_SERIAL
  // Task for reading commands from the serial terminal
  if (--terminal_in_rec_cnt <= 0)
  {
    srv_ui_serial_in_loop();
    terminal_in_rec_cnt = TERMINAL_IN_REC;
  }
#endif

#ifdef USE_ED_DHT
  // Task for collecting data from the DHT11 sensor
  if (--ed_dht_rec_cnt <= 0)
  {
    ed_dht_loop();
    ed_dht_rec_cnt = ED_DHT_REC;
  }
#endif

#ifdef USE_SRV_SNS_AIR_TEMP
  // Task for collecting data from the air temperature sensor
  if (--srv_sns_air_temp_rec_cnt <= 0)
  {
    srv_sns_air_temp_loop();
    srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_REC;
  }
#endif

#ifdef USE_ED_RELAY
  // Task for managing the relay
  if (--ed_relay_rec_cnt <= 0)
  {
    ed_relay_loop();
    ed_relay_rec_cnt = ED_RELAY_REC;
  }
#endif

#ifdef USE_DD_WINDOW
  // Task for managing the windows
  if (--dd_window_rec_cnt <= 0)
  {
    dd_window_loop();
    dd_window_rec_cnt = DD_WINDOW_REC;
  }
#endif

#ifdef USE_CTRL_TEMP_VENT
  // Task for temperature control with ventilation
  if (--ctrl_temp_vent_rec_cnt <= 0)
  {
    ctrl_temp_vent_loop();
    ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_REC;
  }
#endif

#ifdef USE_ED_BMP
  // Task for collecting data from the BMP sensor
  if (--ed_bmp_rec_cnt <= 0)
  {
    ed_bmp_loop();
    ed_bmp_rec_cnt = ED_BMP_REC;
  }
#endif
#ifdef USE_ED_SNS_MOIST
  // Task for collecting data from the soil moisture sensor
  if (--ed_sns_moist_rec_cnt <= 0)
  {
    ed_sns_moist_loop();
    ed_sns_moist_rec_cnt = ED_SNS_MOIST_REC;
  }
#endif
#ifdef USE_DD_HEATER
  // Task for managing the heater
  if (--dd_heater_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_heater_rec_cnt = DD_HEATER_REC;
  }
#endif
#ifdef USE_DD_LIGHTS
  // Task for managing the lights
  if (--dd_lights_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_lights_rec_cnt = DD_LIGHTS_REC;
  }
#endif
#ifdef USE_DD_VALVE
  // Task for managing the valve
  if (--dd_valve_rec_cnt <= 0)
  {
    dd_valve_loop();
    dd_valve_rec_cnt = DD_VALVE_REC;
  }
#endif
#ifdef USE_CTRL_SOIL_MOIST
  // Task for soil moisture control
  if (--ctrl_soil_moist_rec_cnt <= 0)
  {
    ctrl_soil_moist_loop();
    ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC;
  }
#endif
#ifdef USE_CTRL_TEMP_HEAT
  // Task for temperature control with heater
  if (--ctrl_temp_heat_rec_cnt <= 0)
  {
    ctrl_temp_heat_loop();
    ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_REC;
  }
#endif
#ifdef USE_CTRL_LIGHTS
  // Task for light control
  if (--ctrl_lights_rec_cnt <= 0)
  {
    ctrl_lights_loop();
    ctrl_lights_rec_cnt = CTRL_LIGHTS_REC;
  }
#endif
#ifdef USE_CTRL_PRESS_ISOL
  // Task for pressure control with isolation
  if (--ctrl_press_isol_rec_cnt <= 0)
  {
    ctrl_press_isol_loop();
    ctrl_press_isol_rec_cnt = CTRL_PRESS_ISOL_REC;
  }
#endif
#ifdef USE_CTRL_AIR_HUM
  // Task for air humidity control
  if (--ctrl_air_hum_rec_cnt <= 0)
  {
    ctrl_air_hum_loop();
    ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_REC;
  }
#endif
}
