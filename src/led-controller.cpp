#include "arduino.h"
#include "config.h"
#include "led-controller.h"
#include <FastLED.h>


CRGB leds[LED_COUNT];

void setupLEDs() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(80);
    turnOffLEDs();
}

void turnOffLEDs() {
    FastLED.clear();
    FastLED.show();
}


void turnOnLEDs(CRGB color) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
  FastLED.show();
}