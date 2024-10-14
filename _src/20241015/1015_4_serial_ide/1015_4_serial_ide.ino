/* 1015_4_serial_ide.ino */

// Raspberry Pi Pico W: GPIO16番ピンを _SW1 という名前に、GPIO15番ピンを _LED1 という名前に
// Arduino UNO: 7番ピンを _SW1 という名前に、9番ピンを _LED1 という名前に
#if (defined(PICO_RP2040))
#define _LED1 15
#else
#define _LED1 9
#endif

int swState = 0;
int brightness = 0;

void setup() {
  pinMode(_LED1, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // シリアルポートへデータが送られてきているかをチェック
  if (Serial.available()) {
    // シリアルバッファにあるデータを String（文字列）として取り出す
    String s = Serial.readString();

    // 文字列を int（数値）として変換
    brightness = constrain(s.toInt(), 0, 254);

    Serial.println(brightness);
  }

  analogWrite(_LED1, brightness);
}
