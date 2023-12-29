#ifndef CTRL_LIGHTS_H_
#define CTRL_LIGHTS_H_

#include "ecu_config.h"

#include "stdint.h"

#define CTRL_LIGHTS_DISABLE 0
#define CTRL_LIGHTS_ENABLE 1

#ifndef CTRL_LIGHTS_SP_DEFAULT
#define CTRL_LIGHTS_SP_DEFAULT (60.0)
#endif

#ifndef CTRL_LIGHTS_HISTERESIS
#define CTRL_LIGHTS_HISTERESIS (5.0)
#endif

#ifndef CTRL_LIGHTS_OP_D_TIME
#define CTRL_LIGHTS_OP_D_TIME 10
#endif

#define CTRL_LIGHTS_OUT_OFF 0
#define CTRL_LIGHTS_OUT_ON 1


void ctrl_lights_setup();
void ctrl_lights_loop();

int8_t ctrl_lights_set_mode(int8_t mode);
int8_t ctrl_lights_set_mode_manual();
int8_t ctrl_lights_set_mode_auto();
int8_t ctrl_lights_get_mode();
int8_t ctrl_lights_is_enabled();

float ctrl_lights_get_current_light();
float ctrl_lights_set_setpoint(float setpoint);
float ctrl_lights_get_setpoint();
float ctrl_lights_setpoint_up(float d_val);
float ctrl_lights_setpoint_dn(float d_val);
int8_t ctrl_lights_get_output();

#endif
