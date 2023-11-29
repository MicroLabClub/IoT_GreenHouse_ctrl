#ifndef CTRL_ISOLATION_H_
#define CTRL_ISOLATION_H_

#include "stdint.h"

#define CTRL_PRESS_ISOL_HISTERESIS (0.5)
#define CTRL_PRESS_ISOL_RESOLUTION (0.25)

void ctrl_press_isol_setup();
void ctrl_press_isol_loop();

int8_t ctrl_press_isol_set_mode(int8_t mode);
int8_t ctrl_press_isol_set_mode_manual();
int8_t ctrl_press_isol_set_mode_auto();
int8_t ctrl_press_isol_get_mode();
int8_t ctrl_press_isol_is_enabled();

float ctrl_press_isol_set_setpoint(float setpoint);
float ctrl_press_isol_get_setpoint();
float ctrl_press_isol_setpoint_up(float d_val);
float ctrl_press_isol_setpoint_dn(float d_val);
#endif
