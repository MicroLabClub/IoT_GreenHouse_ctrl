#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

#define SYS_TICK 10 // ms
#define TIME_SEC (1000 / SYS_TICK)
#define TIME_MIN (60 * TIME_SEC)
#define TIME_HOUR (60 * TIME_MIN)
#define TIME_DAY (24 * TIMTIME_HOURE_MIN)

#define ECU_ALL 0
#define ECU_CTRL_TEMP_VENT 1
#define ECU_CTRL_TEMP_HEAT 2
#define ECU_CTRL_SOIL_MOISTURE 3

#define ECU_CONFIG ECU_CTRL_TEMP_VENT

#if ECU_CONFIG == ECU_ALL

#define TX_CAN_ID_NR_OF 2
#define TX_CAN_ID_LIST                 \
    {                                  \
        CAN_ID_BUZZER, CAN_ID_JOYSTICK \
    }
#define RX_CAN_ID_NR_OF 2
#define RX_CAN_ID_LIST                 \
    {                                  \
        CAN_ID_JOYSTICK, CAN_ID_BUZZER \
    }

#elif ECU_CONFIG == ECU_CTRL_TEMP_VENT

#define USE_SRV_UI_SERIAL
#define USE_CTRL_TEMP_VENT
#define USE_DD_WINDOW
#define USE_ED_RELAY
// #define USE_SRV_SNS_AIR_TEMP
// #define USE_ED_DHT

#define ED_RELAY_REC (100 / SYS_TICK)
#define ED_RELAY_OFFSET 5

#define DD_WINDOW_REC (100 / SYS_TICK)
#define DD_WINDOW_OFFSET 14

#define TERMINAL_IN_REC (1 / SYS_TICK)
#define TERMINAL_IN_OFFSET 4

#define TERMINAL_OUT_REC (2 * TIME_SEC)
#define TERMINAL_OUT_OFFSET 5

#define CTRL_TEMP_VENT_REC (20 * TIME_SEC)
#define CTRL_TEMP_VENT_OFFSET 20

#define DD_WIN_OP_D_TIME (4 * TIME_SEC / DD_WINDOW_REC)
#define TEMP_VENT_HISTERESIS (0.5)
#define TEMP_DEFAULT (19.0)

#define ED_RELAY_1_PIN 0 //GPIO1
#define ED_RELAY_2_PIN 2 //GPIO2







#elif ECU_CONFIG == ECU_CTRL_TEMP_HEAT

#define TX_CAN_ID_NR_OF 1
#define TX_CAN_ID_LIST \
    {                  \
        CAN_ID_BUZZER  \
    }
#define RX_CAN_ID_NR_OF 1
#define RX_CAN_ID_LIST  \
    {                   \
        CAN_ID_JOYSTICK \
    }

#elif ECU_CONFIG == ECU_CTRL_SOIL_MOISTURE

#endif

#endif