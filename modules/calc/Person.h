//
// Created by /<R3/<(RR00T on 16.09.2026.
//

#ifndef KERNELFORGE_PERSON_H
#define KERNELFORGE_PERSON_H

// Пример работы со структурой b_uint

#include <kernelforge/numeric/b_uint/b_uint.h>

class Person {

public:
    explicit Person(unsigned int age);

    KernelForge::numeric::b_uint age;

};


#endif //KERNELFORGE_PERSON_H