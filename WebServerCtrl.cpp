#include "WebServerCtrl.h"
#include "Config.h"
#include "SystemLogic.h"
#include "TrayManager.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void webServerInit() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.println("\nKet noi WiFi thanh cong!");
    Serial.print("Dia chi IP (HTTP) cua ban la: ");
    Serial.println(WiFi.localIP()); // Dòng này cực kỳ quan trọng để lấy IP!

    server.on("/gui", HTTP_GET, [](AsyncWebServerRequest *request){
        if (!isSystemIdle()) {
            request->send(400, "text/plain", "He thong dang ban!");
            return;
        }
        if (!request->hasParam("id")) {
            request->send(400, "text/plain", "Thieu tham so id");
            return;
        }
        String id = request->getParam("id")->value();
        int target = getEmptyTray();

        if (target == 0) {
            request->send(400, "text/plain", "Da het khay trong!");
            return;
        }

        assignTray(target, id);
        startMovingToTray(target);
        request->send(200, "text/plain", "Nhan lenh GUI. Dang den khay " + String(target));
    });

    server.on("/nhan", HTTP_GET, [](AsyncWebServerRequest *request){
        if (!isSystemIdle()) {
            request->send(400, "text/plain", "He thong dang ban!");
            return;
        }
        if (!request->hasParam("id")) {
            request->send(400, "text/plain", "Thieu tham so id");
            return;
        }
        String id = request->getParam("id")->value();
        int target = getTrayById(id);

        if (target == 0) {
            request->send(404, "text/plain", "Khong tim thay ID!");
            return;
        }

        clearTray(target);
        startMovingToTray(target);
        request->send(200, "text/plain", "Nhan lenh LAY. Dang xuat khay " + String(target));
    });

    server.begin();
}

void webServerLoop() {
    // Để trống do ESPAsyncWebServer xử lý bất đồng bộ ngầm
}

