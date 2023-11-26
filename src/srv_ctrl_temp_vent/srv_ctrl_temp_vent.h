#ifndef SRV_CTRL_TEMP_VENT_H_
#define SRV_CTRL_TEMP_VENT_H_

#include "stdint.h"

#define TEMP_VENT_HISTERESIS (0.5)
#define TEMP_VENT_RESOLUTION (0.25)

void srv_ctrl_temp_vent_setup();
void srv_ctrl_temp_vent_loop();

int8_t srv_ctrl_temp_vent_set_mode(int8_t mode);
int8_t srv_ctrl_temp_vent_set_mode_manual();
int8_t srv_ctrl_temp_vent_set_mode_auto();
int8_t srv_ctrl_temp_vent_get_mode();
int8_t srv_ctrl_temp_vent_is_mode_auto();

float srv_ctrl_temp_vent_set_setpoint(float setpoint);
float srv_ctrl_temp_vent_get_setpoint();
float srv_ctrl_temp_vent_setpoint_up(float d_temp);
float srv_ctrl_temp_vent_setpoint_dn(float d_temp);


#endif
