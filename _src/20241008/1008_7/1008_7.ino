/* 1008_7.ino */

// Arduinoの出力ピンにスケッチ内で使う別名を付ける
// A0番ピンを _CDS1 という名前に、8番ピンを _LED1 という名前に
#define _CDS1 A0
#define _LED1 8

// アナログ入力読み取り用の変数（CdSセルの状態を記憶する領域）を設定する
int cdsVal = 0;

void setup() {
  // _CDS1（A0ピン）を入力にする
  pinMode(_CDS1, INPUT);

  // _LED1（8番ピン）を出力にする
  pinMode(_LED1, OUTPUT);

  // シリアルモニタ用の通信の初期化処理
  Serial.begin(19200);
}

void loop() {
  // アナログ入力から読み取ったCdSセルの状態を変数に記憶する
  // (CdSセルにあたっている光の強さに対応する 0 ~ 1023 までの数値)
  cdsVal = analogRead(_CDS1);

  // シリアルモニタに表示するメッセージ
  Serial.print("_CDS1_Value:");
  Serial.println(cdsVal);

  if(cdsVal < 100) {
    // アナログ入力の値が100より低い場合にLEDを点灯
    //（CdSセルに対してあまり光が当たっていない状態）
    digitalWrite(_LED1, HIGH);
  } else {
    // アナログ入力の値が100より高い場合にLEDを消灯
    //（CdSセルに対してある程度光が当たっている状態）
    digitalWrite(_LED1, LOW);
  }

  // 100ミリ秒待つ
  // （待ち時間を入れないと、変化が早すぎてわかりにくいので）
  delay(100);
}
