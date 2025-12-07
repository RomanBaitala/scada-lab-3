#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

extern const char* mqtt_server;
extern const uint32_t mqtt_port;

extern WiFiClient mqttClient;

void initMQTT(Client& wifiClient, const char* broker, uint16_t port);

void reconnectMQTT();
void mqttLoop(uint32_t currentTime);

void publishMQTT(float temperature, uint8_t barValue, bool ventState);


#endif