//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#include <kernelforge/numeric/b_uint/b_uint_manager.h>

#include "kernelforge/runtime/Runtime.h"

using namespace KernelForge::numeric;

const uint32_t BASE_B_UINT = 1000000000u;

BUIntManager::BUIntManager(const std::shared_ptr<sycl::queue> &queue)
    :   b_uint_pool_(queue),
        queue_(queue)
{}

uint32_t BUIntManager::create(const uint32_t val) {

    const auto allocation = b_uint_pool_.allocate(1);
    allocations_[next_b_uint_id_] = allocation;

    auto* ptr = static_cast<uint32_t *>(b_uint_pool_.resolve(allocation));

    if (!ptr)
        throw std::runtime_error("resolve returned nullptr");

    this->queue_->single_task([=]() {
        ptr[0] = val;
    });

    return next_b_uint_id_++;

}

uint32_t BUIntManager::create(const std::vector<uint32_t>& data) {

    const auto allocation = b_uint_pool_.allocate(data.size());
    allocations_[next_b_uint_id_] = allocation;

    auto* ptr = static_cast<uint32_t *>(b_uint_pool_.resolve(allocation));

    if (!ptr)
        throw std::runtime_error("resolve returned nullptr");

    queue_->memcpy(ptr, data.data(), sizeof(uint32_t) * data.size()).wait();

    return next_b_uint_id_++;

}


void BUIntManager::release_all_data() {
    b_uint_pool_.release_all_chunks();
    allocations_.clear();
}

uint32_t BUIntManager::get_for_one_limb(const uint32_t handle) {

    const auto it = this->allocations_.find(handle);

    if (it == this->allocations_.end())
        return 0;

    const auto allocation = it->second;
    const uint32_t *ptr = b_uint_pool_.resolve<uint32_t>(allocation);

    if (!ptr)
        throw std::runtime_error("get_for_one_limb runtime error");

    uint32_t data;

    queue_->memcpy(&data, ptr, sizeof(uint32_t)).wait();

    return data;
}

void BUIntManager::get_b_uint(uint32_t *data, uint32_t handle) {

    const auto it = this->allocations_.find(handle);

    if (it == this->allocations_.end())
        return;

    const auto allocation = it->second;

    const uint32_t *ptr = b_uint_pool_.resolve<uint32_t>(allocation);

    if (!ptr)
        throw std::runtime_error("get_for_one_limb runtime error");

    // const std::size_t limbs = allocation.capacity / sizeof(uint32_t);

    queue_->memcpy(data, ptr, allocation.capacity).wait();

}

std::size_t BUIntManager::limbs(uint32_t handle) {
    const auto it = this->allocations_.find(handle);

    if (it == this->allocations_.end())
        return 0;

    const auto allocation = it->second;
    return allocation.capacity / sizeof(uint32_t);
}

std::optional<uint32_t> BUIntManager::sum(uint32_t first, uint32_t second) {

    const auto first_it = this->allocations_.find(first);
    if (first_it == allocations_.end())
        return std::nullopt;

    const auto second_it = this->allocations_.find(second);
    if (second_it == allocations_.end())
        return std::nullopt;

    const auto f_alloc = first_it->second;
    const auto s_alloc = second_it->second;

    const size_t f_len = limbs(first);
    const size_t s_len = limbs(second);

    const size_t len = f_len > s_len ? f_len : s_len;

    const auto allocation = b_uint_pool_.allocate(len + 1);
    allocations_[next_b_uint_id_] = allocation;

    const auto* f_ptr = b_uint_pool_.resolve<uint32_t>(f_alloc);
    const auto* s_ptr = b_uint_pool_.resolve<uint32_t>(s_alloc);
    auto* ptr = b_uint_pool_.resolve<uint32_t>(allocation);

    queue_->submit([&](sycl::handler& h) {

        h.single_task([=]() {

            uint64_t carry = 0;

            for (size_t i = 0; i < len; ++i) {
                const uint64_t a = (i < f_len) ? f_ptr[i] : 0;
                const uint64_t b = (i < s_len) ? s_ptr[i] : 0;

                const uint64_t sum = a + b + carry;
                ptr[i] = static_cast<uint32_t>(sum % BASE_B_UINT);
                carry = sum / BASE_B_UINT;
            }

            ptr[len] = static_cast<uint32_t>(carry);

        });

    });

    return next_b_uint_id_++;

}

