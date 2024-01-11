#include "ctrl_lights_term.h"
#include "ctrl_lights.h"
#include "Arduino.h"

void ctrl_lights_report()
{
  if (ctrl_lights_is_enabled())
  {
    Serial.print(F("CTRL_LIGHTS: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_LIGHTS: Mode MANUAL"));
  }

  float lights_current = ctrl_lights_get_current_light();
  Serial.print(F(" | Cur: "));
  Serial.print(lights_current,5);
  Serial.print(F(" %"));

  float lights_setpoint = ctrl_lights_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(lights_setpoint);
  Serial.print(F(" %"));

  Serial.print(F(" | HIST [ "));
  Serial.print(lights_setpoint + CTRL_LIGHTS_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(lights_setpoint - CTRL_LIGHTS_HISTERESIS);
  Serial.print(F(" %] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_lights_get_output() == CTRL_LIGHTS_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_lights_get_output() == CTRL_LIGHTS_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}
