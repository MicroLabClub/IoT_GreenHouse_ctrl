#ifndef ECU_CONFIG_CTRL_AIR_PRESS_H_
#define ECU_CONFIG_CTRL_AIR_PRESS_H_

#define USE_CTRL_AIR_PRESS
// #define USE_SRV_OS_TASK_SEQ
#define USE_SRV_OS_FREERTOS
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
#define USE_DD_AIR_PUMP
#define USE_ED_RELAY

#define USE_SRV_SNS_AIR_PRESS
#define USE_ED_BMP

#define USE_SRV_HERTBEAT

//-------------------------------------------------------------------------
// configure task recurrence and offset for services

#define TERMINAL_IN_REC (1 * TIME_uSEC)
#define TERMINAL_IN_OFFSET 4

#define TERMINAL_OUT_REC (5.0 * TIME_SEC)
#define TERMINAL_OUT_OFFSET 5

#define SRV_COM_MQTT_REC (10.0 * TIME_SEC)
#define SRV_COM_MQTT_OFFSET (5.0 * TIME_SEC)

//-------------------------------------------------------------------------
// configure task recurrence and offset
#define ED_BMP_REC (500 * TIME_uSEC)
#define ED_BMP_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_AIR_PRESS_REC (200 * TIME_uSEC)
#define SRV_SNS_AIR_PRESS_OFFSET (2.8 * TIME_SEC)

#define CTRL_AIR_PRESS_REC (200 * TIME_uSEC)
#define CTRL_AIR_PRESS_OFFSET (3.0 * TIME_SEC)

#define DD_AIR_PUMP_REC (200 * TIME_uSEC)
#define DD_AIR_PUMP_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_uSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_AIR_PRESS_OP_D_TIME (1.0 * TIME_SEC / DD_AIR_PUMP_REC)
#define CTRL_AIR_PRESS_HISTERESIS (0.05)
#define CTRL_AIR_PRESS_CUR_DEFAULT (1.0)
#define CTRL_AIR_PRESS_SP_DEFAULT (1.0)


#define DD_AIR_PUMP_OP_D_TIME (1.0 * TIME_SEC / DD_AIR_PUMP_REC)

#define SRV_BLINK_LED_PIN 5

#define ED_RELAY_6_PIN 33


#endif