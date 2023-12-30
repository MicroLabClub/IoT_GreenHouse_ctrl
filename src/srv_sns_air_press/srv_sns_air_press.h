#ifndef SRV_SNS_AIR_PRESS_H_
#define SRV_SNS_AIR_PRESS_H_


void srv_sns_air_press_setup();
void srv_sns_air_press_loop();

float srv_sns_air_get_pressure(void);
int srv_sns_air_get_pressure_error(void);


#endif