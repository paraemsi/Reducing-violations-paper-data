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

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    void link_at_end(Node* n) noexcept {
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

    void link_at_start(Node* n) noexcept {
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

    void remove_node(Node* n) noexcept {
        Node* prev = n->prev;
        Node* next = n->next;

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

        delete n;
        --size_;
    }

    void clear() noexcept {
        while (head_) {
            remove_node(head_);
        }
    }

public:
    List() = default;

    ~List() { clear(); }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* n = other.head_; n; n = n->next) {
            push(n->value);
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List other) {
        swap(other);
        return *this;
    }

    void swap(List& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) {
        Node* n = new Node(value);
        link_at_end(n);
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        link_at_end(n);
    }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty list");
        }
        T value = std::move(tail_->value);
        remove_node(tail_);
        return value;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        link_at_start(n);
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        link_at_start(n);
    }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty list");
        }
        T value = std::move(head_->value);
        remove_node(head_);
        return value;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n; n = n->next) {
            if (n->value == value) {
                remove_node(n);
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
