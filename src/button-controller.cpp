#include "button-controller.h"
#include <Arduino.h>
#include "config.h"


//Button declarations

    //Encoder switch
Button encoder_sw ={pin: ENCODER_SW_PIN, lastReading: HIGH, stableState: HIGH, lastChangeTime: 0};

    // Buttons
Button r_blinker = {pin: R_BLINKER_PIN,  lastReading: HIGH, stableState: HIGH, lastChangeTime: 0};
Button l_blinker = {pin: L_BLINKER_PIN,  lastReading: HIGH, stableState: HIGH, lastChangeTime: 0};

    
// Setup button pins
// PULLUP: Pressed = LOW, Not Pressed = HIGH
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