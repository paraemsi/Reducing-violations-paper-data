#pragma once
#include <cstddef>   // for std::size_t
#include <stdexcept> // for std::out_of_range
#include <utility>   // for std::swap

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
        while (size_ != 0) {
            pop();
        }
    }

    void detach(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }

        delete node;
        --size_;
    }

    void swap(List& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

public:
    List() = default;

    List(const List& other) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(List other) {
        swap(other);
        return *this;
    }

    ~List() {
        clear();
    }

    void push(const T& value) {
        Node* n = new Node(value);
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            n->prev = tail_;
            tail_ = n;
        }
        ++size_;
    }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop on empty List");
        }
        T value = tail_->value;
        Node* prev = tail_->prev;
        delete tail_;
        tail_ = prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        --size_;
        return value;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        if (!head_) {
            head_ = tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift on empty List");
        }
        T value = head_->value;
        Node* next = head_->next;
        delete head_;
        head_ = next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        --size_;
        return value;
    }

    std::size_t count() const {
        return size_;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                detach(n);
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
