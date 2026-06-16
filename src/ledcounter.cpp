#include <Arduino.h>
#include <RotaryEncoder.h>
#include <FastLED.h>
#include "ledcounter.h"

#define CLK_PIN 18
#define DT_PIN  19
#define SW_PIN  21

// Libary for deboncing, using a cheap noisy rotary encoder
RotaryEncoder encoder(CLK_PIN, DT_PIN, RotaryEncoder::LatchMode::FOUR3);

int lastPos = 0;

#define LED_PIN     2
#define NUM_LEDS    80
#define BRIGHTNESS  80
#define LED_TYPE    WS2812B

#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGB color = CRGB::Blue;
int colorSelect = 0;

int ledAmount = 0;

// Variables for button debounce
bool lastButtonReading = HIGH;
bool buttonState = HIGH;
unsigned long lastButtonChangeTime = 0;
const unsigned long buttonDebounceMs = 50;


// Turns on led based on the amount of turns on the rotary encoder
void UpdateLeds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledAmount) {

      
      switch (colorSelect % 6) {
        case 0:
          color = CRGB::Blue;
          break;
        case 1:
          color = CRGB::Red;
          break;
        case 2:
          color = CRGB::Green;
          break;
        case 3:
          color = CRGB::Yellow;
          break;
        case 4:
          color = CRGB::Purple;
          break;
        case 5:
          color = CRGB::Cyan; 
          break;

      }

      leds[i] = color;
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
}

// Reset leds and counter when button is pressed
void ReadButton() {
  bool reading = digitalRead(SW_PIN);

  if (reading != lastButtonReading) {
    lastButtonChangeTime = millis();
  }

  if ((millis() - lastButtonChangeTime) > buttonDebounceMs) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        Serial.println("Reset");
        colorSelect++;
        ledAmount = 0;
        encoder.setPosition(0);
        lastPos = 0;

        UpdateLeds();
      }
    }
  }

  lastButtonReading = reading;
}

// Reads the rotary encoder and updates led on the pcb
void ReadEncoder() {
    
  encoder.tick();

  int newPos = encoder.getPosition();

  if (newPos != lastPos) {
    if (newPos > lastPos) {
      ledAmount++;
    } else {
      ledAmount--;
    }
    // Min and max
    ledAmount = constrain(ledAmount, 0, NUM_LEDS);

    lastPos = newPos;


    Serial.print("Counter: ");
    Serial.println(ledAmount);
  }
}


// Led setup
void LedCounterSetup() {
  pinMode(SW_PIN, INPUT_PULLUP);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.clear();
  FastLED.show();

  Serial.println("Setup done");
}


