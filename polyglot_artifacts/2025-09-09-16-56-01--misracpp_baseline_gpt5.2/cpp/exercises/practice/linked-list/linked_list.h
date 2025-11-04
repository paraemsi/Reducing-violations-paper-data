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

    void clear() noexcept {
        Node* cur = head_;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void remove_node(Node* n) noexcept {
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

public:
    List() = default;

    ~List() noexcept {
        clear();
    }

    List(const List& other) {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push(cur->value);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
                push(cur->value);
            }
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

    void push(T&& value) {
        Node* n = new Node(std::move(value));
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
            throw std::out_of_range("pop from empty List");
        }
        Node* n = tail_;
        T out = std::move(n->value);
        tail_ = n->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete n;
        --size_;
        return out;
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

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
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
            throw std::out_of_range("shift from empty List");
        }
        Node* n = head_;
        T out = std::move(n->value);
        head_ = n->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete n;
        --size_;
        return out;
    }

    std::size_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            if (cur->value == value) {
                remove_node(cur);
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
