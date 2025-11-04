#pragma once

#include <cstddef>     // std::size_t
#include <stdexcept>   // std::out_of_range
#include <utility>     // std::move

namespace linked_list {

/**
 * A doubly-linked list that stores values of arbitrary type `T`.
 *
 * Supported operations (all O(1) unless otherwise stated):
 *  • push      – append value to the back
 *  • pop       – remove value from the back (throws if empty)
 *  • unshift   – insert value at the front
 *  • shift     – remove value from the front (throws if empty)
 *  • erase     – remove first occurrence of value (O(n))
 *  • count     – number of elements in the list
 */
template <typename T>
class List {
private:
    struct Node {
        T        value;
        Node*    prev{nullptr};
        Node*    next{nullptr};

        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v)      : value(std::move(v)) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    // helper to delete all nodes
    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

public:
    List() = default;
    ~List() { clear(); }

    // disable copy to keep implementation simple
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    // move semantics
    List(List&& other) noexcept { *this = std::move(other); }
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_      = other.head_;
            tail_      = other.tail_;
            size_      = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // number of elements
    std::size_t count() const noexcept { return size_; }

    // push value to back
    void push(const T& value) { push_impl(value); }
    void push(T&& value)      { push_impl(std::move(value)); }

    // unshift value to front
    void unshift(const T& value) { unshift_impl(value); }
    void unshift(T&& value)      { unshift_impl(std::move(value)); }

    // pop from back, throwing if empty
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail_;
        T ret      = std::move(node->value);

        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {  // list became empty
            head_ = nullptr;
        }

        delete node;
        --size_;
        return ret;
    }

    // shift from front, throwing if empty
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head_;
        T ret      = std::move(node->value);

        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {  // list became empty
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return ret;
    }

    // erase first occurrence – returns true if element removed
    bool erase(const T& value) {
        for (Node* cur = head_; cur; cur = cur->next) {
            if (cur->value == value) {
                if (cur->prev) {
                    cur->prev->next = cur->next;
                } else {
                    head_ = cur->next;
                }

                if (cur->next) {
                    cur->next->prev = cur->prev;
                } else {
                    tail_ = cur->prev;
                }

                delete cur;
                --size_;
                return true;
            }
        }
        return false;
    }

private:
    // internal helpers using perfect forwarding
    template <typename U>
    void push_impl(U&& v) {
        Node* node = new Node(std::forward<U>(v));
        node->prev = tail_;
        if (tail_) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    template <typename U>
    void unshift_impl(U&& v) {
        Node* node = new Node(std::forward<U>(v));
        node->next = head_;
        if (head_) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }
};

}  // namespace linked_list
