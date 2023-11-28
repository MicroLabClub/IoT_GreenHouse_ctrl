#include "srv_ctrl_air_humidity.h"
#include "dd_dht/dd_dht.h"
#include "dd_valve/dd_valve.h"

void srv_ctrl_air_hum_setup()
{
}

float hum_setpoint = 60.0;

void srv_ctrl_air_hum_loop()
{

  if (dd_dht_GetHumidityError() == 0)
  {

    float hum_current = dd_dht_GetHumidity();


    int hum_off = hum_setpoint + AIR_HUM_HISTERESIS;
    int hum_on = hum_setpoint - AIR_HUM_HISTERESIS;

    // ON OFF Control cu Histereza
    if (hum_current > hum_off)
    {
      dd_valve_off();
    }
    else if (hum_current < hum_on)
    {
      dd_valve_on();
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
