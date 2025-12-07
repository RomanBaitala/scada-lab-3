#include "wifi_setup.h" 
#include "display.h"
#include "temperature.h"
#include "buttons.h"
#include "led.h"
#include "mqtt.h"
#include "air.h"

const float AIR_SMOOTHING = 0.1;

const uint32_t getTemperaturePause = 1000;
const uint32_t getVentStatePause = 100;
const uint32_t ledBlinkTimeout = 1000;
const uint32_t airChangeTimeout = 100;
const uint32_t mqttTimeout = 3000;

const uint32_t SOIL_WET = 400;
const uint32_t SOIL_DRY = 1023;

uint32_t lastTemperaturePause = 0;
uint32_t lastVentStatePause = 0;
uint32_t lastLedBlink = 0;
uint32_t lastAirUpdate = 0;
uint32_t lastMqtt = 0;

float lastTemp = 0;
uint16_t airVal = 0;
uint16_t airPercent = 0;

void setup() 
{
  Serial.begin(115200);

  analogReadResolution(10);

  initButtons();
  display_setup();
  initLed();
  airBegin(4, 450);
  conWifi();
  initMQTT(mqttClient, mqtt_server, mqtt_port);
  if (!bmp180_begin()) 
  {
        Serial.println("BMP180 not found!");
        while (1);
  }
}

void loop() 
{
  uint32_t currentTime = millis();
  mqttLoop(currentTime);

  if (currentTime - lastMqtt > mqttTimeout)
  {
    publishMQTT(lastTemp, airPercent, ventState);

    lastMqtt = currentTime;
  } 

  if (currentTime - lastTemperaturePause > getTemperaturePause)
  {
    lastTemp = bmp180_readTemperature();
    display_stat(lastTemp, ventState, airPercent);
    lastTemperaturePause = currentTime;
  }

  if (currentTime - lastVentStatePause > getVentStatePause)
  {
    switchWorkingState(lastTemp, airPercent);
    display_stat(lastTemp, ventState, airPercent);
    lastVentStatePause = currentTime;
  }

  if (currentTime - lastLedBlink > ledBlinkTimeout)
  {
    blinkLed(lastTemp, airPercent);
    lastLedBlink = currentTime;
  }

  if (currentTime - lastAirUpdate > airChangeTimeout)
  {
    airUpdate();
    uint16_t raw = airGetRawValue();

    // нове згладжене значення (експоненційне)
    airVal = (uint16_t)(AIR_SMOOTHING * raw + (1.0 - AIR_SMOOTHING) * airVal);
    airPercent = map(airVal, 0, 1023, 0, 100);
    lastAirUpdate = currentTime;
  }

}

