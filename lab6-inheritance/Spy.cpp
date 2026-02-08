//
// Created by Konstantin Kovalev on 3.2.2026.
//

#include "Spy.h"

#include <iostream>

Spy::Spy(const std::string &name, const char *alias, int resistance) : Person (name), // Constructor of Person in the initialization list
spy_resistance{resistance}//, spy_name{name}
{
        setIdentity(alias);
}

void Spy::identity () const // override identity function from Person class (prints the name of the person).
{
        if (this->spy_resistance > 0)
        {
                std::cout << "My name is: \n" << this->spy_alias << "\n" << std::endl; // if resistance greater than 0 print only alias
        }
        else
        {
                std::cout << "My alias is: \n" << this->spy_alias << std::endl; // otherwise print both alias and name
                Person::identity(); // my name is ( calling the function of parent class)
        }
}

void Spy::interrogate() // Interrogate() does nothing (empty body) in class Person. Here it decrements resistance
{
        --this->spy_resistance; // decrement resistance with each interrogate call
}

void Spy::setIdentity(const char *alias)
{
        this->spy_alias = alias;
}


