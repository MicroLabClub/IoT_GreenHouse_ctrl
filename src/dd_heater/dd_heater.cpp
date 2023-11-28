
#include "dd_heater.h"
#include "Arduino.h"

int dd_heater_state;
int dd_heater_relay = ED_RELAY_ID_5;

void dd_heater_setup()
{
    dd_heater_off();
}

void dd_heater_loop()
{

    uint8_t state = dd_heater_state;
    size_t relay_id = dd_heater_relay;

    ed_relay_setState(relay_id, state);
}

int dd_heater_on()
{
    int state = dd_heater_set_state( DD_HEATER_ON);
    return state;
}

int dd_heater_off()
{
    int state = dd_heater_set_state(DD_HEATER_OFF);
    return state;
}

int dd_heater_get_gtate()
{
    return dd_heater_state;
}

int dd_heater_set_state( int state)
{
    dd_heater_state = state;
    return dd_heater_state;
}
