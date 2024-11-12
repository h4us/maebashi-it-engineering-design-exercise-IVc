/* 1112_wifi_osctest.ino */

#include <WiFi.h>
#include <ArduinoOSCWiFi.h>

#if (defined(PICO_RP2040))
#define _PWM_OUTPIN 0
#else
#define _PWM_OUTPIN 0
#endif

// 各人の設定に変更
String ssid = "INAFXXK-XPS 9394";
String pw = "102R!e06";
String osc_dest = "192.168.137.1";

int brightness = 0;

unsigned long tick = 0;
unsigned long tick2 = 0;

IPAddress localIP;

void setup() {
  Serial.begin(57600);

  WiFi.begin(ssid, pw);

  int timeout = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting connection..");
    timeout ++;
    if (timeout > 20) {
      break;
    }
  }

  localIP = WiFi.localIP();

  pinMode(_PWM_OUTPIN, OUTPUT);

  OscWiFi.subscribe(12000, "/brightness", [&](int& val) {
    brightness = val;

    OscWiFi.send(osc_dest, 12000, "/reply", brightness);
    Serial.println("ssid:" + ssid + ", osc_dest:" + osc_dest + ", brightness:" + brightness);
  });

  Serial.println("Enter loop");
}


void loop() {
  if ((millis() - tick) > 33) {
    tick2 = millis();
    analogWrite(_PWM_OUTPIN, constrain(brightness, 0, 254));
  }

  if ((millis() - tick) > 1000) {
    tick = millis();
    // Serial.println("tick", localIP.toString());
  }

  OscWiFi.update();
  delay(33);
}
