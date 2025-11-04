#pragma once

#include <cstdint>
#include <cstddef>

namespace linked_list {

using station_id_t = std::int32_t;

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        explicit Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t sz;

public:
    List() : head(nullptr), tail(nullptr), sz(0U) {}

    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
        tail = nullptr;
        sz = 0U;
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        sz = sz + 1U;
    }

    T pop() {
        if (tail == nullptr) {
            throw std::out_of_range("Cannot pop from empty list");
        }
        Node* node = tail;
        T value = node->value;
        if (tail->prev != nullptr) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = nullptr;
            tail = nullptr;
        }
        delete node;
        sz = sz - 1U;
        return value;
    }

    void unshift(const T& value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        sz = sz + 1U;
    }

    T shift() {
        if (head == nullptr) {
            throw std::out_of_range("Cannot shift from empty list");
        }
        Node* node = head;
        T value = node->value;
        if (head->next != nullptr) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = nullptr;
            tail = nullptr;
        }
        delete node;
        sz = sz - 1U;
        return value;
    }

    std::size_t count() const {
        return sz;
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
                sz = sz - 1U;
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
        : head(other.head), tail(other.tail), sz(other.sz) {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0U;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            // Clean up current list
            Node* current = head;
            while (current != nullptr) {
                Node* next_node = current->next;
                delete current;
                current = next_node;
            }
            head = other.head;
            tail = other.tail;
            sz = other.sz;
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0U;
        }
        return *this;
    }
};

}  // namespace linked_list

