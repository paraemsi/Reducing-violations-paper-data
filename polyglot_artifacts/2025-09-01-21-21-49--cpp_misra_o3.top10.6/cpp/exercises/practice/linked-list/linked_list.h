#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;

        explicit Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:
    List() : head_(nullptr), tail_(nullptr), size_(0U) {}

    ~List() {
        clear();
    }

    void push(const T& value) {
        Node* const node = new Node(value);
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }
        Node* const node = tail_;
        T const value = node->value;
        tail_ = node->prev;
        if (tail_ == nullptr) {
            head_ = nullptr;
        } else {
            tail_->next = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    void unshift(const T& value) {
        Node* const node = new Node(value);
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }
        Node* const node = head_;
        T const value = node->value;
        head_ = node->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev = nullptr;
        }
        delete node;
        --size_;
        return value;
    }

    std::size_t count() const {
        return size_;
    }

    bool erase(const T& value) {
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
    void clear() {
        Node* current = head_;
        while (current != nullptr) {
            Node* const next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }
};

}  // namespace linked_list
