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

    Node* head_;
    Node* tail_;
    std::size_t size_;

    void clear() noexcept
    {
        Node* current = head_;
        while (current != nullptr) {
            Node* const to_delete = current;
            current = current->next;
            delete to_delete;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

public:
    List() noexcept : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {}

    ~List()
    {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U))
    {
        Node* current = other.head_;
        while (current != nullptr) {
            push(current->value);
            current = current->next;
        }
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(const List& other)
    {
        if ((this != &other)) {
            List tmp(other);
            // Swap members
            std::swap(head_, tmp.head_);
            std::swap(tail_, tmp.tail_);
            std::swap(size_, tmp.size_);
        }
        return *this;
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
        Node* const node = new Node(value);
        if ((tail_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    void push(T&& value)
    {
        Node* const node = new Node(std::move(value));
        if ((tail_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    T pop()
    {
        if ((tail_ == nullptr)) {
            throw std::out_of_range("pop from empty list");
        }
        Node* const node = tail_;
        T ret = std::move(node->value);
        tail_ = node->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        size_ = size_ - static_cast<std::size_t>(1U);
        return ret;
    }

    void unshift(const T& value)
    {
        Node* const node = new Node(value);
        if ((head_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    void unshift(T&& value)
    {
        Node* const node = new Node(std::move(value));
        if ((head_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    T shift()
    {
        if ((head_ == nullptr)) {
            throw std::out_of_range("shift from empty list");
        }
        Node* const node = head_;
        T ret = std::move(node->value);
        head_ = node->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        size_ = size_ - static_cast<std::size_t>(1U);
        return ret;
    }

    bool erase(const T& value)
    {
        Node* current = head_;
        while (current != nullptr) {
            if ((current->value == value)) {
                Node* const prev = current->prev;
                Node* const next = current->next;
                if ((prev != nullptr)) {
                    prev->next = next;
                } else {
                    head_ = next;
                }
                if ((next != nullptr)) {
                    next->prev = prev;
                } else {
                    tail_ = prev;
                }
                delete current;
                size_ = size_ - static_cast<std::size_t>(1U);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }
};

}  // namespace linked_list
