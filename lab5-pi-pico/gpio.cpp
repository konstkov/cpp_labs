//
// Created by Konstantin Kovalev on 1.2.2026.
//

#include <cstdint>
#include "gpio.h"

#include "hardware/gpio.h"
#include "pico/time.h"

// parameterized constructor
GPIOPin::GPIOPin(const uint pin, bool input, bool pullup, bool invert) //  true → invert ; false → normal
                : gpio_pin{pin}
{
        if (pins_in_use & (1u << gpio_pin))
        {
                dormant = true; // set dormant state
                return;
        }
        else
        {
                pins_in_use |= (1u << gpio_pin); // set the bit
        }

        gpio_init(gpio_pin); // initialize gpio pin

        if (input)
        {
                gpio_set_dir(gpio_pin, GPIO_IN);
                if (pullup)
                {
                        gpio_pull_up(gpio_pin);
                }
                else gpio_disable_pulls(gpio_pin);
        }
        else
        {
                gpio_set_dir(gpio_pin, GPIO_OUT);
                gpio_put(gpio_pin, invert ? true : false);
        }

}

GPIOPin::~GPIOPin()
{
        if (dormant) return;
        pins_in_use &= ~(1u << gpio_pin); // clear the bit, free the pin
}

        bool GPIOPin::read() const // reads state of the GPIO pin
        {
                if (dormant) return false; // don't use the dormant pin
                return gpio_get(this->gpio_pin); // return the current state of gpio pin
        }

        void GPIOPin::write(bool value) // Sets the state of pin. Has no effect when pin is configured as an input
        {
                if (dormant) return; // don't use the dormant pin
                gpio_put(this->gpio_pin, value); // set the pin value
        }

        GPIOPin::operator bool() const // returns true if pin is usable and false if dormant
{
if (!dormant) return true;
        else return false;
}

