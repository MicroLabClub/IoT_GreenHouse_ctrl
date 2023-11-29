#include "ctrl_soil_moisture.h"
#include "ed_sns_moist/ed_sns_moist.h"
#include "dd_valve/dd_valve.h"

#define VALVE_OP_D_TIME 10
#define CTRL_DISABLE 0
#define CTRL_ENABLE 1

float ctrl_soil_moist_setpoint = 60.0;
int8_t ctrl_soil_moist_mode = CTRL_DISABLE;

float ctrl_soil_moist_set_setpoint(float setpoint)
{
  ctrl_soil_moist_setpoint = setpoint;
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

float ctrl_soil_moist_get_setpoint()
{
  return ctrl_soil_moist_setpoint;
}

int8_t ctrl_soil_moist_set_mode(int8_t mode)
{
  ctrl_soil_moist_mode = mode;
  return ctrl_soil_moist_mode;
}
int8_t ctrl_soil_moist_set_mode_manual()
{
  ctrl_soil_moist_set_mode(CTRL_DISABLE);
}
int8_t ctrl_soil_moist_set_mode_auto()
{
  ctrl_soil_moist_set_mode(CTRL_ENABLE);
}
int8_t ctrl_soil_moist_is_enabled()
{
  return ctrl_soil_moist_mode == CTRL_ENABLE;
}
int8_t ctrl_soil_moist_get_mode()
{
  return ctrl_soil_moist_mode;
}

void ctrl_soil_moist_setup()
{
  ctrl_soil_moist_setpoint = 19.0;
  ctrl_soil_moist_mode = CTRL_DISABLE;
}

void ctrl_soil_moist_loop()
{
  if (ctrl_soil_moist_mode == CTRL_ENABLE)
  {

    float moist_current = ed_sns_moist_GetMoisture();

    int moist_off = ctrl_soil_moist_setpoint + SOIL_MOIST_HISTERESIS;
    int moist_on = ctrl_soil_moist_setpoint - SOIL_MOIST_HISTERESIS;

    // ON OFF Control cu Histereza
    if (moist_current > moist_off)
    {
      dd_valve_off();
    }
    else if (moist_current < moist_on)
    {
      dd_valve_on(VALVE_OP_D_TIME);
    }
    else
    {
      // do nothing
    }
  }
}
