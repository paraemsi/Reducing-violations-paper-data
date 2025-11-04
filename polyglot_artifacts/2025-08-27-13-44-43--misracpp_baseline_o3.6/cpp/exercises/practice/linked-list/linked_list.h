#pragma once

#include <cstddef>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void copy_from(const List& other) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }

public:
    List() = default;

    List(const List& other) {
        copy_from(other);
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            copy_from(other);
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

    ~List() {
        clear();
    }

    // Adds an element to the end of the list.
    void push(const T& value) {
        Node* node = new Node(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        ++size_;
    }

    // Removes and returns the last element of the list.
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail_;
        T value = node->value;
        tail_ = tail_->prev;
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
    void unshift(const T& value) {
        Node* node = new Node(value);
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
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head_;
        T value = node->value;
        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    // Returns the total number of elements in the list.
    std::size_t count() const {
        return size_;
    }

    // Removes the first occurrence of `value` from the list.
    // Returns true if an element was removed, false otherwise.
    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                if (n->prev) {
                    n->prev->next = n->next;
                } else {
                    head_ = n->next;
                }
                if (n->next) {
                    n->next->prev = n->prev;
                } else {
                    tail_ = n->prev;
                }
                delete n;
                --size_;
                return true;
            }
        }
        return false;
    }

private:
    void clear() {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }
};

}  // namespace linked_list
