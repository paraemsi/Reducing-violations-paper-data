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
        Node* prev{nullptr};
        Node* next{nullptr};

        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void clear() noexcept {
        while (head_) {
            Node* nxt = head_->next;
            delete head_;
            head_ = nxt;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void copy_from(const List& other) {
        for (Node* cur = other.head_; cur; cur = cur->next) {
            push(cur->value);
        }
    }

public:
    List() = default;

    List(const List& other) {
        copy_from(other);
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
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

    ~List() {
        clear();
    }

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) {
        Node* n = new Node(value);
        n->prev = tail_;
        if (tail_) {
            tail_->next = n;
        } else {
            head_ = n;
        }
        tail_ = n;
        ++size_;
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        n->prev = tail_;
        if (tail_) {
            tail_->next = n;
        } else {
            head_ = n;
        }
        tail_ = n;
        ++size_;
    }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop on empty list");
        }
        Node* n = tail_;
        T val = std::move(n->value);
        tail_ = n->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        --size_;
        return val;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        n->next = head_;
        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        n->next = head_;
        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift on empty list");
        }
        Node* n = head_;
        T val = std::move(n->value);
        head_ = n->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        --size_;
        return val;
    }

    bool erase(const T& value) {
        for (Node* cur = head_; cur; cur = cur->next) {
            if (cur->value == value) {
                if (cur->prev) {
                    cur->prev->next = cur->next;
                } else {
                    head_ = cur->next;
                }
                if (cur->next) {
                    cur->next->prev = cur->prev;
                } else {
                    tail_ = cur->prev;
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
