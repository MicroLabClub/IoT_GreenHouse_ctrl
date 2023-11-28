#include "srv_ctrl_temp_vent.h"
#include "dd_dht/dd_dht.h"
#include "dd_window/dd_window.h"


#define WIN_OP_D_TIME 10
#define SRV_CTRL_DISABLE 0
#define SRV_CTRL_ENABLE 1

float srv_ctrl_temp_vent_setpoint = 19.0;
int8_t srv_ctrl_temp_vent_mode = SRV_CTRL_DISABLE;

float srv_ctrl_temp_vent_set_setpoint(float setpoint)
{
  srv_ctrl_temp_vent_setpoint = setpoint;
  return srv_ctrl_temp_vent_setpoint;
}

float srv_ctrl_temp_vent_setpoint_up(float d_temp)
{
  float setpoint = srv_ctrl_temp_vent_get_setpoint();
  setpoint+=d_temp;
  setpoint = srv_ctrl_temp_vent_set_setpoint(setpoint);
  return setpoint;
}

float srv_ctrl_temp_vent_setpoint_dn(float d_temp)
{
  float setpoint = srv_ctrl_temp_vent_get_setpoint();
  setpoint-=d_temp;
  setpoint = srv_ctrl_temp_vent_set_setpoint(setpoint);
  return setpoint;
}


float srv_ctrl_temp_vent_get_setpoint()
{
  return srv_ctrl_temp_vent_setpoint;
}

int8_t srv_ctrl_temp_vent_set_mode(int8_t mode)
{
  srv_ctrl_temp_vent_mode = mode;
  return srv_ctrl_temp_vent_mode;
}
int8_t srv_ctrl_temp_vent_set_mode_manual()
{
  srv_ctrl_temp_vent_set_mode(SRV_CTRL_DISABLE);
}
int8_t srv_ctrl_temp_vent_set_mode_auto()
{
  srv_ctrl_temp_vent_set_mode(SRV_CTRL_ENABLE);
}
int8_t srv_ctrl_temp_vent_is_mode_auto()
{
  return srv_ctrl_temp_vent_mode ==  SRV_CTRL_ENABLE;
}
int8_t srv_ctrl_temp_vent_get_mode()
{
  return srv_ctrl_temp_vent_mode;
}

void srv_ctrl_temp_vent_setup()
{
  srv_ctrl_temp_vent_setpoint = 19.0;
  srv_ctrl_temp_vent_mode = SRV_CTRL_DISABLE;
}

void srv_ctrl_temp_vent_loop()
{
  if (srv_ctrl_temp_vent_mode == SRV_CTRL_ENABLE)
  {
    if (dd_dht_GetTemperatureError() == 0)
    {

      float temp_current = dd_dht_GetTemperature();


      int temp_open = srv_ctrl_temp_vent_setpoint + TEMP_VENT_HISTERESIS;
      int temp_close = srv_ctrl_temp_vent_setpoint - TEMP_VENT_HISTERESIS;

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
