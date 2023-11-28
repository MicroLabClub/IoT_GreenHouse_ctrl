#ifndef CTRL_TEMP_HEAT_H_
#define CTRL_TEMP_HEAT_H_

#define TEMP_HEAT_HISTERESIS (0.5)
#define TEMP_HEAT_RESOLUTION (0.25)

void ctrl_temp_heat_setup();
void ctrl_temp_heat_loop();


#endif
