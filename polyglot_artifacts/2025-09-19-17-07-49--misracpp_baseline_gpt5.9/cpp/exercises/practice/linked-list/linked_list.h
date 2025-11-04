#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
    struct Node;
public:
    List() = default;

    // Copy constructor
    List(const List& other) {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push(cur->value);
        }
    }

    // Move constructor
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // Destructor
    ~List() {
        clear();
    }

    // Copy assignment (copy-and-swap)
    List& operator=(const List& other) {
        if (this != &other) {
            List tmp(other);
            swap(tmp);
        }
        return *this;
    }

    // Move assignment
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // push: adds an element to the end
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

    // pop: removes and returns the last element
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

    // shift: removes and returns the first element
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

    // unshift: adds an element to the start
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

    // count: returns the number of elements
    std::size_t count() const noexcept {
        return size_;
    }

    // erase: removes the first occurrence of value; returns true if removed
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

private:
    struct Node {
        T value;
        Node* prev{nullptr};
        Node* next{nullptr};
        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void clear() {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
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
