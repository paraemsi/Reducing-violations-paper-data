#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

// Doubly linked list implemented as a template class.
// All template definitions are provided in this header.
template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(Node&&) = delete;
        ~Node() = default;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:
    // Constructors / destructor
    List() : head_(nullptr), tail_(nullptr), size_(0U) {}

    ~List() {
        clear();
    }

    // Copy constructor: deep copy
    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0U) {
        const Node* cur = other.head_;
        while (cur != nullptr) {
            push(cur->value);
            cur = cur->next;
        }
    }

    // Move constructor
    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    // Copy-and-swap assignment (by value for strong exception safety)
    List& operator=(List other) {
        swap(other);
        return *this;
    }

    void swap(List& other) noexcept {
        Node* const tmpHead = head_;
        head_ = other.head_;
        other.head_ = tmpHead;

        Node* const tmpTail = tail_;
        tail_ = other.tail_;
        other.tail_ = tmpTail;

        const std::size_t tmpSize = size_;
        size_ = other.size_;
        other.size_ = tmpSize;
    }

    // Capacity
    std::size_t count() const noexcept {
        return size_;
    }

    // Modifiers
    void push(const T& value) {
        Node* const n = new Node(value);
        append(n);
    }

    void push(T&& value) {
        Node* const n = new Node(std::move(value));
        append(n);
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop from empty list");
        } else {
            Node* const n = tail_;
            T ret = std::move(n->value);

            if (n->prev != nullptr) {
                n->prev->next = nullptr;
                tail_ = n->prev;
            } else {
                head_ = nullptr;
                tail_ = nullptr;
            }

            delete n;
            size_ -= 1U;
            return ret;
        }
    }

    void unshift(const T& value) {
        Node* const n = new Node(value);
        prepend(n);
    }

    void unshift(T&& value) {
        Node* const n = new Node(std::move(value));
        prepend(n);
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty list");
        } else {
            Node* const n = head_;
            T ret = std::move(n->value);

            if (n->next != nullptr) {
                n->next->prev = nullptr;
                head_ = n->next;
            } else {
                head_ = nullptr;
                tail_ = nullptr;
            }

            delete n;
            size_ -= 1U;
            return ret;
        }
    }

    // Erase first occurrence of value. Returns true if removed.
    bool erase(const T& value) {
        Node* cur = head_;
        while (cur != nullptr) {
            if (cur->value == value) {
                Node* const prevNode = cur->prev;
                Node* const nextNode = cur->next;

                if (prevNode != nullptr) {
                    prevNode->next = nextNode;
                } else {
                    head_ = nextNode;
                }

                if (nextNode != nullptr) {
                    nextNode->prev = prevNode;
                } else {
                    tail_ = prevNode;
                }

                delete cur;
                size_ -= 1U;
                return true;
            } else {
                cur = cur->next;
            }
        }
        return false;
    }

private:
    void clear() noexcept {
        Node* cur = head_;
        while (cur != nullptr) {
            Node* const next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

    void append(Node* n) {
        n->prev = tail_;
        n->next = nullptr;

        if (tail_ != nullptr) {
            tail_->next = n;
        } else {
            head_ = n;
        }

        tail_ = n;
        size_ += 1U;
    }

    void prepend(Node* n) {
        n->next = head_;
        n->prev = nullptr;

        if (head_ != nullptr) {
            head_->prev = n;
        } else {
            tail_ = n;
        }

        head_ = n;
        size_ += 1U;
    }
};

}  // namespace linked_list
