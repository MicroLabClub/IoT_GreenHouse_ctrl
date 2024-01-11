#include "srv_sns_air_temp_term.h"
#include "srv_sns_air_temp.h"
#include "Arduino.h"


void srv_sns_air_temp_report()
{
  float temp = srv_sns_air_get_temperature();
  Serial.print(F("SRV_SNS_AIR_TEMP| Temperature: "));
  Serial.print(temp,5);
  Serial.print(F(" °C"));

  int error = srv_sns_air_get_temperature_error();
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
