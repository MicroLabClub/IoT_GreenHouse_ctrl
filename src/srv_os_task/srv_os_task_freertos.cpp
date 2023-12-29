#include "Arduino.h"

#include "srv_os_task.h"
#include "ecu_modules.h"

// Control modules
void ctrl_temp_vent_task(void *pvParameters);
void ctrl_temp_heat_task(void *pvParameters);
void ctrl_air_hum_task(void *pvParameters);
void ctrl_soil_moist_task(void *pvParameters);
void ctrl_lights_task(void *pvParameters);
void ctrl_press_isol_task(void *pvParameters);

// Service modules
void srv_heartbeat_task(void *pvParameters);
void srv_ui_serial_out_task(void *pvParameters);
void srv_ui_serial_in_task(void *pvParameters);
void srv_com_mqtt_task(void *pvParameters);

// Sensor modules
void srv_sns_air_temp_task(void *pvParameters);
void srv_sns_air_hum_task(void *pvParameters);
void srv_sns_soil_moist_task(void *pvParameters);
void srv_sns_press_task(void *pvParameters);
void srv_sns_AMB_LIGHT_task(void *pvParameters);

// Actuator modules
void dd_window_task(void *pvParameters);
void dd_heater_task(void *pvParameters);
void dd_valve_task(void *pvParameters);
void dd_water_pump_task(void *pvParameters);
void dd_air_pump_task(void *pvParameters);
void dd_lights_task(void *pvParameters);

// ECU modules
void ed_dht_task(void *pvParameters);
void ed_sns_soil_moist_task(void *pvParameters);
void ed_bmp_task(void *pvParameters);
void ed_bh1750_task(void *pvParameters);
void ed_relay_task(void *pvParameters);

// the setup function runs once when you press reset or power the board
void srv_os_task_freertos_setup()
{

    // Set up Tasks to run independently.

    // heart beat
#ifdef USE_SRV_HERTBEAT
    xTaskCreate(
        srv_heartbeat_task, "srv_heartbeat_task" // A name just for humans
        ,
        1024 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 1 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,
        NULL);
#endif
//---------------------------------------------------------------------------------------------
// Control modules
#ifdef USE_CTRL_TEMP_VENT
    xTaskCreate(ctrl_temp_vent_task, "ctrl_temp_vent_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_CTRL_TEMP_HEAT
    xTaskCreate(ctrl_temp_heat_task, "ctrl_temp_heat_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_CTRL_AIR_HUM
    xTaskCreate(ctrl_air_hum_task, "ctrl_air_hum_task", 1024, NULL, 1, NULL);
#endif

#ifdef USE_CTRL_SOIL_MOIST
    xTaskCreate(ctrl_soil_moist_task, "ctrl_soil_moist_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_CTRL_PRESS_ISOL
    xTaskCreate(ctrl_press_isol_task, "ctrl_press_isol_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_CTRL_LIGHTS
    xTaskCreate(ctrl_lights_task, "ctrl_lights_task", 1024, NULL, 1, NULL);
#endif

//---------------------------------------------------------------------------------------------
// Service modules
#ifdef USE_SRV_UI_SERIAL
    xTaskCreate(srv_ui_serial_out_task, "srv_ui_serial_out_task", 4096, NULL, 1, NULL);
    xTaskCreate(srv_ui_serial_in_task, "srv_ui_serial_in_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_SRV_COM_MQTT
    xTaskCreate(srv_com_mqtt_task, "srv_com_mqtt_task", 4096, NULL, 1, NULL);
#endif

//---------------------------------------------------------------------------------------------
// Sensor modules
#ifdef USE_SRV_SNS_AIR_TEMP
    xTaskCreate(srv_sns_air_temp_task, "srv_sns_air_temp_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_SRV_SNS_AIR_HUM
    xTaskCreate(srv_sns_air_hum_task, "srv_sns_air_hum_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
    xTaskCreate(srv_sns_soil_moist_task, "srv_sns_soil_moist_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_SRV_SNS_PRESS
    xTaskCreate(srv_sns_press_task, "srv_sns_press_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
    xTaskCreate(srv_sns_AMB_LIGHT_task, "srv_sns_AMB_LIGHT_task", 1024, NULL, 1, NULL);
#endif
//---------------------------------------------------------------------------------------------
// Actuator modules
#ifdef USE_DD_WINDOW
    xTaskCreate(dd_window_task, "dd_window_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_DD_HEATER
    xTaskCreate(dd_heater_task, "dd_heater_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_DD_VALVE
    xTaskCreate(dd_valve_task, "dd_valve_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_DD_WATER_PUMP
    xTaskCreate(dd_water_pump_task, "dd_water_pump_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_DD_AIR_PUMP
    xTaskCreate(dd_air_pump_task, "dd_air_pump_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_DD_LIGHTS
    xTaskCreate(dd_lights_task, "dd_lights_task", 1024, NULL, 1, NULL);
#endif

//---------------------------------------------------------------------------------------------
// ECU modules
#ifdef USE_ED_DHT
    xTaskCreate(ed_dht_task, "ed_dht_task", 2024, NULL, 1, NULL);
#endif
#ifdef USE_ed_sns_soil_moist
    xTaskCreate(ed_sns_soil_moist_task, "ed_sns_soil_moist_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_ED_BMP
    xTaskCreate(ed_bmp_task, "ed_bmp_task", 1024, NULL, 1, NULL);
#endif
#ifdef USE_ED_BH1750
    xTaskCreate(ed_bh1750_task, "ed_bh1750_task", 2024, NULL, 1, NULL);
#endif

#ifdef USE_ED_RELAY
    xTaskCreate(ed_relay_task, "ed_relay_task", 1024, NULL, 1, NULL);
#endif

    // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}


//=============================================================================
// Control modules
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Task for temperature control with ventilation`
#ifdef USE_CTRL_TEMP_VENT
void ctrl_temp_vent_task(void *pvParameters)
{
    ctrl_temp_vent_setup();
    vTaskDelay(CTRL_TEMP_VENT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_temp_vent_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_TEMP_VENT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for temperature control with heater
#ifdef USE_CTRL_TEMP_HEAT
void ctrl_temp_heat_task(void *pvParameters)
{
    ctrl_temp_heat_setup();
    vTaskDelay(CTRL_TEMP_HEAT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_temp_heat_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_TEMP_HEAT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for air humidity control
#ifdef USE_CTRL_AIR_HUM
void ctrl_air_hum_task(void *pvParameters)
{
    ctrl_air_hum_setup();
    vTaskDelay(CTRL_AIR_HUM_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_air_hum_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_AIR_HUM_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
// Task for soil moisture control
void ctrl_soil_moist_task(void *pvParameters)
{
    ctrl_soil_moist_setup();
    vTaskDelay(CTRL_SOIL_MOIST_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_soil_moist_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_SOIL_MOIST_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for pressure control with isolation
#ifdef USE_CTRL_PRESS_ISOL
void ctrl_press_isol_task(void *pvParameters)
{
    ctrl_press_isol_setup();
    vTaskDelay(CTRL_PRESS_ISOL_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_press_isol_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_PRESS_ISOL_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for light control
#ifdef USE_CTRL_LIGHTS
void ctrl_lights_task(void *pvParameters)
{
    ctrl_lights_setup();
    vTaskDelay(CTRL_LIGHTS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_lights_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_LIGHTS_REC / portTICK_PERIOD_MS);
    }
}
#endif

//=============================================================================
// Service modules
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Task for periodic reporting Hertbeat
#ifdef USE_SRV_HERTBEAT
void srv_heartbeat_task(void *pvParameters) // This is a Task.
{
    srv_hertbeat_setup();
    vTaskDelay(SRV_BLINK_OFFSET / portTICK_PERIOD_MS);

    static int srv_led_blink_state_lcl = 0;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;) // A Task shall never return or exit.
    {
        srv_hertbeat_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_BLINK_REC / portTICK_PERIOD_MS); // one tick delay (15ms) in between reads for stability
    }
}

#endif


//-----------------------------------------------------------------------------
// Task for periodic reporting of signals in serial terminal
#ifdef USE_SRV_UI_SERIAL
void srv_ui_serial_out_task(void *pvParameters)
{
    srv_ui_serial_setup();
    vTaskDelay(TERMINAL_OUT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_ui_serial_out_loop();
        vTaskDelayUntil(&xLastWakeTime, TERMINAL_OUT_REC / portTICK_PERIOD_MS);
    }
}
#endif
//-----------------------------------------------------------------------------
// Task for reading commands from the serial terminal
#ifdef USE_SRV_UI_SERIAL
void srv_ui_serial_in_task(void *pvParameters)
{
    srv_ui_serial_setup();
    vTaskDelay(TERMINAL_IN_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_ui_serial_in_loop();
        vTaskDelayUntil(&xLastWakeTime, TERMINAL_IN_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for handling MQTT communication
#ifdef USE_SRV_COM_MQTT
void srv_com_mqtt_task(void *pvParameters)
{
    srv_com_mqtt_setup();
    vTaskDelay(SRV_COM_MQTT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_com_mqtt_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_COM_MQTT_REC / portTICK_PERIOD_MS);
    }
}
#endif


//-----------------------------------------------------------------------------
// Task for collecting data from the air temperature sensor
#ifdef USE_SRV_SNS_AIR_TEMP
void srv_sns_air_temp_task(void *pvParameters)
{
    srv_sns_air_temp_setup();
    vTaskDelay(SRV_SNS_AIR_TEMP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_air_temp_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AIR_TEMP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the air humidity sensor
#ifdef USE_SRV_SNS_AIR_HUM
void srv_sns_air_hum_task(void *pvParameters)
{
    srv_sns_air_hum_setup();
    vTaskDelay(SRV_SNS_AIR_HUM_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_air_hum_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AIR_HUM_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the soil moisture sensor
#ifdef USE_SRV_SNS_SOIL_MOIST
void srv_sns_soil_moist_task(void *pvParameters)
{
    srv_sns_soil_moist_setup();
    vTaskDelay(SRV_SNS_SOIL_MOIST_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_soil_moist_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_SOIL_MOIST_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the pressure sensor
#ifdef USE_SRV_SNS_PRESS
void srv_sns_press_task(void *pvParameters)
{
    srv_sns_press_setup();
    vTaskDelay(SRV_SNS_PRESS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_press_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_PRESS_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the ambient light sensor
#ifdef USE_SRV_SNS_AMB_LIGHT
void srv_sns_AMB_LIGHT_task(void *pvParameters)
{
    srv_sns_amb_light_setup();
    vTaskDelay(SRV_SNS_AMB_LIGHT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_amb_light_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AMB_LIGHT_REC / portTICK_PERIOD_MS);
    }
}
#endif


//=============================================================================
// Actuator modules
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Task for managing the windows
#ifdef USE_DD_WINDOW
void dd_window_task(void *pvParameters)
{
    dd_window_setup();
    vTaskDelay(DD_WINDOW_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_window_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_WINDOW_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the heater
#ifdef USE_DD_HEATER
void dd_heater_task(void *pvParameters)
{
    dd_heater_setup();
    vTaskDelay(DD_HEATER_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_heater_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_HEATER_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the lights
#ifdef USE_DD_LIGHTS
void dd_lights_task(void *pvParameters)
{
    dd_lights_setup();
    vTaskDelay(DD_LIGHTS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_lights_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_LIGHTS_REC / portTICK_PERIOD_MS);
    }
}
#endif
#ifdef USE_DD_VALVE
// Task for managing the valve
void dd_valve_task(void *pvParameters)
{
    dd_valve_setup();
    vTaskDelay(DD_VALVE_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_valve_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_VALVE_REC / portTICK_PERIOD_MS);
    }
}
#endif


//=============================================================================
// ECU modules
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Task for collecting data from the DHT11 sensor
#ifdef USE_ED_DHT
void ed_dht_task(void *pvParameters)
{
    ed_dht_setup();
    vTaskDelay(ED_DHT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_dht_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_DHT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the soil moisture sensor
#ifdef USE_ed_sns_soil_moist
void ed_sns_soil_moist_task(void *pvParameters)
{
    ed_sns_soil_moist_setup();
    vTaskDelay(ed_sns_soil_moist_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_sns_soil_moist_loop();
        vTaskDelayUntil(&xLastWakeTime, ed_sns_soil_moist_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the BMP sensor
#ifdef USE_ED_BMP
void ed_bmp_task(void *pvParameters)
{
    ed_bmp_setup();
    vTaskDelay(ED_BMP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_bmp_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_BMP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the BH1750 sensor
#ifdef USE_ED_BH1750
void ed_bh1750_task(void *pvParameters)
{
    ed_bh1750_setup();
    vTaskDelay(ED_BH1750_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_bh1750_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_BH1750_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the relay
#ifdef USE_ED_RELAY
void ed_relay_task(void *pvParameters)
{
    ed_relay_setup();
    vTaskDelay(ED_RELAY_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_relay_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_RELAY_REC / portTICK_PERIOD_MS);
    }
}

#endif
