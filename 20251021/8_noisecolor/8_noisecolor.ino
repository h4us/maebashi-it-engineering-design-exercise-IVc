/* 8_noisecolor.ino */

// 外部ライブラリの読み込み・事前にインストールが必要
#include <Adafruit_NeoPixel.h>
#include <SimplexNoise.h>

// LEDデバイスの初期化
Adafruit_NeoPixel pixels(1, D8, NEO_RGB + NEO_KHZ800);

float rx = 0.0;
float ry = 0.0;
float ri = 0.0;

float gx = 0.0;
float gy = 0.0;
float gi = 0.0;

float bx = 0.0;
float by = 0.0;
float bi = 0.0;

void setup() {
  // 乱数のシード（種）をアナログの入力のノイズを拾って決定する
  randomSeed(analogRead(A0));

  // Simplex Noise ジェネレーターの初期化と、R・G・Bそれぞれのステップ数の設定を通常の random() を使用して行う
  ri = random(1, 50) / 1000.0;
  gi = random(1, 50) / 1000.0;
  bi = random(1, 50) / 1000.0;
  SimplexNoise::init(random(100000));

  pixels.begin();
}

void loop() {
  // Simplex Noise の更新とマッピング処理
  rx += ri;
  gx += gi;
  bx += bi;
  int r = SimplexNoise::scaledNoise(rx - ri, ry, 0, 255);
  int g = SimplexNoise::scaledNoise(gx - gi, gy, 0, 255);
  int b = SimplexNoise::scaledNoise(bx - bi, by, 0, 255);

  /*
  // デバッグ用
  Serial.println(String(r) + ":" + String(g) + ":" + String(b));
  */

  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();

  delay(83); /* ~12fps */
}
