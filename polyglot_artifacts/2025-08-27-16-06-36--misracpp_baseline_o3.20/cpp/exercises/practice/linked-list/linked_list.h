#pragma once

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <utility>      // std::swap

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v, Node* p = nullptr, Node* n = nullptr)
            : value(v), prev(p), next(n) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

    // Utility used by destructor and assignment
    void clear() noexcept {
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

    // Disable copy semantics for simplicity; can be implemented later if needed
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // Move semantics
    List(List&& other) noexcept { *this = std::move(other); }

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

    ~List() { clear(); }

    void push(const T& value) {
        Node* node = new Node(value, tail_, nullptr);
        if (tail_)
            tail_->next = node;
        else
            head_ = node;
        tail_ = node;
        ++size_;
    }

    T pop() {
        if (!tail_)
            throw std::out_of_range("pop on empty list");

        Node* node = tail_;
        T value = node->value;
        tail_ = tail_->prev;
        if (tail_)
            tail_->next = nullptr;
        else
            head_ = nullptr;

        delete node;
        --size_;
        return value;
    }

    void unshift(const T& value) {
        Node* node = new Node(value, nullptr, head_);
        if (head_)
            head_->prev = node;
        else
            tail_ = node;
        head_ = node;
        ++size_;
    }

    T shift() {
        if (!head_)
            throw std::out_of_range("shift on empty list");

        Node* node = head_;
        T value = node->value;
        head_ = head_->next;
        if (head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;

        delete node;
        --size_;
        return value;
    }

    std::size_t count() const noexcept { return size_; }

    bool erase(const T& value) {
        for (Node* curr = head_; curr; curr = curr->next) {
            if (curr->value == value) {
                if (curr->prev)
                    curr->prev->next = curr->next;
                else
                    head_ = curr->next;

                if (curr->next)
                    curr->next->prev = curr->prev;
                else
                    tail_ = curr->prev;

                delete curr;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
