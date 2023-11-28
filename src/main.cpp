#include <Arduino.h>

#include "srv_ui_serial/srv_ui_serial.h"
#include "srv_ctrl_temp_heat/srv_ctrl_temp_heat.h"
#include "srv_ctrl_temp_vent/srv_ctrl_temp_vent.h"
#include "srv_ctrl_air_humidity/srv_ctrl_air_humidity.h"


#include "lib_cond/lib_cond.h"
#include "dd_encoder/dd_encoder.h"
#include "dd_dht/dd_dht.h"

#include "dd_heater/dd_heater.h"
#include "dd_valve/dd_valve.h"
#include "dd_window/dd_window.h"
#include "dd_relay/dd_relay.h"
// #include "dd_servo/dd_servo.h"

#define SYS_TICK 10

#define DD_DHT_REC 100 / SYS_TICK
int dd_dht_rec_cnt = DD_DHT_REC + 1;

#define REPORT_OUT_REC 1000 / SYS_TICK
int report_rec_cnt = REPORT_OUT_REC + 4;

// #define DD_SERVO_REC 100 / SYS_TICK
// int dd_servo_rec_cnt = DD_DHT_REC + 2;

#define DD_ENCODER_REC 10 / SYS_TICK
int dd_encoder_rec_cnt = DD_ENCODER_REC + 3;

#define DD_RELAY_REC 10 / SYS_TICK
int dd_relay_rec_cnt = DD_RELAY_REC + 3;

#define DD_HEATER_REC 100 / SYS_TICK
int dd_heater_rec_cnt = DD_HEATER_REC + 3;

#define DD_VALVE_REC 100 / SYS_TICK
int dd_valve_rec_cnt = DD_VALVE_REC + 3;

#define DD_WINDOW_REC 100 / SYS_TICK
int dd_window_rec_cnt = DD_WINDOW_REC + 3;

#define TERMINAL_IN_REC 10 / SYS_TICK
int terminal_in_rec_cnt = TERMINAL_IN_REC + 4;

#define SRV_CTRL_TEMP_VENT_REC 60000 / SYS_TICK
int srv_ctrl_temp_vent_rec_cnt = SRV_CTRL_TEMP_VENT_REC + 5;

#define SRV_CTRL_TEMP_HEAT_REC 10000 / SYS_TICK
int srv_ctrl_temp_heat_rec_cnt = SRV_CTRL_TEMP_HEAT_REC + 6;

#define SRV_CTRL_AIR_HUM_REC 60000 / SYS_TICK
int srv_ctrl_air_hum_rec_cnt = SRV_CTRL_AIR_HUM_REC + 6;

void os_seq_scheduler();

void setup()
{
  //  Initialize device.
  srv_ui_serial_setup();
  dd_dht_setup();
  dd_relay_setup();
  dd_heater_setup();
  dd_valve_setup();
  dd_window_setup();
  // dd_servo_setup();
  dd_encoder_setup();
  srv_ctrl_temp_heat_setup();
  srv_ctrl_temp_vent_setup();
  srv_ctrl_air_hum_setup();
}

void loop()
{
  // put your main code here, to run repeatedly:

  os_seq_scheduler();
  // Asigurarea de pauza pt recurenta
  delay(SYS_TICK);
}

void os_seq_scheduler()
{

  // // Task Scheduler
  // // Task de control al motorului Servo
  // if (--dd_servo_rec_cnt <= 0)
  // {
  //   dd_servo_loop();
  //   dd_servo_rec_cnt = DD_SERVO_REC;
  // }

  // Task de colectare date de la sensorul DHT11
  if (--dd_dht_rec_cnt <= 0)
  {
    dd_dht_loop();
    dd_dht_rec_cnt = DD_DHT_REC;
  }

  // Task de de gestionare releu
  if (--dd_relay_rec_cnt <= 0)
  {
    dd_relay_loop();
    dd_relay_rec_cnt = DD_RELAY_REC;
  }

  // Task de gestionare Heater
  if (--dd_heater_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_heater_rec_cnt = DD_HEATER_REC;
  }

  // Task de gestionare Heater
  if (--dd_valve_rec_cnt <= 0)
  {
    dd_valve_loop();
    dd_valve_rec_cnt = DD_VALVE_REC;
  }

  // Task de gestionare ferestre
  if (--dd_window_rec_cnt <= 0)
  {
    dd_window_loop();
    dd_window_rec_cnt = DD_WINDOW_REC;
  }

  // Task de colctare date de pe encoder
  if (--dd_encoder_rec_cnt <= 0)
  {
    dd_encoder_loop();
    dd_encoder_rec_cnt = DD_ENCODER_REC;
  }

  // Task de control al temperaturii ON-OFF cu Heater
  if (--srv_ctrl_temp_heat_rec_cnt <= 0)
  {
    srv_ctrl_temp_heat_loop();
    srv_ctrl_temp_heat_rec_cnt = SRV_CTRL_TEMP_HEAT_REC;
  }

  // Task de control al temperaturii OPEN-CLOSE cu Ventilare
  if (--srv_ctrl_temp_vent_rec_cnt <= 0)
  {
    srv_ctrl_temp_vent_loop();
    srv_ctrl_temp_vent_rec_cnt = SRV_CTRL_TEMP_VENT_REC;
  }

  // Task de control al temperaturii OPEN-CLOSE cu Ventilare
  if (--srv_ctrl_air_hum_rec_cnt <= 0)
  {
    srv_ctrl_air_hum_loop();
    srv_ctrl_air_hum_rec_cnt = SRV_CTRL_AIR_HUM_REC;
  }

  // Task de raportare periodica a semnalelor in serial terminal
  if (--report_rec_cnt <= 0)
  {
    srv_ui_serial_out_loop();
    report_rec_cnt = REPORT_OUT_REC;
  }

  // Task pentru citirea comenzilor de la serial terminal
  if (--terminal_in_rec_cnt <= 0)
  {
    srv_ui_serial_in_loop();
    terminal_in_rec_cnt = TERMINAL_IN_REC;
  }
}
