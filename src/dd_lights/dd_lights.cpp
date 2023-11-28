
#include "dd_lights.h"
#include "Arduino.h"

int dd_lights_state;
int dd_lights_relay = ED_RELAY_ID_3;

void dd_lights_setup()
{
    dd_lights_off();
}

void dd_lights_loop()
{

    uint8_t state = dd_lights_state;
    size_t relay_id = dd_lights_relay;

    ed_relay_setState(relay_id, state);
}

int dd_lights_on()
{
    int state = dd_lights_set_state( DD_LIGHTS_ON);
    return state;
}

int dd_lights_off()
{
    int state = dd_lights_set_state(DD_LIGHTS_OFF);
    return state;
}

int dd_lights_get_gtate()
{
    return dd_lights_state;
}

int dd_lights_set_state( int state)
{
    dd_lights_state = state;
    return dd_lights_state;
}
