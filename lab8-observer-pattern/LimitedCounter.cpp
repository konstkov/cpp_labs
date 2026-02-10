//
// Created by Konstantin Kovalev on 7.2.2026.
//

#include "LimitedCounter.h"

#include <iostream>

#include "Observer.h"

// overriding pure virtual functions of abstract class 'Counter'

void LimitedCounter::inc() // Counter can’t be incremented over the upper limit
{
        if ( ++this->initial_value > this->upper_limit)
        {
                std::cout << "Limit reached, trying to increment above upper limit. \n" << std::endl;
                notify(); // notify of the state change
        }
}
void LimitedCounter::dec() // Counter can’t be decremented below zero
{
        if (--this->initial_value < 0)
        {
                std::cout << "Limit reached, trying to decrement below zero. \n" << std::endl;
                notify(); // notify of the state change
        }
}

LimitedCounter::operator int () //  conversion operator that can be used
{ // to read or print the current counter value.

        return this->initial_value; // for printing current counter value
}
// implement all the necessary member functions (of class Subject)

void LimitedCounter::attach(Observer *o)  // Add observer
{
        this->observers.push_back(o); // add a pointer of Observer to the end of vector
}
void LimitedCounter::notify() // when one object (Subject)
// changes state, all its dependents (Observer) are notified and updated automatically
{
        for (const auto &v : observers)
        {
                v->update(); // iterate through the observers and call their update() function in order to notify them of the state change
        }
}
