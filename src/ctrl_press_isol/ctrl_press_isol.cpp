#include "ctrl_press_isol.h"
#include "ed_bmp/ed_bmp.h"
#include "dd_air_pump/dd_air_pump.h"

#include "Arduino.h"

float ctrl_press_isol_setpoint = 60.0;
int8_t ctrl_press_isol_mode = CTRL_PRES_ISOL_DISABLE;

float ctrl_press_isol_set_setpoint(float setpoint)
{
  ctrl_press_isol_setpoint = setpoint;
  return ctrl_press_isol_setpoint;
}

float ctrl_press_isol_get_setpoint()
{
  return ctrl_press_isol_setpoint;
}

float ctrl_press_isol_setpoint_up(float d_val)
{
  float setpoint = ctrl_press_isol_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_press_isol_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_press_isol_setpoint_dn(float d_val)
{
  float setpoint = ctrl_press_isol_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_press_isol_set_setpoint(setpoint);
  return setpoint;
}


int8_t ctrl_press_isol_set_mode(int8_t mode)
{
  ctrl_press_isol_mode = mode;
  return ctrl_press_isol_mode;
}
int8_t ctrl_press_isol_get_mode()
{
  return ctrl_press_isol_mode;
}
int8_t ctrl_press_isol_set_mode_manual()
{
  return ctrl_press_isol_set_mode(CTRL_PRES_ISOL_DISABLE);
}
int8_t ctrl_press_isol_set_mode_auto()
{
  return ctrl_press_isol_set_mode(CTRL_PRES_ISOL_ENABLE);
}
int8_t ctrl_press_isol_is_enabled()
{
  return ctrl_press_isol_mode == CTRL_PRES_ISOL_ENABLE;
}

void ctrl_press_isol_setup()
{
  ctrl_press_isol_setpoint = 19.0;
  ctrl_press_isol_mode = CTRL_PRES_ISOL_DISABLE;
}

void ctrl_press_isol_loop()
{
  if (ctrl_press_isol_mode == CTRL_PRES_ISOL_ENABLE)
  {

    float press_current = ed_bmp_GetPressure();

    int press_off = ctrl_press_isol_setpoint + CTRL_PRESS_ISOL_HISTERESIS;
    int press_on = ctrl_press_isol_setpoint - CTRL_PRESS_ISOL_HISTERESIS;

    // ON OFF Control cu Histereza
    if (press_current > press_off)
    {
      dd_air_pump_off();
    }
    else if (press_current < press_on)
    {
      dd_air_pump_on(DD_PRES_ISOL_OP_D_TIME);
    }
    else
    {
      // do nothing
    }
  }
}
