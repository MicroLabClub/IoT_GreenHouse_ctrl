#include "ed_bh1750_term.h"
#include "ed_bh1750.h"
#include "Arduino.h"

void ed_bh1750_report()
{
    float lux = ed_bh1750_get_luminozity();
    Serial.print(F("ED_BH1750| Lux: "));
    Serial.print(lux);
    Serial.print(F(" lx"));
    
    int error = ed_bh1750_get_luminozity_error();
    Serial.print(F(" Error: "));
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

