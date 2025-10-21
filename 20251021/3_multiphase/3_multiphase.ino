/* 3_multiphase.ino */

// D9ピンとD10ピンに対して別名をつける
#define LED_OUT_1 D9
#define LED_OUT_2 D10

// - LED_OUT_1の更新化間隔
// - 最後にLED_OUT_1の状態が変更された時間を格納する変数
// - LED_OUT_1のPWM出力設定用の変数
const unsigned int interval1 = 10;
unsigned long tick1 = 0;
unsigned long phase1 = 0;

// ~ LED_OUT_1と同様、LED_OUT_2用の定数・変数
const unsigned int interval2 = 33;
unsigned long tick2 = 0;
unsigned long phase2 = 0;

void setup() {
  pinMode(LED_OUT_1, OUTPUT);
  pinMode(LED_OUT_2, OUTPUT);

  // PWM出力（analogWrite()）の解像度を10bitに設定する
  analogWriteResolution(10);
}

void loop() {
  // 現在の経過時間を測る
  auto _now = millis();

  // LED_OUT_1 と LED_OUT_2 それぞれの更新間隔でPWM出力の値を更新する
  if (_now - tick1 >= interval1) {
    // コサイン波形に沿ってPWM出力の値（0 ~ 1023）を算出
    analogWrite(LED_OUT_1, (int) abs((1023.0 * cos(phase1 * M_PI / 180.0))));
    phase1 ++;
    tick1 = _now;
  }

  if (_now - tick2 >= interval2) {
    analogWrite(LED_OUT_2, (int) abs((1023.0 * cos(phase2 * M_PI / 180.0))));
    phase2 ++;
    tick2 = _now;
  }
}
