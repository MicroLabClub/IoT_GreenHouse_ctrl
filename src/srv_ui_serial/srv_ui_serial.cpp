#include "srv_ui_serial.h"
#include "dd_dht/dd_dht.h"
#include "dd_relay/dd_relay.h"
// #include "dd_servo/dd_servo.h"
#include "dd_encoder/dd_encoder.h"
#include "srv_ctrl_temp/srv_ctrl_temp.h"


void srv_ui_serial_setup(){
  Serial.begin(9600);
  Serial.println("IoT System started");
}

void srv_ui_serial_in_loop(){
  if (Serial.available())
  {
    char cmd = Serial.read();

    Serial.print("IOT: Recived command: ");
    Serial.println(cmd);

    switch (cmd)
    {
    case 'q':
      dd_relay_on(DD_RELAY_ID_1);
      Serial.println(" DD_REL:  Realay Switched ON");
      break;

    case 'a':
      dd_relay_off(DD_RELAY_ID_1);
      Serial.println(" DD_REL:  Realay Switched OFF");
      break;

    case 'w':
      dd_relay_on(DD_RELAY_ID_2);
      Serial.println(" DD_REL:  Realay Switched ON");
      break;

    case 's':
      dd_relay_off(DD_RELAY_ID_2);
      Serial.println(" DD_REL:  Realay Switched OFF");
      break;

    // case 'w':
    //   dd_servo_open();
    //   Serial.println(" DD_SERVO:  Servo Open");
    //   break;

    // case 's':
    //   dd_servo_close();
    //   Serial.println(" DD_SERVO:  Close");
    //   break;

    default:
      break;
    }
  }

}

void srv_ui_serial_out_loop(){


    int enc_counter = dd_encoder_get_counter();
    Serial.print("Encoder Position: ");
    Serial.println(enc_counter);

    float temp_setpoint = (float)enc_counter * TEMP_RESOLUTION;
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

    int relay_state = dd_relay_getState(DD_RELAY_1_PIN);

    if (relay_state)
    {
      Serial.println("Relay 1 ON");
    }
    else
    {
      Serial.println("Relay 1 OFF");
    }

   relay_state = dd_relay_getState(DD_RELAY_2_PIN);

    if (relay_state)
    {
      Serial.println("Relay 2 ON");
    }
    else
    {
      Serial.println("Relay 2 OFF");
    }
    // servo report
    // int servo_current = dd_servo_get_current();
    // Serial.print("Servo: Current - ");
    // Serial.print(servo_current);

    // int servo_target = dd_servo_get_target();
    // Serial.print("  | Target - ");
    // Serial.println(servo_target);


}
