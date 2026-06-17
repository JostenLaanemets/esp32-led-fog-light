#pragma once
#include <FastLED.h>


constexpr int LED_PIN = 2;
constexpr int LED_COUNT = 80;

void setupLEDs();
void turnOffLEDs();
void turnOnLEDs(CRGB color);
