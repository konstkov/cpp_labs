//
// Created by Konstantin Kovalev on 10.2.2026.
//

#ifndef CPP_LAB7_SUBJECT_H
#define CPP_LAB7_SUBJECT_H

class Observer;
class Subject
{
public:
        virtual void attach(Observer *o) = 0; // Set
        virtual void notify() = 0;
};

#endif //CPP_LAB7_SUBJECT_H