#include "ctrl_air_humidity.h"
#include "ed_dht/ed_dht.h"
#include "dd_valve/dd_valve.h"

#define VALVE_OP_D_TIME 10
#define CTRL_DISABLE 0
#define CTRL_ENABLE 1

float ctrl_air_hum_setpoint = 60.0;
int8_t ctrl_air_hum_mode = CTRL_DISABLE;

float ctrl_air_hum_set_setpoint(float setpoint)
{
  ctrl_air_hum_setpoint = setpoint;
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

float ctrl_air_hum_get_setpoint()
{
  return ctrl_air_hum_setpoint;
}

int8_t ctrl_air_hum_set_mode(int8_t mode)
{
  ctrl_air_hum_mode = mode;
  return ctrl_air_hum_mode;
}
int8_t ctrl_air_hum_set_mode_manual()
{
  ctrl_air_hum_set_mode(CTRL_DISABLE);
}
int8_t ctrl_air_hum_set_mode_auto()
{
  ctrl_air_hum_set_mode(CTRL_ENABLE);
}
int8_t ctrl_air_hum_is_enabled()
{
  return ctrl_air_hum_mode == CTRL_ENABLE;
}
int8_t ctrl_air_hum_get_mode()
{
  return ctrl_air_hum_mode;
}

void ctrl_air_hum_setup()
{
  ctrl_air_hum_setpoint = 19.0;
  ctrl_air_hum_mode = CTRL_DISABLE;
}

void ctrl_air_hum_loop()
{
  if (ctrl_air_hum_mode == CTRL_ENABLE)
  {

    if (ed_dht_GetHumidityError() == 0)
    {

      float hum_current = ed_dht_GetHumidity();

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
