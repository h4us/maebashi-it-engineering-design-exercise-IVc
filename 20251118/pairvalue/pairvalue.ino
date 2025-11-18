/* 1015_n_serial.ino */

// Raspberry Pi Pico W: GPIO16番ピンを _SW1 という名前に、GPIO15番ピンを _LED1 という名前に
// Arduino UNO: 7番ピンを _SW1 という名前に、9番ピンを _LED1 という名前に
#if (defined(PICO_RP2040))
#define _LED1 14
#define _LED2 15
#else
#define _LED1 9
#define _LED2 10
#endif

unsigned long tick = 0;
int brightness = 0;

const byte numChars = 64;
char receivedChars[numChars];

bool newData = false;

void setup() {
  pinMode(_LED1, OUTPUT);

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
      int _v0 = tmp_perms[0].toInt();

      Serial.print("Raw[0]:");
      Serial.print(tmp_perms[0]);
      Serial.print(",Int[0]:");
      Serial.println(_v0);

      analogWrite(_LED1, map(_v0, 0, 1023, 0, 254));
    }

    if (tmp_perms[1].length() != 0) {
      int _v1 = tmp_perms[1].toInt();
      Serial.print("Raw[1]:");
      Serial.print(tmp_perms[1]);
      Serial.print(",Int[1]:");
      Serial.println(_v1);

      analogWrite(_LED2, map(_v1, 0, 1023, 0, 254));
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
