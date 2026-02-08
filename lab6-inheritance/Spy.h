//
// Created by Konstantin Kovalev on 3.2.2026.
//

#ifndef LAB_6__SPY_H
#define LAB_6__SPY_H
#include <string>
#include "Person.h"


class Spy: public Person  // Spy constructor must take three parameters: name of the spy, alias of the spy, and resistance
{
// Note that you must override indentity() and interrogate() in class Spy.
public:
        explicit Spy(const std::string &name,const char * alias, int resistance);
        void identity() const override; // Identity() prints the name of the person.
        void interrogate() override; // Interrogate() does nothing (empty body) in class Person.
        void setIdentity(const char *alias);
private:
        int spy_resistance;
        std::string spy_alias;
        //std::string spy_name;
        // Person name;
};


#endif //LAB_6__SPY_H