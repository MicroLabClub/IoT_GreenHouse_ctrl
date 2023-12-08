#include "ctrl_temp_heat.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "dd_heater/dd_heater.h"
#include "ed_encoder/ed_encoder.h"

float temp_setpoint = 19.0;
int8_t ctrl_temp_heat_mode = CTRL_TEMP_HEAT_DISABLE;

void ctrl_temp_heat_setup()
{
float temp_setpoint = 19.0;
int8_t ctrl_temp_heat_mode = CTRL_TEMP_HEAT_DISABLE;
}



void ctrl_temp_heat_loop()
{
  if (srv_sns_air_GetTemperatureError() == 0)
  {
    float temp_current = srv_sns_air_GetTemperature();

    int temp_off = temp_setpoint + TEMP_HEAT_HISTERESIS;
    int temp_on = temp_setpoint - TEMP_HEAT_HISTERESIS;

    // ON OFF Control cu Histereza
    if (temp_current > temp_off)
    {
      dd_heater_off();
    }
    else if (temp_current < temp_on)
    {
      dd_heater_on();
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    dd_heater_off();
  }
}

int8_t ctrl_temp_heat_set_mode(int8_t mode)
{
  if (mode == CTRL_TEMP_HEAT_DISABLE)
  {
    ctrl_temp_heat_set_mode_manual();
  }
  else if (mode == CTRL_TEMP_HEAT_ENABLE)
  {
    ctrl_temp_heat_set_mode_auto();
  }
  else
  {
    return -1;
  }
  return 0;
}
int8_t ctrl_temp_heat_set_mode_manual()
{
  return ctrl_temp_heat_mode = CTRL_TEMP_HEAT_DISABLE;
}
int8_t ctrl_temp_heat_set_mode_auto()
{
  return ctrl_temp_heat_mode = CTRL_TEMP_HEAT_ENABLE;
}
int8_t ctrl_temp_heat_get_mode()
{
  return ctrl_temp_heat_mode;
}
int8_t ctrl_temp_heat_is_enabled()
{
  return ctrl_temp_heat_mode == CTRL_TEMP_HEAT_ENABLE;
}

float ctrl_temp_heat_set_setpoint(float setpoint)
{
   return temp_setpoint = setpoint;  
}
float ctrl_temp_heat_get_setpoint()
{
  return temp_setpoint;
}
float ctrl_temp_heat_setpoint_up(float d_val)
{
  return temp_setpoint += d_val;
}
float ctrl_temp_heat_setpoint_dn(float d_val)
{
  return temp_setpoint -= d_val;
}

float ctrl_temp_heat_get_current_temp()
{
  return srv_sns_air_GetTemperature();
}
