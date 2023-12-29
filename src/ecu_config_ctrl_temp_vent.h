#ifndef ECU_CONFIG_CTRL_TEMP_VENT_H_
#define ECU_CONFIG_CTRL_TEMP_VENT_H_

#define USE_CTRL_TEMP_VENT
// #define USE_SRV_OS_TASK_SEQ
#define USE_SRV_OS_FREERTOS
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
#define USE_DD_WINDOW
#define USE_ED_RELAY

#define USE_SRV_SNS_AIR_TEMP
#define USE_ED_DHT

#define USE_SRV_HERTBEAT

//-------------------------------------------------------------------------
// configure task recurrence and offset for services
#define TERMINAL_IN_REC (1 * TIME_uSEC)
#define TERMINAL_IN_OFFSET (4 * TIME_uSEC)

#define TERMINAL_OUT_REC (5.0 * TIME_SEC)
#define TERMINAL_OUT_OFFSET (0.1 * TIME_SEC)

#define SRV_COM_MQTT_REC (10.0 * TIME_SEC)
#define SRV_COM_MQTT_OFFSET (5.0 * TIME_SEC)

//-------------------------------------------------------------------------
// configure task recurrence and offset
#define ED_DHT_REC (500 * TIME_uSEC)
#define ED_DHT_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_AIR_TEMP_REC (200 * TIME_uSEC)
#define SRV_SNS_AIR_TEMP_OFFSET (2.8 * TIME_SEC)

#define CTRL_TEMP_VENT_REC (200 * TIME_uSEC)
#define CTRL_TEMP_VENT_OFFSET (3.0 * TIME_SEC)

#define DD_WINDOW_REC (200 * TIME_uSEC)
#define DD_WINDOW_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_uSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------#define DD_WIN_OP_D_TIME (1.0 * TIME_SEC / DD_WINDOW_REC)


#define CTRL_TEMP_VENT_OP_D_TIME (3 * TIME_SEC / DD_WINDOW_REC)
#define CTRL_TEMP_VENT_HISTERESIS (0.5)
#define CTRL_TEMP_VENT_CUR_DEFAULT (10.0) 
#define CTRL_TEMP_VENT_SP_DEFAULT (19.0)

#define DHT_PIN 4 // Digital pin connected to the DHT sensor
#define SRV_BLINK_LED_PIN 5

#define DD_WIN_OP_D_TIME (4 * TIME_SEC / DD_WINDOW_REC)

#define ED_RELAY_1_PIN 32
#define ED_RELAY_2_PIN 33

#endif