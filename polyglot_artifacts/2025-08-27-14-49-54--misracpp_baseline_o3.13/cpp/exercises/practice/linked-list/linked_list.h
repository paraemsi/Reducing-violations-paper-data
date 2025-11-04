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
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

public:
    List() = default;

    ~List() noexcept { clear(); }

    // Copy semantics – perform deep copy
    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* cur = other.head_; cur; cur = cur->next) {
            push(cur->value);
        }
    }
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* cur = other.head_; cur; cur = cur->next) {
                push(cur->value);
            }
        }
        return *this;
    }

    // Enable move semantics
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
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

    void push(const T& value) {
        Node* node = new Node(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev   = tail_;
            tail_        = node;
        }
        ++size_;
    }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail_;
        T value    = node->value;
        tail_      = tail_->prev;
        if (tail_)
            tail_->next = nullptr;
        else
            head_ = nullptr;
        delete node;
        --size_;
        return value;
    }

    void unshift(const T& value) {
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

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head_;
        T value    = node->value;
        head_      = head_->next;
        if (head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;
        delete node;
        --size_;
        return value;
    }

    std::size_t count() const { return size_; }

    bool erase(const T& value) {
        for (Node* cur = head_; cur; cur = cur->next) {
            if (cur->value == value) {
                if (cur->prev)
                    cur->prev->next = cur->next;
                else
                    head_ = cur->next;

                if (cur->next)
                    cur->next->prev = cur->prev;
                else
                    tail_ = cur->prev;

                delete cur;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
