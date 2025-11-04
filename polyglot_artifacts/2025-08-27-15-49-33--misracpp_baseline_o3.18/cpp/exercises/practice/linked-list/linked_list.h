#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <class T>
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

public:
    List() = default;

    List(const List& other) : List() {
        for (Node* node = other.head_; node; node = node->next) {
            push(node->value);
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List other) {
        swap(other);
        return *this;
    }

    ~List() { clear(); }

    void swap(List& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    // Adds an element to the end of the list.
    void push(const T& value) {
        Node* node = new Node(value);
        node->prev = tail_;
        if (tail_) {
            tail_->next = node;
        } else {
            head_ = node;  // first node
        }
        tail_ = node;
        ++size_;
    }

    // Removes and returns the last element of the list.
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty List");
        }
        Node* node = tail_;
        T value = std::move(node->value);
        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;  // list became empty
        }
        delete node;
        --size_;
        return value;
    }

    // Adds an element to the start of the list.
    void unshift(const T& value) {
        Node* node = new Node(value);
        node->next = head_;
        if (head_) {
            head_->prev = node;
        } else {
            tail_ = node;  // first node
        }
        head_ = node;
        ++size_;
    }

    // Removes and returns the first element of the list.
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty List");
        }
        Node* node = head_;
        T value = std::move(node->value);
        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;  // list became empty
        }
        delete node;
        --size_;
        return value;
    }

    // Removes the first occurrence of `value`. Returns true if removed.
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

    // Returns the number of elements in the list.
    std::size_t count() const { return size_; }
};

}  // namespace linked_list
