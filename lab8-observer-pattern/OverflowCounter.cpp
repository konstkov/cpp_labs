//
// Created by Konstantin Kovalev on 7.2.2026.
//
#include <iostream>
#include "OverflowCounter.h"
#include "LimitedCounter.h"
#include "Observer.h"

void OverflowCounter::inc() // Counter can’t be incremented over the upper limit
{
        if ( this->initial_value >= this->upper_limit)
        {
                std::cout << "Overflow, trying to increment above the upper limit. \n" << std::endl;
                notify(); // notify about the state change
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
                std::cout << "Overflow, trying to decrement below zero. \n" << std::endl;
                this->initial_value = this-> upper_limit; // set counter to upper limit
                notify(); // notify about the state change
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

void OverflowCounter::attach(Observer *o)  // Add observer
{
        this->observers.push_back(o); // add a pointer of Observer to the end of vector
}
void OverflowCounter::notify() // when one object (Subject)
// changes state, all its dependents (Observer) are notified and updated automatically
{
        for (const auto &v : observers)
        {
                v->update(); // iterate through the observers and call their update() function in order to notify them of the state change
        }
}