#include "lcd.h"

void CUHAR::LCD::begin() {
    Wire.begin(21, 22);
    Wire.setClock(400000); // เพิ่มความเร็ว I2C (400kHz)
    myLcd.init();
    myLcd.backlight();
    myLcd.setCursor(0, 0);
    myLcd.print("System Starting...");
}

void CUHAR::LCD::printscreen(float current, float voltage, float power, float thrust) {
    // ค่าล่าสุดที่พิมพ์บนจอ (ใช้ตรวจว่าเปลี่ยนไหม)
    static float lastCurrent = -1, lastVoltage = -1, lastPower = -1, lastThrust = -1;

    // ตัวแปรเก็บค่าเฉลี่ยแบบ exponential
    static float avgCurrent = 0, avgVoltage = 0, avgPower = 0, avgThrust = 0;

    // ค่าความไว (alpha): ยิ่งน้อยยิ่งนิ่ง
    const float alpha = 0.2f;

    // คำนวณค่า EMA (Exponential Moving Average)
    avgVoltage = alpha * voltage + (1 - alpha) * avgVoltage;
    avgCurrent = alpha * current + (1 - alpha) * avgCurrent;
    avgPower   = alpha * power   + (1 - alpha) * avgPower;
    avgThrust  = alpha * thrust  + (1 - alpha) * avgThrust;

    // ใช้ค่าที่ผ่านการกรองแล้วในการแสดงผล
    float displayVoltage = avgVoltage;
    float displayCurrent = avgCurrent;
    float displayPower   = avgPower;
    float displayThrust  = avgThrust;

    // อัปเดตเฉพาะถ้ามีการเปลี่ยนมากพอ (ลดการเขียน I2C)
    if (fabs(displayVoltage - lastVoltage) > 0.01f) {
        myLcd.setCursor(0, 0);
        myLcd.print("V:");
        myLcd.print(displayVoltage, 2);
        lastVoltage = displayVoltage;
    }

    if (fabs(displayCurrent - lastCurrent) > 0.01f) {
        myLcd.setCursor(9, 0);
        myLcd.print("A:");
        myLcd.print(displayCurrent, 2);
        lastCurrent = displayCurrent;
    }

    if (fabs(displayPower - lastPower) > 0.01f) {
        myLcd.setCursor(0, 1);
        myLcd.print("P:");
        myLcd.print(displayPower, 2);
        myLcd.print("W ");
        lastPower = displayPower;
    }

    if (fabs(displayThrust - lastThrust) > 0.01f) {
        myLcd.setCursor(8, 1);
        myLcd.print("T:");
        myLcd.print(displayThrust, 2);
        myLcd.print("N ");
        lastThrust = displayThrust;
    }
}
