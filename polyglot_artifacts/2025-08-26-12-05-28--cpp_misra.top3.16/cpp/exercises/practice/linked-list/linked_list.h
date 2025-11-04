#pragma once

#include <cstdint>
#include <stdexcept> // for std::out_of_range

namespace linked_list {

// Move all implementation to the header for templates
template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::uint32_t size_;

public:
    List()
        : head(nullptr), tail(nullptr), size_(0U) {}

    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size_ = 0U;
    }

    void push(const T& value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            head = node;
            tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        size_ = size_ + 1U;
    }

    T pop() {
        if (tail == nullptr) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail;
        T value = node->value;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;
        size_ = size_ - 1U;
        return value;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size_ = size_ + 1U;
    }

    T shift() {
        if (head == nullptr) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head;
        T value = node->value;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;
        size_ = size_ - 1U;
        return value;
    }

    std::uint32_t count() const {
        return size_;
    }

    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                size_ = size_ - 1U;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Disable copy
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // Allow move
    List(List&& other) noexcept
        : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = nullptr;
            other.tail = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }
};

}  // namespace linked_list
