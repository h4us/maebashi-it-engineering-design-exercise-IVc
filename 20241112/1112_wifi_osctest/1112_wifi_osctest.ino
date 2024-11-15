/* 1112_wifi_osctest.ino */

#include <WiFi.h>
#include <ArduinoOSCWiFi.h>

#if (defined(PICO_RP2040))
#define _PWM_OUTPIN 0
#else
#define _PWM_OUTPIN 0
#endif

// 各人の設定に変更
String ssid = "ssid";
String pw = "password";
String osc_dest = "192.168.1.1";

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
  Serial.println(localIP.toString());

  pinMode(_PWM_OUTPIN, OUTPUT);

  OscWiFi.subscribe(12000, "/brightness", [&](int& val) {
    brightness = val;

    OscWiFi.send(osc_dest, 12000, "/reply", brightness);
    Serial.println("brightness:" + brightness);
  });

  Serial.println("Enter loop");
}


void loop() {
  unsigned long _now = millis();
  
  if ((_now - tick2) > 10) {
    tick2 = _now;
    analogWrite(_PWM_OUTPIN, constrain(brightness, 0, 254));
  }

  if ((_now - tick) > 1000) {
    tick = _now;

    OscWiFi.send(osc_dest, 12000, "/ping", localIP.toString());

    Serial.print("ping: ");
    Serial.println(localIP.toString());
  }

  OscWiFi.update();
  delay(10);
}
