/* 1105_servo_simple.ino */

#include <Servo.h>

#if (defined(PICO_RP2040))
#define _SRV_OUTPIN 0
#else
#define _SRV_OUTPIN 9
#endif

Servo srv1;

int angle = 0;

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
  srv1.write(angle);

  Serial.print("Angle: ");
  Serial.println(angle);

  // 2秒間隔で30°ずつ動かす。180°まで行ったら0°に戻す.
  angle += 30;
  if (angle > 180) angle = 0;

  delay(2000);
}
