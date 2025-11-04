#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(0U) {}

    ~List() noexcept {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0U) {
        Node* current = other.head_;
        while (current != nullptr) {
            push(current->value);
            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* current = other.head_;
            while (current != nullptr) {
                push(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    void push(const T& value) {
        Node* n = new Node(value);
        if (tail_ == nullptr) {
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        size_ += 1U;
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop from empty list");
        }
        Node* n = tail_;
        T out = std::move(n->value);
        tail_ = n->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        size_ -= 1U;
        return out;
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty list");
        }
        Node* n = head_;
        T out = std::move(n->value);
        head_ = n->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        size_ -= 1U;
        return out;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        if (head_ == nullptr) {
            head_ = n;
            tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        size_ += 1U;
    }

    std::size_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if (current->value == value) {
                Node* prev = current->prev;
                Node* next = current->next;

                if (prev != nullptr) {
                    prev->next = next;
                } else {
                    head_ = next;
                }

                if (next != nullptr) {
                    next->prev = prev;
                } else {
                    tail_ = prev;
                }

                delete current;
                size_ -= 1U;
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        T value;
        Node* prev;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }
};

}  // namespace linked_list
