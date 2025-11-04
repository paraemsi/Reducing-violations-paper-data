#pragma once

#include <cstdint>
#include <cstddef>

namespace linked_list {

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
    ~List();

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
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;
};

}  // namespace linked_list

// Implementation must be included for templates:
// Do NOT include the .cpp file here. Instead, include the implementation in the .cpp file only.
// This avoids ODR/linker errors and is the standard approach for C++ template classes
