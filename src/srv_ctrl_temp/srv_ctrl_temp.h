#ifndef SRV_CTRL_TEMP_H_
#define SRV_CTRL_TEMP_H_

#define TEMP_HISTERESIS (0.5)
#define TEMP_RESOLUTION (0.25)

void srv_ctrl_temp_setup();
void srv_ctrl_temp_loop();


#endif
