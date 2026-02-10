//
// Created by Konstantin Kovalev on 10.2.2026.
//

// Define and implement a class that inherits from Observer and takes observer
// name as a parameter.
#include <iostream>
#include "InheritedObserver.h"

void InheritedObserver::update() // When observer’s Update is called it prints its name and “got update”.When observer’s Update is called it prints its name and “got update”.
{
        std::cout << this->observer_name << " : Got update" << std::endl;
}
