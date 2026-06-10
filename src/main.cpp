#include <Arduino.h>
#include "ledcounter.h"

void setup() {
  Serial.begin(115200);
  LedCounterSetup();
}

void loop() {
  // Turns on led based on the amount of turns on the rotary encoder, and resets leds and counter when button is pressed
  ReadButton();
  ReadEncoder();
  UpdateLeds();
}