//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#include <kernelforge/runtime/Runtime.h>

using namespace KernelForge;


Runtime::Runtime() {
    this->queue_ = std::make_shared<sycl::queue>();
    this->b_uint_manager_ = std::make_shared<numeric::BUIntManager>(this->queue_);
}

Runtime &Runtime::instance() {
    static Runtime runtime;
    return runtime;
}

std::shared_ptr<sycl::queue> Runtime::get_queue() {
    return this->queue_;
}


std::shared_ptr<numeric::BUIntManager> Runtime::get_b_uint_manager() {
    return this->b_uint_manager_;
}

void Runtime::shutdown() {

    queue_->wait_and_throw();

    b_uint_manager_->release_all_data();

    queue_.reset();
    b_uint_manager_.reset();

}

Runtime::~Runtime() {
}
