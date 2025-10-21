/* 5_external_interrupt_w_mainloop.ino */

// D2ピンとD8ピンに対して別名をつける
#define SW_1 D2
#define LED_OUT_1 D8

// D8ピン（= 外付けLED）の状態を格納する変数
bool ledOut = LOW;

// - オンボードチップLEDの状態を格納する変数
// - 割り込み処理内で変更される変数には volatile 修飾子をつける
volatile bool state = LOW;

void cb() {
  // D2ピンの状態が変化した際に呼び出される処理
  state = !digitalRead(SW_1);
  digitalWrite(PIN_LED, state);
}

void setup() {
  // Arduino 内蔵のプルアップ抵抗を使用する
  pinMode(SW_1, INPUT_PULLUP);

  pinMode(LED_OUT_1, OUTPUT);

  // D2ピンの外部割り込みを有効にする
  attachInterrupt(digitalPinToInterrupt(SW_1), cb, CHANGE);
}

void loop() {
  // - メインループ内で0.5秒間隔で外付けLEDを点滅させる
  // - 外部割り込み内での処理は基本的にメインループ内の delay() の影響を受けない
  digitalWrite(LED_OUT_1, ledOut);
  ledOut = !ledOut;
  delay(500);
}
