#include "ed_relay_term.h"
#include "ed_relay.h"
#include "Arduino.h"

void ed_relay_report()
{
  // Relay Report
  Serial.print("ED_RELAY: Relay ");
  for (size_t relay_it = 0; relay_it < ED_RELAY_NR_OF; relay_it++)
  {
    /* code */
    int relay_state = ed_relay_getState(relay_it);
    int relay_pin = ed_relay_get_pin(relay_it);
    Serial.print(" [");
    Serial.print(relay_it);
    Serial.print(":");
    Serial.print(relay_pin);
    Serial.print("]-");
    if (relay_state == ED_RELAY_ON)
    {
      Serial.print("ON");
    }
    else
    {
      Serial.print("OFF");
    }
  }
  Serial.println();
}

