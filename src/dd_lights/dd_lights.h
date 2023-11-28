#ifndef DD_LIGHTS_H
#define DD_LIGHTS_H

#include "Arduino.h"
#include "dd_relay/dd_relay.h"



#define DD_LIGHTS_ON    DD_RELAY_ON
#define DD_LIGHTS_OFF   DD_RELAY_OFF


void dd_lights_setup();
void dd_lights_loop();

int dd_lights_on();
int dd_lights_off();
int dd_lights_get_state();
int dd_lights_set_state (int state);

#endif


