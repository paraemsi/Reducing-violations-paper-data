#pragma once

#include <cstdint>
#include <stdexcept>
#include <initializer_list>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::uint32_t size_;

    void clear() noexcept
    {
        Node* current = head_;
        while (current != nullptr) {
            Node* const nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::uint32_t>(0U);
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(static_cast<std::uint32_t>(0U)) {}

    explicit List(std::initializer_list<T> init) : List()
    {
        for (const T& value : init) {
            push(value);
        }
    }

    /* rule-of-five: deep copy / move support */

    List(const List& other) : List()
    {
        Node* current = other.head_;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            Node* current = other.head_;
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::uint32_t>(0U);
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
            other.size_ = static_cast<std::uint32_t>(0U);
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* const newNode = new Node(value);
        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            newNode->prev = tail_;
            tail_->next = newNode;
            tail_ = newNode;
        }
        size_ += static_cast<std::uint32_t>(1U);
    }

    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty List");
        }
        Node* const nodeToRemove = tail_;
        T const value = nodeToRemove->data;

        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete nodeToRemove;
        size_ -= static_cast<std::uint32_t>(1U);
        return value;
    }

    void unshift(const T& value)
    {
        Node* const newNode = new Node(value);
        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            newNode->next = head_;
            head_->prev = newNode;
            head_ = newNode;
        }
        size_ += static_cast<std::uint32_t>(1U);
    }

    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty List");
        }
        Node* const nodeToRemove = head_;
        T const value = nodeToRemove->data;

        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete nodeToRemove;
        size_ -= static_cast<std::uint32_t>(1U);
        return value;
    }

    std::uint32_t count() const noexcept
    {
        return size_;
    }

    /* Convenience alias expected by some client code */
    std::uint32_t size() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
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
                size_ -= static_cast<std::uint32_t>(1U);
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
