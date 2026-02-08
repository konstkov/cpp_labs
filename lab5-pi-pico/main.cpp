//
// Created by Konstantin Kovalev on 1.2.2026.
//

#include <iostream>

#include "ButtonLedPair.h"
#include "gpio.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#define LED1 22
#define LED2 21
#define LED3 20

#define SW0 9
#define SW1 8
#define SW2 7
#define DEFAULT 0

int main()
{       // Create button/led pair objects

        ButtonLedPair a(SW0, LED3, DEFAULT); // default value 0 zero for variable pins_in_use
        ButtonLedPair b(SW1, LED2, DEFAULT);
        ButtonLedPair c(SW2, LED1, DEFAULT);

        while (true) // polling
        {
                a.mainLogic();
                b.mainLogic();
                c.mainLogic();
        }
        return 0;
}
