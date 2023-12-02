#include "srv_ui_serial.h"
#include "ecu_config.h"
#include "Arduino.h"

// Control Components
// #include "ctrl_air_humidity/ctrl_air_humidity.h"
// #include "ctrl_lights/ctrl_lights.h"
// #include "ctrl_press_isol/ctrl_press_isol.h"
// #include "ctrl_soil_moisture/ctrl_soil_moisture.h"
// #include "ctrl_temp_heat/ctrl_temp_heat.h"

#ifdef USE_CTRL_TEMP_VENT
#include "ctrl_temp_vent/ctrl_temp_vent.h"
#endif

//=============================================================================
// Platform Services
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#endif

//=============================================================================
// Devise abstraction components
// #include "dd_heater/dd_heater.h"
// #include "dd_lights/dd_lights.h"
// #include "dd_valve/dd_valve.h"

#ifdef USE_DD_WINDOW
#include "dd_window/dd_window.h"
#endif

// ECU Abstraction components

#ifdef USE_ED_DHT
// #include "ed_bmp/ed_bmp.h"
#endif

#ifdef USE_ED_DHT
#include "ed_dht/ed_dht.h"
#endif

// #include "ed_encoder/ed_encoder.h"

#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay.h"
#endif

// #include "ed_servo/ed_servo.h"
// #include "ed_sns_moist/ed_sns_moist.h"

void srv_ui_serial_setup()
{
  Serial.begin(9600);
  Serial.println("IoT System started");
}

void srv_ui_serial_in_loop()
{
  // Serial.println("SCAN ");
  if (Serial.available())
  {
    char cmd = Serial.read();

    Serial.print("IOT: Recived command: ");
    Serial.println(cmd);

    switch (cmd)
    {

    case 'z': // control manual sau automat
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
#elif defined USE_DD_WINDOW
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

      // case 'x': // control manual sau automat
      //   if (ctrl_air_hum_is_enabled())
      //   { // go to manual control
      //     Serial.println(" CTRL_TEMP_VENT:  Change mode to MANUAL");
      //     ctrl_air_hum_set_mode_manual();
      //   }
      //   else
      //   { // go to automat control
      //     Serial.println(" CTRL_TEMP_VENT:  Change mode to AUTO");
      //     ctrl_air_hum_set_mode_auto();
      //   }
      //   dd_valve_stop();
      //   break;

      // case 'w': // UP
      //   if (ctrl_air_hum_is_enabled())
      //   {
      //     ctrl_air_hum_setpoint_up(0.1);
      //   }
      //   else
      //   {
      //     dd_valve_open(100);
      //     Serial.println(" DD_VALVE: Window opening");
      //   }

      //   break;

      // case 's': // Down
      //   if (ctrl_air_hum_is_enabled())
      //   {
      //     ctrl_air_hum_setpoint_dn(0.1);
      //   }
      //   else
      //   {
      //     dd_valve_close(100);
      //     Serial.println(" DD_VALVE: Window opening");
      //   }
      //   break;

      // case 'u':
      //   ed_relay_on(ED_RELAY_ID_2);
      //   Serial.println(" DD_REL:  Realay 2 Switched ON");
      //   break;

      // case 'j':
      //   ed_relay_off(ED_RELAY_ID_2);
      //   Serial.println(" DD_REL:  Realay 2 Switched OFF");
      //   break;

      // case 'w':
      //   ed_servo_open();
      //   Serial.println(" ED_SERVO:  Servo Open");
      //   break;

      // case 's':
      //   ed_servo_close();
      //   Serial.println(" ED_SERVO:  Close");
      //   break;

    default:
      break;
    }
  }
}

void srv_ui_serial_out_loop()
{
  Serial.println(F("===== GH System Report ===== "));

  // int enc_counter = ed_encoder_get_counter();
  // Serial.print("Encoder Position: ");
  // Serial.println(enc_counter);

  srv_ui_serial_ctrl_temp_vent_report();

  srv_ui_serial_dht_report();

  srv_ui_serial_relay_report();

  srv_ui_serial_win_report();

  // servo report
  // int servo_current = ed_servo_get_current();
  // Serial.print("Servo: Current - ");
  // Serial.print(servo_current);

  // int servo_target = ed_servo_get_target();
  // Serial.print("  | Target - ");
  // Serial.println(servo_target);
  Serial.println();
}

void srv_ui_serial_ctrl_temp_vent_report()
{
#ifdef USE_CTRL_TEMP_VENT

  if (ctrl_temp_vent_is_enabled())
  {
    Serial.println(F("CTRL_VENT: Mode AUTO "));
  }
  else
  {
    Serial.println(F("CTRL_VENT: Mode MANUAL"));
  }

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

void srv_ui_serial_relay_report()
{
#ifdef USE_ED_RELAY

  // Relay Report
  Serial.print("ED_RELAY: Relay ");
  for (size_t relay_it = 0; relay_it < ED_RELAY_NR_OF; relay_it++)
  {
    /* code */
    int relay_state = ed_relay_getState(relay_it);
    Serial.print(" [");
    Serial.print(relay_it);
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

void srv_ui_serial_win_report()
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

void srv_ui_serial_dht_report()
{
#ifdef USE_ED_DHT
  if (ed_dht_GetTemperatureError() == 0)
  {
    float temp = ed_dht_GetTemperature();
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