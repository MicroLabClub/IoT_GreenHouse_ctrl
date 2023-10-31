
#include "dd_relay.h"
#include "Arduino.h"

int dd_relay_state = LOW;

void dd_relay_setup(){
    pinMode(DD_RELAY_PIN, OUTPUT);
    dd_relay_off();
}

int dd_relay_on(){
    int state = dd_relay_setState(DD_RELAY_ON);
    return state;
}

int dd_relay_off(){
    int state = dd_relay_setState(DD_RELAY_OFF);
    return state;
}

int dd_relay_getState(){
    return dd_relay_state;
}

int dd_relay_setState (int state){
    dd_relay_state = state;
    digitalWrite(DD_RELAY_PIN,dd_relay_state);
    return dd_relay_state;
}

