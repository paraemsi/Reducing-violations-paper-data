#pragma once

#include <cstddef>    // std::size_t
#include <stdexcept>  // std::out_of_range
#include <utility>    // std::move, std::forward

namespace linked_list {

/**
 * A simple doubly–linked list implementation.
 *
 * The class is fully implemented in the header so that all template code is
 * visible to translation units that include it.
 */
template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        template <typename U>
        explicit Node(U&& v)
            : value(std::forward<U>(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    // Helper that deletes all nodes.
    void clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

public:
    List() = default;

    ~List() { clear(); }

    // Disable copying for simplicity; can be added if required.
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    // Allow move semantics.
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Adds an element to the end of the list.
    template <typename U>
    void push(U&& value) {
        Node* node = new Node(std::forward<U>(value));
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev  = tail_;
            tail_       = node;
        }
        ++size_;
    }

    // Removes and returns the last element of the list.
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop() called on empty list");
        }
        Node* node = tail_;
        T value    = std::move(node->value);
        tail_      = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    // Adds an element to the start of the list.
    template <typename U>
    void unshift(U&& value) {
        Node* node = new Node(std::forward<U>(value));
        if (!head_) {
            head_ = tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    // Removes and returns the first element of the list.
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift() called on empty list");
        }
        Node* node = head_;
        T value    = std::move(node->value);
        head_      = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    // Returns the number of elements currently stored.
    std::size_t count() const noexcept { return size_; }
    // STL-style alias
    std::size_t size() const noexcept { return size_; }

    /**
     * Removes the first occurrence of `value` from the list.
     *
     * @return true if an element was removed, false otherwise.
     */
    bool erase(const T& value) {
        for (Node* node = head_; node; node = node->next) {
            if (node->value == value) {
                if (node->prev) {
                    node->prev->next = node->next;
                } else {
                    head_ = node->next;
                }
                if (node->next) {
                    node->next->prev = node->prev;
                } else {
                    tail_ = node->prev;
                }
                delete node;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
