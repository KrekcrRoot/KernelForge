#include <kernelforge/runtime/Runtime.h>

#include "modules/calc/Person.h"

int main() {

    Person person {18};

    std::cout << person.age << std::endl;

    KernelForge::Runtime::instance().shutdown();
    return 0;
}
