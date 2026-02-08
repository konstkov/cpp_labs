//
// Created by Konstantin Kovalev on 7.2.2026.
//

#ifndef CPP_LAB7_LIMITEDCOUNTER_H
#define CPP_LAB7_LIMITEDCOUNTER_H
#include "Counter.h"

class LimitedCounter: public Counter
{
public: // initialize
        LimitedCounter(int init_value, int upper_lim) : initial_value{init_value}, upper_limit{upper_lim} {} // continue later

        void inc() override;
        void dec() override;
        operator int() override;
private:
        int initial_value;
        int upper_limit;
};


#endif //CPP_LAB7_LIMITEDCOUNTER_H