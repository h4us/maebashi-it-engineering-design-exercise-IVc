/* 1015_1_pwm.ino */

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

// PWMのデューティー比（= LEDの明るさ）を記憶する変数を設定
int brightness = 0;

// 経過時間計測用の変数を設定
unsigned long lastPushed;

void setup() {
  pinMode(_SW1, INPUT_PULLUP);
  pinMode(_LED1, OUTPUT);

  lastPushed = millis();

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

    // デューティー比の値をインクリメント（5ずつ足して、255で余剰演算）
    // 0 ~ 254 の間で変化する
    brightness = (brightness + 5) % 255;

    Serial.print("_SW1_State:");
    Serial.print(swState);
    Serial.print(",brightness:");
    Serial.println(brightness);

    // タクトスイッチ押下の経過時間をアップデート
    lastPushed = millis();
  }

  // PWM
  analogWrite(_LED1, brightness);
}
