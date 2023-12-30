#include "ctrl_air_hum_term.h"
#include "ctrl_air_hum.h"
#include "Arduino.h"

void ctrl_air_hum_report()
{
  if (ctrl_air_hum_is_enabled())
  {
    Serial.print(F("CTRL_AIR_HUM: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_AIR_HUM: Mode MANUAL"));
  }

  float hum_current = ctrl_air_hum_get_current_hum();
  Serial.print(F(" | Cur: "));
  Serial.print(hum_current,5);
  Serial.print(F(" %"));

  float hum_setpoint = ctrl_air_hum_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(hum_setpoint);
  Serial.print(F(" %"));

  Serial.print(F(" | HIST [ "));
  Serial.print(hum_setpoint + CTRL_AIR_HUM_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(hum_setpoint - CTRL_AIR_HUM_HISTERESIS);
  Serial.print(F(" %] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_air_hum_get_output() == CTRL_AIR_HUM_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_air_hum_get_output() == CTRL_AIR_HUM_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}   
