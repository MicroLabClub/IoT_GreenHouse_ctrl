#ifndef DD_DHT_H_
#define DD_DHT_H_


#define DHTPIN 7     // Digital pin connected to the DHT sensor 

void dd_dht_setup();
void dd_dht_loop();

float dd_dht_GetTemperature(void);
float dd_dht_GetHumidity(void);
int dd_dht_GetTemperatureError(void);
int dd_dht_GetHumidityError(void);

#endif