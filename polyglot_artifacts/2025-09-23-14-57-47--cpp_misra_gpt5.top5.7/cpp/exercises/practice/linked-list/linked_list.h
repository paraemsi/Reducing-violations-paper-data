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

    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<std::size_t>(0U);
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {}

    ~List() {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<std::size_t>(0U)) {
        Node* n = other.head_;
        while (n != nullptr) {
            push(n->value);
            n = n->next;
        }
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* n = other.head_;
            while (n != nullptr) {
                push(n->value);
                n = n->next;
            }
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
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

    void push(const T& value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    void push(T&& value) {
        Node* node = new Node(std::move(value));
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("List::pop on empty list");
        }
        Node* node = tail_;
        T result = std::move(node->value);
        tail_ = node->prev;
        if (tail_ == nullptr) {
            head_ = nullptr;
        } else {
            tail_->next = nullptr;
        }
        delete node;
        size_ = size_ - static_cast<std::size_t>(1U);
        return result;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        size_ = size_ + static_cast<std::size_t>(1U);
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("List::shift on empty list");
        }
        Node* node = head_;
        T result = std::move(node->value);
        head_ = node->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev = nullptr;
        }
        delete node;
        size_ = size_ - static_cast<std::size_t>(1U);
        return result;
    }

    std::size_t count() const noexcept {
        return size_;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if ((current->value) == value) {
                Node* prev = current->prev;
                Node* next = current->next;

                if (prev != nullptr) {
                    prev->next = next;
                } else {
                    head_ = next;
                }

                if (next != nullptr) {
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
};

}  // namespace linked_list
