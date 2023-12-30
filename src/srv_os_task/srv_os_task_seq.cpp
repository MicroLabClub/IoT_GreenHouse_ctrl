#include "Arduino.h"
#include "srv_os_task_seq.h"
#include "ecu_modules.h"


//=============================================================================
// Task Scheduling definitions
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_VENT
int ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_OFFSET;
#endif

#ifdef USE_CTRL_SOIL_MOIST
int ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC + 1;
#endif

#ifdef USE_CTRL_TEMP_HEAT
int ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_OFFSET;
#endif

#ifdef USE_CTRL_LIGHTS
int ctrl_lights_rec_cnt = CTRL_LIGHTS_OFFSET;
#endif

#ifdef USE_CTRL_AIR_PRESS
int ctrl_air_press_rec_cnt = CTRL_AIR_PRESS_OFFSET;
#endif

#ifdef USE_CTRL_AIR_HUM
int ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_OFFSET;
#endif

#ifdef USE_SRV_UI_SERIAL
int terminal_in_rec_cnt = TERMINAL_IN_OFFSET;
#endif

#ifdef USE_SRV_UI_SERIAL
int terminal_our_rec_cnt = TERMINAL_OUT_OFFSET;
#endif

#ifdef USE_SRV_COM_MQTT
int srv_com_mqtt_rec_cnt = SRV_COM_MQTT_OFFSET;
#endif

#ifdef USE_SRV_SNS_AIR_TEMP
int srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_OFFSET;
#endif

#ifdef USE_SRV_SNS_AIR_HUM
int srv_sns_air_hum_rec_cnt = SRV_SNS_AIR_HUM_OFFSET;
#endif

#ifdef USE_ED_DHT
int ed_dht_rec_cnt = ED_DHT_OFFSET;
#endif

#ifdef USE_ED_BMP
int ed_bmp_rec_cnt = ED_BMP_OFFSET;
#endif

#ifdef USE_ed_sns_soil_moist
int ed_sns_soil_moist_rec_cnt = ed_sns_soil_moist_OFFSET;
#endif

// Actuators definitions

#ifdef USE_ED_RELAY
int ed_relay_rec_cnt = ED_RELAY_OFFSET;
#endif

#ifdef USE_DD_HEATER
int dd_heater_rec_cnt = DD_HEATER_OFFSET;
#endif

#ifdef USE_DD_LIGHTS
int dd_lights_rec_cnt = DD_LIGHTS_OFFSET;
#endif

#ifdef USE_DD_VALVE
int dd_valve_rec_cnt = DD_VALVE_OFFSET;
#endif

#ifdef USE_DD_WINDOW
int dd_window_rec_cnt = DD_WINDOW_OFFSET;
#endif

#ifdef USE_SRV_HERTBEAT
int srv_blink_rec_cnt = SRV_BLINK_OFFSET;
#endif





void srv_os_task_seq_setup()
{

#ifdef USE_SRV_HERTBEAT
  pinMode(SRV_BLINK_LED_PIN, OUTPUT); // Set GPIO22 as digital output pin
#endif

  // initialize services
#ifdef USE_SRV_UI_SERIAL
  srv_ui_serial_setup();
#endif
#ifdef USE_SRV_COM_MQTT
  srv_com_mqtt_setup();
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
  srv_sns_air_temp_setup();
#endif
#ifdef USE_SRV_SNS_AIR_HUM
  srv_sns_air_hum_setup();
#endif

  // Initialize electronic devices
#ifdef USE_ED_DHT
  ed_dht_setup();
#endif
#ifdef USE_ED_BMP
  ed_bmp_setup();
#endif
#ifdef USE_ED_RELAY
  ed_relay_setup();
#endif
#ifdef USE_ED_SNS_MOIST
  ed_sns_soil_moist_setup();
#endif

  // initialize device drivers
#ifdef USE_DD_WINDOW
  dd_window_setup();
#endif
#ifdef USE_DD_HEATER
  dd_heater_setup();
#endif
#ifdef USE_DD_LIGHTS
  dd_lights_setup();
#endif
#ifdef USE_DD_VALVE
  dd_valve_setup();
#endif

  // initialize control components
#ifdef USE_CTRL_TEMP_VENT
  ctrl_temp_vent_setup();
#endif
#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_setup();
#endif
#ifdef USE_CTRL_LIGHTS
  ctrl_lights_setup();
#endif
#ifdef USE_CTRL_AIR_PRESS
  ctrl_air_press_setup();
#endif
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_setup();
#endif
#ifdef USE_CTRL_TEMP_HEAT
  ctrl_temp_heat_setup();
#endif
}



int srv_led_blink_state = 0;


void srv_os_task_seq_scheduler()
{

#ifdef USE_SRV_HERTBEAT
  // Task Scheduler
  // Task for periodic reporting of signals in serial terminal
  if (--srv_blink_rec_cnt <= 0)
  {
    if (srv_led_blink_state)
    {
      srv_led_blink_state = 0;
      digitalWrite(SRV_BLINK_LED_PIN, LOW);
    }
    else
    {
      srv_led_blink_state = 1;
      digitalWrite(SRV_BLINK_LED_PIN, HIGH);
    }

    Serial.print("HeartBeat:");
    Serial.println(srv_led_blink_state);
    srv_blink_rec_cnt = SRV_BLINK_REC;
  }

#endif

#ifdef USE_SRV_UI_SERIAL
  // Task Scheduler
  // Task for periodic reporting of signals in serial terminal
  if (--terminal_our_rec_cnt <= 0)
  {
    srv_ui_serial_out_loop();
    terminal_our_rec_cnt = TERMINAL_OUT_REC;
  }
#endif

#ifdef USE_SRV_UI_SERIAL
  // Task for reading commands from the serial terminal
  if (--terminal_in_rec_cnt <= 0)
  {
    srv_ui_serial_in_loop();
    terminal_in_rec_cnt = TERMINAL_IN_REC;
  }
#endif

#ifdef USE_SRV_COM_MQTT
  // Task for handling MQTT communication
  if (--srv_com_mqtt_rec_cnt <= 0)
  {
    srv_com_mqtt_loop();
    srv_com_mqtt_rec_cnt = SRV_COM_MQTT_REC;
  }
#endif

#ifdef USE_ED_DHT
  // Task for collecting data from the DHT11 sensor
  if (--ed_dht_rec_cnt <= 0)
  {
    ed_dht_loop();
    ed_dht_rec_cnt = ED_DHT_REC;
  }
#endif

#ifdef USE_SRV_SNS_AIR_TEMP
  // Task for collecting data from the air temperature sensor
  if (--srv_sns_air_temp_rec_cnt <= 0)
  {
    srv_sns_air_temp_loop();
    srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_REC;
  }
#endif

#ifdef USE_SRV_SNS_AIR_HUM
  // Task for collecting data from the air humidity sensor
  if (--srv_sns_air_hum_rec_cnt <= 0)
  {
    srv_sns_air_hum_loop();
    srv_sns_air_hum_rec_cnt = SRV_SNS_AIR_HUM_REC;
  }
#endif

#ifdef USE_ED_RELAY
  // Task for managing the relay
  if (--ed_relay_rec_cnt <= 0)
  {
    ed_relay_loop();
    ed_relay_rec_cnt = ED_RELAY_REC;
  }
#endif

#ifdef USE_DD_WINDOW
  // Task for managing the windows
  if (--dd_window_rec_cnt <= 0)
  {
    dd_window_loop();
    dd_window_rec_cnt = DD_WINDOW_REC;
  }
#endif

#ifdef USE_CTRL_TEMP_VENT
  // Task for temperature control with ventilation
  if (--ctrl_temp_vent_rec_cnt <= 0)
  {
    ctrl_temp_vent_loop();
    ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_REC;
  }
#endif

#ifdef USE_ED_BMP
  // Task for collecting data from the BMP sensor
  if (--ed_bmp_rec_cnt <= 0)
  {
    ed_bmp_loop();
    ed_bmp_rec_cnt = ED_BMP_REC;
  }
#endif
#ifdef USE_ed_sns_soil_moist
  // Task for collecting data from the soil moisture sensor
  if (--ed_sns_soil_moist_rec_cnt <= 0)
  {
    ed_sns_soil_moist_loop();
    ed_sns_soil_moist_rec_cnt = ed_sns_soil_moist_REC;
  }
#endif
#ifdef USE_DD_HEATER
  // Task for managing the heater
  if (--dd_heater_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_heater_rec_cnt = DD_HEATER_REC;
  }
#endif
#ifdef USE_DD_LIGHTS
  // Task for managing the lights
  if (--dd_lights_rec_cnt <= 0)
  {
    dd_lights_loop();
    dd_lights_rec_cnt = DD_LIGHTS_REC;
  }
#endif
#ifdef USE_DD_VALVE
  // Task for managing the valve
  if (--dd_valve_rec_cnt <= 0)
  {
    dd_valve_loop();
    dd_valve_rec_cnt = DD_VALVE_REC;
  }
#endif
#ifdef USE_CTRL_SOIL_MOIST
  // Task for soil moisture control
  if (--ctrl_soil_moist_rec_cnt <= 0)
  {
    ctrl_soil_moist_loop();
    ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC;
  }
#endif
#ifdef USE_CTRL_TEMP_HEAT
  // Task for temperature control with heater
  if (--ctrl_temp_heat_rec_cnt <= 0)
  {
    ctrl_temp_heat_loop();
    ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_REC;
  }
#endif
#ifdef USE_CTRL_LIGHTS
  // Task for light control
  if (--ctrl_lights_rec_cnt <= 0)
  {
    ctrl_lights_loop();
    ctrl_lights_rec_cnt = CTRL_LIGHTS_REC;
  }
#endif
#ifdef USE_CTRL_AIR_PRESS
  // Task for pressure control with isolation
  if (--ctrl_air_press_rec_cnt <= 0)
  {
    ctrl_air_press_loop();
    ctrl_air_press_rec_cnt = CTRL_AIR_PRESS_REC;
  }
#endif
#ifdef USE_CTRL_AIR_HUM
  // Task for air humidity control
  if (--ctrl_air_hum_rec_cnt <= 0)
  {
    ctrl_air_hum_loop();
    ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_REC;
  }
#endif
}





// #define LED 21
hw_timer_t *Timer0_Cfg = NULL;
 
void IRAM_ATTR srv_os_task_seq_scheduler_isr()
{
    // digitalWrite(LED, !digitalRead(LED));
      srv_os_task_seq_scheduler();
    //   Serial.println("OS");
}
void srv_os_task_seq_setup_isr()
{
    // pinMode(LED, OUTPUT);
    Timer0_Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &srv_os_task_seq_scheduler_isr, true);
    timerAlarmWrite(Timer0_Cfg, SYS_TICK, true);
    timerAlarmEnable(Timer0_Cfg);
}

