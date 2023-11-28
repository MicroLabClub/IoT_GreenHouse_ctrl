#include "srv_ui_serial.h"
#include "ed_dht/ed_dht.h"
#include "ed_relay/ed_relay.h"
#include "dd_window/dd_window.h"
// #include "ed_servo/ed_servo.h"
#include "ed_encoder/ed_encoder.h"
#include "ctrl_temp_heat/ctrl_temp_heat.h"
#include "ctrl_temp_vent/ctrl_temp_vent.h"
#include "ctrl_air_humidity/ctrl_air_humidity.h"

void srv_ui_serial_setup()
{
  Serial.begin(9600);
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

    case 'z':// control manual sau automat
      if (ctrl_temp_vent_is_enabled())
      { // go to manual control
        Serial.println(" SRV_TEMP_WENT:  Change mode to MANUAL");
        ctrl_temp_vent_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" SRV_TEMP_WENT:  Change mode to AUTO");
        ctrl_temp_vent_set_mode_auto();
      }
      dd_window_stop();
      break;

    case 'q': // UP 
      if (ctrl_temp_vent_is_enabled())
      {
        ctrl_temp_vent_setpoint_up(0.1);
      }
      else
      {
        dd_window_open(100);
        Serial.println(" DD_WINDOW: Window opening");
      }

      break;

    case 'a': // Down
      if (ctrl_temp_vent_is_enabled())
      {
        ctrl_temp_vent_setpoint_dn(0.1);
      }
      else
      {
        dd_window_close(100);
        Serial.println(" DD_WINDOW: Window opening");
      }
      break;

    case 'x':// control manual sau automat
      if (ctrl_air_hum_is_enabled())
      { // go to manual control
        Serial.println(" SRV_TEMP_WENT:  Change mode to MANUAL");
        ctrl_air_hum_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(" SRV_TEMP_WENT:  Change mode to AUTO");
        ctrl_air_hum_set_mode_auto();
      }
      dd_window_stop();
      break;

    case 'w': // UP 
      if (ctrl_air_hum_is_enabled())
      {
        ctrl_air_hum_setpoint_up(0.1);
      }
      else
      {
        dd_window_open(100);
        Serial.println(" DD_WINDOW: Window opening");
      }

      break;

    case 's': // Down
      if (ctrl_air_hum_is_enabled())
      {
        ctrl_air_hum_setpoint_dn(0.1);
      }
      else
      {
        dd_window_close(100);
        Serial.println(" DD_WINDOW: Window opening");
      }
      break;

    case 'u':
      ed_relay_on(ED_RELAY_ID_2);
      Serial.println(" DD_REL:  Realay 2 Switched ON");
      break;

    case 'j':
      ed_relay_off(ED_RELAY_ID_2);
      Serial.println(" DD_REL:  Realay 2 Switched OFF");
      break;

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

  int enc_counter = ed_encoder_get_counter();
  Serial.print("Encoder Position: ");
  Serial.println(enc_counter);

  float temp_setpoint = (float)enc_counter * TEMP_HEAT_RESOLUTION;
  Serial.print(F("SetPoint T emperature: "));
  Serial.print(temp_setpoint);
  Serial.println(F("°C"));

  if (ed_dht_GetTemperatureError() == 0)
  {
    float temp = ed_dht_GetTemperature();
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
  }

  int relay_state = ed_relay_getState(ED_RELAY_1_PIN);

  if (relay_state)
  {
    Serial.println("Relay 1 ON");
  }
  else
  {
    Serial.println("Relay 1 OFF");
  }

  relay_state = ed_relay_getState(ED_RELAY_2_PIN);

  if (relay_state)
  {
    Serial.println("Relay 2 ON");
  }
  else
  {
    Serial.println("Relay 2 OFF");
  }
  // servo report
  // int servo_current = ed_servo_get_current();
  // Serial.print("Servo: Current - ");
  // Serial.print(servo_current);

  // int servo_target = ed_servo_get_target();
  // Serial.print("  | Target - ");
  // Serial.println(servo_target);
}
