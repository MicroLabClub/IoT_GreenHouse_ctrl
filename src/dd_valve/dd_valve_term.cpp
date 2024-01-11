#include "dd_valve_term.h"
#include "dd_valve.h"
#include "Arduino.h"



void dd_valve_report()
{
  // Valve Report

  int valve_state = dd_valve_get_state();
  Serial.print(F("DD_VALVE: Valve "));
  Serial.print(valve_state);
  Serial.print(F(" - "));

  if (valve_state == DD_VALVE_CLOSE)
  {
    Serial.println(F(" CLOSE"));
  }
    else if (valve_state == DD_VALVE_OPEN)
    {
        Serial.println(F(" OPEN"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}