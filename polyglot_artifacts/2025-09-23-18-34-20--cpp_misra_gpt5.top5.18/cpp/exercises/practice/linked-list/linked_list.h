#pragma once

#include <cstddef>
#include <cstdint>
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

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear_internal() noexcept {
        Node* curr = head_;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0);
    }

public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0)) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0)) {
        Node* n = other.head_;
        while (n != nullptr) {
            push(n->value);
            n = n->next;
        }
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0);
    }

    ~List() noexcept {
        clear_internal();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear_internal();
            Node* n = other.head_;
            while (n != nullptr) {
                push(n->value);
                n = n->next;
            }
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear_internal();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = static_cast<std::size_t>(0);
        }
        return *this;
    }

    void push(const T& value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ += static_cast<std::size_t>(1);
    }

    T pop() {
        if (size_ == static_cast<std::size_t>(0)) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail_;
        T ret = std::move(node->value);
        tail_ = node->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        size_ -= static_cast<std::size_t>(1);
        return ret;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ += static_cast<std::size_t>(1);
    }

    T shift() {
        if (size_ == static_cast<std::size_t>(0)) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head_;
        T ret = std::move(node->value);
        head_ = node->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        size_ -= static_cast<std::size_t>(1);
        return ret;
    }

    std::size_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* n = head_;
        while (n != nullptr) {
            if (n->value == value) {
                if (n->prev != nullptr) {
                    n->prev->next = n->next;
                } else {
                    head_ = n->next;
                }
                if (n->next != nullptr) {
                    n->next->prev = n->prev;
                } else {
                    tail_ = n->prev;
                }
                delete n;
                size_ -= static_cast<std::size_t>(1);
                return true;
            }
            n = n->next;
        }
        return false;
    }
};

}  // namespace linked_list
