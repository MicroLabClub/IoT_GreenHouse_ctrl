#ifndef DD_RELAY_H
#define DD_RELAY_H

#include "Arduino.h"

#define DD_RELAY_PIN 6
#define DD_RELAY_ON LOW
#define DD_RELAY_OFF HIGH

void dd_relay_setup();
int dd_relay_on();
int dd_relay_off();
int dd_relay_getState();
int dd_relay_setState (int state);

#endif


