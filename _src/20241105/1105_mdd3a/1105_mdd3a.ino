/* 1105_servo_with_serial */

#include <Servo.h>

#if (defined(PICO_RP2040))
#define _PWM1 0
#define _PWM2 1
#define _PWM3 2
#define _PWM4 3
#else
#define _PWM1 9
#define _PWM2 10
#define _PWM3 11
#define _PWM4 12
#endif

unsigned long tick = 0;

const byte numChars = 64;
char receivedChars[numChars];

bool newData = false;

void setup() {
  pinMode(_PWM1, OUTPUT);
  pinMode(_PWM2, OUTPUT);
  pinMode(_PWM3, OUTPUT);
  pinMode(_PWM4, OUTPUT);

  analogWrite(_PWM1, 0);
  analogWrite(_PWM2, 0);
  analogWrite(_PWM3, 0);
  analogWrite(_PWM4, 0);

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
      int m1 = map(tmp_perms[0].toInt(), 0, 1023, -254, 254);

      Serial.print("Raw[0]:");
      Serial.print(tmp_perms[0]);
      Serial.print(",m1_status:");
      Serial.println(m1);

      if (m1 < 0) {
        analogWrite(_PWM1, m1);
        analogWrite(_PWM2, 0);
      } else if (m1 == 0) {
        analogWrite(_PWM1, 0);
        analogWrite(_PWM2, 0);
      } else {
        analogWrite(_PWM1, 0);
        analogWrite(_PWM2, m1);
      }
    }

    if (tmp_perms[1].length() != 0) {
      int m2 = map(tmp_perms[1].toInt(), 0, 1023, -254, 254);

      Serial.print("Raw[1]:");
      Serial.print(tmp_perms[1]);
      Serial.print(",m1_status:");
      Serial.println(m2);

      if (m2 < 0) {
        analogWrite(_PWM3, m2);
        analogWrite(_PWM4, 0);
      } else if (m2 == 0) {
        analogWrite(_PWM3, 0);
        analogWrite(_PWM4, 0);
      } else {
        analogWrite(_PWM3, 0);
        analogWrite(_PWM4, m2);
      }
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
