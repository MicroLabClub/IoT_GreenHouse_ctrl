#include "dd_heater_term.h"
#include "dd_heater.h"
#include "Arduino.h"


void dd_heater_report()
{
    // Heater Report

  int heater_state = dd_heater_get_state();
  Serial.print(F("DD_HEATER: Heater "));
  Serial.print(heater_state);
  Serial.print(F(" - "));

  if (heater_state == DD_HEATER_OFF)
  {
    Serial.println(F(" STOP"));
  }
  else if (heater_state == DD_HEATER_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}
