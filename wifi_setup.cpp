#include "wifi_setup.h"

// const char* ssid = "TP-Link_0F0B";
// const char* password = "97751571";

const char* ssid = "TP-Link_0F0B";
const char* password = "97751571";

// const char* ssid = "Roman_A36";
// const char* password = "12345678";

void conWifi() 
{
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
