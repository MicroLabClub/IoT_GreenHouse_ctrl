
#include "dd_heater.h"
#include "Arduino.h"

int dd_heater_state;
int dd_heater_relay = ED_RELAY_ID_3;

int dd_heater_op_cnt = 0;

int dd_heater_set_state( int state)
{
    if(state == DD_HEATER_ON)
    {
        dd_heater_state = DD_HEATER_ON;
    }
    else
    {
        dd_heater_state = DD_HEATER_OFF;
    }
    return dd_heater_state;
}

int dd_heater_get_state()
{
    return dd_heater_state;
}

int dd_heater_off()
{
    int state = dd_heater_set_state(DD_HEATER_OFF);
    return state;
}

int dd_heater_on(int time)
{
    int state = dd_heater_set_state( DD_HEATER_ON);
    dd_heater_op_cnt = time;
    return state;
}


void dd_heater_setup()
{
    dd_heater_off();
}

void dd_heater_loop()
{
    if(dd_heater_op_cnt > -1) // if not continous
    {
        if(--dd_heater_op_cnt <= 0)// decrement
        {
            dd_heater_op_cnt = 0;
            dd_heater_state = DD_HEATER_OFF;//change to off
        }
    }

    if(dd_heater_state == DD_HEATER_ON)
    {
        ed_relay_on(dd_heater_relay);
    }
    else
    {
        ed_relay_off(dd_heater_relay);
        dd_heater_op_cnt = 0;
        dd_heater_state = DD_HEATER_OFF;
    }
}
