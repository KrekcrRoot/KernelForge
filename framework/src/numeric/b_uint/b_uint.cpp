//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#include <kernelforge/runtime/Runtime.h>
#include <kernelforge/numeric/b_uint/b_uint.h>

using namespace KernelForge::numeric;

b_uint::b_uint() : handle_(-1) {}

b_uint::b_uint(const unsigned int integer) {

    const std::shared_ptr<BUIntManager>& manager = Runtime::instance().get_b_uint_manager();

    const auto handle = manager->create(integer);

    handle_ = handle;

}

b_uint::b_uint(const std::initializer_list<unsigned int> limbs) {

    if (limbs.size() == 0)
        throw std::invalid_argument("b_uint cannot be empty");

    const std::shared_ptr<BUIntManager>& manager = Runtime::instance().get_b_uint_manager();

    const std::vector<uint32_t> payload{limbs};

    handle_ = manager->create(payload);

}

b_uint b_uint::operator+(const b_uint &b) const {

    const auto manager = KernelForge::Runtime::instance().get_b_uint_manager();

    const auto result = manager->sum(this->handle_, b.handle_);

    b_uint res;

    if (result.has_value()) {
        res.handle_ = result.value();
    }else {
        throw std::runtime_error("operator + b_uint");
    }

    return res;

}
