#include "buttons.h"


const uint8_t buttonStart = 37;
const uint8_t buttonStop = 38;

bool ventState = false;
bool wasStartPressed = false;
bool wasStopPressed = false;

void initButtons()
{
  pinMode(buttonStart, INPUT);
  pinMode(buttonStop, INPUT);
}

void switchWorkingState(float temp, float airPercent)
{
  if (temp < thresholdTemp || (temp < thresholdTemp && 100 - airPercent < thresholdAir))
  {
    if (digitalRead(buttonStart) == LOW && !wasStartPressed)
    {
      wasStartPressed = true;
      ventState = true;
    }
    else if (digitalRead(buttonStart) == HIGH)
    {
      wasStartPressed = false;
    }
  }
  else if (temp > thresholdTemp) 
  {
    
    if (digitalRead(buttonStop) == LOW && !wasStopPressed) 
    {
      wasStopPressed = true;
      ventState = false;
    }
    else if (digitalRead(buttonStop) == HIGH) 
    {
      wasStopPressed = false;
    }
  }
}

