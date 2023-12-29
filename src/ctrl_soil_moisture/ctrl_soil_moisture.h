#ifndef CTRL_SOIL_MOIST_H_
#define CTRL_SOIL_MOIST_H_

#include "ecu_config.h"

#include "stdint.h"

#define CTRL_SOIL_MOIST_DISABLE 0
#define CTRL_SOIL_MOIST_ENABLE 1

#ifndef CTRL_SOIL_MOIST_SP_DEFAULT
#define CTRL_SOIL_MOIST_SP_DEFAULT (60.0)
#endif

#ifndef CTRL_SOIL_MOIST_HISTERESIS
#define CTRL_SOIL_MOIST_HISTERESIS (0.5)
#endif

#ifndef CTRL_SOIL_MOIST_OP_D_TIME
#define CTRL_SOIL_MOIST_OP_D_TIME 10
#endif

#define CTRL_SOIL_MOIST_OUT_OFF 0
#define CTRL_SOIL_MOIST_OUT_ON 1


void ctrl_soil_moist_setup();
void ctrl_soil_moist_loop();

int8_t ctrl_soil_moist_set_mode(int8_t mode);
int8_t ctrl_soil_moist_set_mode_manual();
int8_t ctrl_soil_moist_set_mode_auto();
int8_t ctrl_soil_moist_get_mode();
int8_t ctrl_soil_moist_is_enabled();

float ctrl_soil_moist_get_current_moist();
float ctrl_soil_moist_set_setpoint(float setpoint);
float ctrl_soil_moist_get_setpoint();
float ctrl_soil_moist_setpoint_up(float d_val);
float ctrl_soil_moist_setpoint_dn(float d_val);
int8_t ctrl_soil_moist_get_output();

#endif
