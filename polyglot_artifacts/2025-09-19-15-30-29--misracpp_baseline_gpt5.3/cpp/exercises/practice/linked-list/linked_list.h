#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

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

public:
    List() = default;

    ~List() { clear(); }

    List(const List& other) {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push(cur->value);
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            List tmp(other);
            swap(tmp);
        }
        return *this;
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

    void swap(List& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }

    // Adds an element to the end of the list
    void push(const T& value) {
        Node* n = new Node(value);
        n->prev = tail_;
        if (tail_) {
            tail_->next = n;
        } else {
            head_ = n;
        }
        tail_ = n;
        ++size_;
    }

    // Adds an element to the end of the list (move overload)
    void push(T&& value) {
        Node* n = new Node(std::move(value));
        n->prev = tail_;
        if (tail_) {
            tail_->next = n;
        } else {
            head_ = n;
        }
        tail_ = n;
        ++size_;
    }

    // Removes and returns the last element of the list
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty List");
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
        n->next = head_;
        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

    // Adds an element to the start of the list (move overload)
    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        n->next = head_;
        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

    // Removes and returns the first element of the list
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty List");
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

    // Returns the total number of elements in the list
    std::size_t count() const noexcept {
        return size_;
    }

    // Removes the first occurrence of value from the list.
    // Returns true if an element was removed; otherwise false.
    bool erase(const T& value) {
        Node* cur = head_;
        while (cur) {
            if (cur->value == value) {
                Node* prev = cur->prev;
                Node* next = cur->next;

                if (prev) {
                    prev->next = next;
                } else {
                    head_ = next;
                }

                if (next) {
                    next->prev = prev;
                } else {
                    tail_ = prev;
                }

                delete cur;
                --size_;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};

}  // namespace linked_list
