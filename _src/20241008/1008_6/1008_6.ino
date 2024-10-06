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
  cdsVal = analogRead(_CDS1); 

  // シリアルモニタに表示するメッセージ（改行なし）
  Serial.print("_CDS1_Value:");
   // シリアルモニタに表示するメッセージ（改行あり） 
  Serial.println(cdsVal);

  // 100ミリ秒待つ
  // （待ち時間を入れないと、変化が早すぎてわかりにくいので）
  delay(100); 
}