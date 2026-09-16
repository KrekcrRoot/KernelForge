//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_B_UINT_MANAGER_H
#define KERNELFORGE_B_UINT_MANAGER_H

#include <kernelforge/numeric/b_uint/b_uint_pool.h>

#include <unordered_map>

namespace KernelForge::numeric {

class BUIntManager {

public:
    explicit BUIntManager(const std::shared_ptr<sycl::queue> &queue);

    uint32_t create(uint32_t val);
    uint32_t create(const std::vector<uint32_t>& data);

    uint32_t get_for_one_limb(uint32_t handle);
    void get_b_uint(uint32_t* data, uint32_t handle);

    std::size_t limbs(uint32_t handle);

    std::optional<uint32_t> sum(uint32_t first, uint32_t second);

    void release_all_data();


private:
    memory::BUIntPool b_uint_pool_;

    std::shared_ptr<sycl::queue> queue_;
    uint32_t next_b_uint_id_ = 0;

    std::unordered_map<uint32_t, memory::Allocation> allocations_;

};

}

#endif //KERNELFORGE_B_UINT_MANAGER_H