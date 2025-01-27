/* servo_with_speed.ino */

#include <Servo.h>

#if (defined(PICO_RP2040))
#define _SRV_OUTPIN 0
#else
#define _SRV_OUTPIN 9
#endif


class Sweeper {
  unsigned long lastUpdate;
  int  updateInterval;
  Servo servo;
  int pos;
  int dest;
  int tick;

public:
  Sweeper() {};
  ~Sweeper() { servo.detach(); };

  void detach() { servo.detach(); }
  void resetTimer() { lastUpdate = 0; }
  void setInterval(int i) { updateInterval = i; }
  void setAngle(int angle) { dest = angle; }
  void write(int angle_or_pwidth) { dest = angle_or_pwidth; }
  void setTick(int t) { tick = t; }

  void setup(int servopin, int rmin, int rmax, int interval = 1000) {
    updateInterval = interval;
    tick = 4;
    pos = 0;

    pinMode(servopin, OUTPUT);
    servo.attach(servopin, rmin, rmax);
    servo.write(pos);
  }

  bool update() {
    if((micros() - lastUpdate) >= updateInterval) {
      lastUpdate = micros();

      if (pos != dest) {
        int dir = (pos > dest) ? -1 : 1;
        pos += (min(abs(dest - pos), tick) * dir);
        servo.write(pos);
      }

      return true;
    } else {
      return false;
    }
  }
};

const byte numChars = 64;
char receivedChars[numChars];

Sweeper srv1;

bool recvWithEndMarker(char endMarker = ';') {
  static byte ndx = 0;
  char rc;
  bool newData = false;

  if (Serial.available()) {
    while (Serial.available() > 0 && newData == false) {
      rc = Serial.read();

      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
      }
    }
  }

  return newData;
}

void setup() {
  // 指定可能なパルス幅の範囲が異なる場合は初期化時に指定する。
  // サーボモーター（FEETECH FT90B）の初期化。
  srv1.setup(_SRV_OUTPIN, 500, 2500);
  // サーボモーター（Tower Pro SG-90）の初期化。
  // srv1.setup(_SRV_OUTPIN, 500, 2400);

  Serial.begin(57600);
}

void loop() {
  bool newData = recvWithEndMarker();

  if (newData == true) {
    int sidx = 0, pidx = 0;
    int dataSize = 3;
    String tmp_str = String(receivedChars);
    String tmp_perms[dataSize] = { "", "", "" };

    while (true) {
      int fidx = tmp_str.indexOf(' ', sidx);
      if (fidx != -1) {
        String sstr = tmp_str.substring(sidx, fidx);
        sidx = fidx + 1;
        if (pidx < dataSize) {
          tmp_perms[pidx] = sstr;
          pidx ++;
        } else {
          break;
        }
      } else {
        String rstr = tmp_str.substring(sidx, tmp_str.length());
        if (pidx < dataSize) {
          tmp_perms[pidx] = rstr;
        }
        break;
      }
    }

    Serial.println(tmp_str);

    if (tmp_perms[0].length() != 0) {
      int angle_or_pwidth = constrain(tmp_perms[0].toInt(), 0, 180);

      Serial.print("Angle:");
      Serial.println(angle_or_pwidth);

      srv1.write(angle_or_pwidth);
    }

    if (tmp_perms[1].length() != 0) {
      int interval = constrain(tmp_perms[1].toInt(), 1000, 50000);

      Serial.print("interval:");
      Serial.println(interval);

      srv1.setInterval(interval);
    }

    if (tmp_perms[2].length() != 0) {
      int tick = constrain(tmp_perms[2].toInt(), 1, 100);

      Serial.print("tick:");
      Serial.println(tick);

      srv1.setTick(tick);
    }
  }

  srv1.update();
}
