#include "ed_servo.h"
#include <Servo.h>
#include "Arduino.h"

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int ed_servo_target_pos = ED_SERVO_MIN;
int ed_servo_current_pos = ED_SERVO_MIN;

int ed_servo_get_target(){
    return ed_servo_target_pos;
}
int ed_servo_get_current(){
    return ed_servo_current_pos;
}


void ed_servo_setup()
{
    myservo.attach(ED_SERVO_PIN); // attaches the servo on pin 9 to the servo object
    ed_servo_target_pos = ED_SERVO_MIN;
    ed_servo_current_pos = ED_SERVO_MIN;
}

void ed_servo_loop()
{
    if (ed_servo_current_pos > ed_servo_target_pos)
    {
        ed_servo_current_pos -= ED_SERVO_STEP;
    }
    else if (ed_servo_current_pos < ed_servo_target_pos)
    {
        ed_servo_current_pos += ED_SERVO_STEP;
    }
    else
    {
        // do nothing - on the target
    }
    ed_servo_current_pos = constrain(ed_servo_current_pos, ED_SERVO_MIN, ED_SERVO_MAX);

    myservo.write(ed_servo_current_pos); // tell servo to go to position in variable 'pos'
}

int ed_servo_set_pos(int pos)
{
    pos = constrain(pos, ED_SERVO_MIN, ED_SERVO_MAX);
    ed_servo_target_pos = pos;
    return pos;
}

void ed_servo_open()
{
    ed_servo_set_pos(ED_SERVO_MAX);
}
void ed_servo_close()
{
    ed_servo_set_pos(ED_SERVO_MIN);
}
