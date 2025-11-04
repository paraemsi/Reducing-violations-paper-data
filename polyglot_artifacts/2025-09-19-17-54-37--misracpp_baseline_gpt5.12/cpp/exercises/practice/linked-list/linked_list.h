#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}
    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }
    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
    List& operator=(List other) noexcept {
        swap(other);
        return *this;
    }
    ~List() { clear(); }

    void push(const T& value) {
        Node* n = new Node(value);
        n->prev = tail_;
        if (tail_) tail_->next = n;
        tail_ = n;
        if (!head_) head_ = n;
        ++size_;
    }

    T pop() {
        if (!tail_) throw std::out_of_range("pop from empty List");
        Node* n = tail_;
        T value = std::move(n->value);
        tail_ = n->prev;
        if (tail_) tail_->next = nullptr;
        else head_ = nullptr;
        delete n;
        --size_;
        return value;
    }

    T shift() {
        if (!head_) throw std::out_of_range("shift from empty List");
        Node* n = head_;
        T value = std::move(n->value);
        head_ = n->next;
        if (head_) head_->prev = nullptr;
        else tail_ = nullptr;
        delete n;
        --size_;
        return value;
    }

    void unshift(const T& value) {
        Node* n = new Node(value);
        n->next = head_;
        if (head_) head_->prev = n;
        head_ = n;
        if (!tail_) tail_ = n;
        ++size_;
    }

    std::size_t count() const noexcept { return size_; }

    bool erase(const T& value) {
        for (Node* n = head_; n != nullptr; n = n->next) {
            if (n->value == value) {
                if (n->prev) n->prev->next = n->next;
                else head_ = n->next;
                if (n->next) n->next->prev = n->prev;
                else tail_ = n->prev;
                delete n;
                --size_;
                return true;
            }
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        T value;
        Node* prev;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept {
        Node* n = head_;
        while (n) {
            Node* next = n->next;
            delete n;
            n = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    void swap(List& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }
};

}  // namespace linked_list
