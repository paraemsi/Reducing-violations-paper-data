#pragma once

#include <cstddef>
#include <stdexcept>

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
    List() : head(nullptr), tail(nullptr), sz(0) {}

    ~List() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push(const T& value) {
        Node* node = new Node(value);
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++sz;
    }

    T pop() {
        if (!tail) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = tail;
        T value = node->value;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;
        --sz;
        return value;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        ++sz;
    }

    T shift() {
        if (!head) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = head;
        T value = node->value;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;
        --sz;
        return value;
    }

    std::size_t count() const {
        return sz;
    }

    bool erase(const T& value) {
        Node* curr = head;
        while (curr) {
            if (curr->value == value) {
                if (curr->prev) {
                    curr->prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                if (curr->next) {
                    curr->next->prev = curr->prev;
                } else {
                    tail = curr->prev;
                }
                delete curr;
                --sz;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
};

}  // namespace linked_list
