 /*!
 * @brief Aa ultrasonic distance sensor From M5Stack
 * @copyright Copyright (c) 2022 by M5Stack[https://m5stack.com]
 *
 * @Links [Unit Sonic I2C](https://docs.m5stack.com/en/unit/sonic.i2c)
 * @Links [Unit Sonic IO](https://docs.m5stack.com/en/unit/sonic.io)
 * @version  V0.0.2
 * @date  2022-07-21
 */
#ifndef _UNIT_SONIC_H_
#define _UNIT_SONIC_H_

#include "Arduino.h"
#include "pins_arduino.h"

class SONIC_IO {
   private:
    uint8_t _trig;
    uint8_t _echo;

   public:
    void begin(uint8_t trig = 26, uint8_t echo = 36);
    float getDuration();
    float getDistance();
};

#endif