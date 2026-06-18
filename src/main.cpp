#include <Arduino.h>
#include "config.h"
#include "led-controller.h"
#include "button-controller.h"
#include <FastLED.h>


void setup() {
    setupLEDs();
    setupButton();
    Serial.begin(115200);
}

void loop() {
if (readButton(encoder_sw)) {
        Serial.println("Encoder button pressed");
        turnOffLEDs();
    }



}