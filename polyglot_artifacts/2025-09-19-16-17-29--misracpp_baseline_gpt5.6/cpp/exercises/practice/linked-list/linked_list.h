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

    void link_back(Node* n) {
        n->prev = tail_;
        n->next = nullptr;
        if (tail_) {
            tail_->next = n;
        }
        tail_ = n;
        if (!head_) {
            head_ = n;
        }
    }

    void link_front(Node* n) {
        n->prev = nullptr;
        n->next = head_;
        if (head_) {
            head_->prev = n;
        }
        head_ = n;
        if (!tail_) {
            tail_ = n;
        }
    }

    void delete_node(Node* n) {
        if (!n) return;
        if (n->prev) {
            n->prev->next = n->next;
        } else {
            head_ = n->next;
        }
        if (n->next) {
            n->next->prev = n->prev;
        } else {
            tail_ = n->prev;
        }
        delete n;
        --size_;
    }

    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~List() { clear(); }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            List tmp(other);
            swap(tmp);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void swap(List& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) {
        Node* n = new Node(value);
        link_back(n);
        ++size_;
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        link_back(n);
        ++size_;
    }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop from empty List");
        }
        Node* n = tail_;
        T val = std::move(n->value);
        if (n->prev) {
            tail_ = n->prev;
            tail_->next = nullptr;
        } else {
            head_ = tail_ = nullptr;
        }
        delete n;
        --size_;
        return val;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        link_front(n);
        ++size_;
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        link_front(n);
        ++size_;
    }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift from empty List");
        }
        Node* n = head_;
        T val = std::move(n->value);
        if (n->next) {
            head_ = n->next;
            head_->prev = nullptr;
        } else {
            head_ = tail_ = nullptr;
        }
        delete n;
        --size_;
        return val;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                delete_node(n);
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
