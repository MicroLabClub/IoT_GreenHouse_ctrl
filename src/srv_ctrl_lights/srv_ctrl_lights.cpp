#include "srv_ctrl_lights.h"
#include "dd_dht/dd_dht.h"
#include "dd_heater/dd_heater.h"
#include "dd_encoder/dd_encoder.h"

void srv_ctrl_lights_setup()
{
}

float lihts_setpoint = 2000.0;

void srv_ctrl_lights_loop()
{

  if (dd_dht_GetTemperatureError() == 0)
  {

    float lihts_current = dd_dht_GetTemperature();
   

    int lihts_off = lihts_setpoint + LIGHTS_HISTERESIS;
    int lihts_on = lihts_setpoint - LIGHTS_HISTERESIS;

    // ON OFF Control cu Histereza
    if (lihts_current > lihts_off)
    {
      dd_heater_off();
    }
    else if (lihts_current < lihts_on)
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
