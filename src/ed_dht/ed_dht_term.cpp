#include "ed_dht_term.h"
#include "ed_dht.h"
#include "Arduino.h"

void ed_dht_report()
{
    Serial.print(F("ED_DHT "));

    float temp = ed_dht_get_temperature();
    Serial.print(F(" | Temperature: "));
    Serial.print(temp);
    Serial.print(F(" °C"));


    int error = ed_dht_get_temperature_error();
    Serial.print(F(" | Temp Error: "));
    if (error == 0)
    {
        Serial.print(F("OK"));
    }
    else
    {
        Serial.print(F("N_OK"));
    }
    // Serial.println();

    float hum = ed_dht_get_humidity();
    Serial.print(F(" | Humidity: "));
    Serial.print(hum);
    Serial.print(F(" %"));

    error =  ed_dht_get_humidity_error();
    Serial.print(F(" | Hum Error: "));
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


    

