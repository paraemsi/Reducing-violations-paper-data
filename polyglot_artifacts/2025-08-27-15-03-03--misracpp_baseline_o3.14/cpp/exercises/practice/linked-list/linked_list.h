#pragma once

#include <cstddef>
#include <stdexcept>

namespace linked_list {

/*
 * A templated doubly-linked list.
 *
 * Required interface (see tests):
 *  - void  push(const T& value);   // append value to back
 *  - T     pop();                  // remove & return value from back
 *  - void  unshift(const T& value);// insert value at front
 *  - T     shift();                // remove & return value from front
 *  - std::size_t count() const;    // number of elements
 *  - bool  erase(const T& value);  // remove *first* occurrence of value
 *
 * pop() and shift() throw std::out_of_range on an empty list.
 */
template <typename T>
class List {
private:
    struct Node {
        T     data;
        Node* prev;
        Node* next;

        explicit Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Node*       head_{nullptr};
    Node*       tail_{nullptr};
    std::size_t size_{0};

public:
    List() = default;
    ~List() { clear(); }

    // copy constructor and copy assignment (deep copy)
    List(const List& other)
        : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* cur = other.head_; cur; cur = cur->next) {
            push(cur->data);
        }
    }
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* cur = other.head_; cur; cur = cur->next) {
                push(cur->data);
            }
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
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

    // Add value to the back
    void push(const T& value) {
        Node* n = new Node(value);
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            n->prev     = tail_;
            tail_       = n;
        }
        ++size_;
    }

    // Remove value from the back
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* n = tail_;
        T value = n->data;

        tail_ = n->prev;
        if (tail_)
            tail_->next = nullptr;
        else
            head_ = nullptr;

        delete n;
        --size_;
        return value;
    }

    // Insert value at the front
    void unshift(const T& value) {
        Node* n = new Node(value);
        if (!head_) {
            head_ = tail_ = n;
        } else {
            n->next  = head_;
            head_->prev = n;
            head_    = n;
        }
        ++size_;
    }

    // Remove value from the front
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        Node* n = head_;
        T value = n->data;

        head_ = n->next;
        if (head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;

        delete n;
        --size_;
        return value;
    }

    // Number of elements
    std::size_t count() const { return size_; }

    // Remove first occurrence of value
    bool erase(const T& value) {
        for (Node* cur = head_; cur; cur = cur->next) {
            if (cur->data == value) {
                if (cur->prev)
                    cur->prev->next = cur->next;
                else
                    head_ = cur->next;

                if (cur->next)
                    cur->next->prev = cur->prev;
                else
                    tail_ = cur->prev;

                delete cur;
                --size_;
                return true;
            }
        }
        return false;
    }

private:
    void clear() {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }
};

}  // namespace linked_list
