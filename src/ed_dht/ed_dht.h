#ifndef ED_DHT_H_
#define ED_DHT_H_


#define DHTPIN GPIO5      // Digital pin connected to the DHT sensor 

void ed_dht_setup();
void ed_dht_loop();

float ed_dht_GetTemperature(void);
float ed_dht_GetHumidity(void);
int ed_dht_GetTemperatureError(void);
int ed_dht_GetHumidityError(void);

#endif