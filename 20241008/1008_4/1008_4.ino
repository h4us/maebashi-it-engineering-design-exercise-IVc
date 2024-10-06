/* 1008_4.ino */

// Arduinoの出力ピンにスケッチ内で使う別名を付ける
// 7番ピンを _SW1 という名前に、8番ピンを _LED1 という名前に
#define _SW1 7
#define _LED1 8

// デジタル入力読み取り用の変数（タクトスイッチの状態を記憶する領域）を設定する
int swState = 0;

void setup() {
  // _SW1（7番ピン）を入力にする・「プルアップ」バージョン
  pinMode(_SW1, INPUT_PULLUP);

  // _LED1（8番ピン）を出力にする
  pinMode(_LED1, OUTPUT);

  // シリアルモニタ用の通信の初期化処理
  Serial.begin(19200);
}

void loop() {
  // デジタル入力から読み取ったタクトスイッチの状態を変数に記憶する
  swState = !digitalRead(_SW1);

  // シリアルモニタに表示するメッセージ・ラベル用のテキスト・改行なし
  Serial.print("_SW1_State:");
   // シリアルモニタに表示するメッセージ・変数「swState」の数値を表示・改行あり
  Serial.println(swState);

  // 変数を使ってLEDの点灯状態を変える
  digitalWrite(_LED1, swState);

  // 200ミリ秒待つ
  // （待ち時間を入れないと、タクトスイッチを押す・離すの動作による変化が早すぎてわかりにくいので）
  delay(200);
}
