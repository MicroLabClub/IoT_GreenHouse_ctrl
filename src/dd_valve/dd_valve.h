#ifndef DD_VALVE_H
#define DD_VALVE_H

#include "Arduino.h"
#include "dd_relay/dd_relay.h"



#define DD_VALVE_ON    DD_RELAY_ON
#define DD_VALVE_OFF   DD_RELAY_OFF


void dd_valve_setup();
void dd_valve_loop();

int dd_valve_on();
int dd_valve_off();
int dd_valve_get_state();
int dd_valve_set_state (int state);

#endif


