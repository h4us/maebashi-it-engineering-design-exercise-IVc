import processing.serial.*;

Serial port;

int bgCol = 255;
int mx = 10, my = 20;

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
  text("timer1: " + str(mx) + ", timer2: " + str(my), 10, 60);
}

void mousePressed() {
  // クリックした際のマウスのXY座標で更新間隔を指定（1 - 150）

  mx = int(map(mouseX, 0, 1023, 1, 150));
  my = int(map(mouseY, 0, 1023, 1, 150));

  port.write(str(mx) + " " +  str(my) + ";\r");
}

void keyPressed() {
  // Space キーでパラメーターをリセット
  if (keyCode == 32) {
    mx = 10;
    my = 20;

    port.write("10 20;\r");
  }
}
