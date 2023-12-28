#ifndef SRV_SNS_AMB_LIGHT_H_
#define SRV_SNS_AMB_LIGHT_H_


void srv_sns_amb_light_setup();
void srv_sns_amb_light_loop();

float srv_sns_amb_get_luminozity(void);
int srv_sns_amb_get_luminozity_error(void);


#endif