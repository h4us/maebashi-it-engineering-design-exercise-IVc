/* 1_internal_pull_up.ino */

void setup() {
  // Arduino 内蔵のプルアップ抵抗を使用する
  pinMode(D2, INPUT_PULLUP);
}

void loop() {
  // - プルアップの指定で digitalRead() の値が反転するので、否定演算子「!」を使って戻す
  // - PIN_LED は Arduino ボード上にあるオンボードチップLED
  digitalWrite(PIN_LED, !digitalRead(D2));
}
