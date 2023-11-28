#ifndef SRV_CTRL_AIR_HUMIDITY_H_
#define SRV_CTRL_AIR_HUMIDITY_H_

#include "stdint.h"

#define AIR_HUM_HISTERESIS (0.5)
#define AIR_HUM_RESOLUTION (0.25)

void srv_ctrl_air_hum_setup();
void srv_ctrl_air_hum_loop();

int8_t srv_ctrl_air_hum_set_mode(int8_t mode);
int8_t srv_ctrl_air_hum_set_mode_manual();
int8_t srv_ctrl_air_hum_set_mode_auto();
int8_t srv_ctrl_air_hum_get_mode();
int8_t srv_ctrl_air_hum_is_mode_auto();

float srv_ctrl_air_hum_set_setpoint(float setpoint);
float srv_ctrl_air_hum_get_setpoint();
float srv_ctrl_air_hum_setpoint_up(float d_hum);
float srv_ctrl_air_hum_setpoint_dn(float d_hum);
#endif
