#include "ed_bmp_term.h"
#include "ed_bmp.h"
#include "Arduino.h"

void ed_bmp_report()
{
    float temp = ed_bmp_get_temperature();
    Serial.print(F("ED_BMP| Temperature: "));
    Serial.print(temp);
    Serial.print(F(" °C"));

    float press = ed_bmp_get_pressure();
    Serial.print(F(" | Pressure: "));
    Serial.print(press,5);
    Serial.print(F(" Bar"));

    int error = ed_bmp_get_sensor_error();
    Serial.print(F(" | Error: "));
    if (error == 0)
    {
        Serial.print(F("OK"));
    }
    else
    {
        Serial.print(F("N_OK"));
    }
    Serial.println();
}
