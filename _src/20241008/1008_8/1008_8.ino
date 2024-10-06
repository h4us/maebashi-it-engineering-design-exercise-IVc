// Arduinoの出力ピンにスケッチ内で使う別名を付ける
// A0番ピンを _CDS1 という名前に、7番ピンを _SW1 という名前に、8番ピンを _LED1 という名前に
#define _CDS1 A0
#define _SW1 7
#define _LED1 8

// アナログ入力読み取り用の変数（CdSセルの状態を記憶する領域）を設定する
int cdsVal = 100;
// デジタル入力読み取り用の変数（タクトスイッチの状態を記憶する領域）を設定する
int swState = 0;
// デジタル出力8番ピン用の変数（8番ピンの状態を記憶する領域）を設定する
int ledState = 0;
// タイマー用の変数（プログラムが起動してからの時間を記憶する領域）を設定する
unsigned long lastTime = 0;

void setup() {
  // _CDS1（A0ピン）を入力にする
  pinMode(_CDS1, INPUT);
   // _SW1（7番ピン）を入力にする・「プルアップ」バージョン
  pinMode(_SW1, INPUT_PULLUP);

  // _LED1（8番ピン）を出力にする
  pinMode(_LED1, OUTPUT);

  // Serial.begin(19200);
}

void loop() {
  // デジタル入力から読み取ったタクトスイッチの状態を一時的な変数に記憶する
  int tmp_s = !digitalRead(_SW1);

  // デジタル入力に変化があった時だけ更新するテクニック
  if (swState != tmp_s) {
    swState = tmp_s;
  }

  // タクトスイッチが押されている時だけアナログ入力から値を読み取って更新
  if (swState > 0) {
    // アナログ入力から読み取った値を変数に記憶する
    cdsVal = analogRead(_CDS1);
  }

  // プログラムが起動してからの時間を一時的な変数に記憶する
  // millis() は、プログラムが起動してからの時間をミリ秒で取得する組み込み関数
  unsigned long tmp_t = millis();

  // 最後に取得した経過時間 lastTime と上記 tmp_t に記憶した経過時間の差分を計算する
  // アナログ入力から読み取った値より上記の差分が大きければ、デジタル出力 _LED1 の状態を反転させる
  // constrain() は値を一定の範囲内に制限する組み込み関数
  // この場合、10ミリ秒～1000ミリ秒の範囲で、一定周期でLEDを点滅させる動作になる
  if ((tmp_t - lastTime) > constrain(1000 - cdsVal, 10, 1000)) {
    ledState = !ledState;
    digitalWrite(_LED1, ledState);
    // 最後に取得した経過時間を新しい値で更新しておく
    lastTime = tmp_t;
  }

  /*
  Serial.print("_CDS1_Value:");
  Serial.print(cdsVal);
  Serial.print(",_SW1_State:");
  Serial.print(swState);
  Serial.print(",Led_State:");
  Serial.println(ledState);
  */

  // 10ミリ秒待つ
  delay(10);
}
