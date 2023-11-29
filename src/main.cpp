#include <Arduino.h>

// Control Components
#include "ctrl_air_humidity/ctrl_air_humidity.h"
#include "ctrl_lights/ctrl_lights.h"
#include "ctrl_press_isol/ctrl_press_isol.h"
#include "ctrl_soil_moisture/ctrl_soil_moisture.h"
#include "ctrl_temp_heat/ctrl_temp_heat.h"
#include "ctrl_temp_vent/ctrl_temp_vent.h"

// Platform Services
#include "srv_ui_serial/srv_ui_serial.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "lib_cond/lib_cond.h"

// Devise abstraction components
#include "dd_heater/dd_heater.h"
#include "dd_lights/dd_lights.h"
#include "dd_valve/dd_valve.h"
#include "dd_window/dd_window.h"

// ECU Abstraction components
#include "ed_bmp/ed_bmp.h"
#include "ed_dht/ed_dht.h"
#include "ed_encoder/ed_encoder.h"
#include "ed_relay/ed_relay.h"
// #include "ed_servo/ed_servo.h"
#include "ed_sns_moist/ed_sns_moist.h"

#define SYS_TICK 10

#define ED_BMP_REC 100 / SYS_TICK
int ed_bmp_rec_cnt = ED_BMP_REC + 1;

#define ED_DHT_REC 100 / SYS_TICK
int ed_dht_rec_cnt = ED_DHT_REC + 1;

#define ED_SNS_MOIST_REC 100 / SYS_TICK
int ed_sns_moist_rec_cnt = ED_SNS_MOIST_REC + 1;

#define SRV_SNS_AIR_TEMP_REC 100 / SYS_TICK
int srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_REC + 2;

#define REPORT_OUT_REC 1000 / SYS_TICK
int report_rec_cnt = REPORT_OUT_REC + 4;

// #define ED_SERVO_REC 100 / SYS_TICK
// int ed_servo_rec_cnt = ED_DHT_REC + 2;

#define ED_ENCODER_REC 10 / SYS_TICK
int ed_encoder_rec_cnt = ED_ENCODER_REC + 3;

#define ED_RELAY_REC 10 / SYS_TICK
int ed_relay_rec_cnt = ED_RELAY_REC + 3;

#define DD_HEATER_REC 100 / SYS_TICK
int dd_heater_rec_cnt = DD_HEATER_REC + 3;

#define DD_LIGHTS_REC 100 / SYS_TICK
int dd_lights_rec_cnt = DD_LIGHTS_REC + 3;

#define DD_VALVE_REC 100 / SYS_TICK
int dd_valve_rec_cnt = DD_VALVE_REC + 3;

#define DD_WINDOW_REC 100 / SYS_TICK
int dd_window_rec_cnt = DD_WINDOW_REC + 3;

#define TERMINAL_IN_REC 10 / SYS_TICK
int terminal_in_rec_cnt = TERMINAL_IN_REC + 4;

#define CTRL_SOIL_MOIST_REC 60000 / SYS_TICK
int ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC + 5;

#define CTRL_TEMP_VENT_REC 60000 / SYS_TICK
int ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_REC + 5;

#define CTRL_TEMP_HEAT_REC 10000 / SYS_TICK
int ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_REC + 6;

#define CTRL_LIGHTS_REC 10000 / SYS_TICK
int ctrl_lights_rec_cnt = CTRL_LIGHTS_REC + 6;

#define CTRL_PRESS_ISOL_REC 100 / SYS_TICK
int ctrl_press_isol_rec_cnt = CTRL_PRESS_ISOL_REC + 3;

#define CTRL_AIR_HUM_REC 60000 / SYS_TICK
int ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_REC + 6;

void os_seq_scheduler();

void setup()
{
  //  Initialize device.
  ctrl_air_hum_setup();
  ctrl_lights_setup();
  ctrl_press_isol_setup();
  ctrl_soil_moist_setup();
  ctrl_temp_heat_setup();
  ctrl_temp_vent_setup();

  srv_sns_air_temp_setup();
  srv_ui_serial_setup();

  dd_heater_setup();
  dd_lights_setup();
  dd_valve_setup();
  dd_window_setup();

  ed_bmp_setup();
  ed_dht_setup();
  // ed_encoder_setup();
  ed_relay_setup();
  // ed_servo_setup();
  ed_sns_moist_setup();
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
  // if (--ed_servo_rec_cnt <= 0)
  // {
  //   ed_servo_loop();
  //   ed_servo_rec_cnt = ED_SERVO_REC;
  // }

  // Task de colectare date de la sensorul DHT11
  if (--ed_bmp_rec_cnt <= 0)
  {
    ed_bmp_loop();
    ed_bmp_rec_cnt = ED_BMP_REC;
  }

  // Task de colectare date de la sensorul DHT11
  if (--ed_dht_rec_cnt <= 0)
  {
    ed_dht_loop();
    ed_dht_rec_cnt = ED_DHT_REC;
  }

  // Task de colectare date de la sensorul de umiditate sol
  if (--ed_sns_moist_rec_cnt <= 0)
  {
    ed_sns_moist_loop();
    ed_sns_moist_rec_cnt = ED_SNS_MOIST_REC;
  }

  // Task de colectare date de la sensorul DHT11
  if (--srv_sns_air_temp_rec_cnt <= 0)
  {
    srv_sns_air_temp_loop();
    srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_REC;
  }

  // Task de de gestionare releu
  if (--ed_relay_rec_cnt <= 0)
  {
    ed_relay_loop();
    ed_relay_rec_cnt = ED_RELAY_REC;
  }

  // Task de gestionare Heater
  if (--dd_heater_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_heater_rec_cnt = DD_HEATER_REC;
  }

  // Task de gestionare Heater
  if (--dd_lights_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_lights_rec_cnt = DD_LIGHTS_REC;
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

  // // Task de colctare date de pe encoder
  // if (--ed_encoder_rec_cnt <= 0)
  // {
  //   ed_encoder_loop();
  //   ed_encoder_rec_cnt = ED_ENCODER_REC;
  // }

  // Task de control al umiditatii sol ON-OFF 
  if (--ctrl_soil_moist_rec_cnt <= 0)
  {
    ctrl_soil_moist_loop();
    ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC;
  }

  // Task de control al temperaturii ON-OFF cu Heater
  if (--ctrl_temp_heat_rec_cnt <= 0)
  {
    ctrl_temp_heat_loop();
    ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_REC;
  }

  // Task de control al temperaturii ON-OFF cu Heater
  if (--ctrl_lights_rec_cnt <= 0)
  {
    ctrl_lights_loop();
    ctrl_lights_rec_cnt = CTRL_LIGHTS_REC;
  }

  // Task de control al presiunii ON-OFF cu Izolare
  if (--ctrl_press_isol_rec_cnt <= 0)
  {
    ctrl_press_isol_loop();
    ctrl_press_isol_rec_cnt = CTRL_PRESS_ISOL_REC;
  }

  // Task de control al temperaturii OPEN-CLOSE cu Ventilare
  if (--ctrl_temp_vent_rec_cnt <= 0)
  {
    ctrl_temp_vent_loop();
    ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_REC;
  }

  // Task de control al temperaturii OPEN-CLOSE cu Ventilare
  if (--ctrl_air_hum_rec_cnt <= 0)
  {
    ctrl_air_hum_loop();
    ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_REC;
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
