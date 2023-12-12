#include "ctrl_air_humidity.h"
#include "srv_sns_air_hum/srv_sns_air_hum.h"
#include "dd_valve/dd_valve.h"

#include "Arduino.h"

float ctrl_air_hum_setpoint = 60.0;
int8_t ctrl_air_hum_mode = CTRL_AIR_HUM_DISABLE;

float ctrl_air_hum_set_setpoint(float setpoint)
{
  ctrl_air_hum_setpoint = setpoint;
  return ctrl_air_hum_setpoint;
}

float ctrl_air_hum_get_setpoint()
{
  return ctrl_air_hum_setpoint;
}

float ctrl_air_hum_setpoint_up(float d_val)
{
  float setpoint = ctrl_air_hum_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_air_hum_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_air_hum_setpoint_dn(float d_val)
{
  float setpoint = ctrl_air_hum_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_air_hum_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_air_hum_set_mode(int8_t mode)
{
  ctrl_air_hum_mode = mode;
  return ctrl_air_hum_mode;
}
int8_t ctrl_air_hum_set_mode_manual()
{
  return ctrl_air_hum_set_mode(CTRL_AIR_HUM_DISABLE);
}
int8_t ctrl_air_hum_set_mode_auto()
{
  return ctrl_air_hum_set_mode(CTRL_AIR_HUM_ENABLE);
}
int8_t ctrl_air_hum_is_enabled()
{
  return ctrl_air_hum_mode == CTRL_AIR_HUM_ENABLE;
}
int8_t ctrl_air_hum_get_mode()
{
  return ctrl_air_hum_mode;
}

void ctrl_air_hum_setup()
{
  ctrl_air_hum_setpoint = 19.0;
  ctrl_air_hum_mode = CTRL_AIR_HUM_DISABLE;
}

float ctrl_air_hum_get_current_hum()
{
  return srv_sns_air_GetHumidity();
}
void ctrl_air_hum_loop()
{
  if (ctrl_air_hum_mode == CTRL_AIR_HUM_ENABLE)
  {

    if (srv_sns_air_GetHumidityError() == 0)
    {
      float hum_current = srv_sns_air_GetHumidity();
      int hum_off = ctrl_air_hum_setpoint + AIR_HUM_HISTERESIS;
      int hum_on = ctrl_air_hum_setpoint - AIR_HUM_HISTERESIS;

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
