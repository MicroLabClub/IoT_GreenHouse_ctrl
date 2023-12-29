#include <Arduino.h>

#include "ed_sns_soil_moist.h"


float ed_sns_soil_moisture = 0;

float ed_sns_soil_moist_get_value(void)
{
  return ed_sns_soil_moisture;
}


void ed_sns_soil_moist_setup()
{
  
}

void ed_sns_soil_moist_loop()
{
  int moisture = analogRead(ed_sns_soil_moist_PIN); // read the analog value from sensor
  ed_sns_soil_moisture = moisture;

  // Serial.print("Moisture: ");
  // Serial.println(moisture);

}
