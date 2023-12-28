#include "ctrl_lights.h"
#include "srv_sns_amb_light/srv_sns_amb_light.h"
#include "dd_lights/dd_lights.h"

#include "Arduino.h"

float ctrl_lights_setpoint = CTRL_LIGHTS_SP_DEFAULT;
int8_t ctrl_lights_mode = CTRL_LIGHTS_DISABLE;

float ctrl_lights_set_setpoint(float setpoint)
{
  ctrl_lights_setpoint = setpoint;
  return ctrl_lights_setpoint;
}

float ctrl_lights_get_setpoint()
{
  return ctrl_lights_setpoint;
}

float ctrl_lights_setpoint_up(float d_val)
{
  float setpoint = ctrl_lights_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_lights_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_lights_setpoint_dn(float d_val)
{
  float setpoint = ctrl_lights_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_lights_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_lights_set_mode(int8_t mode)
{
  if (mode == CTRL_LIGHTS_DISABLE)
  {
    ctrl_lights_mode = CTRL_LIGHTS_DISABLE;
  }
  else if (mode == CTRL_LIGHTS_ENABLE)
  {
    ctrl_lights_mode = CTRL_LIGHTS_ENABLE;
  }
  else
  {
    return -1;
  }
  return ctrl_lights_mode;
}
int8_t ctrl_lights_get_mode()
{
  return ctrl_lights_mode;
}
int8_t ctrl_lights_set_mode_manual()
{
  return ctrl_lights_set_mode(CTRL_LIGHTS_DISABLE);
}
int8_t ctrl_lights_set_mode_auto()
{
  return ctrl_lights_set_mode(CTRL_LIGHTS_ENABLE);
}
int8_t ctrl_lights_is_enabled()
{
  return ctrl_lights_mode == CTRL_LIGHTS_ENABLE;
}
float ctrl_lights_get_current_light()
{
  return srv_sns_amb_get_luminozity();
}


void ctrl_lights_setup()
{
  ctrl_lights_setpoint = CTRL_LIGHTS_SP_DEFAULT;
  ctrl_lights_mode = CTRL_LIGHTS_DISABLE;
}


void ctrl_lights_loop()
{

  if (ctrl_lights_mode == CTRL_LIGHTS_ENABLE)
  {
   if (srv_sns_amb_get_luminozity_error() == 0)
  {

    float lihts_current = ctrl_lights_get_current_light();
   

    int lihts_off = ctrl_lights_setpoint + LIGHTS_HISTERESIS;
    int lihts_on = ctrl_lights_setpoint - LIGHTS_HISTERESIS;

    // ON OFF Control cu Histereza
    if (lihts_current > lihts_off)
    {
      dd_lights_off();
    }
    else if (lihts_current < lihts_on)
    {
      dd_lights_on(DD_LIGHT_OP_D_TIME);
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    dd_lights_off();
  }
  }
}
