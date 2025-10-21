/* 2_taptempo.ino */

// D2ピンに対して別名をつける
#define SW_1 D2

// - オンボードチップLEDの点滅間隔を格納する変数
// - 最後にタクトスイッチが押された時間を格納する変数
// - 最後にオンボードチップLEDの状態が変更された時間を格納する変数
unsigned long tempo = 1000;
unsigned long tapped = 0;
unsigned long tick = 0;

// オンボードチップLEDの状態を格納する変数
bool state = LOW;

// タクトスイッチの連続操作制限用
bool debounced = false;

void setup() {
  // Arduino 内蔵のプルアップ抵抗を使用する
  pinMode(SW_1, INPUT_PULLUP);
}

void loop() {
  // 現在の経過時間を測る
  auto _now = millis();

  if (!digitalRead(SW_1) && !debounced) {
    // - タクトスイッチが押されたら、現在の経過時間と最後にタクトスイッチが押された時間の差分を点滅間隔として算出
    // - 最後にタクトスイッチが押された時間を更新
    tempo = _now - tapped;
    /*
    // デバッグ用
    Serial.println(String(_now) + " / " + String(tapped) + " -> " + String(tempo));
    */
    tapped = _now;
    debounced = true;
  } else if (digitalRead(SW_1)) {
    debounced = false;
  }

  if (_now - tick >= tempo) {
    // - 現在の経過時間と最後にオンボードチップLEDの状態が変更された時間の差分と、現在の点滅間隔を比較
    // - 点滅間隔より大きければ点滅させる
    // - 最後にオンボードチップLEDの状態が変更された時間を更新
    digitalWrite(PIN_LED, state);
    state = !state;
    tick = _now;
  }
}
