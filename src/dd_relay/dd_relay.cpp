
#include "dd_relay.h"
#include "Arduino.h"

int dd_relay_state[DD_RELAY_NR_OF];
int dd_relay_pin[DD_RELAY_NR_OF] = {DD_RELAY_1_PIN, DD_RELAY_2_PIN};

void dd_relay_setup()
{
    for (size_t relay_it = 0; relay_it < DD_RELAY_NR_OF; relay_it++)
    {
        size_t relay_pin = dd_relay_pin[relay_it];
        pinMode(relay_pin, OUTPUT);
        dd_relay_off(relay_it);

    }

}

int dd_relay_on(size_t relay_it)
{
    int state = dd_relay_setState(relay_it,DD_RELAY_ON);
    return state;
}

int dd_relay_off(size_t relay_it)
{
    int state = dd_relay_setState(relay_it, DD_RELAY_OFF);
    return state;
}

int dd_relay_getState(size_t relay_it)
{
    return dd_relay_state[relay_it];
}

int dd_relay_setState(size_t relay_it, int state)
{
    dd_relay_state[relay_it] = state;
    size_t pin_nr = dd_relay_pin[relay_it];
    digitalWrite(pin_nr, state);
    return dd_relay_state[relay_it];
}
