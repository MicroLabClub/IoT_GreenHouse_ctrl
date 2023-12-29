#include "dd_window.h"
#include "ed_relay/ed_relay.h"

#define DD_WINDOW_ACT_POS_TERM ED_RELAY_ID_1
#define DD_WINDOW_ACT_NEG_TERM ED_RELAY_ID_2

int8_t dd_window_state = DD_WINDOW_STOP;
int32_t dd_window_op_cnt = 0;

int8_t dd_window_get_state()
{
    if (dd_window_state == DD_WINDOW_OPEN ||
        dd_window_state == DD_WINDOW_CLOSE ||
        dd_window_state == DD_WINDOW_STOP)
    {
        return dd_window_state;
    }
    else
    {
        return DD_WINDOW_UNKNOWN;
    }
}

int8_t dd_window_set_state(uint8_t state)
{
    if (state == DD_WINDOW_OPEN ||
        state == DD_WINDOW_CLOSE ||
        state == DD_WINDOW_STOP)
    {
        dd_window_state = state;
        return dd_window_state;
    }
    else
    {
        return DD_WINDOW_UNKNOWN;
    }
}


int8_t dd_window_stop()
{
    dd_window_op_cnt = 0;
    dd_window_state = DD_WINDOW_STOP;
    return dd_window_state;
}

int8_t dd_window_open(int time)
{
    dd_window_op_cnt = time;
    dd_window_state = DD_WINDOW_OPEN;
    return dd_window_state;
}

int8_t dd_window_close(int time)
{
    dd_window_op_cnt = time;
    dd_window_state = DD_WINDOW_CLOSE;
    return dd_window_state;
}


void dd_window_setup()
{
    dd_window_stop();
}

void dd_window_loop()
{
    if (dd_window_op_cnt > -1) // if not continous
    {
        if (--dd_window_op_cnt <= 0) // decrement
        {
            dd_window_op_cnt = 0;
            dd_window_state = DD_WINDOW_STOP; // change to off
        }
    }


    if (dd_window_state == DD_WINDOW_OPEN)
    {

        ed_relay_on(DD_WINDOW_ACT_POS_TERM);
        ed_relay_off(DD_WINDOW_ACT_NEG_TERM);
    }
    else if (dd_window_state == DD_WINDOW_CLOSE)
    {

        ed_relay_off(DD_WINDOW_ACT_POS_TERM);
        ed_relay_on(DD_WINDOW_ACT_NEG_TERM);
    }
    else
    { // stop
        ed_relay_off(DD_WINDOW_ACT_POS_TERM);
        ed_relay_off(DD_WINDOW_ACT_NEG_TERM);
        dd_window_op_cnt = 0;
        dd_window_state = DD_WINDOW_STOP;
    }
}
