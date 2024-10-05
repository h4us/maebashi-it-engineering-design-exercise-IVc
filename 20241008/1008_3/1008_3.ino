// Arduinoの出力ピンにスケッチ内で使う別名を付ける
// 7番ピンを _SW1 という名前に、8番ピンを _LED1 という名前に、9番ピンを _LED2 という名前に
#define _SW1 7
#define _LED1 8
#define _LED2 9

// デジタル入力読み取り用の変数（タクトスイッチの状態を記憶する領域）を設定する
int swState = 0;

// カウンタ用の変数（カウントした数を記憶しておく）を設定する
int pushCount = 0;

void setup() {
   // _SW1（7番ピン）を入力にする・「プルアップ」バージョン
  pinMode(_SW1, INPUT_PULLUP);  

  // _LED1（8番ピン）を出力にする
  pinMode(_LED1, OUTPUT);
  // _LED2（9番ピン）を出力にする
  pinMode(_LED2, OUTPUT); 

  // シリアルモニタ用の通信の初期化処理
  Serial.begin(19200);
}

void loop() {  
  // デジタル入力から読み取ったタクトスイッチの状態を変数に記憶する
  swState = !digitalRead(_SW1);

  // タクトスイッチが押されたら1カウントアップする
  // 「%」という記号（余剰演算子）を使って、0・1・2・3と数えたらまた0に戻るようにする
  pushCount = (pushCount + swState) % 4;

  // シリアルモニタに表示するメッセージ（改行なし）
  Serial.print("_SW1 State: ");
   // シリアルモニタに表示するメッセージ（改行なし） 
  Serial.print(swState);
  // シリアルモニタに表示するメッセージ（改行なし）
  Serial.print(" , Count: ");
   // シリアルモニタに表示するメッセージ（改行あり） 
  Serial.println(pushCount);

  // 「&」という記号をビット演算子として使って、特定のカウントの時だけ点灯させる
  // （若干わかりにくい書き方なので、別の方法も後述します）
  digitalWrite(_LED1, pushCount & 1); // カウントが1・3の時だけ点灯
  digitalWrite(_LED2, pushCount & 2); // カウントが2・3の時だけ点灯
  
  // 200ミリ秒待つ
  // （待ち時間を入れないと、タクトスイッチを押す・離すの動作によるカウントアップが早すぎてわかりにくいので）
  delay(200); 
}