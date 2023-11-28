#include "ctrl_lights.h"
#include "ed_dht/ed_dht.h"
#include "dd_heater/dd_heater.h"
#include "ed_encoder/ed_encoder.h"

void ctrl_lights_setup()
{
}

float lihts_setpoint = 2000.0;

void ctrl_lights_loop()
{

  if (ed_dht_GetTemperatureError() == 0)
  {

    float lihts_current = ed_dht_GetTemperature();
   

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
