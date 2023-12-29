#ifndef SRV_SNS_SOIL_MOIST_H_
#define SRV_SNS_SOIL_MOIST_H_


void srv_sns_soil_moist_setup();
void srv_sns_soil_moist_loop();

float srv_sns_soil_get_moisture(void);
int srv_sns_soil_get_moisture_error(void);


#endif