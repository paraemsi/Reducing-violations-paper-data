#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:

public:
    List() = default;

    ~List() noexcept
    {
        clear();
    }

    List(const List& other)
    {
        for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
            push(cur->value);
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
                push(cur->value);
            }
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            head_  = other.head_;
            tail_  = other.tail_;
            size_  = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    void push(const T& value)
    {
        Node* new_node = new Node(value);
        new_node->prev = tail_;

        if (tail_ != nullptr) {
            tail_->next = new_node;
        } else {
            head_ = new_node;
        }

        tail_ = new_node;
        ++size_;
    }

    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop from empty list");
        }

        Node* node = tail_;
        T     value = node->value;

        tail_ = node->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node;
        --size_;
        return value;
    }

    void unshift(const T& value)
    {
        Node* new_node = new Node(value);
        new_node->next = head_;

        if (head_ != nullptr) {
            head_->prev = new_node;
        } else {
            tail_ = new_node;
        }

        head_ = new_node;
        ++size_;
    }

    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty list");
        }

        Node* node = head_;
        T     value = node->value;

        head_ = node->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node;
        --size_;
        return value;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* current = head_;
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }

                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v) {}

        T     value;
        Node* next{nullptr};
        Node* prev{nullptr};
    };

    void clear() noexcept
    {
        Node* cur = head_;
        while (cur != nullptr) {
            Node* next_node = cur->next;
            delete cur;
            cur = next_node;
        }

        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

    Node*       head_{nullptr};
    Node*       tail_{nullptr};
    std::size_t size_{0U};
};

}  // namespace linked_list
