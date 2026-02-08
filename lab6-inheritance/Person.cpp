//
// Created by Konstantin Kovalev on 3.2.2026.
//

#include "Person.h"
#include <iostream>

Person::Person(std::string name)
{
this->name = std::move(name);
}

void Person::identity() const // Identity() prints the name of the person.
{
        std::cout << "My name is " << this->name << std::endl;
}

void Person::interrogate() // Interrogate() does nothing (empty body) in class Person.
{
        // does nothing (empty body)
}
