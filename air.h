#ifndef AIR_H
#define AIR_H

#include <Arduino.h>

constexpr float thresholdAir = 40;

void airBegin(uint8_t analogPin, int threshold = 400);
void airUpdate();
bool airIsOn();
int  airGetRawValue();

#endif
