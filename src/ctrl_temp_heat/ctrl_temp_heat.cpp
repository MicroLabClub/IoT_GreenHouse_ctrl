#include "ctrl_temp_heat.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "dd_heater/dd_heater.h"
#include "ed_encoder/ed_encoder.h"

void ctrl_temp_heat_setup()
{
}

float temp_setpoint = 19.0;

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
