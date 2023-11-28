#ifndef ED_SERVO_H_
#define ED_SERVO_H_

void ed_servo_setup();
void ed_servo_loop();
int ed_servo_set_pos(int pos);
void ed_servo_open();
void ed_servo_close();

int ed_servo_get_target();
int ed_servo_get_current();

#define ED_SERVO_PIN 9

#define ED_SERVO_MAX 125
#define ED_SERVO_MIN 0
#define ED_SERVO_STEP 10


#endif


