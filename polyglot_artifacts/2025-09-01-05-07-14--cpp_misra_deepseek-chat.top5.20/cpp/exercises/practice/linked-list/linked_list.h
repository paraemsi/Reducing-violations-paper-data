#pragma once
#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        explicit Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::int32_t list_count;
    
public:
    List() : head(nullptr), tail(nullptr), list_count(0) {}
    
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
        ++list_count;
    }
    
    T pop() {
        if (tail == nullptr) {
            throw std::runtime_error("Cannot pop from empty list");
        }
        Node* temp = tail;
        T value = temp->value;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --list_count;
        return value;
    }
    
    T shift() {
        if (head == nullptr) {
            throw std::runtime_error("Cannot shift from empty list");
        }
        Node* temp = head;
        T value = temp->value;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --list_count;
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
        ++list_count;
    }
    
    std::int32_t count() const {
        return list_count;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                // Handle the case where current is the head node
                if (current->prev == nullptr) {
                    head = current->next;
                } else {
                    current->prev->next = current->next;
                }
                
                // Handle the case where current is the tail node
                if (current->next == nullptr) {
                    tail = current->prev;
                } else {
                    current->next->prev = current->prev;
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
