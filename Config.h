#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "TEN_WIFI"
#define WIFI_PASS "MAT_KHAU"

// Cấu hình Chân (Theo sơ đồ ESP32-S3 chuẩn)
#define MOTOR_PWM_PIN  1  
#define SERVO_PIN      2  
#define SW_GOC         41 
#define SW_DEM_KHAY    42 
#define SW_SERVO       47 
#define SW_CUA         21 

// Thông số hệ thống
#define NUM_TRAYS      6
#define SERVO_DONG     0
#define SERVO_MO       90
#define MOTOR_SPEED    200
#define MOVE_TIMEOUT_MS 15000 // Tối đa 15s cho 1 vòng xoay

#endif

