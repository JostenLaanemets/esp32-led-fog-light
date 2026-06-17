#pragma once

constexpr int ENCODER_CLK_PIN = 18;
constexpr int ENCODER_DT_PIN = 19;
constexpr int ENCODER_SW_PIN = 21;

constexpr int R_BLINKER_PIN = 12;
constexpr int L_BLINKER_PIN = 13;

constexpr unsigned long DEBOUNCE_MS = 40;

void setupButton();
bool readButton(struct Button &button);




// Button struct for debouncing
struct Button {
    int pin;
    bool lastReading;
    bool stableState;
    unsigned long lastChangeTime;
};


extern Button encoder_sw;
extern Button r_blinder;    
extern Button l_blinder;

