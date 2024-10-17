/* 1015_3_pwm_aio.ino */

// Raspberry Pi Pico W: GPIO16番ピンを _SW1 という名前に、GPIO15番ピンを _LED1 という名前に
// Arduino UNO: 7番ピンを _SW1 という名前に、9番ピンを _LED1 という名前に
#if (defined(PICO_RP2040))
#define _CDS1 A0
#define _LED1 15
#else
#define _CDS1 A0
#define _LED1 9
#endif

// アナログ入力読み取り用の各種変数（CdSセルの状態を記憶する領域）を設定する
// ノイズ対策のために、10サンプルの平均値を取る方法を採用
const int bufSize = 10;
int ainBuf[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int bIndex = 0;
int ainTotal = 0;

// 経過時間計測用の変数を設定
unsigned long elapsed;

void setup() {
  pinMode(_CDS1, INPUT);
  pinMode(_LED1, OUTPUT);

  elapsed = millis();

  Serial.begin(19200);
}

void loop() {
  // 直近10サンプルの平均値を取る
  ainTotal = ainTotal - ainBuf[bIndex];

  ainBuf[bIndex] = analogRead(_CDS1);

  ainTotal = ainTotal + ainBuf[bIndex];

  bIndex = (bIndex + 1) % bufSize;

  int avg = ainTotal / bufSize;

  // PWM
  // map() 関数を使って、マッピングする
  // 周囲の環境が明るいほど明るく点灯
  analogWrite(_LED1, map(avg, 5, 900, 0, 254));

  // 反転版。周囲の環境が暗いほど明るく点灯
  // analogWrite(_LED1, map(avg, 5, 900, 254, 0));

  // 50ミリ秒に一回実行
  if ((millis() - elapsed) >= 50) {
    Serial.println(avg);
    elapsed = millis();
  }

  delay(1);
}
