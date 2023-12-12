#ifndef CTRL_AIR_HUMIDITY_H_
#define CTRL_AIR_HUMIDITY_H_
#include "ecu_config.h"

#include "stdint.h"

#ifndef AIR_HUM_HISTERESIS
#define AIR_HUM_HISTERESIS (0.5)
#endif

#ifndef VALVE_OP_D_TIME
#define VALVE_OP_D_TIME 10
#endif

#define CTRL_AIR_HUM_DISABLE 0
#define CTRL_AIR_HUM_ENABLE 1


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

float ctrl_air_hum_get_current_hum();


#endif
