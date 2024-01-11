#include "ed_sns_soil_moist_term.h"
#include "ed_sns_soil_moist.h"
#include "Arduino.h"

void ed_sns_soil_moist_report()
{
    float moist = ed_sns_soil_moist_get_value();
    Serial.print("ED_SNS_SOIL_MOIST: Moisture ");
    Serial.print(moist);
    Serial.println();

}


