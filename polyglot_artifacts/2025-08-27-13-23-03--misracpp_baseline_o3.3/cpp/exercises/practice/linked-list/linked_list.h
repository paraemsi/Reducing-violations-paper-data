#pragma once
#include <cstddef>   // for std::size_t
#include <stdexcept> // for std::out_of_range
#include <utility>   // for std::move (future-proof)

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev{nullptr};
        Node* next{nullptr};

        explicit Node(const T& v) : value(v) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

public:
    List() = default;

    // Disable copy semantics (deep-copy could be implemented if needed)
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    // Enable move semantics
    List(List&& other) noexcept
        : head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
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

    ~List() { clear(); }

    // Add element to end
    void push(const T& value) { insert_back(value); }

    // Remove and return last element
    T pop() {
        if (!tail_) {
            throw std::out_of_range{"pop from empty list"};
        }
        Node* node = tail_;
        T     val  = node->value;

        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node;
        --size_;
        return val;
    }

    // Remove and return first element
    T shift() {
        if (!head_) {
            throw std::out_of_range{"shift from empty list"};
        }
        Node* node = head_;
        T     val  = node->value;

        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return val;
    }

    // Add element to front
    void unshift(const T& value) { insert_front(value); }

    // Return number of elements
    std::size_t count() const { return size_; }

    // Remove first occurrence of value
    void erase(const T& value) {
        Node* current = head_;
        while (current) {
            if (current->value == value) {
                // Re-link neighbors
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
                return;
            }
            current = current->next;
        }
    }

private:
    void insert_back(const T& value) {
        Node* node = new Node{value};
        node->prev = tail_;
        if (tail_) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    void insert_front(const T& value) {
        Node* node = new Node{value};
        node->next = head_;
        if (head_) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }

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
