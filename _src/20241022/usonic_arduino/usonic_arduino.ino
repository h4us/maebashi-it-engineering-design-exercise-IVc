#include "Unit_sonic_mod.h"

SONIC_IO sensor;

void setup() {
    sensor.begin(7, 8);
    Serial.begin(115200);
}

void loop() {
    static float Distance = 0;
    Distance              = sensor.getDistance();
    if ((Distance < 4000) && (Distance > 20)) {
        char buf[32];
        sprintf(buf, "Distance: %.2fmm\r", Distance);
        Serial.println(buf);
    }
    delay(100);
}