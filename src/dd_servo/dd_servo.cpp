#include "dd_servo.h"
#include <Servo.h>
#include "Arduino.h"

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int dd_servo_target_pos = DD_SERVO_MIN;
int dd_servo_current_pos = DD_SERVO_MIN;

int dd_servo_get_target(){
    return dd_servo_target_pos;
}
int dd_servo_get_current(){
    return dd_servo_current_pos;
}


void dd_servo_setup()
{
    myservo.attach(DD_SERVO_PIN); // attaches the servo on pin 9 to the servo object
    dd_servo_target_pos = DD_SERVO_MIN;
    dd_servo_current_pos = DD_SERVO_MIN;
}

void dd_servo_loop()
{
    if (dd_servo_current_pos > dd_servo_target_pos)
    {
        dd_servo_current_pos -= DD_SERVO_STEP;
    }
    else if (dd_servo_current_pos < dd_servo_target_pos)
    {
        dd_servo_current_pos += DD_SERVO_STEP;
    }
    else
    {
        // do nothing - on the target
    }
    dd_servo_current_pos = constrain(dd_servo_current_pos, DD_SERVO_MIN, DD_SERVO_MAX);

    myservo.write(dd_servo_current_pos); // tell servo to go to position in variable 'pos'
}

int dd_servo_set_pos(int pos)
{
    pos = constrain(pos, DD_SERVO_MIN, DD_SERVO_MAX);
    dd_servo_target_pos = pos;
    return pos;
}

void dd_servo_open()
{
    dd_servo_set_pos(DD_SERVO_MAX);
}
void dd_servo_close()
{
    dd_servo_set_pos(DD_SERVO_MIN);
}
