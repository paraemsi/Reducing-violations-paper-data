#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    using size_type = std::size_t;

    List() noexcept
        : head_(nullptr)
        , tail_(nullptr)
        , size_(static_cast<size_type>(0U)) {
    }

    List(const List& other)
        : head_(nullptr)
        , tail_(nullptr)
        , size_(static_cast<size_type>(0U)) {
        copy_from(other);
    }

    List(List&& other) noexcept
        : head_(other.head_)
        , tail_(other.tail_)
        , size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<size_type>(0U);
    }

    ~List() noexcept {
        clear();
    }

    List& operator=(const List& other) {
        if ((this != &other)) {
            clear();
            copy_from(other);
        } else {
            // no action required
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if ((this != &other)) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = static_cast<size_type>(0U);
        } else {
            // no action required
        }
        return *this;
    }

    // Adds an element to the end of the list
    void push(const T& value) {
        Node* node = new Node(value);
        if ((tail_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ = (size_ + static_cast<size_type>(1U));
    }

    // Adds an element to the end of the list (rvalue overload)
    void push(T&& value) {
        Node* node = new Node(std::move(value));
        if ((tail_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ = (size_ + static_cast<size_type>(1U));
    }

    // Removes and returns the last element of the list
    T pop() {
        if ((tail_ == nullptr)) {
            throw std::runtime_error("pop from empty list");
        } else {
            // continue
        }

        Node* node = tail_;
        T out = std::move(node->value);
        tail_ = node->prev;
        if ((tail_ != nullptr)) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node;
        size_ = (size_ - static_cast<size_type>(1U));
        return out;
    }

    // Adds an element to the start of the list
    void unshift(const T& value) {
        Node* node = new Node(value);
        if ((head_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ = (size_ + static_cast<size_type>(1U));
    }

    // Adds an element to the start of the list (rvalue overload)
    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        if ((head_ == nullptr)) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ = (size_ + static_cast<size_type>(1U));
    }

    // Removes and returns the first element of the list
    T shift() {
        if ((head_ == nullptr)) {
            throw std::runtime_error("shift from empty list");
        } else {
            // continue
        }

        Node* node = head_;
        T out = std::move(node->value);
        head_ = node->next;
        if ((head_ != nullptr)) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node;
        size_ = (size_ - static_cast<size_type>(1U));
        return out;
    }

    // Returns the total number of elements in the current list
    size_type count() const noexcept {
        return size_;
    }

    // Erases the first occurrence of value from the list; returns true if erased
    bool erase(const T& value) {
        Node* cur = head_;
        while ((cur != nullptr)) {
            if ((cur->value == value)) {
                Node* const prev = cur->prev;
                Node* const next = cur->next;

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

                delete cur;
                size_ = (size_ - static_cast<size_type>(1U));
                return true;
            } else {
                // not matched yet
            }
            cur = cur->next;
        }
        return false;
    }

private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v)
            : value(v)
            , prev(nullptr)
            , next(nullptr) {
        }

        explicit Node(T&& v)
            : value(std::move(v))
            , prev(nullptr)
            , next(nullptr) {
        }
    };

    Node* head_;
    Node* tail_;
    size_type size_;

    void clear() noexcept {
        Node* cur = head_;
        while ((cur != nullptr)) {
            Node* const next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<size_type>(0U);
    }

    void copy_from(const List& other) {
        Node* cur = other.head_;
        while ((cur != nullptr)) {
            push(cur->value);
            cur = cur->next;
        }
    }
};

}  // namespace linked_list
