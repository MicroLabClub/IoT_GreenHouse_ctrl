#include "ctrl_air_press_term.h"
#include "ctrl_air_press.h"
#include "Arduino.h"

void ctrl_air_press_report()
{
  if (ctrl_air_press_is_enabled())
  {
    Serial.print(F("CTRL_AIR_PRESS: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_AIR_PRESS: Mode MANUAL"));
  }

  float press_current = ctrl_air_press_get_current_press();
  Serial.print(F(" | Cur: "));
  Serial.print(press_current,5);
  Serial.print(F(" Bar"));

  float press_setpoint = ctrl_air_press_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(press_setpoint);
  Serial.print(F(" Bar"));

  Serial.print(F(" | HIST [ "));
  Serial.print(press_setpoint + CTRL_AIR_PRESS_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(press_setpoint - CTRL_AIR_PRESS_HISTERESIS);
  Serial.print(F(" Bar] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_air_press_get_output() == CTRL_AIR_PRESS_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_air_press_get_output() == CTRL_AIR_PRESS_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}
