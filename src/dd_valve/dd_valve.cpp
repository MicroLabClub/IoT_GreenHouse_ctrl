
#include "dd_valve.h"
#include "Arduino.h"

int dd_valve_state = DD_VALVE_OFF;
int dd_valve_relay = ED_RELAY_ID_4;

int dd_valve_op_cnt = 0;

int dd_valve_set_state(int state)
{
    if (state == DD_VALVE_ON)
    {
        dd_valve_state = DD_VALVE_ON;
    }
    else
    {
        dd_valve_state = DD_VALVE_OFF;
    }
    return dd_valve_state;
}


int dd_valve_get_state()
{
    return dd_valve_state;
}

int dd_valve_off()
{
    int state = dd_valve_set_state(DD_VALVE_OFF);
    return state;
}

int dd_valve_on(int time)
{
    int state = dd_valve_set_state(DD_VALVE_ON);
    dd_valve_op_cnt = time;
    return state;
}


void dd_valve_setup()
{
    dd_valve_off();
}

void dd_valve_loop()
{
    if (dd_valve_op_cnt > -1) // if not continous
    {
        if (--dd_valve_op_cnt <= 0)// decrement
        {
            dd_valve_op_cnt = 0;
            dd_valve_state = DD_VALVE_OFF;//change to off
        }
    }

    if (dd_valve_state == DD_VALVE_ON)
    {
        ed_relay_on(dd_valve_relay);
    }
    else
    { // stop
        ed_relay_off(dd_valve_relay);
        dd_valve_op_cnt = 0;
        dd_valve_state = DD_VALVE_OFF;
    }
}
