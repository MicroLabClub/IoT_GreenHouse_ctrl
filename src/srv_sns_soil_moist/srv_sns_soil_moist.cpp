#include "srv_sns_soil_moist.h"
#include "ed_sns_soil_moist/ed_sns_soil_moist.h"
#include "../lib_cond/lib_cond.h"
#include "Arduino.h"

float srv_sns_soil_moisture = 19.0;
int srv_sns_soil_moisture_error = 0;


float srv_sns_soil_get_moisture(void)
{
  return srv_sns_soil_moisture;
}


int srv_sns_soil_get_moisture_error(void)
{
  return srv_sns_soil_moisture_error;
}


#define INPUT_BUFF_SIZE 8
float srv_sns_soil_moist_buff_in[INPUT_BUFF_SIZE];


#define MEDIAN_BUFF_SIZE 5
float srv_sns_soil_moist_buff_med[MEDIAN_BUFF_SIZE];

#define LPF_BUFF_SIZE 4
float srv_sns_soil_moist_buff_lpf[LPF_BUFF_SIZE];
float srv_sns_soil_moist_weights_lpf[LPF_BUFF_SIZE] = {50, 25, 15, 10};

void srv_sns_soil_moist_setup()
{
  

}

float srv_sns_soil_moist_cond(float temp);

void srv_sns_soil_moist_loop()
{

  if (0)
  {
    // Serial.println(F("SRV SNS Error reading moisture!"));
    srv_sns_soil_moisture_error = 1;
  }
  else
  {
    srv_sns_soil_moisture_error = 0;
    float temp_raw = ed_sns_soil_moist_get_value();

    // Serial.print(F("SRV SNS Luminozity: "));
    // Serial.print(temp_raw);
    // Serial.println(F("°C"));

    srv_sns_soil_moisture = srv_sns_soil_moist_cond(temp_raw);
  }

}

float srv_sns_soil_moist_cond(float temp_raw)
{
  // 1. FILTRU MEDIAN
  // 1.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(temp_raw, srv_sns_soil_moist_buff_in, INPUT_BUFF_SIZE);
  // print_buff(temp_buff_in, INPUT_BUFF_SIZE);

  // 1.2. luam o copie din buferul de intrare
  buf_copy(srv_sns_soil_moist_buff_in, srv_sns_soil_moist_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

  // 1.3. sortam copia
  buf_sort(srv_sns_soil_moist_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

  // 1.4. extragem mediana
  float temp_median = srv_sns_soil_moist_buff_med[MEDIAN_BUFF_SIZE / 2];

  // // raportam valoarea mediana
  // Serial.print(F("Luminozity MEDIAN: "));
  // Serial.print(temp_median);
  // Serial.println(F("°C"));

  // 2. FILTRU TRECE JOS (media ponderata)
  // 2.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(temp_median, srv_sns_soil_moist_buff_lpf, LPF_BUFF_SIZE);
  // print_buff(temp_buff_lpf, LPF_BUFF_SIZE);

  // 2.2 evaluam media ponderata
  float temp_flt = buf_wavg(srv_sns_soil_moist_buff_lpf, srv_sns_soil_moist_weights_lpf, LPF_BUFF_SIZE);

  // // raportam valoarea filtrata
  // Serial.print(F("Luminozity FTJ: "));
  // Serial.print(temp_flt);
  // Serial.println(F("°C"));

  return temp_flt;
}
