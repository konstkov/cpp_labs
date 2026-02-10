//
// Created by Konstantin Kovalev on 7.2.2026.
//

#ifndef CPP_LAB7_OVERFLOWCOUNTER_H
#define CPP_LAB7_OVERFLOWCOUNTER_H
#include <vector>

#include "Counter.h"
#include "Subject.h"

class OverflowCounter : public Counter, public Subject
{
public:
        OverflowCounter(int init_value, int upper_lim) : initial_value{init_value}, upper_limit{upper_lim} {}
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


#endif //CPP_LAB7_OVERFLOWCOUNTER_H