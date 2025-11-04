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
        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t sz;

public:
    List() : head(nullptr), tail(nullptr), sz(0U) {}
    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        sz = 0U;
    }

    void push(const T& value);
    T pop();
    void unshift(const T& value);
    T shift();
    std::size_t count() const;
    bool erase(const T& value);

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
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
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
