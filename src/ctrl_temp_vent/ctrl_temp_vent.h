#ifndef CTRL_TEMP_VENT_H_
#define CTRL_TEMP_VENT_H_
#include "ecu_config.h"

#include "stdint.h"

#ifndef TEMP_VENT_HISTERESIS
#define TEMP_VENT_HISTERESIS (0.5)
#endif

#ifndef DD_WIN_OP_D_TIME
#define DD_WIN_OP_D_TIME 10
#endif

#define CTRL_TEMP_VENT_DISABLE 0
#define CTRL_TEMP_VENT_ENABLE 1


void ctrl_temp_vent_setup();
void ctrl_temp_vent_loop();

int8_t ctrl_temp_vent_set_mode(int8_t mode);
int8_t ctrl_temp_vent_set_mode_manual();
int8_t ctrl_temp_vent_set_mode_auto();
int8_t ctrl_temp_vent_get_mode();
int8_t ctrl_temp_vent_is_enabled();

float ctrl_temp_vent_set_setpoint(float setpoint);
float ctrl_temp_vent_get_setpoint();
float ctrl_temp_vent_setpoint_up(float d_val);
float ctrl_temp_vent_setpoint_dn(float d_val);

float ctrl_temp_vent_get_current_temp();


#endif
