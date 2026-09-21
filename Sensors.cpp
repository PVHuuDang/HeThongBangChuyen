#include "Sensors.h"
#include "Config.h"

void sensorsInit() {
    pinMode(SW_GOC, INPUT_PULLUP);
    pinMode(SW_DEM_KHAY, INPUT_PULLUP);
    pinMode(SW_SERVO, INPUT_PULLUP);
    pinMode(SW_CUA, INPUT_PULLUP);
}

bool isGocPressed() {
    return digitalRead(SW_GOC) == LOW;
}

bool isServoPressed() {
    return digitalRead(SW_SERVO) == LOW;
}

bool isCuaPressed() {
    return digitalRead(SW_CUA) == LOW;
}

bool checkDemKhayPulse() {
    static bool lastState = HIGH;
    static unsigned long lastDebounceTime = 0;
    bool pulseDetected = false;
    
    int currentState = digitalRead(SW_DEM_KHAY);

    if (currentState != lastState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > 50) { 
        if (currentState == LOW && lastState == HIGH) {
            pulseDetected = true;
        }
        lastState = currentState;
    }
    return pulseDetected;
}

