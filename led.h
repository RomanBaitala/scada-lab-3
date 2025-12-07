#ifndef LED_OPP_H
#define LED_OPP_H

#include <stdint.h>
#include <Arduino.h>
#include "temperature.h"
#include "air.h"

extern bool ledState;

void initLed();
void blinkLed(float lastTemp, uint16_t airPer);

#endif