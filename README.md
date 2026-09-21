# Hệ Thống Băng Chuyền Lưu Trữ Xoay Vòng (Carousel Storage System)
Dự án tự động hóa hệ thống lưu trữ khay xoay vòng sử dụng **ESP32-S3**, điều khiển băng chuyền qua **Web Server nội bộ** (Asynchronous). Hệ thống bao gồm 6 khay chứa, định vị qua công tắc hành trình và cơ cấu đóng/mở cửa tự động bằng servo.
## 🚀 Tính Năng Nổi Bật
*   **Điều khiển qua Web (AsyncWebServer):** API gửi/nhận hàng không gây chặn (non-blocking) vòng lặp điều khiển motor.
*   **Lưu trữ Flash (Data Persistence):** Ghi nhớ trạng thái khay chứa và ID hàng hóa vào bộ nhớ Flash (Preferences), không mất dữ liệu khi cúp điện.
*   **Bảo vệ phần cứng (Fail-safe):** Tự động ngắt điện động cơ nếu thời gian xoay vượt quá 15 giây (kẹt cơ cấu cơ khí, đứt dây).
*   **Chống nhiễu (Debounce):** Kết hợp bộ lọc tụ điện 104 phần cứng và thuật toán lọc nhiễu 50ms phần mềm.
## 🛠 Phần Cứng Yêu Cầu
*   1x Vi điều khiển ESP32-S3 (Sử dụng các chân I/O độc lập, không xung đột với module Camera/SD).
*   1x Động cơ giảm tốc trục vít JGY370 (Tự khóa trục khi mất điện).
*   1x Module điều khiển động cơ BTS7960 (43A).
*   1x Động cơ Servo SG90 (Cơ cấu chốt cửa).
*   4x Cảm biến công tắc hành trình (Tích hợp trở kéo lên và LED báo trạng thái).
## 📌 Sơ Đồ Chân (Pinout)

| Thiết bị Ngoại vi | Chân ESP32-S3 | Chức năng |
| :--- | :--- | :--- |
| **BTS7960 (R_PWM)** | `GPIO 1` | Băm xung PWM điều khiển tốc độ motor. |
| **Servo SG90** | `GPIO 2` | Xuất xung PWM điều khiển góc quay. |
| **CTHT Gốc** | `GPIO 41` | `INPUT_PULLUP` - Xác định điểm 0 (Homing). |
| **CTHT Đếm khay** | `GPIO 42` | `INPUT_PULLUP` - Đếm số lượng khay đi qua. |
| **CTHT Servo** | `GPIO 47` | `INPUT_PULLUP` - Nhận diện giới hạn Servo. |
| **CTHT Cửa** | `GPIO 21` | `INPUT_PULLUP` - Nhận diện cửa đóng/mở. |

## 📁 Cấu Trúc Thư Mục
Dự án được viết theo cấu trúc chia Module độc lập, tối ưu hóa việc quản lý và bảo trì mã nguồn:
```text
HeThongBangChuyen/
 ├── HeThongBangChuyen.ino           # File chương trình chính
 ├── Config.h                        # Cấu hình chân tín hiệu, WiFi, hằng số
 ├── Motor.h / Motor.cpp             # Giao tiếp điều khiển IC BTS7960
 ├── ServoCtrl.h / ServoCtrl.cpp     # Giao tiếp điều khiển Servo SG90
 ├── Sensors.h / Sensors.cpp         # Xử lý Công tắc hành trình & lọc nhiễu
 ├── TrayManager.h / TrayManager.cpp # Quản lý dữ liệu khay & Flash (Preferences)
 ├── SystemLogic.h / SystemLogic.cpp # Máy trạng thái (State Machine) điều hướng
 └── WebServerCtrl.h / WebServerCtrl.cpp # API Web Server bất đồng bộ

## ⚙️ HƯỚNG DẪN CÀI ĐẶT CHI TIẾT

Để biên dịch và chạy dự án này, bạn cần thiết lập môi trường lập trình Arduino IDE cho ESP32-S3 và cài đặt các thư viện bất đồng bộ.

### Bước 1: Thiết lập Board ESP32 trên Arduino IDE
1. Mở Arduino IDE, vào **File > Preferences**.
2. Thêm đường dẫn sau vào ô *Additional Boards Manager URLs*: 
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Vào **Tools > Board > Boards Manager**, tìm kiếm `esp32` và cài đặt (phiên bản mới nhất).
4. Cắm cáp kết nối ESP32-S3, vào **Tools > Board** và chọn **ESP32S3 Dev Module**.

### Bước 2: Cài đặt các thư viện bắt buộc
Bạn cần cài đặt 3 thư viện sau để code có thể biên dịch:
*   **ESP32Servo:** Vào **Sketch > Include Library > Manage Libraries**, tìm `ESP32Servo` và cài đặt.
*   **AsyncTCP:** Tải file ZIP từ [me-no-dev/AsyncTCP](https://github.com/me-no-dev/AsyncTCP), sau đó vào **Sketch > Include Library > Add .ZIP Library** để thêm.
*   **ESPAsyncWebServer:** Tải file ZIP từ [me-no-dev/ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) và thêm tương tự như trên.

### Bước 3: Cấu hình và Nạp Code
1. Mở file `HeThongBangChuyen.ino`.
2. Mở tab file `Config.h`, tìm và sửa thông tin WiFi mạng nội bộ của bạn:
   ```cpp
   #define WIFI_SSID "TEN_WIFI_CUA_BAN"
   #define WIFI_PASS "MAT_KHAU_WIFI"

