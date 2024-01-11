#include "srv_sns_air_hum_term.h"
#include "srv_sns_air_hum.h"
#include "Arduino.h"



void srv_sns_air_hum_report()
{
  float hum = srv_sns_air_get_humidity();
  Serial.print(F("SRV_SNS_AIR_HUM| Humidity: "));
  Serial.print(hum,5);
  Serial.print(F(" %"));

  int error = srv_sns_air_get_humidity_error();
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