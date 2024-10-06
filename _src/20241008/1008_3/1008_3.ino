// Arduinoの出力ピンにスケッチ内で使う別名を付ける
// 7番ピンを _SW1 という名前に、8番ピンを _LED1 という名前に
#define _SW1 7
#define _LED1 8

void setup() {
  // _SW1（7番ピン）を入力にする・「プルアップ」バージョン
  pinMode(_SW1, INPUT_PULLUP);

  // _LED1（8番ピン）を出力にする
  pinMode(_LED1, OUTPUT);
}

void loop() {
  // デジタル入力から読み取ったタクトスイッチの状態を使って、LEDの点灯状態を制御する
  // 「!」という記号（論理否定演算子）を使って、押す・離すの挙動を反転させたバージョン
  digitalWrite(_LED1, !digitalRead(_SW1));
}
