#include "ctrl_temp_vent_term.h"
#include "ctrl_temp_vent.h"
#include "Arduino.h"

void ctrl_temp_vent_report()
{
  if (ctrl_temp_vent_get_mode() == CTRL_TEMP_VENT_ENABLE)
  {
    Serial.print(F("CTRL_TEMP_VENT: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_TEMP_VENT: Mode MANUAL"));
  }

  float temp_current = ctrl_temp_vent_get_current_temp();
  Serial.print(F(" | Cur: "));
  Serial.print(temp_current,5);
  Serial.print(F(" °C"));

  float temp_setpoint = ctrl_temp_vent_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F(" °C"));

  Serial.print(F(" | HIST [ "));
  Serial.print(temp_setpoint + CTRL_TEMP_VENT_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(temp_setpoint - CTRL_TEMP_VENT_HISTERESIS);
  Serial.print(F(" °C] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_temp_vent_get_output() == CTRL_TEMP_VENT_OUT_OPEN)
    {
      Serial.print(F("OPEN"));
    }
    else if(ctrl_temp_vent_get_output() == CTRL_TEMP_VENT_OUT_CLOSE)
    {
      Serial.print(F("CLOSE"));
    }
    else if(ctrl_temp_vent_get_output() == CTRL_TEMP_VENT_OUT_STOP)
    {
      Serial.print(F("STOP"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }
    Serial.println();

}
