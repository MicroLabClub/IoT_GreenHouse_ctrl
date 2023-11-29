#ifndef ED_BMP_H_
#define ED_BMP_H_

float ed_bmp_GetTemperature(void);
float ed_bmp_GetPressure(void);
int ed_bmp_GetSensorError(void);
void ed_bmp_setup() ;
void ed_bmp_loop() ;

#endif