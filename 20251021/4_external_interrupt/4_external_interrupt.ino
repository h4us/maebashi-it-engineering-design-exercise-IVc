/* 4_external_interrupt.ino */

void cb() {
  // D2ピンの状態が変化した際に呼び出される処理
  digitalWrite(PIN_LED, !digitalRead(D2));
}

void setup() {
  // Arduino 内蔵のプルアップ抵抗を使用する
  pinMode(D2, INPUT_PULLUP);

  // D2ピンの外部割り込みを有効にする
  attachInterrupt(digitalPinToInterrupt(D2), cb, CHANGE);
}

void loop() {
  // メインループ内では何もしない
}
