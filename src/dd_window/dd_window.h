#ifndef DD_WINDOW_H_
#define DD_WINDOW_H_

#include "stdint.h"

enum dd_windoe_state_t{
    DD_WINDOW_STOP,
    DD_WINDOW_CLOSE,
    DD_WINDOW_OPEN
};

void dd_window_setup();
void dd_window_loop();

int8_t dd_window_stop();
int8_t dd_window_open(uint16_t time);
int8_t dd_window_close(uint16_t time);


#endif