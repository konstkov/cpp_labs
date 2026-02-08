//
// Created by Konstantin Kovalev on 2.2.2026.
//

#ifndef EXERCISE2_BUTTONLEDPAIR_H
#define EXERCISE2_BUTTONLEDPAIR_H
#include "gpio.h"
#include "pico/types.h"

class ButtonLedPair
{
public:
        explicit ButtonLedPair(uint, uint, std::uint32_t);
        void mainLogic();
private:
        GPIOPin button; // from class GPIOPin
        GPIOPin led; // from class GPIOPin
        absolute_time_t timeout_ms; // 10 milliseconds
        absolute_time_t timeout_s; // 1 second
        bool led_on = false; // helps to keep track of led state in main function
        bool timeout_triggered = false;
};

#endif //EXERCISE2_BUTTONLEDPAIR_H