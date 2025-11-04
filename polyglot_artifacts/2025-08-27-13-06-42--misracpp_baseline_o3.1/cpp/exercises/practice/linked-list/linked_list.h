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

    void clear()
    {
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

    // Deep-copy semantics
    List(const List& other) : head_{nullptr}, tail_{nullptr}, size_{0}
    {
        Node* curr = other.head_;
        while (curr) {
            push(curr->value);
            curr = curr->next;
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            Node* curr = other.head_;
            while (curr) {
                push(curr->value);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Enable move semantics
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List&& other) noexcept
    {
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

    ~List() { clear(); }

    // Adds an element to the end of the list
    void push(const T& value)
    {
        Node* node = new Node(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev  = tail_;
            tail_       = node;
        }
        ++size_;
    }

    // Removes and returns the last element
    T pop()
    {
        if (!tail_) {
            throw std::runtime_error("pop on empty list");
        }
        Node* node = tail_;
        T value    = node->value;

        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else { // list became empty
            head_ = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    // Adds an element to the start of the list
    void unshift(const T& value)
    {
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

    // Removes and returns the first element
    T shift()
    {
        if (!head_) {
            throw std::runtime_error("shift on empty list");
        }
        Node* node = head_;
        T value    = node->value;

        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else { // list became empty
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    // Returns the total number of elements
    std::size_t count() const { return size_; }
    // Alias to match standard container naming convention
    std::size_t size() const { return size_; }

    // Removes the first occurrence of the given value; returns true if removed
    bool erase(const T& value)
    {
        Node* current = head_;
        while (current) {
            if (current->value == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else { // removing head
                    head_ = current->next;
                    if (head_) {
                        head_->prev = nullptr;
                    }
                }

                if (current->next) {
                    current->next->prev = current->prev;
                } else { // removing tail
                    tail_ = current->prev;
                    if (tail_) {
                        tail_->next = nullptr;
                    }
                }

                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false; // value not found
    }
};

}  // namespace linked_list
