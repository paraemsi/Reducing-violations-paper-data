#pragma once
#include <cstdint>
#include <stdexcept>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::size_t list_size;
    
public:
    List() : head(nullptr), tail(nullptr), list_size(0) {}
    
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
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
        ++list_size;
    }
    
    T pop() {
        if (tail == nullptr) {
            throw std::runtime_error("Cannot pop from empty list");
        }
        Node* last_node = tail;
        T value = last_node->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete last_node;
        --list_size;
        return value;
    }
    
    T shift() {
        if (head == nullptr) {
            throw std::runtime_error("Cannot shift from empty list");
        }
        Node* first_node = head;
        T value = first_node->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete first_node;
        --list_size;
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
        ++list_size;
    }
    
    std::size_t count() const {
        return list_size;
    }
    
    bool erase(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
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
                --list_size;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Prevent copying for simplicity
    List(const List&) = delete;
    List& operator=(const List&) = delete;
};

}  // namespace linked_list
