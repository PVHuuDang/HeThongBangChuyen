#include "SystemLogic.h"
#include "Motor.h"
#include "ServoCtrl.h"
#include "Sensors.h"
#include "Config.h"

enum SystemState {
    STATE_HOMING,
    STATE_IDLE,
    STATE_MOVING,
    STATE_SERVO_MO,
    STATE_WAIT_DOOR_OPEN,
    STATE_WAIT_DOOR_CLOSE,
    STATE_ERROR 
};

SystemState currentState = STATE_HOMING;
int currentTrayCount = 0;
int destinationTray = 0;
unsigned long startMoveTime = 0;

void systemInit() {
    currentState = STATE_HOMING;
    startMoveTime = millis();
}

bool isSystemIdle() { return (currentState == STATE_IDLE); }

void startMovingToTray(int targetTray) {
    if (currentState == STATE_IDLE) {
        destinationTray = targetTray;
        currentState = STATE_MOVING;
        startMoveTime = millis();
        Serial.println("Di chuyen den khay: " + String(destinationTray));
    }
}

void systemLoop() {
    switch (currentState) {
        case STATE_ERROR:
            motorDung();
            break;

        case STATE_HOMING:
            motorChay();
            if (millis() - startMoveTime > MOVE_TIMEOUT_MS) {
                currentState = STATE_ERROR;
                Serial.println("LOI: Timeout khi tim goc!");
                return;
            }
            if (isGocPressed()) {
                motorDung();
                currentTrayCount = 0;
                currentState = STATE_IDLE;
            }
            break;

        case STATE_MOVING:
            motorChay();
            if (millis() - startMoveTime > MOVE_TIMEOUT_MS) {
                currentState = STATE_ERROR;
                Serial.println("LOI: Ket co cau co khi!");
                return;
            }
            if (isGocPressed()) currentTrayCount = 0;

            if (checkDemKhayPulse()) {
                currentTrayCount++;
                if (currentTrayCount == destinationTray) {
                    motorDung();
                    currentState = STATE_SERVO_MO;
                }
            }
            break;

        case STATE_SERVO_MO:
            servoMo();
            if (!isServoPressed()) currentState = STATE_WAIT_DOOR_OPEN;
            break;

        case STATE_WAIT_DOOR_OPEN:
            if (!isCuaPressed()) currentState = STATE_WAIT_DOOR_CLOSE;
            break;

        case STATE_WAIT_DOOR_CLOSE:
            if (isCuaPressed()) {
                servoDong();
                delay(300);
                currentState = STATE_HOMING;
                startMoveTime = millis();
            }
            break;
            
        case STATE_IDLE:
            break;
    }
}

