#pragma once

#include <cstdint>
#include <cstddef>

namespace linked_list {

typedef std::int32_t station_id_t;

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
    std::size_t sz;

public:
    List() : head(nullptr), tail(nullptr), sz(static_cast<std::size_t>(0)) {}

    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
        tail = nullptr;
        sz = static_cast<std::size_t>(0);
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
        sz = sz + static_cast<std::size_t>(1);
    }

    T pop() {
        if (tail == nullptr) {
            throw "pop from empty list";
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
        sz = sz - static_cast<std::size_t>(1);
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
        sz = sz + static_cast<std::size_t>(1);
    }

    T shift() {
        if (head == nullptr) {
            throw "shift from empty list";
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
        sz = sz - static_cast<std::size_t>(1);
        return value;
    }

    std::size_t count() const {
        return sz;
    }

    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                if ((current->prev) != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if ((current->next) != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                sz = sz - static_cast<std::size_t>(1);
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
        other.sz = static_cast<std::size_t>(0);
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
            other.sz = static_cast<std::size_t>(0);
        }
        return *this;
    }
};

}  // namespace linked_list
