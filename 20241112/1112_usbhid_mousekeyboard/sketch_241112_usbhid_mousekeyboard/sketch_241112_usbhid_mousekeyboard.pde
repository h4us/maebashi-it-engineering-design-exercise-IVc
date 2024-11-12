import processing.serial.*;

Serial port;

void setup() {
  size(1023, 1023);

  println("Available serial ports:");
  println(Serial.list());

  port = new Serial(this, Serial.list()[0], 115200);
}

void draw() {
  port.write("u");
  delay(1000);
  port.write("d");
  delay(1000);
  port.write("l");
  delay(1000);
  port.write("r");

  delay(4000);
}
