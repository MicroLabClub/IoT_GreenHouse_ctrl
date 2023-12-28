#ifndef CTRL_ISOLATION_H_
#define CTRL_ISOLATION_H_
#include "ecu_config.h"

#include "stdint.h"

#ifndef CTRL_PRESS_ISOL_HISTERESIS
#define CTRL_PRESS_ISOL_HISTERESIS (0.5)
#endif

#ifndef DD_PRES_ISOL_OP_D_TIME
#define DD_PRES_ISOL_OP_D_TIME 10
#endif

#define CTRL_PRES_ISOL_DISABLE 0
#define CTRL_PRES_ISOL_ENABLE 1

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

float ctrl_pres_isol_get_current_pres();


#endif
