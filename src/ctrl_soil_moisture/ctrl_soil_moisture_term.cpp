#include "ctrl_soil_moisture_term.h"
#include "ctrl_soil_moisture.h"
#include "Arduino.h"


void ctrl_soil_moist_report()
{
  if (ctrl_soil_moist_is_enabled())
  {
    Serial.print(F("CTRL_SOIL_MOIST: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_SOIL_MOIST: Mode MANUAL"));
  }

  float moist_current = ctrl_soil_moist_get_current_moist();
  Serial.print(F(" | Cur: "));
  Serial.print(moist_current,5);
  Serial.print(F(" %"));

  float moist_setpoint = ctrl_soil_moist_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(moist_setpoint);
  Serial.print(F(" %"));

  Serial.print(F(" | HIST [ "));
  Serial.print(moist_setpoint + CTRL_SOIL_MOIST_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(moist_setpoint - CTRL_SOIL_MOIST_HISTERESIS);
  Serial.print(F(" %] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_soil_moist_get_output() == CTRL_SOIL_MOIST_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_soil_moist_get_output() == CTRL_SOIL_MOIST_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}


