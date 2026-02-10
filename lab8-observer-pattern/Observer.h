//
// Created by Konstantin Kovalev on 10.2.2026.
//

#ifndef CPP_LAB7_OBSERVER_H
#define CPP_LAB7_OBSERVER_H

// Abstract interface of Observer
class Observer
{
public:
        virtual void update() = 0;
};

#endif //CPP_LAB7_OBSERVER_H