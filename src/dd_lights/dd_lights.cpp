
#include "dd_lights.h"
#include "Arduino.h"

int dd_lights_state;
int dd_lights_relay = ED_RELAY_ID_8;

int dd_lights_op_cnt = 0;

int dd_lights_set_state( int state)
{
    if(state == DD_LIGHTS_ON)
    {
        dd_lights_state = DD_LIGHTS_ON;
    }
    else
    {
        dd_lights_state = DD_LIGHTS_OFF;
    }
    return dd_lights_state;
}

int dd_lights_get_gtate()
{
    return dd_lights_state;
}

int dd_lights_off()
{
    int state = dd_lights_set_state(DD_LIGHTS_OFF);
    return state;
}

int dd_lights_on(int time)
{
    int state = dd_lights_set_state( DD_LIGHTS_ON);
    dd_lights_op_cnt = time;
    return state;
}


void dd_lights_setup()
{
    dd_lights_off();
}

void dd_lights_loop()
{
    if(dd_lights_op_cnt > -1) // if not continous
    {
        if(--dd_lights_op_cnt <= 0)// decrement
        {
            dd_lights_op_cnt = 0;
            dd_lights_state = DD_LIGHTS_OFF;//change to off
        }
    }

    if(dd_lights_state == DD_LIGHTS_ON)
    {
        ed_relay_on(dd_lights_relay);
    }
    else
    {
        ed_relay_off(dd_lights_relay);
        dd_lights_op_cnt = 0;
        dd_lights_state = DD_LIGHTS_OFF;
    }
} 
