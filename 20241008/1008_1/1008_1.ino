/* 1008_1.ino */

// Arduinoの出力ピンにスケッチ内で使う別名を付ける
// 7番ピンを _SW1 という名前に、8番ピンを _LED1 という名前に
#define _SW1 7
#define _LED1 8

void setup() {
  // _SW1（7番ピン）を入力にする
  pinMode(_SW1, INPUT);

  // _LED1（8番ピン）を出力にする
  pinMode(_LED1, OUTPUT);
}

void loop() {
  // デジタル入力から読み取ったタクトスイッチの状態を使って、LEDの点灯状態を制御する
  digitalWrite(_LED1, digitalRead(_SW1));
}
