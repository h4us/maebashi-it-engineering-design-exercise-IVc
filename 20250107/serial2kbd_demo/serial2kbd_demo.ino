/* serial2kbd_demo.ino */

#if (defined(PICO_RP2040))
#define _SWIN1_PIN 0
#else
#define _SWIN1_PIN 8
#endif

uint8_t sw_in = 0;

unsigned long tick = 0;
bool newData = false;

void setup() {
  pinMode(_SWIN1_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  delay(1000);
}

void loop() {
  sw_in = digitalRead(_SWIN1_PIN);
  
  if ((millis() - tick) > 3000) {
    if (!sw_in) {
      Serial.print("/type_raw ");
      Serial.println("LeftAlt Tab");
    }
    
    tick = millis();
    // TODO:
    // Serial.println("tick");
  }
}