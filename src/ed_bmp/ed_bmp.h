#ifndef ED_BMP_H_
#define ED_BMP_H_

#define PAS_TO_MMHG (0.75006375541921)
#define PAS_TO_BAR (0.00001)
#define SEA_LEVEL_PRESSURE (1013.25)

float ed_bmp_get_temperature(void);
float ed_bmp_get_pressure(void);
int ed_bmp_get_sensor_error(void);
void ed_bmp_setup() ;
void ed_bmp_loop() ;

#endif