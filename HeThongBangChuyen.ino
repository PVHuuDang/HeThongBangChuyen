#include "Motor.h"
#include "ServoCtrl.h"
#include "Sensors.h"
#include "TrayManager.h"
#include "SystemLogic.h"
#include "WebServerCtrl.h"

void setup() {
    Serial.begin(115200);
    
    // Khởi tạo phần cứng
    sensorsInit();
    motorInit();
    servoInit();
    
    // Khởi tạo logic và bộ nhớ
    trayInit();
    systemInit();
    
    // Khởi tạo Web Server cuối cùng
    webServerInit();
}

void loop() {
    webServerLoop();
    systemLoop();
}

