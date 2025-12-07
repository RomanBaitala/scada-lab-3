#ifndef BUTTONS_OPP_H
#define BUTTONS_OPP_H

#include <stdint.h>
#include <Arduino.h>
#include "temperature.h"
#include "air.h"

extern bool wasStartPressed;
extern bool wasStopPressed;
extern bool ventState;

void initButtons();
void switchWorkingState(float temp, float airPercent);

#endif