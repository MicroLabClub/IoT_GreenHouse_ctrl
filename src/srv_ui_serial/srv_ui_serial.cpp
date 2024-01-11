#include "Arduino.h"

#include "srv_ui_serial.h"

#include "ecu_config.h"
#include "ecu_modules.h"

//-----------------------------------------------
// include Control components reports
#ifdef USE_CTRL_TEMP_HEAT
#include "ctrl_temp_heat/ctrl_temp_heat_term.h"
#endif
#ifdef USE_CTRL_TEMP_VENT
#include "ctrl_temp_vent/ctrl_temp_vent_term.h"
#endif
#ifdef USE_CTRL_AIR_HUM
#include "ctrl_air_hum/ctrl_air_hum_term.h"
#endif
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moisture/ctrl_soil_moisture_term.h"
#endif
#ifdef USE_CTRL_AIR_PRESS
#include "ctrl_air_press/ctrl_air_press_term.h"
#endif
#ifdef USE_CTRL_LIGHTS
#include "ctrl_lights/ctrl_lights_term.h"
#endif

//-----------------------------------------------
// include Sensor components reports
#ifdef USE_SRV_SNS_AIR_PRESS
#include "srv_sns_air_press/srv_sns_air_press_term.h"
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp_term.h"
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
#include "srv_sns_soil_moist/srv_sns_soil_moist_term.h"
#endif
#ifdef USE_SRV_SNS_AIR_HUM
#include "srv_sns_air_hum/srv_sns_air_hum_term.h"
#endif
#ifdef USE_SRV_SNS_LIGHT
#include "srv_sns_amb_light/srv_sns_amb_light_term.h"
#endif

//-----------------------------------------------
// include Actuator components reports
#ifdef USE_DD_WINDOW
#include "dd_window/dd_window_term.h"
#endif
#ifdef USE_DD_HEATER
#include "dd_heater/dd_heater_term.h"
#endif
#ifdef USE_DD_VALVE
#include "dd_valve/dd_valve_term.h"
#endif
#ifdef USE_DD_AIR_PUMP
#include "dd_air_pump/dd_air_pump_term.h"
#endif
#ifdef USE_DD_LIGHTS
#include "dd_lights/dd_lights_term.h"
#endif


//-----------------------------------------------
// include ECU report components
#ifdef USE_ED_DHT
#include "ed_dht/ed_dht_term.h"
#endif
#ifdef USE_ED_BMP
#include "ed_bmp/ed_bmp_term.h"
#endif
#ifdef USE_ED_BH1750
#include "ed_bh1750/ed_bh1750_term.h"
#endif
#ifdef USE_ED_SNS_MOIST
#include "ed_sns_soil_moist/ed_sns_soil_moist_term.h"
#endif
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay_term.h"
#endif




void srv_ui_serial_setup()
{
  Serial.begin(115200);
  Serial.println("IoT System started");
}

void srv_ui_serial_in_loop()
{
  if (Serial.available())
  {
    char cmd = Serial.read();

    Serial.print("IOT: Recived command: ");
    Serial.println(cmd);

    switch (cmd)
    {

    case 'z': //  manual or automat control
#if defined USE_CTRL_TEMP_VENT
      if (ctrl_temp_vent_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_TEMP_VENT:  Change mode to MANUAL");
        ctrl_temp_vent_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_TEMP_VENT:  Change mode to AUTO");
        ctrl_temp_vent_set_mode_auto();
      }
#endif
#if defined USE_DD_WINDOW
      dd_window_stop();
      Serial.println("DD_WINDOW: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_1);
      ed_relay_off(ED_RELAY_ID_2);
#else
      Serial.println("CTRL_TEMP_VENT: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;

    case 'q': // UP
#if defined USE_CTRL_TEMP_VENT
      if (ctrl_temp_vent_is_enabled())
      {
        ctrl_temp_vent_setpoint_up(0.1);
        Serial.print("CTRL_TEMP_VENT: Increase Setpoint:");
        int sp = ctrl_temp_vent_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_window_open(CTRL_TEMP_VENT_OP_D_TIME);
        Serial.println("CTRL_TEMP_VENT: Manual Window opening");
      }
#elif defined USE_DD_WINDOW
      dd_window_open(4 * TIME_SEC / DD_WINDOW_REC);
      Serial.println("DD_WINDOW: Window opening");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_1);
      ed_relay_off(ED_RELAY_ID_2);
      Serial.println("DD_WINDOW: Window opening");
#else
      Serial.println("CTRL_TEMP_VENT: OPEN/SP_Up Command <no action>");
#endif
      break;

    case 'a': // Down
#if defined USE_CTRL_TEMP_VENT
      if (ctrl_temp_vent_is_enabled())
      {
        ctrl_temp_vent_setpoint_dn(0.1);
        Serial.print("CTRL_TEMP_VENT: Decreasing Setpoint:");
        int sp = ctrl_temp_vent_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_window_close(CTRL_TEMP_VENT_OP_D_TIME);
        Serial.println(" DD_WINDOW: Window Closing");
      }
#elif defined USE_DD_WINDOW
      dd_window_close(4 * TIME_SEC / DD_WINDOW_REC);
      Serial.println("DD_WINDOW: Window closing");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_1);
      ed_relay_on(ED_RELAY_ID_2);
      Serial.println(" ED_RELAY: Window Closing");
#else
      Serial.println("CTRL_TEMP_VENT: CLOSE/SP_Dn Command <no action>");
#endif
      break;
    case 'x': //  manual or automat control
#if defined USE_CTRL_TEMP_HEAT
      if (ctrl_temp_heat_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_TEMP_HEAT:  Change mode to MANUAL");
        ctrl_temp_heat_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_TEMP_HEAT:  Change mode to AUTO");
        ctrl_temp_heat_set_mode_auto();
      }
#endif
#if defined USE_DD_HEATER
      dd_heater_off();
      Serial.println("DD_HEATER: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_3);
#else
      Serial.println("CTRL_TEMP_HEAT: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;

    case 'w': // UP
#if defined USE_CTRL_TEMP_HEAT
      if (ctrl_temp_heat_is_enabled())
      {
        ctrl_temp_heat_setpoint_up(0.1);
        Serial.print("CTRL_TEMP_HEAT: Increase Setpoint:");
        int sp = ctrl_temp_heat_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_heater_on(CTRL_TEMP_HEAT_OP_D_TIME);
        Serial.println("CTRL_TEMP_HEAT: Manual Heater ON");
      }
#elif defined USE_DD_HEATER
      dd_heater_on(CTRL_TEMP_HEAT_OP_D_TIME);
      Serial.println("DD_HEATER: Heater ON");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_3);
      Serial.println("DD_HEATER: Heater ON");
#else
      Serial.println("CTRL_TEMP_HEAT: Hea_ON/SP_Up Command <no action>");
#endif
      break;

    case 's': // Down
#if defined USE_CTRL_TEMP_HEAT
      if (ctrl_temp_heat_is_enabled())
      {
        ctrl_temp_heat_setpoint_dn(0.1);
        Serial.print("CTRL_TEMP_HEAT: Decreasing Setpoint:");
        int sp = ctrl_temp_heat_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_heater_off();
        Serial.println(" DD_HEATER: Heater OFF");
      }
#elif defined USE_DD_HEATER
      dd_heater_off();
      Serial.println("DD_HEATER: Heater OFF");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_3);
      Serial.println(" ED_RELAY: Heater OFF");
#else
      Serial.println("CTRL_TEMP_HEAT: Hea_OFF/SP_Dn Command <no action>");
#endif
      break;

    case 'c': //  manual or automat control
#if defined USE_CTRL_AIR_HUM
      if (ctrl_air_hum_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_AIR_HUM:  Change mode to MANUAL");
        ctrl_air_hum_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_AIR_HUM:  Change mode to AUTO");
        ctrl_air_hum_set_mode_auto();
      }
#elif defined USE_DD_VALVE
      dd_valve_off();
      Serial.println("DD_VALVE: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_3);
#else
      Serial.println("CTRL_AIR_HUM: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;
    case 'e': // UP
#if defined USE_CTRL_AIR_HUM
      if (ctrl_air_hum_is_enabled())
      {
        ctrl_air_hum_setpoint_up(0.1);
        Serial.print("CTRL_AIR_HUM: Increase Setpoint:");
        int sp = ctrl_air_hum_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_valve_on(CTRL_AIR_HUM_OP_D_TIME);
        Serial.println("CTRL_AIR_HUM: Manual Valve opening");
      }
#elif defined USE_DD_VALVE
      dd_valve_on(4 * TIME_SEC / DD_VALVE_REC);
      Serial.println("DD_VALVE: Valve opening");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_4);
      Serial.println("DD_VALVE: Valve opening");
#else
      Serial.println("CTRL_AIR_HUM: OPEN/SP_Up Command <no action>");
#endif
      break;

    case 'd': // Down
#if defined USE_CTRL_AIR_HUM
      if (ctrl_air_hum_is_enabled())
      {
        ctrl_air_hum_setpoint_dn(0.1);
        Serial.print("CTRL_AIR_HUM: Decreasing Setpoint:");
        int sp = ctrl_air_hum_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_valve_off();
        Serial.println(" DD_VALVE: Valve Closing");
      }
#elif defined USE_DD_VALVE
      dd_valve_off();
      Serial.println("DD_VALVE: Valve closing");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_4);
      Serial.println(" ED_RELAY: Valve Closing");
#else
      Serial.println("CTRL_AIR_HUM: CLOSE/SP_Dn Command <no action>");
#endif
      break;

      break;

    case 'v': //  manual or automat control
#if defined USE_CTRL_SOIL_MOIST
      if (ctrl_soil_moist_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_SOIL_MOIST:  Change mode to MANUAL");
        ctrl_soil_moist_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_SOIL_MOIST:  Change mode to AUTO");
        ctrl_soil_moist_set_mode_auto();
      }
#elif defined USE_DD_VALVE
      dd_valve_off();
      Serial.println("DD_VALVE: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_5);
#else
      Serial.println("CTRL_SOIL_MOIST: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;
    case 'r': // UP
#if defined USE_CTRL_SOIL_MOIST
      if (ctrl_soil_moist_is_enabled())
      {
        ctrl_soil_moist_setpoint_up(0.1);
        Serial.print("CTRL_SOIL_MOIST: Increase Threshold:");
        float threshold = ctrl_soil_moist_get_setpoint();
        Serial.println(threshold);
      }
      else
      {
        dd_valve_on(CTRL_SOIL_MOIST_OP_D_TIME);
        Serial.println("CTRL_SOIL_MOIST: Valve opening");
      }
#elif defined USE_DD_VALVE
      dd_valve_on(DD_VALVE_OP_D_TIME);
      Serial.println("DD_VALVE: Valve opening");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_5);
      Serial.println("DD_VALVE: Valve opening");
#else
      Serial.println("CTRL_SOIL_MOIST: OPEN/Threshold_Up Command <no action>");
#endif
      break;

    case 'f': // Down
#if defined USE_CTRL_SOIL_MOIST
      if (ctrl_soil_moist_is_enabled())
      {
        ctrl_soil_moist_setpoint_up(0.1);
        Serial.print("CTRL_SOIL_MOIST: Decreasing Threshold:");
        float threshold = ctrl_soil_moist_get_setpoint();
        Serial.println(threshold);
      }
      else
      {
        dd_valve_off();
        Serial.println(" DD_VALVE: Valve Closing");
      }
#elif defined USE_DD_VALVE
      dd_valve_off();
      Serial.println("DD_VALVE: Valve closing");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_5);
      Serial.println(" ED_RELAY: Valve Closing");
#else
      Serial.println("CTRL_SOIL_MOIST: CLOSE/Threshold_Down Command <no action>");
#endif
      break;

    case 'b': //  manual or automat control
#if defined USE_CTRL_AIR_PRESS
      if (ctrl_air_press_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_AIR_PRESS:  Change mode to MANUAL");
        ctrl_air_press_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_AIR_PRESS:  Change mode to AUTO");
        ctrl_air_press_set_mode_auto();
      }
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_off();
      Serial.println("DD_AIR_PUMP: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_6);
#else
      Serial.println("CTRL_AIR_PRESS: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;
    case 't': // UP
#if defined USE_CTRL_AIR_PRESS
      if (ctrl_air_press_is_enabled())
      {
        ctrl_air_press_setpoint_up(0.1);
        Serial.print("CTRL_AIR_PRESS: Increase Setpoint:");
        int sp = ctrl_air_press_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_air_pump_on(DD_AIR_PUMP_OP_D_TIME);
        Serial.println("CTRL_AIR_PRESS: Manual Air_press ON");
      }
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_on(DD_AIR_PUMP_OP_D_TIME);
      Serial.println("DD_AIR_PUMP: Air_pump ON");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_6);
      Serial.println("DD_RELAY: Air_pump ON");
#else
      Serial.println("CTRL_AIR_PRESS: Light_ON/SP_Up Command <no action>");
#endif
      break;

    case 'g': // Down
#if defined USE_CTRL_AIR_PRESS
      if (ctrl_air_press_is_enabled())
      {
        ctrl_air_press_setpoint_dn(0.1);
        Serial.print("CTRL_AIR_PRESS: Decreasing Setpoint:");
        int sp = ctrl_air_press_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_air_pump_off();
        Serial.println(" DD_AIR_PUMP: Air_press OFF");
      }
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_off();
      Serial.println("DD_AIR_PUMP: Air_press OFF");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_6);
      Serial.println(" ED_RELAY: Air_press OFF");
#else
      Serial.println("CTRL_AIR_PRESS: Light_OFF/SP_Dn Command <no action>");
#endif
      break;

    case 'n': //  manual or automat control
#if defined USE_CTRL_LIGHTS
      if (ctrl_lights_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_LIGHTS:  Change mode to MANUAL");
        ctrl_lights_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_LIGHTS:  Change mode to AUTO");
        ctrl_lights_set_mode_auto();
      }
#elif defined USE_DD_LIGHTS
      dd_lights_stop();
      Serial.println("DD_LIGHTS: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_8);
#else
      Serial.println("CTRL_LIGHTS: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;
    case 'y': // UP
#if defined USE_CTRL_LIGHTS
      if (ctrl_lights_is_enabled())
      {
        ctrl_lights_setpoint_up(0.1);
        Serial.print("CTRL_LIGHTS: Increase Setpoint:");
        int sp = ctrl_lights_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_lights_on(-1);
        Serial.println("CTRL_LIGHTS: Manual Lights ON");
      }
#elif defined USE_DD_LIGHTS
      dd_lights_on(CTRL_LIGHTS_OP_D_TIME);
      Serial.println("DD_LIGHTS: Lights ON");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_8);
      Serial.println("DD_LIGHTS: Lights ON");
#else
      Serial.println("CTRL_LIGHTS: Light_ON/SP_Up Command <no action>");
#endif
      break;

    case 'h': // Down
#if defined USE_CTRL_LIGHTS
      if (ctrl_lights_is_enabled())
      {
        ctrl_lights_setpoint_dn(0.1);
        Serial.print("CTRL_LIGHTS: Decreasing Setpoint:");
        int sp = ctrl_lights_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_lights_off();
        Serial.println(" DD_LIGHTS: Lights OFF");
      }
#elif defined USE_DD_LIGHTS
      dd_lights_off(4 * TIME_SEC / DD_LIGHTS_REC);
      Serial.println("DD_LIGHTS: Lights OFF");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_8);
      Serial.println(" ED_RELAY: Lights OFF");
#else
      Serial.println("CTRL_LIGHTS: Light_OFF/SP_Dn Command <no action>");
#endif
      break;

    default:
      break;
    }
  }
}

void srv_ui_serial_out_loop()
{
  Serial.println(F("=============== GH System Report =============== "));

//-----------------------------------------------
//  Report Control components state
#ifdef USE_CTRL_TEMP_VENT
  ctrl_temp_vent_report();
#endif
#ifdef USE_CTRL_TEMP_HEAT
  ctrl_temp_heat_report();
#endif
#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_report();
#endif
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_report();
#endif
#ifdef USE_CTRL_AIR_PRESS
  ctrl_air_press_report();
#endif
#ifdef USE_CTRL_LIGHTS
  ctrl_lights_report();
#endif

//-----------------------------------------------
//  Report Sensor components state
#ifdef USE_SRV_SNS_AIR_TEMP
  srv_sns_air_temp_report();
#endif
#ifdef USE_SRV_SNS_AIR_HUM
  srv_sns_air_hum_report();
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
  srv_sns_soil_moist_report();
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
  srv_sns_air_press_report();
#endif
#ifdef USE_SRV_SNS_LIGHT
  srv_sns_light_report();
#endif

//-----------------------------------------------
//  Report Actuator components state
#ifdef USE_DD_WINDOW
  dd_window_report();
#endif
#ifdef USE_DD_HEATER
  dd_heater_report();
#endif
#ifdef USE_DD_VALVE
  dd_valve_report();
#endif
#ifdef USE_DD_AIR_PUMP
  dd_air_pump_report();
#endif
#ifdef USE_DD_LIGHTS
  dd_lights_report();
#endif

//-----------------------------------------------
//  Report ECU components state
#ifdef USE_ED_DHT
  ed_dht_report();
#endif
#ifdef USE_ED_SNS_MOIST
  ed_sns_soil_moist_report();
#endif
#ifdef USE_ED_BMP
  ed_bmp_report();
#endif
#ifdef USE_ED_BH1750
  ed_bh1750_report();
#endif

#ifdef USE_ED_RELAY
  ed_relay_report();
#endif

  Serial.println();
}

// void ctrl_temp_vent_report()
// {
// #ifdef USE_CTRL_TEMP_VENT

//   if (ctrl_temp_vent_is_enabled())
//   {
//     Serial.print(F("CTRL_VENT: Mode AUTO-"));
//   }
//   else
//   {
//     Serial.print(F("CTRL_VENT: Mode MANUAL-"));
//   }
//   Serial.println(CTRL_TEMP_VENT_REC);

//   float temp_setpoint = ctrl_temp_vent_get_setpoint();
//   Serial.print(F("CTRL_VENT: SP: "));
//   Serial.print(temp_setpoint);
//   Serial.print(F("°C "));

//   Serial.print(F("HIST[OP: "));
//   Serial.print(temp_setpoint + CTRL_TEMP_VENT_HISTERESIS);
//   Serial.print(F("°C  "));

//   Serial.print(F("CL: "));
//   Serial.print(temp_setpoint - CTRL_TEMP_VENT_HISTERESIS);
//   Serial.print(F("°C] "));

//   float temp_current = ctrl_temp_vent_get_current_temp();
//   Serial.print(F("CTRL_VENT: Cur: "));
//   Serial.print(temp_current);
//   Serial.println(F("°C"));

// #endif
// }

// void ctrl_temp_heat_report()
// {
// #ifdef USE_CTRL_TEMP_HEAT

//   if (ctrl_temp_heat_is_enabled())
//   {
//     Serial.print(F("CTRL_VENT: Mode AUTO-"));
//   }
//   else
//   {
//     Serial.print(F("CTRL_VENT: Mode MANUAL-"));
//   }
//   Serial.print(CTRL_TEMP_HEAT_REC);

//   float temp_setpoint = ctrl_temp_heat_get_setpoint();
//   Serial.print(F(" : SP: "));
//   Serial.print(temp_setpoint);
//   Serial.print(F("°C "));

//   Serial.print(F("HIST[OP: "));
//   Serial.print(temp_setpoint + CTRL_TEMP_HEAT_HISTERESIS);
//   Serial.print(F("°C  "));

//   Serial.print(F("CL: "));
//   Serial.print(temp_setpoint - CTRL_TEMP_HEAT_HISTERESIS);
//   Serial.print(F("°C] "));

//   float temp_current = ctrl_temp_heat_get_current_temp();
//   Serial.print(F("  Cur: "));
//   Serial.print(temp_current);
//   Serial.println(F("°C"));

// #endif
// }



// void ctrl_temp_heat_report()
// {
// #ifdef USE_CTRL_TEMP_HEAT
//   if (ctrl_temp_heat_is_enabled())
//   {
//     Serial.println(F("CTRL_HEAT: Mode AUTO "));
//   }
//   else
//   {
//     Serial.println(F("CTRL_HEAT: Mode MANUAL"));
//   }

//   float temp_setpoint = ctrl_temp_heat_get_setpoint();
//   Serial.print(F("CTRL_HEAT: SP: "));
//   Serial.print(temp_setpoint);
//   Serial.print(F("°C "));

//   Serial.print(F("HIST[OP: "));
//   Serial.print(temp_setpoint + CTRL_TEMP_HEAT_HISTERESIS);
//   Serial.print(F("°C  "));

//   Serial.print(F("CL: "));
//   Serial.print(temp_setpoint - CTRL_TEMP_HEAT_HISTERESIS);
//   Serial.print(F("°C] "));

//   float temp_current = ctrl_temp_heat_get_current_temp();
//   Serial.print(F("CTRL_HEAT: Cur: "));
//   Serial.print(temp_current);
//   Serial.println(F("°C"));
// #endif
// }

