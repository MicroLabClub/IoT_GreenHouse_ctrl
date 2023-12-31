#ifndef ECU_CONFIG_CTRL_AIR_HUM_H_
#define ECU_CONFIG_CTRL_AIR_HUM_H_

#define USE_CTRL_AIR_HUM
// #define USE_SRV_OS_TASK_SEQ
#define USE_SRV_OS_FREERTOS
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
#define USE_DD_VALVE
#define USE_ED_RELAY

#define USE_SRV_SNS_AIR_HUM
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

#define SRV_SNS_AIR_HUM_REC (200 * TIME_uSEC)
#define SRV_SNS_AIR_HUM_OFFSET (2.8 * TIME_SEC)

#define CTRL_AIR_HUM_REC (200 * TIME_uSEC)
#define CTRL_AIR_HUM_OFFSET (3.0 * TIME_SEC)

#define DD_VALVE_REC (200 * TIME_uSEC)
#define DD_VALVE_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_uSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_AIR_HUM_OP_D_TIME (4 * TIME_SEC / DD_VALVE_REC)
#define CTRL_AIR_HUM_HISTERESIS (0.5)
#define CTRL_AIR_HUM_CUR_DEFAULT (10.0) 
#define CTRL_AIR_HUM_SP_DEFAULT (60.0)

#define DD_VALVE_OP_D_TIME (4 * TIME_SEC / DD_VALVE_REC)

#define SRV_BLINK_LED_PIN 5

#define CTRL_AIR_HUM_RELAY_ID ED_RELAY_ID_4
#define ED_RELAY_4_PIN 33


#endif