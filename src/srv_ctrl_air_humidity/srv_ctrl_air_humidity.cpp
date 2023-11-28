#include "srv_ctrl_air_humidity.h"
#include "dd_dht/dd_dht.h"
#include "dd_valve/dd_valve.h"

#define VALVE_OP_D_TIME 10
#define SRV_CTRL_DISABLE 0
#define SRV_CTRL_ENABLE 1

float srv_ctrl_air_hum_setpoint = 60.0;
int8_t srv_ctrl_air_hum_mode = SRV_CTRL_DISABLE;

float srv_ctrl_air_hum_set_setpoint(float setpoint)
{
  srv_ctrl_air_hum_setpoint = setpoint;
  return srv_ctrl_air_hum_setpoint;
}

float srv_ctrl_air_hum_setpoint_up(float d_hum)
{
  float setpoint = srv_ctrl_air_hum_get_setpoint();
  setpoint += d_hum;
  setpoint = srv_ctrl_air_hum_set_setpoint(setpoint);
  return setpoint;
}

float srv_ctrl_air_hum_setpoint_dn(float d_hum)
{
  float setpoint = srv_ctrl_air_hum_get_setpoint();
  setpoint -= d_hum;
  setpoint = srv_ctrl_air_hum_set_setpoint(setpoint);
  return setpoint;
}

float srv_ctrl_air_hum_get_setpoint()
{
  return srv_ctrl_air_hum_setpoint;
}

int8_t srv_ctrl_air_hum_set_mode(int8_t mode)
{
  srv_ctrl_air_hum_mode = mode;
  return srv_ctrl_air_hum_mode;
}
int8_t srv_ctrl_air_hum_set_mode_manual()
{
  srv_ctrl_air_hum_set_mode(SRV_CTRL_DISABLE);
}
int8_t srv_ctrl_air_hum_set_mode_auto()
{
  srv_ctrl_air_hum_set_mode(SRV_CTRL_ENABLE);
}
int8_t srv_ctrl_air_hum_is_mode_auto()
{
  return srv_ctrl_air_hum_mode == SRV_CTRL_ENABLE;
}
int8_t srv_ctrl_air_hum_get_mode()
{
  return srv_ctrl_air_hum_mode;
}

void srv_ctrl_air_hum_setup()
{
  srv_ctrl_air_hum_setpoint = 19.0;
  srv_ctrl_air_hum_mode = SRV_CTRL_DISABLE;
}

void srv_ctrl_air_hum_loop()
{
  if (srv_ctrl_air_hum_mode == SRV_CTRL_ENABLE)
  {

    if (dd_dht_GetHumidityError() == 0)
    {

      float hum_current = dd_dht_GetHumidity();

      int hum_off = srv_ctrl_air_hum_setpoint + AIR_HUM_HISTERESIS;
      int hum_on = srv_ctrl_air_hum_setpoint - AIR_HUM_HISTERESIS;

      // ON OFF Control cu Histereza
      if (hum_current > hum_off)
      {
        dd_valve_off();
      }
      else if (hum_current < hum_on)
      {
        dd_valve_on(VALVE_OP_D_TIME);
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      dd_valve_off();
    }
  }
}
