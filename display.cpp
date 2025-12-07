#include <stdint.h>
#include "display.h"

Adafruit_SSD1306 display(screen_width, screen_height, &Wire, -1);

void display_setup()
{
  Serial.println("Start OLED");

  if (!display.begin(SSD1306_SWITCHCAPVCC, oled_addr)) 
  {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Stop here if display not found
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void display_stat(float temp, bool state, uint16_t airValue)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 5);
  display.print("Temperature: ");
  display.print(temp, 1);
  display.println(" C");

  display.setCursor(5, 20);
  display.print("Vent state: ");
  display.println(state ? "ON" : "OFF");

  // --- Air Quality ---
  // uint8_t airPercent = map(airValue, 0, 1023, 0, 100);
  if (airValue < 0) airValue = 0;
  if (airValue > 100) airValue = 100;

  display.setCursor(5, 35);
  display.print("Air Quality: ");
  display.print(100 - airValue); // 100 = good, 0 = bad
  display.println(" %");

  // --- Overheat warning ---
  if (temp > thresholdTemp) 
  {
    display.setCursor(5, 50);
    display.println("Overheat detected!");
  }

  display.display();
}