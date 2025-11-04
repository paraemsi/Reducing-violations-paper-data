#pragma once
#include <cstdint>
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
    std::int32_t list_size;

public:
    List() : head(nullptr), tail(nullptr), list_size(0) {}
    
    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        list_size++;
    }

    T pop() {
        if (tail == nullptr) {
            throw std::runtime_error("Cannot pop from empty list");
        }
        Node* temp = tail;
        T value = tail->value;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        list_size--;
        return value;
    }

    T shift() {
        if (head == nullptr) {
            throw std::runtime_error("Cannot shift from empty list");
        }
        Node* temp = head;
        T value = head->value;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        list_size--;
        return value;
    }

    void unshift(const T& value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        list_size++;
    }

    std::int32_t count() const {
        return list_size;
    }

    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                if (current == head) {
                    // Use shift to remove the head
                    shift();
                } else if (current == tail) {
                    // Use pop to remove the tail
                    pop();
                } else {
                    // Remove from the middle
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    list_size--;
                }
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
