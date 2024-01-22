#include "srv_sns_air_temp.h"
#include "ed_dht/ed_dht.h"
#include "../lib_cond/lib_cond.h"
#include "Arduino.h"



float srv_sns_air_temperature = 19.0;
int srv_sns_air_temperature_error = 0;
int srv_sns_air_temperature_error_sym = 0;
int srv_sns_air_temperature_error_abc = 0;
int srv_sns_air_temperature_error_abc_max = 5;
int srv_sns_air_temperature_error_abc_min = 0;
int srv_sns_air_temperature_error_abc_inc = 1;
int srv_sns_air_temperature_error_abc_dec = 5;

float srv_sns_air_get_temperature(void)
{
  return srv_sns_air_temperature;
}

int srv_sns_air_get_temperature_error(void)
{
  return srv_sns_air_temperature_error;
}

#define INPUT_BUFF_SIZE 8
float srv_sns_air_temp_buff_in[INPUT_BUFF_SIZE];

#define MEDIAN_BUFF_SIZE 5
float srv_sns_air_temp_buff_med[MEDIAN_BUFF_SIZE];

#define LPF_BUFF_SIZE 4
float srv_sns_air_temp_buff_lpf[LPF_BUFF_SIZE];
float srv_sns_air_temp_weights_lpf[LPF_BUFF_SIZE] = {50, 25, 15, 10};

void srv_sns_air_temp_setup()
{
   srv_sns_air_temperature = 19.0;
   srv_sns_air_temperature_error = 0;
   srv_sns_air_temperature_error_sym = 0;
   srv_sns_air_temperature_error_abc = 0;
   srv_sns_air_temperature_error_abc_max = 100;
   srv_sns_air_temperature_error_abc_min = 0;
   srv_sns_air_temperature_error_abc_inc = 1;
   srv_sns_air_temperature_error_abc_dec = 50;
}

float srv_sns_air_temp_cond(float temp);

void srv_sns_air_temp_loop()
{

  if (ed_dht_get_temperature_error())
  {
    // Serial.println(F("SRV SNS Error reading temperature!"));
    srv_sns_air_temperature_error_sym = 1;
  }
  else
  {
    srv_sns_air_temperature_error_sym = 0;
    float temp_raw = ed_dht_get_temperature();

    // Serial.print(F("SRV SNS Temperature: "));
    // Serial.print(temp_raw);
    // Serial.println(F("°C"));

    srv_sns_air_temperature = srv_sns_air_temp_cond(temp_raw);
  }

  // error handling
  if (srv_sns_air_temperature_error_sym)
  {
    if (srv_sns_air_temperature_error_abc < srv_sns_air_temperature_error_abc_max)
    {
      srv_sns_air_temperature_error_abc += srv_sns_air_temperature_error_abc_inc;
    }
    else
    {
      srv_sns_air_temperature_error_abc = srv_sns_air_temperature_error_abc_max;
      srv_sns_air_temperature_error = 1;
    }
  }
  else
  {
    if (srv_sns_air_temperature_error_abc > srv_sns_air_temperature_error_abc_min)
    {
      srv_sns_air_temperature_error_abc -= srv_sns_air_temperature_error_abc_dec;
    }
    else
    {
      srv_sns_air_temperature_error_abc = srv_sns_air_temperature_error_abc_min;
      srv_sns_air_temperature_error = 0;
    }
  }
}

float srv_sns_air_temp_cond(float temp_raw)
{
  // 1. FILTRU MEDIAN
  // 1.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(temp_raw, srv_sns_air_temp_buff_in, INPUT_BUFF_SIZE);
  // print_buff(temp_buff_in, INPUT_BUFF_SIZE);

  // 1.2. luam o copie din buferul de intrare
  buf_copy(srv_sns_air_temp_buff_in, srv_sns_air_temp_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

  // 1.3. sortam copia
  buf_sort(srv_sns_air_temp_buff_med, MEDIAN_BUFF_SIZE);
  // print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

  // 1.4. extragem mediana
  float temp_median = srv_sns_air_temp_buff_med[MEDIAN_BUFF_SIZE / 2];

  // // raportam valoarea mediana
  // Serial.print(F("Temperature MEDIAN: "));
  // Serial.print(temp_median);
  // Serial.println(F("°C"));

  // 2. FILTRU TRECE JOS (media ponderata)
  // 2.1. coletam fluxul de intrare in bufer FIFO
  fifo_push(temp_median, srv_sns_air_temp_buff_lpf, LPF_BUFF_SIZE);
  // print_buff(temp_buff_lpf, LPF_BUFF_SIZE);

  // 2.2 evaluam media ponderata
  float temp_flt = buf_wavg(srv_sns_air_temp_buff_lpf, srv_sns_air_temp_weights_lpf, LPF_BUFF_SIZE);

  // // raportam valoarea filtrata
  // Serial.print(F("Temperature FTJ: "));
  // Serial.print(temp_flt);
  // Serial.println(F("°C"));

  return temp_flt;
}
