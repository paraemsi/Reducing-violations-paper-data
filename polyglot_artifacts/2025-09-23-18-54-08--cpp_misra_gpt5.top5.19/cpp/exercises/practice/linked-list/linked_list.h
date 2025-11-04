#pragma once

#include <cstddef>          // std::size_t
#include <initializer_list> // std::initializer_list
#include <stdexcept>        // std::out_of_range
#include <utility>          // std::move, std::swap

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept
        : head_(nullptr), tail_(nullptr), size_(0U) {
    }

    List(std::initializer_list<T> init)
        : head_(nullptr), tail_(nullptr), size_(0U) {
        for (const T& v : init) {
            this->push(v);
        }
    }

    List(const List& other)
        : head_(nullptr), tail_(nullptr), size_(0U) {
        this->copy_from(other);
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    ~List() {
        this->clear();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            this->clear();
            this->copy_from(other);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            this->clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    // Adds an element to the end of the list
    void push(const T& value) {
        Node* node = new Node{value, nullptr, nullptr};
        node->prev = tail_;
        node->next = nullptr;

        if ((tail_ != nullptr)) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        size_ = size_ + 1U;
    }

    // Removes and returns the last element of the list
    T pop() {
        if ((tail_ == nullptr)) {
            throw std::out_of_range("pop on empty List");
        }

        Node* node = tail_;
        T value = node->value;

        tail_ = node->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node;
        size_ = size_ - 1U;
        return value;
    }

    // Removes and returns the first element of the list
    T shift() {
        if ((head_ == nullptr)) {
            throw std::out_of_range("shift on empty List");
        }

        Node* node = head_;
        T value = node->value;

        head_ = node->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node;
        size_ = size_ - 1U;
        return value;
    }

    // Adds an element to the start of the list
    void unshift(const T& value) {
        Node* node = new Node{value, nullptr, nullptr};
        node->prev = nullptr;
        node->next = head_;

        if ((head_ != nullptr)) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        size_ = size_ + 1U;
    }

    // Returns the total number of elements in the current list
    std::size_t count() const noexcept {
        return size_;
    }

    // Removes the first occurrence of value from the list
    // Returns true if an element was deleted, false otherwise
    bool erase(const T& value) {
        Node* cur = head_;
        while ((cur != nullptr)) {
            if ((cur->value == value)) {
                Node* prev = cur->prev;
                Node* next = cur->next;

                if ((prev != nullptr)) {
                    prev->next = next;
                } else {
                    head_ = next;
                }

                if ((next != nullptr)) {
                    next->prev = prev;
                } else {
                    tail_ = prev;
                }

                delete cur;
                size_ = size_ - 1U;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept {
        Node* cur = head_;
        while ((cur != nullptr)) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

    void copy_from(const List& other) {
        Node* cur = other.head_;
        while ((cur != nullptr)) {
            this->push(cur->value);
            cur = cur->next;
        }
    }
};

}  // namespace linked_list
