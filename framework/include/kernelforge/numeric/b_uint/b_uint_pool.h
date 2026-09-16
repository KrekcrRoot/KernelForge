//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_B_UINT_POOL_H
#define KERNELFORGE_B_UINT_POOL_H

#include <kernelforge/memory/pool/memory_pool.h>


namespace KernelForge::memory {

class BUIntPool : public MemoryPool
{

public:
    BUIntPool(const std::shared_ptr<sycl::queue> &queue);

    Allocation allocate(std::size_t limbs);
    void deallocate(const Allocation& allocation);

};

}

#endif //KERNELFORGE_B_UINT_POOL_H