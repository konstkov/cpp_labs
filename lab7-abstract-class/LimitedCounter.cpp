//
// Created by Konstantin Kovalev on 7.2.2026.
//

#include "LimitedCounter.h"

#include <iostream>

// overriding pure virtual functions of abstract class 'Counter'

void LimitedCounter::inc() // Counter can’t be incremented over the upper limit
{
        if ( this->initial_value == this->upper_limit)
        {
                return; // nothing happens
        }
        ++(this->initial_value); // increment the counter
}
void LimitedCounter::dec() // Counter can’t be decremented below zero
{
        if (this->initial_value <= 0)
        {
                return; // nothing happens
        }
        --this->initial_value; // decrement the counter
}

LimitedCounter::operator int () //  conversion operator that can be used
{ // to read or print the current counter value.

        return this->initial_value; // for printing current counter value
}
