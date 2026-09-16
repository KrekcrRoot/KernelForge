//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_MEMORY_POOL_H
#define KERNELFORGE_MEMORY_POOL_H


#include <kernelforge/memory/Allocation.h>
#include <kernelforge/memory/chunk/chunk.h>
#include <unordered_map>

#include <sycl/sycl.hpp>

namespace KernelForge::memory {

class MemoryPool {

protected:
    MemoryPool();

public:

    Allocation allocate(
        std::size_t bytes,
        std::size_t alignment = alignof(std::max_align_t)
    );

    void deallocate(const Allocation& allocation);

    void* resolve(const Allocation& allocation);

    template<typename T>
    T* resolve(const Allocation& allocation) {
        return static_cast<T*>(this->resolve(allocation));
    }

    void release_all_chunks();


protected:

    std::shared_ptr<sycl::queue> queue_;
    uint32_t next_chunk_id_ = 0;
    std::size_t chunk_size_ = 1 << 20;
    std::unordered_map<uint32_t, Chunk> chunks_;

};


}


#endif //KERNELFORGE_MEMORY_POOL_H