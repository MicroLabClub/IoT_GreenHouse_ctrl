#ifndef ED_SNS_MOIST_H_
#define ED_SNS_MOIST_H_

#define ED_SNS_MOIST_PIN ADC      // Analog pin connected to the sensor 

void ed_sns_moist_setup();
void ed_sns_moist_loop();

float ed_sns_moist_GetMoisture(void);

#endif