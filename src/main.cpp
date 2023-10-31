#include <Arduino.h>

#include "dd_dht/dd_dht.h"
#include "lib_cond/lib_cond.h"
#include "dd_relay/dd_relay.h"
#include "dd_servo/dd_servo.h"
#include "dd_encoder/dd_encoder.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("IoT System started");
  //  Initialize device.
  // dd_dht_setup();
  // dd_relay_setup();
  // dd_servo_setup();
  dd_encoder_setup();
}

#define SYS_TICK 1

#define DD_DHT_REC 100 / SYS_TICK
int dd_dht_rec_cnt = DD_DHT_REC+1;

#define DD_SERVO_REC 100 / SYS_TICK
int dd_servo_rec_cnt = DD_DHT_REC+2;

#define DD_ENCODER_REC 5 / SYS_TICK
int dd_encoder_rec_cnt = DD_ENCODER_REC+3;

#define REPORT_REC 1000 / SYS_TICK
int report_rec_cnt = REPORT_REC+4;

#define SRV_CTRL_TEMP_REC 500 / SYS_TICK
int srv_ctrl_tem_rec_cnt = SRV_CTRL_TEMP_REC+5;

void loop()
{
  // put your main code here, to run repeatedly:
  // dd_servo_loop();
  if (--dd_servo_rec_cnt <= 0)
  {
    dd_servo_loop();
    dd_servo_rec_cnt = DD_SERVO_REC;
  }

  if (--dd_dht_rec_cnt <= 0)
  {
    dd_dht_loop();
    dd_dht_rec_cnt = DD_ENCODER_REC;
  }

  if (--dd_encoder_rec_cnt <= 0)
  { // pentru setpoint
    dd_encoder_loop();
    dd_encoder_rec_cnt = DD_ENCODER_REC;
  }

  if (--srv_ctrl_tem_rec_cnt <= 0)
  { // pentru setpoint
    srv_ctrl_tem_rec_cnt = SRV_CTRL_TEMP_REC;

#define TEMP_HISTERESIS (0.5)

    if (dd_dht_GetTemperatureError() == 0)
    {

      float temp_current = dd_dht_GetTemperature();
      int enc_counter = dd_encoder_get_counter();
      float temp_setpoint = (float)enc_counter * 0.25;

      int temp_off = temp_setpoint + TEMP_HISTERESIS;
      int temp_on = temp_setpoint - TEMP_HISTERESIS;

      // ON OFF Control cu Histereza

      if (temp_current > temp_off)
      {
        // relay off
        dd_relay_off();
      }
      else if (temp_current < temp_on)
      {
        // relay on
        dd_relay_on();
        Serial.println("relay OFF");
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      dd_relay_off();
    }
  }

  if (--report_rec_cnt <= 0)
  {
    report_rec_cnt = REPORT_REC;

    int enc_counter = dd_encoder_get_counter();
    Serial.print("Position: ");
    Serial.println(enc_counter);

    float temp_setpoint = (float)enc_counter * 0.25;
    Serial.print(F("SetPoint T emperature: "));
    Serial.print(temp_setpoint);
    Serial.println(F("°C"));

    if (dd_dht_GetTemperatureError() == 0)
    {
      float temp = dd_dht_GetTemperature();
      Serial.print(F("Temperature: "));
      Serial.print(temp);
      Serial.println(F("°C"));
    }

    int relay_state = dd_relay_getState();

    if (relay_state)
    {
      Serial.println("relay ON");
    }
    else
    {
      Serial.println("relay OFF");
    }
    // servo report
    int servo_current = dd_servo_get_current();
    Serial.print("Servo: Current: ");
    Serial.print(servo_current);

    int servo_target = dd_servo_get_target();
    Serial.print("  | Target: ");
    Serial.println(servo_target);

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
