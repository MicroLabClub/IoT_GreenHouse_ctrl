#include "srv_sns_soil_moist_term.h"
#include "srv_sns_soil_moist.h"
#include "Arduino.h"


void srv_sns_soil_moist_report()
{
  float moist = srv_sns_soil_get_moisture();
  Serial.print(F("SRV_SNS_SOIL_MOIST| Moisture: "));
  Serial.print(moist,5);
  Serial.print(F(" %"));

  int error = srv_sns_soil_get_moisture_error();
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
