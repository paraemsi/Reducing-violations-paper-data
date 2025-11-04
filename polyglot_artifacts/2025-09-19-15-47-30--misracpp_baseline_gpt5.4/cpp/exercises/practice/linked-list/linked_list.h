#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    // Constructors, assignment and destructor
    List() : head_(nullptr), tail_(nullptr), size_(0) {}
    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push(cur->value);
        }
    }
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    // Copy-and-swap assignment (handles both copy and move)
    List& operator=(List other) {
        swap(other);
        return *this;
    }
    ~List() {
        clear();
    }

    // Adds an element to the end of the list
    void push(const T& value) {
        Node* n = new Node(value);
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    // Removes and returns the last element of the list
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* n = tail_;
        T out = std::move(n->value);
        tail_ = n->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        --size_;
        return out;
    }

    // Adds an element to the start of the list
    void unshift(const T& value) {
        Node* n = new Node(value);
        if (!head_) {
            head_ = tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        if (!head_) {
            head_ = tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    // Removes and returns the first element of the list
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        Node* n = head_;
        T out = std::move(n->value);
        head_ = n->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        --size_;
        return out;
    }

    // Removes the first occurrence of value; returns true if removed
    bool erase(const T& value) {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
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

    // Returns the number of elements in the list
    std::size_t count() const noexcept {
        return size_;
    }

private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void swap(List& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }
};

}  // namespace linked_list
