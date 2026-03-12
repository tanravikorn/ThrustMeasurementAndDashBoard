#include <Arduino.h>
#include <WiFi.h>
#include <SocketIoClient.h>
#include <globalData.h>

const char* wifi_name = "CUHAR FreeWifi";
const char* password = "FlyHighSkyHigh";

char host[] = "192.168.1.109";
int port = 3000;
const char* socketUrl = "/socket.io/?EIO=3&transport=websocket";

unsigned long lastSendTime = 0;
const int sendInterval = 100;
unsigned long lastSocketBeginAttempt = 0;
const unsigned long socketReconnectInterval = 5000;

volatile bool socketConnected = false;

SocketIoClient socket;

void onSocketConnect(const char* payload, size_t length) {
    (void)payload;
    (void)length;
    socketConnected = true;
    Serial.println("Socket connected");
}

void onSocketDisconnect(const char* payload, size_t length) {
    (void)payload;
    (void)length;
    socketConnected = false;
    Serial.println("Socket disconnected");
}

void onThrottle(const char* payload, size_t length) {
    String valStr = String(payload).substring(0, length);
    valStr.trim();
    if (valStr.startsWith("\"") && valStr.endsWith("\"") && valStr.length() >= 2) {
        valStr = valStr.substring(1, valStr.length() - 1);
    }

    int val = valStr.toInt();
    
    // Safety clamp (กันค่าเกิน)
    if (val < 0) val = 0;
    if (val > 4095) val = 4095;

    globalData.throttle = val;
    //print data recieve
    //Serial.print("Throttle: "); Serial.println(val);
}

void commandControl(const char* payload, size_t length){
    String cmd  = String(payload).substring(0, length);
    cmd.trim();
    if (cmd.startsWith("\"") && cmd.endsWith("\"") && cmd.length() >= 2) {
        cmd = cmd.substring(1, cmd.length() - 1);
    }

    //Serial.print("CMD: "); Serial.println(cmd);
    if (cmd == "START") globalData.isRunning = true;
    else if (cmd == "STOP")  globalData.isRunning = false;
}

void socketTask(void *pvParameters){
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_name, password);
    while(WiFi.status() != WL_CONNECTED){
        vTaskDelay(pdMS_TO_TICKS(100));
        Serial.print(".");
    }
    Serial.println();
    Serial.println("connected");

    socket.on("connect", onSocketConnect);
    socket.on("disconnect", onSocketDisconnect);
    socket.on("esp32-control", commandControl);
    socket.on("esp32-throttle", onThrottle);
    socket.begin(host, port, socketUrl);
    lastSocketBeginAttempt = millis();
    Serial.println("Socket task started!");
    for(;;){

        if(WiFi.status() != WL_CONNECTED){
            if (globalData.isRunning) {
                Serial.println("WiFi lost");
                globalData.isRunning = false; 
            }

            socketConnected = false;

            Serial.println("Reconnecting WiFi...");
            WiFi.reconnect();
            

            vTaskDelay(pdMS_TO_TICKS(3000)); 
            continue;
        }

        socket.loop();

        unsigned long now = millis();
        if (!socketConnected && (now - lastSocketBeginAttempt >= socketReconnectInterval)) {
            Serial.println("Reconnecting socket...");
            socket.begin(host, port, socketUrl);
            lastSocketBeginAttempt = now;
        }

        if(globalData.isRunning && socketConnected){
            unsigned long currentTime = millis();
            if (currentTime - lastSendTime >= sendInterval) {
                lastSendTime = currentTime;

                String jsonString = "{";
                jsonString += "\"thrust\":" + String(globalData.thrust) + ",";
                jsonString += "\"voltage\":" + String(globalData.voltage) + ",";
                jsonString += "\"current\":" + String(globalData.current) + ",";
                jsonString += "\"power\":" + String(globalData.power) + ",";
                jsonString += "\"rpm\":" + String(globalData.rpm);
                jsonString += "}";

                socket.emit("esp32-send-data", jsonString.c_str());
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
