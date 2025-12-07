#include "air.h"

static uint8_t airPin;
static int airThreshold;
static int airRawValue = 0;
static bool airState = false;

void airBegin(uint8_t analogPin, int threshold) {
    airPin = analogPin;
    airThreshold = threshold;
    pinMode(airPin, INPUT);
}

void airUpdate() {
    airRawValue = analogRead(airPin);
    airState = (airRawValue > airThreshold);
}

bool airIsOn() {
    return airState;
}

int airGetRawValue() {
    return airRawValue;
}
