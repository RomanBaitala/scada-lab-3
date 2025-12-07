#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include <Wire.h>


#define BMP180_ADDR 0x77

constexpr float thresholdTemp = 26;

bool bmp180_begin();
float bmp180_readTemperature();

#endif
