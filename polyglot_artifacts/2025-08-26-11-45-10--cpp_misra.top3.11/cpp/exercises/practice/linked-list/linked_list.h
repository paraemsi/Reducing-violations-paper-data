#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>

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

//
// Template implementations moved here to avoid linker errors
//

template <typename T>
List<T>::~List() {
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

template <typename T>
void List<T>::push(const T& value) {
    Node* node = new Node(value);
    if (tail == nullptr) {
        head = node;
        tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    sz = (sz + 1U);
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        throw std::runtime_error("List is empty");
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
    sz = (sz - 1U);
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    sz = (sz + 1U);
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
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
    sz = (sz - 1U);
    return value;
}

template <typename T>
std::size_t List<T>::count() const {
    return sz;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if ((current->prev != nullptr) && (current->next != nullptr)) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            } else if (current->prev == nullptr) {
                // head node
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (current->next == nullptr) {
                // tail node
                tail = current->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            }
            delete current;
            sz = (sz - 1U);
            if (sz == 0U) {
                head = nullptr;
                tail = nullptr;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

// Move constructor
template <typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), sz(other.sz) {
    other.head = nullptr;
    other.tail = nullptr;
    other.sz = 0U;
}

// Move assignment
template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        // Clean up current resources before taking ownership
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

}  // namespace linked_list
