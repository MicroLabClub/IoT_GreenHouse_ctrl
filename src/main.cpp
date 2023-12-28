
#include <Arduino.h>
#include "ecu_config.h"
#include "ecu_modules.h"


#include <SPI.h>


void setup()
{
#if defined(USE_SRV_OS_TASK_SEQ)
  srv_os_task_seq_setup();
#elif defined(USE_SRV_OS_FREERTOS)
  srv_os_task_freertos_setup();
#else
#error "No OS defined"
#endif
}

// #define USE_SRV_OS_TASK_SEQ
#define USE_SRV_OS_FREERTOS

void loop()
{
  // Task Scheduler
#if defined(USE_SRV_OS_TASK_SEQ)
  srv_os_task_seq_scheduler();
#elif defined(USE_SRV_OS_FREERTOS)
  // nothing in the loop
#else
#error "No OS defined"
#endif
  // Ensuring a pause for recurrence
  delay(SYS_TICK);
}
