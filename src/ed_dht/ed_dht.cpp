// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Arduino.h>

#include "ed_dht.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "../lib_cond/lib_cond.h"

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE    DHT22     // DHT 22 (AM2302)
// #define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

float temperature = 0;
int temperature_error = 0;

float humidity = 0;
int humidity_error = 0;

float ed_dht_GetTemperature(void)
{
  return temperature;
}

float ed_dht_GetHumidity(void)
{
  return humidity;
}

int ed_dht_GetTemperatureError(void)
{
  return temperature_error;
}

int ed_dht_GetHumidityError(void)
{
  return humidity_error;
}

#define INPUT_BUFF_SIZE 8
float temp_buff_in[INPUT_BUFF_SIZE];
float hum_buff_in[INPUT_BUFF_SIZE];

#define MEDIAN_BUFF_SIZE 5
float temp_buff_med[MEDIAN_BUFF_SIZE];
float hum_buff_med[MEDIAN_BUFF_SIZE];

#define LPF_BUFF_SIZE 4
float temp_buff_lpf[LPF_BUFF_SIZE];
float hum_buff_lpf[LPF_BUFF_SIZE];
float temp_weights_lpf[LPF_BUFF_SIZE] = {50, 25, 15, 10};
float hum_weights_lpf[LPF_BUFF_SIZE] = {50, 25, 15, 10};

void ed_dht_setup()
{
  // Serial.begin(9600);
  //  Initialize device.
  dht.begin();
  // Serial.println(F("DHTxx Unified Sensor Example"));
  //  Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Serial.println(F("------------------------------------"));
  // Serial.println(F("Temperature Sensor"));
  // Serial.print  (F("Sensor Type: ")); //Serial.println(sensor.name);
  // Serial.print  (F("Driver Ver:  ")); //Serial.println(sensor.version);
  // Serial.print  (F("Unique ID:   ")); //Serial.println(sensor.sensor_id);
  // Serial.print  (F("Max Value:   ")); //Serial.print(sensor.max_value); //Serial.println(F("°C"));
  // Serial.print  (F("Min Value:   ")); //Serial.print(sensor.min_value); //Serial.println(F("°C"));
  // Serial.print  (F("Resolution:  ")); //Serial.print(sensor.resolution); //Serial.println(F("°C"));
  // Serial.println(F("------------------------------------"));
  //  Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  // Serial.println(F("Humidity Sensor"));
  // Serial.print  (F("Sensor Type: ")); //Serial.println(sensor.name);
  // Serial.print  (F("Driver Ver:  ")); //Serial.println(sensor.version);
  // Serial.print  (F("Unique ID:   ")); //Serial.println(sensor.sensor_id);
  // Serial.print  (F("Max Value:   ")); //Serial.print(sensor.max_value); //Serial.println(F("%"));
  // Serial.print  (F("Min Value:   ")); //Serial.print(sensor.min_value); //Serial.println(F("%"));
  // Serial.print  (F("Resolution:  ")); //Serial.print(sensor.resolution); //Serial.println(F("%"));
  // Serial.println(F("------------------------------------"));
  //  Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

float ed_dht_temp_cond(float temp);
float ed_dht_hum_cond(float temp);

void ed_dht_loop()
{
  // Delay between measurements.
  delay(delayMS);

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
    temperature_error = 1;
  }
  else
  {
    temperature_error = 0;
    float temp_raw = event.temperature;

    Serial.print(F("Temperature: "));
    Serial.print(temp_raw);
    Serial.println(F("°C"));

    temperature = ed_dht_temp_cond(temp_raw);
  }

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    // Serial.println(F("Error reading humidity!"));
    humidity_error = 1;
  }
  else
  {
    humidity_error = 0;

    float hum_raw = event.relative_humidity;
    Serial.print(F("Humidity: "));
    Serial.print(hum_raw);
    Serial.println(F("%"));

    humidity = ed_dht_temp_cond(hum_raw);
  }
}

float ed_dht_temp_cond(float temp_raw)
{
  // 1. FILTRU MEDIAN
  // 1.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(temp_raw, temp_buff_in, INPUT_BUFF_SIZE);
  // print_buff(temp_buff_in, INPUT_BUFF_SIZE);

  // 1.2. luam o copie din buferul de intrare
  buf_copy(temp_buff_in, temp_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

  // 1.3. sortam copia
  buf_sort(temp_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

  // 1.4. extragem mediana
  float temp_median = temp_buff_med[MEDIAN_BUFF_SIZE / 2];

  // // raportam valoarea mediana
  // Serial.print(F("Temperature MEDIAN: "));
  // Serial.print(temp_median);
  // Serial.println(F("°C"));

  // 2. FILTRU TRECE JOS (media ponderata)
  // 2.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(temp_median, temp_buff_lpf, LPF_BUFF_SIZE);
  // print_buff(temp_buff_lpf, LPF_BUFF_SIZE);

  // 2.2 evaluam media ponderata
  float temp_flt = buf_wavg(temp_buff_lpf, temp_weights_lpf, LPF_BUFF_SIZE);

  // // raportam valoarea filtrata
  // Serial.print(F("Temperature FTJ: "));
  // Serial.print(temp_flt);
  // Serial.println(F("°C"));

  return temp_flt;
}

float ed_dht_hum_cond(float hum_raw)
{
  // 1. FILTRU MEDIAN
  // 1.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(hum_raw, hum_buff_in, INPUT_BUFF_SIZE);
  // print_buff(hum_buff_in, INPUT_BUFF_SIZE);

  // 1.2. luam o copie din buferul de intrare
  buf_copy(hum_buff_in, hum_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(hum_buff_med, MEDIAN_BUFF_SIZE);

  // 1.3. sortam copia
  buf_sort(hum_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(hum_buff_med, MEDIAN_BUFF_SIZE);

  // 1.4. extragem mediana
  float hum_median = hum_buff_med[MEDIAN_BUFF_SIZE / 2];

  // // raportam valoarea mediana
  // Serial.print(F("Temperature MEDIAN: "));
  // Serial.print(hum_median);
  // Serial.println(F("°C"));

  // 2. FILTRU TRECE JOS (media ponderata)
  // 2.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(hum_median, hum_buff_lpf, LPF_BUFF_SIZE);
  // print_buff(hum_buff_lpf, LPF_BUFF_SIZE);

  // 2.2 evaluam media ponderata
  float hum_flt = buf_wavg(hum_buff_lpf, hum_weights_lpf, LPF_BUFF_SIZE);

  // // raportam valoarea filtrata
  // Serial.print(F("Temperature FTJ: "));
  // Serial.print(hum_flt);
  // Serial.println(F("°C"));

  return hum_flt;
}