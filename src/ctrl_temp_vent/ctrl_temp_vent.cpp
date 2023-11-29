#include "ctrl_temp_vent.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "dd_window/dd_window.h"


#define WIN_OP_D_TIME 10
#define CTRL_DISABLE 0
#define CTRL_ENABLE 1

float ctrl_temp_vent_setpoint = 19.0;
int8_t ctrl_temp_vent_mode = CTRL_DISABLE;

float ctrl_temp_vent_set_setpoint(float setpoint)
{
  ctrl_temp_vent_setpoint = setpoint;
  return ctrl_temp_vent_setpoint;
}

float ctrl_temp_vent_setpoint_up(float d_val)
{
  float setpoint = ctrl_temp_vent_get_setpoint();
  setpoint+=d_val;
  setpoint = ctrl_temp_vent_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_temp_vent_setpoint_dn(float d_val)
{
  float setpoint = ctrl_temp_vent_get_setpoint();
  setpoint-=d_val;
  setpoint = ctrl_temp_vent_set_setpoint(setpoint);
  return setpoint;
}


float ctrl_temp_vent_get_setpoint()
{
  return ctrl_temp_vent_setpoint;
}

int8_t ctrl_temp_vent_set_mode(int8_t mode)
{
  ctrl_temp_vent_mode = mode;
  return ctrl_temp_vent_mode;
}
int8_t ctrl_temp_vent_set_mode_manual()
{
  ctrl_temp_vent_set_mode(CTRL_DISABLE);
}
int8_t ctrl_temp_vent_set_mode_auto()
{
  ctrl_temp_vent_set_mode(CTRL_ENABLE);
}
int8_t ctrl_temp_vent_is_enabled()
{
  return ctrl_temp_vent_mode ==  CTRL_ENABLE;
}
int8_t ctrl_temp_vent_get_mode()
{
  return ctrl_temp_vent_mode;
}

void ctrl_temp_vent_setup()
{
  ctrl_temp_vent_setpoint = 19.0;
  ctrl_temp_vent_mode = CTRL_DISABLE;
}

void ctrl_temp_vent_loop()
{
  if (ctrl_temp_vent_mode == CTRL_ENABLE)
  {
    if (srv_sns_air_GetTemperatureError() == 0)
    {

      float temp_current = srv_sns_air_GetTemperature();

      int temp_open = ctrl_temp_vent_setpoint + TEMP_VENT_HISTERESIS;
      int temp_close = ctrl_temp_vent_setpoint - TEMP_VENT_HISTERESIS;

      // OPEN/CLOSE Control cu Histereza
      if (temp_current > temp_open)
      {
        dd_window_open(WIN_OP_D_TIME);
      }
      else if (temp_current < temp_close)
      {
        dd_window_close(WIN_OP_D_TIME);
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
