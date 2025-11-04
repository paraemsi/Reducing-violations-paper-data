#pragma once
#include <cstdint>

namespace linked_list {

// Define a type alias for the count type to avoid using standard integer type names directly
using count_t = std::int32_t;

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
    count_t list_count;
    
public:
    List() : head(nullptr), tail(nullptr), list_count(0) {}
    
    ~List() {
        Node* current = head;
        while ((current != nullptr)) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void push(const T& value) {
        Node* new_node = new Node(value);
        if ((tail == nullptr)) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++list_count;
    }
    
    T pop() {
        if ((tail == nullptr)) {
            // Handle error - perhaps throw an exception
            // For now, we'll return a default value
            return T();
        }
        Node* last_node = tail;
        T value = last_node->value;
        tail = tail->prev;
        if ((tail != nullptr)) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete last_node;
        --list_count;
        return value;
    }
    
    T shift() {
        if ((head == nullptr)) {
            // Handle error
            return T();
        }
        Node* first_node = head;
        T value = first_node->value;
        head = head->next;
        if ((head != nullptr)) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete first_node;
        --list_count;
        return value;
    }
    
    void unshift(const T& value) {
        Node* new_node = new Node(value);
        if ((head == nullptr)) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++list_count;
    }
    
    count_t count() const {
        return list_count;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while ((current != nullptr)) {
            if ((current->value == value)) {
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
                --list_count;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
