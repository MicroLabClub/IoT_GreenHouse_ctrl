#ifndef DD_HEATER_H
#define DD_HEATER_H

#include "Arduino.h"
#include "ed_relay/ed_relay.h"



#define DD_HEATER_ON    ED_RELAY_ON
#define DD_HEATER_OFF   ED_RELAY_OFF


void dd_heater_setup();
void dd_heater_loop();

int dd_heater_on();
int dd_heater_off();
int dd_heater_get_state();
int dd_heater_set_state (int state);

#endif


