/* r4wifi-ap-udp.ino */

#include <WiFiS3.h>

int status = WL_IDLE_STATUS;

#define SECRET_SSID "arduino_wifi_ap_" // SSIDが重複するとややこしいので、各自学籍番号などユニークなものに変更する
#define SECRET_PASS "1234567890" // 必要であればPWも変える

char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)

unsigned int localPort = 9998; // local port to listen on

char packetBuffer[256]; // buffer to hold incoming packet
char ReplyBuffer[256]; //
uint8_t replied = 0;

WiFiUDP Udp;

void setup() {
  Serial.begin(115200);

  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);

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

  printWifiStatus();

  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() {

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    IPAddress remoteIp = Udp.remoteIP();
    // Serial.println(packetSize);
    // Serial.print("From ");
    // Serial.print(remoteIp);
    // Serial.print(", port ");
    // Serial.println(Udp.remotePort());

    // read the packet into packetBuffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;

      String rtxt = String(packetBuffer);
      String stxt = "";
      replied++;

      if (rtxt.indexOf("/led1 ") == 0) {
        rtxt.replace("/led1 ", "");
        int ledval = rtxt.toInt();
        analogWrite(D9, constrain(ledval, 0, 254));
        stxt = "replied: LED1 set -> " +  String(ledval) + " [" + String(replied) + "]\n";
      } else if (rtxt.indexOf("/led2 ") == 0) {
        rtxt.replace("/led2 ", "");
        int ledval = rtxt.toInt();
        analogWrite(D10, constrain(ledval, 0, 254));
        stxt = "replied: LED2 set -> " +  String(ledval) + " [" + String(replied) + "]\n";
      } else {
        stxt = "replied: [" + String(replied) + "]\n";
      }

      // send a reply, to the IP address and port that sent us the packet
      stxt.toCharArray(ReplyBuffer, 256);
      Udp.beginPacket(Udp.remoteIP(), 9999);
      Udp.write(ReplyBuffer);
      Udp.endPacket();
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
