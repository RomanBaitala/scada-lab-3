#include "led.h"

const uint8_t ledIndicator = 5;

bool ledState = false; 

void changeState()
{
  if (ledState)
  {
    ledState = false;
  }
  else
  {
    ledState = true;
  }
}

void initLed()
{
  pinMode(ledIndicator, OUTPUT);
}

void blinkLed(float lastTemp, uint16_t airPer)
{
  if (lastTemp > thresholdTemp || 100 - airPer < thresholdAir)
  {
    changeState();
    digitalWrite(ledIndicator, ledState ? HIGH : LOW);
  } 
  else
  {
    ledState = false;
    digitalWrite(ledIndicator, LOW);
  } 
}