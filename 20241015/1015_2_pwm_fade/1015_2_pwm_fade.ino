/* 1015_2_pwm_fade.ino */

// Raspberry Pi Pico W: GPIO16番ピンを _SW1 という名前に、GPIO15番ピンを _LED1 という名前に
// Arduino UNO: 7番ピンを _SW1 という名前に、9番ピンを _LED1 という名前に
#if (defined(PICO_RP2040))
#define _SW1 16
#define _LED1 15
#else
#define _SW1 7
#define _LED1 9
#endif

// デジタル入力読み取り用の変数を設定
int swState = 0;

// 角度をを記憶する変数を設定
float deg = 0;

// 角速度を記憶する変数を設定
int speed = 1;

// 経過時間計測用の変数を設定
unsigned long elapsed;

// 経過時間計測（タクトスイッチ押下）用の変数を設定
unsigned long lastPushed;

void setup() {
  pinMode(_SW1, INPUT_PULLUP);
  pinMode(_LED1, OUTPUT);

  lastPushed = millis();
  elapsed = micros();

  Serial.begin(19200);
}

void loop() {
  int tmp_s = !digitalRead(_SW1);

  // デジタル入力に変化があった時だけ更新
  if (swState != tmp_s) {
    swState = tmp_s;
  }

  // タクトスイッチが押されてる経過時間が200ミリ秒以上の時だけ実行する
  if (swState && (millis() - lastPushed) >= 200) {

    // ビットシフトを利用した角速度の増加
    // 1, 3, 7, ...512, 1023 の間で変化する
    speed = (speed << 1) | speed;
    if (speed > 1024) { speed = 1; }

    Serial.print("_SW1_State:");
    Serial.print(swState);
    Serial.print(",speed:");
    Serial.println(speed);

    // タクトスイッチ押下の経過時間をアップデート
    lastPushed = millis();
  }

  // 500マイクロ秒に一回実行
  if ((micros() - elapsed) >= 500) {
    // cos() 関数を使った周期的なフェードイン・フェードアウト
    deg += (speed / 1023.0);
    int arc = abs((255 * cos(deg * M_PI / 180.0)));

    // PWM
    analogWrite(_LED1, arc);

    elapsed = micros();
  }
}
