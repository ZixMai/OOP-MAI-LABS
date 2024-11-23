#pragma once
#include <memory_resource>
#include <vector>
#include <memory>
#include <algorithm>

class Block {
    size_t offset {0};
    size_t size {0};

    public:
        Block() = default;
        Block(size_t offset, size_t size) : offset(offset), size(size) {}

        Block(const Block& block) {
            offset = block.offset;
            size = block.size;
        }
        Block(Block&& block) noexcept {
            offset = block.offset;
            size = block.size;
        }
        Block& operator=(const Block& block) = default;
        Block& operator=(Block&& block) noexcept {
            offset = block.offset;
            size = block.size;
            return *this;
        }

        size_t get_offset() const { return offset; }
        size_t get_size() const { return size; }

        ~Block() = default;

        bool operator==(const Block& other) const {
            return offset == other.offset && size == other.size;
        }
};

class CustomMemoryResource : public std::pmr::memory_resource
{
    static constexpr size_t max_size{600};
    char buffer[max_size];
    std::vector<Block> used_blocks;

public:
    void *do_allocate(size_t bytes, size_t alignment) override
    {
        size_t new_offset = 0;

        for (const Block& b: used_blocks) {
            if (b.get_offset() - new_offset + 1 >= bytes) break;
            new_offset = b.get_offset() + b.get_size() + 1;
        }
        if (new_offset + bytes >= max_size) throw std::bad_alloc();

        used_blocks.emplace_back(new_offset, bytes);
        std::sort(used_blocks.begin(), used_blocks.end(), [](auto & lhv, auto & rhv) { return lhv.get_offset() <= rhv.get_offset(); });

        return buffer + new_offset;
    }

    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override
    {
        for (size_t i=0; i < used_blocks.size(); ++i)
            if (ptr == buffer + used_blocks[i].get_offset()) {
                used_blocks.erase(used_blocks.begin() + i);
                return;
            }
        throw std::logic_error("Can't free unused memory");
    }

    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override
    {
        return this == &other;
    }

    std::vector<Block> get_used_blocks() {
        return used_blocks;
    }
};