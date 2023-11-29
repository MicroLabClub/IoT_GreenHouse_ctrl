#ifndef SRV_SNS_AIR_TEMP_H_
#define SRV_SNS_AIR_TEMP_H_


void srv_sns_air_temp_setup();
void srv_sns_air_temp_loop();

float srv_sns_air_GetTemperature(void);
int srv_sns_air_GetTemperatureError(void);

#endif