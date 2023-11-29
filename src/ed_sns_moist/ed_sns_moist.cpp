#include <Arduino.h>

#include "ed_sns_moist.h"


float ed_sns_moist_moisture = 0;

float ed_sns_moist_GetMoisture(void)
{
  return ed_sns_moist_moisture;
}


void ed_sns_moist_setup()
{
  
}

void ed_sns_moist_loop()
{
  int moisture = analogRead(ED_SNS_MOIST_PIN); // read the analog value from sensor
  ed_sns_moist_moisture = moisture;

  Serial.print("Moisture: ");
  Serial.println(moisture);

}
