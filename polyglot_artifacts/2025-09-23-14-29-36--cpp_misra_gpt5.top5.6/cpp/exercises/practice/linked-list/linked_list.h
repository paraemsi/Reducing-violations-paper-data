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

    void remove_node(Node* n) noexcept
    {
        if ((n == nullptr)) {
            return;
        }

        if ((n->prev != nullptr)) {
            n->prev->next = n->next;
        } else {
            head_ = n->next;
        }

        if ((n->next != nullptr)) {
            n->next->prev = n->prev;
        } else {
            tail_ = n->prev;
        }

        delete n;

        if ((size_ > static_cast<std::size_t>(0U))) {
            size_ -= static_cast<std::size_t>(1U);
        }
    }

    void clear() noexcept
    {
        Node* cur = head_;
        while ((cur != nullptr)) {
            Node* next_node = cur->next;
            delete cur;
            cur = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {}

    ~List() noexcept
    {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U))
    {
        Node* cur = other.head_;
        while ((cur != nullptr)) {
            push(cur->value);
            cur = cur->next;
        }
    }

    List& operator=(const List& other)
    {
        if ((this != &other)) {
            clear();
            Node* cur = other.head_;
            while ((cur != nullptr)) {
                push(cur->value);
                cur = cur->next;
            }
        }
        return *this;
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(List&& other) noexcept
    {
        if ((this != &other)) {
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

    void push(const T& value)
    {
        Node* n = new Node(value);
        n->prev = tail_;
        n->next = nullptr;

        if ((tail_ != nullptr)) {
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

        if ((tail_ != nullptr)) {
            tail_->next = n;
        } else {
            head_ = n;
        }

        tail_ = n;
        size_ += static_cast<std::size_t>(1U);
    }

    T pop()
    {
        if ((tail_ == nullptr)) {
            throw std::out_of_range("List::pop on empty list");
        }

        Node* n = tail_;
        T result = std::move(n->value);
        remove_node(n);
        return result;
    }

    void unshift(const T& value)
    {
        Node* n = new Node(value);
        n->prev = nullptr;
        n->next = head_;

        if ((head_ != nullptr)) {
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

        if ((head_ != nullptr)) {
            head_->prev = n;
        } else {
            tail_ = n;
        }

        head_ = n;
        size_ += static_cast<std::size_t>(1U);
    }

    T shift()
    {
        if ((head_ == nullptr)) {
            throw std::out_of_range("List::shift on empty list");
        }

        Node* n = head_;
        T result = std::move(n->value);
        remove_node(n);
        return result;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* cur = head_;
        while ((cur != nullptr)) {
            if ((cur->value == value)) {
                remove_node(cur);
                return true;
            } else {
                cur = cur->next;
            }
        }
        return false;
    }
};

}  // namespace linked_list
