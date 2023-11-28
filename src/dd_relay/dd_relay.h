#ifndef DD_RELAY_H
#define DD_RELAY_H

#include "Arduino.h"

#define DD_RELAY_1_PIN GPIO1
#define DD_RELAY_2_PIN GPIO2
#define DD_RELAY_3_PIN GPIO3
#define DD_RELAY_4_PIN GPIO4
#define DD_RELAY_5_PIN GPIO5

#define DD_RELAY_ON LOW
#define DD_RELAY_OFF HIGH

enum dd_relay_t{
    DD_RELAY_ID_1,
    DD_RELAY_ID_2,
    DD_RELAY_ID_3,
    DD_RELAY_ID_4,
    DD_RELAY_ID_5,
    DD_RELAY_NR_OF
};

void dd_relay_setup();
void dd_relay_loop();

int dd_relay_on(size_t relay_it);
int dd_relay_off(size_t relay_it);
int dd_relay_getState(size_t relay_it);
int dd_relay_setState (size_t relay_it, int state);

#endif


