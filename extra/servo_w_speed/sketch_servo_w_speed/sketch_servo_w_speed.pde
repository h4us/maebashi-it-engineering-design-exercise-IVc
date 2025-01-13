import processing.serial.*;

Serial port;
int step = 4;
int interval = 4;
int angle = 0;

int bgCol = 255;

void setup() {
  size(1023, 1023);

  println("Available serial ports:");
  println(Serial.list());

  port = new Serial(this, Serial.list()[0], 57600);
}

void draw() {
  background(bgCol);

  fill(255, 40, 40);
  textSize(30);
  text("angle: " + str(angle) + ", interval: " + str(interval) + ", step: " + str(step), 10, 60);
}

void mouseMoved() {
  // マウスのY座標でサーボ角度の更新間隔と移動ステップ数を指定（0 - 100）
  String data = "";

  if (keyPressed && (keyCode == CONTROL || keyCode == SHIFT)) {
    // Shift もしくは Ctrl キーを押しながら。更新間隔を指定（1 - 100、値が低いほど更新間隔が短い）
    bgCol = 0;
    interval = int(map(mouseY, 0, 1023, 1, 100));
    data  = str(angle) +  " " + str(interval) + ";\r";
  } else if (keyPressed && keyCode == ALT) {
    // Alt キーを押しながら。移動ステップを指定（1 - 100、値が高いほど一度の更新で移動する角度が大きい）
    bgCol = 128;
    step = int(map(mouseY, 0, 1023, 1, 100));
    data  = str(angle) +  " " + str(interval) + " " +  str(step) + ";\r";
  } else {
    bgCol = 255;
  }

  if (data.length() > 0) {
    port.write(data);
  }
}

void mousePressed() {
  // クリックした際のマウスのX座標でサーボの角度を指定（1 - 180）
  String data = "";

  angle = int(map(mouseX, 0, 1023, 0, 180));
  data  = str(angle) + ";\r";

  port.write(data);
}

void keyPressed() {
  // Space キーでサーボのパラメーターをリセット
  if (keyCode == 32) {
    angle = 0;
    interval = 4;
    step = 4;

    port.write("0 10 4;\r");
  }
}
