#include "Arduino.h"

#include "srv_ui_serial.h"

#include "ecu_config.h"
#include "ecu_modules.h"

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
        dd_window_open(2 * TIME_SEC);
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
        dd_window_close(2 * TIME_SEC);
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
        dd_heater_on(DD_HEAT_OP_D_TIME);
        Serial.println("CTRL_TEMP_HEAT: Manual Heater ON");
      }
#elif defined USE_DD_HEATER
      dd_heater_on(DD_HEAT_OP_D_TIME);
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
      dd_valve_stop();
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
        dd_valve_on(DD_HUM_OP_D_TIME);
        Serial.println("CTRL_AIR_HUM: Manual Valve opening");
      }
#elif defined USE_DD_VALVE
      dd_valve_on(DD_HUM_OP_D_TIME);
      Serial.println("DD_VALVE: Valve opening");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_3);
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
      dd_valve_off(4 * TIME_SEC / DD_VALVE_REC);
      Serial.println("DD_VALVE: Valve closing");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_3);
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
      dd_valve_stop();
      Serial.println("DD_VALVE: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_3);
#else
      Serial.println("CTRL_SOIL_MOIST: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;
    case 'r': // UP
#if defined USE_CTRL_SOIL_MOIST
      if (ctrl_soil_moist_is_enabled())
      {
        ctrl_soil_moist_set_threshold_up(0.1);
        Serial.print("CTRL_SOIL_MOIST: Increase Threshold:");
        float threshold = ctrl_soil_moist_get_threshold();
        Serial.println(threshold);
      }
      else
      {
        valve_open();
        Serial.println("CTRL_SOIL_MOIST: Valve opening");
      }
#elif defined USE_DD_VALVE
      valve_open();
      Serial.println("DD_VALVE: Valve opening");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_3);
      Serial.println("DD_VALVE: Valve opening");
#else
      Serial.println("CTRL_SOIL_MOIST: OPEN/Threshold_Up Command <no action>");
#endif
      break;

    case 'f': // Down
#if defined USE_CTRL_SOIL_MOIST
      if (ctrl_soil_moist_is_enabled())
      {
        ctrl_soil_moist_set_threshold_down(0.1);
        Serial.print("CTRL_SOIL_MOIST: Decreasing Threshold:");
        float threshold = ctrl_soil_moist_get_threshold();
        Serial.println(threshold);
      }
      else
      {
        valve_close();
        Serial.println(" DD_VALVE: Valve Closing");
      }
#elif defined USE_DD_VALVE
      valve_close();
      Serial.println("DD_VALVE: Valve closing");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_3);
      Serial.println(" ED_RELAY: Valve Closing");
#else
      Serial.println("CTRL_SOIL_MOIST: CLOSE/Threshold_Down Command <no action>");
#endif
      break;

    case 'b': //  manual or automat control
#if defined USE_CTRL_PRESS_ISOL
      if (ctrl_press_isol_is_enabled())
      { // go to manual control
        Serial.println(" CTRL_PRESS_ISOL:  Change mode to MANUAL");
        ctrl_press_isol_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" CTRL_PRESS_ISOL:  Change mode to AUTO");
        ctrl_press_isol_set_mode_auto();
      }
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_off();
      Serial.println("DD_AIR_PUMP: STOP Command");
#elif defined USE_ED_RELAY
      Serial.println("DD_RELAY: STOP Command");
      ed_relay_off(ED_RELAY_ID_8);
#else
      Serial.println("CTRL_PRESS_ISOL: AUTO/MANUAL/STOP Command <no action>");
#endif
      break;
    case 't': // UP
#if defined USE_CTRL_PRESS_ISOL
      if (ctrl_press_isol_is_enabled())
      {
        ctrl_press_isol_setpoint_up(0.1);
        Serial.print("CTRL_PRESS_ISOL: Increase Setpoint:");
        int sp = ctrl_press_isol_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_air_pump_on(DD_AIR_PUMP_OP_D_TIME);
        Serial.println("CTRL_PRESS_ISOL: Manual Press_isol ON");
      }
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_on(DD_AIR_PUMP_OP_D_TIME);
      Serial.println("DD_AIR_PUMP: Air_pump ON");
#elif defined USE_ED_RELAY
      ed_relay_on(ED_RELAY_ID_8);
      Serial.println("DD_RELAY: Air_pump ON");
#else
      Serial.println("CTRL_PRESS_ISOL: Light_ON/SP_Up Command <no action>");
#endif
      break;

    case 'g': // Down
#if defined USE_CTRL_PRESS_ISOL
      if (ctrl_press_isol_is_enabled())
      {
        ctrl_press_isol_setpoint_dn(0.1);
        Serial.print("CTRL_PRESS_ISOL: Decreasing Setpoint:");
        int sp = ctrl_press_isol_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_air_pump_off();
        Serial.println(" DD_AIR_PUMP: Press_isol OFF");
      }
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_off();
      Serial.println("DD_AIR_PUMP: Press_isol OFF");
#elif defined USE_ED_RELAY
      ed_relay_off(ED_RELAY_ID_8);
      Serial.println(" ED_RELAY: Press_isol OFF");
#else
      Serial.println("CTRL_PRESS_ISOL: Light_OFF/SP_Dn Command <no action>");
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
        dd_lights_on(DD_LIGHT_OP_D_TIME);
        Serial.println("CTRL_LIGHTS: Manual Lights ON");
      }
#elif defined USE_DD_LIGHTS
      dd_lights_on(DD_LIGHT_OP_D_TIME);
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
  Serial.println(F("===== GH System Report ===== "));

  ctrl_temp_vent_report();
  ctrl_temp_heat_report();
  ctrl_lights_report();

  srv_sns_air_temp_report();
  ed_dht_report();

  dd_window_report();
  ed_relay_report();

  Serial.println();
}

void ctrl_temp_vent_report()
{
#ifdef USE_CTRL_TEMP_VENT

  if (ctrl_temp_vent_is_enabled())
  {
    Serial.print(F("CTRL_VENT: Mode AUTO-"));
  }
  else
  {
    Serial.print(F("CTRL_VENT: Mode MANUAL-"));
  }
  Serial.println(CTRL_TEMP_VENT_REC);

  float temp_setpoint = ctrl_temp_vent_get_setpoint();
  Serial.print(F("CTRL_VENT: SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F("°C "));

  Serial.print(F("HIST[OP: "));
  Serial.print(temp_setpoint + TEMP_VENT_HISTERESIS);
  Serial.print(F("°C  "));

  Serial.print(F("CL: "));
  Serial.print(temp_setpoint - TEMP_VENT_HISTERESIS);
  Serial.print(F("°C] "));

  float temp_current = ctrl_temp_vent_get_current_temp();
  Serial.print(F("CTRL_VENT: Cur: "));
  Serial.print(temp_current);
  Serial.println(F("°C"));

#endif
}

void ctrl_temp_heat_report()
{
#ifdef USE_CTRL_TEMP_HEAT

  if (ctrl_temp_heat_is_enabled())
  {
    Serial.print(F("CTRL_VENT: Mode AUTO-"));
  }
  else
  {
    Serial.print(F("CTRL_VENT: Mode MANUAL-"));
  }
  Serial.print(CTRL_TEMP_HEAT_REC);

  float temp_setpoint = ctrl_temp_heat_get_setpoint();
  Serial.print(F(" : SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F("°C "));

  Serial.print(F("HIST[OP: "));
  Serial.print(temp_setpoint + TEMP_HEAT_HISTERESIS);
  Serial.print(F("°C  "));

  Serial.print(F("CL: "));
  Serial.print(temp_setpoint - TEMP_HEAT_HISTERESIS);
  Serial.print(F("°C] "));

  float temp_current = ctrl_temp_heat_get_current_temp();
  Serial.print(F("  Cur: "));
  Serial.print(temp_current);
  Serial.println(F("°C"));

#endif
}

void ctrl_lights_report()
{
#ifdef USE_CTRL_LIGHTS
  Serial.print(F("CTRL_LIGHTS "));
  Serial.print(CTRL_LIGHTS_REC);

  if (ctrl_lights_is_enabled())
  {
    Serial.print(F(" : AUTO "));
  }
  else
  {
    Serial.print(F(": MANUAL "));
  }

  float light_current = ctrl_lights_get_current_light();
  Serial.print(F(": Cur: "));
  Serial.print(light_current);
  Serial.print(F(" lx"));

  float light_setpoint = ctrl_lights_get_setpoint();
  Serial.print(F(": SP: "));
  Serial.print(light_setpoint);
  Serial.print(F(" lx "));

  Serial.print(F("HIST[OP: "));
  Serial.print(light_setpoint + LIGHTS_HISTERESIS);
  Serial.print(F(" lx  "));

  Serial.print(F("CL: "));
  Serial.print(light_setpoint - LIGHTS_HISTERESIS);
  Serial.print(F(" lx] "));

  Serial.println();

#endif
}

void ed_relay_report()
{
#ifdef USE_ED_RELAY

  // Relay Report
  Serial.print("ED_RELAY: Relay ");
  for (size_t relay_it = 0; relay_it < ED_RELAY_NR_OF; relay_it++)
  {
    /* code */
    int relay_state = ed_relay_getState(relay_it);
    int relay_pin = ed_relay_get_pin(relay_it);
    Serial.print(" [");
    Serial.print(relay_it);
    Serial.print(":");
    Serial.print(relay_pin);
    Serial.print("]-");
    if (relay_state == ED_RELAY_ON)
    {
      Serial.print("ON");
    }
    else
    {
      Serial.print("OFF");
    }
  }
  Serial.println();
#endif
}

void dd_window_report()
{
#ifdef USE_DD_WINDOW

  // Window Report

  int window_state = dd_window_get_state();
  Serial.print("DD_WINDOW: Windoe ");
  Serial.print(window_state);
  Serial.print(" - ");

  if (window_state == DD_WINDOW_STOP)
  {
    Serial.println(" STOP");
  }
  else if (window_state == DD_WINDOW_CLOSE)
  {
    Serial.println(" CLOSE");
  }
  else if (window_state == DD_WINDOW_OPEN)
  {
    Serial.println(" OPRN");
  }
  else
  {
    Serial.println(" UNDEFINED");
  }
#endif
}

void ed_dht_report()
{
#ifdef USE_ED_DHT
  if (ed_dht_get_temperature_error() == 0)
  {
    float temp = ed_dht_get_temperature();
    Serial.print(F("ED_DHT Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
  }
  else
  {
    Serial.println(F("ED_DHT Error reading temperature!"));
  }
#endif
}

//----------------------------------------------------------
// Ambient Temperature sensor service report
//----------------------------------------------------------
void srv_sns_air_temp_report()
{
#ifdef USE_SRV_SNS_AIR_TEMP
  float temp = srv_sns_air_get_temperature();
  Serial.print(F("SRV_SNS_AIR_TEMP: Temperature: "));
  Serial.print(temp);
  Serial.println(F("°C"));
#endif
}

void srv_ui_serial_ctrl_temp_heat_report()
{
#ifdef USE_CTRL_TEMP_HEAT
  if (ctrl_temp_heat_is_enabled())
  {
    Serial.println(F("CTRL_HEAT: Mode AUTO "));
  }
  else
  {
    Serial.println(F("CTRL_HEAT: Mode MANUAL"));
  }

  float temp_setpoint = ctrl_temp_heat_get_setpoint();
  Serial.print(F("CTRL_HEAT: SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F("°C "));

  Serial.print(F("HIST[OP: "));
  Serial.print(temp_setpoint + TEMP_HEAT_HISTERESIS);
  Serial.print(F("°C  "));

  Serial.print(F("CL: "));
  Serial.print(temp_setpoint - TEMP_HEAT_HISTERESIS);
  Serial.print(F("°C] "));

  float temp_current = ctrl_temp_heat_get_current_temp();
  Serial.print(F("CTRL_HEAT: Cur: "));
  Serial.print(temp_current);
  Serial.println(F("°C"));
#endif
}

void srv_ui_serial_ctrl_air_hum_report()
{

#ifdef USE_CTRL_AIR_HUM
  if (ctrl_air_hum_is_enabled())
  {
    Serial.println(F("CTRL_AIR_HUM: Mode AUTO "));
  }
  else
  {
    Serial.println(F("CTRL_AIR_HUM: Mode MANUAL"));
  }

  float hum_setpoint = ctrl_air_hum_get_setpoint();
  Serial.print(F("CTRL_AIR_HUM: SP: "));
  Serial.print(hum_setpoint);
  Serial.print(F("% "));

  Serial.print(F("HIST[OP: "));
  Serial.print(hum_setpoint + AIR_HUM_HISTERESIS);
  Serial.print(F("%  "));

  Serial.print(F("CL: "));
  Serial.print(hum_setpoint - AIR_HUM_HISTERESIS);
  Serial.print(F("%] "));

  float hum_current = ctrl_air_hum_get_current_hum();
  Serial.print(F("CTRL_AIR_HUM: Cur: "));
  Serial.print(hum_current);
  Serial.println(F("%"));
#endif
}

void srv_ui_serial_dd_heater_report()
{ // Heater Report
#ifdef USE_DD_HEATER
  int heater_state = dd_heater_get_state();
  Serial.print(F("DD_HEATER: Heater "));
  Serial.print(heater_state);
  Serial.print(F(" - "));

  if (heater_state == DD_HEATER_OFF)
  {
    Serial.println(F(" STOP"));
  }
  else if (heater_state == DD_HEATER_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
#endif
}
