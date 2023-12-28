#include "ctrl_temp_vent.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "dd_window/dd_window.h"

#include "Arduino.h"

float ctrl_temp_vent_setpoint = 19.0;
int8_t ctrl_temp_vent_mode = CTRL_TEMP_VENT_DISABLE;

float ctrl_temp_vent_set_setpoint(float setpoint)
{
  ctrl_temp_vent_setpoint = setpoint;
  return ctrl_temp_vent_setpoint;
}

float ctrl_temp_vent_get_setpoint()
{
  return ctrl_temp_vent_setpoint;
}

float ctrl_temp_vent_setpoint_up(float d_val)
{
  float setpoint = ctrl_temp_vent_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_temp_vent_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_temp_vent_setpoint_dn(float d_val)
{
  float setpoint = ctrl_temp_vent_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_temp_vent_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_temp_vent_set_mode(int8_t mode)
{
  if (mode == CTRL_TEMP_VENT_DISABLE)
  {
    ctrl_temp_vent_mode = CTRL_TEMP_VENT_DISABLE;
  }
  else if (mode == CTRL_TEMP_VENT_ENABLE)
  {
    ctrl_temp_vent_mode = CTRL_TEMP_VENT_ENABLE;
  }
  else
  {
    return -1;
  }
  return ctrl_temp_vent_mode;
}

int8_t ctrl_temp_vent_get_mode()
{
  return ctrl_temp_vent_mode;
}
int8_t ctrl_temp_vent_set_mode_manual()
{
  return ctrl_temp_vent_set_mode(CTRL_TEMP_VENT_DISABLE);
}
int8_t ctrl_temp_vent_set_mode_auto()
{
  return ctrl_temp_vent_set_mode(CTRL_TEMP_VENT_ENABLE);
}
int8_t ctrl_temp_vent_is_enabled()
{
  return ctrl_temp_vent_mode == CTRL_TEMP_VENT_ENABLE;
}
float ctrl_temp_vent_get_current_temp()
{
  return srv_sns_air_get_temperature();
}

void ctrl_temp_vent_setup()
{
  ctrl_temp_vent_setpoint = 19.0;
  ctrl_temp_vent_mode = CTRL_TEMP_VENT_DISABLE;
}

void ctrl_temp_vent_loop()
{
  if (ctrl_temp_vent_mode == CTRL_TEMP_VENT_ENABLE)
  {
    if (srv_sns_air_get_temperature_error() == 0)
    {
      float temp_current = srv_sns_air_get_temperature();
      float temp_open = ctrl_temp_vent_setpoint + TEMP_VENT_HISTERESIS;
      float temp_close = ctrl_temp_vent_setpoint - TEMP_VENT_HISTERESIS;

      // OPEN/CLOSE Control cu Histereza
      if (temp_current > temp_open)
      {
        dd_window_open(DD_WIN_OP_D_TIME);
      }
      else if (temp_current < temp_close)
      {
        dd_window_close(DD_WIN_OP_D_TIME);
      }
      else
      {
        dd_window_stop();
      }
    }
    else
    {
      dd_window_stop();
    }
  }
}
