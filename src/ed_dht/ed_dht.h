#ifndef ED_DHT_H_
#define ED_DHT_H_
#include "ecu_config.h"

// #define DHT_PIN GPIO5      // Digital pin connected to the DHT sensor 
#ifndef DHT_PIN
#define DHT_PIN 4      // Digital pin connected to the DHT sensor 
#endif

void ed_dht_setup();
void ed_dht_loop();

float ed_dht_get_temperature(void);
float ed_dht_GetHumidity(void);
int ed_dht_get_temperature_error(void);
int ed_dht_GetHumidityError(void);

#endif