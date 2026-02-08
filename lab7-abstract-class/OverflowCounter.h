//
// Created by Konstantin Kovalev on 7.2.2026.
//

#ifndef CPP_LAB7_OVERFLOWCOUNTER_H
#define CPP_LAB7_OVERFLOWCOUNTER_H
#include "Counter.h"

class OverflowCounter : public Counter
{
public:
        OverflowCounter(int init_value, int upper_lim) : initial_value{init_value}, upper_limit{upper_lim} {}

        void inc() override;
        void dec() override;
        operator int() override;
private:
        int initial_value;
        int upper_limit;
};


#endif //CPP_LAB7_OVERFLOWCOUNTER_H