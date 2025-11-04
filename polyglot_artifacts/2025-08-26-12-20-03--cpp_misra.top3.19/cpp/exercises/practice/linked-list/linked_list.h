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
        explicit Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
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
        sz = (sz + 1U);
    }

    T pop() {
        if (tail == nullptr) {
            throw "List is empty";
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
        sz = (sz + 1U);
    }

    T shift() {
        if (head == nullptr) {
            throw "List is empty";
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
                sz = (sz - 1U);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Disable copy and assignment
    List(const List&) = delete;
    List& operator=(const List&) = delete;
};

}  // namespace linked_list
