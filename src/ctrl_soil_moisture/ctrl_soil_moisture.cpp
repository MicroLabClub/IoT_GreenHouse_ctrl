#include "ctrl_soil_moisture.h"
#include "srv_sns_soil_moist/srv_sns_soil_moist.h"
#include "dd_valve/dd_valve.h"



float ctrl_soil_moist_setpoint = CTRL_SOIL_MOIST_SP_DEFAULT;
int8_t ctrl_soil_moist_mode = CTRL_SOIL_MOIST_DISABLE;
int8_t ctrl_soil_moist_output = CTRL_SOIL_MOIST_OUT_OFF;
float ctrl_soil_moist_set_setpoint(float setpoint)
{
  ctrl_soil_moist_setpoint = setpoint;
  return ctrl_soil_moist_setpoint;
}

float ctrl_soil_moist_get_setpoint()
{
  return ctrl_soil_moist_setpoint;
}
float ctrl_soil_moist_setpoint_up(float d_val)
{
  float setpoint = ctrl_soil_moist_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_soil_moist_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_soil_moist_setpoint_dn(float d_val)
{
  float setpoint = ctrl_soil_moist_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_soil_moist_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_soil_moist_set_mode(int8_t mode)
{
  if (mode == CTRL_SOIL_MOIST_DISABLE)
  {
    ctrl_soil_moist_mode = CTRL_SOIL_MOIST_DISABLE;
  }
  else if (mode == CTRL_SOIL_MOIST_ENABLE)
  {
    ctrl_soil_moist_mode = CTRL_SOIL_MOIST_ENABLE;
  }
  else
  {
    return -1;
  }
  return ctrl_soil_moist_mode;
}
int8_t ctrl_soil_moist_get_mode()
{
  return ctrl_soil_moist_mode;
}
int8_t ctrl_soil_moist_set_mode_manual()
{
  return ctrl_soil_moist_set_mode(CTRL_SOIL_MOIST_DISABLE);
}
int8_t ctrl_soil_moist_set_mode_auto()
{
  return ctrl_soil_moist_set_mode(CTRL_SOIL_MOIST_ENABLE);
}
int8_t ctrl_soil_moist_is_enabled()
{
  return ctrl_soil_moist_mode == CTRL_SOIL_MOIST_ENABLE;
}
float ctrl_soil_moist_get_current_moist()
{
  return srv_sns_soil_get_moisture();
}
int8_t ctrl_soil_moist_get_output()
{
  return ctrl_soil_moist_output;
}

void ctrl_soil_moist_setup()
{
  ctrl_soil_moist_setpoint = CTRL_SOIL_MOIST_SP_DEFAULT;
  ctrl_soil_moist_mode = CTRL_SOIL_MOIST_DISABLE;
}

void ctrl_soil_moist_loop()
{

  if (ctrl_soil_moist_mode == CTRL_SOIL_MOIST_ENABLE)
  {
    if (srv_sns_soil_get_moisture_error() == 0)
    {

      float moist_current = ctrl_soil_moist_get_current_moist();

      int moist_off = ctrl_soil_moist_setpoint + CTRL_SOIL_MOIST_HISTERESIS;
      int moist_on = ctrl_soil_moist_setpoint - CTRL_SOIL_MOIST_HISTERESIS;

      // ON OFF Control cu Histereza
      if (moist_current > moist_off)
      {
        dd_valve_off();
      }
      else if (moist_current < moist_on)
      {
        dd_valve_on(CTRL_SOIL_MOIST_OP_D_TIME);
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      dd_valve_off();
    }
  }
  if (dd_valve_get_state() == DD_VALVE_ON)
  {
    ctrl_soil_moist_output = CTRL_SOIL_MOIST_OUT_ON;
  }
  else
  {
    ctrl_soil_moist_output = CTRL_SOIL_MOIST_OUT_OFF;
  }
}

