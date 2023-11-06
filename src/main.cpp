#include <Arduino.h>

#include "srv_ui_serial/srv_ui_serial.h"
#include "lib_cond/lib_cond.h"
#include "dd_dht/dd_dht.h"
#include "dd_relay/dd_relay.h"
#include "dd_servo/dd_servo.h"
#include "dd_encoder/dd_encoder.h"
#include "srv_ctrl_temp/srv_ctrl_temp.h"

#define SYS_TICK 1

#define DD_DHT_REC 100 / SYS_TICK
int dd_dht_rec_cnt = DD_DHT_REC + 1;

#define DD_SERVO_REC 100 / SYS_TICK
int dd_servo_rec_cnt = DD_DHT_REC + 2;

#define DD_ENCODER_REC 5 / SYS_TICK
int dd_encoder_rec_cnt = DD_ENCODER_REC + 3;

#define REPORT_REC 1000 / SYS_TICK
int report_rec_cnt = REPORT_REC + 4;

#define TERMINAL_IN_REC 1 / SYS_TICK
int terminal_in_rec_cnt = TERMINAL_IN_REC + 4;

#define SRV_CTRL_TEMP_REC 500 / SYS_TICK
int srv_ctrl_tem_rec_cnt = SRV_CTRL_TEMP_REC + 5;

void setup()
{
  //  Initialize device.
  srv_ui_serial_setup();
  dd_dht_setup();
  dd_relay_setup();
  dd_servo_setup();
  dd_encoder_setup();
  srv_ctrl_temp_setup();
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Task de control al motorului Servo
  if (--dd_servo_rec_cnt <= 0)
  {
    dd_servo_loop();
    dd_servo_rec_cnt = DD_SERVO_REC;
  }

  // Task de colectare date de la sensorul DHT11
  if (--dd_dht_rec_cnt <= 0)
  {
    dd_dht_loop();
    dd_dht_rec_cnt = DD_ENCODER_REC;
  }

  // Task de colctare date de pe encoder
  if (--dd_encoder_rec_cnt <= 0)
  {
    dd_encoder_loop();
    dd_encoder_rec_cnt = DD_ENCODER_REC;
  }

  // Task de control al temperaturii ON-OFF
  if (--srv_ctrl_tem_rec_cnt <= 0)
  {
    srv_ctrl_tem_rec_cnt = SRV_CTRL_TEMP_REC;
    srv_ctrl_temp_loop();
  }

  // Task de raportare periodica a semnalelor in serial terminal
  if (--report_rec_cnt <= 0)
  {
    report_rec_cnt = REPORT_REC;
    srv_ui_serial_out_loop();
  }
  // Task pentru citirea comenzilor de la serial terminal
  if (--terminal_in_rec_cnt <= 0)
  {
    terminal_in_rec_cnt = TERMINAL_IN_REC;
    srv_ui_serial_in_loop();
  }

  // Asigurarea de pauza pt recurenta
  delay(SYS_TICK);
}
