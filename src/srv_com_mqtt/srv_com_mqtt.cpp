#include "srv_com_mqtt.h"


#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


// WiFi access point
#define WIFI_AP_NAME        "Galaxy Fold4DBB3"
// WiFi password
#define WIFI_PASSWORD       "the8time"

const char *SSID = WIFI_AP_NAME;
const char *PWD = WIFI_PASSWORD;

// MQTT server details
char mqttServer[] = "broker.hivemq.com";
// MQTT server port
int mqttPort = 1883;
// create a WiFiClient object to connect to the MQTT server
WiFiClient wifiClient;
// create a PubSubClient object to handle MQTT communication
PubSubClient mqttClient(wifiClient); 



int test_counter = 0;
char data[10];
long last_time = 0;
float sensorValue = 0;

void connectToWiFi();
void setupMQTT();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);


void srv_com_mqtt_setup() {
  // connect to the serial port
  Serial.begin(9600);
  // connect to the WiFi network
  connectToWiFi();
  // here a sensor, will be replaced by an adc read
  sensorValue = 0;
  // connect to the MQTT broker
  setupMQTT();
}



void srv_com_mqtt_loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
  long now = millis();
  if (now - last_time > 10000) {
    // Send data
    sensorValue = (float)((analogRead(A0) + random(0xff) + test_counter++)&0xff)/10.0;
    Serial.print(" Sensor Value Data:");
    Serial.println(sensorValue);
    // Publishing data throgh MQTT
    sprintf(data, "%.2f", sensorValue);
    // 
    Serial.print(" Sending Data:");
    Serial.println(data);
    // 
    mqttClient.publish("/swa/sensorValue", data);

    // Reset timer
    last_time = now;
  }
}


//----------------------------------------------------------
// Function to connect to WiFi
// 1. Connect to the WiFi network
//----------------------------------------------------------

void connectToWiFi() {
  Serial.print("Connectiog to ");
 
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected.");

  // print the IP address of the ESP32
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  
}

// callback function for MQTT client to handle messages from the broker
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



//----------------------------------------------------------
// Function to setup MQTT
// 1. Set the server details
// 2. Set the callback function
//----------------------------------------------------------
void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}

//----------------------------------------------------------
// Function to reconnect to MQTT
// 1. Connect to the MQTT Broker
// 2. Subscribe to the topic
//----------------------------------------------------------
void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      // connect to the MQTT broker with the client ID  
      String clientId = "ESP32Client-";
      // Append a random number to the client ID, to make it unique
      clientId += String(random(0xffff), HEX);

      Serial.println(clientId);

      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("/swa/commands");
      }
      
  }
}
