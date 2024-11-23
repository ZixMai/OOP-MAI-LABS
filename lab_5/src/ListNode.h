#pragma once
#include <memory>

template<class T>
struct PolymorphicDeleter {
    void operator()(T * ptr) const {
    }
};

template <typename T>
struct ListNode {
    std::unique_ptr<T, PolymorphicDeleter<T>> data;
    std::shared_ptr<ListNode> next;
};
