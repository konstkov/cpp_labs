//
// Created by Konstantin Kovalev on 1.2.2026.
//

#ifndef EXERCISE2_GPIO_H
#define EXERCISE2_GPIO_H
#include <cstdint>

#include "pico/types.h"

class GPIOPin
{
public:
        explicit GPIOPin(uint pin, bool input, bool pullup, bool invert); //  true → invert ; false → normal
        GPIOPin(const GPIOPin &) = delete; // Makes the object non-copyable
        ~GPIOPin();
        bool read() const; // reads state of the GPIO pin
        void write(bool value); // Sets the state of pin. Has no effect when pin is configured as an input

        explicit operator bool() const; // returns true if pin is usable and false if dormant

private:
        static std::uint32_t pins_in_use;
        // add others as needed
        uint gpio_pin;
        bool dormant;
};
        // non-member functions
        void mainLogic(GPIOPin &button, GPIOPin &led, bool &led_toggle);
        //void main_state_machine(led_sm & machine);
        void debounce(GPIOPin &pin);
        bool nonBusyWait(uint64_t then, uint64_t delay);



#endif //EXERCISE2_GPIO_H