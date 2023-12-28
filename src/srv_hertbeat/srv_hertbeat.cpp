#include "srv_hertbeat.h"
#include "ecu_config.h"
#include "Arduino.h"

static int srv_hearbeat_state = 0;

void srv_hertbeat_setup()
{
    pinMode(SRV_BLINK_LED_PIN, OUTPUT);
}

void srv_hertbeat_loop()
{
    if (srv_hearbeat_state)
    {
        srv_hearbeat_state = 0;
        digitalWrite(SRV_BLINK_LED_PIN, LOW);
    }
    else
    {
        srv_hearbeat_state = 1;
        digitalWrite(SRV_BLINK_LED_PIN, HIGH);
    }
}