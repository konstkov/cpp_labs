//
// Created by Konstantin Kovalev on 3.2.2026.
//

#ifndef LAB_6__PERSON_H
#define LAB_6__PERSON_H

#include <string>

class Person { // The class simply holds a person’s name and prints it when needed.
public:
        explicit Person(std::string name  = "nobody");
        virtual ~Person() = default;
        virtual void identity() const; // Identity() prints the name of the person.
        virtual void interrogate(); // Interrogate() does nothing (empty body) in class Person.
private:
        std::string name;
};
#endif //LAB_6__PERSON_H