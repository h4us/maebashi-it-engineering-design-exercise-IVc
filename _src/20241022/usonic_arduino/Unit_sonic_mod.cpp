#include "Unit_sonic_mod.h"

/*! @brief Initialize the Sonic. */
void SONIC_IO::begin(uint8_t trig, uint8_t echo) {
    _trig = trig;
    _echo = echo;
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
}

float SONIC_IO::getDuration() {
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);
    
    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);

    float duration = pulseIn(_echo, HIGH);

    return duration;
}

/*! @brief Get distance data. */
float SONIC_IO::getDistance() {
    // Calculating the distance
    float Distance = getDuration() * 0.34 / 2;
    if (Distance > 4500.00) {
        return 4500.00;
    } else {
        return Distance;
    }
}
