#include "mqtt.h"

// const char* mqtt_server = "10.254.0.97";
const char* mqtt_server = "test.mosquitto.org";
const uint32_t mqtt_port = 1883;

const char* topicHumidity = "esp32/wind_system/data";

WiFiClient mqttClient;
PubSubClient client(mqttClient);

const uint32_t reconnectDelay = 6000;
uint32_t lastReconnectAttempt = 0;

void initMQTT(Client& wifiClient, const char* broker, uint16_t port) {
  client.setClient(wifiClient);
  client.setServer(broker, port);
}

void reconnectMQTT() {
  uint32_t now = millis();
  if (client.connected()) return;

  if (now - lastReconnectAttempt > reconnectDelay) {
    Serial.print("Connecting to MQTT... ");
    if (client.connect("ESP8266Client-SiloSensor")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
    }
    lastReconnectAttempt = now;
  }
}

void mqttLoop(uint32_t currentTime) {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
}

void publishMQTT(float temperature, uint8_t barValue, bool ventState) {
  StaticJsonDocument<220> doc;
  doc["temperature"] = temperature;
  doc["status"] = ventState ? 1 : 0;
  doc["air_condition"] = 100 - barValue;
  if (100 - barValue < 40)
  {
    doc["air_alarm"] = 1;
  }
  else 
  {
    doc["air_alarm"] = 0;
  }
  if (temperature >= 26)
  {
    doc["overheat"] = 1;
  }
  else
  {
    doc["overheat"] = 0;
  }

  char buffer[256];
  size_t n = serializeJson(doc, buffer);

  // ===================== Публікація =====================
  client.publish(topicHumidity, buffer, n);
  Serial.print("Published JSON: ");
  Serial.println(buffer);
}