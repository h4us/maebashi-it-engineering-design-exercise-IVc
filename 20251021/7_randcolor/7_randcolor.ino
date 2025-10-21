/* 7_rndcolor.ino */

// 外部ライブラリの読み込み・事前にインストールが必要
#include <Adafruit_NeoPixel.h>

// LEDデバイスの初期化
Adafruit_NeoPixel pixels(1, D8, NEO_RGB + NEO_KHZ800);

void setup() {
  // 乱数のシード（種）をアナログの入力のノイズを拾って決定する
  randomSeed(analogRead(A0));

  pixels.begin();
}

void loop() {
  // 0 ~ 255 の乱数を生成し、RGBの値に使用
  int r = random(256);
  int g = random(256);
  int b = random(256);

  /*
  // デバッグ用
  Serial.println(String(r) + ":" + String(g) + ":" + String(b));
  */

  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();

  delay(83); /* ~12fps */
}
