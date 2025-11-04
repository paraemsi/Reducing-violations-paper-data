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
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear_nodes() noexcept {
        Node* cur = head_;
        while ((cur != nullptr)) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0);
    }

public:
    using size_type = std::size_t;

    List() : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0)) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0)) {
        Node* cur = other.head_;
        while ((cur != nullptr)) {
            push(cur->value);
            cur = cur->next;
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0);
    }

    ~List() {
        clear_nodes();
    }

    List& operator=(const List& other) {
        if ((this != &other)) {
            clear_nodes();
            Node* cur = other.head_;
            while ((cur != nullptr)) {
                push(cur->value);
                cur = cur->next;
            }
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if ((this != &other)) {
            clear_nodes();
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
        Node* n = new Node(value);
        if ((tail_ == nullptr)) {
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        size_ = (size_ + static_cast<std::size_t>(1));
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        if ((tail_ == nullptr)) {
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        size_ = (size_ + static_cast<std::size_t>(1));
    }

    T pop() {
        if ((tail_ == nullptr)) {
            throw std::out_of_range("pop from empty list");
        }
        Node* n = tail_;
        T out = std::move(n->value);
        tail_ = n->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        size_ = (size_ - static_cast<std::size_t>(1));
        return out;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        if ((head_ == nullptr)) {
            head_ = n;
            tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        size_ = (size_ + static_cast<std::size_t>(1));
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        if ((head_ == nullptr)) {
            head_ = n;
            tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        size_ = (size_ + static_cast<std::size_t>(1));
    }

    T shift() {
        if ((head_ == nullptr)) {
            throw std::out_of_range("shift from empty list");
        }
        Node* n = head_;
        T out = std::move(n->value);
        head_ = n->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        size_ = (size_ - static_cast<std::size_t>(1));
        return out;
    }

    size_type count() const noexcept {
        return size_;
    }

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
                size_ = (size_ - static_cast<std::size_t>(1));
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};

}  // namespace linked_list
