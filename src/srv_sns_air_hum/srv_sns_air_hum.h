#ifndef SRV_SNS_AIR_HUM_H_
#define SRV_SNS_AIR_HUM_H_


void srv_sns_air_hum_setup();
void srv_sns_air_hum_loop();

float srv_sns_air_get_humidity(void);
int srv_sns_air_get_humidity_error(void);


#endif