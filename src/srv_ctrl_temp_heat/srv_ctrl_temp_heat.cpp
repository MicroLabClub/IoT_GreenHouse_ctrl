#include "srv_ctrl_temp_heat.h"
#include "dd_dht/dd_dht.h"
#include "dd_heater/dd_heater.h"
#include "dd_encoder/dd_encoder.h"

void srv_ctrl_temp_heat_setup()
{
}

void srv_ctrl_temp_heat_loop()
{

  if (dd_dht_GetTemperatureError() == 0)
  {

    float temp_current = dd_dht_GetTemperature();
    int enc_counter = dd_encoder_get_counter();
    float temp_setpoint = (float)enc_counter * TEMP_HEAT_RESOLUTION;

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
