#include "srv_sns_amb_light_term.h"
#include "srv_sns_amb_light.h"
#include "Arduino.h"


void srv_sns_amb_light_report()
{
  float light = srv_sns_amb_get_luminozity();
  Serial.print(F("SRV_SNS_AMB_LIGHT| Light: "));
  Serial.print(light,5);
  Serial.print(F(" Lux"));

  int error = srv_sns_amb_get_luminozity_error();
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
