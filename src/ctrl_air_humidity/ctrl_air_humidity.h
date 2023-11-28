#ifndef CTRL_AIR_HUMIDITY_H_
#define CTRL_AIR_HUMIDITY_H_

#include "stdint.h"

#define AIR_HUM_HISTERESIS (0.5)
#define AIR_HUM_RESOLUTION (0.25)

void ctrl_air_hum_setup();
void ctrl_air_hum_loop();

int8_t ctrl_air_hum_set_mode(int8_t mode);
int8_t ctrl_air_hum_set_mode_manual();
int8_t ctrl_air_hum_set_mode_auto();
int8_t ctrl_air_hum_get_mode();
int8_t ctrl_air_hum_is_enabled();

float ctrl_air_hum_set_setpoint(float setpoint);
float ctrl_air_hum_get_setpoint();
float ctrl_air_hum_setpoint_up(float d_val);
float ctrl_air_hum_setpoint_dn(float d_val);
#endif
