#include "button-controller.h"
#include <Arduino.h>
#include "config.h"


//Button declarations
Button encoder_sw ={ENCODER_SW_PIN, HIGH, HIGH, 0};
Button r_blinder = {R_BLINKER_PIN,  HIGH, HIGH, 0};
Button l_blinder = {L_BLINKER_PIN,  HIGH, HIGH, 0};

    
// Setup button pins
void setupButton() {
    // ENCODER
    pinMode(ENCODER_SW_PIN, INPUT_PULLUP);
    pinMode(ENCODER_CLK_PIN, INPUT_PULLUP);
    pinMode(ENCODER_DT_PIN, INPUT_PULLUP);

    // BLINKER SWITCHES
    pinMode(R_BLINKER_PIN, INPUT_PULLUP);
    pinMode(L_BLINKER_PIN, INPUT_PULLUP);
}


// Reads bonly when pressed
bool readButton(Button& button) {
    bool reading = digitalRead(button.pin);

    if (reading != button.lastReading) {
        button.lastChangeTime = millis();
    }

    if (millis() - button.lastChangeTime > DEBOUNCE_MS) {
        if (reading != button.stableState) {
            button.stableState = reading;
            
            if (button.stableState == LOW) {
                button.lastReading = reading;
                return true;
            }
        }
    }

    button.lastReading = reading;
    return false;
}