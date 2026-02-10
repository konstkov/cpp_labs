//
// Created by Konstantin Kovalev on 7.2.2026.
//

#ifndef CPP_LAB7_COUNTER_H
#define CPP_LAB7_COUNTER_H

class Counter
{
public:
        virtual void inc() = 0;
        virtual void dec() = 0;
        virtual operator int() = 0;
        virtual ~Counter() {};
};

// you need to implement this function
void UseCounter(Counter& ctr, int num);

#endif //CPP_LAB7_COUNTER_H