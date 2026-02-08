//
// Created by Konstantin Kovalev on 2.2.2026.
//

#include "ButtonLedPair.h"

#include "hardware/gpio.h"
#include "pico/time.h"
#include "pico/types.h"

#define TEN_MILLISECONDS 10000
#define ONE_SECOND 1000000 // how many microseconds in 1 second

// Parameterized constructor
ButtonLedPair::ButtonLedPair(uint button_pin, uint led_pin, std::uint32_t pins_in_use)
        : button{button_pin, true, true, false}, led{led_pin, false, false, false}
{
        timeout_ms = make_timeout_time_us(TEN_MILLISECONDS);
        timeout_s = make_timeout_time_us(ONE_SECOND);
}
// main flow
void ButtonLedPair::mainLogic() {

        if (time_reached(timeout_ms)) // if timeout of 10 ms reached read the pin states
        {
                timeout_ms = make_timeout_time_us(TEN_MILLISECONDS); // reset the timeout

                if (!button.read()) // if button is pressed
                {
                        if (led_on) // if led is on
                        {
                                // don't do anything ( it means the timeout of 1 sec is in progress)
                        }
                        else // if led is off
                        {
                                led.write(true); // toggle led on
                                led_on = true;
                        }
                }
                else if (button.read())// if button is not pressed
                {
                        if (led_on) // if led is on
                        { // implement timeout of 1 second
                                if (!timeout_triggered)
                                {
                                        timeout_s = make_timeout_time_us(ONE_SECOND); // DELETE IF NOT NECCESSARY
                                        timeout_triggered = true;
                                }
                                if (time_reached(timeout_s))
                                {
                                        timeout_s = make_timeout_time_us(ONE_SECOND); // reset the timeout
                                        led.write(false); // toggle led off
                                        led_on = false;
                                        timeout_triggered = false;
                                }
                        }
                        else // if led is off
                        {
                                // continue executing the rest of the program and check other pins
                        }
                }
        }
}
