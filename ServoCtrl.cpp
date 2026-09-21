#include "ServoCtrl.h"
#include "Config.h"

extern Servo myServo; 
Servo myServo;

void servoInit() {
    myServo.attach(SERVO_PIN);
    servoDong();
}

void servoDong() {
    myServo.write(SERVO_DONG);
}

void servoMo() {
    myServo.write(SERVO_MO);
}

