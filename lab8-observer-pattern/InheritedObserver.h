//
// Created by Konstantin Kovalev on 10.2.2026.
//

#ifndef CPP_LAB7_INHERITEDOBSERVER_H
#define CPP_LAB7_INHERITEDOBSERVER_H

#include <string>

#include "Observer.h"

class InheritedObserver : public Observer
{
public:
        explicit InheritedObserver (std::string &name) : observer_name{std::move(name)} {} // not sure about move
        void update() override;
private:
        std::string observer_name;
};

#endif //CPP_LAB7_INHERITEDOBSERVER_H