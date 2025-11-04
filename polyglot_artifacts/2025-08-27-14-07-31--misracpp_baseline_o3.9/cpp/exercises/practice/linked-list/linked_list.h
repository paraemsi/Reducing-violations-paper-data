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
        explicit Node(const T& v, Node* p = nullptr, Node* n = nullptr)
            : value(v), prev(p), next(n) {}
        explicit Node(T&& v, Node* p = nullptr, Node* n = nullptr)
            : value(std::move(v)), prev(p), next(n) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

public:
    List() = default;

    ~List() { clear(); }

    // Copying disabled (keeps exercise simple)
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // Move semantics
    List(List&& other) noexcept { move_from(std::move(other)); }
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            move_from(std::move(other));
        }
        return *this;
    }

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) { emplace_back(value); }
    void push(T&& value) { emplace_back(std::move(value)); }

    T pop() {
        if (!tail_) {
            throw std::out_of_range("pop called on empty list");
        }
        Node* node = tail_;
        T val = std::move(node->value);

        tail_ = tail_->prev;
        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        --size_;
        return val;
    }

    void unshift(const T& value) { emplace_front(value); }
    void unshift(T&& value) { emplace_front(std::move(value)); }

    T shift() {
        if (!head_) {
            throw std::out_of_range("shift called on empty list");
        }
        Node* node = head_;
        T val = std::move(node->value);

        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return val;
    }

    bool erase(const T& value) {
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            if (cur->value == value) {
                detach(cur);
                return true;
            }
        }
        return false;
    }

private:
    template <typename U>
    void emplace_back(U&& value) {
        Node* node = new Node(std::forward<U>(value), tail_, nullptr);
        if (tail_) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    template <typename U>
    void emplace_front(U&& value) {
        Node* node = new Node(std::forward<U>(value), nullptr, head_);
        if (head_) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
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

    void move_from(List&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
};

}  // namespace linked_list
