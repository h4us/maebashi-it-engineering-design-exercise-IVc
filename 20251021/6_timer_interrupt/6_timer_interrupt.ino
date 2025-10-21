/* 6_timer_interrupt.ino */

// ライブラリの読み込み
#include <FspTimer.h>

// D8ピンに対して別名をつける
#define LED_OUT_1 D8

FspTimer tm;

// D8ピン（= 外付けLED）の状態を格納する変数
bool ledOut = LOW;

// - オンボードチップLEDの状態を格納する変数
// - 割り込み処理内で変更される変数には volatile 修飾子をつける
volatile bool state = LOW;

void cb(timer_callback_args_t *arg) {
  digitalWrite(PIN_LED, state);
  state = !state;
}

void setup() {
  pinMode(LED_OUT_1, OUTPUT);

  // 使用可能な割り込み用タイマーの検索
  uint8_t tm_type;
  int8_t tm_ch = FspTimer::get_available_timer(tm_type);
  if (tm_ch < 0) return;

  // - 使用可能な割り込み用タイマーの初期化と開始
  // - begin() の引数は以下
  // -- タイマーのモード
  // -- タイマーのソースタイプ
  // -- タイマーのチャンネル
  // -- 周波数（Hz、１秒間に何度周回するか）
  // -- デューティー比（%）
  // -- 割り込み発生時に呼び出す関数
  // -- 呼び出す関数に引き渡すコンテキスト（省略可）
  tm.begin(TIMER_MODE_PERIODIC, tm_type, tm_ch, 10.0f, 50.0f, cb);
  tm.setup_overflow_irq();
  tm.open();
  tm.start();
}

void loop() {
  digitalWrite(LED_OUT_1, ledOut);
  ledOut = !ledOut;
  delay(500);
}
