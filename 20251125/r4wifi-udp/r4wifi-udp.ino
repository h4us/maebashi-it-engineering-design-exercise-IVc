/* r4wifi-udp.ino */

#include <WiFiS3.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int status = WL_IDLE_STATUS;

#define SECRET_SSID "SSID_NAME" // この箇所を自分のSSIDとPWに変更
#define SECRET_PASS "PASSWORD" // この箇所を自分のSSIDとPWに変更

char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)

unsigned int localPort = 9998; // local port to listen on

char packetBuffer[256]; // buffer to hold incoming packet

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

WiFiUDP Udp;

void setup() {
  Serial.begin(115200);

  matrix.begin();
  matrix.renderBitmap(frame, 8, 12);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  printWifiStatus();

  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    IPAddress remoteIp = Udp.remoteIP();
    // Serial.print("From ");
    // Serial.print(remoteIp);
    // Serial.print(", port ");
    // Serial.println(Udp.remotePort());

    // read the packet into packetBuffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
      String rtxt = String(packetBuffer);

      if (rtxt.indexOf("/led1 ") == 0) {
        rtxt.replace("/led1 ", "");
        int ledval = rtxt.toInt();
        uint8_t m1 = map(ledval, 0, 254, 0, 12);
        for (int i = 0; i < 12; i++) { frame[0][i] = (i < m1) ? 1 : 0; }
      } else if (rtxt.indexOf("/led2 ") == 0) {
        rtxt.replace("/led2 ", "");
        int ledval = rtxt.toInt();
        uint8_t m2 = map(ledval, 0, 254, 0, 12);
        for (int i = 0; i < 12; i++) { frame[1][i] = (i < m2) ? 1 : 0; }
      }

      matrix.renderBitmap(frame, 8, 12);
    }
  }
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
