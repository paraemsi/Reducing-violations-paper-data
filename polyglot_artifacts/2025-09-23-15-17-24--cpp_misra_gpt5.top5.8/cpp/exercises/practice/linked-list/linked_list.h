#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {
        copy_from(other);
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            List tmp(other);
            std::swap(head_, tmp.head_);
            std::swap(tail_, tmp.tail_);
            std::swap(size_, tmp.size_);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }

    ~List() {
        clear();
    }

    void push(const T& value) {
        Node* node = new Node(value);
        node->prev = tail_;
        node->next = nullptr;

        if (tail_ != nullptr) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    T pop() {
        if (size_ == static_cast<std::size_t>(0U)) {
            throw std::underflow_error("pop on empty List");
        }

        Node* node = tail_;
        T out = node->value;

        Node* prev = node->prev;
        if (prev != nullptr) {
            prev->next = nullptr;
        } else {
            head_ = nullptr;
        }
        tail_ = prev;

        delete node;
        size_ = size_ - static_cast<std::size_t>(1U);
        return out;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        node->prev = nullptr;
        node->next = head_;

        if (head_ != nullptr) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    T shift() {
        if (size_ == static_cast<std::size_t>(0U)) {
            throw std::underflow_error("shift on empty List");
        }

        Node* node = head_;
        T out = node->value;

        Node* next = node->next;
        if (next != nullptr) {
            next->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        head_ = next;

        delete node;
        size_ = size_ - static_cast<std::size_t>(1U);
        return out;
    }

    std::size_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* cur = head_;
        while (cur != nullptr) {
            if (cur->value == value) {
                Node* prev = cur->prev;
                Node* next = cur->next;

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

                delete cur;
                size_ = size_ - static_cast<std::size_t>(1U);
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

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept {
        Node* cur = head_;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

    void copy_from(const List& other) {
        Node* cur = other.head_;
        while (cur != nullptr) {
            push(cur->value);
            cur = cur->next;
        }
    }
};

}  // namespace linked_list
