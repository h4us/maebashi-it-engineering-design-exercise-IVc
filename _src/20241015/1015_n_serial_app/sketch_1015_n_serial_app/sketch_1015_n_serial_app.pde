import processing.serial.*;

Serial port;

void setup() {
  size(1023, 1023);

  println("Available serial ports:");
  println(Serial.list());

  port = new Serial(this, Serial.list()[0], 57600);
}

void draw() {
  
  String data = str(mouseX) + " " + str(mouseY) + ";\r";

  port.write(data);
}
