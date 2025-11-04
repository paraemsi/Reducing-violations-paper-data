#pragma once

#include <cstdint>   // fixed-width integral types
#include <stdexcept> // std::out_of_range

namespace linked_list {

/*
 * Doubly linked list implementation that satisfies the interface required by
 * `linked_list_test.cpp`.
 *
 * All operations run in O(1) except `erase`, which is O(n) in the worst case.
 *
 * MISRA-C++  compliance notes:
 *  - Uses std::uint64_t for the size counter – a fixed-width unsigned type.
 *  - All `if` / `else` bodies are compound statements.
 *  - Parentheses are used to clarify operator precedence where needed.
 */
template <typename T>
class List {
private:
    struct Node {
        T       data;
        Node*   prev;
        Node*   next;

        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node*        head_;
    Node*        tail_;
    std::uint64_t size_;

    void unlink_node(Node* node) noexcept
    {
        if (node == nullptr) {
            return;
        }

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }

        --size_;
    }

    void delete_node(Node* node) noexcept
    {
        delete node;
    }

    void clear() noexcept
    {
        Node* current = head_;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete_node(current);
            current = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(0U) {}

    ~List()
    {
        clear();
    }

    // Non-copyable but movable
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept :
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            head_       = other.head_;
            tail_       = other.tail_;
            size_       = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    // Add element to end
    void push(const T& value)
    {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            tail_->next = node;
            node->prev  = tail_;
            tail_       = node;
        }
        ++size_;
    }

    // Remove and return last element
    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty List");
        }

        Node* node = tail_;
        T     val  = node->data;
        unlink_node(node);
        delete_node(node);
        return val;
    }

    // Add element to front
    void unshift(const T& value)
    {
        Node* node = new Node(value);
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    // Remove and return first element
    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty List");
        }

        Node* node = head_;
        T     val  = node->data;
        unlink_node(node);
        delete_node(node);
        return val;
    }

    // Remove first occurrence of value; return true if erased
    bool erase(const T& value)
    {
        Node* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
                unlink_node(current);
                delete_node(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Number of elements in list
    [[nodiscard]] std::uint64_t count() const noexcept
    {
        return size_;
    }
};

} // namespace linked_list
