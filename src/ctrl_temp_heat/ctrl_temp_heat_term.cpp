#include "ctrl_temp_heat_term.h"
#include "ctrl_temp_heat.h"
#include "Arduino.h"

void ctrl_temp_heat_report()
{
  if (ctrl_temp_heat_get_mode() == CTRL_TEMP_HEAT_ENABLE)
  {
    Serial.print(F("CTRL_TEMP_HEAT: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_TEMP_HEAT: Mode MANUAL"));
  }

  float temp_current = ctrl_temp_heat_get_current_temp();
  Serial.print(F(" | Cur: "));
  Serial.print(temp_current,5);
  Serial.print(F(" °C"));

  float temp_setpoint = ctrl_temp_heat_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F(" °C"));

  Serial.print(F(" | HIST [ "));
  Serial.print(temp_setpoint + CTRL_TEMP_HEAT_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(temp_setpoint - CTRL_TEMP_HEAT_HISTERESIS);
  Serial.print(F(" °C] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_temp_heat_get_output() == CTRL_TEMP_HEAT_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_temp_heat_get_output() == CTRL_TEMP_HEAT_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}
