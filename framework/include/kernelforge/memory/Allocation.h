//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_ALLOCATION_H
#define KERNELFORGE_ALLOCATION_H

#include <cstddef>
#include <cstdint>

namespace KernelForge::memory {

struct Allocation {

    uint32_t chunk;
    std::size_t offset;
    std::size_t capacity;

};

}

#endif //KERNELFORGE_ALLOCATION_H