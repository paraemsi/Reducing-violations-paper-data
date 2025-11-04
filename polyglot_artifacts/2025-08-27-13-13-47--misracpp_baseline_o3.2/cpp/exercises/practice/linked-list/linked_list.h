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

    void remove_node(Node* node) {
        if (!node) return;

        if (node->prev)
            node->prev->next = node->next;
        else
            head_ = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail_ = node->prev;

        delete node;
        --size_;
    }

public:
    List() = default;

    // deep copy
    List(const List& other) {
        for (Node* cur = other.head_; cur; cur = cur->next) {
            push(cur->value);
        }
    }
    List& operator=(const List& other) {
        if (this == &other) return *this;
        clear();
        for (Node* cur = other.head_; cur; cur = cur->next) {
            push(cur->value);
        }
        return *this;
    }

    // move
    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
    List& operator=(List&& other) noexcept {
        if (this == &other) return *this;
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    ~List() { clear(); }

    void clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    std::size_t count() const { return size_; }

    // push back
    void push(const T& value) {
        Node* node = new Node(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        ++size_;
    }
    void push(T&& value) {
        Node* node = new Node(std::move(value));
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        ++size_;
    }

    // pop back
    T pop() {
        if (!tail_) throw std::out_of_range("pop from empty list");
        T val = std::move(tail_->value);
        remove_node(tail_);
        return val;
    }

    // push front
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
    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        if (!head_) {
            head_ = tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    // pop front
    T shift() {
        if (!head_) throw std::out_of_range("shift from empty list");
        T val = std::move(head_->value);
        remove_node(head_);
        return val;
    }

    // erase first occurrence of value
    bool erase(const T& value) {
        for (Node* cur = head_; cur; cur = cur->next) {
            if (cur->value == value) {
                remove_node(cur);
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
