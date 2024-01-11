#ifndef DD_VALVE_H
#define DD_VALVE_H

#include "Arduino.h"
#include "ed_relay/ed_relay.h"

#define DD_VALVE_OPEN    ED_RELAY_ON
#define DD_VALVE_CLOSE   ED_RELAY_OFF


void dd_valve_setup();
void dd_valve_loop();

int dd_valve_on(int time);
int dd_valve_off();
int dd_valve_get_state();
int dd_valve_set_state(int state);

#endif


