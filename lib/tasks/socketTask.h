#include <Arduino.h>
#include <WiFi.h>
#include <SocketIoClient.h>
#include <globalData.h>

const char* wifi_name = "Tan 2.4G";
const char* password = "tann122548";

char host[] = "http://192.168.1.41";
int port = 3000;

unsigned long lastSendTime = 0;
const int sendInterval = 100;

SocketIoClient socket;
void onThrottle(const char* payload, size_t length) {
    String valStr = String(payload);
    int val = valStr.toInt();
    
    // Safety clamp (กันค่าเกิน)
    if (val < 0) val = 0;
    if (val > 4095) val = 4095;

    globalData.throttle = val;
    // Serial.print("Set Throttle: "); Serial.println(val);
}

void commandControl(const char* payload, size_t length){
    String cmd  = String(payload);
    //Serial.print("Socket CMD: "); Serial.println(cmd);
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

    socket.on("esp32-control", commandControl);
    socket.on("esp32-throttle", onThrottle);
    socket.begin(host, port);
    for(;;){

        if(WiFi.status() != WL_CONNECTED){
            if (globalData.isRunning) {
                Serial.println("WiFi lost");
                globalData.isRunning = false; 
            }

            Serial.println("Reconnecting WiFi...");
            WiFi.disconnect();
            WiFi.reconnect();
            

            vTaskDelay(pdMS_TO_TICKS(3000)); 
            continue;
        }

        socket.loop();
        if(globalData.isRunning){
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
    }

}
