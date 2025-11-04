#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List final {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

public:
    List() = default;
    ~List() { clear(); }

    // Disable copy semantics
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // Enable move semantics
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_  = other.head_;
            tail_  = other.tail_;
            size_  = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Adds an element to the end of the list.
    void push(T value) {
        Node* node = new Node(std::move(value));
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
            throw std::out_of_range("pop called on empty List");
        }
        Node* node = tail_;
        T value = std::move(node->value);
        tail_ = node->prev;
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
    void unshift(T value) {
        Node* node = new Node(std::move(value));
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
            throw std::out_of_range("shift called on empty List");
        }
        Node* node = head_;
        T value = std::move(node->value);
        head_ = node->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    // Returns the number of elements in the list.
    std::size_t count() const noexcept { return size_; }

    // Removes the first occurrence of value from the list.
    // Returns true if an element was removed, false otherwise.
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
