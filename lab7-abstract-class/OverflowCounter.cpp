//
// Created by Konstantin Kovalev on 7.2.2026.
//

#include "OverflowCounter.h"

#include <iostream>

void OverflowCounter::inc() // Counter can’t be incremented over the upper limit
{
        if ( this->initial_value >= this->upper_limit)
        {
                this->initial_value = 0; // set counter to 0
        }
        else
        {
                ++this->initial_value; // increment the counter
        }
        // std::cout << "Initial value (inc): " << this->initial_value << std::endl;
        // std::cout << "Upper limit: (inc): " << this-> upper_limit << std::endl;
}
void OverflowCounter::dec() // Counter can’t be decremented below zero
{
        if (this->initial_value <= 0)
        {
                this->initial_value = this-> upper_limit; // set counter to upper limit
        }
        else
        {
                --this->initial_value; // increment the counter
        }
        // std::cout << "Initial value (dec): " << this->initial_value << std::endl;
        // std::cout << "Upper limit: (dec): " << this-> upper_limit << std::endl;
}

OverflowCounter::operator int () //  conversion operator that can be used
{ // to read or print the current counter value.
        return this->initial_value;
}