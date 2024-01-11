#include "dd_lights_term.h"
#include "dd_lights.h"
#include "Arduino.h"


void dd_lights_report()
{
  // Lights Report

  int lights_state = dd_lights_get_state();
  Serial.print(F("DD_LIGHTS: Lights "));
  Serial.print(lights_state);
  Serial.print(F(" - "));

  if (lights_state == DD_LIGHTS_OFF)
  {
    Serial.println(F(" OFF"));
  }
  else if (lights_state == DD_LIGHTS_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}
