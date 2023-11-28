
#include "dd_valve.h"
#include "Arduino.h"


int dd_valve_relay = ED_RELAY_ID_4;

int dd_valve_state = DD_VALVE_OFF;
uint32_t dd_valve_op_cnt = 0;



int dd_valve_get_gtate()
{
    return dd_valve_state;
}



void dd_valve_setup()
{
    dd_valve_off();
}

void dd_valve_loop()
{

    if (--dd_valve_op_cnt <= 0)
    {
        dd_valve_op_cnt = 0;
        dd_valve_state = DD_VALVE_OFF;
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


int dd_valve_off()
{
    dd_valve_op_cnt = 0;
    dd_valve_state = DD_VALVE_OFF;
    return dd_valve_state;

}

int dd_valve_on(uint16_t time)
{
    dd_valve_op_cnt = time;
    dd_valve_state = DD_VALVE_ON;
    return dd_valve_state;
}



