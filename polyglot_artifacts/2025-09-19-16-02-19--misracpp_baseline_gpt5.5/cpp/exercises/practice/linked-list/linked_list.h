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

    void clear() noexcept {
        while (head_ != nullptr) {
            Node* n = head_->next;
            delete head_;
            head_ = n;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void copy_from(const List& other) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }

public:
    List() = default;
    ~List() { clear(); }

    List(const List& other) { copy_from(other); }

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
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) {
        Node* n = new Node(value);
        if (tail_ == nullptr) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            n->prev = tail_;
            tail_ = n;
        }
        ++size_;
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        if (tail_ == nullptr) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            n->prev = tail_;
            tail_ = n;
        }
        ++size_;
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop from empty List");
        }
        Node* n = tail_;
        T value = std::move(n->value);
        tail_ = n->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        --size_;
        return value;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        if (head_ == nullptr) {
            head_ = tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        if (head_ == nullptr) {
            head_ = tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty List");
        }
        Node* n = head_;
        T value = std::move(n->value);
        head_ = n->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        --size_;
        return value;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                if (n->prev != nullptr) {
                    n->prev->next = n->next;
                } else {
                    head_ = n->next;
                }
                if (n->next != nullptr) {
                    n->next->prev = n->prev;
                } else {
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
