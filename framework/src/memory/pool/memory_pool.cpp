//
// Created by /<R3/<(RR00T on 13.09.2026.
//

#include <ranges>
#include <kernelforge/memory/pool/memory_pool.h>
#include <kernelforge/runtime/Runtime.h>

using namespace KernelForge::memory;

namespace {
    constexpr std::size_t align_up(const std::size_t value, const std::size_t alignment) noexcept {
        return (value + alignment - 1) & ~(alignment - 1);
    }
}

MemoryPool::MemoryPool() {}


Allocation MemoryPool::allocate(
    const std::size_t bytes,
    const std::size_t alignment
) {


    Allocation allocation;

    Chunk* selected_chunk = nullptr;
    uint32_t selected_chunk_id = 0;

    for (auto& [chunk_id, chunk] : chunks_) {

        const std::size_t aligned = align_up(chunk.used, alignment);

        if (chunk.capacity - aligned >= bytes) {
            selected_chunk = &chunk;
            selected_chunk_id = chunk_id;
            break;
        }

    }

    if (!selected_chunk) {
        // Create new chunk

        Chunk new_chunk;
        new_chunk.capacity = std::max(chunk_size_, bytes);

        void *ptr = sycl::malloc_device(new_chunk.capacity, *this->queue_);
        new_chunk.data = ptr;

        auto [it, success] = chunks_.emplace(next_chunk_id_, new_chunk);

        if (!success)
            throw std::runtime_error("Chunk wasn't created");

        selected_chunk_id = it->first;
        selected_chunk = &it->second;

        chunk_size_ = new_chunk.capacity * 2;
        ++next_chunk_id_;

    }

    const std::size_t aligned_offset = align_up(selected_chunk->used, alignment);

    allocation.chunk = selected_chunk_id;
    allocation.offset = aligned_offset;
    allocation.capacity = bytes;

    selected_chunk->used = aligned_offset + bytes;

    return allocation;

}

void MemoryPool::deallocate(const Allocation &allocation) {

}

void* MemoryPool::resolve(const Allocation& allocation) {

    const auto it = chunks_.find(allocation.chunk);

    if (it == chunks_.end())
        return nullptr;

    const Chunk& chunk = it->second;

    return static_cast<std::byte*>(chunk.data) + allocation.offset;

}

void MemoryPool::release_all_chunks() {

    for (const auto &chunk: chunks_ | std::views::values) {

        if (chunk.data) {
            std::cout << "trying to free memory " << chunk.capacity << "\n";
            sycl::free(chunk.data, *queue_);
        }

    }

    chunks_.clear();

}
