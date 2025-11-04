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

    void clear() noexcept {
        Node* curr = head_;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
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
    List() = default;

    List(const List& other) { copy_from(other); }

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

    ~List() { clear(); }

    std::size_t count() const noexcept { return size_; }

    void push(const T& value) {
        Node* node = new Node(value, tail_, nullptr);
        if (tail_)
            tail_->next = node;
        else
            head_ = node;
        tail_ = node;
        ++size_;
    }

    void push(T&& value) {
        Node* node = new Node(std::move(value), tail_, nullptr);
        if (tail_)
            tail_->next = node;
        else
            head_ = node;
        tail_ = node;
        ++size_;
    }

    T pop() {
        if (!tail_) throw std::out_of_range("pop from empty list");
        Node* node = tail_;
        T value = std::move(node->value);
        tail_ = node->prev;
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

    void unshift(T&& value) {
        Node* node = new Node(std::move(value), nullptr, head_);
        if (head_)
            head_->prev = node;
        else
            tail_ = node;
        head_ = node;
        ++size_;
    }

    T shift() {
        if (!head_) throw std::out_of_range("shift from empty list");
        Node* node = head_;
        T value = std::move(node->value);
        head_ = node->next;
        if (head_)
            head_->prev = nullptr;
        else
            tail_ = nullptr;
        delete node;
        --size_;
        return value;
    }

    bool erase(const T& value) {
        for (Node* n = head_; n; n = n->next) {
            if (n->value == value) {
                if (n->prev)
                    n->prev->next = n->next;
                else
                    head_ = n->next;

                if (n->next)
                    n->next->prev = n->prev;
                else
                    tail_ = n->prev;

                delete n;
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
