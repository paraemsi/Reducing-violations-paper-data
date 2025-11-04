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

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void copy_from(const List& other) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            emplace_back(n->value);
        }
    }

    template <typename U>
    void emplace_back(U&& v) {
        Node* node = new Node(std::forward<U>(v));
        node->prev = tail_;
        node->next = nullptr;

        if (tail_) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    template <typename U>
    void emplace_front(U&& v) {
        Node* node = new Node(std::forward<U>(v));
        node->prev = nullptr;
        node->next = head_;

        if (head_) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~List() { clear(); }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) { copy_from(other); }
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
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

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) { emplace_back(value); }
    void push(T&& value) { emplace_back(std::move(value)); }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop on empty list");
        }

        Node* node = tail_;
        T out = std::move(node->value);
        tail_ = node->prev;

        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node;
        --size_;
        return out;
    }

    void unshift(const T& value) { emplace_front(value); }
    void unshift(T&& value) { emplace_front(std::move(value)); }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift on empty list");
        }

        Node* node = head_;
        T out = std::move(node->value);
        head_ = node->next;

        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return out;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                Node* p = n->prev;
                Node* nx = n->next;

                if (p) {
                    p->next = nx;
                } else {
                    head_ = nx;
                }

                if (nx) {
                    nx->prev = p;
                } else {
                    tail_ = p;
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
