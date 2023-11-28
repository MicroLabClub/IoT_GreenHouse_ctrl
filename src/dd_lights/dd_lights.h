#ifndef DD_LIGHTS_H
#define DD_LIGHTS_H

#include "Arduino.h"
#include "ed_relay/ed_relay.h"



#define DD_LIGHTS_ON    ED_RELAY_ON
#define DD_LIGHTS_OFF   ED_RELAY_OFF


void dd_lights_setup();
void dd_lights_loop();

int dd_lights_on();
int dd_lights_off();
int dd_lights_get_state();
int dd_lights_set_state (int state);

#endif


