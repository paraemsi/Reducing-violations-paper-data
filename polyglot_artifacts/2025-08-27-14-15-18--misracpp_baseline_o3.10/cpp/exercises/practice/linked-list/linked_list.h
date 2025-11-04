#pragma once

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <utility>      // std::move

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v, Node* p = nullptr, Node* n = nullptr)
            : value(v), prev(p), next(n) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void clear() noexcept {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    // helper used by copy constructor / assignment
    void copy_from(const List& other) {
        for (Node* cur = other.head_; cur; cur = cur->next) {
            push(cur->value);
        }
    }

public:
    List() = default;

    // Deep copy semantics
    List(const List& other) : head_{nullptr}, tail_{nullptr}, size_{0} {
        copy_from(other);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    // Move constructor
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    // Move assignment
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_       = other.head_;
            tail_       = other.tail_;
            size_       = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~List() { clear(); }

    // Adds element to end
    void push(const T& value) {
        Node* node = new Node(value, tail_, nullptr);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_       = node;
        }
        ++size_;
    }

    // Removes and returns last element
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail_;
        T val      = std::move(node->value);
        tail_      = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        --size_;
        return val;
    }

    // Removes and returns first element
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head_;
        T val      = std::move(node->value);
        head_      = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return val;
    }

    // Adds element to start
    void unshift(const T& value) {
        Node* node = new Node(value, nullptr, head_);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            head_->prev = node;
            head_       = node;
        }
        ++size_;
    }

    // Returns total number of elements
    std::size_t count() const noexcept { return size_; }

    // Removes first occurrence of value; returns true if removed
    bool erase(const T& value) {
        Node* current = head_;
        while (current) {
            if (current->value == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }
                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
