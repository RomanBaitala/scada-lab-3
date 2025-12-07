#include <stdint.h>
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "temperature.h"

const uint8_t screen_width = 128;
const uint8_t screen_height = 64;
const uint8_t oled_addr = 0x3C;

void display_setup();
void display_stat(float temp, bool state, uint16_t airValue);


#endif