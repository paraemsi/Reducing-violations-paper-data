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
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

public:
    // Constructors, destructor, and assignment
    List() = default;

    ~List() {
        clear();
    }

    List(const List& other) {
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

    List& operator=(List other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(List& a, List& b) noexcept {
        using std::swap;
        swap(a.head_, b.head_);
        swap(a.tail_, b.tail_);
        swap(a.size_, b.size_);
    }

    // Capacity
    std::size_t count() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    // Modifiers
    void push(const T& value) {
        Node* n = new Node(value);
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

    void push(T&& value) {
        Node* n = new Node(std::move(value));
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

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop from empty List");
        }

        Node* n = tail_;
        T out = std::move(n->value);

        tail_ = n->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete n;
        --size_;
        return out;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        n->next = head_;
        n->prev = nullptr;

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
        n->prev = nullptr;

        if (head_) {
            head_->prev = n;
        } else {
            tail_ = n;
        }
        head_ = n;
        ++size_;
    }

    T shift() {
        if (empty()) {
            throw std::out_of_range("shift from empty List");
        }

        Node* n = head_;
        T out = std::move(n->value);

        head_ = n->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete n;
        --size_;
        return out;
    }

    // Remove first occurrence of value. Returns true if removed.
    bool erase(const T& value) {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
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

private:
    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }
};

}  // namespace linked_list
