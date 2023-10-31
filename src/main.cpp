#include <Arduino.h>

#include "dd_dht/dd_dht.h"
#include "lib_cond/lib_cond.h"
#include "dd_relay/dd_relay.h"
#include "dd_servo/dd_servo.h"

#define SYS_TICK 100

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  Initialize device.
  dd_dht_setup();
  dd_relay_setup();
  dd_servo_setup();
}

#define INPUT_BUFF_SIZE 8
float temp_buff_in[INPUT_BUFF_SIZE];
#define MEDIAN_BUFF_SIZE 5
float temp_buff_med[MEDIAN_BUFF_SIZE];

#define LPF_BUFF_SIZE 4
float temp_buff_lpf[LPF_BUFF_SIZE];

float temp_weights_lpf[LPF_BUFF_SIZE] =
    {50, 25, 15, 10};

void loop()
{
  // put your main code here, to run repeatedly:
  // dd_dht_loop();
  dd_servo_loop();

  // servo report
  int servo_current = dd_servo_get_current();
  Serial.print(" Servo current: ");
  Serial.println(servo_current);

  int servo_target = dd_servo_get_target();
  Serial.print(" Servo target: ");
  Serial.println(servo_target);

  if (dd_dht_GetTemperatureError() == 10)
  {
    float temp = dd_dht_GetTemperature();
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));

    // 1. FILTRU MEDIAN
    // 1.1. coletam fluxul de intrare in bufer FIFO
    fifo_push(temp, temp_buff_in, INPUT_BUFF_SIZE);
    print_buff(temp_buff_in, INPUT_BUFF_SIZE);

    // 1.2. luam o copie din buferul de intrare
    buf_copy(temp_buff_in, temp_buff_med, MEDIAN_BUFF_SIZE);
    print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

    // 1.3. sortam copia
    buf_sort(temp_buff_med, MEDIAN_BUFF_SIZE);
    print_buff(temp_buff_med, MEDIAN_BUFF_SIZE);

    // 1.4. extragem mediana
    float temp_median = temp_buff_med[MEDIAN_BUFF_SIZE / 2];

    // raportam valoarea mediana
    Serial.print(F("Temperature MEDIAN: "));
    Serial.print(temp_median);
    Serial.println(F("°C"));

    // 1. FILTRU TRECE JOS (media ponderata)
    // 1.1. coletam fluxul de intrare in bufer FIFO
    fifo_push(temp_median, temp_buff_lpf, LPF_BUFF_SIZE);
    print_buff(temp_buff_lpf, LPF_BUFF_SIZE);

    // 1.2 evaluam media ponderata
    float temp_flt = buf_wavg(temp_buff_lpf, temp_weights_lpf, LPF_BUFF_SIZE);

    // raportam valoarea filtrata
    Serial.print(F("Temperature FTJ: "));
    Serial.print(temp_flt);
    Serial.println(F("°C"));
  }
  else
  {
    // Serial.println(F("Error reading temperature!"));
  }

  if (Serial.available())
  {
    char cmd = Serial.read();

    Serial.print("IOT: Recived command: ");
    Serial.println(cmd);

    switch (cmd)
    {
    case 'q':
      dd_relay_on();
      Serial.println(" DD_REL:  Realay Switched ON");
      break;

    case 'a':
      dd_relay_off();
      Serial.println(" DD_REL:  Realay Switched OFF");
      break;

    case 'w':
      dd_servo_open();
      Serial.println(" DD_SERVO:  Servo Open");
      break;

    case 's':
      dd_servo_close();
      Serial.println(" DD_SERVO:  Close");
      break;

    default:  
      break;
    }
  }

  delay(SYS_TICK);
}
