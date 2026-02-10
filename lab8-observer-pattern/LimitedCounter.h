//
// Created by Konstantin Kovalev on 7.2.2026.
//

#ifndef CPP_LAB7_LIMITEDCOUNTER_H
#define CPP_LAB7_LIMITEDCOUNTER_H
#include <vector>

#include "Counter.h"
#include "Subject.h"


// Derive both counters from Counter and Subject and implement all required member functions.
class LimitedCounter : public Counter, public Subject // deriving a class from two abstract classes
{
public: // initialize
        LimitedCounter(int init_value, int upper_lim) : initial_value{init_value}, upper_limit{upper_lim} {} // continue later

        // Counter functions
        void inc() override;
        void dec() override;
        operator int() override;
        //Subject functions
        void attach(Observer *o) override; // Set
        void notify() override;
private:
        int initial_value;
        int upper_limit;
        std::vector<Observer *> observers; // vector of Observer pointers
};


#endif //CPP_LAB7_LIMITEDCOUNTER_H