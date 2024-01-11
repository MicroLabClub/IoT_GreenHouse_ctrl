#include "dd_air_pump_term.h"
#include "dd_air_pump.h"
#include "Arduino.h"


void dd_air_pump_report()
{
  // Air Pump Report

  int air_pump_state = dd_air_pump_get_state();
  Serial.print("DD_AIR_PUMP: Air Pump ");
  Serial.print(air_pump_state);
  Serial.print(" - ");

  if (air_pump_state == DD_AIR_PUMP_OFF)
  {
    Serial.println(" OFF");
  }
  else if (air_pump_state == DD_AIR_PUMP_ON)
  {
    Serial.println(" ON");
  }
  else
  {
    Serial.println(" UNDEFINED");
  }
}
