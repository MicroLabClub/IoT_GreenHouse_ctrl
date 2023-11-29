#ifndef CTRL_SOIL_MOISTIDITY_H_
#define CTRL_SOIL_MOISTIDITY_H_

#include "stdint.h"

#define SOIL_MOIST_HISTERESIS (0.5)
#define SOIL_MOIST_RESOLUTION (0.25)

void ctrl_soil_moist_setup();
void ctrl_soil_moist_loop();

int8_t ctrl_soil_moist_set_mode(int8_t mode);
int8_t ctrl_soil_moist_set_mode_manual();
int8_t ctrl_soil_moist_set_mode_auto();
int8_t ctrl_soil_moist_get_mode();
int8_t ctrl_soil_moist_is_enabled();

float ctrl_soil_moist_set_setpoint(float setpoint);
float ctrl_soil_moist_get_setpoint();
float ctrl_soil_moist_setpoint_up(float d_val);
float ctrl_soil_moist_setpoint_dn(float d_val);
#endif
