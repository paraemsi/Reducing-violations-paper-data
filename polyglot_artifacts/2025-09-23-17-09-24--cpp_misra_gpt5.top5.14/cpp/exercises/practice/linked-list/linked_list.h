#pragma once

#include <cstddef>
#include <cstdint>
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

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void unlink_node(Node* n)
    {
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

        if (size_ > static_cast<std::size_t>(0U)) {
            size_ -= static_cast<std::size_t>(1U);
        }
    }

    void copy_from(const List& other)
    {
        Node* cur = other.head_;
        while (cur != nullptr) {
            push(cur->value);
            cur = cur->next;
        }
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {}

    ~List()
    {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U))
    {
        copy_from(other);
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }

    void clear() noexcept
    {
        Node* cur = head_;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

    void push(const T& value)
    {
        Node* n = new Node(value);
        n->prev = tail_;
        n->next = nullptr;

        if (tail_ != nullptr) {
            tail_->next = n;
        } else {
            head_ = n;
        }

        tail_ = n;
        size_ += static_cast<std::size_t>(1U);
    }

    void push(T&& value)
    {
        Node* n = new Node(std::move(value));
        n->prev = tail_;
        n->next = nullptr;

        if (tail_ != nullptr) {
            tail_->next = n;
        } else {
            head_ = n;
        }

        tail_ = n;
        size_ += static_cast<std::size_t>(1U);
    }

    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* n = tail_;
        T ret = std::move(n->value);

        if (n->prev != nullptr) {
            n->prev->next = nullptr;
            tail_ = n->prev;
        } else {
            head_ = nullptr;
            tail_ = nullptr;
        }

        delete n;
        size_ -= static_cast<std::size_t>(1U);
        return ret;
    }

    void unshift(const T& value)
    {
        Node* n = new Node(value);
        n->prev = nullptr;
        n->next = head_;

        if (head_ != nullptr) {
            head_->prev = n;
        } else {
            tail_ = n;
        }

        head_ = n;
        size_ += static_cast<std::size_t>(1U);
    }

    void unshift(T&& value)
    {
        Node* n = new Node(std::move(value));
        n->prev = nullptr;
        n->next = head_;

        if (head_ != nullptr) {
            head_->prev = n;
        } else {
            tail_ = n;
        }

        head_ = n;
        size_ += static_cast<std::size_t>(1U);
    }

    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* n = head_;
        T ret = std::move(n->value);

        if (n->next != nullptr) {
            n->next->prev = nullptr;
            head_ = n->next;
        } else {
            head_ = nullptr;
            tail_ = nullptr;
        }

        delete n;
        size_ -= static_cast<std::size_t>(1U);
        return ret;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* cur = head_;
        while (cur != nullptr) {
            if ((cur->value == value)) {
                unlink_node(cur);
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};

}  // namespace linked_list
