#ifndef DD_AIR_PUMP_H
#define DD_AIR_PUMP_H

#include "Arduino.h"
#include "ed_relay/ed_relay.h"



#define DD_AIR_PUMP_ON    ED_RELAY_ON
#define DD_AIR_PUMP_OFF   ED_RELAY_OFF


void dd_air_pump_setup();
void dd_air_pump_loop();

int dd_air_pump_on(int time);
int dd_air_pump_off();
int dd_air_pump_get_state();
int dd_air_pump_set_state(int state);

#endif


