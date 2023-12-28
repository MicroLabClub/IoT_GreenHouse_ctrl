
#include "dd_air_pump.h"
#include "Arduino.h"

int dd_air_pump_state = DD_AIR_PUMP_OFF;
int dd_air_pump_relay = ED_RELAY_ID_6;

int dd_air_pump_op_cnt = 0;

int dd_air_pump_set_state(int state)
{
    if (state == DD_AIR_PUMP_ON)
    {
        dd_air_pump_state = DD_AIR_PUMP_ON;
    }
    else
    {
        dd_air_pump_state = DD_AIR_PUMP_OFF;
    }
    return dd_air_pump_state;
}

int dd_air_pump_get_gtate()
{
    return dd_air_pump_state;
}

int dd_air_pump_off()
{
    int state = dd_air_pump_set_state(DD_AIR_PUMP_OFF);
    return state;
}

int dd_air_pump_on(int time)
{
    int state = dd_air_pump_set_state(DD_AIR_PUMP_ON);
    dd_air_pump_op_cnt = time;
    return state;
}


void dd_air_pump_setup()
{
    dd_air_pump_off();
}

void dd_air_pump_loop()
{
    if (dd_air_pump_op_cnt > -1) // if not continous
    {
        if (--dd_air_pump_op_cnt <= 0)// decrement
        {
            dd_air_pump_op_cnt = 0;
            dd_air_pump_state = DD_AIR_PUMP_OFF;//change to off
        }
    }

    if (dd_air_pump_state == DD_AIR_PUMP_ON)
    {
        ed_relay_on(dd_air_pump_relay);
    }
    else
    { // stop
        ed_relay_off(dd_air_pump_relay);
        dd_air_pump_op_cnt = 0;
        dd_air_pump_state = DD_AIR_PUMP_OFF;
    }
}
