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

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

    template <typename U>
    void emplace_back_impl(U&& v) {
        Node* n = new Node(std::forward<U>(v));
        n->prev = tail_;
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
    List() = default;

    ~List() { clear(); }

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

    List& operator=(List other) noexcept {
        swap(other);
        return *this;
    }

    void swap(List& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    // Adds an element to the end of the list.
    void push(const T& value) { emplace_back_impl(value); }
    void push(T&& value) { emplace_back_impl(std::move(value)); }

    // Removes and returns the last element of the list.
    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop called on empty List");
        }
        Node* n = tail_;
        T v = std::move(n->value);
        tail_ = n->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        --size_;
        return v;
    }

    // Removes and returns the first element of the list.
    T shift() {
        if (!head_) {
            throw std::out_of_range("shift called on empty List");
        }
        Node* n = head_;
        T v = std::move(n->value);
        head_ = n->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        --size_;
        return v;
    }

    // Adds an element to the start of the list.
    void unshift(const T& value) { emplace_front_impl(value); }
    void unshift(T&& value) { emplace_front_impl(std::move(value)); }

    // Returns the total number of elements in the list.
    std::size_t count() const noexcept { return size_; }

    // Removes the first occurrence of value from the list. Returns true if removed.
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

    // Clears the entire list.
    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }
};

}  // namespace linked_list
