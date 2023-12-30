
#include "srv_sns_air_press_term.h"
#include "srv_sns_air_press.h"
#include "Arduino.h"


void srv_sns_air_press_report()
{
  float press = srv_sns_air_get_pressure();
  Serial.print(F("SRV_SNS_AIR_PRESS| Pressure: "));
  Serial.print(press,5);
  Serial.print(F(" Bar"));

  int error = srv_sns_air_get_pressure_error();
    Serial.print(F(" | Error: "));
    if(error == 0)
    {
      Serial.print(F("OK"));
    }
    else
    {
      Serial.print(F("N_OK"));
    }
    Serial.println();
}
