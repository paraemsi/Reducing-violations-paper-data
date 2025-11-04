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
        Node* current = head_;
        while (current) {
            Node* tmp = current->next;
            delete current;
            current = tmp;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void copy_from(const List& other) {
        for (Node* n = other.head_; n; n = n->next) {
            push(n->value);
        }
    }

public:
    // Constructors / assignment
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

    // Capacity
    std::size_t count() const noexcept {
        return size_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    // Modifiers
    void push(const T& value) {
        Node* node = new Node(value);
        if (tail_) {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        } else {          // first element
            head_ = tail_ = node;
        }
        ++size_;
    }

    void push(T&& value) {
        Node* node = new Node(std::move(value));
        if (tail_) {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        } else {
            head_ = tail_ = node;
        }
        ++size_;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop() called on empty List");
        }
        Node* node = tail_;
        T val = std::move(node->value);
        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {          // list became empty
            head_ = nullptr;
        }
        delete node;
        --size_;
        return val;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        if (head_) {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        } else {
            head_ = tail_ = node;
        }
        ++size_;
    }

    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        if (head_) {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        } else {
            head_ = tail_ = node;
        }
        ++size_;
    }

    T shift() {
        if (empty()) {
            throw std::out_of_range("shift() called on empty List");
        }
        Node* node = head_;
        T val = std::move(node->value);
        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {          // list became empty
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return val;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n; n = n->next) {
            if (n->value == value) {
                if (n->prev) {
                    n->prev->next = n->next;
                } else {           // n is head_
                    head_ = n->next;
                }
                if (n->next) {
                    n->next->prev = n->prev;
                } else {           // n is tail_
                    tail_ = n->prev;
                }
                delete n;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
