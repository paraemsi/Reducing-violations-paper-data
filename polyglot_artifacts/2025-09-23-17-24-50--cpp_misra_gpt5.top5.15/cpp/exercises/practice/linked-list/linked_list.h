#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    using value_type = T;
    using size_type = std::size_t;

    List() noexcept : head_(nullptr), tail_(nullptr), size_(static_cast<size_type>(0U)) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(static_cast<size_type>(0U)) {
        Node* curr = other.head_;
        while (curr != nullptr) {
            push(curr->value);
            curr = curr->next;
        }
    }

    List(List&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<size_type>(0U);
    }

    ~List() noexcept {
        clear_();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            List tmp(other);
            swap(tmp);
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear_();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = static_cast<size_type>(0U);
        }
        return *this;
    }

    void swap(List& other) noexcept {
        Node* const tmp_head = head_;
        Node* const tmp_tail = tail_;
        const size_type tmp_size = size_;
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = tmp_head;
        other.tail_ = tmp_tail;
        other.size_ = tmp_size;
    }

    // push: adds an element to the end
    void push(const T& value) {
        Node* n = new Node(value);
        if (tail_ == nullptr) {
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    void push(T&& value) {
        Node* n = new Node(std::move(value));
        if (tail_ == nullptr) {
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    // pop: removes and returns the last element
    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty List");
        }
        Node* n = tail_;
        if (n->prev != nullptr) {
            tail_ = n->prev;
            tail_->next = nullptr;
        } else {
            // removing the only element
            head_ = nullptr;
            tail_ = nullptr;
        }
        --size_;
        T out = std::move(n->value);
        delete n;
        return out;
    }

    // shift: removes and returns the first element
    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty List");
        }
        Node* n = head_;
        if (n->next != nullptr) {
            head_ = n->next;
            head_->prev = nullptr;
        } else {
            // removing the only element
            head_ = nullptr;
            tail_ = nullptr;
        }
        --size_;
        T out = std::move(n->value);
        delete n;
        return out;
    }

    // unshift: adds an element to the start
    void unshift(const T& value) {
        Node* n = new Node(value);
        if (head_ == nullptr) {
            head_ = n;
            tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    void unshift(T&& value) {
        Node* n = new Node(std::move(value));
        if (head_ == nullptr) {
            head_ = n;
            tail_ = n;
        } else {
            n->next = head_;
            head_->prev = n;
            head_ = n;
        }
        ++size_;
    }

    // count: returns the number of elements
    size_type count() const noexcept {
        return size_;
    }

    // erase: removes the first occurrence of value; returns true if deleted
    bool erase(const T& value) {
        Node* curr = head_;
        while (curr != nullptr) {
            if (curr->value == value) {
                if (curr->prev != nullptr) {
                    curr->prev->next = curr->next;
                } else {
                    head_ = curr->next;
                }
                if (curr->next != nullptr) {
                    curr->next->prev = curr->prev;
                } else {
                    tail_ = curr->prev;
                }
                --size_;
                delete curr;
                return true;
            } else {
                curr = curr->next;
            }
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}

        T value;
        Node* prev;
        Node* next;
    };

    void clear_() noexcept {
        Node* curr = head_;
        while (curr != nullptr) {
            Node* const next = curr->next;
            delete curr;
            curr = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = static_cast<size_type>(0U);
    }

    Node* head_;
    Node* tail_;
    size_type size_;
};

}  // namespace linked_list
