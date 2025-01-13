/* task_timer.ino */

#include <Servo.h>

#if (defined(PICO_RP2040))
#define _PWM_OUTPIN 1
#define _SRV_OUTPIN 0
#else
#define _PWM_OUTPIN 10
#define _SRV_OUTPIN 9
#endif


class TaskTimer {
  unsigned long lastUpdate;
  int updateInterval;

public:
  TaskTimer() {};
  ~TaskTimer() {};

  void resetTimer() { lastUpdate = 0; }
  void setInterval(int i) { updateInterval = i; }

  void setup(int interval = 10) {
    updateInterval = interval;
  }

  bool update() {
    if((millis() - lastUpdate) >= updateInterval) {
      lastUpdate = millis();
      return true;
    } else {
      return false;
    }
  }
};

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

int deg1 = 0, deg2 = 0;
int it1 = 10, it2 = 20;

Sweeper srv1;
TaskTimer t1, t2;

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
  pinMode(_PWM_OUTPIN, OUTPUT);

  // 指定可能なパルス幅の範囲が異なる場合は初期化時に指定する。
  // サーボモーター（FEETECH FT90B）の初期化。
  srv1.setup(_SRV_OUTPIN, 500, 2500, 3000);
  srv1.setTick(1);
  // サーボモーター（Tower Pro SG-90）の初期化。
  // srv1.setup(_SRV_OUTPIN, 500, 2400);

  t1.setup(it1);
  t2.setup(it2);

  Serial.begin(57600);
}

void loop() {
  bool newData = recvWithEndMarker();

  if (newData == true) {
    int sidx = 0, pidx = 0;
    int dataSize = 2;
    String tmp_str = String(receivedChars);
    String tmp_perms[dataSize] = { "", "" };

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
      it1 = constrain(tmp_perms[0].toInt(), 1, 300);
      t1.setInterval(it1);
      t1.resetTimer();
    }

    if (tmp_perms[1].length() != 0) {
      it2 = constrain(tmp_perms[1].toInt(), 1, 300);
      t2.setInterval(it2);
      t2.resetTimer();
    }
  }

  if (t1.update()) {
    deg1 = (deg1 + 1) % 180;
    analogWrite(_PWM_OUTPIN, int(abs(254 * cos(deg1 * M_PI / 180.0))));
  }

  if (t2.update()) {
    deg2 = (deg2 + 1) % 180;
    srv1.setAngle(int(abs(180 * cos(deg2 * M_PI / 180.0))));
  }

  srv1.update();
}
