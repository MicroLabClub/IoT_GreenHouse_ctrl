#include "dd_window_term.h"
#include "dd_window.h"
#include "Arduino.h"

void dd_window_report()
{
  // Window Report

  int window_state = dd_window_get_state();
  Serial.print("DD_WINDOW: Windoe ");
  Serial.print(window_state);
  Serial.print(" - ");

  if (window_state == DD_WINDOW_STOP)
  {
    Serial.println(" STOP");
  }
  else if (window_state == DD_WINDOW_CLOSE)
  {
    Serial.println(" CLOSE");
  }
  else if (window_state == DD_WINDOW_OPEN)
  {
    Serial.println(" OPRN");
  }
  else
  {
    Serial.println(" UNDEFINED");
  }
}



