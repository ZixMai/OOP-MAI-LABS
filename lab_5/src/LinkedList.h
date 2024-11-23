#pragma once
#include <memory>
#include "CustomIterator.h"
#include "ListNode.h"
#include "CustomMemoryResource.h"

template <typename T, typename alloc>
requires std::is_default_constructible_v<T> && std::is_same_v<std::pmr::polymorphic_allocator<T>, alloc>
class LinkedList {
    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> last;
    size_t size;
    std::pmr::polymorphic_allocator<T> allocator;
    std::shared_ptr<CustomMemoryResource> memory_resource;
    std::pmr::polymorphic_allocator<ListNode<T>> node_allocator;

    public:
        explicit LinkedList(std::pmr::polymorphic_allocator<T> custom_allocator) : size(0), allocator(custom_allocator), memory_resource(new CustomMemoryResource()), node_allocator(memory_resource.get()) {
            ListNode<T>* temp_node_ptr = node_allocator.allocate(1);
            node_allocator.construct(temp_node_ptr);
            head = last = std::shared_ptr<ListNode<T>>(temp_node_ptr, [](ListNode<T>* node_ptr) {});
        }
        explicit LinkedList(std::initializer_list<T> list, std::pmr::polymorphic_allocator<T> custom_allocator) : size(0), allocator(custom_allocator), memory_resource(new CustomMemoryResource()), node_allocator(memory_resource.get()) {
            ListNode<T>* terminate_node_ptr = node_allocator.allocate(1);
            node_allocator.construct(terminate_node_ptr);
            head = last = std::shared_ptr<ListNode<T>>(terminate_node_ptr, [](ListNode<T>* node_ptr) {});
            for (auto & item : list) {
                T* newData = allocator.allocate(1);
                allocator.construct(newData);
                *newData = item;
                ListNode<T>* temp_node_ptr = node_allocator.allocate(1);
                node_allocator.construct(temp_node_ptr);
                auto newNode = std::shared_ptr<ListNode<T>>(temp_node_ptr, [](ListNode<T>* node_ptr) {});
                newNode->data = std::move(std::unique_ptr<T, PolymorphicDeleter<T>>(newData));
                last->next = newNode;
                last = newNode;
                ++size;
            }
        }

        LinkedList(LinkedList& other) : size(0), allocator(other.allocator) {
            ListNode<T>* terminate_node_ptr = node_allocator.allocate(1);
            node_allocator.construct(terminate_node_ptr);
            head = last = std::shared_ptr<ListNode<T>>(terminate_node_ptr, [](ListNode<T>* node_ptr) {});
            for (auto item : other) {
                this->push_back(item);
            }
        }

        LinkedList(LinkedList&& other) noexcept : size(other.size), allocator(other.allocator) {
            head = std::move(other.head);
            last = std::move(other.last);
        }

        LinkedList& operator=(const LinkedList& other) {
            auto copy = LinkedList(other);
            this->head = copy.head;
            this->last = copy.last;

            return *this;
        }

        LinkedList& operator=(LinkedList&& other) noexcept {
            head = std::move(other.head);
            last = std::move(other.last);

            return *this;
        }

        void push_front(const T& value) {
            T* newData = allocator.allocate(1);
            allocator.construct(newData);
            *newData = value;
            ListNode<T>* temp_node_ptr = node_allocator.allocate(1);
            node_allocator.construct(temp_node_ptr);
            auto newNode = std::shared_ptr<ListNode<T>>(temp_node_ptr, [](ListNode<T>* node_ptr) {});
            newNode->data = std::unique_ptr<T, PolymorphicDeleter<T>>(newData);
            newNode->next = head->next;
            head->next = newNode;
            ++size;
        }

        void push_back(const T& value) {
            T* newData = allocator.allocate(1);
            allocator.construct(newData);
            *newData = value;
            ListNode<T>* temp_node_ptr = node_allocator.allocate(1);
            node_allocator.construct(temp_node_ptr);
            auto newNode = std::shared_ptr<ListNode<T>>(temp_node_ptr, [](ListNode<T>* node_ptr) {});
            newNode->data = std::unique_ptr<T, PolymorphicDeleter<T>>(newData);
            last->next = newNode;
            last = newNode;
            ++size;
        }

        T front() {
            if (size == 0) {
                throw std::out_of_range("List is empty");
            }
            return *(head->next->data);
        }

        T back() {
            if (size == 0) {
                throw std::out_of_range("List is empty");
            }
            return *(last->data);
        }

        CustomIterator<T, LinkedList> begin() {
            return CustomIterator<T, LinkedList>(this, 0, this->size, head->next);
        }

        CustomIterator<T, LinkedList> end() {
            return CustomIterator<T, LinkedList>(this, this->size, this->size, last->next);
        }

        void pop_front() {
            if (size > 0) {
                std::allocator_traits<alloc>::destroy(allocator, head->next->data.get());
                allocator.deallocate(head->next->data.get(), 1);
                std::shared_ptr<ListNode<T>> temp;
                if (size == 1) {
                    temp = head->next;
                } else {
                    temp = head->next->next;
                }
                std::allocator_traits<std::pmr::polymorphic_allocator<ListNode<T>>>::destroy(node_allocator, head->next.get());
                node_allocator.deallocate(head->next.get(), 1);
                head->next = temp;
                --size;
            } else {
                throw std::out_of_range("List is empty");
            }
        }

        size_t get_size() const {
            return size;
        }

        size_t is_empty() const {
            return size == 0;
        }

        ~LinkedList() {
            auto first_node = head->next;
            while (first_node != nullptr) {
                auto new_first_node = first_node->next;
                std::allocator_traits<alloc>::destroy(allocator, first_node->data.get());
                allocator.deallocate(first_node->data.get(), 1);
                std::allocator_traits<std::pmr::polymorphic_allocator<ListNode<T>>>::destroy(node_allocator, first_node.get());
                node_allocator.deallocate(first_node.get(), 1);
                first_node = new_first_node;
            }
        }
};