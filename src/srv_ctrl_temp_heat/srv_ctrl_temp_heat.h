#ifndef SRV_CTRL_TEMP_HEAT_H_
#define SRV_CTRL_TEMP_HEAT_H_

#define TEMP_HEAT_HISTERESIS (0.5)
#define TEMP_HEAT_RESOLUTION (0.25)

void srv_ctrl_temp_heat_setup();
void srv_ctrl_temp_heat_loop();


#endif
