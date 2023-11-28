
#include "ed_relay.h"
#include "Arduino.h"

int ed_relay_state[ED_RELAY_NR_OF];
int ed_relay_pin[ED_RELAY_NR_OF] = {
    ED_RELAY_1_PIN, 
    ED_RELAY_2_PIN,
    ED_RELAY_3_PIN,
    ED_RELAY_4_PIN,
    ED_RELAY_5_PIN
     };

void ed_relay_setup()
{
    for (size_t relay_it = 0; relay_it < ED_RELAY_NR_OF; relay_it++)
    {
        size_t relay_pin = ed_relay_pin[relay_it];
        pinMode(relay_pin, OUTPUT);
        ed_relay_off(relay_it);
    }
}

void ed_relay_loop()
{

    for (size_t relay_it = 0; relay_it < ED_RELAY_NR_OF; relay_it++)
    {
        uint8_t state = ed_relay_state[relay_it];
        size_t pin_nr = ed_relay_pin[relay_it];

        digitalWrite(pin_nr, state);
    }
}

int ed_relay_on(size_t relay_it)
{
    int state = ed_relay_setState(relay_it, ED_RELAY_ON);
    return state;
}

int ed_relay_off(size_t relay_it)
{
    int state = ed_relay_setState(relay_it, ED_RELAY_OFF);
    return state;
}

int ed_relay_getState(size_t relay_it)
{
    return ed_relay_state[relay_it];
}

int ed_relay_setState(size_t relay_it, int state)
{
    ed_relay_state[relay_it] = state;
    return ed_relay_state[relay_it];
}
