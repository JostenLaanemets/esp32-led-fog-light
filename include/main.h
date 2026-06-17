#pragma once

#include <RotaryEncoder.h>
#include <FastLED.h>



#define LED_PIN     2
#define NUM_LEDS    80
#define BRIGHTNESS  80
#define LED_TYPE    WS2812B

#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];