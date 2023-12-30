#include "ctrl_air_press.h"
#include "srv_sns_air_press/srv_sns_air_press.h"
#include "dd_air_pump/dd_air_pump.h"



float ctrl_air_press_setpoint = CTRL_AIR_PRESS_SP_DEFAULT;
int8_t ctrl_air_press_mode = CTRL_AIR_PRESS_DISABLE;
int8_t ctrl_air_press_output = CTRL_AIR_PRESS_OUT_OFF;


float ctrl_air_press_set_setpoint(float setpoint)
{
  ctrl_air_press_setpoint = setpoint;
  return ctrl_air_press_setpoint;
}

float ctrl_air_press_get_setpoint()
{
  return ctrl_air_press_setpoint;
}

float ctrl_air_press_setpoint_up(float d_val)
{
  float setpoint = ctrl_air_press_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_air_press_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_air_press_setpoint_dn(float d_val)
{
  float setpoint = ctrl_air_press_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_air_press_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_air_press_set_mode(int8_t mode)
{
 if(mode == CTRL_AIR_PRESS_DISABLE)
 {
   ctrl_air_press_mode = CTRL_AIR_PRESS_DISABLE;
 }
 else if(mode == CTRL_AIR_PRESS_ENABLE)
 {
   ctrl_air_press_mode = CTRL_AIR_PRESS_ENABLE;
 }
 else
 {
   return -1;
 }
  return ctrl_air_press_mode;
}
int8_t ctrl_air_press_get_mode()
{
  return ctrl_air_press_mode;
}
int8_t ctrl_air_press_set_mode_manual()
{
  return ctrl_air_press_set_mode(CTRL_AIR_PRESS_DISABLE);
}
int8_t ctrl_air_press_set_mode_auto()
{
  return ctrl_air_press_set_mode(CTRL_AIR_PRESS_ENABLE);
}
int8_t ctrl_air_press_is_enabled()
{
  return ctrl_air_press_mode == CTRL_AIR_PRESS_ENABLE;
}
float ctrl_air_press_get_current_press()
{
  return srv_sns_air_get_pressure();
}

int8_t ctrl_air_press_get_output()
{
  return ctrl_air_press_output;
}

void ctrl_air_press_setup()
{
  ctrl_air_press_setpoint = CTRL_AIR_PRESS_SP_DEFAULT;
  ctrl_air_press_mode = CTRL_AIR_PRESS_DISABLE;
  ctrl_air_press_output = CTRL_AIR_PRESS_OUT_OFF;
}

void ctrl_air_press_loop()
{
  if (ctrl_air_press_mode == CTRL_AIR_PRESS_ENABLE)
  {
    if(srv_sns_air_get_pressure_error()==0)
    {

    float press_current = srv_sns_air_get_pressure();

    int press_off = ctrl_air_press_setpoint + CTRL_AIR_PRESS_HISTERESIS;
    int press_on = ctrl_air_press_setpoint - CTRL_AIR_PRESS_HISTERESIS;

    // ON OFF Control cu Histereza
    if (press_current > press_off)
    {
      dd_air_pump_off();
    }
    else if (press_current < press_on)
    {
      dd_air_pump_on(DD_AIR_PRESS_OP_D_TIME);
    }
    else
    {
      // do nothing
    }
    }
    else
    {
      dd_air_pump_off();
    }
  }
  if(dd_air_pump_get_state() == DD_AIR_PUMP_ON)
  {
    ctrl_air_press_output = CTRL_AIR_PRESS_OUT_ON;
  }
  else
  {
    ctrl_air_press_output = CTRL_AIR_PRESS_OUT_OFF;
  }
}
