//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#include <kernelforge/numeric/b_uint/b_uint_pool.h>
#include <kernelforge/runtime/Runtime.h>

using namespace KernelForge::memory;


BUIntPool::BUIntPool(const std::shared_ptr<sycl::queue> &queue) {
    queue_ = queue;
}

Allocation BUIntPool::allocate(const std::size_t limbs) {
    return MemoryPool::allocate(limbs * sizeof(uint32_t), alignof(uint32_t));
}

void BUIntPool::deallocate(const Allocation &allocation) {}

