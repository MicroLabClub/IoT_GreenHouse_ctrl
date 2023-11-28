#ifndef SRV_CTRL_AIR_HUMIDITY_H_
#define SRV_CTRL_AIR_HUMIDITY_H_

#define AIR_HUM_HISTERESIS (0.5)
#define AIR_HUM_RESOLUTION (0.25)

void srv_ctrl_air_hum_setup();
void srv_ctrl_air_hum_loop();

#endif
