/* 1105_servo_with_serial */

#include <Servo.h>

#if (defined(PICO_RP2040))
#define _SRV_OUTPIN 0
#else
#define _SRV_OUTPIN 9
#endif

Servo srv1;

int angle = 90;

unsigned long tick = 0;

const byte numChars = 64;
char receivedChars[numChars];

bool newData = false;

void setup() {
  pinMode(_SRV_OUTPIN, OUTPUT);

  // 指定可能なパルス幅の範囲が異なる場合は初期化時に指定する。
  // サーボモーター（FEETECH FT90B）の初期化。
  srv1.attach(_SRV_OUTPIN, 500, 2500);
  // サーボモーター（Tower Pro SG-90）の初期化。
  // srv1.attach(_SRV_OUTPIN, 500, 2400);
  srv1.write(angle);

  Serial.begin(57600);
}

void loop() {
  recvWithEndMarker();

  if (newData == true) {
    String tmp_str = String(receivedChars);
    String tmp_perms[2] = { "", "" };
    int sidx = 0, pidx = 0;

    while (true) {
      int fidx = tmp_str.indexOf(' ', sidx);
      if (fidx != -1) {
        String sstr = tmp_str.substring(sidx, fidx);
        sidx = fidx + 1;
        if (pidx < 2) {
          tmp_perms[pidx] = sstr;
          pidx ++;
        } else {
          break;
        }
      } else {
        String rstr = tmp_str.substring(sidx, tmp_str.length());
        if (pidx < 2) {
          tmp_perms[pidx] = rstr;
        }
        break;
      }
    }

    Serial.println(tmp_str);

    if (tmp_perms[0].length() != 0) {
      angle = map(tmp_perms[0].toInt(), 0, 1023, 0, 180);

      Serial.print("Raw[0]:");
      Serial.print(tmp_perms[0]);
      Serial.print(",Angle:");
      Serial.println(angle);

      srv1.write(angle);
    }

    newData = false;
  }

  if ((millis() - tick) > 1000) {
    tick = millis();
    Serial.println("tick");
  }
}

void recvWithEndMarker() {
  static byte ndx = 0;
  const char endMarker = ';';
  char rc;

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
}
