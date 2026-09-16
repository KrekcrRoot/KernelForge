//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#ifndef KERNELFORGE_RUNTIME_H
#define KERNELFORGE_RUNTIME_H

#include <kernelforge/numeric/b_uint/b_uint_manager.h>
#include <sycl/sycl.hpp>
#include <memory>

namespace KernelForge {

class Runtime {

public:

    static Runtime& instance();

    std::shared_ptr<numeric::BUIntManager> get_b_uint_manager();
    std::shared_ptr<sycl::queue> get_queue();


    void shutdown();

    ~Runtime();

private:

    Runtime();

    std::shared_ptr<sycl::queue> queue_;
    std::shared_ptr<numeric::BUIntManager> b_uint_manager_;


};

}

#endif //KERNELFORGE_RUNTIME_H