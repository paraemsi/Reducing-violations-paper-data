#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

// Doubly linked list implementation
template <typename T>
class List {
private:
    struct Node {
        T value;
        Node *prev{nullptr};
        Node *next{nullptr};

        explicit Node(const T &val) : value(val) {}
    };

    Node *head_{nullptr};
    Node *tail_{nullptr};
    std::size_t size_{0};

public:
    List() = default;

    // Disable copy semantics for simplicity (can be added later)
    List(const List &)            = delete;
    List &operator=(const List &) = delete;

    // Move semantics
    List(List &&other) noexcept { move_from(std::move(other)); }

    List &operator=(List &&other) noexcept {
        if (this != &other) {
            clear();
            move_from(std::move(other));
        }
        return *this;
    }

    ~List() { clear(); }

    // Adds an element to the end
    void push(const T &value) {
        Node *node = new Node(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev  = tail_;
            tail_       = node;
        }
        ++size_;
    }

    // Removes and returns the last element
    T pop() {
        if (!tail_) throw std::out_of_range("pop on empty list");

        Node *node = tail_;
        T   value  = node->value;
        tail_      = tail_->prev;
        if (tail_)
            tail_->next = nullptr;
        else
            head_ = nullptr;

        delete node;
        --size_;
        return value;
    }

    // Adds an element to the start
    void unshift(const T &value) {
        Node *node = new Node(value);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    // Removes and returns the first element
    T shift() {
        if (!head_) throw std::out_of_range("shift on empty list");

        Node *node = head_;
        T   value  = node->value;
        head_      = head_->next;
        if (head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;

        delete node;
        --size_;
        return value;
    }

    // Returns current number of elements
    std::size_t count() const noexcept { return size_; }

    // Erases first occurrence of value, returns true if erased
    bool erase(const T &value) {
        for (Node *cur = head_; cur; cur = cur->next) {
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

private:
    void clear() noexcept {
        while (head_) {
            Node *next = head_->next;
            delete head_;
            head_ = next;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void move_from(List &&other) noexcept {
        head_       = other.head_;
        tail_       = other.tail_;
        size_       = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
};

}  // namespace linked_list
