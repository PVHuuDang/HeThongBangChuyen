#include "Motor.h"
#include "Config.h"

void motorInit() {
    pinMode(MOTOR_PWM_PIN, OUTPUT);
    motorDung();
}

void motorChay() {
    analogWrite(MOTOR_PWM_PIN, MOTOR_SPEED);
}

void motorDung() {
    analogWrite(MOTOR_PWM_PIN, 0);
}
