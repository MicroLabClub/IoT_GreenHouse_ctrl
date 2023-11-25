#ifndef DD_SERVO_H_
#define DD_SERVO_H_

void dd_servo_setup();
void dd_servo_loop();
int dd_servo_set_pos(int pos);
void dd_servo_open();
void dd_servo_close();

int dd_servo_get_target();
int dd_servo_get_current();

#define DD_SERVO_PIN 9

#define DD_SERVO_MAX 125
#define DD_SERVO_MIN 0
#define DD_SERVO_STEP 10


#endif


