#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "ecu_config.h"
#include "ecu_modules.h"

// put function declarations here:
void connectToWiFi();
void callback(char *topic, byte *payload, unsigned int length);
void publishMessage(int data);
void setupMQTT();
void reconnect();

void ctrl_temp_vent_mqtt_callback(char *topic, byte *payload, unsigned int length);
void ctrl_temp_heat_mqtt_callback(char *topic, byte *payload, unsigned int length);
void ctrl_air_hum_mqtt_callback(char *topic, byte *payload, unsigned int length);


void ctrl_temp_vent_mqtt_publish();
void ctrl_temp_heat_mqtt_publish();
void ctrl_air_hum_mqtt_publish();
void ctrl_soil_moist_mqtt_publish();
void ctrl_air_press_mqtt_publish();
void ctrl_lights_mqtt_publish();

#include "iot_crt.h"

// WiFi access point
#define WIFI_AP_NAME "Galaxy Fold4DBB3"
// WiFi password
#define WIFI_PASSWORD "the8time"
// #define WIFI_PASSWORD       "A3KBuSpq"

// const char *SSID = WIFI_AP_NAME;
// const char *PWD = "the8time";
const char SSID[] = "FabLab-FREE";
const char PWD[] = "";
// MQTT Broker
DynamicJsonDocument doc(1024);
DynamicJsonDocument doc_in(1024);
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);
char mqttServer[] = "9b7b323ee67e46d18f9317162c8e8841.s1.eu.hivemq.cloud";
char mqtt_username[] = "sergiu.doncila";
char mqtt_password[] = "QWEasd!@#123";
int mqttPort = 8883;
long last_time = 0;
char data[10];

void srv_com_mqtt_setup()
{
  // put your setup code here, to run once:
  delay(1000);
  connectToWiFi();
  wifiClient.setInsecure();
  setupMQTT();
}

void srv_com_mqtt_loop()
{
  // put your main code here, to run repeatedly:

  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();

#ifdef USE_CTRL_TEMP_VENT
  ctrl_temp_vent_mqtt_publish();
#endif

#ifdef USE_CTRL_TEMP_HEAT
  ctrl_temp_heat_mqtt_publish();
#endif

#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_mqtt_publish();
#endif

#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_mqtt_publish();
#endif

#ifdef USE_CTRL_AIR_PRESS
  ctrl_air_press_mqtt_publish();
#endif

#ifdef USE_CTRL_LIGHTS
  ctrl_lights_mqtt_publish();
#endif
}

void connectToWiFi()
{
  Serial.print("Connecting to ");
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected.\n");
}

void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);

  mqttClient.setCallback(callback);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println();
  Serial.println("MQTT Callback ");
  Serial.print("Topic:");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  

#ifdef USE_CTRL_TEMP_VENT
ctrl_temp_vent_mqtt_callback(topic, payload, length);
#endif
#ifdef USE_CTRL_TEMP_HEAT
ctrl_temp_heat_mqtt_callback(topic, payload, length);
#endif
#ifdef USE_CTRL_AIR_HUM
ctrl_air_hum_mqtt_callback(topic, payload, length);
#endif

#ifdef USE_CTRL_SOIL_MOIST
  if (strcmp(cmd, "set_point") == 0)
  {
    ctrl_soil_moist_set_setpoint(value_f);
  }
  else if (strcmp(cmd, "ctrl_mode") == 0)
  {
    int mode = value_f;
    if (mode == CTRL_SOIL_MOIST_DISABLE)
    {
      ctrl_soil_moist_set_mode_manual();
    }
    else if (mode == CTRL_SOIL_MOIST_ENABLE)
    {
      ctrl_soil_moist_set_mode_auto();
    }
  }
  else if (strcmp(cmd, "ctrl_out") == 0)
  {
    int out = value_f;
    if (out == CTRL_SOIL_MOIST_OUT_OFF)
    {
      dd_valve_off();
    }
    else if (out == CTRL_SOIL_MOIST_OUT_ON)
    {
      dd_valve_on(CTRL_SOIL_MOIST_OP_D_TIME);
    }
  }
#endif

  Serial.println();
}

void reconnect()
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected())
  {
    Serial.print("Actual state: ");
    Serial.println(mqttClient.state());
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Connected to MQTT broker.");
// subscribe to topic
#ifdef USE_CTRL_TEMP_VENT
      mqttClient.subscribe("microlab/agro/green_house/temp_vent_ctrl/set");
#endif
#ifdef USE_CTRL_TEMP_HEAT
      mqttClient.subscribe("microlab/agro/green_house/temp_heat_ctrl/set");
#endif
#ifdef USE_CTRL_AIR_HUM
      mqttClient.subscribe("microlab/agro/green_house/air_hum_ctrl/set");
#endif
#ifdef USE_CTRL_SOIL_MOIST
      mqttClient.subscribe("microlab/agro/green_house/soil_moist_ctrl/set");
#endif
#ifdef USE_CTRL_AIR_PRESS
      mqttClient.subscribe("microlab/agro/green_house/air_press_ctrl/set");
#endif
#ifdef USE_CTRL_LIGHTS
      mqttClient.subscribe("microlab/agro/green_house/light_ctrl/set");
#endif
    }
  }
}

void publishMessage(int data)
{
}

//==========================================================
// MQTT Callbacks
//==========================================================

//----------------------------------------------------------
// Temperature Control by Ventilation MQTT Callback
void ctrl_temp_vent_mqtt_callback(char *topic, byte *payload, unsigned int length)
{
#ifdef USE_CTRL_TEMP_VENT

  Serial.println();

  Serial.println("SRV_COM_MQTT: ctrl_temp_vent_mqtt_callback");

  deserializeJson(doc_in, (const byte *)payload, length);

  char cmd[32];
  strlcpy(cmd, doc_in["cmd"] | "default", sizeof(cmd));

  Serial.print("Command:");
  Serial.println(cmd);

  char value[32];
  strlcpy(value, doc_in["value"] | "default", sizeof(value));

  Serial.print("Value:");
  Serial.println(value);

  float value_f = atof(value);
  Serial.print("Value_f:");
  Serial.println(value_f);

  // subscribe message example
  // {
  // "cmd":"set_point",
  // "value":"17.3"
  // }

  if (strcmp(cmd, "set_point") == 0)
  {
    ctrl_temp_vent_set_setpoint(value_f);
  }
  else if (strcmp(cmd, "ctrl_mode") == 0)
  {
    int mode = value_f;
    if (mode == CTRL_TEMP_VENT_DISABLE)
    {
      ctrl_temp_vent_set_mode_manual();
    }
    else if (mode == CTRL_TEMP_VENT_ENABLE)
    {
      ctrl_temp_vent_set_mode_auto();
    }
  }
  else if (strcmp(cmd, "ctrl_out") == 0)
  {
    int out = value_f;
    if (out == CTRL_TEMP_VENT_OUT_OPEN)
    {
      dd_window_open(10);
    }
    else if (out == CTRL_TEMP_VENT_OUT_CLOSE)
    {
      dd_window_close(10);
    }
    else if (out == CTRL_TEMP_VENT_OUT_STOP)
    {
      dd_window_stop();
    }
  }
#endif
}
//----------------------------------------------------------
// Temperature Control by Heating MQTT Callback
void ctrl_temp_heat_mqtt_callback(char *topic, byte *payload, unsigned int length){
#ifdef USE_CTRL_TEMP_HEAT

  Serial.println();

  Serial.println("SRV_COM_MQTT: ctrl_temp_heat_mqtt_callback");

  deserializeJson(doc_in, (const byte *)payload, length);

  char cmd[32];
  strlcpy(cmd, doc_in["cmd"] | "default", sizeof(cmd));

  Serial.print("Command:");
  Serial.println(cmd);

  char value[32];
  strlcpy(value, doc_in["value"] | "default", sizeof(value));

  Serial.print("Value:");
  Serial.println(value);

  float value_f = atof(value);
  Serial.print("Value_f:");
  Serial.println(value_f);

  // subscribe message example
  // {
  // "cmd":"set_point",
  // "value":"17.3"
  // }

  if (strcmp(cmd, "set_point") == 0)
  {
    ctrl_temp_heat_set_setpoint(value_f);
  }
  else if (strcmp(cmd, "ctrl_mode") == 0)
  {
    int mode = value_f;
    if (mode == CTRL_TEMP_HEAT_DISABLE)
    {
      ctrl_temp_heat_set_mode_manual();
    }
    else if (mode == CTRL_TEMP_HEAT_ENABLE)
    {
      ctrl_temp_heat_set_mode_auto();
    }
  }
  else if (strcmp(cmd, "ctrl_out") == 0)
  {
    int out = value_f;
    if (out == CTRL_TEMP_HEAT_OUT_OFF)
    {
      dd_heater_off();
    }
    else if (out == CTRL_TEMP_HEAT_OUT_ON)
    {
      dd_heater_on();
    }
  }
  #endif
}

//----------------------------------------------------------
// Air Humidity Control MQTT Callback
void ctrl_air_hum_mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  #ifdef USE_CTRL_AIR_HUM

  Serial.println();

  Serial.println("SRV_COM_MQTT: ctrl_air_hum_mqtt_callback");

  deserializeJson(doc_in, (const byte *)payload, length);

  char cmd[32];
  strlcpy(cmd, doc_in["cmd"] | "default", sizeof(cmd));

  Serial.print("Command:");
  Serial.println(cmd);

  char value[32];
  strlcpy(value, doc_in["value"] | "default", sizeof(value));

  Serial.print("Value:");
  Serial.println(value);

  float value_f = atof(value);
  Serial.print("Value_f:");
  Serial.println(value_f);

  // subscribe message example
  // {
  // "cmd":"set_point",
  // "value":"17.3"
  // }


  if (strcmp(cmd, "set_point") == 0)
  {
    ctrl_air_hum_set_setpoint(value_f);
  }
  else if (strcmp(cmd, "ctrl_mode") == 0)
  {
    int mode = value_f;
    if (mode == CTRL_AIR_HUM_DISABLE)
    {
      ctrl_air_hum_set_mode_manual();
    }
    else if (mode == CTRL_AIR_HUM_ENABLE)
    {
      ctrl_air_hum_set_mode_auto();
    }
  }
  else if (strcmp(cmd, "ctrl_out") == 0)
  {
    int out = value_f;
    if (out == CTRL_AIR_HUM_OUT_OFF)
    {
      dd_valve_off();
    }
    else if (out == CTRL_AIR_HUM_OUT_ON)
    {
      dd_valve_on(CTRL_AIR_HUM_OP_D_TIME);
    }
  }
  #endif
}

//----------------------------------------------------------
// Publish Temperature Control by Ventilation Data to MQTT
void ctrl_temp_vent_mqtt_publish()
{
#ifdef USE_CTRL_TEMP_VENT
  float temp_ctrl_cur_temp = ctrl_temp_vent_get_current_temp();
  float temp_ctrl_sp = ctrl_temp_vent_get_setpoint();
  int temp_ctrl_mode = ctrl_temp_vent_get_mode();
  int temp_out = ctrl_temp_vent_get_output();
  // JSON mapping
  doc.clear();
  doc["sensor_id"] = 111;
  doc["cur_temp"] = temp_ctrl_cur_temp;
  doc["set_point"] = temp_ctrl_sp;
  doc["ctrl_mode"] = temp_ctrl_mode;
  doc["ctrl_out"] = temp_out;

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  mqttClient.publish("microlab/agro/green_house/temp_vent_ctrl", mqtt_message, true);
#endif
}
//----------------------------------------------------------
// Publish Temperature Control by Heating Data to MQTT
void ctrl_temp_heat_mqtt_publish()
{
#ifdef USE_CTRL_TEMP_HEAT
  float temp_ctrl_cur_temp = ctrl_temp_heat_get_current_temp();
  float temp_ctrl_sp = ctrl_temp_heat_get_setpoint();
  int temp_ctrl_mode = ctrl_temp_heat_get_mode();
  int temp_out = ctrl_temp_heat_get_output();
  // JSON mapping
  doc.clear();
  doc["sensor_id"] = 222;
  doc["cur_temp"] = temp_ctrl_cur_temp;
  doc["set_point"] = temp_ctrl_sp;
  doc["ctrl_mode"] = temp_ctrl_mode;
  doc["ctrl_out"] = temp_out;

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  mqttClient.publish("microlab/agro/green_house/temp_heat_ctrl", mqtt_message, true);
#endif
}
//----------------------------------------------------------
// Publish Air Humidity Control Data to MQTT
void ctrl_air_hum_mqtt_publish()
{
#ifdef USE_CTRL_AIR_HUM
  float air_hum_ctrl_cur_hum = ctrl_air_hum_get_current_hum();
  float air_hum_ctrl_sp = ctrl_air_hum_get_setpoint();
  int air_hum_ctrl_mode = ctrl_air_hum_get_mode();
  int air_hum_out = ctrl_air_hum_get_output();
  // JSON mapping
  doc.clear();
  doc["sensor_id"] = 333;
  doc["cur_hum"] = air_hum_ctrl_cur_hum;
  doc["set_point"] = air_hum_ctrl_sp;
  doc["ctrl_mode"] = air_hum_ctrl_mode;
  doc["ctrl_out"] = air_hum_out;

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  mqttClient.publish("microlab/agro/green_house/air_hum_ctrl", mqtt_message, true);
#endif
}

//----------------------------------------------------------
// Publish Soil Moisture Control Data to MQTT
void ctrl_soil_moist_mqtt_publish()
{
#ifdef USE_CTRL_SOIL_MOIST
  float soil_moist_ctrl_cur_moist = ctrl_soil_moist_get_current_moist();
  float soil_moist_ctrl_sp = ctrl_soil_moist_get_setpoint();
  int soil_moist_ctrl_mode = ctrl_soil_moist_get_mode();
  int soil_moist_out = ctrl_soil_moist_get_output();
  // JSON mapping
  doc.clear();
  doc["sensor_id"] = 444;
  doc["cur_moist"] = soil_moist_ctrl_cur_moist;
  doc["set_point"] = soil_moist_ctrl_sp;
  doc["ctrl_mode"] = soil_moist_ctrl_mode;
  doc["ctrl_out"] = soil_moist_out;

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  mqttClient.publish("microlab/agro/green_house/soil_moist_ctrl", mqtt_message, true);
#endif
}

//----------------------------------------------------------
// Publish Pressure Isolation Control Data to MQTT
void ctrl_air_press_mqtt_publish()
{
#ifdef USE_CTRL_AIR_PRESS
  float air_press_ctrl_cur_press = ctrl_air_press_get_current_press();
  float air_press_ctrl_sp = ctrl_air_press_get_setpoint();
  int air_press_ctrl_mode = ctrl_air_press_get_mode();
  int air_press_out = ctrl_air_press_get_output();
  // JSON mapping
  doc.clear();
  doc["sensor_id"] = 555;
  doc["cur_press"] = air_press_ctrl_cur_press;
  doc["set_point"] = air_press_ctrl_sp;
  doc["ctrl_mode"] = air_press_ctrl_mode;
  doc["ctrl_out"] = air_press_out;

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  mqttClient.publish("microlab/agro/green_house/air_press_ctrl", mqtt_message, true);
#endif
}

//----------------------------------------------------------
// Publish Lights Control Data to MQTT
void ctrl_lights_mqtt_publish()
{
#ifdef USE_CTRL_LIGHTS
  float light_ctrl_cur_lum = ctrl_lights_get_current_light();
  float light_ctrl_sp = ctrl_lights_get_setpoint();
  int light_ctrl_mode = ctrl_lights_get_mode();
  int light_out = ctrl_lights_get_output();
  // JSON mapping
  doc.clear();
  doc["sensor_id"] = 666;
  doc["cur_lum"] = light_ctrl_cur_lum;
  doc["set_point"] = light_ctrl_sp;
  doc["ctrl_mode"] = light_ctrl_mode;
  doc["ctrl_out"] = light_out;

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc, mqtt_message);
  mqttClient.publish("microlab/agro/green_house/light_ctrl", mqtt_message, true);
#endif
}