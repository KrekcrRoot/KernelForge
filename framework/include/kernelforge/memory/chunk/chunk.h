//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_CHUNK_H
#define KERNELFORGE_CHUNK_H

#include <cstddef>

namespace KernelForge::memory {

struct Chunk {

    void *data = nullptr;
    std::size_t capacity = 0;   // in bytes
    std::size_t used = 0;       // in bytes

};


}

#endif //KERNELFORGE_CHUNK_H