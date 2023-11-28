#ifndef ED_RELAY_H
#define ED_RELAY_H

#include "Arduino.h"

#define ED_RELAY_1_PIN GPIO1
#define ED_RELAY_2_PIN GPIO2
#define ED_RELAY_3_PIN GPIO3
#define ED_RELAY_4_PIN GPIO4
#define ED_RELAY_5_PIN GPIO5

#define ED_RELAY_ON LOW
#define ED_RELAY_OFF HIGH

enum ed_relay_t{
    ED_RELAY_ID_1,
    ED_RELAY_ID_2,
    ED_RELAY_ID_3,
    ED_RELAY_ID_4,
    ED_RELAY_ID_5,
    ED_RELAY_NR_OF
};

void ed_relay_setup();
void ed_relay_loop();

int ed_relay_on(size_t relay_it);
int ed_relay_off(size_t relay_it);
int ed_relay_getState(size_t relay_it);
int ed_relay_setState (size_t relay_it, int state);

#endif


