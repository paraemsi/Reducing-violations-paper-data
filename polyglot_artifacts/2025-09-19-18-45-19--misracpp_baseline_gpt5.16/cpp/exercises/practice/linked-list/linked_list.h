#pragma once

#include <cstddef>
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

        template <typename U>
        explicit Node(U&& v) : value(std::forward<U>(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void clear() noexcept {
        while (head_ != nullptr) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    template <typename U>
    void emplace_back_impl(U&& v) {
        Node* n = new Node(std::forward<U>(v));
        n->prev = tail_;
        n->next = nullptr;

        if (tail_) {
            tail_->next = n;
        } else {
            head_ = n;
        }
        tail_ = n;
        ++size_;
    }

    template <typename U>
    void emplace_front_impl(U&& v) {
        Node* n = new Node(std::forward<U>(v));
        n->prev = nullptr;
        n->next = head_;

        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

public:
    // Constructors / Assignment
    List() noexcept = default;

    ~List() {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push(cur->value);
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
                push(cur->value);
            }
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
            other.size_ = 0;
        }
        return *this;
    }

    // Capacity
    std::size_t count() const noexcept {
        return size_;
    }

    // Modifiers
    void push(const T& value) {
        emplace_back_impl(value);
    }

    void push(T&& value) {
        emplace_back_impl(std::move(value));
    }

    void unshift(const T& value) {
        emplace_front_impl(value);
    }

    void unshift(T&& value) {
        emplace_front_impl(std::move(value));
    }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* n = tail_;
        T ret = std::move(n->value);

        tail_ = n->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete n;
        --size_;
        return ret;
    }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        Node* n = head_;
        T ret = std::move(n->value);

        head_ = n->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete n;
        --size_;
        return ret;
    }

    bool erase(const T& value) {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            if (cur->value == value) {
                Node* prev = cur->prev;
                Node* next = cur->next;

                if (prev) {
                    prev->next = next;
                } else {
                    head_ = next;
                }

                if (next) {
                    next->prev = prev;
                } else {
                    tail_ = prev;
                }

                delete cur;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
