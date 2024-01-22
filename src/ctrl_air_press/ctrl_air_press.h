#ifndef CTRL_ISOLATION_H_
#define CTRL_ISOLATION_H_

#include "ecu_config.h"

#include "stdint.h"

#define CTRL_AIR_PRESS_DISABLE 0
#define CTRL_AIR_PRESS_ENABLE 1

#ifndef CTRL_AIR_PRESS_SP_DEFAULT
#define CTRL_AIR_PRESS_SP_DEFAULT (1.0)
#endif

#ifndef CTRL_AIR_PRESS_HISTERESIS
#define CTRL_AIR_PRESS_HISTERESIS (0.001)
#endif

#ifndef CTRL_AIR_PRESS_CUR_DEFAULT
#define CTRL_AIR_PRESS_CUR_DEFAULT (1.0)
#endif

#ifndef DD_AIR_PRESS_OP_D_TIME
#define DD_AIR_PRESS_OP_D_TIME (10.0)
#endif

#define CTRL_AIR_PRESS_OUT_OFF 0
#define CTRL_AIR_PRESS_OUT_ON 1


void ctrl_air_press_setup();
void ctrl_air_press_loop();

int8_t ctrl_air_press_set_mode(int8_t mode);
int8_t ctrl_air_press_set_mode_manual();
int8_t ctrl_air_press_set_mode_auto();
int8_t ctrl_air_press_get_mode();
int8_t ctrl_air_press_is_enabled();

float ctrl_air_press_get_current_press();
float ctrl_air_press_set_setpoint(float setpoint);
float ctrl_air_press_get_setpoint();
float ctrl_air_press_setpoint_up(float d_val);
float ctrl_air_press_setpoint_dn(float d_val);
int8_t ctrl_air_press_get_output();

#endif
