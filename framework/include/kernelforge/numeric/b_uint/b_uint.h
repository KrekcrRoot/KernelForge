//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_B_UINT_H
#define KERNELFORGE_B_UINT_H

#include <kernelforge/runtime/Runtime.h>
#include <sycl/sycl.hpp>

namespace KernelForge::numeric {

struct b_uint {

     explicit b_uint();

     explicit b_uint(unsigned int integer);
     b_uint(std::initializer_list<unsigned int> limbs);

     b_uint operator+(const b_uint& b) const;

     uint32_t handle_;

};


inline std::ostream& operator<<(std::ostream& os, const b_uint& v) {

     const auto manager = KernelForge::Runtime::instance().get_b_uint_manager();

     const auto n = manager->limbs(v.handle_);

     if (n == 1) {
          os << manager->get_for_one_limb(v.handle_);
          return os;
     }

     std::vector<uint32_t> buf(n);

     manager->get_b_uint(buf.data(), v.handle_);

     os << '[';

     for (std::size_t i = 0; i < buf.size(); ++i) {
          os << buf[i];
          if (i != buf.size() - 1) os << ", ";
     }

     os << ']';

     return os;
}

inline b_uint operator""_bu(const unsigned long long val) {
     if (val > std::numeric_limits<uint32_t>::max())
          throw std::overflow_error("b_uint literal exceeds 32-bit limb");
     return b_uint {static_cast<unsigned int>(val)};
}

}

#endif //KERNELFORGE_B_UINT_H