#include <Arduino.h>
#include "config.h"
#include "led-controller.h"
#include "button-controller.h"
#include <FastLED.h>

// change to encoder after testing
int Encoder = 1;

void setup() {
    setupLEDs();
    setupButton();
    Serial.begin(115200);
    
}

void loop() {

    Modes();

    //TEST
    if (readButton(encoder_sw)) {
        Serial.println("SW");
        turnOnLEDs(CRGB::Red);
        delay(2000);
        turnOffLEDs();
    }
}

void Modes() {
    switch (Encoder) {
        case 1:
            RightBlinker();
            break;
        case 2:
            LeftBlinker();
            break;
        case 3:
            hazardBlinker();
            break;
        case 4:
            FlashLight();
            break;
        case 5:
            //...
            break;
        case 6:
            // Japanese mode
            break;
        default:
            turnOffLEDs();
            break;
    }
}