/* r4wifi-ap-osc.ino */

#include <WiFiS3.h>
#include <ArduinoOSCWiFi.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int status = WL_IDLE_STATUS;

#define SECRET_SSID "arduino_wifi_ap_"
#define SECRET_PASS "1234567890"

char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)

unsigned int localPort = 9998; // local port to listen on

const char* clientIP = "192.168.4.2";
unsigned int clientPort = 9999;

int i = 0;
float f = 0;
String s = "";

unsigned long elapsed = 0;

byte frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void setup() {
  Serial.begin(115200);

  matrix.begin();
  matrix.renderBitmap(frame, 8, 12);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  // WiFi.config(IPAddress(192,48,56,2));
  status = WiFi.beginAP(ssid, pass);

  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  } else {
    delay(5000);
  }

  OscWiFi.subscribe(localPort, "/bind", i, f, s);
  OscWiFi.subscribe(localPort, "/*", onOscReceieved);

  printWifiStatus();
}

void loop() {
  const unsigned long now = millis();

  OscWiFi.update();

  if (now - elapsed >= 50) {
    uint8_t m1 = map(i, 0, 254, 0, 12);
    for (int i = 0; i < 12; i++) { frame[0][i] = (i < m1) ? 1 : 0; }
    matrix.renderBitmap(frame, 8, 12);
    elapsed = now;
  }
}

void onOscReceieved(const OscMessage& m) {
    Serial.print(m.remoteIP());
    Serial.print(" ");
    Serial.print(m.remotePort());
    Serial.print(" ");
    Serial.print(m.size());
    Serial.print(" ");
    Serial.println(m.address());

    Serial.print(m.arg<int>(0));
    Serial.print(" ");
    Serial.print(m.arg<float>(1));
    Serial.print(" ");
    Serial.print(m.arg<String>(2));
    Serial.println();

    OscWiFi.send(m.remoteIP(), clientPort, "/reply", i, f, s);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
