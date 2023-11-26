#include "dd_window.h"
#include "dd_relay/dd_relay.h"

#define DD_WINDOW_ACT_POS_TERM DD_RELAY_ID_1
#define DD_WINDOW_ACT_NEG_TERM DD_RELAY_ID_2

uint8_t dd_window_state = DD_WINDOW_STOP;
uint32_t dd_window_op_cnt = 0;

uint8_t dd_window_get_state()
{
    return dd_window_state;
}

void dd_window_setup()
{
    dd_window_stop();
}

void dd_window_loop()
{

    if (--dd_window_op_cnt <= 0)
    {
        dd_window_op_cnt = 0;
        dd_window_state = DD_WINDOW_STOP;
    }

    if (dd_window_state == DD_WINDOW_OPEN)
    {

        dd_relay_on(DD_WINDOW_ACT_POS_TERM);
        dd_relay_off(DD_WINDOW_ACT_NEG_TERM);
    }
    else if (dd_window_state == DD_WINDOW_CLOSE)
    {

        dd_relay_off(DD_WINDOW_ACT_POS_TERM);
        dd_relay_on(DD_WINDOW_ACT_NEG_TERM);
    }
    else
    { // stop
        dd_relay_off(DD_WINDOW_ACT_POS_TERM);
        dd_relay_off(DD_WINDOW_ACT_NEG_TERM);
        dd_window_op_cnt = 0;
        dd_window_state = DD_WINDOW_STOP;
    }
}

int8_t dd_window_stop()
{
    dd_window_state = DD_WINDOW_STOP;
    dd_window_op_cnt = 0;
}

int8_t dd_window_open(uint16_t time)
{
    dd_window_op_cnt = time;
    dd_window_state = DD_WINDOW_OPEN;
}

int8_t dd_window_close(uint16_t time)
{
    dd_window_op_cnt = time;
    dd_window_state = DD_WINDOW_CLOSE;
}