
#include "dd_valve.h"
#include "Arduino.h"

int dd_valve_state;
int dd_valve_relay = DD_RELAY_ID_4;

void dd_valve_setup()
{
    dd_valve_off();
}

void dd_valve_loop()
{

    uint8_t state = dd_valve_state;
    size_t relay_id = dd_valve_relay;

    dd_relay_setState(relay_id, state);
}

int dd_valve_on()
{
    int state = dd_valve_set_state( DD_VALVE_ON);
    return state;
}

int dd_valve_off()
{
    int state = dd_valve_set_state(DD_VALVE_OFF);
    return state;
}

int dd_valve_get_gtate()
{
    return dd_valve_state;
}

int dd_valve_set_state( int state)
{
    dd_valve_state = state;
    return dd_valve_state;
}
